// MainDlg.h: interface for the CMainDlg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINDLG_H__0909FF99_73C7_4524_9F62_302DA853D0FF__INCLUDED_)
#define AFX_MAINDLG_H__0909FF99_73C7_4524_9F62_302DA853D0FF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "cap.h"

class CMainDlg: public IMediaReceiver
{
public:
	CMainDlg();
	virtual ~CMainDlg();
	int DoModal();
public: //IMediaReceiverʵ��
	//������Ƶͼ��
	void OnUpdateVideo(const BITMAPINFO *pBmi, const BYTE *pBuf);
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
	//��ˢ���豸����ť��Ӧ����
	void OnGetDevices();
	//����ʼ����ť��Ӧ����
	void OnOk();
	//����ͼ����ť��Ӧ����
	void OnSnapshot();
	//WM_SIZE��Ϣ��Ӧ
	void OnSize(WPARAM wp, LPARAM lp);
	//����Ļ����ת��Ϊ��������
	void ScreenToClientRect(LPRECT prc);
	//�����ͼ�ļ�
	void SaveSnapshotImage(const BITMAPINFOHEADER *pbih, const BYTE *pBuf);
	//��ֹ������Ի����ϵĿؼ�
	void EnableDlgItem(UINT nID, BOOL bEnable);
protected:
	//��Ƶ�ɼ�����
	CCap  m_cap;
	//�Ի�����
	HWND  m_hDlg;
	//��Ƶ��ʾ�ؼ����
	HWND  m_hVideo;
	//��Ƶ�豸�б���
	HWND  m_hDeviceList;
	//�Ի���ԭʼ�ߴ�
	SIZE  m_siDlg;
	//��ǰ�ѽ�ͼ����
	int   m_nSnapshotNum;
	//�ܵĽ�ͼ����
	int   m_nSnapshotCount;
	//����ͼʱ��
	DWORD m_dwLastSnapshot;
	//��ͼ���
	DWORD m_dwSnapshotInterval;
	//��ͼ����·��
	TCHAR m_szSnapshotPath[MAX_PATH];
	//Ӧ�ó���ͼ��
	HICON m_hAppIcon;
};

#endif // !defined(AFX_MAINDLG_H__0909FF99_73C7_4524_9F62_302DA853D0FF__INCLUDED_)
