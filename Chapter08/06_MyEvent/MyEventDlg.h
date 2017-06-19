// MyEventDlg.h : header file
//

#if !defined(AFX_MYEVENTDLG_H__607E8CFA_D6F9_494B_9CBE_2E4C9C8BD3CE__INCLUDED_)
#define AFX_MYEVENTDLG_H__607E8CFA_D6F9_494B_9CBE_2E4C9C8BD3CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMyEventDlg dialog

class CMyEventDlg : public CDialog
{
// Construction
public:
	CMyEventDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMyEventDlg)
	enum { IDD = IDD_MYEVENT_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyEventDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	LPCTSTR FindNext(LPCTSTR lpBuffer);
	void ProcessSleep(LPCTSTR *ppszCmd);
	void ProcessMouseEvent(LPCTSTR *ppszCmd);
	void ProcessKeybdEvent(LPCTSTR *ppszCmd);
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMyEventDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYEVENTDLG_H__607E8CFA_D6F9_494B_9CBE_2E4C9C8BD3CE__INCLUDED_)
