// MultiLanguage.h : main header file for the MULTILANGUAGE application
//

#if !defined(AFX_MULTILANGUAGE_H__2F4440F9_396B_4BCF_B827_4540E1B3C298__INCLUDED_)
#define AFX_MULTILANGUAGE_H__2F4440F9_396B_4BCF_B827_4540E1B3C298__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMultiLanguageApp:
// See MultiLanguage.cpp for the implementation of this class
//

class CMultiLanguageApp : public CWinApp
{
public:
	CMultiLanguageApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMultiLanguageApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMultiLanguageApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MULTILANGUAGE_H__2F4440F9_396B_4BCF_B827_4540E1B3C298__INCLUDED_)
