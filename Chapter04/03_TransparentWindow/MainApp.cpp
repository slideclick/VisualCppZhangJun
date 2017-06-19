// MainApp.cpp: implementation of the CMainApp class.
//
//////////////////////////////////////////////////////////////////////

#include "MainApp.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//定义应用程序框架
CMainApp g_myApp;
//应用程序框架的指针，此变量的作用是把WinMain函数和具体类关联起来。
CMyApp *g_pApp = &g_myApp;

CMainApp::CMainApp()
{
}

CMainApp::~CMainApp()
{
}

BOOL CMainApp::InitInstance()
{
	//应用程序初始化，创建主窗体
	m_wnd.CreateEx(WS_OVERLAPPEDWINDOW, 0, 0, 300, 400, NULL);
	m_wnd.Show(SW_SHOW);

	return(m_wnd.GetHwnd() != NULL);
}
