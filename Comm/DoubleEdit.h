// DoubleEdit.h: interface for the CDoubleEdit class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DOUBLEEDIT_H__D94A05BE_24BE_4B77_80BB_98021847C52C__INCLUDED_)
#define AFX_DOUBLEEDIT_H__D94A05BE_24BE_4B77_80BB_98021847C52C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <tchar.h>
#include <math.h>
#include <stdio.h>

//dobule�ı�����ඨ��
class CDoubleEdit  
{
public:
	CDoubleEdit();
	virtual ~CDoubleEdit();
	//������Ϳؼ�
	BOOL Attach(HWND hWnd);
	//ȡ������
	void Detach();
	//��ȡ���������
	BOOL GetDoubleValue(double *pValue);
	//��ȡ������ı�
	BOOL GetStringValue(LPTSTR lpBuffer, int nLen);
protected:
	//�µĴ������
	static LRESULT APIENTRY NewEditProc(HWND hWnd, UINT uMsg, WPARAM wp, LPARAM lp);
protected:
	HWND m_hWnd;
	long m_lOldProc;
};

#endif // !defined(AFX_DOUBLEEDIT_H__D94A05BE_24BE_4B77_80BB_98021847C52C__INCLUDED_)
