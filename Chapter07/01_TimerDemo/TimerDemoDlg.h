// TimerDemoDlg.h : header file
//

#if !defined(AFX_TIMERDEMODLG_H__7FEC0B92_14F8_47D0_B2F5_BF107B3EE6DB__INCLUDED_)
#define AFX_TIMERDEMODLG_H__7FEC0B92_14F8_47D0_B2F5_BF107B3EE6DB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTimerDemoDlg dialog

class CTimerDemoDlg : public CDialog
{
// Construction
public:
	CTimerDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTimerDemoDlg)
	enum { IDD = IDD_TIMERDEMO_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTimerDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	UINT m_nRedID;
	UINT m_nGreenID;
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTimerDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnRed();
	afx_msg void OnBtnGreen();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TIMERDEMODLG_H__7FEC0B92_14F8_47D0_B2F5_BF107B3EE6DB__INCLUDED_)
