// SysKeyDlg.h : header file
//

#if !defined(AFX_SYSKEYDLG_H__99759BFC_64E8_474C_B661_B00C8F39E820__INCLUDED_)
#define AFX_SYSKEYDLG_H__99759BFC_64E8_474C_B661_B00C8F39E820__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSysKeyDlg dialog
//键盘HOOK中的函数指针
typedef void (*SetVKeyProc)(DWORD dwVKey);

class CSysKeyDlg : public CDialog
{
// Construction
public:
	CSysKeyDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSysKeyDlg)
	enum { IDD = IDD_SYSKEY_DIALOG };
	CComboBox	m_cmb_VKey;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSysKeyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HMODULE m_hHookDll;
	SetVKeyProc m_proc;
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSysKeyDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSelchangeCmbVkey();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYSKEYDLG_H__99759BFC_64E8_474C_B661_B00C8F39E820__INCLUDED_)
