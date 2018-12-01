/*!
\file    menu.h
\brief   Main menu
\author  David Joffe

Copyright (C) 1995-2001 David Joffe

License: GNU GPL Version 2 (*not* "later versions")
*/
/*--------------------------------------------------------------------------*/
/* menu.h
 */
/* David Joffe '95/07/20 */
/*--------------------------------------------------------------------------*/
#ifndef _MENU_H_
#define _MENU_H_
/*--------------------------------------------------------------------------*/
#include "djtypes.h"
#include "djsound.h"
/*--------------------------------------------------------------------------*/
//! A single item in the menu
struct SMenuItem
{
	//! A real menu item (true), or just a string (false)?
	bool m_bitem;
	//! The menu text to display
	char *m_szText;
};
/*--------------------------------------------------------------------------*/
/*!
\class CMenu
\nosubgrouping

A menu (e.g. the main menu). Consists of an array of menu items (\ref SMenuItem).
A menu item with \ref SMenuItem::m_szText value NULL indicates the end of the
array.
*/
class CMenu
{
public:
	CMenu()
	{
		m_items = NULL;
		m_szCursor = NULL;
		m_xOffset = -1;
		m_yOffset = -1;
		m_iSize = -1;
		m_clrBack = djColor(0,0,0);
		m_iSoundMove = SOUNDHANDLE_INVALID;
	}
	SMenuItem *     m_items;    // (m_szText==NULL)-terminated
	unsigned char * m_szCursor;
	int             m_xOffset;
	int             m_yOffset;
	int             m_iSize;
	djColor         m_clrBack; // background color (the above ones are obsolete)
	SOUND_HANDLE    m_iSoundMove; // Sound to play when cursor moved
};

//! Pop up a menu and wait for the user to select something from the menu.
extern int do_menu( CMenu *pMenu );

#endif

