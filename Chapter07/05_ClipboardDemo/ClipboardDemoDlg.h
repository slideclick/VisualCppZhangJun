// ClipboardDemoDlg.h : header file
//

#if !defined(AFX_CLIPBOARDDEMODLG_H__672033EB_3E96_43BB_946F_05AF00E4BA1C__INCLUDED_)
#define AFX_CLIPBOARDDEMODLG_H__672033EB_3E96_43BB_946F_05AF00E4BA1C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CClipboardDemoDlg dialog

class CClipboardDemoDlg : public CDialog
{
// Construction
public:
	CClipboardDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CClipboardDemoDlg)
	enum { IDD = IDD_CLIPBOARDDEMO_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClipboardDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CClipboardDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnSet();
	afx_msg void OnBtnGet();
	afx_msg void OnBtnEmpty();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIPBOARDDEMODLG_H__672033EB_3E96_43BB_946F_05AF00E4BA1C__INCLUDED_)
