// ResStr.cpp: implementation of the CResStr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ResStr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CResStr::CResStr(HINSTANCE hInst, UINT uID)
{
	//使用默认缓冲长度加载资源
	LoadStr(hInst, uID, 128);
}
CResStr::CResStr(HINSTANCE hInst, UINT uID, UINT uLen)
{
	//使用指定缓冲长度加载资源
	LoadStr(hInst, uID, uLen);	
}
CResStr::~CResStr()
{
	//释放缓冲区
	if (m_pBuf != NULL) 
	{
		delete []m_pBuf;
		m_pBuf = NULL;
	}
}
//从资源中加载字符串
inline void CResStr::LoadStr(HINSTANCE hInst, UINT uID, UINT uLen)
{
	//创建缓冲区
	m_pBuf = new TCHAR[uLen + 1] ;
	*m_pBuf = 0;
	//加载资源
	LoadString(hInst, uID, m_pBuf, uLen);
}
//LPCTSTR操作符
CResStr::operator LPCTSTR()
{
	//返回缓冲区地址
	return m_pBuf;
}