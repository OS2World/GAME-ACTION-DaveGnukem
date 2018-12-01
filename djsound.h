/*--------------------------------------------------------------------------*/
// djsound.h
//
// Sound interface
/*
Copyright (C) 1999-2002 David Joffe

License: GNU GPL Version 2 (*not* "later versions")
*/
/*--------------------------------------------------------------------------*/
#ifndef _DJSOUND_H_
#define _DJSOUND_H_
/*--------------------------------------------------------------------------*/

#include <vector>
using namespace std;

typedef unsigned int SOUND_HANDLE;
#define SOUNDHANDLE_INVALID ((unsigned int)~0)

extern bool bSoundEnabled;
// not all sound cards have a mixer
extern bool bHaveMixer;

extern int          djSoundInit();
extern void         djSoundDone();
extern void         djSoundEnable();
extern void         djSoundDisable();
extern bool         djSoundEnabled();
extern SOUND_HANDLE djSoundLoad( char *szFilename );
extern bool         djSoundPlay( SOUND_HANDLE iHandle );

#ifdef WIN32

//#include <dsound.h>
#include <stdio.h>

/* Obsolete ..

  struct SdjSound
{
	SOUND_HANDLE         m_iHandle;
	char                *m_szFilename;
	LPDIRECTSOUNDBUFFER  m_pSoundBuffer;
};
extern vector<SdjSound> g_aSounds;

struct WaveHeader
{
    BYTE        RIFF[4];          // "RIFF"
    DWORD       dwSize;           // Size of data to follow
    BYTE        WAVE[4];          // "WAVE"
    BYTE        fmt_[4];          // "fmt "
    DWORD       dw16;             // 16
    WORD        wOne_0;           // 1
    WORD        wChnls;           // Number of Channels
    DWORD       dwSRate;          // Sample Rate
    DWORD       BytesPerSec;      // Sample Rate
    WORD        wBlkAlign;        // 1
    WORD        BitsPerSample;    // Sample size
    BYTE        DATA[4];          // "DATA"
    DWORD       dwDSize;          // Number of Samples
};
*/

#endif

#endif
