// KeyVoiceDlg.h : header file
//

#if !defined(AFX_KEYVOICEDLG_H__8A6CB021_0F0D_4B51_951E_02C1071D75EC__INCLUDED_)
#define AFX_KEYVOICEDLG_H__8A6CB021_0F0D_4B51_951E_02C1071D75EC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CKeyVoiceDlg dialog

class CKeyVoiceDlg : public CDialog
{
// Construction
public:
	CKeyVoiceDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CKeyVoiceDlg)
	enum { IDD = IDD_KEYVOICE_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKeyVoiceDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CKeyVoiceDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnChkVoice();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KEYVOICEDLG_H__8A6CB021_0F0D_4B51_951E_02C1071D75EC__INCLUDED_)
