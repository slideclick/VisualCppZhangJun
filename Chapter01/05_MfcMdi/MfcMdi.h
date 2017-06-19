// MfcMdi.h : main header file for the MFCMDI application
//

#if !defined(AFX_MFCMDI_H__1EA556F3_86BC_4C61_90CD_09E9F550EF12__INCLUDED_)
#define AFX_MFCMDI_H__1EA556F3_86BC_4C61_90CD_09E9F550EF12__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMfcMdiApp:
// See MfcMdi.cpp for the implementation of this class
//

class CMfcMdiApp : public CWinApp
{
public:
	CMfcMdiApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMfcMdiApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMfcMdiApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCMDI_H__1EA556F3_86BC_4C61_90CD_09E9F550EF12__INCLUDED_)
