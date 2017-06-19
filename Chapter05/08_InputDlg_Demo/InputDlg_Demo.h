// InputDlg_Demo.h : main header file for the INPUTDLG_DEMO application
//

#if !defined(AFX_INPUTDLG_DEMO_H__B3B44934_E452_4A33_A5CC_104E87AC4255__INCLUDED_)
#define AFX_INPUTDLG_DEMO_H__B3B44934_E452_4A33_A5CC_104E87AC4255__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CInputDlg_DemoApp:
// See InputDlg_Demo.cpp for the implementation of this class
//

class CInputDlg_DemoApp : public CWinApp
{
public:
	CInputDlg_DemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInputDlg_DemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CInputDlg_DemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INPUTDLG_DEMO_H__B3B44934_E452_4A33_A5CC_104E87AC4255__INCLUDED_)
