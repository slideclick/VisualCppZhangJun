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
//�ж϶����Ƿ���Ч������Ч�����٣�������Ϊ��
#define SR(x) if(x != NULL){x->Release(); x=NULL;}
//�ж�һ��COM�����Ƿ�ɹ�����ʧ�ܷ���FALSE���ɹ�����
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
//��������
BOOL CVideoRender::Create(HWND hNotifyHost, UINT nNotifyMsg)
{
	//����IGraphBuilder����ʵ��
	JIF(CoCreateInstance(
		CLSID_FilterGraph, NULL, CLSCTX_INPROC, 
		IID_IGraphBuilder, (void **)&m_pGraph));
	//��ȡIVideoWindow�ӿ�
    JIF(m_pGraph->QueryInterface(
		IID_IVideoWindow, (void **)&m_pVideoWnd));
	//��ȡIMediaEventEx�ӿ�
    JIF(m_pGraph->QueryInterface(
		IID_IMediaEventEx, (void **)&m_pMediaEventEx));
	//���ý�����Ϣ�Ĵ���
	JIF(m_pMediaEventEx->SetNotifyWindow(
		(OAHWND)hNotifyHost, nNotifyMsg, 0));
	//��ȡIMediaSeeking�ӿ�
	JIF(m_pGraph->QueryInterface(
		IID_IMediaSeeking, (void **)&m_pMediaSeeking));
	//��ȡIMediaControl�ӿ�
	JIF(m_pGraph->QueryInterface(
		IID_IMediaControl, (void **)&m_pMediaCtrl));
	return TRUE;
}
//�ͷ����ж���
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
//������Ƶ�ļ�
BOOL CVideoRender::LoadFile(LPCTSTR lpFile)
{
	//RenderFile����ֻ֧��UNICODE�ַ������ڴ����жϲ�����
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
//������Ƶ������
BOOL CVideoRender::SetOwner(HWND hWnd)
{
	JIF(m_pVideoWnd->put_Owner((OAHWND)hWnd));
	JIF(m_pVideoWnd->put_WindowStyle( WS_CHILD | WS_CLIPSIBLINGS));
	return TRUE;
}
//������Ƶ���ڴ�С
BOOL CVideoRender::MoveVideoWnd(LPRECT lpRect)
{
	long lWidth, lHeight;
	lWidth = lpRect->right - lpRect->left;
	lHeight = lpRect->bottom - lpRect->top;
	//�������Ը�����Ŀͻ������Ͻ�Ϊԭ��
	JIF(m_pVideoWnd->SetWindowPosition(
		lpRect->left, lpRect->top, lWidth, lHeight));
	
	return TRUE;
}
//��ʼ����
BOOL CVideoRender::Run()
{
	JIF(m_pMediaCtrl->Run());
	return TRUE;	
}
//��ͣ����
BOOL CVideoRender::Pause()
{
	JIF(m_pMediaCtrl->Pause());
	return TRUE;
}
//ֹͣ����
BOOL CVideoRender::Stop()
{
	JIF(m_pMediaCtrl->Stop());
	return TRUE;	
}
//��ȡ��Ƶ�ܳ���
BOOL CVideoRender::GetDuration(__int64 *pDuration)
{
	JIF(m_pMediaSeeking->GetDuration(pDuration));
	//Ĭ�ϵĵ�λ��100���룬����ת��Ϊ����Ϊ��λ
	*pDuration /= POS_BASE;
	return TRUE;
}
//���ò��Ž���
BOOL CVideoRender::SetPosition(__int64 iPosition)
{
	iPosition *= POS_BASE;
	JIF(m_pMediaSeeking->SetPositions(&iPosition, 
		AM_SEEKING_AbsolutePositioning | AM_SEEKING_SeekToKeyFrame, 
		0, AM_SEEKING_NoPositioning));
	return TRUE;
}
//��ȡ��ǰ����
BOOL CVideoRender::GetPosition(__int64 *pPosition)
{
	JIF(m_pMediaSeeking->GetCurrentPosition(pPosition));
	*pPosition /= POS_BASE;
	return TRUE;
}
//��ȡ�¼�
BOOL CVideoRender::GetEvent(LONG *plCode, LONG *plParam1, LONG *plParam2)
{
	JIF(m_pMediaEventEx->GetEvent(plCode, plParam1, plParam2, 5));
	m_pMediaEventEx->FreeEventParams(*plCode, *plParam1, *plParam2);
	return TRUE;
}
//��ȡ������Ϣ
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
//���ô�����Ϣ
void CVideoRender::SetErrMsg(LPCTSTR lpMsg)
{
	_tcscpy(m_szErrMsg, lpMsg);
}
