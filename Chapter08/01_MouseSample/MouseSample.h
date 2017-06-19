// MouseSample.h : main header file for the MOUSESAMPLE application
//

#if !defined(AFX_MOUSESAMPLE_H__FFBF447B_5AB2_47B5_B249_6833B0B6FCBC__INCLUDED_)
#define AFX_MOUSESAMPLE_H__FFBF447B_5AB2_47B5_B249_6833B0B6FCBC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMouseSampleApp:
// See MouseSample.cpp for the implementation of this class
//

class CMouseSampleApp : public CWinApp
{
public:
	CMouseSampleApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMouseSampleApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMouseSampleApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOUSESAMPLE_H__FFBF447B_5AB2_47B5_B249_6833B0B6FCBC__INCLUDED_)
