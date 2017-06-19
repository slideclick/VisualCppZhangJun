// ZoomBitmap.h : main header file for the ZOOMBITMAP application
//

#if !defined(AFX_ZOOMBITMAP_H__6248DFBD_D73D_4298_BF1B_5F54632CD143__INCLUDED_)
#define AFX_ZOOMBITMAP_H__6248DFBD_D73D_4298_BF1B_5F54632CD143__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CZoomBitmapApp:
// See ZoomBitmap.cpp for the implementation of this class
//

class CZoomBitmapApp : public CWinApp
{
public:
	CZoomBitmapApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZoomBitmapApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CZoomBitmapApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZOOMBITMAP_H__6248DFBD_D73D_4298_BF1B_5F54632CD143__INCLUDED_)
