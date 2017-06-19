// MenuDemo.h : main header file for the MENUDEMO application
//

#if !defined(AFX_MENUDEMO_H__6F68EF31_53C0_4B19_8843_7C1FDF10CE81__INCLUDED_)
#define AFX_MENUDEMO_H__6F68EF31_53C0_4B19_8843_7C1FDF10CE81__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMenuDemoApp:
// See MenuDemo.cpp for the implementation of this class
//

class CMenuDemoApp : public CWinApp
{
public:
	CMenuDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMenuDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMenuDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MENUDEMO_H__6F68EF31_53C0_4B19_8843_7C1FDF10CE81__INCLUDED_)
