// MsgSrc.h : main header file for the MSGSRC application
//

#if !defined(AFX_MSGSRC_H__42AEA48C_9741_42C0_91DA_6F4A609FC57E__INCLUDED_)
#define AFX_MSGSRC_H__42AEA48C_9741_42C0_91DA_6F4A609FC57E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMsgSrcApp:
// See MsgSrc.cpp for the implementation of this class
//

class CMsgSrcApp : public CWinApp
{
public:
	CMsgSrcApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMsgSrcApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMsgSrcApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSGSRC_H__42AEA48C_9741_42C0_91DA_6F4A609FC57E__INCLUDED_)
