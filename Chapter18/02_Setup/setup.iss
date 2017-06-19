[Setup]
AppName=我的程序
AppVerName=我的程序 1.0
AppPublisher=我的公司
AppPublisherURL=http://www.WanMeiTech.com
AppSupportURL=http://www.WanMeiTech.com
AppUpdatesURL=http://www.WanMeiTech.com
DefaultDirName={pf}\我的程序
DefaultGroupName=我的程序
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
; 注意: 不要在任何共享系统文件上使用“Flags: ignoreversion”

[Icons]
Name: "{group}\我的程序"; Filename: "{app}\HelloWindows.exe"
Name: "{userdesktop}\我的程序"; Filename: "{app}\HelloWindows.exe"; Tasks: desktopicon

[Run]
Filename: "{app}\HelloWindows.exe"; Description: "{cm:LaunchProgram,我的程序}"; Flags: nowait postinstall skipifsilent

