#include "stdafx.h"
#include "MainDlg.h"
#include "..\..\comm\folderdlg.h"
#include "resource.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COLORREF g_crCustom[16] = {RGB(255, 255, 255)}; 
const 	DWORD dwRTFMask = CFM_BOLD | CFM_CHARSET | CFM_COLOR |
CFM_FACE | CFM_ITALIC | CFM_SIZE | CFM_STRIKEOUT | CFM_UNDERLINE;

CMainDlg::CMainDlg()
{
	//初始化变量
	m_hDlg			=	NULL;
	m_hAppIcon		=	NULL;
	*m_szImagePath	=	_T('\0');
	*m_szText		=	_T('\0');
	m_nTextSite		=	0;
	m_nAlpha		=	128;
	for(int i=0; i<sizeof(g_crCustom)/sizeof(g_crCustom[0]); i++)
	{
		g_crCustom[i] = RGB(255, 255, 255);
	}
}
CMainDlg::~CMainDlg()
{
}
//弹出对话框
int CMainDlg::DoModal()
{
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
	case WM_CLOSE:
		EndDialog(hDlg, 0);
		break;
	case WM_DESTROY:
		pDlg->OnDestroy();
		break;
	case WM_HSCROLL:
		pDlg->OnHScroll(wParam, lParam);
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
	m_hDlg		= hWnd;
	//应用程序图标
	m_hAppIcon	= LoadIcon(GetInstance(), MAKEINTRESOURCE(IDI_APP));
	//设置大图标
	SendMessage(m_hDlg, WM_SETICON, ICON_BIG, (LPARAM)m_hAppIcon);
	//设置小图标
	SendMessage(m_hDlg, WM_SETICON, ICON_SMALL, (LPARAM)m_hAppIcon);
	//初始化“文字位置”下拉框
	SendDlgMsg(IDC_CMB_ALIGN, CB_ADDSTRING, 0, (LPARAM)_T("左上"));
	SendDlgMsg(IDC_CMB_ALIGN, CB_ADDSTRING, 0, (LPARAM)_T("右上"));
	SendDlgMsg(IDC_CMB_ALIGN, CB_ADDSTRING, 0, (LPARAM)_T("左下"));
	SendDlgMsg(IDC_CMB_ALIGN, CB_ADDSTRING, 0, (LPARAM)_T("右下"));
	SendDlgMsg(IDC_CMB_ALIGN, CB_ADDSTRING, 0, (LPARAM)_T("中间"));
	SendDlgMsg(IDC_CMB_ALIGN, CB_SETCURSEL, 0, 0);
	//初始化“透明度”
	SendDlgMsg(IDC_SLIDER_ALPHA, TBM_SETRANGE, FALSE, MAKELONG(0, 255));
	SendDlgMsg(IDC_SLIDER_ALPHA, TBM_SETPOS, TRUE, m_nAlpha);
	SetDlgItemInt(m_hDlg, IDC_ALPHA, m_nAlpha, FALSE) ;
	//设置文本框最大可输入字符数
	SendDlgMsg(IDC_EDT_TEXT, EM_LIMITTEXT, MAX_CHARS, 0);
	//设置文本框默认颜色和字体大小
	CHARFORMAT2 cfm;
	ZeroMemory(&cfm, sizeof(CHARFORMAT2));
	cfm.cbSize = sizeof(CHARFORMAT2);
	SendDlgMsg(IDC_EDT_TEXT, EM_GETCHARFORMAT, SCF_DEFAULT, (LPARAM)&cfm);
	cfm.yHeight = 320;
	cfm.crTextColor = RGB(255, 0, 0);
	cfm.dwEffects = CFE_BOLD;
	SendDlgMsg(IDC_EDT_TEXT, EM_SETCHARFORMAT, SCF_DEFAULT, (LPARAM)&cfm);
	//设置文本框背景色
	SendDlgMsg(IDC_EDT_TEXT, EM_SETBKGNDCOLOR, 0, 0);
	return TRUE;
}
//销毁前消息
void CMainDlg::OnDestroy()
{
	DestroyIcon(m_hAppIcon);
}
//WM_COMMAND消息响应
BOOL CMainDlg::OnCommand(WPARAM wp, LPARAM lp)
{
	switch(wp) 
	{
	case IDOK:
		OnOk();
		break;
	case IDCANCEL:
		PostMessage(m_hDlg, WM_CLOSE, 0, 0);
		break;
	case IDC_BTN_BROWSE:
		OnBtnBrowse();
		break;
	case IDC_BTN_FONT:
		OnBtnFont();
		break;
	case IDC_BTN_COLOR:
		OnBtnColor();
		break;
	default:
		return FALSE;
	}
	return TRUE;
}
//“开始”按钮响应函数
void CMainDlg::OnOk()
{
	//取得用户输入
	//取得图片路径
	UINT nLen = GetDlgItemText(m_hDlg, IDC_EDT_PATH, m_szImagePath, MAX_PATH);
	if(nLen == 0)
	{
		MessageBox(m_hDlg, _T("请输入图片文件所在路径！"), _T("提示"), 
			MB_OK | MB_ICONWARNING);
		return;
	}
	if(m_szImagePath[nLen - 1] != _T('\\'))
		_tcscat(m_szImagePath, _T("\\"));
	//取得输入的文字
	nLen = GetDlgItemText(m_hDlg, IDC_EDT_TEXT, m_szText, MAX_CHARS);
	if(nLen == 0)
	{
		MessageBox(m_hDlg, _T("请输入要绘制的文字！"), _T("提示"), 
			MB_OK | MB_ICONWARNING);
		return;
	}
	//取得字体和颜色信息
	CHARFORMAT2 cfm;
	GetRichEditCharFormat(&cfm);
	//取得文字位置
	m_nTextSite = SendDlgMsg(IDC_CMB_ALIGN, CB_GETCURSEL, 0, 0);
	//取得透明度
	m_nAlpha = SendDlgMsg(IDC_SLIDER_ALPHA, TBM_GETPOS, 0, 0);
	
	//生成搜索路径
	TCHAR szPath[MAX_PATH];
	_tcscpy(szPath, m_szImagePath);
	_tcscat(szPath, _T("*.*"));
	//搜索文件
	int nCount = 0;
	WIN32_FIND_DATA fd = {0};
	HANDLE hFind = FindFirstFile(szPath, &fd);
	if(hFind == INVALID_HANDLE_VALUE )
	{
		MessageBox(m_hDlg, _T("所选目录没有文件！"), _T("提示"), 
			MB_OK | MB_ICONWARNING);
		return;
	}
	//绘制文字到临时位图中
	if(!DrawRtfText())
	{
		DebugBreak();
	}
	//循环处理文件
	do
	{
		if(!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			OutStatusText(_T("正在处理文件：%s。"), fd.cFileName);
			if(ProcessFile(fd.cFileName))
				nCount ++;
		}
	} while(FindNextFile(hFind, &fd));
	//结束搜索
	FindClose(hFind);
	//删除GDI对象
	m_dc.DeleteObj();		
	//显示结果
	OutStatusText(_T("已成功处理%d个文件。"), nCount);
}
//“浏览”按钮的响应函数
void CMainDlg::OnBtnBrowse()
{
	CFolderDlg dlg(NULL, _T("请选择图片所在目录"));
	if(dlg.ShowDlg(m_hDlg))
		SetDlgItemText(m_hDlg, IDC_EDT_PATH, dlg.GetSelectedPath());
}
//“字体”按钮的响应函数
void CMainDlg::OnBtnFont()
{
	//获取文本框当前字体
	CHARFORMAT2 cfm;
	GetRichEditCharFormat(&cfm);
	//字体对话框选项
    CHOOSEFONT cf;
    memset(&cf, 0, sizeof(CHOOSEFONT));
    cf.rgbColors = cfm.crTextColor;
    cf.lStructSize = sizeof(CHOOSEFONT);
    cf.hwndOwner = m_hDlg;
    cf.lpLogFont = &m_logfont;
    cf.Flags = CF_SCREENFONTS | CF_EFFECTS | CF_INITTOLOGFONTSTRUCT;
    //选择字体
    if (ChooseFont(&cf))
    {
		//根据CHOOSEFONT结构中的值，设定CHARFORMAT2中的值
        cfm.cbSize = sizeof(CHARFORMAT);
        cfm.dwMask = dwRTFMask;
        cfm.yHeight = 2 * cf.iPointSize;
        cfm.dwEffects = 0;
        if (m_logfont.lfWeight >= FW_BOLD)
            cfm.dwEffects |= CFE_BOLD;
        if (m_logfont.lfItalic)
            cfm.dwEffects |= CFE_ITALIC;
        if (m_logfont.lfUnderline)
            cfm.dwEffects |= CFE_UNDERLINE;
        if (m_logfont.lfStrikeOut)
            cfm.dwEffects |= CFE_STRIKEOUT;
        cfm.crTextColor = (COLORREF)cf.rgbColors;
        cfm.bPitchAndFamily = m_logfont.lfPitchAndFamily;
        cfm.bCharSet = m_logfont.lfCharSet;
        strcpy(cfm.szFaceName, m_logfont.lfFaceName);
		//更新文本框字体
        SendDlgMsg(IDC_EDT_TEXT, EM_SETCHARFORMAT, SCF_ALL, (LPARAM)&cfm); 
    }
}
//“颜色”按钮的响应函数
void CMainDlg::OnBtnColor()
{
	//获取文本框当前颜色
	CHARFORMAT2 cf;
	GetRichEditCharFormat(&cf);
	//颜色对话框选项
	CHOOSECOLOR cc = {0};
	cc.lStructSize = sizeof(cc);
	cc.Flags = CC_RGBINIT | CC_FULLOPEN | CC_ANYCOLOR;
	cc.hwndOwner = m_hDlg;
	cc.lpCustColors = g_crCustom;
	cc.rgbResult = cf.crTextColor;
	//选择颜色
	if(ChooseColor(&cc))
	{
		//更新文本框颜色
		cf.dwMask = CFM_COLOR;
		cf.dwEffects = 0;
		cf.crTextColor = cc.rgbResult;
		SendDlgMsg(IDC_EDT_TEXT, EM_SETCHARFORMAT, SCF_ALL, (LPARAM)&cf);
	}
}
//水平滚动条消息
void CMainDlg::OnHScroll(WPARAM wp, LPARAM lp)
{
	int nPos = SendDlgMsg(IDC_SLIDER_ALPHA, TBM_GETPOS, 0, 0);
	SetDlgItemInt(m_hDlg, IDC_ALPHA, nPos, FALSE);
}
//向某个控件发送消息
int CMainDlg::SendDlgMsg(int nID, UINT nMsg, WPARAM wp, LPARAM lp)
{
	return SendDlgItemMessage(m_hDlg, nID, nMsg, wp, lp);
}
//根据文件格式获取其编码器CLSID
BOOL CMainDlg::FindEncoder(GUID *pFormat, CLSID *pClsid)
{
	//获取编码器总数
    UINT  nNum = 0;  
    UINT  nSize = 0;
    ImageCodecInfo* pImageCodecInfo = NULL;
    GetImageEncodersSize(&nNum, &nSize);
    if(nSize == 0)
        return FALSE;
    //获取所有编码器
    pImageCodecInfo = (ImageCodecInfo*)(malloc(nSize));
    if(pImageCodecInfo == NULL)
        return FALSE;
    GetImageEncoders(nNum, nSize, pImageCodecInfo);
    //查找需要的编码器
    for(UINT i = 0; i < nNum; ++i)
    {
        if(pImageCodecInfo[i].FormatID  == *pFormat)
        {
			//找到匹配的编码器
            *pClsid = pImageCodecInfo[i].Clsid;
            free(pImageCodecInfo);
            return TRUE;
        }    
    }
    free(pImageCodecInfo);
    return FALSE;
}
//处理文件
BOOL CMainDlg::ProcessFile(LPCTSTR lpFile)
{
	//将文件名和目录组成完整的文件路径
	TCHAR szFullName[MAX_PATH];
	_tcscpy(szFullName, m_szImagePath);
	_tcscat(szFullName, lpFile);
	//确保文件路径是宽字符串
	WCHAR wszFile[MAX_PATH] = {0};
#ifdef UNICODE
	_tcscpy(wszFile, szFullName);
#else
	MultiByteToWideChar(CP_ACP, 0, szFullName, -1, 
		wszFile, sizeof(wszFile)/sizeof(wszFile[0])); 
#endif
	//得到文件的格式
	//加载文件
	Bitmap img(wszFile);
	Status s = img.GetLastStatus();
	if(s != Ok)
	{
		OutStatusText(_T("打开文件%s时发生错误，错误代码=%d。"), 
			szFullName, s);
		return FALSE;
	}
	//获取格式编码器
	GUID guid;
	img.GetRawFormat(&guid);
	CLSID clsid;
	if(!FindEncoder(&guid, &clsid))
	{
		OutStatusText(_T("无法找到文件%s的编码器。"), szFullName);
		return FALSE;
	}
	//计算文字绘制位置
	POINT pt;
	switch(m_nTextSite) 
	{
	case TS_LeftTop:
		pt.x = pt.y = 0;
		break;
	case TS_RightTop:
		pt.x = img.GetWidth() - m_dc.GetWidth();
		pt.y = 0;
		break;
	case TS_LeftBottom:
		pt.x = 0;
		pt.y = img.GetHeight() - m_dc.GetHeight();
		break;
	case TS_RightBottom:
		pt.x = img.GetWidth() - m_dc.GetWidth();
		pt.y = img.GetHeight() - m_dc.GetHeight();
		break;
	default:
		pt.x = (img.GetWidth() - m_dc.GetWidth())/2;
		pt.y = (img.GetHeight() - m_dc.GetHeight())/2;
		break;
	}
	//循环为复制每个点
	int x, y, nWidth, nHeight;
	nWidth = m_dc.GetWidth();
	nHeight= m_dc.GetHeight();
	COLORREF crSrc;
	Color crDest;
	int nSrcR, nSrcG, nSrcB;
	int nDestR, nDestG, nDestB;
	for(x = 0; x<nWidth; x++)
	{
		for(y=0; y<nHeight; y++)
		{
			//取得源颜色，如果为0，表示透明
			crSrc = GetPixel(m_dc, x, y);
			if(crSrc > 0)
			{
				//获取源的3基色
				nSrcR = GetRValue(crSrc);
				nSrcG = GetGValue(crSrc);
				nSrcB = GetBValue(crSrc);
				//获取目标颜色，pt中是位置偏移量
				img.GetPixel(pt.x + x, pt.y + y, &crDest);
				//取得目标的3基色
				nDestR = crDest.GetR();
				nDestG = crDest.GetG();
				nDestB = crDest.GetB();
				//按透明度计算新颜色
				nDestR = nSrcR * m_nAlpha / 255 + nDestR * (255 - m_nAlpha) / 255;
				nDestG = nSrcG * m_nAlpha / 255 + nDestG * (255 - m_nAlpha) / 255;
				nDestB = nSrcB * m_nAlpha / 255 + nDestB * (255 - m_nAlpha) / 255;
				//生成新的目标颜色
				crDest.SetFromCOLORREF(RGB(nDestR, nDestG, nDestB));
				//将颜色设置到图片
				img.SetPixel(pt.x + x, pt.y + y, crDest);
			}
		}
	}
	//新的文件路径和文件名
	WCHAR *p = wcsrchr(wszFile, L'\\');
	if(p == NULL)
	{
		DebugBreak();
		return FALSE;
	}
	*p = L'\0';
	p ++;
	WCHAR wszNewFile[MAX_PATH] = {0};
	wcscpy(wszNewFile, wszFile);
	wcscat(wszNewFile, L"\\New\\");
	//创建保存的新目录
	CreateDirectoryW(wszNewFile, NULL);
	wcscat(wszNewFile, p);
	//保存新文件
	s = img.Save(wszNewFile, &clsid, NULL);
	if(s != Ok)
	{
		OutStatusText(_T("保存文件%s时发生错误，错误代码=%d。"), szFullName, s);
		return FALSE;
	}
	else
		return TRUE;
}
//输出提示信息
void CMainDlg::OutStatusText(LPCTSTR lpMsg, ...)
{
	//根据参数格式化文本
	TCHAR szStatus[1024] = {0};
	va_list pArgs;
    va_start(pArgs, lpMsg);
    _vsntprintf(szStatus, 1020, lpMsg, pArgs);
    va_end(pArgs);
	//输出调试信息
	SetDlgItemText(m_hDlg, IDC_EDT_STATUS, szStatus);
	OutputDebugString(szStatus);
	OutputDebugString(_T("\n"));
	DoEvents();
}
//获取并保存文本框当前字符格式
void CMainDlg::GetRichEditCharFormat(CHARFORMAT2 *pCF)
{
	//得到字符格式
	ZeroMemory(pCF, sizeof(CHARFORMAT2));
	pCF->cbSize = sizeof(CHARFORMAT2);
	memset(&m_logfont, 0, sizeof(LOGFONT));
	SendDlgMsg(IDC_EDT_TEXT, EM_GETCHARFORMAT, SCF_DEFAULT, (LPARAM)pCF);	
	//保存当前颜色
	m_crText = pCF->crTextColor;
	//保存字体信息
	HWND hEdit = GetDlgItem(m_hDlg, IDC_EDT_TEXT);
    HDC  hDC   = GetDC(hEdit);
	//将缇转换为像素
    m_logfont.lfHeight = MulDiv(pCF->yHeight,
        GetDeviceCaps(hDC, LOGPIXELSY), -1440);
    ReleaseDC(hEdit, hDC);
	//字体效果
    if (pCF->dwEffects & CFE_BOLD)
        m_logfont.lfWeight = FW_BOLD;
    else
        m_logfont.lfWeight = FW_NORMAL;
    if (pCF->dwEffects & CFE_ITALIC)
        m_logfont.lfItalic = TRUE;
    if (pCF->dwEffects & CFE_UNDERLINE)
        m_logfont.lfUnderline = TRUE;
    if (pCF->dwEffects & CFE_STRIKEOUT)
        m_logfont.lfStrikeOut = TRUE;
    m_logfont.lfCharSet = pCF->bCharSet;
    m_logfont.lfQuality = DEFAULT_QUALITY;
    m_logfont.lfPitchAndFamily = pCF->bPitchAndFamily;
    _tcscpy(m_logfont.lfFaceName, pCF->szFaceName );
}
//将输入的文字绘制到内存位图中
BOOL CMainDlg::DrawRtfText()
{
	BOOL bRet = FALSE;
	HDC hDC = GetDC(m_hDlg);
	//创建一个1X1大小的内存DC，用于计算
	m_dc.CreateObj(hDC, 1, 1);
	//创建字体对象
	HFONT hFont = CreateFontIndirect(&m_logfont);
	//将字体选入DC
	HFONT hOldFont = (HFONT)SelectObject(m_dc, hFont);
	//计算文字大小
	RECT rc = {0};
	int nDraw = DrawText(m_dc, m_szText, -1, &rc, DT_CALCRECT);
	if(nDraw != 0)
	{
		//删除DC
		SelectObject(m_dc, hOldFont);
		m_dc.DeleteObj();
		//重新建立合适大小的DC
		m_dc.CreateObj(hDC, rc.right, rc.bottom);
		//设置DC参数
		hOldFont = (HFONT)SelectObject(m_dc, hFont);
		SetTextColor(m_dc, m_crText);
		SetBkMode(m_dc, TRANSPARENT);
		//绘制文本
		nDraw = DrawText(m_dc, m_szText, -1, &rc, DT_LEFT);
		bRet = (nDraw > 0);
	}
	//将字体选出DC
	SelectObject(m_dc, hOldFont);
	//删除字体对象
	DeleteObject(hFont);
	//释放窗口DC
	ReleaseDC(m_hDlg, hDC);
	if(!bRet)
		m_dc.DeleteObj();
	return bRet;
}