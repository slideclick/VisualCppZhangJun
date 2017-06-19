// ComboBoxDemoDlg.h : header file
//

#if !defined(AFX_COMBOBOXDEMODLG_H__A54D111F_13F9_4EB9_9FCD_BEEDCF3080A0__INCLUDED_)
#define AFX_COMBOBOXDEMODLG_H__A54D111F_13F9_4EB9_9FCD_BEEDCF3080A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CComboBoxDemoDlg dialog

class CComboBoxDemoDlg : public CDialog
{
// Construction
public:
	CComboBoxDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CComboBoxDemoDlg)
	enum { IDD = IDD_COMBOBOXDEMO_DIALOG };
	CListBox	m_lst_demo;
	CComboBox	m_cmb_demo;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComboBoxDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CComboBoxDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnAdd();
	afx_msg void OnBtnDelete();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMBOBOXDEMODLG_H__A54D111F_13F9_4EB9_9FCD_BEEDCF3080A0__INCLUDED_)
