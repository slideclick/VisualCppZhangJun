// ModallessDlg.cpp : Defines the entry point for the application.
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
			DestroyWindow(hwndDlg);
			return TRUE;
		}
		break;
		//关闭按钮的处理
		case WM_CLOSE:
			DestroyWindow(hwndDlg);
			return TRUE;
		case WM_DESTROY:
			OutputDebugString(_T("**对话框即将销毁\n"));			
			PostQuitMessage(0);
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
	//创建非模式对话框
	HWND hWnd = CreateDialogParam(hInstance, MAKEINTRESOURCE(IDD_MAIN), NULL, DlgProc, 0);
	//显示对话框
	ShowWindow(hWnd, SW_SHOW);
	//处理消息循环并等待结束
	MSG msg = {0};
	while(GetMessage(&msg, NULL, 0, 0))
	{
		DispatchMessage(&msg);
	}
	OutputDebugString(_T("**消息循环结束了\n"));
	return 0;
}



