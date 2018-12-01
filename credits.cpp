/*********
  credits.cpp

  Copyright (C) 1999-2001 David Joffe
  
  License: GNU GPL Version 2 (*not* "later versions")
*********/
#include <stdlib.h> // for NULL
#include "djtypes.h"
#include "credits.h"
#include "menu.h"
#include "graph.h"

djImage *pImageCredits=NULL;

struct SMenuItem creditsMenuItems[] =
{
   { false, "        " },
   { true,  "   OK   " },
   { false, "        " },
   { false, NULL }     
};
unsigned char creditsMenuCursor[] = { 128, 129, 130, 131, 0 };
CMenu creditsMenu;

int credits_init()
{
	// Load credits bitmap
	if (NULL == (pImageCredits = new djImage))
		return -1;

	creditsMenu.m_iSize = 0;
	creditsMenu.m_items = creditsMenuItems;
	creditsMenu.m_szCursor = creditsMenuCursor;
	creditsMenu.m_clrBack = djColor(0,0,0);
	creditsMenu.m_xOffset = 200;
	creditsMenu.m_yOffset = 128;

	pImageCredits->Load( FILE_IMG_CREDITS );
	return 0;
}

void ShowCredits()
{
	// First time?
	if (pImageCredits==NULL)
	{
		if (0!=credits_init())
			return;
	}

	// Display credits bitmap
	if (pImageCredits)
		djgDrawImage( pVisBack, pImageCredits, 0, 0, pImageCredits->Width(), pImageCredits->Height() );
	GraphFlip();
	
	// Pop up credits menu
	do_menu( &creditsMenu );
}
