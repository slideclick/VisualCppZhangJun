// LockMouse.h : main header file for the LOCKMOUSE application
//

#if !defined(AFX_LOCKMOUSE_H__1125EB4A_673A_4F9B_92C4_BFACB957E950__INCLUDED_)
#define AFX_LOCKMOUSE_H__1125EB4A_673A_4F9B_92C4_BFACB957E950__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CLockMouseApp:
// See LockMouse.cpp for the implementation of this class
//

class CLockMouseApp : public CWinApp
{
public:
	CLockMouseApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLockMouseApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CLockMouseApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOCKMOUSE_H__1125EB4A_673A_4F9B_92C4_BFACB957E950__INCLUDED_)
