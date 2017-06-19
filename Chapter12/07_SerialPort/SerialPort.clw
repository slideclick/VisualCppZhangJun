; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSerialPortDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "SerialPort.h"

ClassCount=2
Class1=CSerialPortApp
Class2=CSerialPortDlg

ResourceCount=3
Resource2=IDR_MAINFRAME
Resource3=IDD_SERIALPORT_DIALOG

[CLS:CSerialPortApp]
Type=0
HeaderFile=SerialPort.h
ImplementationFile=SerialPort.cpp
Filter=N

[CLS:CSerialPortDlg]
Type=0
HeaderFile=SerialPortDlg.h
ImplementationFile=SerialPortDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CSerialPortDlg



[DLG:IDD_SERIALPORT_DIALOG]
Type=1
Class=CSerialPortDlg
ControlCount=6
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDT_READ,edit,1353783428
Control3=IDC_EDT_WRITE,edit,1353781380
Control4=IDC_BTN_WRITE,button,1476460544
Control5=IDC_CMB_COM,combobox,1344339971
Control6=IDC_BTN_OPEN,button,1342242816

