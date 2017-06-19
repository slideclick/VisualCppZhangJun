// MenuDemoDlg.h : header file
//

#if !defined(AFX_MENUDEMODLG_H__9C035A43_97A3_4C8C_8BF5_AC3BB52CC031__INCLUDED_)
#define AFX_MENUDEMODLG_H__9C035A43_97A3_4C8C_8BF5_AC3BB52CC031__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMenuDemoDlg dialog

class CMenuDemoDlg : public CDialog
{
// Construction
public:
	CMenuDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMenuDemoDlg)
	enum { IDD = IDD_MENUDEMO_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMenuDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
protected:
	HMENU m_hMenu1;
	HMENU m_hMenu2;

	// Generated message map functions
	//{{AFX_MSG(CMenuDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnHideMenu();
	afx_msg void OnDestroy();
	afx_msg void OnMiCheck();
	afx_msg void OnMiDisable();
	afx_msg void OnMiEnable();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MENUDEMODLG_H__9C035A43_97A3_4C8C_8BF5_AC3BB52CC031__INCLUDED_)
