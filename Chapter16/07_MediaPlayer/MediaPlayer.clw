; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMediaPlayerDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "MediaPlayer.h"

ClassCount=2
Class1=CMediaPlayerApp
Class2=CMediaPlayerDlg

ResourceCount=3
Resource2=IDD_MEDIAPLAYER_DIALOG
Resource1=IDR_MAINFRAME
Resource3=IDR_MENU_MAIN

[CLS:CMediaPlayerApp]
Type=0
HeaderFile=MediaPlayer.h
ImplementationFile=MediaPlayer.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=IDR_OPEN

[CLS:CMediaPlayerDlg]
Type=0
HeaderFile=MediaPlayerDlg.h
ImplementationFile=MediaPlayerDlg.cpp
Filter=W
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CMediaPlayerDlg



[DLG:IDD_MEDIAPLAYER_DIALOG]
Type=1
Class=CMediaPlayerDlg
ControlCount=1
Control1=IDC_SLIDER,msctls_trackbar32,1476460568

[MNU:IDR_MENU_MAIN]
Type=1
Class=?
Command1=IDR_OPEN
CommandCount=1

