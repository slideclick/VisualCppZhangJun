// BigPrimeNumber.h : main header file for the BIGPRIMENUMBER application
//

#if !defined(AFX_BIGPRIMENUMBER_H__3623BB84_AF92_4ED9_9AA1_F4E67EE76373__INCLUDED_)
#define AFX_BIGPRIMENUMBER_H__3623BB84_AF92_4ED9_9AA1_F4E67EE76373__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CBigPrimeNumberApp:
// See BigPrimeNumber.cpp for the implementation of this class
//

class CBigPrimeNumberApp : public CWinApp
{
public:
	CBigPrimeNumberApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBigPrimeNumberApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CBigPrimeNumberApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BIGPRIMENUMBER_H__3623BB84_AF92_4ED9_9AA1_F4E67EE76373__INCLUDED_)
