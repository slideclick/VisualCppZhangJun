#pragma once

#include "stdafx.h"
#include "samplecb.h"

class CCap
{
public:
	CCap(void);
	~CCap(void);
	//ö���豸�б�
	int EnumDevices(HWND hList);
	//��ʼ������
	HRESULT Init(int iDeviceID);
	//�ͷŶ�����Դ
	void Release();
	//��ʼ
	HRESULT Run();
	//��ͣ
	HRESULT Pause();
	//ֹͣ
	HRESULT Stop();
	//��ȡISampleGrabberCB
	CSampleCB *GetSampleCB();
	//�����豸�������豸��ţ��������-1����û���ҵ��豸
	int FindDeviceByName(LPCTSTR lpName);	
	//��ȡ����ŵ��豸����
	LPCTSTR GetDeviceName(int nIndex);
	//��ȡ�豸����
	int GetDeviceCount();
protected:
	void FreeMediaType(AM_MEDIA_TYPE& mt); 
	//����Filter
	BOOL BindFilter(int nDeviceId, IBaseFilter **pFilter); 
	//������Ƶ����
	HRESULT SetupVideoWindow(); 
	//��ʼ��GraphBuilder
	HRESULT InitCaptureGraphBuilder();
protected:
	IGraphBuilder	*m_pGB; 
	ICaptureGraphBuilder2* m_pCapture; 
	IBaseFilter		*m_pBF; 
	IMediaControl	*m_pMC; 
	IVideoWindow	*m_pVW; 
	LPTSTR			*m_pDevice;
	int 			m_nDeviceCount;
	BOOL			m_bRunning;
	HWND			m_hWnd;
	CSampleCB		m_cb;
	CComPtr<ISampleGrabber> m_pGrabber; 
};
