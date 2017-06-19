// TransExecDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TransExec.h"
#include "TransExecDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTransExecDlg dialog

CTransExecDlg::CTransExecDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTransExecDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTransExecDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTransExecDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTransExecDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTransExecDlg, CDialog)
	//{{AFX_MSG_MAP(CTransExecDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTransExecDlg message handlers

BOOL CTransExecDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	//��ʼ��COM����
	AfxOleInit();
	//��ʼ�����ݿ����Ӷ���
	m_pConnection.CreateInstance(__uuidof(Connection));
	CString strConn = _T("Driver={SQL Server};Server=127.0.0.1;Database=MyDB;Uid=Test;Pwd=;");
	try                 
	{	
		//�����ݿ�����
		m_pConnection->Open((_bstr_t)strConn, "", "", adModeUnknown);
	}
	catch(_com_error &e)
	{
		AfxMessageBox((LPCTSTR)e.Description());
		m_pConnection = NULL;
		return TRUE;
	}
	catch(...)
	{
		AfxMessageBox(_T("δ֪����"));
		m_pConnection = NULL;
		return TRUE;
	}
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTransExecDlg::OnPaint() 
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
HCURSOR CTransExecDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTransExecDlg::OnBtnAdd() 
{
	if(m_pConnection == NULL)
	{
		AfxMessageBox(_T("���ȴ����ݿ�����"));
		return;
	}
	//ȡ����������
	CString strID, strName, strAge, strSex;
	GetDlgItemText(IDC_EDT_ID, strID);
	GetDlgItemText(IDC_EDT_NAME, strName);
	GetDlgItemText(IDC_EDT_AGE, strAge);
	GetDlgItemText(IDC_EDT_SEX, strSex);
	//���ɲ�ѯ���
	CString strStep1, strStep2;
	//��һ�β�ѯ��SQL���
	strStep1.Format(
		_T("insert into StudentList(StudentID, StudentName)values(%s, '%s')"), 
		strID, strName);
	//�ڶ��β�ѯ��SQL���
	strStep2.Format(
		_T("insert into StudentDetail(StudentID, StudentAge, StudentSex)values(%s, %s, '%s')"), 
		strID, strAge, strSex);
	//��ʼ����
	m_pConnection->BeginTrans();
	BOOL bOk = FALSE;
	_variant_t   ra;
	try
	{
		//�ύ2��SQL���
		m_pConnection->Execute((LPCTSTR)strStep1, &ra, adCmdText);
		m_pConnection->Execute((LPCTSTR)strStep2, &ra, adCmdText);
		bOk = TRUE;
	}
	catch(_com_error &e)
	{
		AfxMessageBox((LPCTSTR)e.Description());
	}
	catch(...)
	{
		AfxMessageBox(_T("δ֪����"));
	}
	if(bOk)
	{
		//���û�г����ύ����������
		m_pConnection->CommitTrans();
		AfxMessageBox(_T("ִ������ɹ��������������ύ��"));
	}
	else
	{
		//������ֹ����󣬻ع�����������
		m_pConnection->RollbackTrans();
		AfxMessageBox(_T("ִ������ʧ�ܣ����������ѻع���"));
	}
}

void CTransExecDlg::OnDestroy() 
{
	CDialog::OnDestroy();	
	//�ر����ݿ�����
	if(m_pConnection != NULL)
	{
		if(m_pConnection->State)
			m_pConnection->Close();
		m_pConnection = NULL;
	}
}
