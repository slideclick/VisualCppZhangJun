// DrawLineDlg.h : header file
//

#if !defined(AFX_DRAWLINEDLG_H__B99BECB7_B8AD_4A40_A421_7C7A74FA275C__INCLUDED_)
#define AFX_DRAWLINEDLG_H__B99BECB7_B8AD_4A40_A421_7C7A74FA275C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDrawLineDlg dialog

class CDrawLineDlg : public CDialog
{
// Construction
public:
	CDrawLineDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDrawLineDlg)
	enum { IDD = IDD_DRAWLINE_DIALOG };
	CStatic	m_preview;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrawLineDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void GetNextValue(double &i, BOOL &bInc);
	CBitmap m_bmp;
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDrawLineDlg)
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

#endif // !defined(AFX_DRAWLINEDLG_H__B99BECB7_B8AD_4A40_A421_7C7A74FA275C__INCLUDED_)
