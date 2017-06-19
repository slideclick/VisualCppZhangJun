// ColorProgress.cpp: implementation of the CColorProgress class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "ColorStatusBar.h"
#include "ColorProgress.h"

#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CColorProgress::CColorProgress(): m_hWnd(NULL), m_nMaxRange(100), m_nMinRange(0), m_nCurrentRange(0), m_crBegin(0), m_crEnd(0)
{

}

CColorProgress::~CColorProgress()
{

}

BOOL CColorProgress::Create(HWND hParent, LPRECT prcWnd, COLORREF crBegin, COLORREF crEnd)
{
	m_crBegin = crBegin;
	m_crEnd = crEnd;
	//创建一个窗口
	m_hWnd = CreateWindow(_T("STATIC"), NULL, WS_CHILD, 
		prcWnd->left, prcWnd->top, prcWnd->right - prcWnd->left, prcWnd->bottom - prcWnd->top, 
		hParent, NULL, NULL, this);
	if(m_hWnd)
	{
		//修改窗口的消息处理函数地址，实现子类化，以便接管绘制过程
		SetWindowLong(m_hWnd, GWL_USERDATA, (long)this);
		m_pOldProc = (WNDPROC)SetWindowLong(m_hWnd, GWL_WNDPROC, (long)NewWndProc);
	}
	return (m_hWnd != NULL);
}

void CColorProgress::Destroy()
{
	//释放资源
	if(m_hWnd)
	{
		SetWindowLong(m_hWnd, GWL_WNDPROC, (long)m_pOldProc);
		DestroyWindow(m_hWnd);
		m_hWnd = NULL;
	}
}

BOOL CColorProgress::SetRange(int nRange)
{
	//设置进度
	if(nRange >= m_nMaxRange || nRange < m_nMinRange)
		return FALSE;
	//保存新的进度，并刷新窗口
	m_nCurrentRange = nRange;
	InvalidateRect(m_hWnd, NULL, FALSE);
	return TRUE;
}

BOOL CColorProgress::SetVsible(BOOL bVisible)
{
	return ShowWindow(m_hWnd, bVisible ? SW_SHOW : SW_HIDE);
}

BOOL CColorProgress::GetVisible()
{
	//判断窗体是否可见
	long lStyle = GetWindowLong(m_hWnd, GWL_STYLE);
	return(lStyle | WS_VISIBLE == WS_VISIBLE);
}

void CColorProgress::Move(LPRECT prcWnd)
{
	MoveWindow(m_hWnd, prcWnd->left, prcWnd->top, prcWnd->right - prcWnd->left, prcWnd->bottom - prcWnd->top, TRUE);
}

void CColorProgress::DrawBar(HDC hDC)
{
	//绘制进度条
	RECT rcClient;
	RECT rcDraw = {0};
	COLORREF crTemp;
	HBRUSH hbTemp = NULL;
	//算出每步绘制的像素
	GetClientRect(m_hWnd, &rcClient);
	int nStep = (rcClient.right + m_nMaxRange - 1)/ m_nMaxRange;
	//循环绘制
	for(int i=m_nMinRange; i<m_nCurrentRange; i++)
	{
		crTemp = GetNextColor(i);
		SetRect(&rcDraw, i * nStep, 0, (i + 1) * nStep, rcClient.bottom);
		hbTemp = CreateSolidBrush(crTemp);
		FillRect(hDC, &rcDraw, hbTemp);
		DeleteObject(hbTemp);
	}
}

COLORREF CColorProgress::GetNextColor(int nRange)
{
	int r,g,b;
	//新的红分量
	r = (GetRValue(m_crEnd) - GetRValue(m_crBegin)) * nRange / m_nMaxRange;
	if(r < 0)
		r += GetRValue(m_crBegin);
	//新的绿分量
	g =	(GetGValue(m_crEnd) - GetGValue(m_crBegin)) * nRange / m_nMaxRange;
	if(g < 0)
		g += GetGValue(m_crBegin);
	//新的蓝分量
	b = (GetBValue(m_crEnd) - GetBValue(m_crBegin)) * nRange / m_nMaxRange;
	if(b < 0)
		b += GetBValue(m_crBegin);
	//组合成颜色并返回
	return RGB(r, g, b);
}

LRESULT CALLBACK CColorProgress::NewWndProc(HWND hWnd, UINT nMsg, WPARAM wp, LPARAM lp)
{
	//控件的消息处理过程
	CColorProgress *pCtrl = (CColorProgress *)GetWindowLong(hWnd, GWL_USERDATA);
	switch(nMsg)
	{
	//绘制消息，绘制进度条
	case WM_PAINT:	
		if(pCtrl->m_nCurrentRange == 0)
			break;
		else
		{
			PAINTSTRUCT ps = {0};
			BeginPaint(hWnd, &ps);
			pCtrl->DrawBar(ps.hdc);
			EndPaint(hWnd, &ps);
		}
		return 0;
	default:		
		break;
	}
	//其他消息用默认过程处理
	return CallWindowProc(pCtrl->m_pOldProc, hWnd, nMsg, wp, lp);
}