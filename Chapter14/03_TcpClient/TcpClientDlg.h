// TcpClientDlg.h : header file
//

#if !defined(AFX_TCPCLIENTDLG_H__C9E6B74B_6C2B_4383_9D3A_B780144F68F4__INCLUDED_)
#define AFX_TCPCLIENTDLG_H__C9E6B74B_6C2B_4383_9D3A_B780144F68F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTcpClientDlg dialog

class CTcpClientDlg : public CDialog
{
// Construction
public:
	CTcpClientDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTcpClientDlg)
	enum { IDD = IDD_TCPCLIENT_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTcpClientDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void ErrMsg(int nCode);
	void OutputMsg(LPCTSTR lpMsg);
	afx_msg void OnSockNotify(WPARAM wp, LPARAM lp);
protected:
	SOCKET m_sock;
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTcpClientDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnConnect();
	afx_msg void OnBtnSend();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TCPCLIENTDLG_H__C9E6B74B_6C2B_4383_9D3A_B780144F68F4__INCLUDED_)
