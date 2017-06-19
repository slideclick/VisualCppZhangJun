#include "stdafx.h"
#include "maindlg.h"

//------------------
//ȫ�ֱ���
//------------------
HINSTANCE				g_hInst = NULL;
GdiplusStartupInput		g_gdiplusStartupInput;
ULONG_PTR               g_gdiplusToken;

//------------------
//����ʵ��
//------------------
//Ӧ�ó������ں���
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	g_hInst = hInstance;
	//��ʼ��GDI+
	GdiplusStartup(&g_gdiplusToken, &g_gdiplusStartupInput, NULL);
	//   Load   the   rich   edit   DLL  
	HMODULE hRTFLib = LoadLibrary("RICHED32.DLL");   
	//��ʼ�������ؼ�
	InitCommonControls();
	//�������Ի��򣬲��ȴ��Ի������
	int nRet;
	{
		CMainDlg dlg;
		nRet = dlg.DoModal();
	}
	FreeLibrary(hRTFLib);
	//ж��GDI+
	GdiplusShutdown(g_gdiplusToken);
	return nRet;
}
//����Ӧ�ó���ʵ�����
HINSTANCE GetInstance()
{
	return g_hInst;
}
//������Ϣ
void DoEvents()
{
	MSG msg;  
	while(PeekMessage(&msg,NULL,0,0,PM_REMOVE))  
	{  
		TranslateMessage(&msg);  
		DispatchMessage(&msg);  
	}  
}