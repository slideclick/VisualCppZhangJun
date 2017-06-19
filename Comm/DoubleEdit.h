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

//dobule文本框的类定义
class CDoubleEdit  
{
public:
	CDoubleEdit();
	virtual ~CDoubleEdit();
	//关联类和控件
	BOOL Attach(HWND hWnd);
	//取消关联
	void Detach();
	//获取输入的数字
	BOOL GetDoubleValue(double *pValue);
	//获取输入的文本
	BOOL GetStringValue(LPTSTR lpBuffer, int nLen);
protected:
	//新的处理过程
	static LRESULT APIENTRY NewEditProc(HWND hWnd, UINT uMsg, WPARAM wp, LPARAM lp);
protected:
	HWND m_hWnd;
	long m_lOldProc;
};

#endif // !defined(AFX_DOUBLEEDIT_H__D94A05BE_24BE_4B77_80BB_98021847C52C__INCLUDED_)
