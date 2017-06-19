[Setup]
AppName={cm:MyAppName}
AppVerName={cm:MyAppVerName}
AppPublisher={cm:Company}
AppPublisherURL=http://www.WanMeiTech.com
AppSupportURL=http://www.WanMeiTech.com
AppUpdatesURL=http://www.WanMeiTech.com
DefaultDirName={pf}\{cm:MyAppName}
DefaultGroupName={cm:MyAppName}
OutputDir=.\
OutputBaseFilename=setupex
Compression=lzma
SolidCompression=yes

[Languages]
Name: "en"; MessagesFile: "compiler:Languages\English.isl"
Name: "chs"; MessagesFile: "compiler:Default.isl"

[Messages]
en.BeveledLabel=English
chs.BeveledLabel=Simplified Chinese

[CustomMessages]
chs.MyAppName=��������ʾ����
en.MyAppName=Multi-Language Application
chs.MyAppVerName=��������ʾ���� 1.0
en.MyAppVerName=Multi-Language Application 1.0
chs.MyHelp=�����ļ�
en.MyHelp=Help
chs.Uninstall=ж�س���
en.Uninstall=Uninstall
chs.Company=����������
en.Company=WanMeiTech
chs.Launch=���г���
en.Launch=Launch Program

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "..\04_MultiLanguageEx\MultiLanguage.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\01_MyHelp\MyHelp.chm"; DestDir: "{app}"; Flags: ignoreversion
; ע��: ��Ҫ���κι���ϵͳ�ļ���ʹ�á�Flags: ignoreversion��

[Icons]
Name: "{group}\{cm:MyAppName}"; Filename: "{app}\MultiLanguage.exe"
Name: "{group}\{cm:MyHelp}"; Filename: "{app}\MyHelp.chm"
Name: "{userdesktop}\{cm:MyAppName}"; Filename: "{app}\MultiLanguage.exe"; Tasks: desktopicon
Name: "{group}\{cm:Uninstall}"; Filename: "{uninstallexe}"

[Run]
Filename: "{app}\MultiLanguage.exe"; Description: "{cm:Launch}"; Flags: nowait postinstall skipifsilent

