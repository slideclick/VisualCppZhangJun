// EditDemo.h : main header file for the EDITDEMO application
//

#if !defined(AFX_EDITDEMO_H__DCA25478_88B4_4A01_9C06_5F8E24908C1B__INCLUDED_)
#define AFX_EDITDEMO_H__DCA25478_88B4_4A01_9C06_5F8E24908C1B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CEditDemoApp:
// See EditDemo.cpp for the implementation of this class
//

class CEditDemoApp : public CWinApp
{
public:
	CEditDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEditDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITDEMO_H__DCA25478_88B4_4A01_9C06_5F8E24908C1B__INCLUDED_)
