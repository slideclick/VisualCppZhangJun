// CheckBoxDemoDlg.h : header file
//

#if !defined(AFX_CHECKBOXDEMODLG_H__E5A1BDFA_4738_4863_BFBF_1DC54F814216__INCLUDED_)
#define AFX_CHECKBOXDEMODLG_H__E5A1BDFA_4738_4863_BFBF_1DC54F814216__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCheckBoxDemoDlg dialog

class CCheckBoxDemoDlg : public CDialog
{
// Construction
public:
	CCheckBoxDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCheckBoxDemoDlg)
	enum { IDD = IDD_CHECKBOXDEMO_DIALOG };
	CButton	m_rd_round;
	CButton	m_rd_rect;
	CButton	m_chk_red;
	CButton	m_chk_green;
	CButton	m_chk_blue;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCheckBoxDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCheckBoxDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnChkBlue();
	afx_msg void OnChkGreen();
	afx_msg void OnChkRed();
	afx_msg void OnRdRect();
	afx_msg void OnRdRound();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHECKBOXDEMODLG_H__E5A1BDFA_4738_4863_BFBF_1DC54F814216__INCLUDED_)
