; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAnimatedWndDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "AnimatedWnd.h"

ClassCount=3
Class1=CAnimatedWndApp
Class2=CAnimatedWndDlg

ResourceCount=3
Resource2=IDD_ANIMATEDWND_DIALOG
Resource1=IDR_MAINFRAME
Class3=CAnimatedDlg
Resource3=IDD_ANIMATED

[CLS:CAnimatedWndApp]
Type=0
HeaderFile=AnimatedWnd.h
ImplementationFile=AnimatedWnd.cpp
Filter=N

[CLS:CAnimatedWndDlg]
Type=0
HeaderFile=AnimatedWndDlg.h
ImplementationFile=AnimatedWndDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CAnimatedWndDlg



[DLG:IDD_ANIMATEDWND_DIALOG]
Type=1
Class=CAnimatedWndDlg
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDC_BTN_HIDE,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_CMB_ANIMATETYPE,combobox,1344339971
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDT_TIME,edit,1350639744

[DLG:IDD_ANIMATED]
Type=1
Class=CAnimatedDlg
ControlCount=1
Control1=IDC_STATIC,static,1342308353

[CLS:CAnimatedDlg]
Type=0
HeaderFile=AnimatedDlg.h
ImplementationFile=AnimatedDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CAnimatedDlg
VirtualFilter=dWC

