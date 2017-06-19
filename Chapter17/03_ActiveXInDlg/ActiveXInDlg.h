// ActiveXInDlg.h : main header file for the ACTIVEXINDLG application
//

#if !defined(AFX_ACTIVEXINDLG_H__48C67B65_4595_43FD_B091_8A6E6B85E1BD__INCLUDED_)
#define AFX_ACTIVEXINDLG_H__48C67B65_4595_43FD_B091_8A6E6B85E1BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CActiveXInDlgApp:
// See ActiveXInDlg.cpp for the implementation of this class
//

class CActiveXInDlgApp : public CWinApp
{
public:
	CActiveXInDlgApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CActiveXInDlgApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CActiveXInDlgApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ACTIVEXINDLG_H__48C67B65_4595_43FD_B091_8A6E6B85E1BD__INCLUDED_)
