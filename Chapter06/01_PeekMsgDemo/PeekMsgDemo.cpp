// PeekMsgDemo.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

#include "msgwnd.h"


int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	//����������
	CMsgWnd wnd;
	wnd.CreateEx(WS_OVERLAPPEDWINDOW, 300, 300, 300, 200, NULL);
	if(wnd.GetHwnd() == NULL)
	{
		MessageBox(NULL, _T("����������ʧ�ܣ�"), _T(""), MB_OK);
		return 0;
	}
 	wnd.Show(SW_SHOW);
	//������Ϣѭ��
	MSG msg;
	BOOL bProcessIdle;
	while(TRUE)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			//����Ƿ���Ҫ�˳�ѭ��
			if(msg.message == WM_QUIT)
				break;
			bProcessIdle = TRUE;
			//ת����Ϣ
			TranslateMessage(&msg); 
			//������Ϣ
			DispatchMessage(&msg); 			
		}
		else
		{
			//Ӧ�ó��������
			if(bProcessIdle)
				//�������ʱ���Ĺ���
				bProcessIdle = wnd.OnIdle();
			else
				//�ͷ�CPUʱ��Ƭ
				Sleep(1);
		}
	}
	//�˳�Ӧ�ó���
	return 0;
}



