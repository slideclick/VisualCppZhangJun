// PopMenuDemoDlg.h : header file
//

#if !defined(AFX_POPMENUDEMODLG_H__1503AEA7_D4BA_4C67_8D60_A98E57098FFC__INCLUDED_)
#define AFX_POPMENUDEMODLG_H__1503AEA7_D4BA_4C67_8D60_A98E57098FFC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CPopMenuDemoDlg dialog

class CPopMenuDemoDlg : public CDialog
{
// Construction
public:
	CPopMenuDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CPopMenuDemoDlg)
	enum { IDD = IDD_POPMENUDEMO_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPopMenuDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
protected:
	CMenu m_menu;		//菜单
	int m_nClickCount;	//点击次数
	BOOL m_bChecked;	//是否选中

	// Generated message map functions
	//{{AFX_MSG(CPopMenuDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POPMENUDEMODLG_H__1503AEA7_D4BA_4C67_8D60_A98E57098FFC__INCLUDED_)
