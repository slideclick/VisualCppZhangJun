// CheckBoxDemo.h : main header file for the CHECKBOXDEMO application
//

#if !defined(AFX_CHECKBOXDEMO_H__CF5394D6_6514_4089_90FD_EF154E2F254F__INCLUDED_)
#define AFX_CHECKBOXDEMO_H__CF5394D6_6514_4089_90FD_EF154E2F254F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCheckBoxDemoApp:
// See CheckBoxDemo.cpp for the implementation of this class
//

class CCheckBoxDemoApp : public CWinApp
{
public:
	CCheckBoxDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCheckBoxDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCheckBoxDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHECKBOXDEMO_H__CF5394D6_6514_4089_90FD_EF154E2F254F__INCLUDED_)
