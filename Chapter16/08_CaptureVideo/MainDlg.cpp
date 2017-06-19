#include "stdafx.h"
#include "MainDlg.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMainDlg::CMainDlg()
{
	//初始化变量
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
	//弹出对话框
	return DialogBoxParam(
		GetInstance(), MAKEINTRESOURCE(IDD_MAIN), 
		NULL, DlgProc, (LPARAM)this);
}
//对话框过程
int CALLBACK CMainDlg::DlgProc(
	HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//对话框类指针
	static CMainDlg *pDlg = NULL;
	if(pDlg == NULL && uMsg != WM_INITDIALOG)
		return 0;
	//消息处理
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
			//限制窗体最小尺寸
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
//初始化对话框
BOOL CMainDlg::OnInitDialog(HWND hWnd)
{
	//保存句柄
	m_hDlg			= hWnd;
	m_hVideo		= GetDlgItem(m_hDlg, IDC_VIDEO);
	m_hDeviceList	= GetDlgItem(m_hDlg, IDC_CMB_DEVICE);
	//关联本类和视频采集类
	m_cap.GetSampleCB()->SetReceiver(this);
	//枚举视频采集设备
	OnGetDevices();
	//保存窗口原始尺寸
	RECT rc = {0};
	GetClientRect(m_hDlg, &rc);
	m_siDlg.cx = rc.right - rc.left;
	m_siDlg.cy = rc.bottom - rc.top;
	//初始化截图间隔
	SendDlgItemMessage(m_hDlg, IDC_SPIN_INTERVAL, UDM_SETRANGE32, 0, 100000);
	SetDlgItemText(m_hDlg, IDC_EDT_INTERVAL, _T("200"));
	//设置加速为100
	UDACCEL uda = {0};
	uda.nInc = 100;
	uda.nSec = 0;
	SendDlgItemMessage(m_hDlg, IDC_SPIN_INTERVAL, UDM_SETACCEL, 1, (LPARAM)&uda);
	//初始化截图张数
	SendDlgItemMessage(m_hDlg, IDC_SPIN_COUNT, UDM_SETRANGE32, 1, 1000);
	SetDlgItemText(m_hDlg, IDC_EDT_COUNT, _T("1"));
	//应用程序图标
	m_hAppIcon = LoadIcon(GetInstance(), MAKEINTRESOURCE(IDI_APP));
	//设置大图标
	SendMessage(m_hDlg, WM_SETICON, ICON_BIG, (LPARAM)m_hAppIcon);
	//设置小图标
	SendMessage(m_hDlg, WM_SETICON, ICON_SMALL, (LPARAM)m_hAppIcon);
	return TRUE;
}
//销毁前消息
void CMainDlg::OnDestroy()
{
	DestroyIcon(m_hAppIcon);
	m_cap.Stop();
	m_cap.Release();
}
//WM_COMMAND消息响应
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
//“刷新设备”按钮响应函数
void CMainDlg::OnGetDevices()
{
	//清空设备列表
	SendMessage(m_hDeviceList, CB_RESETCONTENT, 0, 0);
	//枚举设备
	int nCount = m_cap.EnumDevices(m_hDeviceList);
	if(nCount > 0)
	{
		//默认选择第一个设备
		SendMessage(m_hDeviceList, CB_SETCURSEL, nCount - 1, 0);
	}
	//如果有设备，允许“开始”按钮，否则禁止
	EnableDlgItem(IDOK, nCount > 0);
}
//“开始”按钮响应函数
void CMainDlg::OnOk()
{
	//初始化对象
	HRESULT hr = m_cap.Init(0);
	if(SUCCEEDED(hr))
	{
		//开始显示图像
		if(SUCCEEDED(m_cap.Run()))
		{
			//禁止“刷新设备”按钮
			EnableDlgItem(IDC_BTN_GETDEVICES, FALSE);
			//禁止设备列表
			EnableDlgItem(IDC_CMB_DEVICE, FALSE);
			//禁止“开始”按钮
			EnableDlgItem(IDOK, FALSE);
			//允许“截图”按钮
			EnableDlgItem(IDC_BTN_SNAPSHOT, TRUE);			
		}
	}
	else
		m_cap.Release();
}
//“截图”按钮响应函数
void CMainDlg::OnSnapshot()
{
	//禁用按钮，防止再次按下
	EnableDlgItem(IDC_BTN_SNAPSHOT, FALSE);
	//获取要截图的张数
	m_nSnapshotCount = 
		SendDlgItemMessage(m_hDlg, IDC_SPIN_COUNT, UDM_GETPOS32, 0, 0);
	if(m_nSnapshotCount < 1)
		m_nSnapshotCount = 1;	
	//获取截图间隔
	m_dwSnapshotInterval = 
		SendDlgItemMessage(m_hDlg, IDC_SPIN_INTERVAL, UDM_GETPOS32, 0, 0);
	//获取本程序路径
	DWORD dwLen = GetModuleFileName(NULL, m_szSnapshotPath, MAX_PATH);
	TCHAR *p = _tcsrchr(m_szSnapshotPath, _T('\\'));
	if(p == NULL)
		DebugBreak();
	*p = _T('\0');
	//获取当前时间
	SYSTEMTIME time = {0};
	GetLocalTime(&time);
	//按照时间合成位图保存目录
	TCHAR szTime[32] = {0};
	_stprintf(szTime, _T("\\%d%.2d%.2d%.2d%.2d%.2d\\"), 
		time.wYear, time.wMonth, time.wDay,
		time.wHour, time.wMinute, time.wSecond);
	_tcscat(m_szSnapshotPath, szTime);	
	//创建目录
	if(!CreateDirectory(m_szSnapshotPath, NULL))
	{
		DebugBreak();
	}
}
//WM_SIZE消息响应
void CMainDlg::OnSize(WPARAM wp, LPARAM lp)
{
	//只处理必要的消息，对于非必要消息直接返回
	switch(wp)
	{
	case SIZE_MAXHIDE:
	case SIZE_MAXSHOW:
	case SIZE_MINIMIZED:
		return;
	}
	//取得对话框的新大小
	int nWidth = LOWORD(lp);
	int nHeight = HIWORD(lp);
	//获得改变的差值
	int x, y;
	x = nWidth - m_siDlg.cx;
	y = nHeight - m_siDlg.cy;
	//移动视频显示控件
	RECT rc = {0};
	GetWindowRect(m_hVideo, &rc);
	rc.right += x;
	rc.bottom += y;
	//将屏幕坐标转换为窗口坐标
	ScreenToClientRect(&rc);
	//移动控件
	MoveWindow(m_hVideo, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, FALSE);
	//保存当前大小
	m_siDlg.cx = nWidth;
	m_siDlg.cy = nHeight;
}
//将屏幕坐标转换为窗体坐标
void CMainDlg::ScreenToClientRect(LPRECT prc)
{
	ScreenToClient(m_hDlg, (LPPOINT)prc);
	ScreenToClient(m_hDlg, ((LPPOINT)prc) + 1);	
}
//保存截图文件
void CMainDlg::SaveSnapshotImage(const BITMAPINFOHEADER *pbih, const BYTE *pBuf)
{
	//生成本次截图文件名
	TCHAR szFile[MAX_PATH] = {0};
	_stprintf(szFile, _T("%s%.3d.bmp"), m_szSnapshotPath, m_nSnapshotNum);
	//创建文件
	HANDLE hFile = CreateFile(szFile, GENERIC_WRITE, FILE_SHARE_READ, 
		NULL, CREATE_ALWAYS, NULL, NULL );   
	if(hFile == INVALID_HANDLE_VALUE)
	{
		DebugBreak();
		return  ;   
	}
	//写位图文件头[注意，实际使用时应判断WriteFile的返回值]
	BITMAPFILEHEADER bfh = {0};   
	bfh.bfType = 'MB';   
	bfh.bfOffBits = sizeof(bfh) + sizeof(BITMAPINFOHEADER);   
	bfh.bfSize = bfh.bfOffBits + pbih->biSizeImage;   
	DWORD dwWritten = 0;   
	WriteFile(hFile, &bfh, sizeof(bfh), &dwWritten, NULL );   
	//写位图信息
	WriteFile(hFile, pbih, sizeof(BITMAPINFOHEADER), &dwWritten, NULL);   
	//写位图数据
	WriteFile(hFile, pBuf, pbih->biSizeImage, &dwWritten, NULL);   
	//关闭文件
	CloseHandle(hFile);
}
//禁止或允许对话框上的控件
void CMainDlg::EnableDlgItem(UINT nID, BOOL bEnable)
{
	HWND hItem = GetDlgItem(m_hDlg, nID);
	if(hItem != NULL)
	{
		EnableWindow(hItem, bEnable);
	}
}
//更新视频图像
void CMainDlg::OnUpdateVideo(const BITMAPINFO * pBmi, const BYTE *pBuf)
{
	//获取显示控件的DC
	HDC hDC = GetDC(m_hVideo);
	//获取控件大小
	RECT rcClient = {0};
	GetClientRect(m_hVideo, &rcClient);
	//设置位图缩放模式
	int i = SetStretchBltMode(hDC, COLORONCOLOR); 
	//复制位图到DC
	StretchDIBits(hDC, 0, 0, rcClient.right, rcClient.bottom, 
		0, 0, pBmi->bmiHeader.biWidth, pBmi->bmiHeader.biHeight, 
		pBuf, pBmi, DIB_RGB_COLORS, SRCCOPY);
	//恢复原缩放模式
	SetStretchBltMode(hDC, i);
	//释放DC
	ReleaseDC(m_hVideo, hDC);
	//看看是否需要截图
	if(m_nSnapshotCount > 0)
	{
		//看看是否到了截图间隔
		DWORD dwTicks = GetTickCount();
		DWORD dwInterval = dwTicks - m_dwLastSnapshot;
		if(dwTicks - m_dwLastSnapshot >= m_dwSnapshotInterval)
		{
			//截图
			SaveSnapshotImage(&pBmi->bmiHeader, pBuf);
			//增加已截图数量
			m_nSnapshotNum ++;
			//如果达到输入的数量，结束本次截图
			if(m_nSnapshotNum >= m_nSnapshotCount)
			{
				m_dwLastSnapshot = 0;
				m_nSnapshotNum = m_nSnapshotCount = 0;
				EnableDlgItem(IDC_BTN_SNAPSHOT, TRUE);
			}
			else
			{
				//保存本次截图时间
				m_dwLastSnapshot = dwTicks;				
			}
		}
	}
}