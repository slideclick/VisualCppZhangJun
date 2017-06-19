// CalendarDemo.h : main header file for the CALENDARDEMO application
//

#if !defined(AFX_CALENDARDEMO_H__2304E561_FF38_4504_A5A0_34545393DB58__INCLUDED_)
#define AFX_CALENDARDEMO_H__2304E561_FF38_4504_A5A0_34545393DB58__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCalendarDemoApp:
// See CalendarDemo.cpp for the implementation of this class
//

class CCalendarDemoApp : public CWinApp
{
public:
	CCalendarDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCalendarDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCalendarDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALENDARDEMO_H__2304E561_FF38_4504_A5A0_34545393DB58__INCLUDED_)
