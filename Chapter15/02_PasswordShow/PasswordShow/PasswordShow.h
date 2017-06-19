// PasswordShow.h : main header file for the PASSWORDSHOW application
//

#if !defined(AFX_PASSWORDSHOW_H__418A039D_2128_4A70_8F2D_B03F323144C4__INCLUDED_)
#define AFX_PASSWORDSHOW_H__418A039D_2128_4A70_8F2D_B03F323144C4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CPasswordShowApp:
// See PasswordShow.cpp for the implementation of this class
//

class CPasswordShowApp : public CWinApp
{
public:
	CPasswordShowApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPasswordShowApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPasswordShowApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PASSWORDSHOW_H__418A039D_2128_4A70_8F2D_B03F323144C4__INCLUDED_)
