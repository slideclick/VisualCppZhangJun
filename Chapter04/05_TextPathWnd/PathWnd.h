// PathWnd.h: interface for the CPathWnd class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PATHWND_H__B2D7B5B0_1BAB_44FE_9CE5_42D0A1F3B1C4__INCLUDED_)
#define AFX_PATHWND_H__B2D7B5B0_1BAB_44FE_9CE5_42D0A1F3B1C4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\comm\MyWnd.h"

class CPathWnd : public CMyWnd  
{
public:
	CPathWnd();
	virtual ~CPathWnd();
	void Create();
	void UpdateText(LPCTSTR lpText, HFONT hFont);
protected:
	BOOL OnDestroy();
	BOOL PreProcessMsg(HWND hWnd, UINT nMsg, WPARAM wp, LPARAM lp, LRESULT *pResult);
protected:
	HRGN m_hRgn;	
};

#endif // !defined(AFX_PATHWND_H__B2D7B5B0_1BAB_44FE_9CE5_42D0A1F3B1C4__INCLUDED_)
