// BgMusicDlg.h : header file
//

#if !defined(AFX_BGMUSICDLG_H__9F599A03_C891_4435_963E_6A5480D49EA1__INCLUDED_)
#define AFX_BGMUSICDLG_H__9F599A03_C891_4435_963E_6A5480D49EA1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CBgMusicDlg dialog

class CBgMusicDlg : public CDialog
{
// Construction
public:
	CBgMusicDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CBgMusicDlg)
	enum { IDD = IDD_BGMUSIC_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBgMusicDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CBgMusicDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnChkPlay();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BGMUSICDLG_H__9F599A03_C891_4435_963E_6A5480D49EA1__INCLUDED_)
