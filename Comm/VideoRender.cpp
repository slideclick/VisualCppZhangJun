// VideoRender.cpp: implementation of the CVideoRender class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VideoRender.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define POS_BASE 10000000
//判断对象是否有效，如有效，销毁，并设置为空
#define SR(x) if(x != NULL){x->Release(); x=NULL;}
//判断一个COM操作是否成功，如失败返回FALSE，成功继续
#define JIF(x) if(FAILED(m_hr = (x))) {return FALSE;}
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVideoRender::CVideoRender()
{
	m_hr			= 0;
	*m_szErrMsg		= _T('\0');
	m_pMediaSeeking	= NULL;
	m_pMediaEventEx	= NULL;
	m_pVideoWnd		= NULL;
	m_pMediaCtrl	= NULL;
	m_pGraph		= NULL;
}
CVideoRender::~CVideoRender()
{
	Release();
}
//建立对象
BOOL CVideoRender::Create(HWND hNotifyHost, UINT nNotifyMsg)
{
	//创建IGraphBuilder对象实例
	JIF(CoCreateInstance(
		CLSID_FilterGraph, NULL, CLSCTX_INPROC, 
		IID_IGraphBuilder, (void **)&m_pGraph));
	//获取IVideoWindow接口
    JIF(m_pGraph->QueryInterface(
		IID_IVideoWindow, (void **)&m_pVideoWnd));
	//获取IMediaEventEx接口
    JIF(m_pGraph->QueryInterface(
		IID_IMediaEventEx, (void **)&m_pMediaEventEx));
	//设置接收消息的窗口
	JIF(m_pMediaEventEx->SetNotifyWindow(
		(OAHWND)hNotifyHost, nNotifyMsg, 0));
	//获取IMediaSeeking接口
	JIF(m_pGraph->QueryInterface(
		IID_IMediaSeeking, (void **)&m_pMediaSeeking));
	//获取IMediaControl接口
	JIF(m_pGraph->QueryInterface(
		IID_IMediaControl, (void **)&m_pMediaCtrl));
	return TRUE;
}
//释放所有对象
void CVideoRender::Release()
{
	if(m_pVideoWnd != NULL)
	{
		m_pVideoWnd->put_Visible(OAFALSE);
		m_pVideoWnd->put_MessageDrain((OAHWND)NULL);
		m_pVideoWnd->put_Owner(OAHWND(0));
		SR(m_pVideoWnd);
	}
	SR(m_pMediaSeeking);
	SR(m_pMediaEventEx);
	SR(m_pMediaCtrl);
	SR(m_pGraph);
}
//加载视频文件
BOOL CVideoRender::LoadFile(LPCTSTR lpFile)
{
	//RenderFile函数只支持UNICODE字符串，在此做判断并处理
	LPCWSTR lpwszPath;
#ifndef UNICODE
	WCHAR szFile[MAX_PATH] = {0};
	MultiByteToWideChar(CP_ACP, 0, lpFile, -1, szFile, MAX_PATH);
	lpwszPath = szFile;
#else
	lpwszPath = lpFile;
#endif
	JIF(m_pGraph->RenderFile(lpwszPath, NULL));
	return TRUE;
}
//设置视频父窗口
BOOL CVideoRender::SetOwner(HWND hWnd)
{
	JIF(m_pVideoWnd->put_Owner((OAHWND)hWnd));
	JIF(m_pVideoWnd->put_WindowStyle( WS_CHILD | WS_CLIPSIBLINGS));
	return TRUE;
}
//设置视频窗口大小
BOOL CVideoRender::MoveVideoWnd(LPRECT lpRect)
{
	long lWidth, lHeight;
	lWidth = lpRect->right - lpRect->left;
	lHeight = lpRect->bottom - lpRect->top;
	//坐标是以父窗体的客户区左上角为原点
	JIF(m_pVideoWnd->SetWindowPosition(
		lpRect->left, lpRect->top, lWidth, lHeight));
	
	return TRUE;
}
//开始播放
BOOL CVideoRender::Run()
{
	JIF(m_pMediaCtrl->Run());
	return TRUE;	
}
//暂停播放
BOOL CVideoRender::Pause()
{
	JIF(m_pMediaCtrl->Pause());
	return TRUE;
}
//停止播放
BOOL CVideoRender::Stop()
{
	JIF(m_pMediaCtrl->Stop());
	return TRUE;	
}
//获取视频总长度
BOOL CVideoRender::GetDuration(__int64 *pDuration)
{
	JIF(m_pMediaSeeking->GetDuration(pDuration));
	//默认的单位是100纳秒，将其转换为以秒为单位
	*pDuration /= POS_BASE;
	return TRUE;
}
//设置播放进度
BOOL CVideoRender::SetPosition(__int64 iPosition)
{
	iPosition *= POS_BASE;
	JIF(m_pMediaSeeking->SetPositions(&iPosition, 
		AM_SEEKING_AbsolutePositioning | AM_SEEKING_SeekToKeyFrame, 
		0, AM_SEEKING_NoPositioning));
	return TRUE;
}
//获取当前进度
BOOL CVideoRender::GetPosition(__int64 *pPosition)
{
	JIF(m_pMediaSeeking->GetCurrentPosition(pPosition));
	*pPosition /= POS_BASE;
	return TRUE;
}
//获取事件
BOOL CVideoRender::GetEvent(LONG *plCode, LONG *plParam1, LONG *plParam2)
{
	JIF(m_pMediaEventEx->GetEvent(plCode, plParam1, plParam2, 5));
	m_pMediaEventEx->FreeEventParams(*plCode, *plParam1, *plParam2);
	return TRUE;
}
//获取错误信息
LPCTSTR CVideoRender::GetErrMsg()
{
	if(m_hr != 0)
	{
		FormatMessage(
			FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, 
			NULL, m_hr, 
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
			m_szErrMsg, sizeof(m_szErrMsg)/sizeof(*m_szErrMsg), NULL);
	}
	return m_szErrMsg;
}
//设置错误信息
void CVideoRender::SetErrMsg(LPCTSTR lpMsg)
{
	_tcscpy(m_szErrMsg, lpMsg);
}
