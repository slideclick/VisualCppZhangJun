// PopMenuDemo.h : main header file for the POPMENUDEMO application
//

#if !defined(AFX_POPMENUDEMO_H__A20EEB42_0453_4076_9372_CD380096074A__INCLUDED_)
#define AFX_POPMENUDEMO_H__A20EEB42_0453_4076_9372_CD380096074A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CPopMenuDemoApp:
// See PopMenuDemo.cpp for the implementation of this class
//

class CPopMenuDemoApp : public CWinApp
{
public:
	CPopMenuDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPopMenuDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPopMenuDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POPMENUDEMO_H__A20EEB42_0453_4076_9372_CD380096074A__INCLUDED_)
