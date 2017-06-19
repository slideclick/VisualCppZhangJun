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
	BOOL m_bRunning;			//ָʾ��ǰ�����Ƿ��ڽ���
	CRITICAL_SECTION m_csGet;	//���ڻ�ȡ���ֵ��߳�ͬ���ٽ���
	CRITICAL_SECTION m_csAdd;	//������ӽ�����߳�ͬ���ٽ���
	int m_nMaxNumber;			//����ļ�������
	int m_nFoundCount;			//�ҵ�����������
	int m_nThreadCount;			//������߳���
	HANDLE *m_pThreadHandles;	//�����߳̾��
	HANDLE m_hRunEvent;			//�̵߳��˳���־Event 
	CString m_strPrimeNumbers;	//�ҵ�������
	DWORD m_dwStartTick;		//���㿪ʼʱ�ĵδ���
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRIMENUMBERFINALDLG_H__6C3516BB_F37F_4159_864C_905F7D52B03D__INCLUDED_)
