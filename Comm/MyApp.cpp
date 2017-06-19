// MyApp.cpp: implementation of the CMyApp class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyApp.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//应用程序的实例句柄
HINSTANCE g_hInstance = NULL;
HINSTANCE MyGetInstance()
{
	return g_hInstance;
}

//应用程序框架的指针，必须事先定义，并且指向派生类。
extern CMyApp *g_pApp;
//获取应用程序框架指针
CMyApp *MyGetApp()
{
	return g_pApp;
}

//全局的WinMain函数，整个应用程序的入口
int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPTSTR lpCmdLine, int nCmdShow)
{
	g_hInstance = hInstance;
	int nReturnValue = 0;
	//初始化框架
	if(g_pApp->InitInstance())
	{
		//进入消息循环
		MSG msg = {0};
		while (GetMessage(&msg, NULL, 0, 0))
		{
			TranslateMessage(&msg); 
			DispatchMessage(&msg);
		}
		//消息循环结束、应用程序即将退出
		nReturnValue = g_pApp->ExitInstance(msg.wParam);
	}
	
	return nReturnValue;
}

CMyApp::CMyApp()
{
}

CMyApp::~CMyApp()
{
}

BOOL CMyApp::InitInstance()
{
	//应用程序初始化，派生类应该在重载此函数并创建主窗体
	return FALSE;
}

int CMyApp::ExitInstance(int nExitCode)
{
	//应用程序即将退出，可以在此释放资源
	return nExitCode;
}