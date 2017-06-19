// MainDlg.h: interface for the CMainDlg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINDLG_H__0909FF99_73C7_4524_9F62_302DA853D0FF__INCLUDED_)
#define AFX_MAINDLG_H__0909FF99_73C7_4524_9F62_302DA853D0FF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\comm\mymemdc.h"

//最多允许输入的字符数
#define MAX_CHARS 256
//文字未知枚举
enum emTextSite
{
	//左上
	TS_LeftTop = 0,
	//右上
	TS_RightTop,
	//左下
	TS_LeftBottom,
	//右下
	TS_RightBottom,
	//中间
	TS_Cent
};
//主对话框类的声明
class CMainDlg
{
public:
	CMainDlg();
	virtual ~CMainDlg();
	int DoModal();
protected:
	//对话框过程
	static int CALLBACK 
		DlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
	//初始化对话框
	BOOL OnInitDialog(HWND hWnd);
	//销毁前消息
	void OnDestroy();
	//WM_COMMAND消息响应
	BOOL OnCommand(WPARAM wp, LPARAM lp);
	//“开始”按钮响应函数
	void OnOk();
	//“浏览”按钮的响应函数
	void OnBtnBrowse();
	//“字体”按钮的响应函数
	void OnBtnFont();
	//“颜色”按钮的响应函数
	void OnBtnColor();
	//水平滚动条消息
	void OnHScroll(WPARAM wp, LPARAM lp);
	//向某个控件发送消息
	int  SendDlgMsg(int nID, UINT nMsg, WPARAM wp, LPARAM lp);
	//处理文件
	BOOL ProcessFile(LPCTSTR lpFile);
	//根据文件格式获取其编码器CLSID
	BOOL FindEncoder(GUID *pFormat, CLSID* pClsid);
	//输出提示信息
	void OutStatusText(LPCTSTR lpMsg, ...);
	//获取并保存文本框当前字符格式
	void GetRichEditCharFormat(CHARFORMAT2 *pCF);
	//将输入的文字绘制到内存位图中
	BOOL DrawRtfText();
protected:
	//对话框句柄
	HWND		m_hDlg;
	//应用程序图标
	HICON		m_hAppIcon;
	//所输入的图片目录
	TCHAR		m_szImagePath[MAX_PATH];
	//保存设置的文本字体信息
	LOGFONT		m_logfont;
	//保存设置的文字颜色
	COLORREF	m_crText;
	//保存要绘制的文本
	TCHAR		m_szText[MAX_CHARS + 2];
	//保存设置的文本位置
	UINT		m_nTextSite;
	//保存设置的透明度
	BYTE		m_nAlpha;
	//存放绘制好的文本
	CMyMemDC	m_dc;
};

#endif // !defined(AFX_MAINDLG_H__0909FF99_73C7_4524_9F62_302DA853D0FF__INCLUDED_)
