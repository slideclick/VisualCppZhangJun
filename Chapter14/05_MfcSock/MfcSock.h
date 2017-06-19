// MfcSock.h : main header file for the MFCSOCK application
//

#if !defined(AFX_MFCSOCK_H__2D6A368A_DFA3_4C88_84A2_E1194B0857C7__INCLUDED_)
#define AFX_MFCSOCK_H__2D6A368A_DFA3_4C88_84A2_E1194B0857C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMfcSockApp:
// See MfcSock.cpp for the implementation of this class
//

class CMfcSockApp : public CWinApp
{
public:
	CMfcSockApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMfcSockApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMfcSockApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCSOCK_H__2D6A368A_DFA3_4C88_84A2_E1194B0857C7__INCLUDED_)
