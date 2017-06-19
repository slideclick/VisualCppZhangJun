// ExecProcDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ExecProc.h"
#include "ExecProcDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExecProcDlg dialog

CExecProcDlg::CExecProcDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CExecProcDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CExecProcDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExecProcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CExecProcDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CExecProcDlg, CDialog)
	//{{AFX_MSG_MAP(CExecProcDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_EXEC1, OnBtnExec1)
	ON_BN_CLICKED(IDC_BTN_EXEC2, OnBtnExec2)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExecProcDlg message handlers

BOOL CExecProcDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
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

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CExecProcDlg::OnPaint() 
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
HCURSOR CExecProcDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
//ͨ��Connection������ô洢����
void CExecProcDlg::OnBtnExec1() 
{
	_variant_t   ra;
	//����SQL����
	LPCTSTR lpSql = _T("exec GetSum 5, 8, 'ʹ��Connection����'");
	try
	{
		//�����ʽִ�д洢���̣���ȡ�÷��صĽ����
		_RecordsetPtr pRecordset = m_pConnection->Execute(lpSql, &ra, adCmdText);
		pRecordset->MoveFirst();
		_variant_t ret = pRecordset->GetCollect(_T("ret"));
		SetDlgItemText(IDC_EDT_RESULT, (LPCTSTR)_bstr_t(ret));
	}
	catch(_com_error &e)
	{
		AfxMessageBox((LPCTSTR)e.Description());
	}
	catch(...)
	{
		AfxMessageBox(_T("����δ֪����"));
	}
}
//ͨ��Command������ô洢����
void CExecProcDlg::OnBtnExec2() 
{
	_CommandPtr pCmd; 
	HRESULT hr = pCmd.CreateInstance(__uuidof(Command));  
	if(FAILED(hr))  
	{   
		AfxMessageBox("����Command����ʧ��");   
		return ;  
	}
	//��һ��������9
	_ParameterPtr pParam = pCmd->CreateParameter(_T(""), adInteger, adParamInput, sizeof(int), _variant_t((long)9));
	pCmd->Parameters->Append(pParam);
	//�ڶ���������6
	pParam = pCmd->CreateParameter(_T(""), adInteger, adParamInput, sizeof(int), _variant_t((long)6));
	pCmd->Parameters->Append(pParam);
	//������������˵��
	LPCTSTR lpDesc = _T("ʹ��Command����");
	pParam = pCmd->CreateParameter(_T(""), adVarChar, adParamInput, sizeof(TCHAR) * (_tcslen(lpDesc) + 1), _variant_t(lpDesc));
	pCmd->Parameters->Append(pParam);
	//�������洢���̵�����
	pCmd->CommandText=_bstr_t("GetSum");
	//Command������ʹ�õ�����
	pCmd->ActiveConnection = m_pConnection;
	//��������
	pCmd->CommandType = adCmdStoredProc;

	try
	{
		//ִ�У���ȡ�÷��صĽ����
		_RecordsetPtr pRecordset = pCmd->Execute(NULL, NULL, adCmdStoredProc);
		if (pRecordset == NULL) 
		{
			AfxMessageBox(_T("�޷�ȡ�ý������"));
		}
		else
		{
			pRecordset->MoveFirst();
			_variant_t ret = pRecordset->GetCollect(_T("ret"));
			SetDlgItemText(IDC_EDT_RESULT, (LPCTSTR)_bstr_t(ret));			
		}
	}
	catch(_com_error &e)
	{
		AfxMessageBox((LPCTSTR)e.Description());
	}
	catch(...)
	{
		AfxMessageBox(_T("����δ֪����"));
	}
	pCmd = NULL;
}

void CExecProcDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	//�ر����ݿ�����
	if(m_pConnection != NULL)
		if(m_pConnection->State)
			m_pConnection->Close();
	
}
