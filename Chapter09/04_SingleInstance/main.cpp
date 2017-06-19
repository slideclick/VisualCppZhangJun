#include <windows.h>
#include <tchar.h>
#include "resource.h"

//�������ݶ�
#pragma data_seg("sharedata")
HWND volatile g_hPreWnd = NULL;
#pragma data_seg()
#pragma comment(linker,"/section:sharedata,RWS")
//�����������
#define MY_SINGLE_INSTANCE_MUTEX_NAME \
	_T("My_Single_Instance")

//�Ի�����̺���
INT_PTR CALLBACK MainDlgProc(HWND hDlg,
							 UINT uMsg,
							 WPARAM wp,
							 LPARAM lp)
{
	BOOL bRet = TRUE;
	//��Ϣ����
	switch(uMsg) 
	{
	case WM_INITDIALOG:
		g_hPreWnd = hDlg;
		break;
	case WM_CLOSE:
		//�����Ի���
		EndDialog(hDlg, 0);
		break;
	case WM_COMMAND:
		//����ok��cancel��ť���رնԻ���
		if(LOWORD(wp) == IDOK || LOWORD(wp) == IDCANCEL)
			PostMessage(hDlg, WM_CLOSE, 0, 0);
		else
			bRet = FALSE;
		break;
	default:
		bRet = FALSE;
		break;
	}
	return bRet;
}

//Ӧ�ó�����ں���
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	//�����������
	HANDLE hMutex = CreateMutex(
		NULL, FALSE, MY_SINGLE_INSTANCE_MUTEX_NAME);
	if(hMutex == NULL)
		return 0;
	
	switch(GetLastError()) 
	{
	case ERROR_SUCCESS:
		//��ʾ���Ի���
		DialogBox(hInstance, 
			MAKEINTRESOURCE(IDD_MAIN), NULL, MainDlgProc);
		ReleaseMutex(hMutex);
		break;
	case ERROR_ALREADY_EXISTS:
		//��������Ѿ����ڣ��򼤻��һ��ʵ�����˳�������
		if(g_hPreWnd)
		{
			SetForegroundWindow(g_hPreWnd);
			FlashWindow(g_hPreWnd, TRUE);
		}
		CloseHandle(hMutex);
		break;
	default:
		break;
	}
	return 0;
}

