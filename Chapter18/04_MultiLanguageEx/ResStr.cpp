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
	//ʹ��Ĭ�ϻ��峤�ȼ�����Դ
	LoadStr(hInst, uID, 128);
}
CResStr::CResStr(HINSTANCE hInst, UINT uID, UINT uLen)
{
	//ʹ��ָ�����峤�ȼ�����Դ
	LoadStr(hInst, uID, uLen);	
}
CResStr::~CResStr()
{
	//�ͷŻ�����
	if (m_pBuf != NULL) 
	{
		delete []m_pBuf;
		m_pBuf = NULL;
	}
}
//����Դ�м����ַ���
inline void CResStr::LoadStr(HINSTANCE hInst, UINT uID, UINT uLen)
{
	//����������
	m_pBuf = new TCHAR[uLen + 1] ;
	*m_pBuf = 0;
	//������Դ
	LoadString(hInst, uID, m_pBuf, uLen);
}
//LPCTSTR������
CResStr::operator LPCTSTR()
{
	//���ػ�������ַ
	return m_pBuf;
}