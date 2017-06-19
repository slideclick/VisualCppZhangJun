// MsgInMfc.h : main header file for the MSGINMFC application
//

#if !defined(AFX_MSGINMFC_H__90AAEBE8_BF2A_4200_B806_2471E240E78B__INCLUDED_)
#define AFX_MSGINMFC_H__90AAEBE8_BF2A_4200_B806_2471E240E78B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMsgInMfcApp:
// See MsgInMfc.cpp for the implementation of this class
//

class CMsgInMfcApp : public CWinApp
{
public:
	CMsgInMfcApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMsgInMfcApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMsgInMfcApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSGINMFC_H__90AAEBE8_BF2A_4200_B806_2471E240E78B__INCLUDED_)
