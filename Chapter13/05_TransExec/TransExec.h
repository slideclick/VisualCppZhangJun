// TransExec.h : main header file for the TRANSEXEC application
//

#if !defined(AFX_TRANSEXEC_H__6225D990_5E57_4904_B1A6_B24685EFCAB7__INCLUDED_)
#define AFX_TRANSEXEC_H__6225D990_5E57_4904_B1A6_B24685EFCAB7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTransExecApp:
// See TransExec.cpp for the implementation of this class
//

class CTransExecApp : public CWinApp
{
public:
	CTransExecApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTransExecApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTransExecApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRANSEXEC_H__6225D990_5E57_4904_B1A6_B24685EFCAB7__INCLUDED_)
