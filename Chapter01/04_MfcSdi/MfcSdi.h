// MfcSdi.h : main header file for the MFCSDI application
//

#if !defined(AFX_MFCSDI_H__1867F570_95B2_4C52_B349_5735F9CCB57D__INCLUDED_)
#define AFX_MFCSDI_H__1867F570_95B2_4C52_B349_5735F9CCB57D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMfcSdiApp:
// See MfcSdi.cpp for the implementation of this class
//

class CMfcSdiApp : public CWinApp
{
public:
	CMfcSdiApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMfcSdiApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMfcSdiApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCSDI_H__1867F570_95B2_4C52_B349_5735F9CCB57D__INCLUDED_)
