// MsgInMfcDlg.h : header file
//

#if !defined(AFX_MSGINMFCDLG_H__750C4A3C_176B_4A47_89F1_951BBFEAA42E__INCLUDED_)
#define AFX_MSGINMFCDLG_H__750C4A3C_176B_4A47_89F1_951BBFEAA42E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMsgInMfcDlg dialog

class CMsgInMfcDlg : public CDialog
{
// Construction
public:
	CMsgInMfcDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMsgInMfcDlg)
	enum { IDD = IDD_MSGINMFC_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMsgInMfcDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMsgInMfcDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	//清除按钮的响应函数
	afx_msg void OnBtnClear();
	//文本框文本改变消息的响应函数
	afx_msg void OnEdtInputChange();
	//擦除背景消息的响应函数
	afx_msg void OnEraseBackground(WPARAM wp, LPARAM lp);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSGINMFCDLG_H__750C4A3C_176B_4A47_89F1_951BBFEAA42E__INCLUDED_)
