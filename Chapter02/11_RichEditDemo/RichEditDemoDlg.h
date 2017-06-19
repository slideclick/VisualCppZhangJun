// RichEditDemoDlg.h : header file
//

#if !defined(AFX_RICHEDITDEMODLG_H__C22377CD_2B47_4B47_825F_2159E7D467AF__INCLUDED_)
#define AFX_RICHEDITDEMODLG_H__C22377CD_2B47_4B47_825F_2159E7D467AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CRichEditDemoDlg dialog

class CRichEditDemoDlg : public CDialog
{
// Construction
public:
	CRichEditDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CRichEditDemoDlg)
	enum { IDD = IDD_RICHEDITDEMO_DIALOG };
	CRichEditCtrl	m_edit;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRichEditDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	static DWORD CALLBACK StreamOutProc(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb);
	static DWORD CALLBACK StreamInProc(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb);
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CRichEditDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnColor();
	afx_msg void OnBtnFont();
	afx_msg void OnBtnSave();
	afx_msg void OnBtnLoad();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RICHEDITDEMODLG_H__C22377CD_2B47_4B47_825F_2159E7D467AF__INCLUDED_)
