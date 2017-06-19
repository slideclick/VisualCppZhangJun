// ClipboardMonitorDlg.h : header file
//

#if !defined(AFX_CLIPBOARDMONITORDLG_H__11B50CA3_7151_40A5_B9B7_58390B0CD539__INCLUDED_)
#define AFX_CLIPBOARDMONITORDLG_H__11B50CA3_7151_40A5_B9B7_58390B0CD539__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CClipboardMonitorDlg dialog

class CClipboardMonitorDlg : public CDialog
{
// Construction
public:
	CClipboardMonitorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CClipboardMonitorDlg)
	enum { IDD = IDD_CLIPBOARDMONITOR_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClipboardMonitorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HWND m_hwndNextViewer;
	HICON m_hIcon;

	void DrawClipboard();
	// Generated message map functions
	//{{AFX_MSG(CClipboardMonitorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	afx_msg void OnChangeCbChain(HWND hWndRemove, HWND hWndAfter);
	afx_msg void OnDrawClipboard();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIPBOARDMONITORDLG_H__11B50CA3_7151_40A5_B9B7_58390B0CD539__INCLUDED_)
