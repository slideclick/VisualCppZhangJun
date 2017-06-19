// SerialPortDlg.h : header file
//

#if !defined(AFX_SERIALPORTDLG_H__8E6830FF_851F_4BB0_B2BE_D5C8A2B888EA__INCLUDED_)
#define AFX_SERIALPORTDLG_H__8E6830FF_851F_4BB0_B2BE_D5C8A2B888EA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\comm\mycom.h"
/////////////////////////////////////////////////////////////////////////////
// CSerialPortDlg dialog

class CSerialPortDlg : public CDialog
{
// Construction
public:
	CSerialPortDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSerialPortDlg)
	enum { IDD = IDD_SERIALPORT_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSerialPortDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CMyCom m_com;
	afx_msg void OnCommNotify(WPARAM wp, LPARAM lp);
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSerialPortDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnWrite();
	afx_msg void OnDestroy();
	afx_msg void OnBtnOpen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERIALPORTDLG_H__8E6830FF_851F_4BB0_B2BE_D5C8A2B888EA__INCLUDED_)
