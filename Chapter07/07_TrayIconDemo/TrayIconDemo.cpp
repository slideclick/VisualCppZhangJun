// TrayIconDemo.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"
#include "..\..\comm\trayicon.h"

//托盘鼠标事件通知消息
#define WM_USER_TRAYICON_NOTIFY (WM_USER + 102)
//任务栏重建消息
const UINT WM_TASKBARCREATED = 
	RegisterWindowMessage(_T("TaskbarCreated"));
//全局变量申明
CTrayIcon *g_pTrayicon = NULL;
HICON g_hIcon = NULL;
HMENU g_hTrayMenu = NULL;
TCHAR g_szTip[64];
HINSTANCE g_hInst;
UINT g_uLastIconID;
//主对话框过程函数申明
BOOL CALLBACK DlgProc(HWND hDlg, UINT uMsg, 
	WPARAM wp, LPARAM lp);
//应用程序入口
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	g_hInst = hInstance;
	_tcscpy(g_szTip, _T("托盘图标演示！"));
	//创建非模式对话框
	HWND hWnd = CreateDialogParam(hInstance, 
		MAKEINTRESOURCE(IDD_MAIN), 
		NULL, DlgProc, 0);
	//处理消息循环并等待结束
	MSG msg = {0};
	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}
//主对话框过程实现
BOOL CALLBACK DlgProc(HWND hDlg, UINT uMsg, 
	WPARAM wp, LPARAM lp)
{
	switch(uMsg) 
	{
	case WM_INITDIALOG:
		//初始化变量
		g_hTrayMenu = LoadMenu(g_hInst, 
			MAKEINTRESOURCE(IDR_TRAYICON));
		SetDlgItemText(hDlg, IDC_EDT_TIP, g_szTip);
		g_uLastIconID = IDI_TRAYICON;
		g_hIcon = LoadIcon(g_hInst, 
			MAKEINTRESOURCE(g_uLastIconID));
		//创建托盘图标类
		g_pTrayicon = new CTrayIcon(hDlg, 0, 
			WM_USER_TRAYICON_NOTIFY, g_hIcon, g_szTip);
		//显示图标
		g_pTrayicon->ShowIcon();
		break;
	case WM_DESTROY:
		//删除托盘图标，销毁对象
		g_pTrayicon->HideIcon();
		delete g_pTrayicon;
		//退出应用程序
		PostQuitMessage(0);
		break;
	case WM_CLOSE:
		DestroyWindow(hDlg);
		break;
	case WM_COMMAND:
		//处理按钮和菜单消息
		switch(LOWORD(wp))
		{
		case IDCANCEL:
			PostMessage(hDlg, WM_CLOSE, 0, 0);
			break;
		case IDC_BTN_CHANGEICON:
			//更换图标
			if(g_uLastIconID == IDI_TRAYICON)
				g_uLastIconID = IDI_TRAYICON_1;
			else
				g_uLastIconID = IDI_TRAYICON;
			g_hIcon = LoadIcon(g_hInst, 
				MAKEINTRESOURCE(g_uLastIconID));
			g_pTrayicon->SetIcon(g_hIcon);
			break;
		case IDC_BTN_UPDATETIP:
			//修改提示文本
			GetDlgItemText(hDlg, IDC_EDT_TIP, 
				g_szTip, sizeof(g_szTip)/sizeof(TCHAR) - 1);
			g_pTrayicon->SetTipText(g_szTip);
			break;
		case IDR_SHOW_WINDOW:
			//显示主对话框
			ShowWindow(hDlg, SW_SHOW);
			break;
		}
		break;
	case WM_USER_TRAYICON_NOTIFY:
		//托盘图标鼠标消息响应
		if(lp == WM_LBUTTONDOWN || lp == WM_RBUTTONDOWN)
		{
			SetForegroundWindow(hDlg);
			POINT pt = {0};
			GetCursorPos(&pt);
			//在鼠标位置弹出菜单
			TrackPopupMenu(GetSubMenu(g_hTrayMenu, 0), 
				TPM_RIGHTALIGN | TPM_BOTTOMALIGN | TPM_RIGHTBUTTON, 
				pt.x, pt.y, 0, hDlg, NULL);
		}
		break;
	default:
		if(uMsg == WM_TASKBARCREATED)
		{
			//任务栏重建消息，重建托盘图标
			if(g_pTrayicon->IsVisibled())
				g_pTrayicon->Rebuild();
			break;
		}
		return FALSE;
	}
	return TRUE;
}