// FlashWnd.h : main header file for the FLASHWND application
//

#if !defined(AFX_FLASHWND_H__811B1E63_D0E1_4FFE_895A_562D326B00EC__INCLUDED_)
#define AFX_FLASHWND_H__811B1E63_D0E1_4FFE_895A_562D326B00EC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CFlashWndApp:
// See FlashWnd.cpp for the implementation of this class
//

class CFlashWndApp : public CWinApp
{
public:
	CFlashWndApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFlashWndApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CFlashWndApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FLASHWND_H__811B1E63_D0E1_4FFE_895A_562D326B00EC__INCLUDED_)
