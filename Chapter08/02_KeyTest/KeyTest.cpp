// KeyTest.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "keytestwnd.h"

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	//创建主窗体
	CKeyTestWnd wnd;
	wnd.CreateEx(WS_OVERLAPPEDWINDOW, 
		CW_USEDEFAULT, CW_USEDEFAULT, 
		CW_USEDEFAULT, CW_USEDEFAULT, NULL);
	wnd.Show(SW_SHOW);
	//进入消息循环
	TCHAR szKey[256];
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) )
	{
		//显示键盘按下消息的详细情况
		if(msg.message == WM_KEYDOWN 
			|| msg.message == WM_SYSKEYDOWN)
		{
			int n = HIWORD(msg.lParam);
			//取出按键消息各bit信息
			_stprintf(szKey, 
				_T("键值：%d(%c)，重复：%d，扫描码：%d，扩展：%c， 系统：%c，之前：%s"), 
				msg.wParam, (TCHAR)msg.wParam, 
				LOWORD(msg.lParam), 0x00FF & n , 
				0x0100 & n ? 'Y' : 'N', 
				0x2000 & n ? 'Y' : 'N', 
				0x4000 & n ? _T("按下") : _T("松开"));
			SetWindowText(wnd, szKey);
		}
		DispatchMessage(&msg);
	}
	return 0;
}