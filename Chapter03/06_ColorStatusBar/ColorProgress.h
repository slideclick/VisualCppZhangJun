// ColorProgress.h: interface for the CColorProgress class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COLORPROGRESS_H__C0BC22FC_6875_4E86_8A96_D8C4D75CE6B6__INCLUDED_)
#define AFX_COLORPROGRESS_H__C0BC22FC_6875_4E86_8A96_D8C4D75CE6B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CColorProgress  
{
public:
	void Move(LPRECT prcWnd);			//移动控件到指定位置
	BOOL GetVisible();					//获取控件是否可见
	BOOL SetVsible(BOOL bVisible);		//设置控件的可见状态
	BOOL SetRange(int nRange);			//设置进度
	void Destroy();						//销毁控件
	BOOL Create(HWND hParent, LPRECT prcWnd, COLORREF crBegin, COLORREF crEnd);
	CColorProgress();
	virtual ~CColorProgress();
protected:
	void DrawBar(HDC hDC);
	COLORREF GetNextColor(int nRange);
	static LRESULT CALLBACK NewWndProc(HWND hWnd, UINT nMsg, WPARAM wp, LPARAM lp);
protected:
	HWND m_hWnd;
	int m_nMaxRange;
	int m_nMinRange;
	int m_nCurrentRange;
	COLORREF m_crBegin;
	COLORREF m_crEnd;
	WNDPROC m_pOldProc;
};

#endif // !defined(AFX_COLORPROGRESS_H__C0BC22FC_6875_4E86_8A96_D8C4D75CE6B6__INCLUDED_)
