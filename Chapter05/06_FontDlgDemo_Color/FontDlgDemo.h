// FontDlgDemo.h : main header file for the FONTDLGDEMO application
//

#if !defined(AFX_FONTDLGDEMO_H__38DE4DD4_E73E_488F_A4DF_A2A0282FF246__INCLUDED_)
#define AFX_FONTDLGDEMO_H__38DE4DD4_E73E_488F_A4DF_A2A0282FF246__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CFontDlgDemoApp:
// See FontDlgDemo.cpp for the implementation of this class
//

class CFontDlgDemoApp : public CWinApp
{
public:
	CFontDlgDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFontDlgDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CFontDlgDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FONTDLGDEMO_H__38DE4DD4_E73E_488F_A4DF_A2A0282FF246__INCLUDED_)
