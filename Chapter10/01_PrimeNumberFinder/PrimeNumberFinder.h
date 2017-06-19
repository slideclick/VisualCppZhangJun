// PrimeNumberFinder.h : main header file for the PRIMENUMBERFINDER application
//

#if !defined(AFX_PRIMENUMBERFINDER_H__BB87DAD5_46E8_4AC3_8B8E_3B6F15DEBE69__INCLUDED_)
#define AFX_PRIMENUMBERFINDER_H__BB87DAD5_46E8_4AC3_8B8E_3B6F15DEBE69__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CPrimeNumberFinderApp:
// See PrimeNumberFinder.cpp for the implementation of this class
//

class CPrimeNumberFinderApp : public CWinApp
{
public:
	CPrimeNumberFinderApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrimeNumberFinderApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPrimeNumberFinderApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRIMENUMBERFINDER_H__BB87DAD5_46E8_4AC3_8B8E_3B6F15DEBE69__INCLUDED_)
