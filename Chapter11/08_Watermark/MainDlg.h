// MainDlg.h: interface for the CMainDlg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINDLG_H__0909FF99_73C7_4524_9F62_302DA853D0FF__INCLUDED_)
#define AFX_MAINDLG_H__0909FF99_73C7_4524_9F62_302DA853D0FF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\comm\mymemdc.h"

//�������������ַ���
#define MAX_CHARS 256
//����δ֪ö��
enum emTextSite
{
	//����
	TS_LeftTop = 0,
	//����
	TS_RightTop,
	//����
	TS_LeftBottom,
	//����
	TS_RightBottom,
	//�м�
	TS_Cent
};
//���Ի����������
class CMainDlg
{
public:
	CMainDlg();
	virtual ~CMainDlg();
	int DoModal();
protected:
	//�Ի������
	static int CALLBACK 
		DlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
	//��ʼ���Ի���
	BOOL OnInitDialog(HWND hWnd);
	//����ǰ��Ϣ
	void OnDestroy();
	//WM_COMMAND��Ϣ��Ӧ
	BOOL OnCommand(WPARAM wp, LPARAM lp);
	//����ʼ����ť��Ӧ����
	void OnOk();
	//���������ť����Ӧ����
	void OnBtnBrowse();
	//�����塱��ť����Ӧ����
	void OnBtnFont();
	//����ɫ����ť����Ӧ����
	void OnBtnColor();
	//ˮƽ��������Ϣ
	void OnHScroll(WPARAM wp, LPARAM lp);
	//��ĳ���ؼ�������Ϣ
	int  SendDlgMsg(int nID, UINT nMsg, WPARAM wp, LPARAM lp);
	//�����ļ�
	BOOL ProcessFile(LPCTSTR lpFile);
	//�����ļ���ʽ��ȡ�������CLSID
	BOOL FindEncoder(GUID *pFormat, CLSID* pClsid);
	//�����ʾ��Ϣ
	void OutStatusText(LPCTSTR lpMsg, ...);
	//��ȡ�������ı���ǰ�ַ���ʽ
	void GetRichEditCharFormat(CHARFORMAT2 *pCF);
	//����������ֻ��Ƶ��ڴ�λͼ��
	BOOL DrawRtfText();
protected:
	//�Ի�����
	HWND		m_hDlg;
	//Ӧ�ó���ͼ��
	HICON		m_hAppIcon;
	//�������ͼƬĿ¼
	TCHAR		m_szImagePath[MAX_PATH];
	//�������õ��ı�������Ϣ
	LOGFONT		m_logfont;
	//�������õ�������ɫ
	COLORREF	m_crText;
	//����Ҫ���Ƶ��ı�
	TCHAR		m_szText[MAX_CHARS + 2];
	//�������õ��ı�λ��
	UINT		m_nTextSite;
	//�������õ�͸����
	BYTE		m_nAlpha;
	//��Ż��ƺõ��ı�
	CMyMemDC	m_dc;
};

#endif // !defined(AFX_MAINDLG_H__0909FF99_73C7_4524_9F62_302DA853D0FF__INCLUDED_)
