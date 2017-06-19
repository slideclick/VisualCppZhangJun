; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CColorStatusBarDlg
LastTemplate=CStatic
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ColorStatusBar.h"

ClassCount=3
Class1=CColorStatusBarApp
Class2=CColorStatusBarDlg

ResourceCount=2
Resource1=IDR_MAINFRAME
Class3=CColorProgress
Resource2=IDD_COLORSTATUSBAR_DIALOG

[CLS:CColorStatusBarApp]
Type=0
HeaderFile=ColorStatusBar.h
ImplementationFile=ColorStatusBar.cpp
Filter=N

[CLS:CColorStatusBarDlg]
Type=0
HeaderFile=ColorStatusBarDlg.h
ImplementationFile=ColorStatusBarDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CColorStatusBarDlg



[DLG:IDD_COLORSTATUSBAR_DIALOG]
Type=1
Class=CColorStatusBarDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_BTN_RESET,button,1342242816

[CLS:CColorProgress]
Type=0
HeaderFile=ColorProgress.h
ImplementationFile=ColorProgress.cpp
BaseClass=CStatic
Filter=W

