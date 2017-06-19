// RedirectStdio.h : main header file for the REDIRECTSTDIO application
//

#if !defined(AFX_REDIRECTSTDIO_H__3499B52C_728C_4D74_9833_2549E8C66BB1__INCLUDED_)
#define AFX_REDIRECTSTDIO_H__3499B52C_728C_4D74_9833_2549E8C66BB1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CRedirectStdioApp:
// See RedirectStdio.cpp for the implementation of this class
//

class CRedirectStdioApp : public CWinApp
{
public:
	CRedirectStdioApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRedirectStdioApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CRedirectStdioApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REDIRECTSTDIO_H__3499B52C_728C_4D74_9833_2549E8C66BB1__INCLUDED_)
