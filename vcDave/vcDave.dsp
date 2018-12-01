# Microsoft Developer Studio Project File - Name="vcDave" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=vcDave - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "vcDave.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "vcDave.mak" CFG="vcDave - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "vcDave - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "vcDave - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/DaveGnukem/DaveGnukem/src/vcDave", IAAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "vcDave - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../../"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "USESDL" /D "VISUALC6" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"Release\vcDave.bsc"
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib dinput.lib dxguid.lib ddraw.lib dsound.lib SDL.lib SDLmain.lib SDL_mixer.lib /nologo /subsystem:windows /pdb:none /machine:I386 /out:"../../DaveGnukem.exe"

!ELSEIF  "$(CFG)" == "vcDave - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../../"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "USESDL" /D "VISUALC6" /YX /FD /GZ /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"Debug/vcDave.bsc"
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 dsound.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib dinput.lib dxguid.lib ddraw.lib SDL.lib SDLmain.lib SDL_mixer.lib /nologo /subsystem:windows /pdb:none /debug /machine:I386 /out:"../../DaveGnukem.exe"

!ENDIF 

# Begin Target

# Name "vcDave - Win32 Release"
# Name "vcDave - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "djGameLib"

# PROP Default_Filter ""
# Begin Group "win32"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\win32\winmain.cpp
# End Source File
# End Group
# Begin Group "sdl"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\sdl\djgraph.cpp
# End Source File
# Begin Source File

SOURCE=..\sdl\djinput.cpp
# End Source File
# Begin Source File

SOURCE=..\sdl\djsound.cpp
# End Source File
# Begin Source File

SOURCE=..\sdl\djtime.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=..\djimage.cpp
# End Source File
# Begin Source File

SOURCE=..\djlog.cpp
# End Source File
# Begin Source File

SOURCE=..\djstring.cpp
# End Source File
# Begin Source File

SOURCE=..\djtypes.cpp
# End Source File
# End Group
# Begin Group "Editor"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\ed.cpp
# End Source File
# Begin Source File

SOURCE=..\ed_common.cpp
# End Source File
# Begin Source File

SOURCE=..\ed_DrawBoxContents.cpp
# End Source File
# Begin Source File

SOURCE=..\ed_lvled.cpp
# End Source File
# Begin Source File

SOURCE=..\ed_macros.cpp
# End Source File
# Begin Source File

SOURCE=..\ed_spred.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=..\block.cpp
# End Source File
# Begin Source File

SOURCE=..\bullet.cpp
# End Source File
# Begin Source File

SOURCE=..\credits.cpp
# End Source File
# Begin Source File

SOURCE=..\game.cpp
# End Source File
# Begin Source File

SOURCE=..\graph.cpp
# End Source File
# Begin Source File

SOURCE=..\hero.cpp
# End Source File
# Begin Source File

SOURCE=..\hiscores.cpp
# End Source File
# Begin Source File

SOURCE=..\instructions.cpp
# End Source File
# Begin Source File

SOURCE=..\inventory.cpp
# End Source File
# Begin Source File

SOURCE=..\keys.cpp
# End Source File
# Begin Source File

SOURCE=..\level.cpp
# End Source File
# Begin Source File

SOURCE=..\m_misc.cpp
# End Source File
# Begin Source File

SOURCE=..\main.cpp
# End Source File
# Begin Source File

SOURCE=..\menu.cpp
# End Source File
# Begin Source File

SOURCE=..\mission.cpp
# End Source File
# Begin Source File

SOURCE=..\mixins.cpp
# End Source File
# Begin Source File

SOURCE=..\settings.cpp
# End Source File
# Begin Source File

SOURCE=..\sys_error.cpp
# End Source File
# Begin Source File

SOURCE=..\sys_log.cpp
# End Source File
# Begin Source File

SOURCE=..\thing.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "djGameLibHeaders"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\djgamelib.h
# End Source File
# Begin Source File

SOURCE=..\djgraph.h
# End Source File
# Begin Source File

SOURCE=..\djimage.h
# End Source File
# Begin Source File

SOURCE=..\djinput.h
# End Source File
# Begin Source File

SOURCE=..\djlog.h
# End Source File
# Begin Source File

SOURCE=..\djsound.h
# End Source File
# Begin Source File

SOURCE=..\djstring.h
# End Source File
# Begin Source File

SOURCE=..\djtime.h
# End Source File
# Begin Source File

SOURCE=..\djtypes.h
# End Source File
# End Group
# Begin Group "EditorHeaders"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\ed.h
# End Source File
# Begin Source File

SOURCE=..\ed_common.h
# End Source File
# Begin Source File

SOURCE=..\ed_DrawBoxContents.h
# End Source File
# Begin Source File

SOURCE=..\ed_lvled.h
# End Source File
# Begin Source File

SOURCE=..\ed_macros.h
# End Source File
# Begin Source File

SOURCE=..\ed_spred.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\block.h
# End Source File
# Begin Source File

SOURCE=..\bullet.h
# End Source File
# Begin Source File

SOURCE=..\credits.h
# End Source File
# Begin Source File

SOURCE=..\datadir.h
# End Source File
# Begin Source File

SOURCE=..\game.h
# End Source File
# Begin Source File

SOURCE=..\graph.h
# End Source File
# Begin Source File

SOURCE=..\hero.h
# End Source File
# Begin Source File

SOURCE=..\hiscores.h
# End Source File
# Begin Source File

SOURCE=..\instructions.h
# End Source File
# Begin Source File

SOURCE=..\inventory.h
# End Source File
# Begin Source File

SOURCE=..\keys.h
# End Source File
# Begin Source File

SOURCE=..\level.h
# End Source File
# Begin Source File

SOURCE=..\m_aliases.h
# End Source File
# Begin Source File

SOURCE=..\m_misc.h
# End Source File
# Begin Source File

SOURCE=..\menu.h
# End Source File
# Begin Source File

SOURCE=..\mission.h
# End Source File
# Begin Source File

SOURCE=..\mixins.h
# End Source File
# Begin Source File

SOURCE=..\settings.h
# End Source File
# Begin Source File

SOURCE=..\sys_defs.h
# End Source File
# Begin Source File

SOURCE=..\sys_error.h
# End Source File
# Begin Source File

SOURCE=..\sys_log.h
# End Source File
# Begin Source File

SOURCE=..\thing.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "Documentation"

# PROP Default_Filter ""
# Begin Group "Doxygen"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\documentation\doxygen\doxygen.cfg
# End Source File
# Begin Source File

SOURCE=..\..\documentation\doxygen\FooterFile.html
# End Source File
# Begin Source File

SOURCE=..\..\documentation\doxygen\HeaderFile.html
# End Source File
# Begin Source File

SOURCE=..\..\documentation\doxygen\mainpage.txt
# End Source File
# Begin Source File

SOURCE=..\..\documentation\doxygen\styles.css
# End Source File
# End Group
# End Group
# Begin Group "Data"

# PROP Default_Filter ""
# Begin Group "games"

# PROP Default_Filter ""
# Begin Group "tog"

# PROP Default_Filter ""
# Begin Source File

SOURCE="..\..\data\tog\tog-bg-black.tga"
# End Source File
# Begin Source File

SOURCE="..\..\data\tog\tog-lev_0.lev"
# End Source File
# Begin Source File

SOURCE="..\..\data\tog\tog-lev_1.lev"
# End Source File
# Begin Source File

SOURCE="..\..\data\tog\tog-lev_2.lev"
# End Source File
# Begin Source File

SOURCE="..\..\data\tog\tog-lev_3.lev"
# End Source File
# Begin Source File

SOURCE="..\..\data\tog\tog-spr_16.bmp"
# End Source File
# Begin Source File

SOURCE="..\..\data\tog\tog-spr_16.dat"
# End Source File
# Begin Source File

SOURCE="..\..\data\tog\tog-spr_16.psd"
# End Source File
# Begin Source File

SOURCE="..\..\data\tog\tog-spr_16.tga"
# End Source File
# Begin Source File

SOURCE=..\..\data\tog\tog.gam
# End Source File
# Begin Source File

SOURCE="..\..\data\tog\zz-empty.lev"
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\data\default.gam
# End Source File
# Begin Source File

SOURCE=..\..\data\foo.gam
# End Source File
# End Group
# Begin Group "sprites"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\data\sprites\def0spr.dat
# End Source File
# Begin Source File

SOURCE=..\..\data\sprites\def1spr.dat
# End Source File
# Begin Source File

SOURCE=..\..\data\sprites\def2spr.dat
# End Source File
# Begin Source File

SOURCE=..\..\data\sprites\def3spr.dat
# End Source File
# Begin Source File

SOURCE=..\..\data\sprites\def4spr.dat
# End Source File
# Begin Source File

SOURCE=..\..\data\sprites\def5spr.dat
# End Source File
# Begin Source File

SOURCE=..\..\data\sprites\def6spr.dat
# End Source File
# Begin Source File

SOURCE=..\..\data\sprites\def7spr.dat
# End Source File
# Begin Source File

SOURCE=..\..\data\sprites\foo0spr.dat
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\data\missions.txt
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\HISTORY.txt
# End Source File
# Begin Source File

SOURCE=..\..\TODO.txt
# End Source File
# End Target
# End Project
