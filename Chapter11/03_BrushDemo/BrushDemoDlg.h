// BrushDemoDlg.h : header file
//

#if !defined(AFX_BRUSHDEMODLG_H__6FACB089_C600_4AC9_8955_381FC8B7CBEA__INCLUDED_)
#define AFX_BRUSHDEMODLG_H__6FACB089_C600_4AC9_8955_381FC8B7CBEA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CBrushDemoDlg dialog

class CBrushDemoDlg : public CDialog
{
// Construction
public:
	CBrushDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CBrushDemoDlg)
	enum { IDD = IDD_BRUSHDEMO_DIALOG };
	CComboBox	m_cmb_brush;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBrushDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CBrush m_brush;
	CBitmap m_bmp;
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CBrushDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSelchangeCmbBrush();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BRUSHDEMODLG_H__6FACB089_C600_4AC9_8955_381FC8B7CBEA__INCLUDED_)
