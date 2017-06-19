// MyRealDlg.h : header file
//
//{{AFX_INCLUDES()
#include "realaudio.h"
//}}AFX_INCLUDES

#if !defined(AFX_MYREALDLG_H__5C9CABFB_A18C_48E8_8E83_69099DD235DE__INCLUDED_)
#define AFX_MYREALDLG_H__5C9CABFB_A18C_48E8_8E83_69099DD235DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMyRealDlg dialog

class CMyRealDlg : public CDialog
{
// Construction
public:
	CMyRealDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMyRealDlg)
	enum { IDD = IDD_MYREAL_DIALOG };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyRealDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CRealAudio *m_pReal;
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMyRealDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYREALDLG_H__5C9CABFB_A18C_48E8_8E83_69099DD235DE__INCLUDED_)
