// TreeCtrlDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TreeCtrlDemo.h"
#include "TreeCtrlDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTreeCtrlDemoDlg dialog

CTreeCtrlDemoDlg::CTreeCtrlDemoDlg(CWnd* pParent /*=NULL*/)
: CDialog(CTreeCtrlDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTreeCtrlDemoDlg)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTreeCtrlDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTreeCtrlDemoDlg)
	DDX_Control(pDX, IDC_TREE, m_tree);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTreeCtrlDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CTreeCtrlDemoDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
	ON_BN_CLICKED(IDC_BTN_DELETE, OnBtnDelete)
	ON_BN_CLICKED(IDC_BTN_EDIT, OnBtnEdit)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE, OnSelchangedTree)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTreeCtrlDemoDlg message handlers

BOOL CTreeCtrlDemoDlg::OnInitDialog()
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

void CTreeCtrlDemoDlg::OnPaint() 
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
HCURSOR CTreeCtrlDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
//����ӡ���ť����Ӧ����
void CTreeCtrlDemoDlg::OnBtnAdd() 
{
	//��ȡ�û�����
	CString strText;
	GetDlgItemText(IDC_EDT_TEXT, strText);
	if(strText.GetLength() == 0)
	{
		AfxMessageBox(_T("�������ı���"));
		return;	
	}
	//��ȡ��ǰ��ѡ�ڵ�
	HTREEITEM hItem = m_tree.GetSelectedItem();
	//�����ǰû��ѡ�нڵ㣬����Ӹ��ڵ�
	if(hItem == NULL)
		hItem = TVI_ROOT;
	//�ڵ�����
	TVINSERTSTRUCT ts = {0};
	//�½ڵ�ĸ��ڵ�
	ts.hParent = hItem;
	//�½ڵ������ͬ���ڵ����
	ts.hInsertAfter = TVI_LAST;
	//�½ڵ���ı�
	ts.item.pszText = (LPTSTR)(LPCTSTR)strText;
	//���ı���Ա��Ч
	ts.item.mask = TVIF_TEXT;
	//����½ڵ�
	HTREEITEM hNewItem = m_tree.InsertItem(&ts);
	//ѡ���½ڵ�
	m_tree.SelectItem(hNewItem);
	//ȷ���½ڵ㴦�ڿ��ӷ�Χ��
	m_tree.EnsureVisible(hNewItem);
}
//��ɾ������ť����Ӧ����
void CTreeCtrlDemoDlg::OnBtnDelete() 
{
	//��ȡ��ǰ��ѡ�ڵ�
	HTREEITEM hItem = m_tree.GetSelectedItem();
	if(hItem == NULL)
	{
		AfxMessageBox(_T("��ѡ��һ���ڵ㣡"));
		return;	
	}
	//ȡ�ýڵ�ĸ��ڵ�
	HTREEITEM hParent = m_tree.GetParentItem(hItem);
	//ɾ���ڵ�
	m_tree.DeleteItem(hItem);
	//ѡ���丸�ڵ�
	m_tree.SelectItem(hParent);
}
//���޸ġ���ť����Ӧ����
void CTreeCtrlDemoDlg::OnBtnEdit() 
{
	//��ȡ��ǰѡ�еĽڵ�
	HTREEITEM hItem = m_tree.GetSelectedItem();
	if(hItem == NULL)
	{
		AfxMessageBox(_T("��ѡ��һ���ڵ㣡"));
		return;	
	}
	//��ȡ�û�����
	CString strText;
	GetDlgItemText(IDC_EDT_TEXT, strText);
	if(strText.GetLength() == 0)
	{
		AfxMessageBox(_T("�������ı���"));
		return;	
	}
	//�޸Ľڵ��ı�
	m_tree.SetItemText(hItem, strText);
}
//�ؼ���ǰ�ڵ�ı�ʱ����Ϣ����
void CTreeCtrlDemoDlg::OnSelchangedTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	//��ȡ��ǰ��ѡ�ڵ�
	HTREEITEM hItem = m_tree.GetSelectedItem();
	if(hItem != NULL)
	{
		//��ȡ�ڵ��ı�
		CString strText = m_tree.GetItemText(hItem);
		//���ڵ��ı���ʾ���ı�����
		SetDlgItemText(IDC_EDT_TEXT, strText);
	}
	*pResult = 0;
}
