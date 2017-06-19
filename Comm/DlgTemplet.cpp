// DlgTemplet.cpp: implementation of the CDlgTemplet class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "InputDlg_Demo.h"
#include <atlconv.h>
#include "DlgTemplet.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDlgTemplet::CDlgTemplet(UINT nBufLen)
{
	//��ʼ��������
	m_pBuffer   = new WORD[nBufLen];
	m_pNext     = m_pBuffer;
	m_pEndBuf   = m_pNext + nBufLen;
}

CDlgTemplet::~CDlgTemplet()
{
	//�ͷŻ�������Դ
	delete [] m_pBuffer;
}

//�����Ի���ģ��
DLGTEMPLATE* CDlgTemplet::Begin(DWORD dwStyle, const CRect& rcDlg,
	LPCTSTR lpText, DWORD dwStyleEx)
{
	DLGTEMPLATE* pTemplate = (DLGTEMPLATE*)m_pBuffer;
	//�Ի�������
	pTemplate->style = dwStyle;					 
	pTemplate->dwExtendedStyle = dwStyleEx;	 
	//��ʼ�ؼ���Ϊ0
	pTemplate->cdit = 0;
	//�Ի���λ�úʹ�С
	pTemplate->x  = (short)rcDlg.left;
	pTemplate->y  = (short)rcDlg.top;
	pTemplate->cx = (short)rcDlg.Width();
	pTemplate->cy = (short)rcDlg.Height();

	//�Ի���ģ��䳤�򣬰����˵����ࡢ����
	m_pNext = (WORD*)(pTemplate+1);
	*m_pNext++ = 0;							 // û�в˵�
	*m_pNext++ = 0;							 // ʹ��Ĭ�����
	m_pNext = AddText(m_pNext, lpText);		 // �Ի������

	ASSERT(m_pNext < m_pEndBuf);
	return pTemplate;
}

//��ӿؼ�
void CDlgTemplet::AddItem(WORD wType, DWORD dwStyle,
	const CRect& rc, LPCTSTR lpText, WORD nID, DWORD dwStyleEx)
{
	ASSERT(m_pNext < m_pEndBuf);
	//��ʼ���ؼ�ģ��
	DLGITEMTEMPLATE *pTemplate = (DLGITEMTEMPLATE*)AlignDWORD(m_pNext);
	//�ؼ����
	pTemplate->style = dwStyle;
	pTemplate->dwExtendedStyle = dwStyleEx;
	//λ�úͳߴ�
	pTemplate->x  = (short)rc.left;
	pTemplate->y  = (short)rc.top;
	pTemplate->cx = (short)rc.Width();
	pTemplate->cy = (short)rc.Height();
	//�ؼ�ID
	pTemplate->id = nID;

	//�Ի���ؼ�ģ��䳤�򣬰����������ı�����������
	m_pNext = (WORD*)(pTemplate+1);
	//��һ��WORD��ԭ��ֵ
	*m_pNext++ = 0xFFFF;
	//����ؼ�������ԭ��ֵ
	*m_pNext++ = wType;						 
	ASSERT(m_pNext < m_pEndBuf);	
	//�ı�
	m_pNext = AddText(m_pNext, lpText);
	//�޴�������
	*m_pNext++ = 0;
	ASSERT(m_pNext < m_pEndBuf);

	//�����Ի����ϵĿؼ�����һ
	((DLGTEMPLATE*)m_pBuffer)->cdit ++;
}

//�����ı������������ı�����ΪUNICODE����
WORD* CDlgTemplet::AddText(WORD* pBuf, LPCTSTR lpText)
{
	if (lpText && *lpText != _T('\0'))
	{
		//�����ǰ���̲���UNICODE���룬ת���ַ�
#ifndef UNICODE
		int nLen = _tcslen(lpText);
		WCHAR *pWbuf = new WCHAR[nLen];
		MultiByteToWideChar(CP_ACP, 0, lpText, -1, pWbuf, nLen);
		wcscpy((WCHAR*)pBuf, pWbuf);
		delete []pWbuf;
#else
		wcscpy((WCHAR*)pBuf, lpText);
#endif
		pBuf += wcslen((WCHAR*)pBuf)+1;
	} 
	else 
	{
		*pBuf++ = 0;
	}
	return pBuf;
}
