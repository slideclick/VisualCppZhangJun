// RegDemo.h : main header file for the REGDEMO application
//

#if !defined(AFX_REGDEMO_H__30647B20_4873_498C_B193_6BB484A88214__INCLUDED_)
#define AFX_REGDEMO_H__30647B20_4873_498C_B193_6BB484A88214__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CRegDemoApp:
// See RegDemo.cpp for the implementation of this class
//

class CRegDemoApp : public CWinApp
{
public:
	CRegDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRegDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CRegDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REGDEMO_H__30647B20_4873_498C_B193_6BB484A88214__INCLUDED_)
