#include <windows.h>
#include <commctrl.h>
#include "resource.h"
#pragma comment(lib, "comctl32.lib")
//ATL���ͷ�ļ��ɿ��ļ�
#include <atlbase.h>
extern CComModule _Module;
#include <atlcom.h>
#include <atlwin.h>
#pragma comment(lib,"atl")
//DirectX���ͷ�ļ��Ϳ��ļ�
#include <dshow.h> 
#include <Qedit.h>
#pragma comment(lib, "strmiids.lib")
//�궨��
#define SafeRelease(x) if(x){x->Release();x=NULL;}
#define MAX_DEVICE 128
//��������
HINSTANCE GetInstance();