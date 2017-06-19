// MediaPlayerDlg.h : header file
//

#if !defined(AFX_MEDIAPLAYERDLG_H__367716A4_7F26_499A_9584_EF02C2896BBC__INCLUDED_)
#define AFX_MEDIAPLAYERDLG_H__367716A4_7F26_499A_9584_EF02C2896BBC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\comm\videorender.h"

/////////////////////////////////////////////////////////////////////////////
// CMediaPlayerDlg dialog

class CMediaPlayerDlg : public CDialog
{
// Construction
public:
	CMediaPlayerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMediaPlayerDlg)
	enum { IDD = IDD_MEDIAPLAYER_DIALOG };
	CSliderCtrl	m_slider;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMediaPlayerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void OnVideoNotify();
	CVideoRender m_video;
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMediaPlayerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnOpen();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnReleasedcaptureSlider(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MEDIAPLAYERDLG_H__367716A4_7F26_499A_9584_EF02C2896BBC__INCLUDED_)
