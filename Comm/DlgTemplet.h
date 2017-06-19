// DlgTemplet.h: interface for the CDlgTemplet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DLGTEMPLET_H__03D4FB4C_FD5B_429E_9906_C8AACD5EDFD2__INCLUDED_)
#define AFX_DLGTEMPLET_H__03D4FB4C_FD5B_429E_9906_C8AACD5EDFD2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDlgTemplet  
{
public:
	CDlgTemplet(UINT nBufLen=1024);
	virtual ~CDlgTemplet();
	// Windows 预定义的原子值
	enum { BUTTON=0x0080, EDIT, STATIC, LISTBOX, SCROLLBAR, COMBOBOX};
	DLGTEMPLATE* Begin(DWORD dwStyle, const CRect& rcDlg, LPCTSTR caption, DWORD dwStyleEx=0);
	void AddItem(WORD wType, DWORD dwStyle, const CRect& rc,
		LPCTSTR lpText, WORD nID=-1, DWORD dwStyleEx=0);
protected:
	WORD* m_pBuffer;	//对话框模版缓冲区
	WORD* m_pNext;		//动态创建时的临时缓冲指针
	WORD* m_pEndBuf;	//缓冲区的结束点
	
	//对齐指针实用函数
	WORD* AlignDWORD(WORD* ptr) 
	{
		ptr++;			 
		LPARAM lp = (LPARAM)ptr; 
		lp &= 0xFFFFFFFC;
		return (WORD*)lp;
	}
	WORD* AddText(WORD* pBuf, LPCTSTR lpText);
};

#endif // !defined(AFX_DLGTEMPLET_H__03D4FB4C_FD5B_429E_9906_C8AACD5EDFD2__INCLUDED_)
