#include "stdafx.h"
#include "maindlg.h"

//------------------
//ȫ�ֱ���
//------------------
CComModule _Module;
HINSTANCE g_hInst = NULL;
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
	//��ʼ��COM
	CoInitialize(NULL);
	//��ʼ�������ؼ�
	InitCommonControls();
	//�������Ի��򣬲��ȴ��Ի������
	int nRet;
	{
		CMainDlg dlg;
		nRet = dlg.DoModal();
	}
	//����COM
	CoUninitialize();
	return nRet;
}
//����Ӧ�ó���ʵ�����
HINSTANCE GetInstance()
{
	return g_hInst;
}