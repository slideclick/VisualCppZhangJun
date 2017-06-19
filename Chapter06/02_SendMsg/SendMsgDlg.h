// SendMsgDlg.h : header file
//

#if !defined(AFX_SENDMSGDLG_H__37A709D9_A868_485C_A46D_F72E8E912145__INCLUDED_)
#define AFX_SENDMSGDLG_H__37A709D9_A868_485C_A46D_F72E8E912145__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSendMsgDlg dialog

class CSendMsgDlg : public CDialog
{
// Construction
public:
	CSendMsgDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSendMsgDlg)
	enum { IDD = IDD_SENDMSG_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSendMsgDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HCURSOR m_hCursor;	//����϶�ʱ�Ĺ��
	BOOL m_bCapturing;	//�Ƿ��ڲ�����
	RECT m_rtCtrl;		//�϶��ؼ���λ�úʹ�С
	HWND m_hwndDest;	//Ŀ�괰��ľ��
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSendMsgDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBtnSettext();
	afx_msg void OnBtnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SENDMSGDLG_H__37A709D9_A868_485C_A46D_F72E8E912145__INCLUDED_)
