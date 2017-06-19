// TreeCtrlDemo.h : main header file for the TREECTRLDEMO application
//

#if !defined(AFX_TREECTRLDEMO_H__DD4914EA_F129_4687_8C26_E31971A9AA10__INCLUDED_)
#define AFX_TREECTRLDEMO_H__DD4914EA_F129_4687_8C26_E31971A9AA10__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTreeCtrlDemoApp:
// See TreeCtrlDemo.cpp for the implementation of this class
//

class CTreeCtrlDemoApp : public CWinApp
{
public:
	CTreeCtrlDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTreeCtrlDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTreeCtrlDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TREECTRLDEMO_H__DD4914EA_F129_4687_8C26_E31971A9AA10__INCLUDED_)
