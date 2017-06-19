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
	//��ʼ������
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
//�����Ի���
int CMainDlg::DoModal()
{
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
//��ʼ���Ի���
BOOL CMainDlg::OnInitDialog(HWND hWnd)
{
	//������
	m_hDlg		= hWnd;
	//Ӧ�ó���ͼ��
	m_hAppIcon	= LoadIcon(GetInstance(), MAKEINTRESOURCE(IDI_APP));
	//���ô�ͼ��
	SendMessage(m_hDlg, WM_SETICON, ICON_BIG, (LPARAM)m_hAppIcon);
	//����Сͼ��
	SendMessage(m_hDlg, WM_SETICON, ICON_SMALL, (LPARAM)m_hAppIcon);
	//��ʼ��������λ�á�������
	SendDlgMsg(IDC_CMB_ALIGN, CB_ADDSTRING, 0, (LPARAM)_T("����"));
	SendDlgMsg(IDC_CMB_ALIGN, CB_ADDSTRING, 0, (LPARAM)_T("����"));
	SendDlgMsg(IDC_CMB_ALIGN, CB_ADDSTRING, 0, (LPARAM)_T("����"));
	SendDlgMsg(IDC_CMB_ALIGN, CB_ADDSTRING, 0, (LPARAM)_T("����"));
	SendDlgMsg(IDC_CMB_ALIGN, CB_ADDSTRING, 0, (LPARAM)_T("�м�"));
	SendDlgMsg(IDC_CMB_ALIGN, CB_SETCURSEL, 0, 0);
	//��ʼ����͸���ȡ�
	SendDlgMsg(IDC_SLIDER_ALPHA, TBM_SETRANGE, FALSE, MAKELONG(0, 255));
	SendDlgMsg(IDC_SLIDER_ALPHA, TBM_SETPOS, TRUE, m_nAlpha);
	SetDlgItemInt(m_hDlg, IDC_ALPHA, m_nAlpha, FALSE) ;
	//�����ı������������ַ���
	SendDlgMsg(IDC_EDT_TEXT, EM_LIMITTEXT, MAX_CHARS, 0);
	//�����ı���Ĭ����ɫ�������С
	CHARFORMAT2 cfm;
	ZeroMemory(&cfm, sizeof(CHARFORMAT2));
	cfm.cbSize = sizeof(CHARFORMAT2);
	SendDlgMsg(IDC_EDT_TEXT, EM_GETCHARFORMAT, SCF_DEFAULT, (LPARAM)&cfm);
	cfm.yHeight = 320;
	cfm.crTextColor = RGB(255, 0, 0);
	cfm.dwEffects = CFE_BOLD;
	SendDlgMsg(IDC_EDT_TEXT, EM_SETCHARFORMAT, SCF_DEFAULT, (LPARAM)&cfm);
	//�����ı��򱳾�ɫ
	SendDlgMsg(IDC_EDT_TEXT, EM_SETBKGNDCOLOR, 0, 0);
	return TRUE;
}
//����ǰ��Ϣ
void CMainDlg::OnDestroy()
{
	DestroyIcon(m_hAppIcon);
}
//WM_COMMAND��Ϣ��Ӧ
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
//����ʼ����ť��Ӧ����
void CMainDlg::OnOk()
{
	//ȡ���û�����
	//ȡ��ͼƬ·��
	UINT nLen = GetDlgItemText(m_hDlg, IDC_EDT_PATH, m_szImagePath, MAX_PATH);
	if(nLen == 0)
	{
		MessageBox(m_hDlg, _T("������ͼƬ�ļ�����·����"), _T("��ʾ"), 
			MB_OK | MB_ICONWARNING);
		return;
	}
	if(m_szImagePath[nLen - 1] != _T('\\'))
		_tcscat(m_szImagePath, _T("\\"));
	//ȡ�����������
	nLen = GetDlgItemText(m_hDlg, IDC_EDT_TEXT, m_szText, MAX_CHARS);
	if(nLen == 0)
	{
		MessageBox(m_hDlg, _T("������Ҫ���Ƶ����֣�"), _T("��ʾ"), 
			MB_OK | MB_ICONWARNING);
		return;
	}
	//ȡ���������ɫ��Ϣ
	CHARFORMAT2 cfm;
	GetRichEditCharFormat(&cfm);
	//ȡ������λ��
	m_nTextSite = SendDlgMsg(IDC_CMB_ALIGN, CB_GETCURSEL, 0, 0);
	//ȡ��͸����
	m_nAlpha = SendDlgMsg(IDC_SLIDER_ALPHA, TBM_GETPOS, 0, 0);
	
	//��������·��
	TCHAR szPath[MAX_PATH];
	_tcscpy(szPath, m_szImagePath);
	_tcscat(szPath, _T("*.*"));
	//�����ļ�
	int nCount = 0;
	WIN32_FIND_DATA fd = {0};
	HANDLE hFind = FindFirstFile(szPath, &fd);
	if(hFind == INVALID_HANDLE_VALUE )
	{
		MessageBox(m_hDlg, _T("��ѡĿ¼û���ļ���"), _T("��ʾ"), 
			MB_OK | MB_ICONWARNING);
		return;
	}
	//�������ֵ���ʱλͼ��
	if(!DrawRtfText())
	{
		DebugBreak();
	}
	//ѭ�������ļ�
	do
	{
		if(!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			OutStatusText(_T("���ڴ����ļ���%s��"), fd.cFileName);
			if(ProcessFile(fd.cFileName))
				nCount ++;
		}
	} while(FindNextFile(hFind, &fd));
	//��������
	FindClose(hFind);
	//ɾ��GDI����
	m_dc.DeleteObj();		
	//��ʾ���
	OutStatusText(_T("�ѳɹ�����%d���ļ���"), nCount);
}
//���������ť����Ӧ����
void CMainDlg::OnBtnBrowse()
{
	CFolderDlg dlg(NULL, _T("��ѡ��ͼƬ����Ŀ¼"));
	if(dlg.ShowDlg(m_hDlg))
		SetDlgItemText(m_hDlg, IDC_EDT_PATH, dlg.GetSelectedPath());
}
//�����塱��ť����Ӧ����
void CMainDlg::OnBtnFont()
{
	//��ȡ�ı���ǰ����
	CHARFORMAT2 cfm;
	GetRichEditCharFormat(&cfm);
	//����Ի���ѡ��
    CHOOSEFONT cf;
    memset(&cf, 0, sizeof(CHOOSEFONT));
    cf.rgbColors = cfm.crTextColor;
    cf.lStructSize = sizeof(CHOOSEFONT);
    cf.hwndOwner = m_hDlg;
    cf.lpLogFont = &m_logfont;
    cf.Flags = CF_SCREENFONTS | CF_EFFECTS | CF_INITTOLOGFONTSTRUCT;
    //ѡ������
    if (ChooseFont(&cf))
    {
		//����CHOOSEFONT�ṹ�е�ֵ���趨CHARFORMAT2�е�ֵ
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
		//�����ı�������
        SendDlgMsg(IDC_EDT_TEXT, EM_SETCHARFORMAT, SCF_ALL, (LPARAM)&cfm); 
    }
}
//����ɫ����ť����Ӧ����
void CMainDlg::OnBtnColor()
{
	//��ȡ�ı���ǰ��ɫ
	CHARFORMAT2 cf;
	GetRichEditCharFormat(&cf);
	//��ɫ�Ի���ѡ��
	CHOOSECOLOR cc = {0};
	cc.lStructSize = sizeof(cc);
	cc.Flags = CC_RGBINIT | CC_FULLOPEN | CC_ANYCOLOR;
	cc.hwndOwner = m_hDlg;
	cc.lpCustColors = g_crCustom;
	cc.rgbResult = cf.crTextColor;
	//ѡ����ɫ
	if(ChooseColor(&cc))
	{
		//�����ı�����ɫ
		cf.dwMask = CFM_COLOR;
		cf.dwEffects = 0;
		cf.crTextColor = cc.rgbResult;
		SendDlgMsg(IDC_EDT_TEXT, EM_SETCHARFORMAT, SCF_ALL, (LPARAM)&cf);
	}
}
//ˮƽ��������Ϣ
void CMainDlg::OnHScroll(WPARAM wp, LPARAM lp)
{
	int nPos = SendDlgMsg(IDC_SLIDER_ALPHA, TBM_GETPOS, 0, 0);
	SetDlgItemInt(m_hDlg, IDC_ALPHA, nPos, FALSE);
}
//��ĳ���ؼ�������Ϣ
int CMainDlg::SendDlgMsg(int nID, UINT nMsg, WPARAM wp, LPARAM lp)
{
	return SendDlgItemMessage(m_hDlg, nID, nMsg, wp, lp);
}
//�����ļ���ʽ��ȡ�������CLSID
BOOL CMainDlg::FindEncoder(GUID *pFormat, CLSID *pClsid)
{
	//��ȡ����������
    UINT  nNum = 0;  
    UINT  nSize = 0;
    ImageCodecInfo* pImageCodecInfo = NULL;
    GetImageEncodersSize(&nNum, &nSize);
    if(nSize == 0)
        return FALSE;
    //��ȡ���б�����
    pImageCodecInfo = (ImageCodecInfo*)(malloc(nSize));
    if(pImageCodecInfo == NULL)
        return FALSE;
    GetImageEncoders(nNum, nSize, pImageCodecInfo);
    //������Ҫ�ı�����
    for(UINT i = 0; i < nNum; ++i)
    {
        if(pImageCodecInfo[i].FormatID  == *pFormat)
        {
			//�ҵ�ƥ��ı�����
            *pClsid = pImageCodecInfo[i].Clsid;
            free(pImageCodecInfo);
            return TRUE;
        }    
    }
    free(pImageCodecInfo);
    return FALSE;
}
//�����ļ�
BOOL CMainDlg::ProcessFile(LPCTSTR lpFile)
{
	//���ļ�����Ŀ¼����������ļ�·��
	TCHAR szFullName[MAX_PATH];
	_tcscpy(szFullName, m_szImagePath);
	_tcscat(szFullName, lpFile);
	//ȷ���ļ�·���ǿ��ַ���
	WCHAR wszFile[MAX_PATH] = {0};
#ifdef UNICODE
	_tcscpy(wszFile, szFullName);
#else
	MultiByteToWideChar(CP_ACP, 0, szFullName, -1, 
		wszFile, sizeof(wszFile)/sizeof(wszFile[0])); 
#endif
	//�õ��ļ��ĸ�ʽ
	//�����ļ�
	Bitmap img(wszFile);
	Status s = img.GetLastStatus();
	if(s != Ok)
	{
		OutStatusText(_T("���ļ�%sʱ�������󣬴������=%d��"), 
			szFullName, s);
		return FALSE;
	}
	//��ȡ��ʽ������
	GUID guid;
	img.GetRawFormat(&guid);
	CLSID clsid;
	if(!FindEncoder(&guid, &clsid))
	{
		OutStatusText(_T("�޷��ҵ��ļ�%s�ı�������"), szFullName);
		return FALSE;
	}
	//�������ֻ���λ��
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
	//ѭ��Ϊ����ÿ����
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
			//ȡ��Դ��ɫ�����Ϊ0����ʾ͸��
			crSrc = GetPixel(m_dc, x, y);
			if(crSrc > 0)
			{
				//��ȡԴ��3��ɫ
				nSrcR = GetRValue(crSrc);
				nSrcG = GetGValue(crSrc);
				nSrcB = GetBValue(crSrc);
				//��ȡĿ����ɫ��pt����λ��ƫ����
				img.GetPixel(pt.x + x, pt.y + y, &crDest);
				//ȡ��Ŀ���3��ɫ
				nDestR = crDest.GetR();
				nDestG = crDest.GetG();
				nDestB = crDest.GetB();
				//��͸���ȼ�������ɫ
				nDestR = nSrcR * m_nAlpha / 255 + nDestR * (255 - m_nAlpha) / 255;
				nDestG = nSrcG * m_nAlpha / 255 + nDestG * (255 - m_nAlpha) / 255;
				nDestB = nSrcB * m_nAlpha / 255 + nDestB * (255 - m_nAlpha) / 255;
				//�����µ�Ŀ����ɫ
				crDest.SetFromCOLORREF(RGB(nDestR, nDestG, nDestB));
				//����ɫ���õ�ͼƬ
				img.SetPixel(pt.x + x, pt.y + y, crDest);
			}
		}
	}
	//�µ��ļ�·�����ļ���
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
	//�����������Ŀ¼
	CreateDirectoryW(wszNewFile, NULL);
	wcscat(wszNewFile, p);
	//�������ļ�
	s = img.Save(wszNewFile, &clsid, NULL);
	if(s != Ok)
	{
		OutStatusText(_T("�����ļ�%sʱ�������󣬴������=%d��"), szFullName, s);
		return FALSE;
	}
	else
		return TRUE;
}
//�����ʾ��Ϣ
void CMainDlg::OutStatusText(LPCTSTR lpMsg, ...)
{
	//���ݲ�����ʽ���ı�
	TCHAR szStatus[1024] = {0};
	va_list pArgs;
    va_start(pArgs, lpMsg);
    _vsntprintf(szStatus, 1020, lpMsg, pArgs);
    va_end(pArgs);
	//���������Ϣ
	SetDlgItemText(m_hDlg, IDC_EDT_STATUS, szStatus);
	OutputDebugString(szStatus);
	OutputDebugString(_T("\n"));
	DoEvents();
}
//��ȡ�������ı���ǰ�ַ���ʽ
void CMainDlg::GetRichEditCharFormat(CHARFORMAT2 *pCF)
{
	//�õ��ַ���ʽ
	ZeroMemory(pCF, sizeof(CHARFORMAT2));
	pCF->cbSize = sizeof(CHARFORMAT2);
	memset(&m_logfont, 0, sizeof(LOGFONT));
	SendDlgMsg(IDC_EDT_TEXT, EM_GETCHARFORMAT, SCF_DEFAULT, (LPARAM)pCF);	
	//���浱ǰ��ɫ
	m_crText = pCF->crTextColor;
	//����������Ϣ
	HWND hEdit = GetDlgItem(m_hDlg, IDC_EDT_TEXT);
    HDC  hDC   = GetDC(hEdit);
	//���ת��Ϊ����
    m_logfont.lfHeight = MulDiv(pCF->yHeight,
        GetDeviceCaps(hDC, LOGPIXELSY), -1440);
    ReleaseDC(hEdit, hDC);
	//����Ч��
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
//����������ֻ��Ƶ��ڴ�λͼ��
BOOL CMainDlg::DrawRtfText()
{
	BOOL bRet = FALSE;
	HDC hDC = GetDC(m_hDlg);
	//����һ��1X1��С���ڴ�DC�����ڼ���
	m_dc.CreateObj(hDC, 1, 1);
	//�����������
	HFONT hFont = CreateFontIndirect(&m_logfont);
	//������ѡ��DC
	HFONT hOldFont = (HFONT)SelectObject(m_dc, hFont);
	//�������ִ�С
	RECT rc = {0};
	int nDraw = DrawText(m_dc, m_szText, -1, &rc, DT_CALCRECT);
	if(nDraw != 0)
	{
		//ɾ��DC
		SelectObject(m_dc, hOldFont);
		m_dc.DeleteObj();
		//���½������ʴ�С��DC
		m_dc.CreateObj(hDC, rc.right, rc.bottom);
		//����DC����
		hOldFont = (HFONT)SelectObject(m_dc, hFont);
		SetTextColor(m_dc, m_crText);
		SetBkMode(m_dc, TRANSPARENT);
		//�����ı�
		nDraw = DrawText(m_dc, m_szText, -1, &rc, DT_LEFT);
		bRet = (nDraw > 0);
	}
	//������ѡ��DC
	SelectObject(m_dc, hOldFont);
	//ɾ���������
	DeleteObject(hFont);
	//�ͷŴ���DC
	ReleaseDC(m_hDlg, hDC);
	if(!bRet)
		m_dc.DeleteObj();
	return bRet;
}