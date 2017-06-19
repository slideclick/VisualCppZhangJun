#include <windows.h>
#include <commctrl.h>
#include "resource.h"
#pragma comment(lib, "comctl32.lib")
//ATL相关头文件可库文件
#include <atlbase.h>
extern CComModule _Module;
#include <atlcom.h>
#include <atlwin.h>
#pragma comment(lib,"atl")
//DirectX相关头文件和库文件
#include <dshow.h> 
#include <Qedit.h>
#pragma comment(lib, "strmiids.lib")
//宏定义
#define SafeRelease(x) if(x){x->Release();x=NULL;}
#define MAX_DEVICE 128
//函数定义
HINSTANCE GetInstance();