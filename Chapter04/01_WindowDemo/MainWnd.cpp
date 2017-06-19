// MainWnd.cpp: implementation of the CMainWnd class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MainWnd.h"
#include "resource.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMainWnd::CMainWnd()
{
}

CMainWnd::~CMainWnd()
{
}

BOOL CMainWnd::OnCommand(int nCmdID)
{
	switch(nCmdID) 
	{
	//����1����
	case ID_MI_WND1_CREATE:
		if (!m_wndChild1.GetHwnd())
		{
			RECT rc1 = {0, 0, 300, 300};
			m_wndChild1.CreateEx(NULL, 0, _T("���Դ���1"), WS_OVERLAPPEDWINDOW, &rc1, m_hWnd, 0);
			m_wndChild1.Show(SW_SHOW);
		}
		break;
	//����1����
	case ID_MI_WND1_DESTROY:
		if (m_wndChild1.GetHwnd())
			m_wndChild1.Destroy();
		break;
	//����1��ʾ
	case ID_MI_WND1_SHOW:
		if (m_wndChild1.GetHwnd())
			m_wndChild1.Show(SW_SHOW);
		break;
	//����1����
	case ID_MI_WND1_HIDE:
		if (m_wndChild1.GetHwnd())
			m_wndChild1.Show(SW_HIDE);
		break;
	//����2����
	case ID_MI_WND2_CREATE:
		if (!m_wndChild2.GetHwnd())
		{
			RECT rc2 = {100, 100, 400, 400};
			m_wndChild2.CreateEx(NULL, 0, _T("���Դ���2"), WS_OVERLAPPEDWINDOW, &rc2, m_hWnd, 0);
			m_wndChild2.Show(SW_SHOW);
		}
		break;
	//����2����
	case ID_MI_WND2_DESTROY:
		if (m_wndChild2.GetHwnd())
			m_wndChild2.Destroy();
		break;
	//����2��ʾ
	case ID_MI_WND2_SHOW:
		if (m_wndChild2.GetHwnd())
			m_wndChild2.Show(SW_SHOW);
		break;
	//��������
	case ID_MI_WND2_HIDE:
		if (m_wndChild2.GetHwnd())
			m_wndChild2.Show(SW_HIDE);
		break;
	default:
		break;
	}

	return 0;
}

BOOL CMainWnd::OnDestroy()
{
	//����������Ϣѭ����Ϣ���Խ���Ӧ�ó���
	PostQuitMessage(0);
	return 0;
}
