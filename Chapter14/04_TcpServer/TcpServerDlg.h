// TcpServerDlg.h : header file
//

#if !defined(AFX_TCPSERVERDLG_H__9A195D99_2A91_40C3_A0AA_B72C2FB9D9D2__INCLUDED_)
#define AFX_TCPSERVERDLG_H__9A195D99_2A91_40C3_A0AA_B72C2FB9D9D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTcpServerDlg dialog
#define MAX_SOCKETS 32

class CTcpServerDlg : public CDialog
{
// Construction
public:
	CTcpServerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTcpServerDlg)
	enum { IDD = IDD_TCPSERVER_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTcpServerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void ErrMsg(int nCode);
	void OutputMsg(LPCTSTR lpMsg);
	afx_msg void OnSockAccept(WPARAM wp, LPARAM lp);
	afx_msg void OnSockMsg(WPARAM wp, LPARAM lp);
protected:
	SOCKET m_server;		//用于监听的套接字
	SOCKET m_clients[32];	//保存和客户端通讯的套接字
	UINT m_nClients;		//已连接的客户端数量
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTcpServerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnListen();
	afx_msg void OnBtnSend();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TCPSERVERDLG_H__9A195D99_2A91_40C3_A0AA_B72C2FB9D9D2__INCLUDED_)
