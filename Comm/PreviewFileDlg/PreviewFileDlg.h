#if !defined(AFX_PreviewFileDlg_H__2967BF94_2BE4_4141_A864_452F583BA78D__INCLUDED_)
#define AFX_PreviewFileDlg_H__2967BF94_2BE4_4141_A864_452F583BA78D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PreviewFileDlg.h : header file
//


/////////////////////////////////////////////////////////////////////////////
// CPreviewFileDlg dialog

class CPreviewFileDlg : public CFileDialog
{
	DECLARE_DYNAMIC(CPreviewFileDlg)

public:
	void PreviewImg(HWND hDlg, LPCTSTR lpPath);
	CPreviewFileDlg(BOOL bOpenFileDialog, // TRUE for FileOpen, FALSE for FileSaveAs
		LPCTSTR lpszDefExt = NULL,
		LPCTSTR lpszFileName = NULL,
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		LPCTSTR lpszFilter = NULL,
		CWnd* pParentWnd = NULL);

protected:
	//{{AFX_MSG(CPreviewFileDlg)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PreviewFileDlg_H__2967BF94_2BE4_4141_A864_452F583BA78D__INCLUDED_)
