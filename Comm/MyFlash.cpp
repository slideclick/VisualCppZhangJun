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
ע�⣬ʹ�ô���֮ǰ�������ȳ�ʼ��ATL����
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
//�����ؼ�
BOOL CMyFlash::Create(HWND hParent)
{
	m_hParent = hParent;
	//��������
	RECT rc = {0};
	GetClientRect(hParent,&rc);
	m_hWnd = m_wndContainer.Create(hParent, &rc, _T("ShockwaveFlash.ShockwaveFlash"), WS_CHILD | WS_VISIBLE);
	if (m_hWnd == NULL) 
	{
		AfxMessageBox(_T("����Flash����ʧ�ܣ�"));
		return FALSE;
	}
	//��ȡFlash�ӿ�
	HRESULT hr = m_wndContainer.QueryControl(__uuidof(IShockwaveFlash),(void**)&m_pFlash);
	if(FAILED(hr))
	{
		AfxMessageBox(_T("��ȡFlash����ӿ�ʧ�ܣ�"));
		return FALSE;
	}
	return TRUE;
}
//���ٿؼ�
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
//�ƶ��ؼ�λ��
void CMyFlash::Move(LPCRECT lprc)
{
	m_wndContainer.MoveWindow(lprc);
}
//����ӰƬ
BOOL CMyFlash::LoadMovie(LPCTSTR lpFile)
{
	_bstr_t strFile = lpFile;
	return SUCCEEDED(m_pFlash->put_Movie(strFile));	
}
//��ʼ����
BOOL CMyFlash::Play()
{
	return SUCCEEDED(m_pFlash->Play());
}
//ֹͣ����
BOOL CMyFlash::Stop()
{
	return SUCCEEDED(m_pFlash->Stop());
}
