// OpenFileDemoDlg.h : header file
//

#if !defined(AFX_OPENFILEDEMODLG_H__97165ED3_CA64_414C_84A3_06932E38CCBB__INCLUDED_)
#define AFX_OPENFILEDEMODLG_H__97165ED3_CA64_414C_84A3_06932E38CCBB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// COpenFileDemoDlg dialog

class COpenFileDemoDlg : public CDialog
{
// Construction
public:
	COpenFileDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(COpenFileDemoDlg)
	enum { IDD = IDD_OPENFILEDEMO_DIALOG };
	CButton	m_chkMultiSel;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COpenFileDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(COpenFileDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnBtnMfc();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPENFILEDEMODLG_H__97165ED3_CA64_414C_84A3_06932E38CCBB__INCLUDED_)
