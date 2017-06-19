// ChildWnd1.cpp: implementation of the CChildWnd1 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ChildWnd1.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CChildWnd1::CChildWnd1()
{
}

CChildWnd1::~CChildWnd1()
{
}

BOOL CChildWnd1::OnEraseBk(HDC hDC)
{
	//测试窗体1绘制背景为绿色
	HBRUSH hb = CreateSolidBrush(RGB(0, 127, 0));
	RECT rect = {0};
	GetClientRect(m_hWnd, &rect);
	FillRect(hDC, &rect, hb);
	DeleteObject(hb);
	return 0;
}