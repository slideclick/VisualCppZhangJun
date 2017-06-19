// ChildWnd2.cpp: implementation of the CChildWnd2 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ChildWnd2.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CChildWnd2::CChildWnd2()
{
}

CChildWnd2::~CChildWnd2()
{
}

BOOL CChildWnd2::OnEraseBk(HDC hDC)
{
	//测试窗体2绘制背景为蓝色
	HBRUSH hb = CreateSolidBrush(RGB(0, 0, 127));
	RECT rect = {0};
	GetClientRect(m_hWnd, &rect);
	FillRect(hDC, &rect, hb);
	DeleteObject(hb);
	return 0;
}