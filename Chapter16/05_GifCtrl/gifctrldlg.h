// GifCtrlDlg.h : header file
//

#if !defined(AFX_GIFCTRLDLG_H__A989F34D_1F7E_4B94_A71A_5B1A6DBF0390__INCLUDED_)
#define AFX_GIFCTRLDLG_H__A989F34D_1F7E_4B94_A71A_5B1A6DBF0390__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\comm\pictureex.h"

/////////////////////////////////////////////////////////////////////////////
// CGifCtrlDlg dialog

class CGifCtrlDlg : public CDialog
{
// Construction
public:
	CGifCtrlDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CGifCtrlDlg)
	enum { IDD = IDD_GIFCTRL_DIALOG };
	CComboBox	m_cmb_vmode;
	CComboBox	m_cmb_hmode;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGifCtrlDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CPictureEx m_pic;
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CGifCtrlDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnBrowse();
	afx_msg void OnBtnSet();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GIFCTRLDLG_H__A989F34D_1F7E_4B94_A71A_5B1A6DBF0390__INCLUDED_)
