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
	//����������
	CMainWnd wnd;
	HWND hWnd = wnd.CreateEx(hInstance, 0, _T("������"), WS_OVERLAPPEDWINDOW, NULL, NULL, IDR_MAIN);
	wnd.Show(SW_SHOW);
	if(!hWnd)
	{
		MessageBox(NULL, _T("����������ʱ����"), NULL, MB_OK);
		return 0;
	}
	//��Ϣѭ��
	MSG msg = {0};
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg); 
        DispatchMessage(&msg);
	}
	return 0;
}



