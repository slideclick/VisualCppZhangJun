// SliderDemoDlg.h : header file
//

#if !defined(AFX_SLIDERDEMODLG_H__8E703B9A_77A9_4EA1_8C05_7D59AE08D218__INCLUDED_)
#define AFX_SLIDERDEMODLG_H__8E703B9A_77A9_4EA1_8C05_7D59AE08D218__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSliderDemoDlg dialog

class CSliderDemoDlg : public CDialog
{
// Construction
public:
	CSliderDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSliderDemoDlg)
	enum { IDD = IDD_SLIDERDEMO_DIALOG };
	CSliderCtrl	m_slider;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSliderDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSliderDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SLIDERDEMODLG_H__8E703B9A_77A9_4EA1_8C05_7D59AE08D218__INCLUDED_)
