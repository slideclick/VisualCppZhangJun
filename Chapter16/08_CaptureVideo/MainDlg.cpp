#include "stdafx.h"
#include "MainDlg.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMainDlg::CMainDlg()
{
	//��ʼ������
	m_hDlg			=	NULL;
	m_hDeviceList	=	NULL;
	m_hVideo		=	NULL;
	m_siDlg.cx		=	m_siDlg.cy = 0;
	m_nSnapshotNum  =	m_nSnapshotCount = 0;
	m_dwLastSnapshot=	m_dwSnapshotInterval = 0;
	*m_szSnapshotPath = _T('\0');
	m_hAppIcon		=	NULL;
}

CMainDlg::~CMainDlg()
{

}

int CMainDlg::DoModal()
{
	//�����Ի���
	return DialogBoxParam(
		GetInstance(), MAKEINTRESOURCE(IDD_MAIN), 
		NULL, DlgProc, (LPARAM)this);
}
//�Ի������
int CALLBACK CMainDlg::DlgProc(
	HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//�Ի�����ָ��
	static CMainDlg *pDlg = NULL;
	if(pDlg == NULL && uMsg != WM_INITDIALOG)
		return 0;
	//��Ϣ����
	int nRet = 0;
	switch(uMsg) 
	{
	case WM_INITDIALOG:
		pDlg = (CMainDlg *)lParam;
		nRet = pDlg->OnInitDialog(hDlg);
		break;
	case WM_COMMAND:
		nRet = pDlg->OnCommand(wParam, lParam);
		break;
	case WM_SIZE:
		pDlg->OnSize(wParam, lParam);
		nRet = 1;
		break;
	case WM_CLOSE:
		EndDialog(hDlg, 0);
		break;
	case WM_DESTROY:
		pDlg->OnDestroy();
		break;
	case WM_GETMINMAXINFO:
		{
			//���ƴ�����С�ߴ�
			LPMINMAXINFO lpmm = (LPMINMAXINFO)lParam;
			lpmm->ptMinTrackSize.x = pDlg->m_siDlg.cx;
			lpmm->ptMinTrackSize.y = pDlg->m_siDlg.cy;
		}
		nRet = 1;
		break;
	default:
		nRet = 0;
		break;
	}
	return nRet;
}
//��ʼ���Ի���
BOOL CMainDlg::OnInitDialog(HWND hWnd)
{
	//������
	m_hDlg			= hWnd;
	m_hVideo		= GetDlgItem(m_hDlg, IDC_VIDEO);
	m_hDeviceList	= GetDlgItem(m_hDlg, IDC_CMB_DEVICE);
	//�����������Ƶ�ɼ���
	m_cap.GetSampleCB()->SetReceiver(this);
	//ö����Ƶ�ɼ��豸
	OnGetDevices();
	//���洰��ԭʼ�ߴ�
	RECT rc = {0};
	GetClientRect(m_hDlg, &rc);
	m_siDlg.cx = rc.right - rc.left;
	m_siDlg.cy = rc.bottom - rc.top;
	//��ʼ����ͼ���
	SendDlgItemMessage(m_hDlg, IDC_SPIN_INTERVAL, UDM_SETRANGE32, 0, 100000);
	SetDlgItemText(m_hDlg, IDC_EDT_INTERVAL, _T("200"));
	//���ü���Ϊ100
	UDACCEL uda = {0};
	uda.nInc = 100;
	uda.nSec = 0;
	SendDlgItemMessage(m_hDlg, IDC_SPIN_INTERVAL, UDM_SETACCEL, 1, (LPARAM)&uda);
	//��ʼ����ͼ����
	SendDlgItemMessage(m_hDlg, IDC_SPIN_COUNT, UDM_SETRANGE32, 1, 1000);
	SetDlgItemText(m_hDlg, IDC_EDT_COUNT, _T("1"));
	//Ӧ�ó���ͼ��
	m_hAppIcon = LoadIcon(GetInstance(), MAKEINTRESOURCE(IDI_APP));
	//���ô�ͼ��
	SendMessage(m_hDlg, WM_SETICON, ICON_BIG, (LPARAM)m_hAppIcon);
	//����Сͼ��
	SendMessage(m_hDlg, WM_SETICON, ICON_SMALL, (LPARAM)m_hAppIcon);
	return TRUE;
}
//����ǰ��Ϣ
void CMainDlg::OnDestroy()
{
	DestroyIcon(m_hAppIcon);
	m_cap.Stop();
	m_cap.Release();
}
//WM_COMMAND��Ϣ��Ӧ
BOOL CMainDlg::OnCommand(WPARAM wp, LPARAM lp)
{
	switch(wp) 
	{
	case IDC_BTN_GETDEVICES:
		OnGetDevices();
		break;
	case IDOK:
		OnOk();
		break;
	case IDC_BTN_SNAPSHOT:
		OnSnapshot();
		break;
	case IDCANCEL:
		PostMessage(m_hDlg, WM_CLOSE, 0, 0);
		break;
	default:
		return FALSE;
	}
	return TRUE;
}
//��ˢ���豸����ť��Ӧ����
void CMainDlg::OnGetDevices()
{
	//����豸�б�
	SendMessage(m_hDeviceList, CB_RESETCONTENT, 0, 0);
	//ö���豸
	int nCount = m_cap.EnumDevices(m_hDeviceList);
	if(nCount > 0)
	{
		//Ĭ��ѡ���һ���豸
		SendMessage(m_hDeviceList, CB_SETCURSEL, nCount - 1, 0);
	}
	//������豸��������ʼ����ť�������ֹ
	EnableDlgItem(IDOK, nCount > 0);
}
//����ʼ����ť��Ӧ����
void CMainDlg::OnOk()
{
	//��ʼ������
	HRESULT hr = m_cap.Init(0);
	if(SUCCEEDED(hr))
	{
		//��ʼ��ʾͼ��
		if(SUCCEEDED(m_cap.Run()))
		{
			//��ֹ��ˢ���豸����ť
			EnableDlgItem(IDC_BTN_GETDEVICES, FALSE);
			//��ֹ�豸�б�
			EnableDlgItem(IDC_CMB_DEVICE, FALSE);
			//��ֹ����ʼ����ť
			EnableDlgItem(IDOK, FALSE);
			//������ͼ����ť
			EnableDlgItem(IDC_BTN_SNAPSHOT, TRUE);			
		}
	}
	else
		m_cap.Release();
}
//����ͼ����ť��Ӧ����
void CMainDlg::OnSnapshot()
{
	//���ð�ť����ֹ�ٴΰ���
	EnableDlgItem(IDC_BTN_SNAPSHOT, FALSE);
	//��ȡҪ��ͼ������
	m_nSnapshotCount = 
		SendDlgItemMessage(m_hDlg, IDC_SPIN_COUNT, UDM_GETPOS32, 0, 0);
	if(m_nSnapshotCount < 1)
		m_nSnapshotCount = 1;	
	//��ȡ��ͼ���
	m_dwSnapshotInterval = 
		SendDlgItemMessage(m_hDlg, IDC_SPIN_INTERVAL, UDM_GETPOS32, 0, 0);
	//��ȡ������·��
	DWORD dwLen = GetModuleFileName(NULL, m_szSnapshotPath, MAX_PATH);
	TCHAR *p = _tcsrchr(m_szSnapshotPath, _T('\\'));
	if(p == NULL)
		DebugBreak();
	*p = _T('\0');
	//��ȡ��ǰʱ��
	SYSTEMTIME time = {0};
	GetLocalTime(&time);
	//����ʱ��ϳ�λͼ����Ŀ¼
	TCHAR szTime[32] = {0};
	_stprintf(szTime, _T("\\%d%.2d%.2d%.2d%.2d%.2d\\"), 
		time.wYear, time.wMonth, time.wDay,
		time.wHour, time.wMinute, time.wSecond);
	_tcscat(m_szSnapshotPath, szTime);	
	//����Ŀ¼
	if(!CreateDirectory(m_szSnapshotPath, NULL))
	{
		DebugBreak();
	}
}
//WM_SIZE��Ϣ��Ӧ
void CMainDlg::OnSize(WPARAM wp, LPARAM lp)
{
	//ֻ�����Ҫ����Ϣ�����ڷǱ�Ҫ��Ϣֱ�ӷ���
	switch(wp)
	{
	case SIZE_MAXHIDE:
	case SIZE_MAXSHOW:
	case SIZE_MINIMIZED:
		return;
	}
	//ȡ�öԻ�����´�С
	int nWidth = LOWORD(lp);
	int nHeight = HIWORD(lp);
	//��øı�Ĳ�ֵ
	int x, y;
	x = nWidth - m_siDlg.cx;
	y = nHeight - m_siDlg.cy;
	//�ƶ���Ƶ��ʾ�ؼ�
	RECT rc = {0};
	GetWindowRect(m_hVideo, &rc);
	rc.right += x;
	rc.bottom += y;
	//����Ļ����ת��Ϊ��������
	ScreenToClientRect(&rc);
	//�ƶ��ؼ�
	MoveWindow(m_hVideo, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, FALSE);
	//���浱ǰ��С
	m_siDlg.cx = nWidth;
	m_siDlg.cy = nHeight;
}
//����Ļ����ת��Ϊ��������
void CMainDlg::ScreenToClientRect(LPRECT prc)
{
	ScreenToClient(m_hDlg, (LPPOINT)prc);
	ScreenToClient(m_hDlg, ((LPPOINT)prc) + 1);	
}
//�����ͼ�ļ�
void CMainDlg::SaveSnapshotImage(const BITMAPINFOHEADER *pbih, const BYTE *pBuf)
{
	//���ɱ��ν�ͼ�ļ���
	TCHAR szFile[MAX_PATH] = {0};
	_stprintf(szFile, _T("%s%.3d.bmp"), m_szSnapshotPath, m_nSnapshotNum);
	//�����ļ�
	HANDLE hFile = CreateFile(szFile, GENERIC_WRITE, FILE_SHARE_READ, 
		NULL, CREATE_ALWAYS, NULL, NULL );   
	if(hFile == INVALID_HANDLE_VALUE)
	{
		DebugBreak();
		return  ;   
	}
	//дλͼ�ļ�ͷ[ע�⣬ʵ��ʹ��ʱӦ�ж�WriteFile�ķ���ֵ]
	BITMAPFILEHEADER bfh = {0};   
	bfh.bfType = 'MB';   
	bfh.bfOffBits = sizeof(bfh) + sizeof(BITMAPINFOHEADER);   
	bfh.bfSize = bfh.bfOffBits + pbih->biSizeImage;   
	DWORD dwWritten = 0;   
	WriteFile(hFile, &bfh, sizeof(bfh), &dwWritten, NULL );   
	//дλͼ��Ϣ
	WriteFile(hFile, pbih, sizeof(BITMAPINFOHEADER), &dwWritten, NULL);   
	//дλͼ����
	WriteFile(hFile, pBuf, pbih->biSizeImage, &dwWritten, NULL);   
	//�ر��ļ�
	CloseHandle(hFile);
}
//��ֹ������Ի����ϵĿؼ�
void CMainDlg::EnableDlgItem(UINT nID, BOOL bEnable)
{
	HWND hItem = GetDlgItem(m_hDlg, nID);
	if(hItem != NULL)
	{
		EnableWindow(hItem, bEnable);
	}
}
//������Ƶͼ��
void CMainDlg::OnUpdateVideo(const BITMAPINFO * pBmi, const BYTE *pBuf)
{
	//��ȡ��ʾ�ؼ���DC
	HDC hDC = GetDC(m_hVideo);
	//��ȡ�ؼ���С
	RECT rcClient = {0};
	GetClientRect(m_hVideo, &rcClient);
	//����λͼ����ģʽ
	int i = SetStretchBltMode(hDC, COLORONCOLOR); 
	//����λͼ��DC
	StretchDIBits(hDC, 0, 0, rcClient.right, rcClient.bottom, 
		0, 0, pBmi->bmiHeader.biWidth, pBmi->bmiHeader.biHeight, 
		pBuf, pBmi, DIB_RGB_COLORS, SRCCOPY);
	//�ָ�ԭ����ģʽ
	SetStretchBltMode(hDC, i);
	//�ͷ�DC
	ReleaseDC(m_hVideo, hDC);
	//�����Ƿ���Ҫ��ͼ
	if(m_nSnapshotCount > 0)
	{
		//�����Ƿ��˽�ͼ���
		DWORD dwTicks = GetTickCount();
		DWORD dwInterval = dwTicks - m_dwLastSnapshot;
		if(dwTicks - m_dwLastSnapshot >= m_dwSnapshotInterval)
		{
			//��ͼ
			SaveSnapshotImage(&pBmi->bmiHeader, pBuf);
			//�����ѽ�ͼ����
			m_nSnapshotNum ++;
			//����ﵽ������������������ν�ͼ
			if(m_nSnapshotNum >= m_nSnapshotCount)
			{
				m_dwLastSnapshot = 0;
				m_nSnapshotNum = m_nSnapshotCount = 0;
				EnableDlgItem(IDC_BTN_SNAPSHOT, TRUE);
			}
			else
			{
				//���汾�ν�ͼʱ��
				m_dwLastSnapshot = dwTicks;				
			}
		}
	}
}