// CalendarDemoDlg.h : header file
//

#if !defined(AFX_CALENDARDEMODLG_H__88C53222_DF83_408C_9356_655455B685B4__INCLUDED_)
#define AFX_CALENDARDEMODLG_H__88C53222_DF83_408C_9356_655455B685B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCalendarDemoDlg dialog

class CCalendarDemoDlg : public CDialog
{
// Construction
public:
	CCalendarDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCalendarDemoDlg)
	enum { IDD = IDD_CALENDARDEMO_DIALOG };
	CMonthCalCtrl	m_calendar;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCalendarDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCalendarDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSelchangeCalendar(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALENDARDEMODLG_H__88C53222_DF83_408C_9356_655455B685B4__INCLUDED_)
