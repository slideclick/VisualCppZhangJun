// MainWnd.cpp: implementation of the CMainWnd class.
//
//////////////////////////////////////////////////////////////////////

#include "MainWnd.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define LWA_ALPHA 0x2
#define WS_EX_LAYERED 0x80000
typedef BOOL (WINAPI *LPSETPROC)(HWND, COLORREF, BYTE, DWORD);
//LPSETPROC g_pSetLayered = NULL;

CMainWnd::CMainWnd()
{
}

CMainWnd::~CMainWnd()
{
}

LRESULT CMainWnd::OnCreate(HWND hWnd)
{
	//�ı䴰����չ�������֧�ֲַ���ʾ
	DWORD dwExStyle = GetWindowLong(hWnd, GWL_EXSTYLE);
	SetWindowLong(hWnd, GWL_EXSTYLE, dwExStyle | WS_EX_LAYERED);
	//������ʱ��
	SetTimer(hWnd, 1, 50, NULL);
	return 0;
}

BOOL CMainWnd::OnDestroy()
{
	//���ͽ�����Ϣѭ����Ϣ���˳�Ӧ�ó���
	PostQuitMessage(0);
	return FALSE;
}

BOOL CMainWnd::OnTimer(int nID)
{
	//��ʱ�ı䴰���͸����
	static int nTrans = 0xFF;
	nTrans --;
	if (nTrans == 0) 
		nTrans = 0xFF;
	//�ڱ�������ʾĿǰ��͸����
	TCHAR szTitle[128] = {0};
	_stprintf(szTitle, _T("͸���ȣ�%d"), nTrans);
	SetWindowText(m_hWnd, szTitle);
	//���ô���͸����
	HMODULE hDll = LoadLibrary(_T("user32.dll"));
	LPSETPROC pSetLayered =	(LPSETPROC)GetProcAddress(hDll, _T("SetLayeredWindowAttributes")); 
	pSetLayered(m_hWnd, RGB(255, 0, 0), nTrans, LWA_ALPHA);
	FreeLibrary(hDll);

	return FALSE;
}