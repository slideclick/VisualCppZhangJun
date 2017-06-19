// DateTimeDemoDlg.h : header file
//

#if !defined(AFX_DATETIMEDEMODLG_H__C64CAAEE_0388_4E3B_A7A8_71AC6DC0E74E__INCLUDED_)
#define AFX_DATETIMEDEMODLG_H__C64CAAEE_0388_4E3B_A7A8_71AC6DC0E74E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDateTimeDemoDlg dialog

class CDateTimeDemoDlg : public CDialog
{
// Construction
public:
	CDateTimeDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDateTimeDemoDlg)
	enum { IDD = IDD_DATETIMEDEMO_DIALOG };
	CDateTimeCtrl	m_date_end;
	CDateTimeCtrl	m_date_begin;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDateTimeDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void CountSpan();
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDateTimeDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDatetimechangeDateBegin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDatetimechangeDateEnd(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATETIMEDEMODLG_H__C64CAAEE_0388_4E3B_A7A8_71AC6DC0E74E__INCLUDED_)
