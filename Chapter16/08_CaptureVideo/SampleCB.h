#pragma once

//���ڽ�����Ƶͼ��Ķ�����
class IMediaReceiver
{
public:
	virtual void OnUpdateVideo(
		const BITMAPINFO *, const BYTE *) = 0;
};
//��Ƶ�ص��ӿ�ʵ��
class CSampleCB :
	public ISampleGrabberCB
{
public:
	CSampleCB(void);
	~CSampleCB(void);
	STDMETHODIMP_(ULONG) AddRef() { return 2; } 
	STDMETHODIMP_(ULONG) Release() { return 1; } 
	STDMETHODIMP QueryInterface(REFIID riid, void ** ppv)
	{ 
		if( riid == IID_ISampleGrabberCB || riid == IID_IUnknown )
		{
			*ppv = (void *) static_cast<ISampleGrabberCB*>(this); 
			return NOERROR; 
		} 
		return E_NOINTERFACE; 
	} 
	//�ص�����������һ�����ɻ��ͼ��
	STDMETHODIMP SampleCB(double SampleTime, IMediaSample *pSample);
	STDMETHODIMP BufferCB(
		double dblSampleTime, BYTE *pBuffer, long lBufferSize);
	//����ͼ�������
	void SetReceiver(IMediaReceiver * pObj);
	//����ͼ��ߴ�
	void SetImageInfo(LONG nWidth, LONG nHeight);
protected:
	IMediaReceiver * m_pReceiver;
	BITMAPINFO m_bmi;
};
