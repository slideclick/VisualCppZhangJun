// MyWebProtocolDlg.h : header file
//

#if !defined(AFX_MYWEBPROTOCOLDLG_H__693D05DE_E415_4416_AFC7_68E4092D190C__INCLUDED_)
#define AFX_MYWEBPROTOCOLDLG_H__693D05DE_E415_4416_AFC7_68E4092D190C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMyWebProtocolDlg dialog

class CMyWebProtocolDlg : public CDialog
{
// Construction
public:
	CMyWebProtocolDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMyWebProtocolDlg)
	enum { IDD = IDD_MYWEBPROTOCOL_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyWebProtocolDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMyWebProtocolDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnRegister();
	afx_msg void OnBtnDelete();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYWEBPROTOCOLDLG_H__693D05DE_E415_4416_AFC7_68E4092D190C__INCLUDED_)
