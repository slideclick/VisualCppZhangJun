// MouseMoving.h : main header file for the MOUSEMOVING application
//

#if !defined(AFX_MOUSEMOVING_H__72E812D9_76F0_499E_B915_5F483847B30A__INCLUDED_)
#define AFX_MOUSEMOVING_H__72E812D9_76F0_499E_B915_5F483847B30A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMouseMovingApp:
// See MouseMoving.cpp for the implementation of this class
//

class CMouseMovingApp : public CWinApp
{
public:
	CMouseMovingApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMouseMovingApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMouseMovingApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOUSEMOVING_H__72E812D9_76F0_499E_B915_5F483847B30A__INCLUDED_)
