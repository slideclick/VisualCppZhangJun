// RecorderDlg.h : header file
//

#if !defined(AFX_RECORDERDLG_H__9C917638_AE80_42A4_8FCE_2E248D2808CE__INCLUDED_)
#define AFX_RECORDERDLG_H__9C917638_AE80_42A4_8FCE_2E248D2808CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CRecorderDlg dialog

class CRecorderDlg : public CDialog
{
// Construction
public:
	CRecorderDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CRecorderDlg)
	enum { IDD = IDD_RECORDER_DIALOG };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRecorderDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void ErrBox(DWORD dwErr);
	BOOL m_bRecording;
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CRecorderDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnRecord();
	afx_msg void OnBtnSave();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECORDERDLG_H__9C917638_AE80_42A4_8FCE_2E248D2808CE__INCLUDED_)
