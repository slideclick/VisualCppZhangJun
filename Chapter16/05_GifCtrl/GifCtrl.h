// GifCtrl.h : main header file for the GIFCTRL application
//

#if !defined(AFX_GIFCTRL_H__B893955D_384B_4721_9854_D0C57D6388F7__INCLUDED_)
#define AFX_GIFCTRL_H__B893955D_384B_4721_9854_D0C57D6388F7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CGifCtrlApp:
// See GifCtrl.cpp for the implementation of this class
//

class CGifCtrlApp : public CWinApp
{
public:
	CGifCtrlApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGifCtrlApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CGifCtrlApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GIFCTRL_H__B893955D_384B_4721_9854_D0C57D6388F7__INCLUDED_)
