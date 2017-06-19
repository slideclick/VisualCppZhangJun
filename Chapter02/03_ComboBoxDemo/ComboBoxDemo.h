// ComboBoxDemo.h : main header file for the COMBOBOXDEMO application
//

#if !defined(AFX_COMBOBOXDEMO_H__0751F801_97A8_4444_8119_B0E1F7CFB5CE__INCLUDED_)
#define AFX_COMBOBOXDEMO_H__0751F801_97A8_4444_8119_B0E1F7CFB5CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CComboBoxDemoApp:
// See ComboBoxDemo.cpp for the implementation of this class
//

class CComboBoxDemoApp : public CWinApp
{
public:
	CComboBoxDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComboBoxDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CComboBoxDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMBOBOXDEMO_H__0751F801_97A8_4444_8119_B0E1F7CFB5CE__INCLUDED_)
