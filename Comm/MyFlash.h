// MyFlash.h: interface for the CMyFlash class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYFLASH_H__F012226A_DA2D_48A1_BC29_D691A2284831__INCLUDED_)
#define AFX_MYFLASH_H__F012226A_DA2D_48A1_BC29_D691A2284831__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//注意，在编译代码之前，请先修改以下路径，
//使其指向本机实际的OCX文件路径
#import "d:\windows\system32\macromed\flash\flash9e.ocx"
using namespace ShockwaveFlashObjects;

class CMyFlash  
{
public:
	CMyFlash();
	virtual ~CMyFlash();
	//创建控件
	BOOL Create(HWND hParent);
	//销毁控件
	void Destroy();
	//加载影片
	BOOL LoadMovie(LPCTSTR lpFile);
	//移动控件位置
	void Move(LPCRECT lprc);
	//开始播放
	BOOL Play();
	//停止播放
	BOOL Stop();
protected:
	HWND m_hParent;
	HWND m_hWnd;
	CAxWindow m_wndContainer;
	CComPtr<IShockwaveFlash> m_pFlash;
};

#endif // !defined(AFX_MYFLASH_H__F012226A_DA2D_48A1_BC29_D691A2284831__INCLUDED_)
