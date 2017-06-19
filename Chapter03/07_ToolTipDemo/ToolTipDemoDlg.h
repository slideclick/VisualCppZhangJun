// ToolTipDemoDlg.h : header file
//

#if !defined(AFX_TOOLTIPDEMODLG_H__C3121017_DE3A_4D26_9353_D9C13798D709__INCLUDED_)
#define AFX_TOOLTIPDEMODLG_H__C3121017_DE3A_4D26_9353_D9C13798D709__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CToolTipDemoDlg dialog

class CToolTipDemoDlg : public CDialog
{
// Construction
public:
	CToolTipDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CToolTipDemoDlg)
	enum { IDD = IDD_TOOLTIPDEMO_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolTipDemoDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CToolTipCtrl m_tooltip;
	BOOL m_bTooltipActived;
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CToolTipDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOOLTIPDEMODLG_H__C3121017_DE3A_4D26_9353_D9C13798D709__INCLUDED_)
