// David Joffe, 1999/12 GNU etc.
/*
instructions.cpp

Copyright (C) 1999-2001 David Joffe

License: GNU GPL Version 2 (*not* "later versions")
*/
#include "djtypes.h"
#include "instructions.h"
#include "menu.h"
#include "graph.h"

djImage *pImgInstructions=NULL;

struct SMenuItem instructionsMenuItems[] =
{
   { false, "{~~~~~~}" },
   { true,  "|  OK  |" },
   { false, "[~~~~~~]" },
   { false, NULL }     
};
unsigned char instructionsMenuCursor[] = { 128, 129, 130, 131, 0 };
CMenu instructionsMenu;

void ShowInstructions()
{
	instructionsMenu.m_iSize = 0;
	instructionsMenu.m_items = instructionsMenuItems;
	instructionsMenu.m_szCursor = instructionsMenuCursor;
	instructionsMenu.m_clrBack = djColor(0,173,173);
	instructionsMenu.m_xOffset = 220;
	instructionsMenu.m_yOffset = 128;
	if (pImgInstructions==NULL)
	{
		if (NULL != (pImgInstructions = new djImage))
			pImgInstructions->Load( FILE_IMG_INSTRUCTIONS );
	}
	if (pImgInstructions)
	{
		djgDrawImage( pVisBack, pImgInstructions, 0, 0, pImgInstructions->Width(), pImgInstructions->Height() );
		GraphFlip();
		
		// Pop up credits menu
		do_menu( &instructionsMenu );
	}
}

