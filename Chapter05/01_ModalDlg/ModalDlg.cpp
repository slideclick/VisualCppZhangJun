// ModalDlg.cpp : Defines the entry point for the application.
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
			EndDialog(hwndDlg, 1);
			return TRUE;
		}
		break;
		//�رհ�ť�Ĵ���
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
	//��ʾģʽ�Ի��򣬲��ȴ���ֱ���Ի�������ŷ��ء�
 	int nRet = DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_MAIN), NULL, DlgProc, 0);
	//�˺����ķ���ֵ����EndDialog����ָ����
	switch(nRet)
	{
	case 0:
		OutputDebugString(_T("**�������Ĺرհ�ť�ر��˶Ի���\n"));
		break;
	case 1:
		OutputDebugString(_T("**��ȡ������ť�ر��˶Ի���\n"));
		break;
	}
	return 0;
}



