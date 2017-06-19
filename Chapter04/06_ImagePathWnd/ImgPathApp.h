// ImgPathApp.h: interface for the CImgPathApp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMGPATHAPP_H__97F4505A_7E3B_4B60_BE9D_108196BCA0ED__INCLUDED_)
#define AFX_IMGPATHAPP_H__97F4505A_7E3B_4B60_BE9D_108196BCA0ED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\comm\MyApp.h"
#include "imgpathwnd.h"

class CImgPathApp : public CMyApp  
{
public:
	CImgPathApp();
	virtual ~CImgPathApp();
	BOOL InitInstance();
protected:
	CImgPathWnd m_wnd;
};

#endif // !defined(AFX_IMGPATHAPP_H__97F4505A_7E3B_4B60_BE9D_108196BCA0ED__INCLUDED_)
