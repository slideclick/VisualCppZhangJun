// MainApp.cpp: implementation of the CMainApp class.
//
//////////////////////////////////////////////////////////////////////

#include "MainApp.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//����Ӧ�ó�����
CMainApp g_myApp;
//Ӧ�ó����ܵ�ָ�룬�˱����������ǰ�WinMain�����;��������������
CMyApp *g_pApp = &g_myApp;

CMainApp::CMainApp()
{
}

CMainApp::~CMainApp()
{
}

BOOL CMainApp::InitInstance()
{
	//Ӧ�ó����ʼ��������������
	m_wnd.CreateEx(WS_OVERLAPPEDWINDOW, 0, 0, 300, 400, NULL);
	m_wnd.Show(SW_SHOW);

	return(m_wnd.GetHwnd() != NULL);
}
