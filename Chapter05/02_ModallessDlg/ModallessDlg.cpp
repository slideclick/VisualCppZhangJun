// ModallessDlg.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "tchar.h"
#include "resource.h"

//�Ի�����̣����������Ϣ��
BOOL CALLBACK DlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg) 
	{
	case WM_CREATE:
		OutputDebugString(_T("**�յ���WM_CREATE��Ϣ\n"));
		break;
	case WM_INITDIALOG:
		OutputDebugString(_T("**�յ���WM_INITDIALOG��Ϣ\n"));
		break;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDOK:
			break;
			//ȡ����ť�Ĵ���
		case IDCANCEL:
			DestroyWindow(hwndDlg);
			return TRUE;
		}
		break;
		//�رհ�ť�Ĵ���
		case WM_CLOSE:
			DestroyWindow(hwndDlg);
			return TRUE;
		case WM_DESTROY:
			OutputDebugString(_T("**�Ի��򼴽�����\n"));			
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
	//������ģʽ�Ի���
	HWND hWnd = CreateDialogParam(hInstance, MAKEINTRESOURCE(IDD_MAIN), NULL, DlgProc, 0);
	//��ʾ�Ի���
	ShowWindow(hWnd, SW_SHOW);
	//������Ϣѭ�����ȴ�����
	MSG msg = {0};
	while(GetMessage(&msg, NULL, 0, 0))
	{
		DispatchMessage(&msg);
	}
	OutputDebugString(_T("**��Ϣѭ��������\n"));
	return 0;
}



