#include "stdafx.h"
#include "maindlg.h"

//------------------
//全局变量
//------------------
HINSTANCE				g_hInst = NULL;
GdiplusStartupInput		g_gdiplusStartupInput;
ULONG_PTR               g_gdiplusToken;

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
	//初始化GDI+
	GdiplusStartup(&g_gdiplusToken, &g_gdiplusStartupInput, NULL);
	//   Load   the   rich   edit   DLL  
	HMODULE hRTFLib = LoadLibrary("RICHED32.DLL");   
	//初始化公共控件
	InitCommonControls();
	//弹出主对话框，并等待对话框结束
	int nRet;
	{
		CMainDlg dlg;
		nRet = dlg.DoModal();
	}
	FreeLibrary(hRTFLib);
	//卸载GDI+
	GdiplusShutdown(g_gdiplusToken);
	return nRet;
}
//返回应用程序实例句柄
HINSTANCE GetInstance()
{
	return g_hInst;
}
//处理消息
void DoEvents()
{
	MSG msg;  
	while(PeekMessage(&msg,NULL,0,0,PM_REMOVE))  
	{  
		TranslateMessage(&msg);  
		DispatchMessage(&msg);  
	}  
}