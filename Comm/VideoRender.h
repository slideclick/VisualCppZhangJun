// VideoRender.h: interface for the CVideoRender class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VIDEORENDER_H__1EDB4C90_1331_4106_B740_00BE357278F4__INCLUDED_)
#define AFX_VIDEORENDER_H__1EDB4C90_1331_4106_B740_00BE357278F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <dshow.h>
#pragma comment(lib, "strmiids.lib")

class CVideoRender  
{
public:
	CVideoRender();
	virtual ~CVideoRender();
	//��������
	BOOL Create(HWND hNotifyHost, UINT nNotifyMsg);
	//�ͷŶ���
	void Release();
	//������Ƶ�ļ�
	BOOL LoadFile(LPCTSTR lpFile);
	//������Ƶ������
	BOOL SetOwner(HWND hWnd);
	//������Ƶ���ڴ�С
	BOOL MoveVideoWnd(LPRECT lpRect);
	//��ʼ����
	BOOL Run();
	//��ͣ����
	BOOL Pause();
	//ֹͣ����
	BOOL Stop();
	//��ȡ��Ƶ�ܳ���
	BOOL GetDuration(__int64 *pDuration);
	//���ò��Ž���
	BOOL SetPosition(__int64 iPosition);
	//��ȡ��ǰ����
	BOOL GetPosition(__int64 *pPosition);
	//��ȡ������Ϣ
	LPCTSTR GetErrMsg();
	//��ȡ�¼�
	BOOL GetEvent(LONG *plCode, LONG *plParam1, LONG *plParam2);
protected:
	//���ô�����Ϣ
	void SetErrMsg(LPCTSTR lpMsg);
protected:
	HRESULT			 m_hr;
	TCHAR			 m_szErrMsg[1024];
	IMediaSeeking   *m_pMediaSeeking;
	IMediaEventEx   *m_pMediaEventEx;
	IVideoWindow    *m_pVideoWnd;
	IMediaControl   *m_pMediaCtrl;
	IGraphBuilder   *m_pGraph;
};

#endif // !defined(AFX_VIDEORENDER_H__1EDB4C90_1331_4106_B740_00BE357278F4__INCLUDED_)
