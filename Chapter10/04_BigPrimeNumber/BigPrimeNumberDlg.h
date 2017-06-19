// BigPrimeNumberDlg.h : header file
//

#if !defined(AFX_BIGPRIMENUMBERDLG_H__D4FAD8A7_0830_4A21_9075_8FDED10B7A16__INCLUDED_)
#define AFX_BIGPRIMENUMBERDLG_H__D4FAD8A7_0830_4A21_9075_8FDED10B7A16__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CBigPrimeNumberDlg dialog

class CBigPrimeNumberDlg : public CDialog
{
// Construction
public:
	CBigPrimeNumberDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CBigPrimeNumberDlg)
	enum { IDD = IDD_BIGPRIMENUMBER_DIALOG };
	CEdit	m_edtResult;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBigPrimeNumberDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CBigPrimeNumberDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	//输出数字消息响应
	afx_msg void OnUserPrime(WPARAM wp, LPARAM lp);
	//输出进度消息
	afx_msg void OnUserNotify(WPARAM wp, LPARAM lp);
	//计算终止消息
	afx_msg void OnUserStop();
	void OutString(LPCTSTR lpStr);
	static void FibProc(LPVOID p);
	static void PrimeProc(LPVOID p);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BIGPRIMENUMBERDLG_H__D4FAD8A7_0830_4A21_9075_8FDED10B7A16__INCLUDED_)
