// ListCtrlDemoDlg.h : header file
//

#if !defined(AFX_LISTCTRLDEMODLG_H__60A0B5F9_1BF6_4774_9D9F_D5AA175B40E8__INCLUDED_)
#define AFX_LISTCTRLDEMODLG_H__60A0B5F9_1BF6_4774_9D9F_D5AA175B40E8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CListCtrlDemoDlg dialog

class CListCtrlDemoDlg : public CDialog
{
// Construction
public:
	CListCtrlDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CListCtrlDemoDlg)
	enum { IDD = IDD_LISTCTRLDEMO_DIALOG };
	CListCtrl	m_list;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListCtrlDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CImageList m_images;
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CListCtrlDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnAdd();
	afx_msg void OnBtnDelete();
	afx_msg void OnSelchangeCmbView();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTCTRLDEMODLG_H__60A0B5F9_1BF6_4774_9D9F_D5AA175B40E8__INCLUDED_)
