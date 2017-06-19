#include "StdAfx.h"
#include ".\samplecb.h"

CSampleCB::CSampleCB(void)
{
	//��ʼ������
	m_pReceiver = NULL;
	memset(&m_bmi, 0, sizeof(m_bmi));
	m_bmi.bmiHeader.biSize = sizeof(m_bmi.bmiHeader);
	m_bmi.bmiHeader.biPlanes = 1;
	m_bmi.bmiHeader.biBitCount = 24;
}
CSampleCB::~CSampleCB(void)
{
}
STDMETHODIMP CSampleCB::SampleCB(
	double SampleTime, IMediaSample *pSample)
{   
	return   0;   
}  
//ÿ�β������õĺ���
STDMETHODIMP CSampleCB::BufferCB(
	double dblSampleTime, BYTE *pBuffer, long lBufferSize)
{   
	if(!pBuffer)
		return E_POINTER;  
	//�������ݴ�С
	m_bmi.bmiHeader.biSizeImage = lBufferSize;
	//���ý����߷���
	if(m_pReceiver)
		m_pReceiver->OnUpdateVideo(&m_bmi, pBuffer);
	return 0;
}
//����ͼ�������
void CSampleCB::SetReceiver(IMediaReceiver * pObj)
{
	m_pReceiver = pObj;
}
//����ͼ���С
void CSampleCB::SetImageInfo(LONG nWidth, LONG nHeight)
{
	m_bmi.bmiHeader.biWidth = nWidth;
	m_bmi.bmiHeader.biHeight = nHeight;
}