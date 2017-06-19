// ScrollBarDemoDlg.h : header file
//

#if !defined(AFX_SCROLLBARDEMODLG_H__2986DF00_43DC_4537_B924_FF3CA37BE31C__INCLUDED_)
#define AFX_SCROLLBARDEMODLG_H__2986DF00_43DC_4537_B924_FF3CA37BE31C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CScrollBarDemoDlg dialog

class CScrollBarDemoDlg : public CDialog
{
// Construction
public:
	CScrollBarDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CScrollBarDemoDlg)
	enum { IDD = IDD_SCROLLBARDEMO_DIALOG };
	CScrollBar	m_scroll;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScrollBarDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CScrollBarDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCROLLBARDEMODLG_H__2986DF00_43DC_4537_B924_FF3CA37BE31C__INCLUDED_)
