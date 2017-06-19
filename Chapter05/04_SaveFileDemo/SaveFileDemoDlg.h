// SaveFileDemoDlg.h : header file
//

#if !defined(AFX_SAVEFILEDEMODLG_H__36057AD6_227F_4156_B839_44C9C1F3D5C5__INCLUDED_)
#define AFX_SAVEFILEDEMODLG_H__36057AD6_227F_4156_B839_44C9C1F3D5C5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSaveFileDemoDlg dialog

class CSaveFileDemoDlg : public CDialog
{
// Construction
public:
	CSaveFileDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSaveFileDemoDlg)
	enum { IDD = IDD_SAVEFILEDEMO_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSaveFileDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSaveFileDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAVEFILEDEMODLG_H__36057AD6_227F_4156_B839_44C9C1F3D5C5__INCLUDED_)
