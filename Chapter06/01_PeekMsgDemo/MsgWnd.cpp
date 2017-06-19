// MsgWnd.cpp: implementation of the CMsgWnd class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MsgWnd.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMsgWnd::CMsgWnd()
{
	//��ʼ����Ա����
	m_dwTick = GetTickCount();
}

CMsgWnd::~CMsgWnd()
{
}

BOOL CMsgWnd::OnIdle()
{
	//������д���
	if(GetTickCount() - m_dwTick >= 1000)
	{
		//���������1���ˣ����ٽ��տ���֪ͨ
		SetWindowText(m_hWnd, _T("���������1����..."));
		return FALSE;
	}
	else
		return TRUE;
}

BOOL CMsgWnd::OnDestroy()
{
	//�˳���Ϣѭ��
	PostQuitMessage(0);
	return FALSE;
}

BOOL CMsgWnd::PreProcessMsg(HWND hWnd, UINT nMsg, WPARAM wp, LPARAM lp, LRESULT *pResult)
{
	//��������Ϣ�����¼������ʱ��
	m_dwTick = GetTickCount();
	//�ڽ�������ʾ���̻������Ϣ
	if(nMsg >= WM_KEYFIRST && nMsg <= WM_KEYLAST)
		SetWindowText(m_hWnd, _T("�յ��˼�����Ϣ..."));
	else if(nMsg >= WM_MOUSEFIRST && nMsg <= WM_MOUSELAST)
		SetWindowText(m_hWnd, _T("�յ��������Ϣ..."));
	return TRUE;
}