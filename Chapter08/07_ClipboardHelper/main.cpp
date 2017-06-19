#include <windows.h>
#include <tchar.h>
#include <stdio.h>

#include "resource.h"

//////////////////////////////////////////////////////////////////////////
// �궨��
//////////////////////////////////////////////////////////////////////////

//ճ�����ȼ�ID
#define HOTKEY_ID_PASTE 1
//�����˳����ȼ�ID
#define HOTKEY_ID_EXIT 2
//���а��ʽ
#ifdef UNICODE
  #define CT_TCHAR CF_UNICODETEXT
#else
  #define CT_TCHAR CF_TEXT
#endif //#ifdef UNICODE


//////////////////////////////////////////////////////////////////////////
// ȫ�ֱ�������
//////////////////////////////////////////////////////////////////////////

//�Ի�����
HWND g_hDlg;


//////////////////////////////////////////////////////////////////////////
// ȫ�ֺ�������
//////////////////////////////////////////////////////////////////////////

//�Ի������
INT_PTR CALLBACK MainDlgProc(HWND hDlg, UINT uMsg, WPARAM wp, LPARAM lp);
//�ȼ�����
void OnHotkey();


//////////////////////////////////////////////////////////////////////////
// ����ʵ��
//////////////////////////////////////////////////////////////////////////

//�������
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	//��������
	g_hDlg = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_MAIN), NULL, MainDlgProc);
	if (g_hDlg == NULL) 
	{
		DebugBreak();
		return 0;
	}
	//��Ϣѭ��
	MSG msg;
	while(GetMessage(&msg, NULL, 0, 0))
	{
		DispatchMessage(&msg);
	}
	return 0;
}

//�Ի������
INT_PTR CALLBACK MainDlgProc(HWND hDlg, UINT uMsg, WPARAM wp, LPARAM lp)
{
	BOOL bRet = TRUE;
	switch(uMsg) 
	{
	case WM_INITDIALOG:
		//ע���ȼ�
		if( !RegisterHotKey(hDlg, HOTKEY_ID_PASTE, MOD_WIN, 'P')
			|| !RegisterHotKey(hDlg, HOTKEY_ID_EXIT, MOD_WIN, 'Q'))
		{
			//���ע��ʧ�ܣ���ʾ������ʾ���˳�
			DWORD dwErr = GetLastError();
			TCHAR szBuf[256] = {0};
			FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, dwErr, 
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
				szBuf, sizeof(szBuf)/sizeof(*szBuf), NULL);
			MessageBox(NULL, szBuf, _T("Error"), MB_OK);
			PostMessage(hDlg, WM_CLOSE, 0, 0);
		}
		break;
	case WM_CLOSE:
		//���ٴ���
		DestroyWindow(hDlg);
		break;
	case WM_DESTROY:
		//ȡ���ȼ������˳�����
		UnregisterHotKey(hDlg, HOTKEY_ID_PASTE);
		UnregisterHotKey(hDlg, HOTKEY_ID_EXIT);
		PostQuitMessage(0);
		break;
	case WM_HOTKEY:
		//�����ȼ���Ϣ
		if(wp == HOTKEY_ID_PASTE)
		{
			//���ı�ճ��
			OnHotkey();
		}
		else if(wp == HOTKEY_ID_EXIT)
		{
			//�˳�Ӧ�ó���
			MessageBeep(MB_OK);
			PostMessage(hDlg, WM_CLOSE, 0, 0);
		}
		break;
	default:
		bRet = FALSE;
		break;
	}
	return bRet;
}

void OnHotkey()
{
	//�򿪼��а�
	if(OpenClipboard(g_hDlg))
	{
		//���ԴӼ��а��ȡ�ı��͵�����
		HGLOBAL hGlobal = GetClipboardData(CT_TCHAR);
		//�����ڴ�
		LPCSTR lpText = (LPCSTR)GlobalLock(hGlobal);
		if(lpText && *lpText)
		{
			//���ı�
			int nLen = (_tcslen(lpText) + 1) * sizeof(TCHAR);
			//����һ��ɿ���̷��ʵ��ڴ�
			HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, nLen);
			//�����ڴ沢����ڴ����ֽ�ָ��
			LPTSTR pText = (LPTSTR)GlobalLock(hGlobal);
			//���ı����Ƶ����ڴ�
			_tcscpy(pText, lpText);
			//�����ڴ�
			GlobalUnlock(hGlobal);
			//��ռ��а�
			EmptyClipboard();
			//���ı����õ����а�
			SetClipboardData(CT_TCHAR, hGlobal);	
			//�رռ��а�
			CloseClipboard();

			//ճ��
			keybd_event(VK_CONTROL, 0, 0, 0);
			keybd_event('V', 0, 0, 0);
			Sleep(1);
			keybd_event('V', 0, KEYEVENTF_KEYUP, 0);
			keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		}
		else
		{
			GlobalUnlock(hGlobal);
			CloseClipboard();
			//���ı�
			MessageBeep(MB_ICONEXCLAMATION);
		}
	}
	else
	{
		MessageBeep(MB_ICONEXCLAMATION);
	}
}