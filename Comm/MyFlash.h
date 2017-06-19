// MyFlash.h: interface for the CMyFlash class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYFLASH_H__F012226A_DA2D_48A1_BC29_D691A2284831__INCLUDED_)
#define AFX_MYFLASH_H__F012226A_DA2D_48A1_BC29_D691A2284831__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//ע�⣬�ڱ������֮ǰ�������޸�����·����
//ʹ��ָ�򱾻�ʵ�ʵ�OCX�ļ�·��
#import "d:\windows\system32\macromed\flash\flash9e.ocx"
using namespace ShockwaveFlashObjects;

class CMyFlash  
{
public:
	CMyFlash();
	virtual ~CMyFlash();
	//�����ؼ�
	BOOL Create(HWND hParent);
	//���ٿؼ�
	void Destroy();
	//����ӰƬ
	BOOL LoadMovie(LPCTSTR lpFile);
	//�ƶ��ؼ�λ��
	void Move(LPCRECT lprc);
	//��ʼ����
	BOOL Play();
	//ֹͣ����
	BOOL Stop();
protected:
	HWND m_hParent;
	HWND m_hWnd;
	CAxWindow m_wndContainer;
	CComPtr<IShockwaveFlash> m_pFlash;
};

#endif // !defined(AFX_MYFLASH_H__F012226A_DA2D_48A1_BC29_D691A2284831__INCLUDED_)
