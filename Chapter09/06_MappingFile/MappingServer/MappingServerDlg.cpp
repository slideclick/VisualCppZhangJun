// MappingServerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MappingServer.h"
#include "MappingServerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MY_MAPPING_NAME _T("My_Maping_File_Name")
#define MAX_MAPPING_SIZE (1024*1024)
/////////////////////////////////////////////////////////////////////////////
// CMappingServerDlg dialog

CMappingServerDlg::CMappingServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMappingServerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMappingServerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hFile = NULL;
}

void CMappingServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMappingServerDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMappingServerDlg, CDialog)
	//{{AFX_MSG_MAP(CMappingServerDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMappingServerDlg message handlers

BOOL CMappingServerDlg::OnInitDialog()
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

void CMappingServerDlg::OnPaint() 
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
HCURSOR CMappingServerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMappingServerDlg::OnOK() 
{
	if(!m_hFile)
	{
		//�����ڴ�ӳ���ļ�
		m_hFile = CreateFileMapping(
			INVALID_HANDLE_VALUE,
			NULL,
			PAGE_READWRITE,
			0, 
			MAX_MAPPING_SIZE, 
			MY_MAPPING_NAME);
	}
	if(!m_hFile)
	{
		AfxMessageBox(_T("�����ڴ�ӳ���ļ�ʧ�ܣ�"));
		return;
	}
	//�õ��ڴ��ļ����ֽڵ�ַ
	LPTSTR lpStr = (LPTSTR)MapViewOfFile(
		m_hFile, FILE_MAP_WRITE, 0, 0, 0);
	if(!lpStr)
	{
		AfxMessageBox(_T("��ȡ�ļ��׵�ַʧ�ܣ�"));
		return;
	}
	//���Ի���������д���ڴ�ӳ���ļ�
	GetDlgItemText(IDC_EDT_CONTENT, lpStr, 
		MAX_MAPPING_SIZE / sizeof(TCHAR) - 1);
	//����ӳ��
	UnmapViewOfFile(lpStr);
	//��������ı���
	SetDlgItemText(IDC_EDT_CONTENT, NULL);
}

void CMappingServerDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	//�ͷ��ļ�
	CloseHandle(m_hFile);
}
