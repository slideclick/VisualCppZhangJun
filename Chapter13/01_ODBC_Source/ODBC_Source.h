// ODBC_Source.h : main header file for the ODBC_SOURCE application
//

#if !defined(AFX_ODBC_SOURCE_H__E179B7E6_3EE9_46E3_BC69_AA47AC1AD1D5__INCLUDED_)
#define AFX_ODBC_SOURCE_H__E179B7E6_3EE9_46E3_BC69_AA47AC1AD1D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CODBC_SourceApp:
// See ODBC_Source.cpp for the implementation of this class
//

class CODBC_SourceApp : public CWinApp
{
public:
	CODBC_SourceApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CODBC_SourceApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CODBC_SourceApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ODBC_SOURCE_H__E179B7E6_3EE9_46E3_BC69_AA47AC1AD1D5__INCLUDED_)
