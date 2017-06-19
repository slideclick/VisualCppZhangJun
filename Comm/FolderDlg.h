// FolderDlg.h: interface for the CFolderDlg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FOLDERDLG_H__5957E671_4A1F_4B9D_B3D5_AC6114F921C7__INCLUDED_)
#define AFX_FOLDERDLG_H__5957E671_4A1F_4B9D_B3D5_AC6114F921C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#define UNICODE
//#define _UNICODE

#include <windows.h>
#include <tchar.h>
#include <shlobj.h>

class CFolderDlg  
{
public:
	CFolderDlg(LPCTSTR lpInitPath, LPCTSTR lpTitle);
	virtual ~CFolderDlg();
	BOOL ShowDlg(HWND hParent);
	LPCTSTR GetSelectedPath();
protected:
	static int CALLBACK BrowseProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData);
protected:
	LPCTSTR m_lpszInitPath;
	LPCTSTR m_lpszTitle;
	TCHAR m_szSelectedPath[MAX_PATH];
};

#endif // !defined(AFX_FOLDERDLG_H__5957E671_4A1F_4B9D_B3D5_AC6114F921C7__INCLUDED_)
