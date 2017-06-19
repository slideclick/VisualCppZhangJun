// PreviewFileDlg_DemoDlg.h : header file
//

#if !defined(AFX_PREVIEWFILEDLG_DEMODLG_H__A2D7E304_1734_4E0D_A515_A5491E309BB9__INCLUDED_)
#define AFX_PREVIEWFILEDLG_DEMODLG_H__A2D7E304_1734_4E0D_A515_A5491E309BB9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CPreviewFileDlg_DemoDlg dialog

class CPreviewFileDlg_DemoDlg : public CDialog
{
// Construction
public:
	CPreviewFileDlg_DemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CPreviewFileDlg_DemoDlg)
	enum { IDD = IDD_PREVIEWFILEDLG_DEMO_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPreviewFileDlg_DemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CPreviewFileDlg_DemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PREVIEWFILEDLG_DEMODLG_H__A2D7E304_1734_4E0D_A515_A5491E309BB9__INCLUDED_)
