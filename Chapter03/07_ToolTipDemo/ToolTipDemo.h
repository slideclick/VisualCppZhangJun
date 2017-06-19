// ToolTipDemo.h : main header file for the TOOLTIPDEMO application
//

#if !defined(AFX_TOOLTIPDEMO_H__5F668A36_8AF2_440F_BF69_43B1E985FEFB__INCLUDED_)
#define AFX_TOOLTIPDEMO_H__5F668A36_8AF2_440F_BF69_43B1E985FEFB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CToolTipDemoApp:
// See ToolTipDemo.cpp for the implementation of this class
//

class CToolTipDemoApp : public CWinApp
{
public:
	CToolTipDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolTipDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CToolTipDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOOLTIPDEMO_H__5F668A36_8AF2_440F_BF69_43B1E985FEFB__INCLUDED_)
