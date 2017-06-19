// ResStr.h: interface for the CResStr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RESSTR_H__5B9A5ABA_06DF_4CC0_B8FA_434074761995__INCLUDED_)
#define AFX_RESSTR_H__5B9A5ABA_06DF_4CC0_B8FA_434074761995__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CResStr  
{
public:
	operator LPCTSTR ();
	CResStr(HINSTANCE hInst, UINT uID, UINT uLen);
	CResStr(HINSTANCE hInst, UINT uID);
	virtual ~CResStr();
protected:
	inline void LoadStr(HINSTANCE hInst, UINT uID, UINT uLen);
	TCHAR * m_pBuf;
};

#endif // !defined(AFX_RESSTR_H__5B9A5ABA_06DF_4CC0_B8FA_434074761995__INCLUDED_)
