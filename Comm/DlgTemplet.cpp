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
	//初始化缓冲区
	m_pBuffer   = new WORD[nBufLen];
	m_pNext     = m_pBuffer;
	m_pEndBuf   = m_pNext + nBufLen;
}

CDlgTemplet::~CDlgTemplet()
{
	//释放缓冲区资源
	delete [] m_pBuffer;
}

//创建对话框模板
DLGTEMPLATE* CDlgTemplet::Begin(DWORD dwStyle, const CRect& rcDlg,
	LPCTSTR lpText, DWORD dwStyleEx)
{
	DLGTEMPLATE* pTemplate = (DLGTEMPLATE*)m_pBuffer;
	//对话框属性
	pTemplate->style = dwStyle;					 
	pTemplate->dwExtendedStyle = dwStyleEx;	 
	//初始控件数为0
	pTemplate->cdit = 0;
	//对话框位置和大小
	pTemplate->x  = (short)rcDlg.left;
	pTemplate->y  = (short)rcDlg.top;
	pTemplate->cx = (short)rcDlg.Width();
	pTemplate->cy = (short)rcDlg.Height();

	//对话框模板变长域，包括菜单、类、标题
	m_pNext = (WORD*)(pTemplate+1);
	*m_pNext++ = 0;							 // 没有菜单
	*m_pNext++ = 0;							 // 使用默认类别
	m_pNext = AddText(m_pNext, lpText);		 // 对话框标题

	ASSERT(m_pNext < m_pEndBuf);
	return pTemplate;
}

//添加控件
void CDlgTemplet::AddItem(WORD wType, DWORD dwStyle,
	const CRect& rc, LPCTSTR lpText, WORD nID, DWORD dwStyleEx)
{
	ASSERT(m_pNext < m_pEndBuf);
	//初始化控件模板
	DLGITEMTEMPLATE *pTemplate = (DLGITEMTEMPLATE*)AlignDWORD(m_pNext);
	//控件风格
	pTemplate->style = dwStyle;
	pTemplate->dwExtendedStyle = dwStyleEx;
	//位置和尺寸
	pTemplate->x  = (short)rc.left;
	pTemplate->y  = (short)rc.top;
	pTemplate->cx = (short)rc.Width();
	pTemplate->cy = (short)rc.Height();
	//控件ID
	pTemplate->id = nID;

	//对话框控件模板变长域，包括类名、文本、创建数据
	m_pNext = (WORD*)(pTemplate+1);
	//下一个WORD是原子值
	*m_pNext++ = 0xFFFF;
	//代表控件类名的原子值
	*m_pNext++ = wType;						 
	ASSERT(m_pNext < m_pEndBuf);	
	//文本
	m_pNext = AddText(m_pNext, lpText);
	//无创建数据
	*m_pNext++ = 0;
	ASSERT(m_pNext < m_pEndBuf);

	//整个对话框上的控件数加一
	((DLGTEMPLATE*)m_pBuffer)->cdit ++;
}

//保存文本到缓冲区，文本必须为UNICODE编码
WORD* CDlgTemplet::AddText(WORD* pBuf, LPCTSTR lpText)
{
	if (lpText && *lpText != _T('\0'))
	{
		//如果当前工程不是UNICODE编码，转换字符
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
