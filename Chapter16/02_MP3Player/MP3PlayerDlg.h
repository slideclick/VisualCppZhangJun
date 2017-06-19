// MP3PlayerDlg.h : header file
//

#if !defined(AFX_MP3PLAYERDLG_H__C36026D2_5F47_48F0_A107_3AC8452DAE27__INCLUDED_)
#define AFX_MP3PLAYERDLG_H__C36026D2_5F47_48F0_A107_3AC8452DAE27__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMP3PlayerDlg dialog

class CMP3PlayerDlg : public CDialog
{
// Construction
public:
	CMP3PlayerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMP3PlayerDlg)
	enum { IDD = IDD_MP3PLAYER_DIALOG };
	CSliderCtrl	m_slider;
	CListBox	m_list_music;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMP3PlayerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void ErrBox(DWORD dwErr);
	BOOL StopPlay();
	BOOL m_bPlaying;
	UINT m_nTotalLen;
	TCHAR m_szFullName[MAX_PATH];
	TCHAR m_szShortName[MAX_PATH];
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMP3PlayerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnAdd();
	afx_msg void OnBtnRemove();
	afx_msg void OnBtnPlay();
	afx_msg void OnDblclkLitMusic();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MP3PLAYERDLG_H__C36026D2_5F47_48F0_A107_3AC8452DAE27__INCLUDED_)
