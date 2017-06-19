// SliderDemo.h : main header file for the SLIDERDEMO application
//

#if !defined(AFX_SLIDERDEMO_H__D3E2F0E0_8365_422A_91EB_C893D55F6220__INCLUDED_)
#define AFX_SLIDERDEMO_H__D3E2F0E0_8365_422A_91EB_C893D55F6220__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSliderDemoApp:
// See SliderDemo.cpp for the implementation of this class
//

class CSliderDemoApp : public CWinApp
{
public:
	CSliderDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSliderDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSliderDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SLIDERDEMO_H__D3E2F0E0_8365_422A_91EB_C893D55F6220__INCLUDED_)
