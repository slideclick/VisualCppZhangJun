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
	//创建窗体
	RECT rect = {0, 500, 300, 700};
	CreateEx(NULL, WS_EX_LAYERED, _T("分层显示透明"), WS_POPUP | WS_SYSMENU, &rect, NULL, NULL);
	Show(SW_SHOW);
	//设置透明色，白色透明
	HMODULE hDll = LoadLibrary(_T("user32.dll"));
	LPSETPROC pSetLayered =	(LPSETPROC)GetProcAddress(hDll, _T("SetLayeredWindowAttributes")); 
	pSetLayered(m_hWnd, RGB(255, 255, 255), 0, LWA_COLORKEY);
	FreeLibrary(hDll);
}

void CLayeredWnd::UpdateText(LPCTSTR lpText, HFONT hFont)
{
	//记录文本，并刷新窗体
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
		//设置DC上的字体和颜色
		HFONT hOldFont = (HFONT)SelectObject(ps.hdc, m_hFont);
		COLORREF crOld = SetTextColor(ps.hdc, RGB(0, 0, 255));
		int nOldMode = SetBkMode(ps.hdc, TRANSPARENT);
		//填充为白色
		FillRect(ps.hdc, &ps.rcPaint, (HBRUSH)GetStockObject(WHITE_BRUSH));
		//绘制文字
		DrawText(ps.hdc, m_lpText, -1, &ps.rcPaint, DT_CENTER);
		//恢复DC并结束绘制
		SelectObject(ps.hdc, hOldFont);
		SetBkMode(ps.hdc, nOldMode);
		SetTextColor(ps.hdc, crOld);
		EndPaint(m_hWnd, &ps);
		//返回FALSE，不调用默认处理过程
		return FALSE;
	}
	else
		//如果没有输入文字，则按默认颜色绘制
		return TRUE;
}

BOOL CLayeredWnd::PreProcessMsg(HWND hWnd, UINT nMsg, WPARAM wp, LPARAM lp, LRESULT *pResult)
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