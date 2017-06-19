#include "resource.h"
#include "MyPing.h"
#include "options.h"
#include "..\..\comm\trayicon.h"

//托盘图标消息
#define WM_USER_TRAYICON (WM_USER + 121)
//Ping消息
#define WM_USER_PING	 (WM_USER + 122)

//----------------
//全局变量声明
//-----------------
//应用程序实例句柄
HINSTANCE	g_hInst = NULL;
//主对话框的窗口句柄
HWND		g_hDlg = NULL;
//Ping封装类
CMyPing		g_ping;
//托盘图标封装类
CTrayIcon	*g_pTray = NULL;
//程序参数
COptions		g_option;
//应用程序图标
HICON		g_hIconApp	 = NULL;
//托盘中的图标
HICON		g_hIconTray0 = NULL;
HICON		g_hIconTray1 = NULL;
HICON		g_hIconTray2 = NULL;
HICON		g_hIconTray3 = NULL;
HICON		g_hIconTray4 = NULL;
//托盘菜单
HMENU		g_hTrayMenu  = NULL;
//任务栏重建消息
const UINT WM_TASKBARCREATED = 
	RegisterWindowMessage(_T("TaskbarCreated"));

//----------------
//函数声明
//----------------
//对话框过程函数
int CALLBACK 
MainDlgProc(HWND hwndDlg, UINT uMsg, 
			WPARAM wParam, LPARAM lParam);
//对话框初始化消息处理
void OnInitDialog();
//对话框销毁前
void OnDestroy();
//Ping消息
void OnPingNotify(WPARAM wp, LPARAM lp);

//------------------
//函数实现
//------------------
//应用程序的入口函数
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	g_hInst = hInstance;
	//初始化Windows Sockets环境
	WSADATA wsa = {0};	
	WSAStartup(MAKEWORD(2,2) , &wsa);
	//创建一个隐藏的非模式对话框
	HWND hWnd = CreateDialog(hInstance, 
		MAKEINTRESOURCE(IDD_MAIN), NULL, MainDlgProc);
	if(hWnd == NULL)
	{
		DebugBreak();
		return 0;
	}
	//进入消息循环
	MSG msg = {0};
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg); 
		DispatchMessage(&msg);
	}
	//清理Sockets环境
	WSACleanup();
	//消息循环结束、应用程序即将退出
	return msg.wParam;
}
//对话框过程函数
int CALLBACK 
MainDlgProc(HWND hwndDlg, UINT uMsg, 
			WPARAM wParam, LPARAM lParam)
{
	int nRet = 1;
	switch(uMsg) 
	{
		//对话框初始化
	case WM_INITDIALOG:		
		//保存窗口句柄
		g_hDlg = hwndDlg;		
		OnInitDialog();
		break;
		//处理命令
	case WM_COMMAND:		
		switch(LOWORD(wParam))
		{
		//退出菜单
		case IDR_EXIT:
			PostMessage(hwndDlg, WM_CLOSE, 0, 0);
			break;
		}
		break;
		//关闭对话框
	case WM_CLOSE:			
		DestroyWindow(hwndDlg);
		break;
		//销毁窗口
	case WM_DESTROY:
		OnDestroy();
		break;
		//托盘图标事件
	case WM_USER_TRAYICON:
		if(lParam == WM_LBUTTONDOWN || lParam == WM_RBUTTONDOWN)
		{
			SetForegroundWindow(hwndDlg);
			POINT pt = {0};
			GetCursorPos(&pt);
			//在鼠标位置弹出菜单
			TrackPopupMenu(GetSubMenu(g_hTrayMenu, 0), 
				TPM_RIGHTALIGN | TPM_BOTTOMALIGN | TPM_RIGHTBUTTON, 
				pt.x, pt.y, 0, hwndDlg, NULL);
		}
		break;
		//Ping线程发出的消息
	case WM_USER_PING:
		OnPingNotify(wParam, lParam);
		break;
	default:
		if(uMsg == WM_TASKBARCREATED)
		{
			//任务栏重建消息，重建托盘图标
			if(g_pTray->IsVisibled())
				g_pTray->Rebuild();
			break;
		}
		nRet = 0;
	}
	return nRet;
}
//对话框初始化消息处理
void OnInitDialog()
{
	//加载应用程序图标
	g_hIconApp = LoadIcon(g_hInst, MAKEINTRESOURCE(IDI_APP));
	//加载托盘要用到的图标
	g_hIconTray0 = LoadIcon(g_hInst, MAKEINTRESOURCE(IDI_TRAY0));
	g_hIconTray1 = LoadIcon(g_hInst, MAKEINTRESOURCE(IDI_TRAY1));
	g_hIconTray2 = LoadIcon(g_hInst, MAKEINTRESOURCE(IDI_TRAY2));
	g_hIconTray3 = LoadIcon(g_hInst, MAKEINTRESOURCE(IDI_TRAY3));
	g_hIconTray4 = LoadIcon(g_hInst, MAKEINTRESOURCE(IDI_TRAY4));
	g_hTrayMenu  = LoadMenu(g_hInst, MAKEINTRESOURCE(IDR_TRAY));
	//创建托盘图标对象
	g_pTray = new CTrayIcon(g_hDlg, 1, 
		WM_USER_TRAYICON, g_hIconApp, _T("等待Ping..."));
	//显示图标
	g_pTray->ShowIcon();
	//初始化CPing对象
	g_ping.StartPing(g_hDlg, g_option.szTargetName, 
		WM_USER_PING, g_option.dwPingInterval, g_option.dwTimeout);
}
//对话框销毁前
void OnDestroy()
{
	g_pTray->SetIcon(g_hIconApp);
	g_pTray->SetTipText(_T("等待关闭..."));
	//释放CPing对象的资源
	g_ping.Release();
	//删除托盘图标
	g_pTray->HideIcon();
	delete g_pTray;
	//释放图标资源
	DestroyIcon(g_hIconApp);
	DestroyIcon(g_hIconTray0);
	DestroyIcon(g_hIconTray1);
	DestroyIcon(g_hIconTray2);
	DestroyIcon(g_hIconTray3);
	DestroyIcon(g_hIconTray4);
	//删除菜单资源
	DestroyMenu(g_hTrayMenu);
	//投递退出消息
	PostQuitMessage(0);	
}
//Ping消息,wp代表Ping是否成功，lp代表Ping值
void OnPingNotify(WPARAM wp, LPARAM lp)
{
	HICON hTrayIcon;
	TCHAR szText[128] = {0};
	switch(wp) 
	{
	//通讯过程中出错
	case 2:
		hTrayIcon = g_hIconTray0;
		_tcscpy(szText, _T("通讯出错"));
		break;
	//超时
	case 1:
		hTrayIcon = g_hIconTray0;
		_tcscpy(szText, _T("通讯超时"));
		break;
	//正常
	case 0:
		//根据Ping值确定图标
		if(lp < g_option.dwTime4)
			hTrayIcon = g_hIconTray4;
		else if(lp < g_option.dwTime3)
			hTrayIcon = g_hIconTray3;
		else if (lp < g_option.dwTime2)
			hTrayIcon = g_hIconTray2;
		else
			hTrayIcon = g_hIconTray1;
		_stprintf(szText, _T("网络Ping值:%d"), lp);
		break;
	default:
		DebugBreak();
		return;
	}
	//更新托盘图标的提示文字
	TCHAR szTrayText[512] = {0};
	_stprintf(szTrayText, _T("与 %s 的%s"), g_option.szTargetName, szText);
	g_pTray->SetTipText(szTrayText);
	//更新托盘的图标
	g_pTray->SetIcon(hTrayIcon);
}
