/*--------------------------------------------------------------------------*/
/* David Joffe '99/02 */
/* Level sets, campaigns, missions, whatever you want to call 'em */

/*
mission.cpp

Copyright (C) 1999-2002 David Joffe

License: GNU GPL Version 2 (*not* "later versions")
*/
/*--------------------------------------------------------------------------*/
#include "datadir.h"
#include "mission.h"
#include "djlog.h"
#include "djstring.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

vector<CMission * > g_apMissions;
// FIXME: Does this stuff really belong here? Probably not.
CMission * g_pCurMission = NULL;
/*--------------------------------------------------------------------------*/
int LoadMissions( const char * szfilename )
{
	if (szfilename==NULL) return -1; // NULL string
	if (szfilename[0]==0) return -2; // empty string
	FILE * fin;
	char buf[1024];

	// open file
	// FIXME: We need a consistent way to handle "DATA_DIR"
	if ( NULL == ( fin = fopen( szfilename, "r" ) ) )
	{
		djMSG("ERROR: LoadMissions(%s): Unable to open file.\n", szfilename);
		return -3;
	}

	// Read the list of available mission filenames from the "mission registry"
	fgets( buf, sizeof(buf), fin );
	djStripCRLF(buf); // strip CR/LF characters
	while (!feof( fin ))
	{
		CMission * pMission;
		if ( strlen(buf) > 1 )
		{
			pMission = new CMission;

			// Load this mission and add to list (FIXME: ERROR CHECK)
			pMission->Load( buf );
			g_apMissions.push_back(pMission);
		}
		
		fgets( buf, sizeof(buf), fin );
		djStripCRLF(buf); // strip CR/LF characters
	}

	fclose( fin );

	if (g_apMissions.size()<1)
	{
		djMSG("ERROR: LoadMissions(%s): No valid missions loaded from file.\n", szfilename);
		return -1;
	}

	// Set current mission by default to the first one in the list
	g_pCurMission = g_apMissions[0];
	return 0;
}
/*--------------------------------------------------------------------------*/
CMission::CMission()
{
	for ( int i=0; i<256; i++ )
	{
		m_apSpriteData[ i ] = NULL;
	}
	m_szName = NULL;
}

int CMission::Load( char * szfilename )
{
	if (szfilename==NULL) return -1; // NULL string
	if (szfilename[0]==0) return -2; // empty string

	FILE * fin;
	char   buf[1024];
	int    state;
	char   filename[1024];

	TRACE( "CMission::Load( %s ): Loading ...\n", szfilename );

	sprintf( filename, "%s%s", DATA_DIR, szfilename );
	// open file
	if ( NULL == ( fin = fopen( filename, "r" ) ) )
	{
		djMSG( "CMission::Load( %s ) Unable to open file.\n", szfilename );
		return -3;
	}

	state = 0;
	fgets( buf, sizeof(buf), fin );
	djStripCRLF(buf); // strip CR/LF characters
	while (!feof( fin ))
	{
		switch (state)
		{
			///////////////////////////////////////////////////////////////
		case 0: // name
			SetName( buf );
			TRACE( "CMission::Load(): Name: %s\n", GetName() );
			state = 1;
			TRACE( "CMission::Load(): Description:\n", buf );
			break;
			///////////////////////////////////////////////////////////////
		case 1: // description
			if ( 0 == strcmp( buf, "~" ) )
			{
				state = 2;
				TRACE( "-------------\n" );
			}
			else
			{
				// add this part of string to description
				TRACE( "%s\n", buf );
			}
			break;
			///////////////////////////////////////////////////////////////
		case 2: // level filenames, names, authors
			if ( 0 == strcmp( buf, "~" ) )
			{
				state = 3;
			}
			else
			{
				CLevel * pLevel;
				pLevel = new CLevel();
				if ( NULL == pLevel )
				{
					djMSG( "CMission::Load(): Failed to allocate CLevel.\n" );
				}
				char *szFilename, *szName, *szAuthor, *szBackground;
				// Interpret line of level information

				szFilename   = djStrPart( buf, 1, "," );
				szBackground = djStrPart( buf, 2, "," );
				szName       = djStrPart( buf, 3, "," );
				szAuthor     = djStrPart( buf, 4, "," );

				TRACE( "CMission::Load(): Level: [%s][%s][%s]\n", szFilename, szName, szAuthor );

				pLevel->SetFilename(szFilename);
				pLevel->m_szName		= djStrDeepCopy(szName);
				pLevel->m_szBackground	= djStrDeepCopy(szBackground);
				pLevel->m_szAuthor		= djStrDeepCopy(szAuthor);
				AddLevel( pLevel );

				DELV(szFilename);
				DELV(szName);
				DELV(szAuthor);
				DELV(szBackground);
			}
			break;
			///////////////////////////////////////////////////////////////
		case 3: // sprites
			if ( 0 == strcmp( buf, "~" ) )
			{
				state = 4;
			}
			else
			{
				char * szID, * szDatafile, *szImgFilename;
				CSpriteData * pSpriteData;

				pSpriteData = new CSpriteData();

				szID          = djStrPart( buf, 1, "," );
				szImgFilename = djStrPart( buf, 2, "," );
				szDatafile    = djStrPart( buf, 3, "," );

				TRACE( "CMission::Load(): Sprites: [%s][%s][%s]\n",
					szID, szImgFilename, szDatafile );
				// Should this happen? NO! LATER! Then must remember names!
				//	       pSprites->LoadSpriteImage(
				pSpriteData->m_iID            = atoi( szID );
				pSpriteData->m_szImgFilename  = djStrDeepCopy( szImgFilename );
				pSpriteData->m_szFilenameData = djStrDeepCopy( szDatafile );
				AddSpriteData( pSpriteData->m_iID, pSpriteData );

				DELV( szID );
				DELV( szImgFilename );
				DELV( szDatafile );
			}
			break;
		}

		fgets( buf, sizeof(buf), fin );
		djStripCRLF(buf); // strip CR/LF characters
	} // while (!feof( fin ))

	if (state != 4)
	{
		djMSG( "CMission::Load( %s ): Bad end state %d\n", szfilename, state );
	}

	fclose( fin );

	return 0;
}

void CMission::AddLevel( CLevel * pLevel )
{
	m_apLevels.push_back( pLevel );
}

CLevel * CMission::GetLevel( int i )
{
	return m_apLevels[i];
}

int CMission::NumLevels()
{
	return m_apLevels.size();
}

void CMission::AddSpriteData( int iID, CSpriteData * pSprites )
{
	TRACE( "CMission::AddSpriteData( %d )\n", iID );
	if ( m_apSpriteData[ iID ] != NULL )
	{
		delete m_apSpriteData[ iID ];
	}
	m_apSpriteData[ iID ] = pSprites;
}

CSpriteData * CMission::GetSpriteData( int iID )
{
	// FIXME: Error check here
	return m_apSpriteData[ iID ];
}

int CMission::LoadSprites()
{
	int i;

	// i iterates through the 256 possible ID's for spritesets
	for ( i=0; i<256; i++ )
	{
		CSpriteData * pSpriteData;

		pSpriteData = g_pCurMission->GetSpriteData( i );
		if ( pSpriteData != NULL )
		{
			// FIXME: WHERE IS OUR ERROR CHECKING!?!?!?
			// Load spriteset (the sprite image)
			pSpriteData->LoadSpriteImage();

			// Load data (flags etc associated with sprites)
			pSpriteData->LoadData( pSpriteData->m_szFilenameData );

		} // if
	} // i

	return 0;
}

int CMission::SaveSprites()
{
	int i;
	int nRet = 0;

	// i iterates through the 256 possible ID's for spritesets
	for ( i=0; i<256; i++ )
	{
		CSpriteData * pSpriteData;

		pSpriteData = g_pCurMission->GetSpriteData( i );
		if ( pSpriteData != NULL ) // It *can* be NULL
		{
			char szFilename[1024];
			// Save sprite data file
#ifdef DATA_DIR
			sprintf( szFilename, "%s%s", DATA_DIR, pSpriteData->m_szFilenameData );
#else
			sprintf( szFilename, "%s", pSpriteData->m_szFilenameData );
#endif
			if (nRet>=0)
				nRet = pSpriteData->SaveData( szFilename );

		} // if
	}

	return nRet;
}

/*--------------------------------------------------------------------------*/
CLevel::CLevel()
{
	m_szFilename = NULL;
	m_szName = NULL;
	m_szAuthor = NULL;
	m_szBackground = NULL;
}

void CLevel::SetFilename( char * szFilename )
{
	DELV(m_szFilename);

	m_szFilename = djStrDeepCopy( szFilename );
}

char * CLevel::GetFilename()
{
	return m_szFilename;
}
/*--------------------------------------------------------------------------*/
CSpriteData::CSpriteData()
{
	m_iID = -1;
	m_szFilenameData = NULL;
	m_pImage = NULL;
	m_szImgFilename = NULL;
	// fixme; not everything inti
}

int CSpriteData::LoadData( char * szFilename )
{
	FILE * fin;
	char   buf[1024];
	int    i, j;

	TRACE( "CSpriteData::LoadData( %s ): Loading ...\n", szFilename );

	// open the file
	if (NULL == (fin = fopen( szFilename, "r" )))
	{
#ifdef DATA_DIR
		char buf[1024];
		sprintf( buf, "%s%s", DATA_DIR, szFilename );
		if (NULL == (fin = fopen( buf, "r" )))
#endif
		{
			djMSG( "CSpriteData::LoadData( %s ): Error opening file\n", szFilename );
			return -1;
		}
	}

	// Read "128"
	fgets( buf, sizeof(buf), fin );
	if (feof(fin))
		goto error;

	for ( i=0; i<128; i++ )
	{
		// Read type
		fgets( buf, sizeof(buf), fin );
		if (feof(fin))
			goto error;
		djStripCRLF(buf); // strip CR/LF characters

		m_type[i] = atoi( buf );

		// Read extras
		fgets( buf, sizeof(buf), fin );
		if (feof(fin))
			goto error;
		djStripCRLF(buf); // strip CR/LF characters

		for ( j=0; j<12; j++ )
		{
			char * temp;
			temp = djStrPart( buf, j+1, "," );
			if (NULL == temp)
			{
				djMSG( "CSpriteData::LoadData( %s ): Error reading extras\n", szFilename );
				goto error;
			}
			else
			{
				m_extras[i][j] = atoi( temp );
				//FIXME:WHY?				delete[] temp;
			}
		}

		// FIXME: FOLLOWING OLD COLOR OBSOLETE
		// Read block color
		fgets( buf, sizeof(buf), fin );
		if (feof(fin))
			goto error;
		djStripCRLF(buf); // strip CR/LF characters

		m_color[i] = atoi( buf );


		// Calculate color from sprite by averaging the 16x16 array of pixels
		if (m_pImage)
		{
			int iIndexX = (i%16)*16; // x offset into image
			int iIndexY = (i/16)*16; // y offset into image
			int r=0,g=0,b=0;
			for ( j=0; j<16; j++ )
			{
				for ( int k=0; k<16; k++ )
				{
					djColor clr = m_pImage->GetPixelColor(k+iIndexX, j+iIndexY);
					r += (int)clr.r;
					g += (int)clr.g;
					b += (int)clr.b;
				}
			}
			r /= 256;
			g /= 256;
			b /= 256;
			m_Color[i] = djColor((unsigned char)r,(unsigned char)g,(unsigned char)b);
		}


	}

	fclose( fin );
	return 0;

error:

	djMSG( "CSpriteData::LoadData( %s ): Error reading data.\n", szFilename );

	fclose( fin );
	return -2;
}

int CSpriteData::SaveData( char * szFilename )
{
	FILE * fout;
	int    i, j;

	TRACE( "CSpriteData::SaveData( %s ): Saving ...\n", szFilename );

	if (NULL == (fout = fopen( szFilename, "w" )))
	{
		djMSG( "CSpriteData::SaveData( %s ): unable to open file.\n", szFilename );
		return -1;
	}

	// Print the number of images in the file. Not used yet, but maybe in
	// the future.
	fprintf( fout, "%d\n", 128 );
	for ( i=0; i<128; i++ )
	{
		// output block type
		fprintf( fout, "%d\n", m_type[i] );

		// output "extras" values
		for ( j=0; j<12; j++ )
		{
			if ( j<11 )
				fprintf( fout, "%d,", m_extras[i][j] );
			else
				fprintf( fout, "%d\n", m_extras[i][j] );
		} // j

		// output block color (for level editor)
		fprintf( fout, "%d\n", m_color[i] );
	} // i

	fclose( fout );

	return 0;
}

int CSpriteData::LoadSpriteImage()
{
	TRACE( "CSpriteData::LoadSpriteImage( %s ): Loading ...\n", m_szImgFilename );

	// If image already exists, delete it
	DEL(m_pImage);

	int iRet = 0;

	// Attempt to load image file
	m_pImage = new djImage;
	if (m_pImage==NULL)
	{
	}
	else
	{
		char buf[1024];
#ifdef DATA_DIR
		sprintf( buf, "%s%s", DATA_DIR, m_szImgFilename );
#else
		sprintf( buf, "%s", m_szImgFilename );
#endif
		iRet = m_pImage->Load( buf );
	}

	return iRet;
}
/*--------------------------------------------------------------------------*/
