// SuperPwd.h : main header file for the SUPERPWD application
//

#if !defined(AFX_SUPERPWD_H__E89BC100_53AD_49CA_8B08_8EBF706D1A53__INCLUDED_)
#define AFX_SUPERPWD_H__E89BC100_53AD_49CA_8B08_8EBF706D1A53__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSuperPwdApp:
// See SuperPwd.cpp for the implementation of this class
//

class CSuperPwdApp : public CWinApp
{
public:
	CSuperPwdApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSuperPwdApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSuperPwdApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SUPERPWD_H__E89BC100_53AD_49CA_8B08_8EBF706D1A53__INCLUDED_)
