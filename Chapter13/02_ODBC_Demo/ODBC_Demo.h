// ODBC_Demo.h : main header file for the ODBC_DEMO application
//

#if !defined(AFX_ODBC_DEMO_H__6B759540_DE65_4A4A_9415_B3E82540E038__INCLUDED_)
#define AFX_ODBC_DEMO_H__6B759540_DE65_4A4A_9415_B3E82540E038__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CODBC_DemoApp:
// See ODBC_Demo.cpp for the implementation of this class
//

class CODBC_DemoApp : public CWinApp
{
public:
	CODBC_DemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CODBC_DemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CODBC_DemoApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ODBC_DEMO_H__6B759540_DE65_4A4A_9415_B3E82540E038__INCLUDED_)
