// MsgDest.h : main header file for the MSGDEST application
//

#if !defined(AFX_MSGDEST_H__5448447B_B7F3_443A_801A_1F85F36A107B__INCLUDED_)
#define AFX_MSGDEST_H__5448447B_B7F3_443A_801A_1F85F36A107B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMsgDestApp:
// See MsgDest.cpp for the implementation of this class
//

class CMsgDestApp : public CWinApp
{
public:
	CMsgDestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMsgDestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMsgDestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSGDEST_H__5448447B_B7F3_443A_801A_1F85F36A107B__INCLUDED_)
