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
	//初始化成员变量
	m_dwTick = GetTickCount();
}

CMsgWnd::~CMsgWnd()
{
}

BOOL CMsgWnd::OnIdle()
{
	//程序空闲处理
	if(GetTickCount() - m_dwTick >= 1000)
	{
		//如果空闲了1秒了，则不再接收空闲通知
		SetWindowText(m_hWnd, _T("程序空闲了1秒了..."));
		return FALSE;
	}
	else
		return TRUE;
}

BOOL CMsgWnd::OnDestroy()
{
	//退出消息循环
	PostQuitMessage(0);
	return FALSE;
}

BOOL CMsgWnd::PreProcessMsg(HWND hWnd, UINT nMsg, WPARAM wp, LPARAM lp, LRESULT *pResult)
{
	//处理了消息，重新计算空闲时间
	m_dwTick = GetTickCount();
	//在界面上显示键盘或鼠标消息
	if(nMsg >= WM_KEYFIRST && nMsg <= WM_KEYLAST)
		SetWindowText(m_hWnd, _T("收到了键盘消息..."));
	else if(nMsg >= WM_MOUSEFIRST && nMsg <= WM_MOUSELAST)
		SetWindowText(m_hWnd, _T("收到了鼠标消息..."));
	return TRUE;
}