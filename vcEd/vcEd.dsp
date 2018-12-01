# Microsoft Developer Studio Project File - Name="vcEd" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=vcEd - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "vcEd.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "vcEd.mak" CFG="vcEd - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "vcEd - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "vcEd - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/DaveGnukem/DaveGnukem/src/vcEd", JAAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "vcEd - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "USESDL" /D "VISUALC6" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"Release\vcEd.bsc"
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib dinput.lib dxguid.lib ddraw.lib dsound.lib winmm.lib SDL.lib SDLmain.lib SDL_mixer.lib /nologo /subsystem:windows /pdb:none /machine:I386 /out:"../../LevelEd.exe"

!ELSEIF  "$(CFG)" == "vcEd - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "USESDL" /D "VISUALC6" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"Debug/vcEd.bsc"
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib dinput.lib dxguid.lib ddraw.lib dsound.lib winmm.lib SDL.lib SDLmain.lib SDL_mixer.lib /nologo /subsystem:windows /pdb:none /debug /machine:I386 /out:"../../LevelEd.exe"

!ENDIF 

# Begin Target

# Name "vcEd - Win32 Release"
# Name "vcEd - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "djGameLib"

# PROP Default_Filter ""
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
# Begin Source File

SOURCE=..\win32\winmain.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=..\block.cpp
# End Source File
# Begin Source File

SOURCE=..\ed_standalone_original.cpp
# End Source File
# Begin Source File

SOURCE=..\level.cpp
# End Source File
# Begin Source File

SOURCE=..\m_misc.cpp
# End Source File
# Begin Source File

SOURCE=..\mission.cpp
# End Source File
# Begin Source File

SOURCE=..\mixins.cpp
# End Source File
# Begin Source File

SOURCE=..\sys_error.cpp
# End Source File
# Begin Source File

SOURCE=..\sys_log.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "djGameLibHeader"

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
# Begin Source File

SOURCE=..\block.h
# End Source File
# Begin Source File

SOURCE=..\datadir.h
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

SOURCE=..\mission.h
# End Source File
# Begin Source File

SOURCE=..\mixins.h
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
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=..\..\TODO.txt
# End Source File
# End Target
# End Project
