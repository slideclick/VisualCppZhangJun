// AnimateDemoDlg.h : header file
//

#if !defined(AFX_ANIMATEDEMODLG_H__A56D2561_34DB_4C46_9742_AF9FC83DE666__INCLUDED_)
#define AFX_ANIMATEDEMODLG_H__A56D2561_34DB_4C46_9742_AF9FC83DE666__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CAnimateDemoDlg dialog

class CAnimateDemoDlg : public CDialog
{
// Construction
public:
	CAnimateDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CAnimateDemoDlg)
	enum { IDD = IDD_ANIMATEDEMO_DIALOG };
	CAnimateCtrl	m_animate;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAnimateDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CAnimateDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnBrowse();
	afx_msg void OnBtnPlayfile();
	afx_msg void OnBtnPlayres();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANIMATEDEMODLG_H__A56D2561_34DB_4C46_9742_AF9FC83DE666__INCLUDED_)
