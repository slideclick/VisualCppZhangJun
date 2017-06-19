// MyReal.h : main header file for the MYREAL application
//

#if !defined(AFX_MYREAL_H__713E1797_AACA_43E9_A3E6_32DB80833750__INCLUDED_)
#define AFX_MYREAL_H__713E1797_AACA_43E9_A3E6_32DB80833750__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMyRealApp:
// See MyReal.cpp for the implementation of this class
//

class CMyRealApp : public CWinApp
{
public:
	CMyRealApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyRealApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMyRealApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYREAL_H__713E1797_AACA_43E9_A3E6_32DB80833750__INCLUDED_)
