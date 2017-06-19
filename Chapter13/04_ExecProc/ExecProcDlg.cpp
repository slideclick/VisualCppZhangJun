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
	//初始化COM环境
	AfxOleInit();
	//初始化数据库连接对象
	m_pConnection.CreateInstance(__uuidof(Connection));
	CString strConn = _T("Driver={SQL Server};Server=127.0.0.1;Database=MyDB;Uid=Test;Pwd=;");
	try                 
	{	
		//打开数据库连接
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
		AfxMessageBox(_T("未知错误！"));
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
//通过Connection对象调用存储过程
void CExecProcDlg::OnBtnExec1() 
{
	_variant_t   ra;
	//生成SQL命令
	LPCTSTR lpSql = _T("exec GetSum 5, 8, '使用Connection对象'");
	try
	{
		//以命令方式执行存储过程，并取得返回的结果集
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
		AfxMessageBox(_T("发生未知错误！"));
	}
}
//通过Command对象调用存储过程
void CExecProcDlg::OnBtnExec2() 
{
	_CommandPtr pCmd; 
	HRESULT hr = pCmd.CreateInstance(__uuidof(Command));  
	if(FAILED(hr))  
	{   
		AfxMessageBox("创建Command对象失败");   
		return ;  
	}
	//第一个参数，9
	_ParameterPtr pParam = pCmd->CreateParameter(_T(""), adInteger, adParamInput, sizeof(int), _variant_t((long)9));
	pCmd->Parameters->Append(pParam);
	//第二个参数，6
	pParam = pCmd->CreateParameter(_T(""), adInteger, adParamInput, sizeof(int), _variant_t((long)6));
	pCmd->Parameters->Append(pParam);
	//第三个参数，说明
	LPCTSTR lpDesc = _T("使用Command对象");
	pParam = pCmd->CreateParameter(_T(""), adVarChar, adParamInput, sizeof(TCHAR) * (_tcslen(lpDesc) + 1), _variant_t(lpDesc));
	pCmd->Parameters->Append(pParam);
	//命令，输入存储过程的名称
	pCmd->CommandText=_bstr_t("GetSum");
	//Command对象所使用的连接
	pCmd->ActiveConnection = m_pConnection;
	//命令类型
	pCmd->CommandType = adCmdStoredProc;

	try
	{
		//执行，并取得返回的结果集
		_RecordsetPtr pRecordset = pCmd->Execute(NULL, NULL, adCmdStoredProc);
		if (pRecordset == NULL) 
		{
			AfxMessageBox(_T("无法取得结果集！"));
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
		AfxMessageBox(_T("发生未知错误！"));
	}
	pCmd = NULL;
}

void CExecProcDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	//关闭数据库连接
	if(m_pConnection != NULL)
		if(m_pConnection->State)
			m_pConnection->Close();
	
}
