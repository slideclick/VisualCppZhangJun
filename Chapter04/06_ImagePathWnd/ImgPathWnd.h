// ImgPathWnd.h: interface for the CImgPathWnd class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMGPATHWND_H__F2EFCF05_7EC3_46A9_9741_0589381EF953__INCLUDED_)
#define AFX_IMGPATHWND_H__F2EFCF05_7EC3_46A9_9741_0589381EF953__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\comm\MyWnd.h"

class CImgPathWnd : public CMyWnd  
{
public:
	CImgPathWnd();
	virtual ~CImgPathWnd();
protected:
	LRESULT OnCreate(HWND hWnd);
	BOOL OnDestroy();
	BOOL OnPaint();
	BOOL PreProcessMsg(HWND hWnd, UINT nMsg, WPARAM wp, LPARAM lp, LRESULT *pResult);
	HRGN CreateRgn(COLORREF crTransparent);
protected:
	HDC m_hMemDC;
	HBITMAP m_hBmp;
	HBITMAP m_hOldBmp;
	HRGN m_hRgn;
};

#endif // !defined(AFX_IMGPATHWND_H__F2EFCF05_7EC3_46A9_9741_0589381EF953__INCLUDED_)
