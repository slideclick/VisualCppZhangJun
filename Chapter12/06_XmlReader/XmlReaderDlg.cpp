// XmlReaderDlg.cpp : implementation file
//

#include "stdafx.h"
#include "XmlReader.h"
#include "XmlReaderDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXmlReaderDlg dialog

CXmlReaderDlg::CXmlReaderDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CXmlReaderDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CXmlReaderDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CXmlReaderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CXmlReaderDlg)
	DDX_Control(pDX, IDC_TREE, m_tree);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CXmlReaderDlg, CDialog)
	//{{AFX_MSG_MAP(CXmlReaderDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXmlReaderDlg message handlers

BOOL CXmlReaderDlg::OnInitDialog()
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

void CXmlReaderDlg::OnPaint() 
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
HCURSOR CXmlReaderDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CXmlReaderDlg::OnOK() 
{
	CFileDialog dlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST, _T("*.xml|*.xml|*.*|*.*||"), this);
	if (dlg.DoModal() != IDOK)
		return;
	
	IXMLDOMDocumentPtr pXmlDoc;
	HRESULT hr;
	hr = pXmlDoc.CreateInstance(MSXML::CLSID_DOMDocument);
	if (FAILED(hr)) 
	{
		AfxMessageBox(_T("无法创建Xml对象实例。"));
		return ;
	}
	if(!pXmlDoc->load((LPCTSTR)dlg.GetPathName()) )
	{
		AfxMessageBox(_T("无法加载Xml文件。"));
		return ;
	}
	//获取Xml文件首个元素
	IXMLDOMElementPtr pRoot = pXmlDoc->GetdocumentElement();
	if(pRoot != NULL)
	{
		//将元素显示在tree控件中
		HTREEITEM hItem = m_tree.InsertItem(pRoot->GetnodeName());
		//获取所有的子节点
		IXMLDOMNodeListPtr pNodes = pRoot->GetchildNodes();
		for(int i=0; i<pNodes->Getlength(); i++)
		{
			//将节点及其下所有子节点显示在tree中
			IXMLDOMNodePtr pNode = pNodes->nextNode();
			if(pNode != NULL)
			{
				AddTreeNodes(pNode, hItem);
			}
		}
	}
	return ;
}

void CXmlReaderDlg::AddTreeNodes(IXMLDOMNodePtr pXmlNode, HTREEITEM hTreeItem)
{
	_bstr_t str;
	//获取节点的子节点
	IXMLDOMNodeListPtr pNodes = pXmlNode->GetchildNodes();
	if(pNodes != NULL && pNodes->Getlength() > 0)
	{
		//如果节点有子节点，则递归显示
		str = pXmlNode->GetnodeName();
		HTREEITEM hItem = m_tree.InsertItem(str, hTreeItem);
		long len = pNodes->Getlength();
		for(long i=0; i<len; i++)
		{
			IXMLDOMNodePtr pNode = pNodes->nextNode();
			if(pNode != NULL)
			{
				AddTreeNodes(pNode, hItem);
			}
		}
	}
	else
	{
		//如果节点没有子节点，则显示其文本
		str = pXmlNode->Gettext();
		if(str.length() == 0)
			str = pXmlNode->GetnodeName();
		m_tree.InsertItem(str, hTreeItem);
	}
}
//保存XML文件
void CXmlReaderDlg::OnSave() 
{
	HTREEITEM hItem = m_tree.GetRootItem();
	if(hItem == NULL)
		return;
	//得到要保存的文件名
	CFileDialog dlg(
		FALSE, _T("xml"), NULL, OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT, 
		_T("*.xml|*.xml|*.*|*.*||"), this);
	if(dlg.DoModal() != IDOK)
		return;
	//创建XML对象
	IXMLDOMDocumentPtr pXmlDoc;
	HRESULT hr;
	hr = pXmlDoc.CreateInstance(MSXML::CLSID_DOMDocument);
	if (FAILED(hr)) 
	{
		AfxMessageBox(_T("无法创建Xml对象实例。"));
		return ;
	} 
	//添加编码方式等
	IXMLDOMProcessingInstructionPtr pPro;
	pPro = pXmlDoc->createProcessingInstruction(_T("xml"), _T("version='1.0' encoding='gb2312'"));
	pXmlDoc->appendChild(pPro);
	//创建根元素
	_bstr_t name = (LPCTSTR)m_tree.GetItemText(hItem);
	IXMLDOMElementPtr pRoot = pXmlDoc->createElement(name);
	pXmlDoc->appendChild(pRoot);
	//递归将将根元素添加到Xml文档
	AddXmlNodes(pRoot, hItem);
	//保存文件
	hr = pXmlDoc->save((LPCTSTR)dlg.GetPathName());
	if(FAILED(hr))
		AfxMessageBox(_T("保存Xml文件时出错。"));	
}
//添加xml节点的递归函数
void CXmlReaderDlg::AddXmlNodes(IXMLDOMElementPtr pXmlNode, HTREEITEM hTreeItem)
{
	HTREEITEM hItem = m_tree.GetChildItem(hTreeItem);
	if(hItem == NULL)
	{
		//如果树节点无子节点，则当前树节点为xml文本
		pXmlNode->Puttext((LPCTSTR)m_tree.GetItemText(hTreeItem));
	}
	else
	{
		//如果树节点有子节点，则当前树节点为xml中的节点
		while(hItem != NULL)
		{
			//递归添加子节点
			HTREEITEM hChild = m_tree.GetChildItem(hItem);
			if(hChild != NULL)
			{
				IXMLDOMElementPtr pNode;
				_bstr_t name = (LPCTSTR)m_tree.GetItemText(hItem);
				pNode = pXmlNode->GetownerDocument()->createElement(name);
				pXmlNode->appendChild(pNode);
				AddXmlNodes(pNode, hItem);
			}
			else
				AddXmlNodes(pXmlNode, hItem);
			hItem = m_tree.GetNextSiblingItem(hItem);
		}
	}
}
//为Tree Control添加节点
void CXmlReaderDlg::OnAdd() 
{
	//获取文本
	CString str;
	GetDlgItemText(IDC_EDT_TEXT, str);
	if(str.GetLength() == 0)
		return;
	//得到当前所选树节点
	HTREEITEM hItem = m_tree.GetSelectedItem();
	if(hItem == NULL)
		hItem = TVI_ROOT;
	//添加节点
	hItem = m_tree.InsertItem(str, hItem);
	m_tree.SelectItem(hItem);
}
