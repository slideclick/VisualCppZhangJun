// Compressor.cpp: implementation of the CCompressor class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyCompressor.h"
#include "Compressor.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//�궨��
#define BUF_LEN (1024*1024)
#define HEAD_LEN 3
//ȫ�ֳ���
const byte g_nFlag = 0xFF;
const byte g_nHead[] = {'M','C','F'};
const LPCTSTR g_lpExt = _T("mcf");

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCompressor::CCompressor()
{
}

CCompressor::~CCompressor()
{
}
//ѹ���ļ�
BOOL CCompressor::CompressFile(LPCTSTR lpFile)
{
	//��Ҫѹ�����ļ�
	CFile file;
	if(!file.Open(lpFile, CFile::modeRead))
		return FALSE;
	//����ѹ������ļ���
	TCHAR szDest[MAX_PATH];
	GetDestFilename(lpFile, szDest);
	_tcscat(szDest, g_lpExt);
	CFile fdest;
	//����ѹ���ļ�
	if(!fdest.Open(szDest, CFile::modeCreate | CFile::modeWrite))
		return FALSE;
	//д��ѹ����־
	fdest.Write(g_nHead, sizeof(g_nHead));
	//д��ԭʼ�ļ���׺��
	TCHAR *lpExt = _tcsrchr(lpFile, _T('.'));
	lpExt ++;
	fdest.Write(lpExt, strlen(lpExt) + 1);
	//����һ��������
	UINT nLen = file.GetLength();
	UINT nBufLen = min(BUF_LEN, nLen);
	byte *pBuf = new byte[nBufLen];
	byte nLast;
	int nRepeat = 0;
	UINT nRead = 0;
	UINT i;
	//���ļ����뻺����
	nRead = file.ReadHuge(pBuf, nBufLen);
	ASSERT(nRead == nBufLen);
	//ѭ��ѹ������
	for(i=0; i<nRead; i++)
	{
		//�״�ѭ����������ǰ�ֽ�
		if(nRepeat == 0)	
		{
			nRepeat ++;
			nLast = pBuf[i];
		}
		else
		{
			//�����ǰһ�ֽ��ظ����ظ�������һ
			if(nLast == pBuf[i] && nRepeat < 0xFF)
			{
				nRepeat ++;
			}
			else
			{
				//����ظ�������3����ѹ����ʽд��
				if(nRepeat > 3)
				{
					fdest.Write(&g_nFlag, 1);
					fdest.Write(&nLast, 1);
					fdest.Write(&nRepeat, 1);
				}
				else
				{
					//����ظ���С�ڵ���3����ԭʼ����д��
					while(nRepeat > 0)
					{
						if (nLast == g_nFlag) 
						{
							//���ԭʼ�����Ǳ�־�������⴦��
							fdest.Write(&nLast, 1);
							fdest.Write(&nLast, 1);
							nLast = 1;
							fdest.Write(&nLast, 1);
						}
						else
						{
							fdest.Write(&nLast, 1);
						}
						nRepeat --;
					} 
				}
				nLast = pBuf[i];
				nRepeat = 1;
			}
		}
	}
	//д�����һ���ֽ�
	if(nRepeat > 3)
	{
		fdest.Write(&g_nFlag, 1);
		fdest.Write(&nLast, 1);
		fdest.Write(&nRepeat, 1);
	}
	else
	{
		while(nRepeat > 0)
		{
			if (nLast == g_nFlag) 
			{
				fdest.Write(&nLast, 1);
				fdest.Write(&nLast, 1);
				nLast = 1;
				fdest.Write(&nLast, 1);
			}
			else
			{
				fdest.Write(&nLast, 1);
			}
			nRepeat --;
		} 
	}
	//�ر��ļ�
	fdest.Close();
	file.Close();
	//�ͷŻ�����
	delete []pBuf;
	return TRUE;
}
//��ѹ�ļ�
BOOL CCompressor::DecompressFile(LPCTSTR lpFile)
{
	//��Ҫ��ѹ���ļ�
	CFile file;
	if(!file.Open(lpFile, CFile::modeRead))
		return FALSE;
	//�ж��ļ�ǰ�Ƿ��б�־
	byte nHead[HEAD_LEN] = {0};
	file.Read(nHead, HEAD_LEN);
	if(memcmp(nHead, g_nHead, HEAD_LEN))
		return FALSE;
	//�õ���ѹ����ļ���
	TCHAR szDest[MAX_PATH];
	GetDestFilename(lpFile, szDest);
	UINT nNameLen = _tcslen(szDest);
	char nName = 1;
	UINT nExtLen = 0;
	while(nName)
	{
		file.Read(&nName, 1);
		szDest[nNameLen] = nName;
		nExtLen ++;
		nNameLen++;
		ASSERT(nNameLen < MAX_PATH);
	}
	//������ѹ����ļ�
	CFile fdest;
	fdest.Open(szDest, CFile::modeCreate | CFile::modeWrite);
	//��ѹ���ļ���ȡ��������
	UINT nLen = file.GetLength() - HEAD_LEN - nExtLen;
	UINT nBufLen = min(BUF_LEN, nLen);
	byte *pBuf = new byte[nBufLen];
	byte *pTemp = pBuf;
	byte nRepeat = 0;
	byte nLast;
	file.ReadHuge(pBuf, nBufLen);
	//ѭ����ȡѹ���ļ�����ѹ��Ŀ���ļ�
	while(pTemp < pBuf + nBufLen)
	{
		if(*pTemp == g_nFlag)
		{
			pTemp ++;
			nLast = *(pTemp ++);
			nRepeat = *(pTemp ++);
			while(nRepeat > 0)
			{
				fdest.Write(&nLast, 1);
				nRepeat --;
			}
		}
		else
		{
			fdest.Write(pTemp++, 1);
		}
	}
	//�ͷŻ�����
	delete []pBuf;
	//�ر��ļ�
	file.Close();
	fdest.Close();
	return TRUE;
}
//�õ�������׺���ļ���
void CCompressor::GetDestFilename(LPCTSTR lpSrc, LPTSTR lpDest)
{
	_tcscpy(lpDest, lpSrc);
	TCHAR *p = _tcsrchr(lpDest, _T('.'));
	ASSERT(p);
	p++;
	*p = _T('\0');
}