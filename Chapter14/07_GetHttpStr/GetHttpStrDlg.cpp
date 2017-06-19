// GetHttpStrDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GetHttpStr.h"
#include "GetHttpStrDlg.h"
#include <afxinet.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGetHttpStrDlg dialog

CGetHttpStrDlg::CGetHttpStrDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGetHttpStrDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGetHttpStrDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGetHttpStrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGetHttpStrDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGetHttpStrDlg, CDialog)
	//{{AFX_MSG_MAP(CGetHttpStrDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGetHttpStrDlg message handlers

BOOL CGetHttpStrDlg::OnInitDialog()
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

void CGetHttpStrDlg::OnPaint() 
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
HCURSOR CGetHttpStrDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CGetHttpStrDlg::OnOK() 
{
	//��������URL
	CString strUrl;
	GetDlgItemText(IDC_EDT_URL, strUrl);
	//����Internet�Ự
	CInternetSession   session(NULL,0);   
	CHttpFile*   file = NULL;   
	CString   strContent;  
	//��URL
	try
	{
		file = (CHttpFile*)session.OpenURL(strUrl);
	}
	catch (CInternetException *pException) 
	{
		pException->ReportError();
		pException->Delete();
		return;
	}
	//ѭ����ȡ����	
	CString strTemp;
	while(file->ReadString(strTemp))   
	{
		strContent += strTemp;
	}
	//�ͷ���Դ
	file->Close();
	delete file;
	session.Close();
	SetDlgItemText(IDC_EDT_CONTENT, strContent);
}
