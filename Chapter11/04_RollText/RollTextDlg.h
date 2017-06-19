// RollTextDlg.h : header file
//

#if !defined(AFX_ROLLTEXTDLG_H__8CBF9AD4_DCFF_4F0B_AE70_17A337111E6F__INCLUDED_)
#define AFX_ROLLTEXTDLG_H__8CBF9AD4_DCFF_4F0B_AE70_17A337111E6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CRollTextDlg dialog

class CRollTextDlg : public CDialog
{
// Construction
public:
	CRollTextDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CRollTextDlg)
	enum { IDD = IDD_ROLLTEXT_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRollTextDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CFont m_font;
	COLORREF m_crText;
	COLORREF m_crBk;
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CRollTextDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnBtnColor();
	afx_msg void OnBtnBk();
	afx_msg void OnBtnFont();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROLLTEXTDLG_H__8CBF9AD4_DCFF_4F0B_AE70_17A337111E6F__INCLUDED_)
