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
chs.MyAppName=多语言演示程序
en.MyAppName=Multi-Language Application
chs.MyAppVerName=多语言演示程序 1.0
en.MyAppVerName=Multi-Language Application 1.0
chs.MyHelp=帮助文件
en.MyHelp=Help
chs.Uninstall=卸载程序
en.Uninstall=Uninstall
chs.Company=完美工作室
en.Company=WanMeiTech
chs.Launch=运行程序
en.Launch=Launch Program

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "..\04_MultiLanguageEx\MultiLanguage.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\01_MyHelp\MyHelp.chm"; DestDir: "{app}"; Flags: ignoreversion
; 注意: 不要在任何共享系统文件上使用“Flags: ignoreversion”

[Icons]
Name: "{group}\{cm:MyAppName}"; Filename: "{app}\MultiLanguage.exe"
Name: "{group}\{cm:MyHelp}"; Filename: "{app}\MyHelp.chm"
Name: "{userdesktop}\{cm:MyAppName}"; Filename: "{app}\MultiLanguage.exe"; Tasks: desktopicon
Name: "{group}\{cm:Uninstall}"; Filename: "{uninstallexe}"

[Run]
Filename: "{app}\MultiLanguage.exe"; Description: "{cm:Launch}"; Flags: nowait postinstall skipifsilent

