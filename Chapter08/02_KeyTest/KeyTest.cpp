// KeyTest.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "keytestwnd.h"

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	//����������
	CKeyTestWnd wnd;
	wnd.CreateEx(WS_OVERLAPPEDWINDOW, 
		CW_USEDEFAULT, CW_USEDEFAULT, 
		CW_USEDEFAULT, CW_USEDEFAULT, NULL);
	wnd.Show(SW_SHOW);
	//������Ϣѭ��
	TCHAR szKey[256];
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) )
	{
		//��ʾ���̰�����Ϣ����ϸ���
		if(msg.message == WM_KEYDOWN 
			|| msg.message == WM_SYSKEYDOWN)
		{
			int n = HIWORD(msg.lParam);
			//ȡ��������Ϣ��bit��Ϣ
			_stprintf(szKey, 
				_T("��ֵ��%d(%c)���ظ���%d��ɨ���룺%d����չ��%c�� ϵͳ��%c��֮ǰ��%s"), 
				msg.wParam, (TCHAR)msg.wParam, 
				LOWORD(msg.lParam), 0x00FF & n , 
				0x0100 & n ? 'Y' : 'N', 
				0x2000 & n ? 'Y' : 'N', 
				0x4000 & n ? _T("����") : _T("�ɿ�"));
			SetWindowText(wnd, szKey);
		}
		DispatchMessage(&msg);
	}
	return 0;
}