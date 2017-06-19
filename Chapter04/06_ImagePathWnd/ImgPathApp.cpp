// ImgPathApp.cpp: implementation of the CImgPathApp class.
//
//////////////////////////////////////////////////////////////////////

#include "ImgPathApp.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CImgPathApp g_app;
CMyApp *g_pApp = &g_app;

CImgPathApp::CImgPathApp()
{

}

CImgPathApp::~CImgPathApp()
{

}

BOOL CImgPathApp::InitInstance()
{
	//创建并显示主窗体
	m_wnd.CreateEx(WS_POPUP | WS_SYSMENU, 0, 0, 400, 400, NULL);
	m_wnd.Show(SW_SHOW);
	return (m_wnd.GetHwnd() != NULL);
}