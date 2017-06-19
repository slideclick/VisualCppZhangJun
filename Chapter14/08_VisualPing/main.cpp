#include "resource.h"
#include "MyPing.h"
#include "options.h"
#include "..\..\comm\trayicon.h"

//����ͼ����Ϣ
#define WM_USER_TRAYICON (WM_USER + 121)
//Ping��Ϣ
#define WM_USER_PING	 (WM_USER + 122)

//----------------
//ȫ�ֱ�������
//-----------------
//Ӧ�ó���ʵ�����
HINSTANCE	g_hInst = NULL;
//���Ի���Ĵ��ھ��
HWND		g_hDlg = NULL;
//Ping��װ��
CMyPing		g_ping;
//����ͼ���װ��
CTrayIcon	*g_pTray = NULL;
//�������
COptions		g_option;
//Ӧ�ó���ͼ��
HICON		g_hIconApp	 = NULL;
//�����е�ͼ��
HICON		g_hIconTray0 = NULL;
HICON		g_hIconTray1 = NULL;
HICON		g_hIconTray2 = NULL;
HICON		g_hIconTray3 = NULL;
HICON		g_hIconTray4 = NULL;
//���̲˵�
HMENU		g_hTrayMenu  = NULL;
//�������ؽ���Ϣ
const UINT WM_TASKBARCREATED = 
	RegisterWindowMessage(_T("TaskbarCreated"));

//----------------
//��������
//----------------
//�Ի�����̺���
int CALLBACK 
MainDlgProc(HWND hwndDlg, UINT uMsg, 
			WPARAM wParam, LPARAM lParam);
//�Ի����ʼ����Ϣ����
void OnInitDialog();
//�Ի�������ǰ
void OnDestroy();
//Ping��Ϣ
void OnPingNotify(WPARAM wp, LPARAM lp);

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
	//��ʼ��Windows Sockets����
	WSADATA wsa = {0};	
	WSAStartup(MAKEWORD(2,2) , &wsa);
	//����һ�����صķ�ģʽ�Ի���
	HWND hWnd = CreateDialog(hInstance, 
		MAKEINTRESOURCE(IDD_MAIN), NULL, MainDlgProc);
	if(hWnd == NULL)
	{
		DebugBreak();
		return 0;
	}
	//������Ϣѭ��
	MSG msg = {0};
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg); 
		DispatchMessage(&msg);
	}
	//����Sockets����
	WSACleanup();
	//��Ϣѭ��������Ӧ�ó��򼴽��˳�
	return msg.wParam;
}
//�Ի�����̺���
int CALLBACK 
MainDlgProc(HWND hwndDlg, UINT uMsg, 
			WPARAM wParam, LPARAM lParam)
{
	int nRet = 1;
	switch(uMsg) 
	{
		//�Ի����ʼ��
	case WM_INITDIALOG:		
		//���洰�ھ��
		g_hDlg = hwndDlg;		
		OnInitDialog();
		break;
		//��������
	case WM_COMMAND:		
		switch(LOWORD(wParam))
		{
		//�˳��˵�
		case IDR_EXIT:
			PostMessage(hwndDlg, WM_CLOSE, 0, 0);
			break;
		}
		break;
		//�رնԻ���
	case WM_CLOSE:			
		DestroyWindow(hwndDlg);
		break;
		//���ٴ���
	case WM_DESTROY:
		OnDestroy();
		break;
		//����ͼ���¼�
	case WM_USER_TRAYICON:
		if(lParam == WM_LBUTTONDOWN || lParam == WM_RBUTTONDOWN)
		{
			SetForegroundWindow(hwndDlg);
			POINT pt = {0};
			GetCursorPos(&pt);
			//�����λ�õ����˵�
			TrackPopupMenu(GetSubMenu(g_hTrayMenu, 0), 
				TPM_RIGHTALIGN | TPM_BOTTOMALIGN | TPM_RIGHTBUTTON, 
				pt.x, pt.y, 0, hwndDlg, NULL);
		}
		break;
		//Ping�̷߳�������Ϣ
	case WM_USER_PING:
		OnPingNotify(wParam, lParam);
		break;
	default:
		if(uMsg == WM_TASKBARCREATED)
		{
			//�������ؽ���Ϣ���ؽ�����ͼ��
			if(g_pTray->IsVisibled())
				g_pTray->Rebuild();
			break;
		}
		nRet = 0;
	}
	return nRet;
}
//�Ի����ʼ����Ϣ����
void OnInitDialog()
{
	//����Ӧ�ó���ͼ��
	g_hIconApp = LoadIcon(g_hInst, MAKEINTRESOURCE(IDI_APP));
	//��������Ҫ�õ���ͼ��
	g_hIconTray0 = LoadIcon(g_hInst, MAKEINTRESOURCE(IDI_TRAY0));
	g_hIconTray1 = LoadIcon(g_hInst, MAKEINTRESOURCE(IDI_TRAY1));
	g_hIconTray2 = LoadIcon(g_hInst, MAKEINTRESOURCE(IDI_TRAY2));
	g_hIconTray3 = LoadIcon(g_hInst, MAKEINTRESOURCE(IDI_TRAY3));
	g_hIconTray4 = LoadIcon(g_hInst, MAKEINTRESOURCE(IDI_TRAY4));
	g_hTrayMenu  = LoadMenu(g_hInst, MAKEINTRESOURCE(IDR_TRAY));
	//��������ͼ�����
	g_pTray = new CTrayIcon(g_hDlg, 1, 
		WM_USER_TRAYICON, g_hIconApp, _T("�ȴ�Ping..."));
	//��ʾͼ��
	g_pTray->ShowIcon();
	//��ʼ��CPing����
	g_ping.StartPing(g_hDlg, g_option.szTargetName, 
		WM_USER_PING, g_option.dwPingInterval, g_option.dwTimeout);
}
//�Ի�������ǰ
void OnDestroy()
{
	g_pTray->SetIcon(g_hIconApp);
	g_pTray->SetTipText(_T("�ȴ��ر�..."));
	//�ͷ�CPing�������Դ
	g_ping.Release();
	//ɾ������ͼ��
	g_pTray->HideIcon();
	delete g_pTray;
	//�ͷ�ͼ����Դ
	DestroyIcon(g_hIconApp);
	DestroyIcon(g_hIconTray0);
	DestroyIcon(g_hIconTray1);
	DestroyIcon(g_hIconTray2);
	DestroyIcon(g_hIconTray3);
	DestroyIcon(g_hIconTray4);
	//ɾ���˵���Դ
	DestroyMenu(g_hTrayMenu);
	//Ͷ���˳���Ϣ
	PostQuitMessage(0);	
}
//Ping��Ϣ,wp����Ping�Ƿ�ɹ���lp����Pingֵ
void OnPingNotify(WPARAM wp, LPARAM lp)
{
	HICON hTrayIcon;
	TCHAR szText[128] = {0};
	switch(wp) 
	{
	//ͨѶ�����г���
	case 2:
		hTrayIcon = g_hIconTray0;
		_tcscpy(szText, _T("ͨѶ����"));
		break;
	//��ʱ
	case 1:
		hTrayIcon = g_hIconTray0;
		_tcscpy(szText, _T("ͨѶ��ʱ"));
		break;
	//����
	case 0:
		//����Pingֵȷ��ͼ��
		if(lp < g_option.dwTime4)
			hTrayIcon = g_hIconTray4;
		else if(lp < g_option.dwTime3)
			hTrayIcon = g_hIconTray3;
		else if (lp < g_option.dwTime2)
			hTrayIcon = g_hIconTray2;
		else
			hTrayIcon = g_hIconTray1;
		_stprintf(szText, _T("����Pingֵ:%d"), lp);
		break;
	default:
		DebugBreak();
		return;
	}
	//��������ͼ�����ʾ����
	TCHAR szTrayText[512] = {0};
	_stprintf(szTrayText, _T("�� %s ��%s"), g_option.szTargetName, szText);
	g_pTray->SetTipText(szTrayText);
	//�������̵�ͼ��
	g_pTray->SetIcon(hTrayIcon);
}
