// BinDataDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BinData.h"
#include "BinDataDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBinDataDlg dialog

CBinDataDlg::CBinDataDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBinDataDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBinDataDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBinDataDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBinDataDlg)
	DDX_Control(pDX, IDC_LIST, m_list);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBinDataDlg, CDialog)
	//{{AFX_MSG_MAP(CBinDataDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
	ON_BN_CLICKED(IDC_BTN_EDIT, OnBtnEdit)
	ON_BN_CLICKED(IDC_BTN_BROWSE, OnBtnBrowse)
	ON_WM_DESTROY()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, OnItemchangedList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBinDataDlg message handlers

BOOL CBinDataDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	//变量初始化
	*m_szPhoto = _T('\0');
	m_hPhoto = NULL;
	GetModuleFileName(NULL, m_szTempPath, MAX_PATH);
	GetPathParent(m_szTempPath, 1);
	_tcscat(m_szTempPath, _T("\\temp.bmp"));
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
	GetPathParent(szPath, 2);
	_tcscat(szPath, _T("\\MyAccessEx.mdb;"));
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
	catch(...)
	{
		AfxMessageBox(_T("未知错误！"));
		m_pConnection = NULL;
		return TRUE;
	}
	//从数据库取得数据
	GetDataset();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBinDataDlg::OnPaint() 
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
HCURSOR CBinDataDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
//将图片显示在图片控件上
void CBinDataDlg::ShowImage(LPCTSTR lpFilename)
{
	FreeGdiObject();
	if(*lpFilename > 0)
	{
		m_hPhoto = (HBITMAP)LoadImage(NULL, lpFilename, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		((CStatic *)GetDlgItem(IDC_PHOTO))->SetBitmap(m_hPhoto);
		_tcscpy(m_szPhoto, lpFilename);
	}
	this->Invalidate(FALSE);
}
//获取某个路径的上层路径
void CBinDataDlg::GetPathParent(LPTSTR lpPath, int nCount)
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
void CBinDataDlg::GetDataset()
{
	//从数据库读取记录
	LPCTSTR lpSql = _T("select StudentID, StudentName from Students order by StudentID");

	_RecordsetPtr pRecordset;
	pRecordset.CreateInstance(__uuidof(Recordset));	
	pRecordset->Open((_variant_t)lpSql,              
		m_pConnection.GetInterfacePtr(),	 
		adOpenDynamic,
		adLockOptimistic,
		adCmdText);
	if (pRecordset == NULL) 
	{
		AfxMessageBox(_T("读取数据库记录错误！"));
		return ;
	}
	m_list.DeleteAllItems();
	//将数据显示在列表控件	
	int nitem=0;
	_variant_t id, name;
	CString strID, strName;
	while(!pRecordset->adoEOF){
		id = pRecordset->GetCollect("StudentID");
		name = pRecordset->GetCollect("StudentName");
		
		strID.Format(_T("%d"), id.intVal);
		strName = (LPCTSTR)_bstr_t(name);
		
		m_list.InsertItem(nitem, strID);
		m_list.SetItemText(nitem, 1, strName);  //????
		m_list.SetItemData(nitem, id.intVal);
		
		nitem++;
		pRecordset->MoveNext();
	}	
	pRecordset->Close();
}
//释放程序运行中创建的GDI对象
void CBinDataDlg::FreeGdiObject()
{
	if(m_hPhoto != NULL)
	{
		DeleteObject(m_hPhoto);
		m_hPhoto = NULL;
	}
}

//从数据库读取某条记录
void CBinDataDlg::ReadRecordPhoto(int nID)
{
	*m_szPhoto = _T('\0');
	
	_variant_t   ra;
	CString strSql;
	strSql.Format(_T("select StudentPhoto from Students where StudentID=%d"), nID); 

	_RecordsetPtr pRecordset;
	pRecordset.CreateInstance(__uuidof(Recordset));	
	try
	{
		pRecordset->Open((_variant_t)strSql,              
			m_pConnection.GetInterfacePtr(),	 // 获取库接库的IDispatch指针
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);
	}
	catch(_com_error &e)
	{
		AfxMessageBox((LPCTSTR)e.Description());
		return ;
	}
	catch(...){
		AfxMessageBox(_T("未知错误!"));
		return ;
	}
	
	pRecordset->MoveFirst();
	if(!pRecordset->adoEOF)
	{
		LONG lLen = pRecordset->GetFields()->GetItem("StudentPhoto")->ActualSize;
		if(lLen > 0)
		{
			_variant_t varBLOB = pRecordset->GetFields()->
				GetItem("StudentPhoto")->GetChunk(lLen);
			SetCursor(AfxGetApp()->LoadStandardCursor(IDC_WAIT));
			//得到指向数据的指针
			byte *pTemp;
			HRESULT hr = SafeArrayAccessData(varBLOB.parray,(void **)&pTemp);              
			//保存到文件
			CFile file(m_szTempPath, CFile::modeCreate|CFile::modeWrite);
			file.WriteHuge(pTemp, lLen);
			file.Close();
			SafeArrayUnaccessData (varBLOB.parray);
			
			SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW)); 			
		}
	}
	pRecordset->Close();
	ShowImage(m_szTempPath);
}

//将数据保存到数据库
void CBinDataDlg::SaveRecordPhoto(int nID)
{
	//获取用户输入
	int nNewID = GetDlgItemInt(IDC_EDT_ID);
	CString strNewName;
	GetDlgItemText(IDC_EDT_NAME, strNewName);
	ASSERT(nNewID > 0 && strNewName.GetLength() > 0 && _tcslen(m_szPhoto) > 0);
	//从数据库取得要编辑的数据，如果是新建，取得一个空的记录集
	CString strSql;
	strSql.Format(_T("select * from Students where StudentID=%d"), nID);
	_RecordsetPtr pRecordset;
	pRecordset.CreateInstance(__uuidof(Recordset));
	try
	{
		//打开记录集
		pRecordset->Open((_variant_t)strSql,              
			m_pConnection.GetInterfacePtr(),	 // 获取库接库的IDispatch指针
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);
	}
	catch(_com_error &e)
	{
		AfxMessageBox((LPCTSTR)e.Description());
		return ;
	}
	catch(...)
	{
		AfxMessageBox(_T("未知错误!"));
		return ;
	}
	//将图片读取至内存
	CFile file(m_szPhoto, CFile::modeRead);
	DWORD dwLen = file.GetLength();
	byte *pBuf = new byte[dwLen];
	file.ReadHuge(pBuf, dwLen);
	file.Close();

	//传来的ID大于0时代表编辑，否则代表添加
	if(nID == 0)
	{
		pRecordset->AddNew();
	}
	else
	{
		pRecordset->MoveFirst();
		ASSERT(!pRecordset->adoEOF);
	}
	//设置学号和姓名
	pRecordset->PutCollect(_T("StudentID"), (long)nNewID);
	pRecordset->PutCollect(_T("StudentName"), (LPCTSTR)strNewName);
	//设置照片
	VARIANT  varBLOB;
	SAFEARRAY *psa;
	SAFEARRAYBOUND sab[1];
	sab[0].lLbound = 0;
	sab[0].cElements = dwLen;
	//创建SAFEARRAY对象
	psa = SafeArrayCreate(VT_UI1, 1, sab);                      
	//将内存中的数据保存到SAFEARRAY对象中
	byte *p = pBuf;
	for (LONG i = 0; i < dwLen; i++)
		SafeArrayPutElement (psa, &i, p++); 
	//数据类型为BYTE型的数组
	varBLOB.vt = VT_UI1 | VT_ARRAY; 
	//为varBLOB变量赋值
	varBLOB.parray = psa;
	//将数据保存到记录集
	pRecordset->GetFields()->GetItem("StudentPhoto")->AppendChunk(varBLOB);
	//释放临时申请的内存
	SafeArrayDestroy(psa);
	delete []pBuf;

	try
	{
		//将结果更新到数据库
		pRecordset->Update();
		pRecordset->Close();
	}
	catch(_com_error &e)
	{
		AfxMessageBox((LPCTSTR)e.Description());
	}
	catch(...)
	{
		AfxMessageBox(_T("未知错误!"));
	}
}
//添加记录
void CBinDataDlg::OnBtnAdd() 
{
	SaveRecordPhoto(0);
	GetDataset();
}
//编辑当前记录
void CBinDataDlg::OnBtnEdit() 
{
	//得到当前List所选项
	int nIndex = m_list.GetSelectionMark();
	if(nIndex < 0)
		return;
	//得到当前所选的学号
	int nID = m_list.GetItemData(nIndex);
	//更新信息
	SaveRecordPhoto(nID);
	GetDataset();
}
//选择图片
void CBinDataDlg::OnBtnBrowse() 
{
	CFileDialog dlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST, _T("*.bmp|*.bmp||"), this);
	if(dlg.DoModal() == IDOK)
	{
		ShowImage(dlg.GetPathName());
	}
}

void CBinDataDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	//关闭数据库连接
	if(m_pConnection != NULL)
	{
		if(m_pConnection->State)
			m_pConnection->Close();	
	}
	//释放GDI对象
	FreeGdiObject();	
}

void CBinDataDlg::OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if(( pNMListView->uChanged & LVIF_STATE ) 
		&&( pNMListView->uNewState & LVIS_SELECTED ))	
	{
		//列表框当前选中项目改变时，更新文本框内容
		SetDlgItemText(IDC_EDT_ID, (m_list.GetItemText(pNMListView->iItem, 0)));
		SetDlgItemText(IDC_EDT_NAME, (m_list.GetItemText(pNMListView->iItem, 1)));
		//读取图片
		ReadRecordPhoto(m_list.GetItemData(pNMListView->iItem));
	}
	
	*pResult = 0;
}
