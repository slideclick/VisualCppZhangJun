#include <windows.h>
#include "resource.h"

//全局变量声明
//主对话框的窗口句柄
HWND g_hWnd = NULL;
//对话框改变之前的大小
BOOL g_bAuto = FALSE;

//函数声明
//对话框过程函数
INT_PTR CALLBACK 
DlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
//对话框命令响应
void OnCommand(WPARAM wp, LPARAM lp);

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
		g_hWnd = hwndDlg;
		SetDlgItemInt(g_hWnd, IDC_EDT_RANGE, 10, FALSE);
		return 1;
	case WM_COMMAND:		//发生命令
		OnCommand(wParam, lParam);
		return 1;
	case WM_CLOSE:			//关闭对话框
		EndDialog(hwndDlg, 0);
		return 1;
	case WM_WINDOWPOSCHANGING:
		{
			//如果选中了“停靠”复选框
			if(g_bAuto)
			{
				//获取停靠范围
				int nRange = GetDlgItemInt(g_hWnd, IDC_EDT_RANGE, NULL, FALSE);
				if(nRange < 50 && nRange > 0)
				{
					//得到消息参数
					WINDOWPOS *wp = (WINDOWPOS *)lParam;
					//如果处于停靠范围内，实现停靠效果
					if(wp->x < nRange && wp->x > -nRange)
						wp->x = 0;
					if(wp->y < nRange)
						wp->y = 0;
				}
			}
		}
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
	//“停靠”复选框单击
	case IDC_CHK_AUTO:
		{
			//取得控件句柄
			HWND hCtrl = GetDlgItem(g_hWnd, IDC_CHK_AUTO);
			//获取控件选中状态
			UINT nCheck = SendMessage(hCtrl, BM_GETCHECK, 0, 0);
			//设置变量值
			g_bAuto = (nCheck == BST_CHECKED);
		}
		break;
	}
}
