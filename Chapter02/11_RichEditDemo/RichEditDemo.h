// RichEditDemo.h : main header file for the RICHEDITDEMO application
//

#if !defined(AFX_RICHEDITDEMO_H__27DCF33D_B642_4712_BBA6_927F79440547__INCLUDED_)
#define AFX_RICHEDITDEMO_H__27DCF33D_B642_4712_BBA6_927F79440547__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CRichEditDemoApp:
// See RichEditDemo.cpp for the implementation of this class
//

class CRichEditDemoApp : public CWinApp
{
public:
	CRichEditDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRichEditDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CRichEditDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RICHEDITDEMO_H__27DCF33D_B642_4712_BBA6_927F79440547__INCLUDED_)
