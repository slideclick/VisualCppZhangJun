// TabCtrlDemo.h : main header file for the TABCTRLDEMO application
//

#if !defined(AFX_TABCTRLDEMO_H__2A87FF1E_AC61_4DD4_A13F_F6326A5EDE28__INCLUDED_)
#define AFX_TABCTRLDEMO_H__2A87FF1E_AC61_4DD4_A13F_F6326A5EDE28__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTabCtrlDemoApp:
// See TabCtrlDemo.cpp for the implementation of this class
//

class CTabCtrlDemoApp : public CWinApp
{
public:
	CTabCtrlDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabCtrlDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTabCtrlDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABCTRLDEMO_H__2A87FF1E_AC61_4DD4_A13F_F6326A5EDE28__INCLUDED_)
