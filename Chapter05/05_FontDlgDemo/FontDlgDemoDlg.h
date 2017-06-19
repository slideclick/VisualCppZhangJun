// FontDlgDemoDlg.h : header file
//

#if !defined(AFX_FONTDLGDEMODLG_H__540D72C9_4FD7_4866_A3D0_9806857F1DEB__INCLUDED_)
#define AFX_FONTDLGDEMODLG_H__540D72C9_4FD7_4866_A3D0_9806857F1DEB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CFontDlgDemoDlg dialog

class CFontDlgDemoDlg : public CDialog
{
// Construction
public:
	CFontDlgDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CFontDlgDemoDlg)
	enum { IDD = IDD_FONTDLGDEMO_DIALOG };
	CRichEditCtrl	m_edtContent;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFontDlgDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CFontDlgDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FONTDLGDEMODLG_H__540D72C9_4FD7_4866_A3D0_9806857F1DEB__INCLUDED_)
