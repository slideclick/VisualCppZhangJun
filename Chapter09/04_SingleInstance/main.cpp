#include <windows.h>
#include <tchar.h>
#include "resource.h"

//共享数据段
#pragma data_seg("sharedata")
HWND volatile g_hPreWnd = NULL;
#pragma data_seg()
#pragma comment(linker,"/section:sharedata,RWS")
//互斥对象名称
#define MY_SINGLE_INSTANCE_MUTEX_NAME \
	_T("My_Single_Instance")

//对话框过程函数
INT_PTR CALLBACK MainDlgProc(HWND hDlg,
							 UINT uMsg,
							 WPARAM wp,
							 LPARAM lp)
{
	BOOL bRet = TRUE;
	//消息处理
	switch(uMsg) 
	{
	case WM_INITDIALOG:
		g_hPreWnd = hDlg;
		break;
	case WM_CLOSE:
		//结束对话框
		EndDialog(hDlg, 0);
		break;
	case WM_COMMAND:
		//单击ok或cancel按钮，关闭对话框
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

//应用程序入口函数
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	//创建互斥对象
	HANDLE hMutex = CreateMutex(
		NULL, FALSE, MY_SINGLE_INSTANCE_MUTEX_NAME);
	if(hMutex == NULL)
		return 0;
	
	switch(GetLastError()) 
	{
	case ERROR_SUCCESS:
		//显示主对话框
		DialogBox(hInstance, 
			MAKEINTRESOURCE(IDD_MAIN), NULL, MainDlgProc);
		ReleaseMutex(hMutex);
		break;
	case ERROR_ALREADY_EXISTS:
		//互斥对象已经存在，则激活第一个实例，退出本程序
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

