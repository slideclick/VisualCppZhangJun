// WindowDemo.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "tchar.h"

#include "mainwnd.h"
#include "resource.h"

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	//建立主窗体
	CMainWnd wnd;
	HWND hWnd = wnd.CreateEx(hInstance, 0, _T("主窗体"), WS_OVERLAPPEDWINDOW, NULL, NULL, IDR_MAIN);
	wnd.Show(SW_SHOW);
	if(!hWnd)
	{
		MessageBox(NULL, _T("创建主窗体时错误。"), NULL, MB_OK);
		return 0;
	}
	//消息循环
	MSG msg = {0};
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg); 
        DispatchMessage(&msg);
	}
	return 0;
}



