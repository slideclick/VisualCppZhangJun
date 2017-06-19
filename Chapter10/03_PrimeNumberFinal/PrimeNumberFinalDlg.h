// PrimeNumberFinalDlg.h : header file
//

#if !defined(AFX_PRIMENUMBERFINALDLG_H__6C3516BB_F37F_4159_864C_905F7D52B03D__INCLUDED_)
#define AFX_PRIMENUMBERFINALDLG_H__6C3516BB_F37F_4159_864C_905F7D52B03D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CPrimeNumberFinalDlg dialog

class CPrimeNumberFinalDlg : public CDialog
{
// Construction
public:
	CPrimeNumberFinalDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CPrimeNumberFinalDlg)
	enum { IDD = IDD_PRIMENUMBERFINAL_DIALOG };
	CSpinButtonCtrl	m_spin_thread;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrimeNumberFinalDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CPrimeNumberFinalDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	int GetANumber();
	void AddNewPrimeNumber(int nNumber);
	void CloseAllThread();
	void OnWaitThreadEnd();
	static void WorkProc(LPVOID lpParam);
protected:
	BOOL m_bRunning;			//指示当前计算是否在进行
	CRITICAL_SECTION m_csGet;	//用于获取数字的线程同步临界区
	CRITICAL_SECTION m_csAdd;	//用于添加结果的线程同步临界区
	int m_nMaxNumber;			//输入的计算数字
	int m_nFoundCount;			//找到的素数个数
	int m_nThreadCount;			//输入的线程数
	HANDLE *m_pThreadHandles;	//保存线程句柄
	HANDLE m_hRunEvent;			//线程的退出标志Event 
	CString m_strPrimeNumbers;	//找到的素数
	DWORD m_dwStartTick;		//计算开始时的滴答数
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRIMENUMBERFINALDLG_H__6C3516BB_F37F_4159_864C_905F7D52B03D__INCLUDED_)
