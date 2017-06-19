// TreeCtrlDemoDlg.h : header file
//

#if !defined(AFX_TREECTRLDEMODLG_H__EF9B3254_8AF3_4523_83A0_9166E3EED937__INCLUDED_)
#define AFX_TREECTRLDEMODLG_H__EF9B3254_8AF3_4523_83A0_9166E3EED937__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTreeCtrlDemoDlg dialog

class CTreeCtrlDemoDlg : public CDialog
{
// Construction
public:
	CTreeCtrlDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTreeCtrlDemoDlg)
	enum { IDD = IDD_TREECTRLDEMO_DIALOG };
	CTreeCtrl	m_tree;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTreeCtrlDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTreeCtrlDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnAdd();
	afx_msg void OnBtnDelete();
	afx_msg void OnBtnEdit();
	afx_msg void OnSelchangedTree(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TREECTRLDEMODLG_H__EF9B3254_8AF3_4523_83A0_9166E3EED937__INCLUDED_)
