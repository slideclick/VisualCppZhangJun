// PreviewFileDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PreviewFileDlg.h"
#include "PreviewFileDlg_ids.h"
#include "..\MyMemDC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPreviewFileDlg

//����֪ͨ��Ϣ�ĺ�������
BOOL NEAR CALLBACK HandleNotify(HWND hDlg, LPOFNOTIFY pofn);
//�µĶԻ������
LRESULT CALLBACK PreviewDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

IMPLEMENT_DYNAMIC(CPreviewFileDlg, CFileDialog)

CPreviewFileDlg::CPreviewFileDlg(BOOL bOpenFileDialog, LPCTSTR lpszDefExt, LPCTSTR lpszFileName,
		DWORD dwFlags, LPCTSTR lpszFilter, CWnd* pParentWnd) :
		CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd)
{
	//�޸�ѡ������Զ���
	m_ofn.Flags |= OFN_EXPLORER |OFN_HIDEREADONLY | OFN_ENABLEHOOK | OFN_ENABLETEMPLATE; 
	//�޸�ʵ�����
	m_ofn.hInstance = AfxGetInstanceHandle();
	//�޸ĶԻ���ģ��
	m_ofn.lpTemplateName = MAKEINTRESOURCE(IDD_PREVIEW_DLG);
	//�޸ĶԻ������
	m_ofn.lpfnHook =  (LPOFNHOOKPROC)PreviewDlgProc;
}

BEGIN_MESSAGE_MAP(CPreviewFileDlg, CFileDialog)
	//{{AFX_MSG_MAP(CPreviewFileDlg)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CPreviewFileDlg::PreviewImg(HWND hDlg, LPCTSTR lpPath)
{
	//Ԥ��
	HWND hPreview = ::GetDlgItem(this->GetSafeHwnd(), IDC_PREVIEW_RENDER);
	if (hPreview != NULL) 
	{
		//����ͼƬ
		CMyMemDC dc;
		dc.CreateFromFile(lpPath);
		//��ͼƬ���Ƶ��ؼ�
		HDC hDC = ::GetDC(hPreview);
		RECT rcWnd = {0};
		::GetClientRect(hPreview, &rcWnd);
		SetStretchBltMode(hDC, HALFTONE); 
		StretchBlt(hDC, 0, 0, rcWnd.right, rcWnd.bottom, dc, 0, 0, dc.GetWidth(), dc.GetHeight(), SRCCOPY);
		::ReleaseDC(hPreview, hDC);
		//��ʾ��С
		TCHAR szSize[32] = {0};
		_stprintf(szSize, _T("%d X %d"), dc.GetWidth(), dc.GetHeight());
		SetDlgItemText(IDC_PREVIEW_SIZE, szSize);
	}
}

LRESULT CALLBACK PreviewDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam){
	LRESULT lRet = 1;
	switch(uMsg)
	{
		case WM_NOTIFY:
			//�Լ�����֪ͨ��Ϣ
			lRet = HandleNotify(hDlg, (LPOFNOTIFY)lParam);
		default:
			lRet = 0;
			break;
	}
	return lRet;
}

BOOL CALLBACK HandleNotify(HWND hDlg, LPOFNOTIFY pofn)
{
	CPreviewFileDlg dlg(TRUE);
	dlg.Attach(hDlg);
	switch (pofn->hdr.code)
	{
	case CDN_SELCHANGE:
		{
			TCHAR szFile[MAX_PATH];
			//��ȡ��ǰѡ�е��ļ�
			if (CommDlg_OpenSave_GetFilePath(GetParent(hDlg), szFile, sizeof(szFile)) <= sizeof(szFile))
			{
				//���ѡ�е����ļ���Ԥ���ļ�
				if(GetFileAttributes(szFile) !=  FILE_ATTRIBUTE_DIRECTORY)
				{			
					dlg.PreviewImg(hDlg, szFile);	
				}
			}
		}
		break;
	case CDN_FILEOK:
		_AFX_THREAD_STATE* pThreadState = AfxGetThreadState();
		pThreadState->m_pAlternateWndInit = NULL;
		return 0;
	}

	dlg.Detach();
	return(TRUE);
}
