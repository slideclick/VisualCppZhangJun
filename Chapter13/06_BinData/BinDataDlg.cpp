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
	//������ʼ��
	*m_szPhoto = _T('\0');
	m_hPhoto = NULL;
	GetModuleFileName(NULL, m_szTempPath, MAX_PATH);
	GetPathParent(m_szTempPath, 1);
	_tcscat(m_szTempPath, _T("\\temp.bmp"));
	//��ʼ��COM����
	AfxOleInit();
	//��ʼ���б�ؼ�����
	LV_COLUMN listColumn;
	TCHAR * listTitle [2] = {_T("ѧ��"),_T("����")};
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
	
	//��ʼ�����ݿ����Ӷ���
	TCHAR szPath[MAX_PATH] = {0};
	GetModuleFileName(NULL, szPath, MAX_PATH);
	GetPathParent(szPath, 2);
	_tcscat(szPath, _T("\\MyAccessEx.mdb;"));
	m_pConnection.CreateInstance(__uuidof(Connection));
	CString strConn = _T("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=");
	strConn += szPath;
	try                 
	{	
		//��Access���ݿ�
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
	//�����ݿ�ȡ������
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
//��ͼƬ��ʾ��ͼƬ�ؼ���
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
//��ȡĳ��·�����ϲ�·��
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
//�����ݿ��ȡ���ݣ�����ʾ���б�ؼ�
void CBinDataDlg::GetDataset()
{
	//�����ݿ��ȡ��¼
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
		AfxMessageBox(_T("��ȡ���ݿ��¼����"));
		return ;
	}
	m_list.DeleteAllItems();
	//��������ʾ���б�ؼ�	
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
//�ͷų��������д�����GDI����
void CBinDataDlg::FreeGdiObject()
{
	if(m_hPhoto != NULL)
	{
		DeleteObject(m_hPhoto);
		m_hPhoto = NULL;
	}
}

//�����ݿ��ȡĳ����¼
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
			m_pConnection.GetInterfacePtr(),	 // ��ȡ��ӿ��IDispatchָ��
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
		AfxMessageBox(_T("δ֪����!"));
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
			//�õ�ָ�����ݵ�ָ��
			byte *pTemp;
			HRESULT hr = SafeArrayAccessData(varBLOB.parray,(void **)&pTemp);              
			//���浽�ļ�
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

//�����ݱ��浽���ݿ�
void CBinDataDlg::SaveRecordPhoto(int nID)
{
	//��ȡ�û�����
	int nNewID = GetDlgItemInt(IDC_EDT_ID);
	CString strNewName;
	GetDlgItemText(IDC_EDT_NAME, strNewName);
	ASSERT(nNewID > 0 && strNewName.GetLength() > 0 && _tcslen(m_szPhoto) > 0);
	//�����ݿ�ȡ��Ҫ�༭�����ݣ�������½���ȡ��һ���յļ�¼��
	CString strSql;
	strSql.Format(_T("select * from Students where StudentID=%d"), nID);
	_RecordsetPtr pRecordset;
	pRecordset.CreateInstance(__uuidof(Recordset));
	try
	{
		//�򿪼�¼��
		pRecordset->Open((_variant_t)strSql,              
			m_pConnection.GetInterfacePtr(),	 // ��ȡ��ӿ��IDispatchָ��
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
		AfxMessageBox(_T("δ֪����!"));
		return ;
	}
	//��ͼƬ��ȡ���ڴ�
	CFile file(m_szPhoto, CFile::modeRead);
	DWORD dwLen = file.GetLength();
	byte *pBuf = new byte[dwLen];
	file.ReadHuge(pBuf, dwLen);
	file.Close();

	//������ID����0ʱ����༭������������
	if(nID == 0)
	{
		pRecordset->AddNew();
	}
	else
	{
		pRecordset->MoveFirst();
		ASSERT(!pRecordset->adoEOF);
	}
	//����ѧ�ź�����
	pRecordset->PutCollect(_T("StudentID"), (long)nNewID);
	pRecordset->PutCollect(_T("StudentName"), (LPCTSTR)strNewName);
	//������Ƭ
	VARIANT  varBLOB;
	SAFEARRAY *psa;
	SAFEARRAYBOUND sab[1];
	sab[0].lLbound = 0;
	sab[0].cElements = dwLen;
	//����SAFEARRAY����
	psa = SafeArrayCreate(VT_UI1, 1, sab);                      
	//���ڴ��е����ݱ��浽SAFEARRAY������
	byte *p = pBuf;
	for (LONG i = 0; i < dwLen; i++)
		SafeArrayPutElement (psa, &i, p++); 
	//��������ΪBYTE�͵�����
	varBLOB.vt = VT_UI1 | VT_ARRAY; 
	//ΪvarBLOB������ֵ
	varBLOB.parray = psa;
	//�����ݱ��浽��¼��
	pRecordset->GetFields()->GetItem("StudentPhoto")->AppendChunk(varBLOB);
	//�ͷ���ʱ������ڴ�
	SafeArrayDestroy(psa);
	delete []pBuf;

	try
	{
		//��������µ����ݿ�
		pRecordset->Update();
		pRecordset->Close();
	}
	catch(_com_error &e)
	{
		AfxMessageBox((LPCTSTR)e.Description());
	}
	catch(...)
	{
		AfxMessageBox(_T("δ֪����!"));
	}
}
//��Ӽ�¼
void CBinDataDlg::OnBtnAdd() 
{
	SaveRecordPhoto(0);
	GetDataset();
}
//�༭��ǰ��¼
void CBinDataDlg::OnBtnEdit() 
{
	//�õ���ǰList��ѡ��
	int nIndex = m_list.GetSelectionMark();
	if(nIndex < 0)
		return;
	//�õ���ǰ��ѡ��ѧ��
	int nID = m_list.GetItemData(nIndex);
	//������Ϣ
	SaveRecordPhoto(nID);
	GetDataset();
}
//ѡ��ͼƬ
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
	//�ر����ݿ�����
	if(m_pConnection != NULL)
	{
		if(m_pConnection->State)
			m_pConnection->Close();	
	}
	//�ͷ�GDI����
	FreeGdiObject();	
}

void CBinDataDlg::OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if(( pNMListView->uChanged & LVIF_STATE ) 
		&&( pNMListView->uNewState & LVIS_SELECTED ))	
	{
		//�б��ǰѡ����Ŀ�ı�ʱ�������ı�������
		SetDlgItemText(IDC_EDT_ID, (m_list.GetItemText(pNMListView->iItem, 0)));
		SetDlgItemText(IDC_EDT_NAME, (m_list.GetItemText(pNMListView->iItem, 1)));
		//��ȡͼƬ
		ReadRecordPhoto(m_list.GetItemData(pNMListView->iItem));
	}
	
	*pResult = 0;
}
