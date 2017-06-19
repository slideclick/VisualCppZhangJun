// IPCtrlDemo.h : main header file for the IPCTRLDEMO application
//

#if !defined(AFX_IPCTRLDEMO_H__A50AD279_34D0_45B5_B24F_B761151243A7__INCLUDED_)
#define AFX_IPCTRLDEMO_H__A50AD279_34D0_45B5_B24F_B761151243A7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CIPCtrlDemoApp:
// See IPCtrlDemo.cpp for the implementation of this class
//

class CIPCtrlDemoApp : public CWinApp
{
public:
	CIPCtrlDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIPCtrlDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CIPCtrlDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IPCTRLDEMO_H__A50AD279_34D0_45B5_B24F_B761151243A7__INCLUDED_)
