#include "stdafx.h"
#include "trayicon.h"

CTrayIcon::CTrayIcon(HWND hWnd, UINT uID, UINT nNotifyMsg, HICON hIcon /*= NULL*/, LPCTSTR lpTip /*= NULL*/)
{
	//初始化变量
	m_bVisibled = FALSE;
	m_uTrayNotifyMsg = nNotifyMsg;
	//初始化托盘图标数据
	memset(&m_nidata, 0, sizeof(m_nidata));
	m_nidata.cbSize = sizeof(m_nidata);
	m_nidata.uID = uID; 
	m_nidata.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;
	m_nidata.uCallbackMessage = m_uTrayNotifyMsg;
	m_nidata.hIcon = hIcon;
	if(lpTip)
		_tcsncpy(m_nidata.szTip, lpTip, sizeof(m_nidata.szTip)/sizeof(TCHAR) - 1);
	else
		m_nidata.szTip[0] = _T('\0');
	m_nidata.hWnd = hWnd;
}
CTrayIcon::~CTrayIcon()
{
}
//显示图标
BOOL CTrayIcon::ShowIcon()	
{
	if(!m_bVisibled)
	{
		m_bVisibled = Shell_NotifyIcon(NIM_ADD, &m_nidata);
	}
	return m_bVisibled;
}
//隐藏图标
BOOL CTrayIcon::HideIcon()
{
	if(m_bVisibled)
	{
		m_bVisibled = (!Shell_NotifyIcon(NIM_DELETE, &m_nidata));
	}
	return (!m_bVisibled);
}
//设置图标
BOOL CTrayIcon::SetIcon(HICON hNewIcon)
{
	m_nidata.hIcon = hNewIcon;
	if(m_bVisibled)
	{
		BOOL bRet;
		bRet = Shell_NotifyIcon(NIM_MODIFY, &m_nidata);
		return bRet;
	}
	else
		return TRUE;
}
//设置提示文本
BOOL CTrayIcon::SetTipText(LPCTSTR lpNewTipText)
{
	memset(m_nidata.szTip, 0, sizeof(m_nidata.szTip));
	_tcsncpy(m_nidata.szTip, lpNewTipText, sizeof(m_nidata.szTip)/sizeof(TCHAR) - 1);

	if(m_bVisibled)
	{
		BOOL bRet;
		bRet = Shell_NotifyIcon(NIM_MODIFY, &m_nidata);
		return bRet;
	}
	else
		return TRUE;
}
//是否可见
BOOL CTrayIcon::IsVisibled()
{
	return m_bVisibled;
}
//重建图标
BOOL CTrayIcon::Rebuild()
{
	if(m_bVisibled)
	{
		Shell_NotifyIcon(NIM_DELETE, &m_nidata);
		m_bVisibled = FALSE;
		return ShowIcon();
	}
	else
		return FALSE;
}