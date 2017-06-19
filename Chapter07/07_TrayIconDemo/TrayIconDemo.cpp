// TrayIconDemo.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"
#include "..\..\comm\trayicon.h"

//��������¼�֪ͨ��Ϣ
#define WM_USER_TRAYICON_NOTIFY (WM_USER + 102)
//�������ؽ���Ϣ
const UINT WM_TASKBARCREATED = 
	RegisterWindowMessage(_T("TaskbarCreated"));
//ȫ�ֱ�������
CTrayIcon *g_pTrayicon = NULL;
HICON g_hIcon = NULL;
HMENU g_hTrayMenu = NULL;
TCHAR g_szTip[64];
HINSTANCE g_hInst;
UINT g_uLastIconID;
//���Ի�����̺�������
BOOL CALLBACK DlgProc(HWND hDlg, UINT uMsg, 
	WPARAM wp, LPARAM lp);
//Ӧ�ó������
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	g_hInst = hInstance;
	_tcscpy(g_szTip, _T("����ͼ����ʾ��"));
	//������ģʽ�Ի���
	HWND hWnd = CreateDialogParam(hInstance, 
		MAKEINTRESOURCE(IDD_MAIN), 
		NULL, DlgProc, 0);
	//������Ϣѭ�����ȴ�����
	MSG msg = {0};
	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}
//���Ի������ʵ��
BOOL CALLBACK DlgProc(HWND hDlg, UINT uMsg, 
	WPARAM wp, LPARAM lp)
{
	switch(uMsg) 
	{
	case WM_INITDIALOG:
		//��ʼ������
		g_hTrayMenu = LoadMenu(g_hInst, 
			MAKEINTRESOURCE(IDR_TRAYICON));
		SetDlgItemText(hDlg, IDC_EDT_TIP, g_szTip);
		g_uLastIconID = IDI_TRAYICON;
		g_hIcon = LoadIcon(g_hInst, 
			MAKEINTRESOURCE(g_uLastIconID));
		//��������ͼ����
		g_pTrayicon = new CTrayIcon(hDlg, 0, 
			WM_USER_TRAYICON_NOTIFY, g_hIcon, g_szTip);
		//��ʾͼ��
		g_pTrayicon->ShowIcon();
		break;
	case WM_DESTROY:
		//ɾ������ͼ�꣬���ٶ���
		g_pTrayicon->HideIcon();
		delete g_pTrayicon;
		//�˳�Ӧ�ó���
		PostQuitMessage(0);
		break;
	case WM_CLOSE:
		DestroyWindow(hDlg);
		break;
	case WM_COMMAND:
		//����ť�Ͳ˵���Ϣ
		switch(LOWORD(wp))
		{
		case IDCANCEL:
			PostMessage(hDlg, WM_CLOSE, 0, 0);
			break;
		case IDC_BTN_CHANGEICON:
			//����ͼ��
			if(g_uLastIconID == IDI_TRAYICON)
				g_uLastIconID = IDI_TRAYICON_1;
			else
				g_uLastIconID = IDI_TRAYICON;
			g_hIcon = LoadIcon(g_hInst, 
				MAKEINTRESOURCE(g_uLastIconID));
			g_pTrayicon->SetIcon(g_hIcon);
			break;
		case IDC_BTN_UPDATETIP:
			//�޸���ʾ�ı�
			GetDlgItemText(hDlg, IDC_EDT_TIP, 
				g_szTip, sizeof(g_szTip)/sizeof(TCHAR) - 1);
			g_pTrayicon->SetTipText(g_szTip);
			break;
		case IDR_SHOW_WINDOW:
			//��ʾ���Ի���
			ShowWindow(hDlg, SW_SHOW);
			break;
		}
		break;
	case WM_USER_TRAYICON_NOTIFY:
		//����ͼ�������Ϣ��Ӧ
		if(lp == WM_LBUTTONDOWN || lp == WM_RBUTTONDOWN)
		{
			SetForegroundWindow(hDlg);
			POINT pt = {0};
			GetCursorPos(&pt);
			//�����λ�õ����˵�
			TrackPopupMenu(GetSubMenu(g_hTrayMenu, 0), 
				TPM_RIGHTALIGN | TPM_BOTTOMALIGN | TPM_RIGHTBUTTON, 
				pt.x, pt.y, 0, hDlg, NULL);
		}
		break;
	default:
		if(uMsg == WM_TASKBARCREATED)
		{
			//�������ؽ���Ϣ���ؽ�����ͼ��
			if(g_pTrayicon->IsVisibled())
				g_pTrayicon->Rebuild();
			break;
		}
		return FALSE;
	}
	return TRUE;
}