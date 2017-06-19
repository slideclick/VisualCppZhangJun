// NCMsg.h : main header file for the NCMSG application
//

#if !defined(AFX_NCMSG_H__591010C7_7A10_4ACF_996D_978F8509DFED__INCLUDED_)
#define AFX_NCMSG_H__591010C7_7A10_4ACF_996D_978F8509DFED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CNCMsgApp:
// See NCMsg.cpp for the implementation of this class
//

class CNCMsgApp : public CWinApp
{
public:
	CNCMsgApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNCMsgApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CNCMsgApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NCMSG_H__591010C7_7A10_4ACF_996D_978F8509DFED__INCLUDED_)
