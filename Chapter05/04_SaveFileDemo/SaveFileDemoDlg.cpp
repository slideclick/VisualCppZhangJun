// SaveFileDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SaveFileDemo.h"
#include "SaveFileDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSaveFileDemoDlg dialog

CSaveFileDemoDlg::CSaveFileDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSaveFileDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSaveFileDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSaveFileDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSaveFileDemoDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSaveFileDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CSaveFileDemoDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSaveFileDemoDlg message handlers

BOOL CSaveFileDemoDlg::OnInitDialog()
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

void CSaveFileDemoDlg::OnPaint() 
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
HCURSOR CSaveFileDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSaveFileDemoDlg::OnOK() 
{
	//显示保存文件对话框
	CFileDialog dlg(FALSE, NULL, NULL, 
		OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_PATHMUSTEXIST, 
		_T("*.txt|*.txt||"), this);
	if (dlg.DoModal() == IDOK) 
	{
		//得到文件名
		SetDlgItemText(IDC_EDT_FILENAME, dlg.GetPathName());
	}
}
