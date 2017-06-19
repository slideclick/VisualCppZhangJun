// ODBC_SourceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ODBC_Source.h"
#include "ODBC_SourceDlg.h"
//ODBC API��ͷ�ļ�
#include "ODBCINST.H"
//ODBC API�Ŀ��ļ�
#pragma comment(lib, "ODBCCP32.LIB")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CODBC_SourceDlg dialog

CODBC_SourceDlg::CODBC_SourceDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CODBC_SourceDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CODBC_SourceDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CODBC_SourceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CODBC_SourceDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CODBC_SourceDlg, CDialog)
	//{{AFX_MSG_MAP(CODBC_SourceDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_BROWSE, OnBtnBrowse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CODBC_SourceDlg message handlers

BOOL CODBC_SourceDlg::OnInitDialog()
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

void CODBC_SourceDlg::OnPaint() 
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
HCURSOR CODBC_SourceDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CODBC_SourceDlg::OnBtnBrowse() 
{
	//�������ȡ���ݿ��ļ�·��
	CFileDialog dlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST, _T("*.mdb|*.mdb||"), this);
	if(dlg.DoModal() != IDOK)
		return;
	CString strFile = dlg.GetPathName();
	SetDlgItemText(IDC_EDT_FILE, strFile);
}

void CODBC_SourceDlg::OnOK() 
{
	//�õ����ݿ��ļ�·��
	CString strFile;
	GetDlgItemText(IDC_EDT_FILE, strFile);
	//���ݿ�ע��˵��
	TCHAR szBuf[2048] = {0};
	_stprintf(szBuf, _T("DSN=%s|DBQ=%s|"), _T("MyAccessDB"), (LPCTSTR)strFile);
	//˵���У�ÿ������'\0'�ָ����滻�ַ����е�'|'Ϊ'\0'
	LPTSTR p = szBuf;
	while(*p != 0)
	{
		if(*p == _T('|'))
			*p = _T('\0');
		p ++;
	}
	//���ODBC����Դ
	BOOL bAdd = SQLConfigDataSource(
		NULL, 
		//��ϵͳ�������Դ
		ODBC_ADD_DSN,  
		//���ݿ�����ΪAccess���ݿ�
		_T("Microsoft Access Driver (*.mdb)"), 
		szBuf);	
	if(!bAdd)
	{
		DWORD dwErr = GetLastError();
		_stprintf(szBuf, _T("��������Դʧ�ܣ��������Ϊ0x%.8X��"), dwErr);
		MessageBox(szBuf);
	}
	else
		MessageBox(_T("��������Դ�ɹ�"));
}
