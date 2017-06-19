// Ado_DemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Ado_Demo.h"
#include "Ado_DemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CAdo_DemoDlg dialog

CAdo_DemoDlg::CAdo_DemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAdo_DemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAdo_DemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAdo_DemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAdo_DemoDlg)
	DDX_Control(pDX, IDC_LIST, m_list);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAdo_DemoDlg, CDialog)
	//{{AFX_MSG_MAP(CAdo_DemoDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
	ON_BN_CLICKED(IDC_BTN_EDIT, OnBtnEdit)
	ON_BN_CLICKED(IDC_BTN_DELETE, OnBtnDelete)
	ON_WM_DESTROY()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, OnItemchangedList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAdo_DemoDlg message handlers

//获取某个路径的上层路径
void CAdo_DemoDlg::GetPathParent(LPTSTR lpPath, int nCount)
{
	TCHAR *p;
	while(nCount > 0)
	{
		p = _tcsrchr(lpPath, _T('\\'));
		if(p)
		{
			*p = _T('\0');
		}
		nCount --;
	}	
}
//从数据库获取数据，并显示在列表控件
void CAdo_DemoDlg::GetDataset()
{
	//从数据库读取记录
	LPCTSTR lpSql = _T("select * from Students order by StudentID");
	m_pRecordset->Open((_variant_t)lpSql,              
		m_pConnection.GetInterfacePtr(),	 
		adOpenDynamic,
		adLockOptimistic,
		adCmdText);
	if (m_pRecordset == NULL) 
	{
		AfxMessageBox(_T("读取数据库记录错误！"));
		return ;
	}
	m_list.DeleteAllItems();
	//将数据显示在列表控件	
	int nitem=0;
	_variant_t id, name;
	CString strID, strName;
	while(!m_pRecordset->adoEOF){
		id = m_pRecordset->GetCollect("StudentID");
		name = m_pRecordset->GetCollect("StudentName");
		
		strID.Format(_T("%d"), id.intVal);
		strName = (LPCTSTR)_bstr_t(name);
		
		m_list.InsertItem(nitem, strID);
		m_list.SetItemText(nitem, 1, strName);  //????
		m_list.SetItemData(nitem, id.intVal);
		
		nitem++;
		m_pRecordset->MoveNext();
	}	
	m_pRecordset->Close();
}
//执行无需返回值的SQL命令
void CAdo_DemoDlg::ExecuteSql(LPCTSTR lpSql)
{
	_variant_t   ra;
	try
	{
		m_pConnection->Execute(lpSql, &ra, adCmdText);
	}
	catch(_com_error &e)
	{
		AfxMessageBox((LPCTSTR)e.Description());
	}
	catch(...)
	{
		AfxMessageBox(_T("执行SQL语句时发生未知错误！"));
	}
}

BOOL CAdo_DemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	//初始化COM环境
	AfxOleInit();
	//初始化列表控件的列
	LV_COLUMN listColumn;
	TCHAR * listTitle [2] = {_T("学号"),_T("姓名")};
	int intColCx[2] = {100,120};
	listColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
	listColumn.fmt = LVCFMT_LEFT;
	for(int ncol=0;ncol<2;ncol++){
		listColumn.cx = intColCx[ncol];
		listColumn.iSubItem = ncol;
		listColumn.pszText = listTitle[ncol];
		m_list.InsertColumn(ncol,&listColumn);
	}
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT); 
	
	//初始化数据库连接对象
	TCHAR szPath[MAX_PATH] = {0};
	GetModuleFileName(NULL, szPath, MAX_PATH);
	GetPathParent(szPath, 3);
	_tcscat(szPath, _T("\\01_ODBC_Source\\MyAccess.mdb;"));
	m_pConnection.CreateInstance(__uuidof(Connection));
	CString strConn = _T("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=");
	strConn += szPath;
	try                 
	{	
		//打开Access数据库
		m_pConnection->Open((_bstr_t)strConn, "", "", adModeUnknown);
	}
	catch(_com_error &e)
	{
		AfxMessageBox((LPCTSTR)e.Description());
		m_pConnection = NULL;
		return TRUE;
	}
	catch(...){
		AfxMessageBox(_T("未知错误！"));
		m_pConnection = NULL;
		return TRUE;
	}
	//初始化记录集对象
	m_pRecordset.CreateInstance(__uuidof(Recordset));
	//从数据库取得数据
	GetDataset();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAdo_DemoDlg::OnPaint() 
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
HCURSOR CAdo_DemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
//添加记录
void CAdo_DemoDlg::OnBtnAdd() 
{
	//获取输入的内容
	int nID = GetDlgItemInt(IDC_EDT_ID);
	CString strName;
	GetDlgItemText(IDC_EDT_NAME, strName);
	if(strName.GetLength() == 0 || nID <= 0)
		return;
	//对特殊字符单引号做处理
	strName.Replace(_T("'"), _T("''"));
	//组合成SQL语句
	TCHAR szSql[1024] = {0};
	_stprintf(szSql, _T("insert into Students(StudentID, StudentName)values(%d, '%s')"), nID, (LPCTSTR)strName);
	//执行命令并更新列表控件
	ExecuteSql(szSql);
	GetDataset();
}
//编辑当前记录
void CAdo_DemoDlg::OnBtnEdit() 
{
	//获取输入的内容
	int nIndex = m_list.GetSelectionMark();
	if(nIndex < 0)
		return;
	int nID = m_list.GetItemData(nIndex);
	int nNewID = GetDlgItemInt(IDC_EDT_ID);
	CString strNewName;
	GetDlgItemText(IDC_EDT_NAME, strNewName);
	if(strNewName.GetLength() == 0 || nNewID <= 0)
		return;
	//对特殊字符单引号做处理
	strNewName.Replace(_T("'"), _T("''"));
	//生成编辑记录的SQL命令
	TCHAR szSql[1024] = {0};
	_stprintf(szSql, _T("update Students set StudentID=%d, StudentName='%s' where StudentID=%d"), nNewID, (LPCTSTR)strNewName, nID);
	//执行命令并更新列表控件
	ExecuteSql(szSql);
	GetDataset();
}
//删除当前记录
void CAdo_DemoDlg::OnBtnDelete() 
{
	//取得当前所选记录
	int nIndex = m_list.GetSelectionMark();
	if(nIndex < 0)
		return;
	//取得当前所选记录的学号字段值
	int nID = m_list.GetItemData(nIndex);
	//生成SQL命令
	TCHAR szSql[1024] = {0};
	_stprintf(szSql, _T("delete from Students where StudentID=%d"), nID);
	//执行命令并更新列表控件
	ExecuteSql(szSql);
	GetDataset();
}

void CAdo_DemoDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	//关闭数据库连接
	if(m_pConnection != NULL)
		if(m_pConnection->State)
			m_pConnection->Close();	
}

void CAdo_DemoDlg::OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	if(( pNMListView->uChanged & LVIF_STATE ) 
		&&( pNMListView->uNewState & LVIS_SELECTED ))	
	{
		//列表框当前选中项目改变时，更新文本框内容
		SetDlgItemText(IDC_EDT_ID, (m_list.GetItemText(pNMListView->iItem, 0)));
		SetDlgItemText(IDC_EDT_NAME, (m_list.GetItemText(pNMListView->iItem, 1)));
	}
	
	*pResult = 0;
}

