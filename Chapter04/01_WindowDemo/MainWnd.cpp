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
	//窗体1建立
	case ID_MI_WND1_CREATE:
		if (!m_wndChild1.GetHwnd())
		{
			RECT rc1 = {0, 0, 300, 300};
			m_wndChild1.CreateEx(NULL, 0, _T("测试窗体1"), WS_OVERLAPPEDWINDOW, &rc1, m_hWnd, 0);
			m_wndChild1.Show(SW_SHOW);
		}
		break;
	//窗体1销毁
	case ID_MI_WND1_DESTROY:
		if (m_wndChild1.GetHwnd())
			m_wndChild1.Destroy();
		break;
	//窗体1显示
	case ID_MI_WND1_SHOW:
		if (m_wndChild1.GetHwnd())
			m_wndChild1.Show(SW_SHOW);
		break;
	//窗体1隐藏
	case ID_MI_WND1_HIDE:
		if (m_wndChild1.GetHwnd())
			m_wndChild1.Show(SW_HIDE);
		break;
	//窗体2建立
	case ID_MI_WND2_CREATE:
		if (!m_wndChild2.GetHwnd())
		{
			RECT rc2 = {100, 100, 400, 400};
			m_wndChild2.CreateEx(NULL, 0, _T("测试窗体2"), WS_OVERLAPPEDWINDOW, &rc2, m_hWnd, 0);
			m_wndChild2.Show(SW_SHOW);
		}
		break;
	//窗体2销毁
	case ID_MI_WND2_DESTROY:
		if (m_wndChild2.GetHwnd())
			m_wndChild2.Destroy();
		break;
	//窗体2显示
	case ID_MI_WND2_SHOW:
		if (m_wndChild2.GetHwnd())
			m_wndChild2.Show(SW_SHOW);
		break;
	//窗体隐藏
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
	//发出结束消息循环消息，以结束应用程序。
	PostQuitMessage(0);
	return 0;
}
