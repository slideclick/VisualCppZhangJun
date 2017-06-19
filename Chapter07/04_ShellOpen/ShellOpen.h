// ShellOpen.h : main header file for the SHELLOPEN application
//

#if !defined(AFX_SHELLOPEN_H__3289AD74_051E_4DB4_A8FD_A50D6460B5D0__INCLUDED_)
#define AFX_SHELLOPEN_H__3289AD74_051E_4DB4_A8FD_A50D6460B5D0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CShellOpenApp:
// See ShellOpen.cpp for the implementation of this class
//

class CShellOpenApp : public CWinApp
{
public:
	CShellOpenApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShellOpenApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CShellOpenApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHELLOPEN_H__3289AD74_051E_4DB4_A8FD_A50D6460B5D0__INCLUDED_)
