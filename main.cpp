/*--------------------------------------------------------------------------*/
/* David Joffe '95/07/20 */
// Pre-1995 : something similar from QBasic or Pascal, I can't remember ...
// 1995 : original DOS/EGA version
// 1998/12/23 : begin attempted Linux port
// 1999/05 : begin attempted Win32 port, ack
// 1999/12 : re-begin attempted Win32 port
// 2001/05 : begin SDL port; doxygen comments

/*
Copyright (C) 1995-2001 David Joffe

License: GNU GPL Version 2 (*not* "later versions")
*/

/*--------------------------------------------------------------------------*/

#define INCL_DOS
#include <os2.h>
//#include <windows.h>
#include <stdio.h>


#include <time.h>   // for srand()
#include <stdlib.h> // for rand()

#include <string.h>

#include "graph.h"

//- djg lib -------------
#include "djgamelib.h"
//-----------------------

#include "hiscores.h"
#include "menu.h"
#include "game.h"
#include "level.h"
#include "keys.h"
#include "settings.h"

#include "mission.h"

#include "credits.h"
#include "instructions.h"
#include "sys_log.h"

/*--------------------------------------------------------------------------*/
djImage *pImgMain=NULL;

int  DaveStartup(bool bFullScreen);	// Application initialization
void DaveCleanup();					// Application cleanup
bool StartNewGame();				// Start new game. Return true if new high score obtained.
void SelectMission();				// Select a mission
void RedefineKeys();				// Redefine keys

void DoMainMenu();					// Start main menu

void MorphToPM();

/*--------------------------------------------------------------------------*/
// Main menu
struct SMenuItem mainMenuItems[] =
{
	{ false, "{~~~~~~~~~~~~~~~~~}" },
	{ true,  "|  Start gnu game |" },
	{ true,  "|  Select Mission |" },
	{ true,  "|  Restore game   |" },
	{ true,  "|  Ordering info  |" },
	{ true,  "|   (not!)        |" },
	{ true,  "|  Instructions   |" },
	{ true,  "|  Redefine keys  |" },
	{ true,  "|  High scores    |" },
	{ true,  "|  Credits        |" },
	{ true,  "|  Quit           |" },
	{ false, "[~~~~~~~~~~~~~~~~~]" },
	{ false, NULL }
};
unsigned char mainMenuCursor[] = { 128, 129, 130, 131, 0 };
unsigned char mainMenuCursorSkull[] = { 161, 162, 163, 164, 0 };
CMenu mainMenu;


void MorphToPM()
 {
   PPIB pib;
   PTIB tib;
 
   DosGetInfoBlocks(&tib, &pib);
 
   // Change flag from VIO to PM:
   if (pib->pib_ultype==2) pib->pib_ultype = 3;
 }

/*--------------------------------------------------------------------------*/
// This is the 'main' function. The big cheese.
int main ( int argc, char** argv )
{

        MorphToPM(); // Morph the VIO application to a PM one to be able to use Win* functions

	// Check commandline args
	bool bfullscreen = false;

	InitLog ();

	if (argc > 1)
	{
		for ( int i=1; i<argc; i++ )
		{
			if (0 == strncmp( argv[i], "-f", 2 )) bfullscreen = true;
		}
	}
	else
	{
		// Show usage information
		printf( "---------------------------------------------------------\n" );
		printf( " Command-line options:\n" );
		printf( "   -f    Fullscreen mode\n" );
		printf( "---------------------------------------------------------\n" );
	}

	// Initialize everything
	if (0 != DaveStartup(bfullscreen))
	{
		djMSG("main(): initialization failed.");
		KillLog ();
		return -1;
	}

	// Enter main menu
	DoMainMenu();

	// Cleanup
	DaveCleanup();

	KillLog ();

	return 0;
}

int DaveStartup(bool bFullScreen)
{
	g_Settings.Load(CONFIG_FILE);		// Load saved settings

	srand(time(NULL));					// Seed the random number generator

	djTimeInit();						// Initialise timer

	InitialiseGameKeySystem();			// Initialise game keys

	//-- Initialize graphics
	TRACE("DaveStartup(): Initializing graphics system ...\n");
//	if (!GraphInit( bFullScreen, 640, 480 )) // <-- 640,480 actually "works", sort of
	if (!GraphInit( bFullScreen, 320, 200 ))
	{
		TRACE( "DaveStartup(): Graphics initialization failed.\n" );
		return -1;
	}

	djSoundInit();						// Initialize sound

	pImgMain = new djImage;				// Load main skin (title screen)
	pImgMain->Load("data/main.tga");

	// Load missions
	if (0 != LoadMissions("data/missions.txt"))
		return -1;
	TRACE( "DaveStartup(): %d missions(s) found.\n", g_apMissions.size() );

	TRACE("DaveStartup(): level_init()\n");
	level_init();

	//-- Initialize input devices
	TRACE("DaveStartup(): Initializing keys ..\n");
	if (!djiInit( pVisMain, INPUT_KEYDOWN|INPUT_KEYUP|INPUT_KEYREPEAT ))
		return -1;

	mainMenu.m_clrBack = djColor(10,40,150); // Crap colour. Need something better, like a bitmap
	//mainMenu.m_clrBack = djColor(129,60,129);
	mainMenu.m_iSize = 0;
	mainMenu.m_items = mainMenuItems;
	mainMenu.m_szCursor = mainMenuCursor;
	mainMenu.m_xOffset = -1;
	mainMenu.m_yOffset = -1;
	mainMenu.m_iSoundMove = djSoundLoad( "data/sounds/cardflip.wav" );

	LoadHighScores();					// Load high scores

	GameInitialSetup();					// Once-off setup for the game itself (e.g. create in-game menu etc)

	return 0;
}

void DaveCleanup()
{
	GameFinalCleanup();		// Game
	SaveHighScores();		// Save high scores
	djiDone();				// Input
	djSoundDone();			// Sound
	GraphDone();			// Graphics
	djTimeDone();			// Timer stuff
	g_Settings.Save(CONFIG_FILE);	// Save settings
}

void DoMainMenu()
{
	bool brunning = true;
	do
	{
		int menu_option;

		// Load main menu background image
		if (pImgMain)
			djgDrawImage( pVisBack, pImgMain, 0, 0, pImgMain->Width(), pImgMain->Height() );
		GraphFlip();

		// Random select menu cursor, either hearts or skulls
		mainMenu.m_szCursor = (rand()%4==0 ? mainMenuCursorSkull : mainMenuCursor);

		menu_option = do_menu( &mainMenu );

		switch (menu_option)
		{
		case 1: // start new game
			if (StartNewGame())
				ShowHighScores();
			break;
		case 2: // select mission
			SelectMission();
			break;
		case 3: // restore game
			break;
		case 6: // instructions
			ShowInstructions();
			break;
		case 7:
			RedefineKeys();
			break;
		case 8:
			ShowHighScores();
			break;
		case 9: // credits
			ShowCredits();
			break;
		case -1: // escape
		case 10: // quit
			brunning = false;
			break;
		}

		// is this necessary?
		if (g_iKeys[DJKEY_ESC] == 1)
			brunning = false;
	} while (brunning);
}

void AppendCharacter(char *szBuffer, char c, int nMaxLen)
{
	int nStrLen = strlen(szBuffer);
	if (nStrLen<nMaxLen)
	{
		szBuffer[nStrLen] = c;
		szBuffer[nStrLen+1] = 0;
	}
}

void CornyDialogEffect(int x1, int y1, int w, int h, bool bInverted = false)
{
	// Background
	djgSetColorFore( pVisBack, djColor(170,170,170) );
	djgDrawBox( pVisBack, x1, y1, w, h );
	// dark bottom/right edge
	djgSetColorFore( pVisBack, bInverted ? djColor(230,230,230) : djColor(80,80,80) );
	djgDrawBox( pVisBack, x1, y1+h-1, w, 1);
	djgDrawBox( pVisBack, x1+w-1, y1, 1, h);
	// white top/left edge
	djgSetColorFore( pVisBack, bInverted ? djColor(80,80,80) : djColor(230,230,230) );
	djgDrawBox( pVisBack, x1, y1, w, 1);
	djgDrawBox( pVisBack, x1, y1, 1, h);
}

void RedefineKeys()
{
	int anKeys[KEY_NUMKEYS] = {0};
	bool bLoop = true;
	bool bFinished = false;
	int nCurrent = 0;
	do
	{
		int nDX = 152*2;
		int nXLeft = (320/2) - (nDX/2);

		// Black background
		djgSetColorFore( pVisBack, djColor(0,0,0) );
		djgDrawBox( pVisBack, 0, 0, 320, 200 );
		// Stupid cheesy boring dialog-border effect
		CornyDialogEffect(nXLeft, 32, nDX, 128);

		djiPollBegin();
		//SDLMod ModState = SDL_GetModState();
		SDL_Event Event;
		while (djiPollEvents(Event))
		{
			switch (Event.type)
			{
			case SDL_KEYDOWN:
				break;
			case SDL_KEYUP:
				switch (Event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					bLoop = false;
					break;
				default:
					if (bFinished)
					{
						if (Event.key.keysym.sym==SDLK_RETURN)
						{
							bLoop = false;
							// Commit changes
							int j;
							for ( j=0; j<KEY_NUMKEYS; j++ )
							{
								g_anKeys[j] = anKeys[j];
							}
							// Save into the settings object so it gets saved to disk
							StoreGameKeys();
						}
					}
					else if (IsGameKey(Event.key.keysym.sym))
					{
						anKeys[nCurrent] = Event.key.keysym.sym;
						nCurrent++;
						if (nCurrent==KEY_NUMKEYS)
						{
							bFinished = true;
						}
					}
					break;
				}
				break;
			case SDL_QUIT:
				bLoop = false;
				break;
			}
		}
		djiPollEnd();


		//CornyDialogEffect(nXLeft-4, 100, nDX+8, 16, true);
		int i;
		for ( i=0; i<KEY_NUMKEYS; i++ )
		{
			int j;
			GraphDrawString( pVisBack, g_pFont8x8, 64, 64+i*16, (unsigned char*)g_aszKeys[i]);
			for ( j=strlen(g_aszKeys[i])+1; j<14; j++ )
			{
				GraphDrawString( pVisBack, g_pFont8x8, 64+j*8, 64+i*16, (unsigned char*)".");
			}
			if (i==nCurrent)
			{
				GraphDrawString( pVisBack, g_pFont8x8, 64+14*8, 64+i*16, (unsigned char*)"( )" );
				if ((SDL_GetTicks() % 700) < 400) // Draw flashing cursor thingy
				{
					GraphDrawString( pVisBack, g_pFont8x8, 64+14*8+8, 64+i*16, (unsigned char*)"_" );
					GraphDrawString( pVisBack, g_pFont8x8, 48, 64+nCurrent*16, (unsigned char*)"=>");
				}
			}
			else if (anKeys[i]!=0)
			{
				// Show new key
				char szBuf[1024] = "";
				sprintf(szBuf, "(%s)", GetKeyString(anKeys[i]));
				GraphDrawString( pVisBack, g_pFont8x8, 64+14*8, 64+i*16, (unsigned char*)szBuf );
			}
			// Show previous key
			{
				char szBuf[1024] = "";
				sprintf(szBuf, "(%s)", GetKeyString(g_anKeys[i]));
				GraphDrawString( pVisBack, g_pFont8x8, 64+22*8, 64+i*16, (unsigned char*)szBuf );
			}
		}

		if (bFinished)
			GraphDrawString(pVisBack, g_pFont8x8, 48, 180, (unsigned char*)"Enter accepts, escape cancels");
		else
			GraphDrawString(pVisBack, g_pFont8x8, 48, 180, (unsigned char*)"Escape cancels");
		/*
		GraphDrawString( pVisBack, g_pFont8x8, 100,  72, (unsigned char*)"New high score!");
		GraphDrawString( pVisBack, g_pFont8x8,  96,  88, (unsigned char*)"Enter your name:" );
		GraphDrawString( pVisBack, g_pFont8x8, nXLeft-2, 104, (unsigned char*)szBuffer );
		if ((SDL_GetTicks() % 700) < 400) // Draw flashing cursor
		{
			unsigned char szCursor[2] = { 254, 0 };
			GraphDrawString( pVisBack, g_pFont8x8, (nXLeft-2) + 8*strlen(szBuffer), 104, szCursor );
		}
		*/

		GraphFlip();
	} while (bLoop);
}

bool GetHighScoreUserName(char *szBuffer)
{
#define MAX_HIGHSCORE_LEN 22
	bool bRet = true; // Return false if user selected quit/close or something
	bool bLoop = true;
	do
	{
		int nDX = MAX_HIGHSCORE_LEN*8;
		int nXLeft = (320/2) - (nDX / 2);

		// Black background
		djgSetColorFore( pVisBack, djColor(0,0,0) );
		djgDrawBox( pVisBack, 0, 0, 320, 200 );
		// Stupid cheesy boring dialog-border effect
		CornyDialogEffect(nXLeft-12, 64, nDX+24, 64);

		djiPollBegin();
		SDLMod ModState = SDL_GetModState();
		SDL_Event Event;
		while (djiPollEvents(Event))
		{
			switch (Event.type)
			{
			case SDL_KEYDOWN:
				if (Event.key.keysym.sym>=SDLK_a && Event.key.keysym.sym<=SDLK_z)
				{
					// I'm assuming these constants are linearly increasing, hopefully they are
					AppendCharacter(szBuffer, ((char)Event.key.keysym.sym - SDLK_a) + ((ModState & KMOD_SHIFT) ? 'A' : 'a'), MAX_HIGHSCORE_LEN);
				}
				else if (Event.key.keysym.sym>=SDLK_0 && Event.key.keysym.sym<=SDLK_9)
				{
					char acShifted[] = ")!@#$%^&*(";
					if (ModState & KMOD_SHIFT)
						AppendCharacter(szBuffer, acShifted[(char)Event.key.keysym.sym - SDLK_0], MAX_HIGHSCORE_LEN);
					else
						AppendCharacter(szBuffer, ((char)Event.key.keysym.sym - SDLK_0) + '0', MAX_HIGHSCORE_LEN);
				}
				else
				{
					switch (Event.key.keysym.sym)
					{
					case SDLK_SPACE:	AppendCharacter(szBuffer, ' ', MAX_HIGHSCORE_LEN); break;
					case SDLK_PLUS:		AppendCharacter(szBuffer, '+', MAX_HIGHSCORE_LEN); break;
					case SDLK_MINUS:	AppendCharacter(szBuffer, '-', MAX_HIGHSCORE_LEN); break;
					case SDLK_COMMA:	AppendCharacter(szBuffer, ',', MAX_HIGHSCORE_LEN); break;
					case SDLK_BACKSPACE:
						if (strlen(szBuffer)>0)
							szBuffer[strlen(szBuffer) - 1] = 0;
						break;
					}
				}
				break;
			case SDL_KEYUP:
				break;
				/*
			case SDL_QUIT:
				bLoop = false;
				bRet = false;
				break;
				*/
			}
		}
		djiPollEnd();

		if (g_iKeys[DJKEY_ESC])
		{
			bLoop = false;
			bRet = false;
		}
		// Handle this when user lets go of enter key, not when presses down, otherwise
		// event transfers to main menu and starts a gnu game immediately.
		if (!g_iKeys[DJKEY_ENTER] && g_iKeysLast[DJKEY_ENTER])
		{
			bLoop = false;
		}

		CornyDialogEffect(nXLeft-4, 100, nDX+8, 16, true);
		GraphDrawString( pVisBack, g_pFont8x8, 100,  72, (unsigned char*)"New high score!");
		GraphDrawString( pVisBack, g_pFont8x8,  96,  88, (unsigned char*)"Enter your name:" );
		GraphDrawString( pVisBack, g_pFont8x8, nXLeft-2, 104, (unsigned char*)szBuffer );
		if ((SDL_GetTicks() % 700) < 400) // Draw flashing cursor
		{
			unsigned char szCursor[2] = { 254, 0 };
			GraphDrawString( pVisBack, g_pFont8x8, (nXLeft-2) + 8*strlen(szBuffer), 104, szCursor );
		}


		GraphFlip();
	} while (bLoop);
	return bRet;
}

bool StartNewGame()
{
	int nScore = game_startup();
	if (IsNewHighScore(nScore))
	{
		char szUserName[1024] = "";
		if (GetHighScoreUserName(szUserName))
		{
			AddHighScore(szUserName, nScore);
			SaveHighScores(); // Save high scores immediately, in case Windows crashes
			return true;
		}
	}
	return false;
}

void SelectMission()
{
	int i, iret, maxlen;
	SMenuItem *pMenuItems;
	unsigned char menuMissionCursor[] = { 128, 129, 130, 131, 0 };
	CMenu menuMission;
	menuMission.m_clrBack = djColor(129,0,129);
	menuMission.m_iSize = 0;
	menuMission.m_szCursor = menuMissionCursor;
	menuMission.m_xOffset = -1;
	menuMission.m_yOffset = -1;
	menuMission.m_items = NULL;

	// Build the menu, adding mission names as entries
	maxlen = 0;
	pMenuItems = new SMenuItem[g_apMissions.size() + 3];
	for ( i=0; i<(int)g_apMissions.size(); i++ )
	{
		pMenuItems[i+1].m_bitem = true;
		pMenuItems[i+1].m_szText = new char[128];
		sprintf( pMenuItems[i+1].m_szText, "|  %-31.31s |", g_apMissions[i]->GetName() );
	}
	// Top and bottom menu entries, the borders
	pMenuItems[0].m_bitem = false;
	pMenuItems[0].m_szText = djStrDeepCopy( "{~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~}" );

	pMenuItems[g_apMissions.size()+1].m_bitem = false;
	pMenuItems[g_apMissions.size()+1].m_szText = djStrDeepCopy("[~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~]");
	pMenuItems[g_apMissions.size()+2].m_bitem = false; // Null-terminator
	pMenuItems[g_apMissions.size()+2].m_szText = NULL;

	menuMission.m_items = pMenuItems;

	// Do menu
	iret = do_menu( &menuMission );
	if (iret != -1)
	{
		g_pCurMission = g_apMissions[iret - 1];
	}

	// Unallocate menu
	for ( i=0; i<(int)g_apMissions.size() + 2; i++ )
	{
		if (pMenuItems[i].m_szText)
		{
			DELV(pMenuItems[i].m_szText);
		}
	}
	DELV(pMenuItems);
}

