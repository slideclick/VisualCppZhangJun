// TopMostWnd.h : main header file for the TOPMOSTWND application
//

#if !defined(AFX_TOPMOSTWND_H__A4C4AD9E_FB82_4DFA_8573_E6ADB25E6CC1__INCLUDED_)
#define AFX_TOPMOSTWND_H__A4C4AD9E_FB82_4DFA_8573_E6ADB25E6CC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTopMostWndApp:
// See TopMostWnd.cpp for the implementation of this class
//

class CTopMostWndApp : public CWinApp
{
public:
	CTopMostWndApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTopMostWndApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTopMostWndApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOPMOSTWND_H__A4C4AD9E_FB82_4DFA_8573_E6ADB25E6CC1__INCLUDED_)
