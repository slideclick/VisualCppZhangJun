// MyFlash.cpp: implementation of the CMyFlash class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyFlash.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*
注意，使用此类之前，必须先初始化ATL环境
*/

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyFlash::CMyFlash()
{
	m_pFlash = NULL;
}
CMyFlash::~CMyFlash()
{
}
//创建控件
BOOL CMyFlash::Create(HWND hParent)
{
	m_hParent = hParent;
	//创建容器
	RECT rc = {0};
	GetClientRect(hParent,&rc);
	m_hWnd = m_wndContainer.Create(hParent, &rc, _T("ShockwaveFlash.ShockwaveFlash"), WS_CHILD | WS_VISIBLE);
	if (m_hWnd == NULL) 
	{
		AfxMessageBox(_T("创建Flash对象失败！"));
		return FALSE;
	}
	//获取Flash接口
	HRESULT hr = m_wndContainer.QueryControl(__uuidof(IShockwaveFlash),(void**)&m_pFlash);
	if(FAILED(hr))
	{
		AfxMessageBox(_T("获取Flash对象接口失败！"));
		return FALSE;
	}
	return TRUE;
}
//销毁控件
void CMyFlash::Destroy()
{
	if(m_pFlash != NULL)
	{
		m_pFlash = NULL;
	}
	if (IsWindow(m_wndContainer)) 
	{
		m_wndContainer.DestroyWindow();
	}
}
//移动控件位置
void CMyFlash::Move(LPCRECT lprc)
{
	m_wndContainer.MoveWindow(lprc);
}
//加载影片
BOOL CMyFlash::LoadMovie(LPCTSTR lpFile)
{
	_bstr_t strFile = lpFile;
	return SUCCEEDED(m_pFlash->put_Movie(strFile));	
}
//开始播放
BOOL CMyFlash::Play()
{
	return SUCCEEDED(m_pFlash->Play());
}
//停止播放
BOOL CMyFlash::Stop()
{
	return SUCCEEDED(m_pFlash->Stop());
}
