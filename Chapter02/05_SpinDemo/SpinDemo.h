// SpinDemo.h : main header file for the SPINDEMO application
//

#if !defined(AFX_SPINDEMO_H__8BCCB29D_C48A_48F5_8DA4_11DA1D983C4A__INCLUDED_)
#define AFX_SPINDEMO_H__8BCCB29D_C48A_48F5_8DA4_11DA1D983C4A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSpinDemoApp:
// See SpinDemo.cpp for the implementation of this class
//

class CSpinDemoApp : public CWinApp
{
public:
	CSpinDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpinDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSpinDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPINDEMO_H__8BCCB29D_C48A_48F5_8DA4_11DA1D983C4A__INCLUDED_)
