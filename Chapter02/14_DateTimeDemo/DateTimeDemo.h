// DateTimeDemo.h : main header file for the DATETIMEDEMO application
//

#if !defined(AFX_DATETIMEDEMO_H__A58508DD_BAB0_4AE4_BDA4_BAC5BBC7F4FE__INCLUDED_)
#define AFX_DATETIMEDEMO_H__A58508DD_BAB0_4AE4_BDA4_BAC5BBC7F4FE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDateTimeDemoApp:
// See DateTimeDemo.cpp for the implementation of this class
//

class CDateTimeDemoApp : public CWinApp
{
public:
	CDateTimeDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDateTimeDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDateTimeDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATETIMEDEMO_H__A58508DD_BAB0_4AE4_BDA4_BAC5BBC7F4FE__INCLUDED_)
