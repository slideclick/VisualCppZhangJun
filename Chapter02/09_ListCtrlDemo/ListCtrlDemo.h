// ListCtrlDemo.h : main header file for the LISTCTRLDEMO application
//

#if !defined(AFX_LISTCTRLDEMO_H__4C479563_FB63_4952_8780_F873DD5A75BD__INCLUDED_)
#define AFX_LISTCTRLDEMO_H__4C479563_FB63_4952_8780_F873DD5A75BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CListCtrlDemoApp:
// See ListCtrlDemo.cpp for the implementation of this class
//

class CListCtrlDemoApp : public CWinApp
{
public:
	CListCtrlDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListCtrlDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CListCtrlDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTCTRLDEMO_H__4C479563_FB63_4952_8780_F873DD5A75BD__INCLUDED_)
