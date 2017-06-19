// MappingClientDlg.h : header file
//

#if !defined(AFX_MAPPINGCLIENTDLG_H__625DBFB0_0F4B_4D8E_A920_CCD64753728D__INCLUDED_)
#define AFX_MAPPINGCLIENTDLG_H__625DBFB0_0F4B_4D8E_A920_CCD64753728D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMappingClientDlg dialog

class CMappingClientDlg : public CDialog
{
// Construction
public:
	CMappingClientDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMappingClientDlg)
	enum { IDD = IDD_MAPPINGCLIENT_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMappingClientDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMappingClientDlg)
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

#endif // !defined(AFX_MAPPINGCLIENTDLG_H__625DBFB0_0F4B_4D8E_A920_CCD64753728D__INCLUDED_)
