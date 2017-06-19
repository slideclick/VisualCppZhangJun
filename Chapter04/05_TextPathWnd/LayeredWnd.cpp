// LayeredWnd.cpp: implementation of the CLayeredWnd class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TextPathWnd.h"
#include "LayeredWnd.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#define WS_EX_LAYERED 0x80000
#define LWA_COLORKEY 0x1
typedef BOOL (WINAPI *LPSETPROC)(HWND, COLORREF, BYTE, DWORD);

CLayeredWnd::CLayeredWnd(): m_lpText(NULL), m_hFont(NULL)
{

}

CLayeredWnd::~CLayeredWnd()
{

}

void CLayeredWnd::Create()
{
	//��������
	RECT rect = {0, 500, 300, 700};
	CreateEx(NULL, WS_EX_LAYERED, _T("�ֲ���ʾ͸��"), WS_POPUP | WS_SYSMENU, &rect, NULL, NULL);
	Show(SW_SHOW);
	//����͸��ɫ����ɫ͸��
	HMODULE hDll = LoadLibrary(_T("user32.dll"));
	LPSETPROC pSetLayered =	(LPSETPROC)GetProcAddress(hDll, _T("SetLayeredWindowAttributes")); 
	pSetLayered(m_hWnd, RGB(255, 255, 255), 0, LWA_COLORKEY);
	FreeLibrary(hDll);
}

void CLayeredWnd::UpdateText(LPCTSTR lpText, HFONT hFont)
{
	//��¼�ı�����ˢ�´���
	m_lpText = lpText;
	m_hFont = hFont;
	InvalidateRect(m_hWnd, NULL, FALSE);
}

BOOL CLayeredWnd::OnPaint()
{
	if(m_lpText && (*m_lpText != 0))
	{
		PAINTSTRUCT ps = {0};
		BeginPaint(m_hWnd, &ps);
		//����DC�ϵ��������ɫ
		HFONT hOldFont = (HFONT)SelectObject(ps.hdc, m_hFont);
		COLORREF crOld = SetTextColor(ps.hdc, RGB(0, 0, 255));
		int nOldMode = SetBkMode(ps.hdc, TRANSPARENT);
		//���Ϊ��ɫ
		FillRect(ps.hdc, &ps.rcPaint, (HBRUSH)GetStockObject(WHITE_BRUSH));
		//��������
		DrawText(ps.hdc, m_lpText, -1, &ps.rcPaint, DT_CENTER);
		//�ָ�DC����������
		SelectObject(ps.hdc, hOldFont);
		SetBkMode(ps.hdc, nOldMode);
		SetTextColor(ps.hdc, crOld);
		EndPaint(m_hWnd, &ps);
		//����FALSE��������Ĭ�ϴ������
		return FALSE;
	}
	else
		//���û���������֣���Ĭ����ɫ����
		return TRUE;
}

BOOL CLayeredWnd::PreProcessMsg(HWND hWnd, UINT nMsg, WPARAM wp, LPARAM lp, LRESULT *pResult)
{
	if (nMsg == WM_NCHITTEST) 
	{
		//�ڴ�������λ�þ�����HTCAPTION���Ա㴰����Ա�����϶�
		*pResult = HTCAPTION;
		return FALSE;
	}
	else
		return TRUE;
}