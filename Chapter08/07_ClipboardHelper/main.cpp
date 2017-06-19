#include <windows.h>
#include <tchar.h>
#include <stdio.h>

#include "resource.h"

//////////////////////////////////////////////////////////////////////////
// 宏定义
//////////////////////////////////////////////////////////////////////////

//粘贴的热键ID
#define HOTKEY_ID_PASTE 1
//程序退出的热键ID
#define HOTKEY_ID_EXIT 2
//剪切板格式
#ifdef UNICODE
  #define CT_TCHAR CF_UNICODETEXT
#else
  #define CT_TCHAR CF_TEXT
#endif //#ifdef UNICODE


//////////////////////////////////////////////////////////////////////////
// 全局变量申明
//////////////////////////////////////////////////////////////////////////

//对话框句柄
HWND g_hDlg;


//////////////////////////////////////////////////////////////////////////
// 全局函数申明
//////////////////////////////////////////////////////////////////////////

//对话框过程
INT_PTR CALLBACK MainDlgProc(HWND hDlg, UINT uMsg, WPARAM wp, LPARAM lp);
//热键处理
void OnHotkey();


//////////////////////////////////////////////////////////////////////////
// 函数实现
//////////////////////////////////////////////////////////////////////////

//程序入口
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	//创建窗体
	g_hDlg = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_MAIN), NULL, MainDlgProc);
	if (g_hDlg == NULL) 
	{
		DebugBreak();
		return 0;
	}
	//消息循环
	MSG msg;
	while(GetMessage(&msg, NULL, 0, 0))
	{
		DispatchMessage(&msg);
	}
	return 0;
}

//对话框过程
INT_PTR CALLBACK MainDlgProc(HWND hDlg, UINT uMsg, WPARAM wp, LPARAM lp)
{
	BOOL bRet = TRUE;
	switch(uMsg) 
	{
	case WM_INITDIALOG:
		//注册热键
		if( !RegisterHotKey(hDlg, HOTKEY_ID_PASTE, MOD_WIN, 'P')
			|| !RegisterHotKey(hDlg, HOTKEY_ID_EXIT, MOD_WIN, 'Q'))
		{
			//如果注册失败，显示错误提示并退出
			DWORD dwErr = GetLastError();
			TCHAR szBuf[256] = {0};
			FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, dwErr, 
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
				szBuf, sizeof(szBuf)/sizeof(*szBuf), NULL);
			MessageBox(NULL, szBuf, _T("Error"), MB_OK);
			PostMessage(hDlg, WM_CLOSE, 0, 0);
		}
		break;
	case WM_CLOSE:
		//销毁窗体
		DestroyWindow(hDlg);
		break;
	case WM_DESTROY:
		//取消热键，并退出程序
		UnregisterHotKey(hDlg, HOTKEY_ID_PASTE);
		UnregisterHotKey(hDlg, HOTKEY_ID_EXIT);
		PostQuitMessage(0);
		break;
	case WM_HOTKEY:
		//处理热键消息
		if(wp == HOTKEY_ID_PASTE)
		{
			//纯文本粘贴
			OnHotkey();
		}
		else if(wp == HOTKEY_ID_EXIT)
		{
			//退出应用程序
			MessageBeep(MB_OK);
			PostMessage(hDlg, WM_CLOSE, 0, 0);
		}
		break;
	default:
		bRet = FALSE;
		break;
	}
	return bRet;
}

void OnHotkey()
{
	//打开剪切板
	if(OpenClipboard(g_hDlg))
	{
		//尝试从剪切板获取文本型的数据
		HGLOBAL hGlobal = GetClipboardData(CT_TCHAR);
		//锁定内存
		LPCSTR lpText = (LPCSTR)GlobalLock(hGlobal);
		if(lpText && *lpText)
		{
			//有文本
			int nLen = (_tcslen(lpText) + 1) * sizeof(TCHAR);
			//分配一块可跨进程访问的内存
			HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, nLen);
			//锁定内存并获得内存首字节指针
			LPTSTR pText = (LPTSTR)GlobalLock(hGlobal);
			//将文本复制到该内存
			_tcscpy(pText, lpText);
			//解锁内存
			GlobalUnlock(hGlobal);
			//清空剪切板
			EmptyClipboard();
			//将文本放置到剪切板
			SetClipboardData(CT_TCHAR, hGlobal);	
			//关闭剪切板
			CloseClipboard();

			//粘贴
			keybd_event(VK_CONTROL, 0, 0, 0);
			keybd_event('V', 0, 0, 0);
			Sleep(1);
			keybd_event('V', 0, KEYEVENTF_KEYUP, 0);
			keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		}
		else
		{
			GlobalUnlock(hGlobal);
			CloseClipboard();
			//无文本
			MessageBeep(MB_ICONEXCLAMATION);
		}
	}
	else
	{
		MessageBeep(MB_ICONEXCLAMATION);
	}
}