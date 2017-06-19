#include "StdAfx.h"
#include ".\cap.h"

CCap::CCap(void)
{
	//初始化变量
	m_pVW			=   NULL;   
	m_pMC			=   NULL;   
	m_pGB			=   NULL;   
	m_pCapture		=   NULL;  
	m_pBF			=	NULL;
	m_pGrabber		=	NULL;
	m_pDevice		= new LPTSTR[MAX_DEVICE];
	m_nDeviceCount	= 0;
	m_hWnd			= NULL;
	m_bRunning		= FALSE;
}
CCap::~CCap(void)
{
	Release();
}
//枚举设备列表
int CCap::EnumDevices(HWND hList)
{
	m_nDeviceCount = 0; 
	//创建COM对象实例 
	ICreateDevEnum *pCreateDevEnum; 
	HRESULT hr = CoCreateInstance(CLSID_SystemDeviceEnum, 
		NULL, CLSCTX_INPROC_SERVER, IID_ICreateDevEnum, 
		(void**)&pCreateDevEnum); 
	if (FAILED(hr)) 
		return -1; 
	//创建枚举器
	CComPtr<IEnumMoniker> pEm; 
	hr = pCreateDevEnum->CreateClassEnumerator(
		CLSID_VideoInputDeviceCategory,&pEm, 0); 
	if (FAILED(hr) || pEm == NULL) 
		return -1; 
	//轮询每一个设备
	pEm->Reset(); 
	ULONG cFetched; 
	IMoniker *pM; 
	while(hr = pEm->Next(1, &pM, &cFetched), hr == S_OK) 
	{ 
		IPropertyBag *pBag; 
		//准备读取属性
		hr = pM->BindToStorage(0, 0, IID_IPropertyBag, (void **)&pBag); 
		if(SUCCEEDED(hr)) 
		{
			VARIANT var; 
			var.vt = VT_BSTR; 
			//获取友好名称
			hr = pBag->Read(L"FriendlyName", &var, NULL); 
			if (hr == NOERROR) 
			{
				TCHAR *pBuf = new TCHAR[512];
				*pBuf = _T('\0');
				
#ifndef UNICODE
				WideCharToMultiByte(
					CP_ACP, 0, var.bstrVal, -1, pBuf, 500, NULL, NULL);
#else
				_tcscpy(pBuf, var.bstrVal);
#endif
				SysFreeString(var.bstrVal);
				//保存该名称
				m_pDevice[m_nDeviceCount] = pBuf;
				m_nDeviceCount++;
				//将其显示到列表中
				if(hList)
					::SendMessage(hList, CB_ADDSTRING, 0, (LPARAM)pBuf);
			}
			pBag->Release();
		}
		pM->Release();
	}
	return m_nDeviceCount; 
}
//初始化
HRESULT CCap::Init(int iDeviceID)
{
	if(iDeviceID < 0)
		return S_FALSE;
	//初始化GraphBuilder
	HRESULT hr; 
	hr = InitCaptureGraphBuilder(); 
	if (FAILED(hr))
		return hr; 
	//连接Filter
	if(!BindFilter(iDeviceID, &m_pBF))
		return S_FALSE; 
	hr = m_pGB->AddFilter(m_pBF, L"Capture Filter"); 
	//创建ISampleGrabbe 
	hr = m_pGrabber.CoCreateInstance(CLSID_SampleGrabber); 
	if(!m_pGrabber)	return hr; 
	CComQIPtr<IBaseFilter, &IID_IBaseFilter> pGrabBase(m_pGrabber); 
	//设置视频格式 
	AM_MEDIA_TYPE mt; 
	ZeroMemory(&mt, sizeof(AM_MEDIA_TYPE)); 
	mt.majortype = MEDIATYPE_Video; 
	mt.subtype = MEDIASUBTYPE_RGB24; 
	hr = m_pGrabber->SetMediaType(&mt); 
	if(FAILED(hr))
		return hr; 
	//链接Filter
	hr = m_pGB->AddFilter(pGrabBase, L"Grabber"); 
	if(FAILED(hr))
		return hr; 
	//预览或采集视频 
	hr = m_pCapture->RenderStream(
		&PIN_CATEGORY_PREVIEW, &MEDIATYPE_Video,m_pBF,pGrabBase,NULL); 
	if(FAILED(hr)) 
		hr = m_pCapture->RenderStream(
		&PIN_CATEGORY_CAPTURE, &MEDIATYPE_Video,m_pBF,pGrabBase,NULL); 
	if(FAILED(hr))
		return hr; 
	//获取媒体格式
	hr = m_pGrabber->GetConnectedMediaType(&mt); 
	if (FAILED(hr))
		return hr; 
	VIDEOINFOHEADER * vih = (VIDEOINFOHEADER*) mt.pbFormat; 
	//保存图像大小
	m_cb.SetImageInfo(vih->bmiHeader.biWidth, vih->bmiHeader.biHeight);
	FreeMediaType(mt); 
	//设置选项
	hr = m_pGrabber->SetBufferSamples(FALSE); 
	hr = m_pGrabber->SetOneShot(FALSE); 
	//设置回调对象
	hr = m_pGrabber->SetCallback(&m_cb, 1); 
	//设置视频窗口
	SetupVideoWindow();
	return S_OK; 
}
//释放对象
void CCap::Release()
{
	if(m_nDeviceCount > 0)
	{
		TCHAR *p;
		for(int i=0; i<m_nDeviceCount; i++)
		{
			p = m_pDevice[i];
			delete []p;
		}
		delete []m_pDevice;
		m_pDevice = NULL;
		m_nDeviceCount = 0;
	}
	if(m_pMC) 
	{
		m_pMC->Stop(); 
		SafeRelease(m_pMC);
	}
	if(m_pVW)
	{ 
		m_pVW->put_Owner(NULL); 
		SafeRelease(m_pVW);
	} 
	SafeRelease(m_pCapture); 
	SafeRelease(m_pMC); 
	if(m_pGB)
		m_pGB->RemoveFilter(m_pBF);
	SafeRelease(m_pGB); 
	m_pGrabber = NULL;
	if(m_hWnd)
	{
		DestroyWindow(m_hWnd);
		m_hWnd = NULL;
	}
}
//开始
HRESULT CCap::Run()
{
	if(!m_pMC)
		return S_FALSE;
	HRESULT hr = m_pMC->Run();
	return hr;
}
//暂停
HRESULT CCap::Pause()
{
	if(!m_pMC)
		return S_FALSE;
	return m_pMC->Pause();
}
//停止
HRESULT CCap::Stop()
{
	if(!m_pMC)
		return S_FALSE;
	return m_pMC->Stop();
}
//获取ISampleGrabberCB
CSampleCB *CCap::GetSampleCB()
{
	return &m_cb;
}
//根据设备名查找设备序号，如果返回-1代表没有找到设备
int CCap::FindDeviceByName(LPCTSTR lpName)
{
	int id = -1;
	if(m_nDeviceCount > 0)
	{
		TCHAR *p;
		for(int i=0; i<m_nDeviceCount; i++)
		{
			p = m_pDevice[i];
			if(_tcscmp(lpName, p) == 0)
			{
				id = i;
				break;
			}
		}
	}
	return id;
}
//获取该序号的设备名称
LPCTSTR CCap::GetDeviceName(int nIndex)
{
	if(nIndex < 0 || nIndex >= m_nDeviceCount)
	{
		DebugBreak();
		return NULL;
	}
	return m_pDevice[nIndex];
}
//获取设备总数
int CCap::GetDeviceCount()
{
	return m_nDeviceCount;
}
void CCap::FreeMediaType(AM_MEDIA_TYPE& mt)
{
	if (mt.cbFormat != 0) 
	{ 
		CoTaskMemFree((PVOID)mt.pbFormat); 
		mt.cbFormat = 0; 
		mt.pbFormat = NULL; 
	} 
	if (mt.pUnk != NULL) 
	{ 
		mt.pUnk->Release(); 
		mt.pUnk = NULL; 
	}
}
//连接Filter
BOOL CCap::BindFilter(int nDeviceId, IBaseFilter **pFilter)
{
	if (nDeviceId < 0) 
		return FALSE; 
	//枚举设备 
	CComPtr<ICreateDevEnum> pCreateDevEnum; 
	HRESULT hr = CoCreateInstance(
		CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER, 
		IID_ICreateDevEnum, (void**)&pCreateDevEnum); 
	if (hr != NOERROR) 
		return FALSE; 
	//创建枚举器
	CComPtr<IEnumMoniker> pEm; 
	hr = pCreateDevEnum->CreateClassEnumerator(
		CLSID_VideoInputDeviceCategory,&pEm, 0); 
	if (hr != NOERROR) 
		return FALSE; 
	//枚举设备
	pEm->Reset(); 
	ULONG cFetched; 
	IMoniker *pM; 
	int index = 0; 
	while(hr = pEm->Next(1, &pM, &cFetched), hr == S_OK, index <= nDeviceId) 
	{ 
		IPropertyBag *pBag; 
		hr = pM->BindToStorage(0, 0, IID_IPropertyBag, (void **)&pBag); 
		if(SUCCEEDED(hr)) 
		{ 
			VARIANT var; 
			var.vt = VT_BSTR; 
			hr = pBag->Read(L"FriendlyName", &var, NULL); 
			if (hr == NOERROR) 
			{ 
				if (index == nDeviceId) 
				{
					//连接到指定序号的设备
					pM->BindToObject(
						0, 0, IID_IBaseFilter, (void**)pFilter); 
				} 
				SysFreeString(var.bstrVal); 
			} 
			pBag->Release(); 
		} 
		pM->Release(); 
		index++; 
	} 
	return TRUE; 
}
//设置视频窗口
HRESULT CCap::SetupVideoWindow()
{
	//创建一个隐藏的窗口
	m_hWnd = CreateWindow(_T("STATIC"), 
		_T(""), WS_POPUP, 0, 0, 1, 1, NULL, NULL, NULL, NULL);
	HRESULT hr;
	hr = m_pVW->put_Owner((OAHWND)m_hWnd); 
	if (FAILED(hr))
		return hr; 
	hr = m_pVW->put_WindowStyle(WS_CHILD | WS_CLIPCHILDREN); 
	if (FAILED(hr))
		return hr; 
	//隐藏视频窗口
	hr = m_pVW->put_Visible(OAFALSE); 
	return hr; 
}
//初始化GraphBuilder
HRESULT CCap::InitCaptureGraphBuilder()
{
	HRESULT hr; 
	//创建IGraphBuilder接口 
	hr=CoCreateInstance(CLSID_FilterGraph, 
		NULL, CLSCTX_INPROC_SERVER, 
		IID_IGraphBuilder, (void **)&m_pGB); 
	//创建ICaptureGraphBuilder2接口 
	hr = CoCreateInstance (
		CLSID_CaptureGraphBuilder2 , NULL, CLSCTX_INPROC, 
		IID_ICaptureGraphBuilder2, (void **) &m_pCapture); 
	if (FAILED(hr))
		return hr; 
	m_pCapture->SetFiltergraph(m_pGB); 
	//获取IMediaControl接口
	hr = m_pGB->QueryInterface(IID_IMediaControl, (void **)&m_pMC); 
	if (FAILED(hr))
		return hr; 
	//获取IVideoWindow接口
	hr = m_pGB->QueryInterface(IID_IVideoWindow, (LPVOID *) &m_pVW); 
	if (FAILED(hr))
		return hr; 
	return hr; 
}