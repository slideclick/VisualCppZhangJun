; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMP3PlayerDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "MP3Player.h"

ClassCount=2
Class1=CMP3PlayerApp
Class2=CMP3PlayerDlg

ResourceCount=3
Resource2=IDR_MAINFRAME
Resource3=IDD_MP3PLAYER_DIALOG

[CLS:CMP3PlayerApp]
Type=0
HeaderFile=MP3Player.h
ImplementationFile=MP3Player.cpp
Filter=N

[CLS:CMP3PlayerDlg]
Type=0
HeaderFile=MP3PlayerDlg.h
ImplementationFile=MP3PlayerDlg.cpp
Filter=D
LastObject=IDC_LIT_MUSIC
BaseClass=CDialog
VirtualFilter=dWC



[DLG:IDD_MP3PLAYER_DIALOG]
Type=1
Class=CMP3PlayerDlg
ControlCount=5
Control1=IDC_LIT_MUSIC,listbox,1353777409
Control2=IDC_BTN_ADD,button,1342242816
Control3=IDC_BTN_REMOVE,button,1342242816
Control4=IDC_BTN_PLAY,button,1342242816
Control5=IDC_SLIDER,msctls_trackbar32,1342242840

