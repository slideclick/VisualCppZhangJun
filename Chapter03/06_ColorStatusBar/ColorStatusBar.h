// ColorStatusBar.h : main header file for the COLORSTATUSBAR application
//

#if !defined(AFX_COLORSTATUSBAR_H__75DED75A_E931_4EF7_ABD4_0C7FE6FE4430__INCLUDED_)
#define AFX_COLORSTATUSBAR_H__75DED75A_E931_4EF7_ABD4_0C7FE6FE4430__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CColorStatusBarApp:
// See ColorStatusBar.cpp for the implementation of this class
//

class CColorStatusBarApp : public CWinApp
{
public:
	CColorStatusBarApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorStatusBarApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CColorStatusBarApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORSTATUSBAR_H__75DED75A_E931_4EF7_ABD4_0C7FE6FE4430__INCLUDED_)
