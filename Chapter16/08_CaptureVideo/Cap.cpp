#include "StdAfx.h"
#include ".\cap.h"

CCap::CCap(void)
{
	//��ʼ������
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
//ö���豸�б�
int CCap::EnumDevices(HWND hList)
{
	m_nDeviceCount = 0; 
	//����COM����ʵ�� 
	ICreateDevEnum *pCreateDevEnum; 
	HRESULT hr = CoCreateInstance(CLSID_SystemDeviceEnum, 
		NULL, CLSCTX_INPROC_SERVER, IID_ICreateDevEnum, 
		(void**)&pCreateDevEnum); 
	if (FAILED(hr)) 
		return -1; 
	//����ö����
	CComPtr<IEnumMoniker> pEm; 
	hr = pCreateDevEnum->CreateClassEnumerator(
		CLSID_VideoInputDeviceCategory,&pEm, 0); 
	if (FAILED(hr) || pEm == NULL) 
		return -1; 
	//��ѯÿһ���豸
	pEm->Reset(); 
	ULONG cFetched; 
	IMoniker *pM; 
	while(hr = pEm->Next(1, &pM, &cFetched), hr == S_OK) 
	{ 
		IPropertyBag *pBag; 
		//׼����ȡ����
		hr = pM->BindToStorage(0, 0, IID_IPropertyBag, (void **)&pBag); 
		if(SUCCEEDED(hr)) 
		{
			VARIANT var; 
			var.vt = VT_BSTR; 
			//��ȡ�Ѻ�����
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
				//���������
				m_pDevice[m_nDeviceCount] = pBuf;
				m_nDeviceCount++;
				//������ʾ���б���
				if(hList)
					::SendMessage(hList, CB_ADDSTRING, 0, (LPARAM)pBuf);
			}
			pBag->Release();
		}
		pM->Release();
	}
	return m_nDeviceCount; 
}
//��ʼ��
HRESULT CCap::Init(int iDeviceID)
{
	if(iDeviceID < 0)
		return S_FALSE;
	//��ʼ��GraphBuilder
	HRESULT hr; 
	hr = InitCaptureGraphBuilder(); 
	if (FAILED(hr))
		return hr; 
	//����Filter
	if(!BindFilter(iDeviceID, &m_pBF))
		return S_FALSE; 
	hr = m_pGB->AddFilter(m_pBF, L"Capture Filter"); 
	//����ISampleGrabbe 
	hr = m_pGrabber.CoCreateInstance(CLSID_SampleGrabber); 
	if(!m_pGrabber)	return hr; 
	CComQIPtr<IBaseFilter, &IID_IBaseFilter> pGrabBase(m_pGrabber); 
	//������Ƶ��ʽ 
	AM_MEDIA_TYPE mt; 
	ZeroMemory(&mt, sizeof(AM_MEDIA_TYPE)); 
	mt.majortype = MEDIATYPE_Video; 
	mt.subtype = MEDIASUBTYPE_RGB24; 
	hr = m_pGrabber->SetMediaType(&mt); 
	if(FAILED(hr))
		return hr; 
	//����Filter
	hr = m_pGB->AddFilter(pGrabBase, L"Grabber"); 
	if(FAILED(hr))
		return hr; 
	//Ԥ����ɼ���Ƶ 
	hr = m_pCapture->RenderStream(
		&PIN_CATEGORY_PREVIEW, &MEDIATYPE_Video,m_pBF,pGrabBase,NULL); 
	if(FAILED(hr)) 
		hr = m_pCapture->RenderStream(
		&PIN_CATEGORY_CAPTURE, &MEDIATYPE_Video,m_pBF,pGrabBase,NULL); 
	if(FAILED(hr))
		return hr; 
	//��ȡý���ʽ
	hr = m_pGrabber->GetConnectedMediaType(&mt); 
	if (FAILED(hr))
		return hr; 
	VIDEOINFOHEADER * vih = (VIDEOINFOHEADER*) mt.pbFormat; 
	//����ͼ���С
	m_cb.SetImageInfo(vih->bmiHeader.biWidth, vih->bmiHeader.biHeight);
	FreeMediaType(mt); 
	//����ѡ��
	hr = m_pGrabber->SetBufferSamples(FALSE); 
	hr = m_pGrabber->SetOneShot(FALSE); 
	//���ûص�����
	hr = m_pGrabber->SetCallback(&m_cb, 1); 
	//������Ƶ����
	SetupVideoWindow();
	return S_OK; 
}
//�ͷŶ���
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
//��ʼ
HRESULT CCap::Run()
{
	if(!m_pMC)
		return S_FALSE;
	HRESULT hr = m_pMC->Run();
	return hr;
}
//��ͣ
HRESULT CCap::Pause()
{
	if(!m_pMC)
		return S_FALSE;
	return m_pMC->Pause();
}
//ֹͣ
HRESULT CCap::Stop()
{
	if(!m_pMC)
		return S_FALSE;
	return m_pMC->Stop();
}
//��ȡISampleGrabberCB
CSampleCB *CCap::GetSampleCB()
{
	return &m_cb;
}
//�����豸�������豸��ţ��������-1����û���ҵ��豸
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
//��ȡ����ŵ��豸����
LPCTSTR CCap::GetDeviceName(int nIndex)
{
	if(nIndex < 0 || nIndex >= m_nDeviceCount)
	{
		DebugBreak();
		return NULL;
	}
	return m_pDevice[nIndex];
}
//��ȡ�豸����
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
//����Filter
BOOL CCap::BindFilter(int nDeviceId, IBaseFilter **pFilter)
{
	if (nDeviceId < 0) 
		return FALSE; 
	//ö���豸 
	CComPtr<ICreateDevEnum> pCreateDevEnum; 
	HRESULT hr = CoCreateInstance(
		CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER, 
		IID_ICreateDevEnum, (void**)&pCreateDevEnum); 
	if (hr != NOERROR) 
		return FALSE; 
	//����ö����
	CComPtr<IEnumMoniker> pEm; 
	hr = pCreateDevEnum->CreateClassEnumerator(
		CLSID_VideoInputDeviceCategory,&pEm, 0); 
	if (hr != NOERROR) 
		return FALSE; 
	//ö���豸
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
					//���ӵ�ָ����ŵ��豸
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
//������Ƶ����
HRESULT CCap::SetupVideoWindow()
{
	//����һ�����صĴ���
	m_hWnd = CreateWindow(_T("STATIC"), 
		_T(""), WS_POPUP, 0, 0, 1, 1, NULL, NULL, NULL, NULL);
	HRESULT hr;
	hr = m_pVW->put_Owner((OAHWND)m_hWnd); 
	if (FAILED(hr))
		return hr; 
	hr = m_pVW->put_WindowStyle(WS_CHILD | WS_CLIPCHILDREN); 
	if (FAILED(hr))
		return hr; 
	//������Ƶ����
	hr = m_pVW->put_Visible(OAFALSE); 
	return hr; 
}
//��ʼ��GraphBuilder
HRESULT CCap::InitCaptureGraphBuilder()
{
	HRESULT hr; 
	//����IGraphBuilder�ӿ� 
	hr=CoCreateInstance(CLSID_FilterGraph, 
		NULL, CLSCTX_INPROC_SERVER, 
		IID_IGraphBuilder, (void **)&m_pGB); 
	//����ICaptureGraphBuilder2�ӿ� 
	hr = CoCreateInstance (
		CLSID_CaptureGraphBuilder2 , NULL, CLSCTX_INPROC, 
		IID_ICaptureGraphBuilder2, (void **) &m_pCapture); 
	if (FAILED(hr))
		return hr; 
	m_pCapture->SetFiltergraph(m_pGB); 
	//��ȡIMediaControl�ӿ�
	hr = m_pGB->QueryInterface(IID_IMediaControl, (void **)&m_pMC); 
	if (FAILED(hr))
		return hr; 
	//��ȡIVideoWindow�ӿ�
	hr = m_pGB->QueryInterface(IID_IVideoWindow, (LPVOID *) &m_pVW); 
	if (FAILED(hr))
		return hr; 
	return hr; 
}