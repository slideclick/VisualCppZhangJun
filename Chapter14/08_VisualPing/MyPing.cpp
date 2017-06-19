// MyPing.cpp: implementation of the CMyPing class.
//
//////////////////////////////////////////////////////////////////////
#include "MyPing.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMyPing::CMyPing()
{
	//������ʼ��
	m_hHost			=	NULL;
	m_socket		=	INVALID_SOCKET;
	m_dwDestIP		=	0;
	m_dwInterval	=	0;
	m_dwTimeout		=	0;
	m_hRunEvent		=	NULL;
	m_hThread		=	NULL;
}
CMyPing::~CMyPing()
{
}
//��ʼ������
BOOL CMyPing::StartPing(HWND hHost, LPCTSTR lpDestHost, 
			UINT nMsgID, DWORD dwInterval, DWORD dwTimeout)
{
	DWORD dwErr;
	//�������
	m_hHost		 = hHost;
	m_nMsgID	 = nMsgID;
	m_dwInterval = dwInterval;
	m_dwTimeout	 = dwTimeout;
	//��ȡĿ������IP
	struct hostent* dest = gethostbyname(lpDestHost);
	if(dest == NULL)
	{
		dwErr = WSAGetLastError();
		DebugPrint("����: �޷�������������%s,%.8X.\n", lpDestHost, dwErr);
		return FALSE;
	}
	m_dwDestIP = *(DWORD*)dest->h_addr_list[0];
	//����ԭʼ�׽���
	m_socket = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if(m_socket == INVALID_SOCKET)
	{
		dwErr = WSAGetLastError();
		DebugPrint(_T("�����׽���ʧ��:%.8X.\n"), dwErr);
		return FALSE;
	}
	int nTimeOut = m_dwTimeout;
	//���ý��ճ�ʱ
	int nRet = setsockopt(m_socket, SOL_SOCKET, SO_RCVTIMEO, 
		(const char*)&nTimeOut, sizeof(nTimeOut));
	if(nRet == SOCKET_ERROR)
	{
		dwErr = WSAGetLastError();
		DebugPrint(_T("���ý��ճ�ʱʱ����:%.8X.\n"), dwErr);
		return FALSE;
	}
	//�����¼����󣬸ö�������ȷ���߳��˳����߳���ʱ
	m_hRunEvent = CreateEvent(NULL, TRUE, FALSE, _T("Ping_Thread_Event"));
	//�����߳�
	UINT nID;
	m_hThread = (HANDLE)_beginthreadex(NULL, 0, WorkProc, this, 0, &nID);
	//CloseHandle(hThread);
	return TRUE;
}
//�ͷŶ��󴴽�����Դ
void  CMyPing::Release()
{
	//���¼���������Ϊ���źţ�ʹ�߳̽���
	SetEvent(m_hRunEvent);
	//�ȴ��߳̽���
	DWORD dwWait = WaitForSingleObject(m_hThread, m_dwTimeout * 2);
	if(dwWait != WAIT_OBJECT_0)
		DebugPrint(_T("���棬�߳̿���δ�����ر�...\n"));
	CloseHandle(m_hThread);
	//�ͷ��¼�����
	CloseHandle(m_hRunEvent);
	m_hRunEvent = NULL;
	//�ͷ��׽���
	closesocket(m_socket);
	m_socket = INVALID_SOCKET;
}
//���������Ϣ
void CMyPing::DebugPrint(LPCTSTR lpMsg, ...)
{
#ifdef _DEBUG
	//���ݲ�����ʽ���ı�
	TCHAR szErr[1024] = {0};
	va_list pArgs;
    va_start(pArgs, lpMsg);
    _vsntprintf(szErr, 1020, lpMsg, pArgs);
    va_end(pArgs);
	//���������Ϣ
	OutputDebugString(szErr);
#endif
}
//����У���
WORD CMyPing::GetCheckSum(char *pBuf, int nLen)
{
	WORD *pwBuf = (WORD *)pBuf;
	UINT nSum = 0;
	while(nLen > 1)
	{
		nSum += *pwBuf;
		++pwBuf;
		nLen -= sizeof(WORD);
	}
	if(nLen)
	{
		nSum += *(BYTE*)pwBuf;
	}
	nSum = (nSum >> 16) + (nSum & 0xffff);
	nSum += (nSum>>16);
	return (WORD)(~nSum);
}
//Ping�̺߳���
UINT CALLBACK CMyPing::WorkProc(LPVOID p)
{
	//���洫������ָ��
	CMyPing *pMyPing = (CMyPing *)p;
	//ѭ����Ҫ�õ��ı���
	struct sockaddr_in destAddr = {0};
	char bySendBuf[sizeof(ICMP_HDR)+32] = {0};
	PICMP_HDR pIcmp = (PICMP_HDR)bySendBuf;
	char byRecvBuf[1024] = {0};
	int nSeq = 0;
	int nRet = 0;
	int nLen = 0;
	DWORD dwErr = 0;
	DWORD dwTicks;
	DWORD dwTime;
	UINT  nFlag;
	DWORD dwWait;
	//����Ŀ��������ַ
	destAddr.sin_family = AF_INET;
	destAddr.sin_addr.s_addr = pMyPing->m_dwDestIP;
	destAddr.sin_port = htons(0);
	//����ICMP�����8������������
	pIcmp->icmp_type = 8;
	pIcmp->icmp_code = 0;
	pIcmp->icmp_id = (unsigned short)GetCurrentProcessId();
	pIcmp->icmp_sequence = 0;
	memset(&bySendBuf[sizeof(ICMP_HDR)], 0xA, 32);
	//ѭ��PingĿ������
	while(TRUE)
	{
		dwTime = 0;
		nFlag  = 4;
		//����ż�1
		++nSeq;
		//���ICMP������
		pIcmp->icmp_checksum = 0;
		pIcmp->icmp_sequence = nSeq;
		pIcmp->imcp_timestamp = GetTickCount();
		pIcmp->icmp_checksum = CMyPing::GetCheckSum(
			bySendBuf, sizeof(ICMP_HDR)+32);
		//����ICMP��
		nRet = sendto(pMyPing->m_socket, bySendBuf, sizeof(ICMP_HDR)+32, 
			0, (SOCKADDR*)&destAddr, sizeof(destAddr));
		if(nRet == SOCKET_ERROR)
		{
			//����ʧ��
			dwErr = WSAGetLastError();
			DebugPrint(_T("����ICMP��ʱʧ��,0x%.8X.\n"), dwErr);
			return 0;
		}
		//ѭ������Ӧ���
		while(TRUE)
		{
			//����ڳ�ʱʱ�䵽����û���յ���ȷ�Ļ�Ӧ����ʱ�˳�
			dwTicks = GetTickCount();
			if(dwTicks - pIcmp->imcp_timestamp >= pMyPing->m_dwTimeout)
			{
				DebugPrint("Wait timed out.\n");
				nFlag = 3;
				break;
			}
			//��������
			memset(byRecvBuf, 0, sizeof(byRecvBuf));
			nLen = sizeof(destAddr);
			nRet = recvfrom(pMyPing->m_socket, byRecvBuf, sizeof(byRecvBuf), 
				0, (SOCKADDR*)&destAddr, &nLen);
			if(nRet == SOCKET_ERROR)
			{
				dwErr = WSAGetLastError();
				//��ʱ
				if(dwErr == WSAETIMEDOUT)
				{
					DebugPrint(_T("Request timed out.\n"));
					nFlag = 1;
				}
				//��������
				else
				{
					DebugPrint(_T("����ICMP��ʱʧ��,0x%.8X.\n"), dwErr);
					nFlag = 2;
				}
				//�˳�����ѭ����������ѭ��
				break;
			}
			
			//�����յ������ݰ�
			dwTicks = GetTickCount();
			if(nRet < sizeof(IP_HDR) + sizeof(ICMP_HDR))
			{
				//���ݰ���������
				DebugPrint(_T("���յ��쳣���ݰ�,��:%s.\n"), 
					inet_ntoa(destAddr.sin_addr));
				nFlag = 3;
			}
			else
			{
				PICMP_HDR pRecvIcmp = (PICMP_HDR)&byRecvBuf[sizeof(IP_HDR)];
				if(pRecvIcmp->icmp_type != 0)
				{
					//���ݰ����Ͳ��ԣ����ǻ���Ӧ���
					DebugPrint(_T("�յ������Ӧ������:%d.\n"), 
						pRecvIcmp->icmp_type);
					nFlag = 3;
				}
				else
				{
					if(pRecvIcmp->icmp_id != GetCurrentProcessId())
					{
						//���ݰ�ID����
						DebugPrint(_T("�յ��Ǳ����̷�����Ӧ���.\n"));
						nFlag = 3;
					}
					else if(pRecvIcmp->icmp_sequence != pIcmp->icmp_sequence)
					{
						//���ݰ���Ų���
						DebugPrint(_T("�յ���Ԥ����ŵİ�.\n"));
						nFlag = 3;
					}
					else
					{
						//���յ���������
						nFlag = 0;
						dwTime = dwTicks - pRecvIcmp->imcp_timestamp;
						DebugPrint(_T("�յ���Ӧ�������=%d,Time=%d.\n"), 
							pRecvIcmp->icmp_sequence, dwTime);
						//�˳�����ѭ����������ѭ��
						break;
					}
				}
			}
		}//End of ѭ������Ӧ���
		if(nFlag < 3)
		{
			//��Pingֵ���͸�����
			PostMessage(pMyPing->m_hHost, pMyPing->m_nMsgID, nFlag, dwTime);
			//�ȴ��¼������û�źţ��ﵽ��ʱ��Ŀ�ġ�
			//������źţ�������Ҫ���������߳�
			dwWait = WaitForSingleObject(pMyPing->m_hRunEvent, pMyPing->m_dwInterval);
			if(dwWait != WAIT_TIMEOUT)
			{
				DebugPrint(_T("End Thread\n"));
				break;
			}
		}
		else
		{
			//���nFlagΪ3���������ݴ��󣬼�������
		}
	}//End of ѭ��PingĿ������
	return 0;
}