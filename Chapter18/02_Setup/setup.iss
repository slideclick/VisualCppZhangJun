[Setup]
AppName=�ҵĳ���
AppVerName=�ҵĳ��� 1.0
AppPublisher=�ҵĹ�˾
AppPublisherURL=http://www.WanMeiTech.com
AppSupportURL=http://www.WanMeiTech.com
AppUpdatesURL=http://www.WanMeiTech.com
DefaultDirName={pf}\�ҵĳ���
DefaultGroupName=�ҵĳ���
OutputDir=.\
OutputBaseFilename=setup
Compression=lzma
SolidCompression=yes

[Languages]
Name: "chinese"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "..\..\Chapter01\02_HelloWindows\HelloWindows.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\01_MyHelp\MyHelp.chm"; DestDir: "{app}"; Flags: ignoreversion
; ע��: ��Ҫ���κι���ϵͳ�ļ���ʹ�á�Flags: ignoreversion��

[Icons]
Name: "{group}\�ҵĳ���"; Filename: "{app}\HelloWindows.exe"
Name: "{userdesktop}\�ҵĳ���"; Filename: "{app}\HelloWindows.exe"; Tasks: desktopicon

[Run]
Filename: "{app}\HelloWindows.exe"; Description: "{cm:LaunchProgram,�ҵĳ���}"; Flags: nowait postinstall skipifsilent

