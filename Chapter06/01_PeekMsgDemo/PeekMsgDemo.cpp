// PeekMsgDemo.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

#include "msgwnd.h"


int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	//建立主窗体
	CMsgWnd wnd;
	wnd.CreateEx(WS_OVERLAPPEDWINDOW, 300, 300, 300, 200, NULL);
	if(wnd.GetHwnd() == NULL)
	{
		MessageBox(NULL, _T("创建主窗体失败！"), _T(""), MB_OK);
		return 0;
	}
 	wnd.Show(SW_SHOW);
	//进入消息循环
	MSG msg;
	BOOL bProcessIdle;
	while(TRUE)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			//检查是否需要退出循环
			if(msg.message == WM_QUIT)
				break;
			bProcessIdle = TRUE;
			//转换消息
			TranslateMessage(&msg); 
			//分派消息
			DispatchMessage(&msg); 			
		}
		else
		{
			//应用程序空闲了
			if(bProcessIdle)
				//处理空闲时做的工作
				bProcessIdle = wnd.OnIdle();
			else
				//释放CPU时间片
				Sleep(1);
		}
	}
	//退出应用程序
	return 0;
}



