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
	//创建并显示窗体
	RECT rect = {0, 100, 300, 300};
	CreateEx(NULL, 0, _T("利用路径透明"), WS_OVERLAPPEDWINDOW, &rect, NULL, NULL);
	Show(SW_SHOW);
}

BOOL CPathWnd::OnDestroy()
{
	//释放资源
	if (m_hRgn) 
	{
		DeleteObject(m_hRgn);
		m_hRgn = NULL;
	}
	return TRUE;
}

void CPathWnd::UpdateText(LPCTSTR lpText, HFONT hFont)
{
	//先释放资源
	if (m_hRgn) 
	{
		DeleteObject(m_hRgn);
		m_hRgn = NULL;
	}
	//取得窗体DC	
	HDC hDC = GetDC(m_hWnd);
	int nOldMode = SetBkMode(hDC, TRANSPARENT);
	HFONT hOldFont = (HFONT)SelectObject(hDC, hFont);
	//开始路径记录
	BeginPath(hDC);
	//绘制文本
	TextOut(hDC, 20, 50, lpText, _tcslen(lpText));
	//结束路径记录
	EndPath(hDC);
	//从路径生成区域对象
	m_hRgn = PathToRegion(hDC);
	//恢复并释放DC	
	SetBkMode(hDC, nOldMode);
	SelectObject(hDC, hOldFont);
	ReleaseDC(m_hWnd, hDC);
	//把区域对象设置到窗体
	SetWindowRgn(m_hWnd, m_hRgn, TRUE);
}

BOOL CPathWnd::PreProcessMsg(HWND hWnd, UINT nMsg, WPARAM wp, LPARAM lp, LRESULT *pResult)
{
	if (nMsg == WM_NCHITTEST) 
	{
		//在窗体任意位置均返回HTCAPTION，以便窗体可以被鼠标拖动
		*pResult = HTCAPTION;
		return FALSE;
	}
	else
		return TRUE;
}
