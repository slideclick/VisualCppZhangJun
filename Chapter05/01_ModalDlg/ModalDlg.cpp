// ModalDlg.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "tchar.h"
#include "resource.h"

//对话框过程，处理各种消息。
BOOL CALLBACK DlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg) 
	{
	case WM_CREATE:
		OutputDebugString(_T("**收到了WM_CREATE消息\n"));
		break;
	case WM_INITDIALOG:
		OutputDebugString(_T("**收到了WM_INITDIALOG消息\n"));
		break;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDOK:
			break;
		//取消按钮的处理
		case IDCANCEL:
			EndDialog(hwndDlg, 1);
			return TRUE;
		}
		break;
		//关闭按钮的处理
	case WM_CLOSE:
		EndDialog(hwndDlg, 0);
		return TRUE;
	default:
		break;
	}
	return FALSE;
}

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	//显示模式对话框，并等待，直到对话框结束才返回。
 	int nRet = DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_MAIN), NULL, DlgProc, 0);
	//此函数的返回值是由EndDialog函数指定的
	switch(nRet)
	{
	case 0:
		OutputDebugString(_T("**标题栏的关闭按钮关闭了对话框\n"));
		break;
	case 1:
		OutputDebugString(_T("**‘取消’按钮关闭了对话框\n"));
		break;
	}
	return 0;
}



