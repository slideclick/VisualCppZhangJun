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

//宏定义
#define BUF_LEN (1024*1024)
#define HEAD_LEN 3
//全局常量
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
//压缩文件
BOOL CCompressor::CompressFile(LPCTSTR lpFile)
{
	//打开要压缩的文件
	CFile file;
	if(!file.Open(lpFile, CFile::modeRead))
		return FALSE;
	//生成压缩后的文件名
	TCHAR szDest[MAX_PATH];
	GetDestFilename(lpFile, szDest);
	_tcscat(szDest, g_lpExt);
	CFile fdest;
	//创建压缩文件
	if(!fdest.Open(szDest, CFile::modeCreate | CFile::modeWrite))
		return FALSE;
	//写入压缩标志
	fdest.Write(g_nHead, sizeof(g_nHead));
	//写入原始文件后缀名
	TCHAR *lpExt = _tcsrchr(lpFile, _T('.'));
	lpExt ++;
	fdest.Write(lpExt, strlen(lpExt) + 1);
	//创建一个缓冲区
	UINT nLen = file.GetLength();
	UINT nBufLen = min(BUF_LEN, nLen);
	byte *pBuf = new byte[nBufLen];
	byte nLast;
	int nRepeat = 0;
	UINT nRead = 0;
	UINT i;
	//将文件读入缓冲区
	nRead = file.ReadHuge(pBuf, nBufLen);
	ASSERT(nRead == nBufLen);
	//循环压缩内容
	for(i=0; i<nRead; i++)
	{
		//首次循环，保留当前字节
		if(nRepeat == 0)	
		{
			nRepeat ++;
			nLast = pBuf[i];
		}
		else
		{
			//如果和前一字节重复，重复计数加一
			if(nLast == pBuf[i] && nRepeat < 0xFF)
			{
				nRepeat ++;
			}
			else
			{
				//如果重复数大于3，则按压缩格式写入
				if(nRepeat > 3)
				{
					fdest.Write(&g_nFlag, 1);
					fdest.Write(&nLast, 1);
					fdest.Write(&nRepeat, 1);
				}
				else
				{
					//如果重复数小于等于3，则按原始数据写入
					while(nRepeat > 0)
					{
						if (nLast == g_nFlag) 
						{
							//如果原始数据是标志，做特殊处理
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
	//写入最后一个字节
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
	//关闭文件
	fdest.Close();
	file.Close();
	//释放缓冲区
	delete []pBuf;
	return TRUE;
}
//解压文件
BOOL CCompressor::DecompressFile(LPCTSTR lpFile)
{
	//打开要解压的文件
	CFile file;
	if(!file.Open(lpFile, CFile::modeRead))
		return FALSE;
	//判断文件前是否有标志
	byte nHead[HEAD_LEN] = {0};
	file.Read(nHead, HEAD_LEN);
	if(memcmp(nHead, g_nHead, HEAD_LEN))
		return FALSE;
	//得到解压后的文件名
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
	//创建解压后的文件
	CFile fdest;
	fdest.Open(szDest, CFile::modeCreate | CFile::modeWrite);
	//将压缩文件读取至缓冲区
	UINT nLen = file.GetLength() - HEAD_LEN - nExtLen;
	UINT nBufLen = min(BUF_LEN, nLen);
	byte *pBuf = new byte[nBufLen];
	byte *pTemp = pBuf;
	byte nRepeat = 0;
	byte nLast;
	file.ReadHuge(pBuf, nBufLen);
	//循环读取压缩文件，解压倒目标文件
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
	//释放缓冲区
	delete []pBuf;
	//关闭文件
	file.Close();
	fdest.Close();
	return TRUE;
}
//得到不带后缀的文件名
void CCompressor::GetDestFilename(LPCTSTR lpSrc, LPTSTR lpDest)
{
	_tcscpy(lpDest, lpSrc);
	TCHAR *p = _tcsrchr(lpDest, _T('.'));
	ASSERT(p);
	p++;
	*p = _T('\0');
}