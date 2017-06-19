// MyApp.cpp: implementation of the CMyApp class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyApp.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//Ӧ�ó����ʵ�����
HINSTANCE g_hInstance = NULL;
HINSTANCE MyGetInstance()
{
	return g_hInstance;
}

//Ӧ�ó����ܵ�ָ�룬�������ȶ��壬����ָ�������ࡣ
extern CMyApp *g_pApp;
//��ȡӦ�ó�����ָ��
CMyApp *MyGetApp()
{
	return g_pApp;
}

//ȫ�ֵ�WinMain����������Ӧ�ó�������
int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPTSTR lpCmdLine, int nCmdShow)
{
	g_hInstance = hInstance;
	int nReturnValue = 0;
	//��ʼ�����
	if(g_pApp->InitInstance())
	{
		//������Ϣѭ��
		MSG msg = {0};
		while (GetMessage(&msg, NULL, 0, 0))
		{
			TranslateMessage(&msg); 
			DispatchMessage(&msg);
		}
		//��Ϣѭ��������Ӧ�ó��򼴽��˳�
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
	//Ӧ�ó����ʼ����������Ӧ�������ش˺���������������
	return FALSE;
}

int CMyApp::ExitInstance(int nExitCode)
{
	//Ӧ�ó��򼴽��˳��������ڴ��ͷ���Դ
	return nExitCode;
}