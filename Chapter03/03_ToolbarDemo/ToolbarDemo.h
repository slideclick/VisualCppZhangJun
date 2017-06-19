// ToolbarDemo.h : main header file for the TOOLBARDEMO application
//

#if !defined(AFX_TOOLBARDEMO_H__B943ECBB_E3F8_4798_932B_5DB55457492E__INCLUDED_)
#define AFX_TOOLBARDEMO_H__B943ECBB_E3F8_4798_932B_5DB55457492E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CToolbarDemoApp:
// See ToolbarDemo.cpp for the implementation of this class
//

class CToolbarDemoApp : public CWinApp
{
public:
	CToolbarDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolbarDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CToolbarDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOOLBARDEMO_H__B943ECBB_E3F8_4798_932B_5DB55457492E__INCLUDED_)
