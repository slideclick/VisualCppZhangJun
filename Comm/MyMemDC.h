// MyMemDC.h: interface for the CMyMemDC class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MyMemDC_H__F76F5843_C94C_4912_940F_6064AA0960C3__INCLUDED_)
#define AFX_MyMemDC_H__F76F5843_C94C_4912_940F_6064AA0960C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <GdiPlus.h>

#define RectWidth(x) ((x)->right - (x)->left)
#define RectHeight(x) ((x)->bottom - (x)->top)


class CMyMemDC  
{
public:
	LPRECT GetImageRect();
	int GetHeight();
	int GetWidth();
	HBITMAP GetBitmap() const;
	BOOL CreateFromFile(LPCTSTR lpFile);
	BOOL CreateFromFile(LPCTSTR lpFile, LPRECT lprcBmp);
	BOOL CreateFromFile(LPCTSTR lpFile, HDC hDC, LPRECT lprcBmp);
	operator HDC();
	HDC GetDC() const;
	BOOL DeleteObj();
	BOOL CreateObj(HDC hDC, int nWidth, int nHeight);
	CMyMemDC();
	virtual ~CMyMemDC();
protected:
	RECT m_rcImg;
	HBITMAP m_hOldBmp;
	HBITMAP m_hBmp;
	HDC m_hDC;
};

#endif // !defined(AFX_MyMemDC_H__F76F5843_C94C_4912_940F_6064AA0960C3__INCLUDED_)
