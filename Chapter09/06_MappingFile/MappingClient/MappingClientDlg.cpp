// MappingClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MappingClient.h"
#include "MappingClientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MY_MAPPING_NAME _T("My_Maping_File_Name")
#define MAX_MAPPING_SIZE (1024*1024)

/////////////////////////////////////////////////////////////////////////////
// CMappingClientDlg dialog

CMappingClientDlg::CMappingClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMappingClientDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMappingClientDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMappingClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMappingClientDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMappingClientDlg, CDialog)
	//{{AFX_MSG_MAP(CMappingClientDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMappingClientDlg message handlers

BOOL CMappingClientDlg::OnInitDialog()
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

void CMappingClientDlg::OnPaint() 
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
HCURSOR CMappingClientDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMappingClientDlg::OnOK() 
{
	//打开内存映射文件
	HANDLE hFile = OpenFileMapping(
		FILE_MAP_READ, FALSE, MY_MAPPING_NAME);
	if (!hFile)
	{
		AfxMessageBox(_T("打开内存映射文件失败！"));
		return;
	}
	//获取文件首字节地址
	LPCTSTR lpStr = (LPCTSTR)MapViewOfFile(
		hFile, FILE_MAP_READ, 0, 0, 0);
	if (!lpStr)
	{
		AfxMessageBox(_T("获取映射文件起始地址失败！"));
		return;
	}
	//将文本框上的光标移到最后
	CEdit * pEdit = (CEdit *)GetDlgItem(IDC_EDT_CONTENT);
	pEdit->SetSel(pEdit->GetWindowTextLength(), 
		pEdit->GetWindowTextLength());
	//将内存映射文件中的内容追加到文本框
	pEdit->ReplaceSel(lpStr, FALSE);
	//关闭文件，释放句柄
	UnmapViewOfFile(lpStr);
	CloseHandle(hFile);
}

void CMappingClientDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	
}
