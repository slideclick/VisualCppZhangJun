// MainWnd.cpp: implementation of the CMainWnd class.
//
//////////////////////////////////////////////////////////////////////

#include "MainWnd.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define LWA_ALPHA 0x2
#define WS_EX_LAYERED 0x80000
typedef BOOL (WINAPI *LPSETPROC)(HWND, COLORREF, BYTE, DWORD);
//LPSETPROC g_pSetLayered = NULL;

CMainWnd::CMainWnd()
{
}

CMainWnd::~CMainWnd()
{
}

LRESULT CMainWnd::OnCreate(HWND hWnd)
{
	//改变窗体扩展风格，让其支持分层显示
	DWORD dwExStyle = GetWindowLong(hWnd, GWL_EXSTYLE);
	SetWindowLong(hWnd, GWL_EXSTYLE, dwExStyle | WS_EX_LAYERED);
	//创建定时器
	SetTimer(hWnd, 1, 50, NULL);
	return 0;
}

BOOL CMainWnd::OnDestroy()
{
	//发送结束消息循环消息，退出应用程序
	PostQuitMessage(0);
	return FALSE;
}

BOOL CMainWnd::OnTimer(int nID)
{
	//定时改变窗体的透明度
	static int nTrans = 0xFF;
	nTrans --;
	if (nTrans == 0) 
		nTrans = 0xFF;
	//在标题栏显示目前的透明度
	TCHAR szTitle[128] = {0};
	_stprintf(szTitle, _T("透明度：%d"), nTrans);
	SetWindowText(m_hWnd, szTitle);
	//设置窗体透明度
	HMODULE hDll = LoadLibrary(_T("user32.dll"));
	LPSETPROC pSetLayered =	(LPSETPROC)GetProcAddress(hDll, _T("SetLayeredWindowAttributes")); 
	pSetLayered(m_hWnd, RGB(255, 0, 0), nTrans, LWA_ALPHA);
	FreeLibrary(hDll);

	return FALSE;
}