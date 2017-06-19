// PicShowDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PicShow.h"
#include "PicShowDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPicShowDlg dialog

CPicShowDlg::CPicShowDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPicShowDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPicShowDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	*m_szFile = _T('\0');
}

void CPicShowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPicShowDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPicShowDlg, CDialog)
	//{{AFX_MSG_MAP(CPicShowDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(IDR_OPEN, OnOpen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPicShowDlg message handlers

BOOL CPicShowDlg::OnInitDialog()
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

void CPicShowDlg::OnPaint() 
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
		if(m_dc.GetDC())
		{
			//将打开的图片绘制到窗体
			CRect rect;
			GetClientRect(&rect);
			CPaintDC dc(this);
			int nMode = SetStretchBltMode(dc, COLORONCOLOR);
			::StretchBlt(dc, 0, 0, rect.right, rect.bottom, 
				m_dc, 0, 0, m_dc.GetWidth(), m_dc.GetHeight(), SRCCOPY);
			SetStretchBltMode(dc, nMode);
		}
		else
			CDialog::OnPaint();

	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPicShowDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CPicShowDlg::OnOpen() 
{
	//打开图片文件
	LPCTSTR lpFilter = _T("*.bmp;*.jpg;*.gif;*.png;*.tiff;|*.bmp;*.jpg;*.gif;*.png;*.tiff;||");
	CFileDialog dlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST, lpFilter, this);
	if(dlg.DoModal() == IDOK)
	{
		_tcscpy(m_szFile, dlg.GetPathName());
		//用gdi+打开图片并保存在内存dc
		if(m_dc.GetDC())
			m_dc.DeleteObj();
		m_dc.CreateFromFile(m_szFile);
		//刷新窗体
		Invalidate(FALSE);
	}
}
