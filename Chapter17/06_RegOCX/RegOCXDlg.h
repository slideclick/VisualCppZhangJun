// RegOCXDlg.h : header file
//

#if !defined(AFX_REGOCXDLG_H__9A858488_4E08_44CB_9D1A_70CB9B75B9E9__INCLUDED_)
#define AFX_REGOCXDLG_H__9A858488_4E08_44CB_9D1A_70CB9B75B9E9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CRegOCXDlg dialog

class CRegOCXDlg : public CDialog
{
// Construction
public:
	CRegOCXDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CRegOCXDlg)
	enum { IDD = IDD_REGOCX_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRegOCXDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL RegProc(BOOL bReg);
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CRegOCXDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnBrowse();
	afx_msg void OnBtnReg();
	afx_msg void OnBtnUnreg();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REGOCXDLG_H__9A858488_4E08_44CB_9D1A_70CB9B75B9E9__INCLUDED_)
