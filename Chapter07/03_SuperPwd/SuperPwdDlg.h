// SuperPwdDlg.h : header file
//

#if !defined(AFX_SUPERPWDDLG_H__DD00C04D_1ABA_4FA5_B463_76BEEBA81A62__INCLUDED_)
#define AFX_SUPERPWDDLG_H__DD00C04D_1ABA_4FA5_B463_76BEEBA81A62__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSuperPwdDlg dialog

class CSuperPwdDlg : public CDialog
{
// Construction
public:
	CSuperPwdDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSuperPwdDlg)
	enum { IDD = IDD_SUPERPWD_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSuperPwdDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	UINT m_nSeed;
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSuperPwdDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SUPERPWDDLG_H__DD00C04D_1ABA_4FA5_B463_76BEEBA81A62__INCLUDED_)
