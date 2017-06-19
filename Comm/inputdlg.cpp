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
	//ͼ��
	rc.SetRect(10, 10, 40, 40);
	m_templet.AddItem(CDlgTemplet::STATIC, WS_VISIBLE|WS_TABSTOP|SS_ICON, rc, NULL, IDC_STATIC_ICON);
	//��ʾ�ı�
	rc.SetRect(50, 10, 190, 25);
	m_templet.AddItem(CDlgTemplet::STATIC, WS_VISIBLE|WS_TABSTOP, rc, lpTip, IDC_STATIC);
	//�����
	rc.SetRect(50, 25, 190, 40);
	m_templet.AddItem(CDlgTemplet::EDIT, WS_VISIBLE|WS_TABSTOP|WS_BORDER, rc, _T(""), IDC_EDT_INPUT);
	//ȷ����ť
	rc.SetRect(90, 50, 130, 65);
	m_templet.AddItem(CDlgTemplet::BUTTON, WS_VISIBLE|WS_TABSTOP, rc, _T("ȷ��"), IDOK);
	//ȡ����ť
	rc.SetRect(150, 50, 190, 65);
	m_templet.AddItem(CDlgTemplet::BUTTON, WS_VISIBLE|WS_TABSTOP, rc, _T("ȡ��"), IDCANCEL);
	//��ʼ���Ի���ģ��
	InitModalIndirect(pTempl, pParent);
}

LPCTSTR CInputDlg::GetInputText()
{
	//���������ı�
	return m_strInput;
}

BOOL CInputDlg::OnInitDialog()
{
	//����ͼ��
	CStatic *pIcon = (CStatic *)GetDlgItem(IDC_STATIC_ICON);
	pIcon->SetIcon(LoadIcon(NULL, IDI_INFORMATION));
	//���ý��㵽�ı���
	GetDlgItem(IDC_EDT_INPUT)->SetFocus();
	SetDlgItemText(IDC_EDT_INPUT, m_strInput);
	return TRUE;
}

void CInputDlg::OnOK()
{
	//��ȡ���룬�����Ի���
	GetDlgItemText(IDC_EDT_INPUT, m_strInput);
	CDialog::OnOK();
}
