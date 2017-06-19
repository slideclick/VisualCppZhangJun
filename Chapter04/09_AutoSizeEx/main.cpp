#include <windows.h>
#include "resource.h"

//全局变量声明
//主对话框的窗口句柄
HWND g_hWnd = NULL;
//对话框改变之前的大小
SIZE g_siDlg = {0};

//函数声明
//对话框过程函数
INT_PTR CALLBACK 
DlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
//对话框命令响应
void OnCommand(WPARAM wp, LPARAM lp);
//WM_SIZE消息响应
void OnSize(WPARAM wp, LPARAM lp);
//按照指定规则移动某个控件
HDWP MoveCtrl(HDWP hDwp, UINT nID, int x, int y, BOOL bLeft, BOOL bTop, BOOL bRight, BOOL bBottom);
//将屏幕坐标转换为窗体坐标
void ScreenToClientRect(LPRECT prc);

//应用程序的入口函数
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	//弹出一个模式对话框，并等待对话框结束
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_MAIN), NULL, DlgProc);
	return 0;
}
//对话框过程函数
INT_PTR CALLBACK 
DlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg) 
	{
	case WM_INITDIALOG:		//对话框初始化
		{
			//保存窗口原始尺寸
			RECT rc = {0};
			GetClientRect(hwndDlg, &rc);
			g_siDlg.cx = rc.right - rc.left;
			g_siDlg.cy = rc.bottom - rc.top;
			//保存窗口句柄
			g_hWnd = hwndDlg;
			return 1;
		}
	case WM_COMMAND:		//发生命令
		OnCommand(wParam, lParam);
		return 1;
	case WM_CLOSE:			//关闭对话框
		EndDialog(hwndDlg, 0);
		return 1;
	case WM_SIZE:			//对话框大小改变
		OnSize(wParam, lParam);
		return 1;
	default:
		break;
	}
	//默认返回0
	return 0;
}
//对话框命令响应
void OnCommand(WPARAM wp, LPARAM lp)
{
	int nID = LOWORD(wp);
	switch(nID)
	{
	//单击“确定”或“取消”按钮时结束对话框
	case IDOK:
	case IDCANCEL:
		SendMessage(g_hWnd, WM_CLOSE, 0, 0);
		break;
	}
}
//WM_SIZE消息响应
void OnSize(WPARAM wp, LPARAM lp)
{
	//只处理必要的消息，对于非必要消息直接返回
	switch(wp)
	{
	case SIZE_MAXHIDE:
	case SIZE_MAXSHOW:
	case SIZE_MINIMIZED:
		return;
	}
	//取得对话框的新大小
	int nWidth = LOWORD(lp);
	int nHeight = HIWORD(lp);
	//获得改变的差值
	int x, y;
	x = nWidth - g_siDlg.cx;
	y = nHeight - g_siDlg.cy;
	//开始移动控件，做相应的初始化
	HDWP hDwp = BeginDeferWindowPos(4);
	if(hDwp == NULL)
		return;
	//移动“确定”按钮
	hDwp = MoveCtrl(hDwp, IDOK, x, y, TRUE, FALSE, TRUE, FALSE);
	//移动“取消”按钮
	hDwp = MoveCtrl(hDwp, IDCANCEL, x, y, TRUE, FALSE, TRUE, FALSE);
	//移动文本框
	hDwp = MoveCtrl(hDwp, IDC_EDT_TEST, x, y, FALSE, FALSE, TRUE, TRUE);
	//移动静态文本控件
	hDwp = MoveCtrl(hDwp, IDC_BOTTOM, x, y, FALSE, TRUE, FALSE, TRUE);
	//结束移动，使所有控件一次性完成移动
	EndDeferWindowPos(hDwp);
	//保存当前大小
	g_siDlg.cx = nWidth;
	g_siDlg.cy = nHeight;
}
//按照指定规则移动某个控件
HDWP MoveCtrl(HDWP hDwp, UINT nID, int x, int y, BOOL bLeft, BOOL bTop, BOOL bRight, BOOL bBottom)
{
	//获取控件句柄
	HWND hCtrl = GetDlgItem(g_hWnd, nID);
	//取得控件位置和大小
	RECT rc = {0};
	GetWindowRect(hCtrl, &rc);
	//将屏幕坐标转换为窗口坐标
	ScreenToClientRect(&rc);
	//根据选项改变位置和大小
	if(bLeft)
		rc.left += x;
	if(bTop)
		rc.top += y;
	if(bRight)
		rc.right += x;
	if(bBottom)
		rc.bottom += y;
	//移动控件
	return DeferWindowPos(hDwp, hCtrl, 0, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER);
}
//将屏幕坐标转换为窗体坐标
void ScreenToClientRect(LPRECT prc)
{
	ScreenToClient(g_hWnd, (LPPOINT)prc);
	ScreenToClient(g_hWnd, ((LPPOINT)prc) + 1);	
}

