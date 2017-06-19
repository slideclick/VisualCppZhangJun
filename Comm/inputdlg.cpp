// InputDlg1.cpp : implementation file
//

#include "stdafx.h"
#include "InputDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInputDlg dialog


CInputDlg::CInputDlg(CWnd* pParent, LPCTSTR lpTitle, LPCTSTR lpTip, LPCTSTR lpDef)
{
	if(lpDef != NULL)
		m_strInput = lpDef;

	CRect rc(0, 0, 200, 75);
	DLGTEMPLATE* pTempl = m_templet.Begin(WS_POPUPWINDOW|DS_MODALFRAME|WS_DLGFRAME, &rc, lpTitle);
	//图标
	rc.SetRect(10, 10, 40, 40);
	m_templet.AddItem(CDlgTemplet::STATIC, WS_VISIBLE|WS_TABSTOP|SS_ICON, rc, NULL, IDC_STATIC_ICON);
	//提示文本
	rc.SetRect(50, 10, 190, 25);
	m_templet.AddItem(CDlgTemplet::STATIC, WS_VISIBLE|WS_TABSTOP, rc, lpTip, IDC_STATIC);
	//输入框
	rc.SetRect(50, 25, 190, 40);
	m_templet.AddItem(CDlgTemplet::EDIT, WS_VISIBLE|WS_TABSTOP|WS_BORDER, rc, _T(""), IDC_EDT_INPUT);
	//确定按钮
	rc.SetRect(90, 50, 130, 65);
	m_templet.AddItem(CDlgTemplet::BUTTON, WS_VISIBLE|WS_TABSTOP, rc, _T("确定"), IDOK);
	//取消按钮
	rc.SetRect(150, 50, 190, 65);
	m_templet.AddItem(CDlgTemplet::BUTTON, WS_VISIBLE|WS_TABSTOP, rc, _T("取消"), IDCANCEL);
	//初始化对话框模版
	InitModalIndirect(pTempl, pParent);
}

LPCTSTR CInputDlg::GetInputText()
{
	//返回输入文本
	return m_strInput;
}

BOOL CInputDlg::OnInitDialog()
{
	//设置图标
	CStatic *pIcon = (CStatic *)GetDlgItem(IDC_STATIC_ICON);
	pIcon->SetIcon(LoadIcon(NULL, IDI_INFORMATION));
	//设置焦点到文本框
	GetDlgItem(IDC_EDT_INPUT)->SetFocus();
	SetDlgItemText(IDC_EDT_INPUT, m_strInput);
	return TRUE;
}

void CInputDlg::OnOK()
{
	//获取输入，结束对话框
	GetDlgItemText(IDC_EDT_INPUT, m_strInput);
	CDialog::OnOK();
}
