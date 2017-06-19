// LayeredWnd.h: interface for the CLayeredWnd class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LAYEREDWND_H__A5F44562_F9D2_4DEB_9E7E_BD0BDB351664__INCLUDED_)
#define AFX_LAYEREDWND_H__A5F44562_F9D2_4DEB_9E7E_BD0BDB351664__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\comm\MyWnd.h"

class CLayeredWnd : public CMyWnd  
{
public:
	CLayeredWnd();
	virtual ~CLayeredWnd();
	void Create();
	void UpdateText(LPCTSTR lpText, HFONT hFont);
protected:
	BOOL OnPaint();
	BOOL PreProcessMsg(HWND hWnd, UINT nMsg, WPARAM wp, LPARAM lp, LRESULT *pResult);
protected:
	LPCTSTR m_lpText;
	HFONT m_hFont;
};

#endif // !defined(AFX_LAYEREDWND_H__A5F44562_F9D2_4DEB_9E7E_BD0BDB351664__INCLUDED_)
