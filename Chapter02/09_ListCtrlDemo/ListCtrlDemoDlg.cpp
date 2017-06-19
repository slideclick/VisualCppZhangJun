// ListCtrlDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ListCtrlDemo.h"
#include "ListCtrlDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListCtrlDemoDlg dialog

CListCtrlDemoDlg::CListCtrlDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CListCtrlDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CListCtrlDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CListCtrlDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CListCtrlDemoDlg)
	DDX_Control(pDX, IDC_LIST, m_list);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CListCtrlDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CListCtrlDemoDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
	ON_BN_CLICKED(IDC_BTN_DELETE, OnBtnDelete)
	ON_CBN_SELCHANGE(IDC_CMB_VIEW, OnSelchangeCmbView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListCtrlDemoDlg message handlers

BOOL CListCtrlDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	//为列表控件添加列
	m_list.InsertColumn(0, _T("第1列"), LVCFMT_LEFT, 100);
	m_list.InsertColumn(1, _T("第2列"), LVCFMT_LEFT, 100);
	//创建图片列表
	m_images.Create(32, 32, ILC_COLOR32, 1, 1);
	//在图片列表中添加一个图标
	m_images.Add(m_hIcon);
	//将图片列表和对话框上的列表控件关联
	m_list.SetImageList(&m_images, LVSIL_SMALL);
	m_list.SetImageList(&m_images, LVSIL_NORMAL);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CListCtrlDemoDlg::OnPaint() 
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
HCURSOR CListCtrlDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
//“添加行”按钮的响应函数
void CListCtrlDemoDlg::OnBtnAdd() 
{
	int nCount = m_list.GetItemCount();
	TCHAR szText[128] = {0};
	_stprintf(szText, _T("第%d行第1列"), nCount + 1);
	m_list.InsertItem(nCount, szText, 0);
	_stprintf(szText, _T("第%d行第2列"), nCount + 1);
	m_list.SetItemText(nCount, 1, szText);
}
//“删除行”按钮的响应函数
void CListCtrlDemoDlg::OnBtnDelete() 
{
	//获取总行数
	int nCount = m_list.GetItemCount() - 1;
	//循环，从下网上删除选中的行
	for(int i=nCount; i>=0; i--)
	{
		if(m_list.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
			m_list.DeleteItem(i);
	}
}
//组合框选项改变消息的响应函数
void CListCtrlDemoDlg::OnSelchangeCmbView() 
{
	DWORD dwStyle;
	//取得控件
	CComboBox *pView;
	pView = (CComboBox *)GetDlgItem(IDC_CMB_VIEW);
	//根据控件当前所选，得到列表框新的显示风格
	switch(pView->GetCurSel()) 
	{
	case 0:		//大图标
		dwStyle = LVS_ICON;
		break;
	case 1:		//小图标
		dwStyle = LVS_SMALLICON;
		break;
	case 2:		//列表
		dwStyle = LVS_LIST;
		break;
	case 3:		//详细资料
		dwStyle = LVS_REPORT;
		break;
	default:
		return;
	}
	//应用新的风格
	m_list.ModifyStyle(LVS_TYPEMASK, dwStyle);
}
