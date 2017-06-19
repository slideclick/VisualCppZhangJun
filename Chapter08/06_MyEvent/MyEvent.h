// MyEvent.h : main header file for the MYEVENT application
//

#if !defined(AFX_MYEVENT_H__2F4743FB_8F1D_49F1_A588_8903A10E1AF5__INCLUDED_)
#define AFX_MYEVENT_H__2F4743FB_8F1D_49F1_A588_8903A10E1AF5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMyEventApp:
// See MyEvent.cpp for the implementation of this class
//

class CMyEventApp : public CWinApp
{
public:
	CMyEventApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyEventApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMyEventApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYEVENT_H__2F4743FB_8F1D_49F1_A588_8903A10E1AF5__INCLUDED_)
