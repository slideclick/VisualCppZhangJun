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
	void Move(LPRECT prcWnd);			//�ƶ��ؼ���ָ��λ��
	BOOL GetVisible();					//��ȡ�ؼ��Ƿ�ɼ�
	BOOL SetVsible(BOOL bVisible);		//���ÿؼ��Ŀɼ�״̬
	BOOL SetRange(int nRange);			//���ý���
	void Destroy();						//���ٿؼ�
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
