// EllipticalWindow.h : main header file for the ELLIPTICALWINDOW application
//

#if !defined(AFX_ELLIPTICALWINDOW_H__A502E57F_0F0B_43FC_B2D7_0B7FA8381F6C__INCLUDED_)
#define AFX_ELLIPTICALWINDOW_H__A502E57F_0F0B_43FC_B2D7_0B7FA8381F6C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CEllipticalWindowApp:
// See EllipticalWindow.cpp for the implementation of this class
//

class CEllipticalWindowApp : public CWinApp
{
public:
	CEllipticalWindowApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEllipticalWindowApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEllipticalWindowApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ELLIPTICALWINDOW_H__A502E57F_0F0B_43FC_B2D7_0B7FA8381F6C__INCLUDED_)
