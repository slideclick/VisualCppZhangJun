// Recorder.h : main header file for the RECORDER application
//

#if !defined(AFX_RECORDER_H__1F9ECFD0_6A8B_40B1_9EE6_32D7EE770F50__INCLUDED_)
#define AFX_RECORDER_H__1F9ECFD0_6A8B_40B1_9EE6_32D7EE770F50__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CRecorderApp:
// See Recorder.cpp for the implementation of this class
//

class CRecorderApp : public CWinApp
{
public:
	CRecorderApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRecorderApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CRecorderApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECORDER_H__1F9ECFD0_6A8B_40B1_9EE6_32D7EE770F50__INCLUDED_)
