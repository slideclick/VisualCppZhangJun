// DlgSkin.h: interface for the CDlgSkin class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DLGSKIN_H__2BC3EC14_E1DA_4E39_83D0_7091982A3F22__INCLUDED_)
#define AFX_DLGSKIN_H__2BC3EC14_E1DA_4E39_83D0_7091982A3F22__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//∆§∑Ù ˝æ›
struct SkinData
{
	HWND hWnd;
	WNDPROC procOld;
};

class CDlgSkin  
{
public:
	//…Ë÷√∆§∑Ù
	static int SetSkin(COLORREF crBg);
	//–∂‘ÿ∆§∑Ù
	static int FreeSkin();
protected:
	static LRESULT CALLBACK NewDlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK CallWndProc(int nCode, WPARAM wp, LPARAM lp);
};

#endif // !defined(AFX_DLGSKIN_H__2BC3EC14_E1DA_4E39_83D0_7091982A3F22__INCLUDED_)
