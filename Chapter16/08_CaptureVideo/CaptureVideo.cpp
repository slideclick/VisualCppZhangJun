#include "stdafx.h"
#include "maindlg.h"

//------------------
//全局变量
//------------------
CComModule _Module;
HINSTANCE g_hInst = NULL;
//------------------
//函数实现
//------------------
//应用程序的入口函数
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	g_hInst = hInstance;
	//初始化COM
	CoInitialize(NULL);
	//初始化公共控件
	InitCommonControls();
	//弹出主对话框，并等待对话框结束
	int nRet;
	{
		CMainDlg dlg;
		nRet = dlg.DoModal();
	}
	//清理COM
	CoUninitialize();
	return nRet;
}
//返回应用程序实例句柄
HINSTANCE GetInstance()
{
	return g_hInst;
}