// FolderDlg.cpp: implementation of the CFolderDlg class.
//
//////////////////////////////////////////////////////////////////////

#include "FolderDlg.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFolderDlg::CFolderDlg(LPCTSTR lpInitPath, LPCTSTR lpTitle)
{
	m_lpszInitPath = lpInitPath;
	m_lpszTitle = lpTitle;
	*m_szSelectedPath = _T('\0');
}

CFolderDlg::~CFolderDlg()
{

}

BOOL CFolderDlg::ShowDlg(HWND hParent)
{
	BROWSEINFO bi = {0};
	bi.lpszTitle = m_lpszTitle;
	bi.lpfn = BrowseProc;
	bi.lParam = (LPARAM)this;
	bi.hwndOwner = hParent;
	LPITEMIDLIST pidl = SHBrowseForFolder(&bi);
	if(pidl != NULL)
	{
		SHGetPathFromIDList(pidl, m_szSelectedPath);
		return TRUE;
	}
	else
		return FALSE;
}

LPCTSTR CFolderDlg::GetSelectedPath()
{
	return m_szSelectedPath;
}

int CALLBACK CFolderDlg::BrowseProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
	CFolderDlg *pDlg = (CFolderDlg *)lpData;
	switch(uMsg)
	{
	case BFFM_INITIALIZED:
		SendMessage(hwnd, BFFM_SETSELECTION, TRUE, (LPARAM)pDlg->m_lpszInitPath);
		break;
	default:
		break;
	}
	return 0;
}