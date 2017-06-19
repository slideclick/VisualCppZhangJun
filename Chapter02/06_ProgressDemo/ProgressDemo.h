// ProgressDemo.h : main header file for the PROGRESSDEMO application
//

#if !defined(AFX_PROGRESSDEMO_H__A8FD581E_A45E_472D_AB28_781AB7833EF1__INCLUDED_)
#define AFX_PROGRESSDEMO_H__A8FD581E_A45E_472D_AB28_781AB7833EF1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CProgressDemoApp:
// See ProgressDemo.cpp for the implementation of this class
//

class CProgressDemoApp : public CWinApp
{
public:
	CProgressDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProgressDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CProgressDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROGRESSDEMO_H__A8FD581E_A45E_472D_AB28_781AB7833EF1__INCLUDED_)
