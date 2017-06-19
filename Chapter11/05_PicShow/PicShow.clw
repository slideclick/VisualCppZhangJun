; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CPicShowApp
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "PicShow.h"

ClassCount=2
Class1=CPicShowApp
Class2=CPicShowDlg

ResourceCount=4
Resource2=IDR_MAINFRAME
Resource3=IDD_PICSHOW_DIALOG
Resource4=IDR_MAIN

[CLS:CPicShowApp]
Type=0
HeaderFile=PicShow.h
ImplementationFile=PicShow.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=CPicShowApp

[CLS:CPicShowDlg]
Type=0
HeaderFile=PicShowDlg.h
ImplementationFile=PicShowDlg.cpp
Filter=D
LastObject=IDR_OPEN
BaseClass=CDialog
VirtualFilter=dWC



[DLG:IDD_PICSHOW_DIALOG]
Type=1
Class=CPicShowDlg
ControlCount=0

[MNU:IDR_MAIN]
Type=1
Class=?
Command1=IDR_OPEN
CommandCount=1

