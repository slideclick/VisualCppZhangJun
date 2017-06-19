// CreateMdbDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CreateMdb.h"
#include "CreateMdbDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCreateMdbDlg dialog

CCreateMdbDlg::CCreateMdbDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCreateMdbDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCreateMdbDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCreateMdbDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCreateMdbDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCreateMdbDlg, CDialog)
	//{{AFX_MSG_MAP(CCreateMdbDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCreateMdbDlg message handlers

BOOL CCreateMdbDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	//初始化COM环境
	AfxOleInit();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCreateMdbDlg::OnPaint() 
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
HCURSOR CCreateMdbDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCreateMdbDlg::OnOK() 
{
	//浏览，并取得文件名
	CFileDialog dlg(FALSE, _T("*.mdb"), NULL, 
		OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY, 
		_T("*.mdb|*.mdb||"), this);
	if(dlg.DoModal() != IDOK)
		return;
	//生成连接字串
	CString strConn;
	strConn = _T("Provider=Microsoft.JET.OLEDB.4.0;Data source =");
	strConn += dlg.GetPathName();
	//生成创建表的SQL命令
	CString strSql = _T("CREATE TABLE Students(StudentID AUTOINCREMENT (1, 1) not null, ");
	strSql += _T("StudentName nvarchar(32) not null)");
	try
	{
		//创建空的数据库文件
		{
			ADOX::_CatalogPtr pCatalog = NULL;
			HRESULT hr = pCatalog.CreateInstance(__uuidof (ADOX::Catalog));
			if(FAILED(hr))
			{
				AfxMessageBox(_T("创建ADOX::Catalog对象实例失败。"));
				return ;
			}
			pCatalog->Create(_bstr_t(strConn));
		}
		//创建表
		_ConnectionPtr pConnection = NULL;
		pConnection.CreateInstance(__uuidof(Connection));
		pConnection->Open((LPCTSTR)strConn, "", "", adModeUnknown);
		_variant_t   ra;
		pConnection->Execute((LPCTSTR)strSql, &ra, adCmdText);
		pConnection->Close();
		AfxMessageBox(_T("创建数据库及表成功！"));
	}
	catch (_com_error &ex) 
	{
		AfxMessageBox(ex.Description());
	}
	catch(...)
	{
		AfxMessageBox(_T("未知错误"));
	}
}
