// BinData.h : main header file for the BINDATA application
//

#if !defined(AFX_BINDATA_H__DA84A169_9844_4CE9_B9A8_E32E90BFB9AE__INCLUDED_)
#define AFX_BINDATA_H__DA84A169_9844_4CE9_B9A8_E32E90BFB9AE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CBinDataApp:
// See BinData.cpp for the implementation of this class
//

class CBinDataApp : public CWinApp
{
public:
	CBinDataApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBinDataApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CBinDataApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BINDATA_H__DA84A169_9844_4CE9_B9A8_E32E90BFB9AE__INCLUDED_)
