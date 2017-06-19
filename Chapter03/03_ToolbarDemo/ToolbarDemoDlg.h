// ToolbarDemoDlg.h : header file
//

#if !defined(AFX_TOOLBARDEMODLG_H__C4C940F7_8D3C_4C08_863F_AC76C264CDB3__INCLUDED_)
#define AFX_TOOLBARDEMODLG_H__C4C940F7_8D3C_4C08_863F_AC76C264CDB3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CToolbarDemoDlg dialog

class CToolbarDemoDlg : public CDialog
{
// Construction
public:
	CToolbarDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CToolbarDemoDlg)
	enum { IDD = IDD_TOOLBARDEMO_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolbarDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation

protected:
	HICON m_hIcon;
protected:
	CToolBar m_toolbar;	//工具栏
	BOOL m_bCanTest;	//测试按钮是否被禁用
	LRESULT OnKickIdle(WPARAM wParam, LPARAM ICount);
	// Generated message map functions
	//{{AFX_MSG(CToolbarDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnMiTest();
	afx_msg void OnMiDisable();
	afx_msg void OnUpdateMiTest(CCmdUI* pCmdUI);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOOLBARDEMODLG_H__C4C940F7_8D3C_4C08_863F_AC76C264CDB3__INCLUDED_)
