// OpenFileDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OpenFileDemo.h"
#include "OpenFileDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COpenFileDemoDlg dialog

COpenFileDemoDlg::COpenFileDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COpenFileDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(COpenFileDemoDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void COpenFileDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COpenFileDemoDlg)
	DDX_Control(pDX, IDC_CHK_MULTISEL, m_chkMultiSel);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(COpenFileDemoDlg, CDialog)
	//{{AFX_MSG_MAP(COpenFileDemoDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_MFC, OnBtnMfc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COpenFileDemoDlg message handlers

BOOL COpenFileDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void COpenFileDemoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR COpenFileDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void COpenFileDemoDlg::OnOK() 
{
	//存放文件的缓冲
	TCHAR szBuffer[MAX_PATH * 10] = {0};
	//初始化结构
	OPENFILENAME ofn = {0};
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = m_hWnd;
	ofn.lpstrFilter = _T("文本文件(*.txt)\0*.txt\0所有文件(*.*)\0*.*\0");
	ofn.lpstrInitialDir = _T("c:\\");
	ofn.lpstrFile = szBuffer;
	ofn.nMaxFile = sizeof(szBuffer)/sizeof(*szBuffer);
	ofn.nFilterIndex = 0;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER;
	//如果多选，加上多选标志
	if(m_chkMultiSel.GetCheck())
		ofn.Flags |= OFN_ALLOWMULTISELECT;
	//显示打开文件对话框
	BOOL bSel = GetOpenFileName(&ofn);
	if(!bSel)
	{
		SetDlgItemText(IDC_EDT_RESULT, _T("选择被取消。"));
		return;
	}
	//获得所选文件
	if(m_chkMultiSel.GetCheck())
	{
		//如果有多选标志，缓冲区第一节为路径，文件名在路径之后。
		TCHAR szPath[MAX_PATH] = {0};
		CString str;
		int nLen;
		TCHAR *p = ofn.lpstrFile + ofn.nFileOffset;
		_tcsncpy(szPath, ofn.lpstrFile, ofn.nFileOffset);
		if(szPath[ofn.nFileOffset - 1] != '\\')
			_tcscat(szPath, _T("\\"));
		while(TRUE)
		{
			nLen = _tcslen(p);
			if (nLen == 0)
				break;
			str += szPath;
			str += p;
			str += _T("\r\n");
			p += nLen + 1;
		}
		SetDlgItemText(IDC_EDT_RESULT, str);
	}
	else
	{
		//如果没有多选标志，缓冲区内为完整文件名。
		SetDlgItemText(IDC_EDT_RESULT, szBuffer);
	}

}

void COpenFileDemoDlg::OnBtnMfc() 
{
	//定义缓冲和对话框
	TCHAR szBuffer[MAX_PATH * 10] = {0};
	CFileDialog dlg(TRUE, NULL, NULL, 
		OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST, 
		_T("文本文件(*.txt)|*.txt|所有文件(*.*)|*.*||"), this);
	dlg.m_ofn.lpstrInitialDir = _T("c:\\");
	//如果多选，需要给对话框分配更大的缓冲以保存更多文件名
	if(m_chkMultiSel.GetCheck())
	{
		dlg.m_ofn.lpstrFile = szBuffer;
		dlg.m_ofn.nMaxFile = sizeof(szBuffer)/sizeof(*szBuffer);
		dlg.m_ofn.Flags |= OFN_ALLOWMULTISELECT;
	}
	//显示对话框
	if(dlg.DoModal() != IDOK)
	{
		SetDlgItemText(IDC_EDT_RESULT, _T("选择被取消。"));
		return;
	}
	//得到所选文件
	if (m_chkMultiSel.GetCheck())
	{
		//如果有多选标志，需要用循环获得文件名
		CString strFile;
		POSITION pos = dlg.GetStartPosition();
		while(pos)
		{
			strFile += dlg.GetNextPathName(pos);
			strFile += _T("\r\n");
		}
		SetDlgItemText(IDC_EDT_RESULT, strFile);
	}
	else
	{
		//如果没有多选标志，可以直接获得文件名
		SetDlgItemText(IDC_EDT_RESULT, dlg.GetPathName());
	}
}
