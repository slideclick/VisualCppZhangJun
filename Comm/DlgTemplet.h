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
	// Windows Ԥ�����ԭ��ֵ
	enum { BUTTON=0x0080, EDIT, STATIC, LISTBOX, SCROLLBAR, COMBOBOX};
	DLGTEMPLATE* Begin(DWORD dwStyle, const CRect& rcDlg, LPCTSTR caption, DWORD dwStyleEx=0);
	void AddItem(WORD wType, DWORD dwStyle, const CRect& rc,
		LPCTSTR lpText, WORD nID=-1, DWORD dwStyleEx=0);
protected:
	WORD* m_pBuffer;	//�Ի���ģ�滺����
	WORD* m_pNext;		//��̬����ʱ����ʱ����ָ��
	WORD* m_pEndBuf;	//�������Ľ�����
	
	//����ָ��ʵ�ú���
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
