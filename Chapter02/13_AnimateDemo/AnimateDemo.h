// AnimateDemo.h : main header file for the ANIMATEDEMO application
//

#if !defined(AFX_ANIMATEDEMO_H__155B21EF_F343_4945_A1F8_00449C9CE767__INCLUDED_)
#define AFX_ANIMATEDEMO_H__155B21EF_F343_4945_A1F8_00449C9CE767__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CAnimateDemoApp:
// See AnimateDemo.cpp for the implementation of this class
//

class CAnimateDemoApp : public CWinApp
{
public:
	CAnimateDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAnimateDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CAnimateDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANIMATEDEMO_H__155B21EF_F343_4945_A1F8_00449C9CE767__INCLUDED_)
