#pragma once

#include <shellapi.h>
#include <tchar.h>

class CTrayIcon
{
public:
	CTrayIcon(HWND hWnd, UINT uID, UINT nNotifyMsg, HICON hIcon = NULL, LPCTSTR lpTip = NULL);
	virtual ~CTrayIcon();
	//��ʾͼ��
	BOOL ShowIcon();	
	//����ͼ��
	BOOL HideIcon();
	//����ͼ��
	BOOL SetIcon(HICON hNewIcon);
	//������ʾ�ı�
	BOOL SetTipText(LPCTSTR lpNewTipText);
	//�Ƿ�ɼ�
	BOOL IsVisibled();
	//�ؽ�ͼ��
	BOOL Rebuild();
protected:
	//ͼ������
	NOTIFYICONDATA m_nidata;
	//ͼ��Ŀǰ�Ƿ���ʾ
	BOOL m_bVisibled;
	//֪ͨ��ϢID
	UINT m_uTrayNotifyMsg;
};

