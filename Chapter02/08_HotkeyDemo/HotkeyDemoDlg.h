// HotkeyDemoDlg.h : header file
//

#if !defined(AFX_HOTKEYDEMODLG_H__1F0971AD_4151_4648_B42F_36FA6E07DB8A__INCLUDED_)
#define AFX_HOTKEYDEMODLG_H__1F0971AD_4151_4648_B42F_36FA6E07DB8A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CHotkeyDemoDlg dialog

class CHotkeyDemoDlg : public CDialog
{
// Construction
public:
	CHotkeyDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CHotkeyDemoDlg)
	enum { IDD = IDD_HOTKEYDEMO_DIALOG };
	CHotKeyCtrl	m_hotkey;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHotkeyDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void OnHotkey(WPARAM wp, LPARAM lp);
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CHotkeyDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnRegister();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HOTKEYDEMODLG_H__1F0971AD_4151_4648_B42F_36FA6E07DB8A__INCLUDED_)
