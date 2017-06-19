// PrimeNumberFinderExDlg.h : header file
//

#if !defined(AFX_PRIMENUMBERFINDEREXDLG_H__A3F5F0FF_D6A3_4B77_83F4_8CE5F5B4637C__INCLUDED_)
#define AFX_PRIMENUMBERFINDEREXDLG_H__A3F5F0FF_D6A3_4B77_83F4_8CE5F5B4637C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CPrimeNumberFinderExDlg dialog

class CPrimeNumberFinderExDlg : public CDialog
{
// Construction
public:
	CPrimeNumberFinderExDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CPrimeNumberFinderExDlg)
	enum { IDD = IDD_PRIMENUMBERFINDEREX_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrimeNumberFinderExDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	static UINT WorkProc(LPVOID lpParam);
	inline BOOL IsPrimeNumber(int nInput);
	HICON m_hIcon;
	BOOL m_bRunning;

	// Generated message map functions
	//{{AFX_MSG(CPrimeNumberFinderExDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRIMENUMBERFINDEREXDLG_H__A3F5F0FF_D6A3_4B77_83F4_8CE5F5B4637C__INCLUDED_)
