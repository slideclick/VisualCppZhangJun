// PathWnd.cpp: implementation of the CPathWnd class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TextPathWnd.h"
#include "PathWnd.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPathWnd::CPathWnd(): m_hRgn(NULL)
{
}

CPathWnd::~CPathWnd()
{
}

void CPathWnd::Create()
{
	//��������ʾ����
	RECT rect = {0, 100, 300, 300};
	CreateEx(NULL, 0, _T("����·��͸��"), WS_OVERLAPPEDWINDOW, &rect, NULL, NULL);
	Show(SW_SHOW);
}

BOOL CPathWnd::OnDestroy()
{
	//�ͷ���Դ
	if (m_hRgn) 
	{
		DeleteObject(m_hRgn);
		m_hRgn = NULL;
	}
	return TRUE;
}

void CPathWnd::UpdateText(LPCTSTR lpText, HFONT hFont)
{
	//���ͷ���Դ
	if (m_hRgn) 
	{
		DeleteObject(m_hRgn);
		m_hRgn = NULL;
	}
	//ȡ�ô���DC	
	HDC hDC = GetDC(m_hWnd);
	int nOldMode = SetBkMode(hDC, TRANSPARENT);
	HFONT hOldFont = (HFONT)SelectObject(hDC, hFont);
	//��ʼ·����¼
	BeginPath(hDC);
	//�����ı�
	TextOut(hDC, 20, 50, lpText, _tcslen(lpText));
	//����·����¼
	EndPath(hDC);
	//��·�������������
	m_hRgn = PathToRegion(hDC);
	//�ָ����ͷ�DC	
	SetBkMode(hDC, nOldMode);
	SelectObject(hDC, hOldFont);
	ReleaseDC(m_hWnd, hDC);
	//������������õ�����
	SetWindowRgn(m_hWnd, m_hRgn, TRUE);
}

BOOL CPathWnd::PreProcessMsg(HWND hWnd, UINT nMsg, WPARAM wp, LPARAM lp, LRESULT *pResult)
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
