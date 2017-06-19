#pragma once

#include <shellapi.h>
#include <tchar.h>

class CTrayIcon
{
public:
	CTrayIcon(HWND hWnd, UINT uID, UINT nNotifyMsg, HICON hIcon = NULL, LPCTSTR lpTip = NULL);
	virtual ~CTrayIcon();
	//显示图标
	BOOL ShowIcon();	
	//隐藏图标
	BOOL HideIcon();
	//设置图标
	BOOL SetIcon(HICON hNewIcon);
	//设置提示文本
	BOOL SetTipText(LPCTSTR lpNewTipText);
	//是否可见
	BOOL IsVisibled();
	//重建图标
	BOOL Rebuild();
protected:
	//图标描述
	NOTIFYICONDATA m_nidata;
	//图标目前是否显示
	BOOL m_bVisibled;
	//通知消息ID
	UINT m_uTrayNotifyMsg;
};

