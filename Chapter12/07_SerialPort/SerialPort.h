// SerialPort.h : main header file for the SERIALPORT application
//

#if !defined(AFX_SERIALPORT_H__26591E57_BEE2_4462_997D_7348CA0368A9__INCLUDED_)
#define AFX_SERIALPORT_H__26591E57_BEE2_4462_997D_7348CA0368A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSerialPortApp:
// See SerialPort.cpp for the implementation of this class
//

class CSerialPortApp : public CWinApp
{
public:
	CSerialPortApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSerialPortApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSerialPortApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERIALPORT_H__26591E57_BEE2_4462_997D_7348CA0368A9__INCLUDED_)
