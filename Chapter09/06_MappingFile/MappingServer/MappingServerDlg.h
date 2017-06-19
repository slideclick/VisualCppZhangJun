// MappingServerDlg.h : header file
//

#if !defined(AFX_MAPPINGSERVERDLG_H__6185594F_25EB_4608_8590_1885265A0E14__INCLUDED_)
#define AFX_MAPPINGSERVERDLG_H__6185594F_25EB_4608_8590_1885265A0E14__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMappingServerDlg dialog

class CMappingServerDlg : public CDialog
{
// Construction
public:
	CMappingServerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMappingServerDlg)
	enum { IDD = IDD_MAPPINGSERVER_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMappingServerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HANDLE m_hFile;
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMappingServerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAPPINGSERVERDLG_H__6185594F_25EB_4608_8590_1885265A0E14__INCLUDED_)
