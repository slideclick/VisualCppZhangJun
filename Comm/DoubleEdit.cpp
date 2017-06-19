// DoubleEdit.cpp: implementation of the CDoubleEdit class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DoubleEdit.h"

//存放控件类指针的属性值
#define DOUBLE_EDIT_PROP_NAME _T("Double_Edit_Prop_Name")

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDoubleEdit::CDoubleEdit(): m_hWnd(NULL), m_lOldProc(0)
{
}

CDoubleEdit::~CDoubleEdit()
{
	Detach();
}

BOOL CDoubleEdit::Attach(HWND hWnd)
{
	//将类和控件关联
	if(m_hWnd != NULL)
	{
		DebugBreak();
		return FALSE;
	}

	m_hWnd = hWnd;
	SetProp(hWnd, DOUBLE_EDIT_PROP_NAME, this);
	//修改控件过程为新的处理过程
	m_lOldProc = SetWindowLong(hWnd, GWL_WNDPROC, (long)NewEditProc);
	if (m_lOldProc == 0)
	{
		m_hWnd = NULL;
		return FALSE;
	}
	else
		return TRUE;
}

void CDoubleEdit::Detach()
{
	//恢复控件默认处理过程，取消类和控件的关联
	if(m_hWnd == NULL)
		return;
	SetWindowLong(m_hWnd, GWL_WNDPROC, m_lOldProc);
	m_hWnd = NULL;
	m_lOldProc = 0;
}

BOOL CDoubleEdit::GetDoubleValue(double *pValue)
{
	//获取所输入的double值
	TCHAR szBuf[32];
	if(GetStringValue(szBuf, 32))
	{
		*pValue = atof(szBuf);
		return TRUE;
	}
	else
		return FALSE;
}

BOOL CDoubleEdit::GetStringValue(LPTSTR lpBuffer, int nLen)
{
	//获取所输入的文本值
	return GetWindowText(m_hWnd, lpBuffer, nLen);
}

LRESULT APIENTRY CDoubleEdit::NewEditProc(HWND hWnd, UINT uMsg, WPARAM wp, LPARAM lp) 
{
	//新的处理过程
	CDoubleEdit *pEdit = (CDoubleEdit *)GetProp(hWnd, DOUBLE_EDIT_PROP_NAME);
	if (pEdit == NULL)
	{
		return DefWindowProc(hWnd, uMsg, wp, lp);
	}

	//处理按键消息，忽略不符合要求的按键
	BOOL bCanceled = FALSE;
	if (uMsg == WM_CHAR) 
	{
		TCHAR szBuf[32] = {0};
		pEdit->GetStringValue(szBuf, 32);
		switch(wp)
		{
		case '.':
			//限制只能输入一个小数点
			if(_tcschr(szBuf, '.'))
			{
				bCanceled = TRUE;
			}
			break;
		case '-':
			//限制只能输入一个负号，并且只能是第一个字符
			if(_tcschr(szBuf, '-'))
			{
				bCanceled = TRUE;
			}
			else if (LOWORD(SendMessage(hWnd, EM_GETSEL, 0, 0)) != 0)
			{
				bCanceled = TRUE;
			}
			break;
		default:
			//限制只能输入0-9之间的字符
			if ((wp > '9' || wp < '0') && wp != VK_BACK)
			{
				bCanceled = TRUE;
			}
			break;
		}
		if (bCanceled) 
		{
			//对于不符合要求的字符输入，直接返回
			MessageBeep(-1);
			return 0;
		}
	}
	//其余消息均采用默认处理
	return CallWindowProc((WNDPROC)pEdit->m_lOldProc, hWnd, uMsg, wp, lp); 
}
