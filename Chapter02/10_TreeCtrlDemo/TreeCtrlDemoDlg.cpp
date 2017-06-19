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
//“添加”按钮的响应函数
void CTreeCtrlDemoDlg::OnBtnAdd() 
{
	//获取用户输入
	CString strText;
	GetDlgItemText(IDC_EDT_TEXT, strText);
	if(strText.GetLength() == 0)
	{
		AfxMessageBox(_T("请输入文本！"));
		return;	
	}
	//获取当前所选节点
	HTREEITEM hItem = m_tree.GetSelectedItem();
	//如果当前没有选中节点，则添加根节点
	if(hItem == NULL)
		hItem = TVI_ROOT;
	//节点数据
	TVINSERTSTRUCT ts = {0};
	//新节点的父节点
	ts.hParent = hItem;
	//新节点添加在同级节点最后
	ts.hInsertAfter = TVI_LAST;
	//新节点的文本
	ts.item.pszText = (LPTSTR)(LPCTSTR)strText;
	//让文本成员有效
	ts.item.mask = TVIF_TEXT;
	//添加新节点
	HTREEITEM hNewItem = m_tree.InsertItem(&ts);
	//选中新节点
	m_tree.SelectItem(hNewItem);
	//确保新节点处于可视范围内
	m_tree.EnsureVisible(hNewItem);
}
//“删除”按钮的响应函数
void CTreeCtrlDemoDlg::OnBtnDelete() 
{
	//获取当前所选节点
	HTREEITEM hItem = m_tree.GetSelectedItem();
	if(hItem == NULL)
	{
		AfxMessageBox(_T("请选择一个节点！"));
		return;	
	}
	//取得节点的父节点
	HTREEITEM hParent = m_tree.GetParentItem(hItem);
	//删除节点
	m_tree.DeleteItem(hItem);
	//选中其父节点
	m_tree.SelectItem(hParent);
}
//“修改”按钮的响应函数
void CTreeCtrlDemoDlg::OnBtnEdit() 
{
	//获取当前选中的节点
	HTREEITEM hItem = m_tree.GetSelectedItem();
	if(hItem == NULL)
	{
		AfxMessageBox(_T("请选择一个节点！"));
		return;	
	}
	//获取用户输入
	CString strText;
	GetDlgItemText(IDC_EDT_TEXT, strText);
	if(strText.GetLength() == 0)
	{
		AfxMessageBox(_T("请输入文本！"));
		return;	
	}
	//修改节点文本
	m_tree.SetItemText(hItem, strText);
}
//控件当前节点改变时的消息处理
void CTreeCtrlDemoDlg::OnSelchangedTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	//获取当前所选节点
	HTREEITEM hItem = m_tree.GetSelectedItem();
	if(hItem != NULL)
	{
		//获取节点文本
		CString strText = m_tree.GetItemText(hItem);
		//将节点文本显示在文本框中
		SetDlgItemText(IDC_EDT_TEXT, strText);
	}
	*pResult = 0;
}
