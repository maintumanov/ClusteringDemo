; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!
   
; ��� ����������
#define   Name       "ClusteringDemo"
; ������ ����������
#define   Version    "1.1"
; �����-�����������
#define   Publisher  "�����"
; ���� ����� ������������

[Setup]
AppName={#Name}
AppVersion={#Version}
DefaultDirName={pf}\SignalNet\ClusteringDemo
DefaultGroupName=SignalNet
UninstallDisplayIcon={app}\ClusteringDemo.exe
Compression=lzma2
SolidCompression=yes
OutputDir=..\!Distrib
OutputBaseFilename=SetupClusteringDemo {#Version}
AllowNoIcons=yes
;AppPublisherURL=http://signalnet.com
AppPublisher=SignalNet, LLC.
CreateUninstallRegKey=yes 

[Languages]
Name: "ru"; MessagesFile: "compiler:Languages\Russian.isl"

[Files]
Source: "..\build-ClusteringDemo-Desktop_Qt_5_15_2_MinGW_32_bit-Release\release\ClusteringDemo.exe"; DestDir: "{app}"
Source: "C:\Qt\5.15.2\mingw81_32\bin\libgcc_s_dw2-1.dll"; DestDir: "{app}"
Source: "C:\Qt\5.15.2\mingw81_32\bin\libstdc++-6.dll"; DestDir: "{app}"
Source: "C:\Qt\5.15.2\mingw81_32\bin\libwinpthread-1.dll"; DestDir: "{app}"
Source: "C:\Qt\5.15.2\mingw81_32\bin\Qt5Core.dll"; DestDir: "{app}"
Source: "C:\Qt\5.15.2\mingw81_32\bin\Qt5Gui.dll"; DestDir: "{app}"
Source: "C:\Qt\5.15.2\mingw81_32\bin\Qt5Widgets.dll"; DestDir: "{app}"
Source: "C:\Qt\5.15.2\mingw81_32\bin\Qt5WinExtras.dll"; DestDir: "{app}"


Source: "C:\Qt\5.15.2\mingw81_32\plugins\platforms\qwindows.dll"; DestDir: "{app}\platforms"
Source: "C:\Qt\5.15.2\mingw81_32\plugins\styles\qwindowsvistastyle.dll"; DestDir: "{app}\styles"
Source: "C:\Qt\5.15.2\mingw81_32\plugins\bearer\qgenericbearer.dll"; DestDir: "{app}\bearer"

[Icons]
Name: "{group}\ClusteringDemo"; Filename: "{app}\ClusteringDemo.exe"
Name: "{commondesktop}\ClusteringDemo"; Filename: "{app}\ClusteringDemo.exe"