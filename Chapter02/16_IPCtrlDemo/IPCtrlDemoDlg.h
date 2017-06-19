// IPCtrlDemoDlg.h : header file
//

#if !defined(AFX_IPCTRLDEMODLG_H__FC9B115C_96AB_45B2_B904_BD2D8965609F__INCLUDED_)
#define AFX_IPCTRLDEMODLG_H__FC9B115C_96AB_45B2_B904_BD2D8965609F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CIPCtrlDemoDlg dialog

class CIPCtrlDemoDlg : public CDialog
{
// Construction
public:
	CIPCtrlDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CIPCtrlDemoDlg)
	enum { IDD = IDD_IPCTRLDEMO_DIALOG };
	CIPAddressCtrl	m_ip;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIPCtrlDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CIPCtrlDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnSend();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IPCTRLDEMODLG_H__FC9B115C_96AB_45B2_B904_BD2D8965609F__INCLUDED_)
