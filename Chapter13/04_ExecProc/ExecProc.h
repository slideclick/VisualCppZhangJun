// ExecProc.h : main header file for the EXECPROC application
//

#if !defined(AFX_EXECPROC_H__D99EF002_9D76_4C3A_8C2E_2EB39B55B4B4__INCLUDED_)
#define AFX_EXECPROC_H__D99EF002_9D76_4C3A_8C2E_2EB39B55B4B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CExecProcApp:
// See ExecProc.cpp for the implementation of this class
//

class CExecProcApp : public CWinApp
{
public:
	CExecProcApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExecProcApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CExecProcApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXECPROC_H__D99EF002_9D76_4C3A_8C2E_2EB39B55B4B4__INCLUDED_)
