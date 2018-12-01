/*
 * File:    sys_error.cc
 * Created: 2002-08-30 (Friday), 22:38
 * Modified: 2002-08-30 (Friday), 22:38
 * Author: Vytautas Shaltenis, a.k.a. rtfb
 *
 * Project: Dave Gnukem
 *
 * Description: Error, warning and debug output.
 *
 * NOTE: I use quite an intensive and dangerous perprocessor hackery here.
 * Kids, do not try this at home :)
 */

#include "sys_log.h"

#include "sys_defs.h"


static char	*file = NULL;
static int	line = 0;



void _SetFileAndLine ( const char *filename, const int linenum )
{
	file = (char*) filename;
	line = linenum;
}

#ifdef VISUALC6
// Visual C++ 6 versions of these functions just don't support __FILE__/__LINE__.
// See sys_error.h for explanation.

void SYS_Error( const char *fmt, ... )
{
	char		text[2048];
	va_list		args = NULL;
	if ( NULL == fmt )
		return;

	va_start ( args, fmt );
		vsprintf ( text, fmt, args );
	va_end ( args );

	Log ( "[Error]: %s", text );
	exit ( 0 );
}

void SYS_Warning( const char *fmt, ... )
{
	char		text[2048];
	va_list		args = NULL;
	if ( NULL == fmt )
		return;

	va_start ( args, fmt );
		vsprintf ( text, fmt, args );
	va_end ( args );

	Log ( "[Warning]: %s", text );
}

void SYS_Debug( const char *fmt, ... )
{
	char		text[2048];
	va_list		args = NULL;
	if ( NULL == fmt )
		return;

	va_start ( args, fmt );
		vsprintf ( text, fmt, args );
	va_end ( args );

	Log ( "[Debug]: %s", text );
}

#endif

void _SYS_Error ( char *fmt, ... )
{
	char		text[1024];
	char		text2[1024];
	char		*ptr, *ptr2;
	va_list		args = NULL;

	if ( NULL == fmt )
		return;

	va_start ( args, fmt );
		vsprintf ( text, fmt, args );
	va_end ( args );

	sprintf ( text2, "[Error] %s line %d: ", file, line );
	ptr2 = text2 + strlen ( text2 );

	ptr = text;
	while ( *ptr )
	{
		*ptr2++ = *ptr++;
	}
	*ptr2 = '\0';

	Log ( "%s", text2 );
	exit ( 0 );
}


void _SYS_Warning ( char *fmt, ... )
{
	char		text[1024];
	char		text2[1024];
	char		*ptr, *ptr2;
	va_list		args = NULL;

	if ( NULL == fmt )
		return;

	va_start ( args, fmt );
		vsprintf ( text, fmt, args );
	va_end ( args );

	sprintf ( text2, "[Warning] %s line %d: ", file, line );
	ptr2 = text2 + strlen ( text2 );

	ptr = text;
	while ( *ptr )
	{
		*ptr2++ = *ptr++;
	}
	*ptr2 = '\0';

	Log ( "%s", text2 );
}


void _SYS_Debug ( char *fmt, ... )
{
	char		text[1024];
	char		text2[1024];
	char		*ptr, *ptr2;
	va_list		args = NULL;

	if ( NULL == fmt )
		return;

	va_start ( args, fmt );
		vsprintf ( text, fmt, args );
	va_end ( args );

	sprintf ( text2, "[Debug] %s line %d: ", file, line );
	ptr2 = text2 + strlen ( text2 );

	ptr = text;
	while ( *ptr )
	{
		*ptr2++ = *ptr++;
	}
	*ptr2 = '\0';

	Log ( "%s", text2 );
}


/*
void _SYS_Error ( const char *file, const int line, char *fmt, ... )
{
	char		text[1024];
	char		text2[1024];
	char		*ptr, *ptr2;
	va_list		args = NULL;

	if ( NULL == fmt )
		return;

	va_start ( args, fmt );
		vsprintf ( text, fmt, args );
	va_end ( args );

	sprintf ( text2, "[Error] %s line %d: ", file, line );
	ptr2 = text2 + strlen ( text2 );

	ptr = text;
	while ( *ptr )
	{
		*ptr2++ = *ptr++;
	}
	*ptr2 = '\0';

	Log ( "%s", text2 );
	exit ( 0 );
}


void _SYS_Warning ( const char *file, const int line, char *fmt, ... )
{
	char		text[1024];
	char		text2[1024];
	char		*ptr, *ptr2;
	va_list		args = NULL;

	if ( NULL == fmt )
		return;

	va_start ( args, fmt );
		vsprintf ( text, fmt, args );
	va_end ( args );

	sprintf ( text2, "[Warning] %s line %d: ", file, line );
	ptr2 = text2 + strlen ( text2 );

	ptr = text;
	while ( *ptr )
	{
		*ptr2++ = *ptr++;
	}
	*ptr2 = '\0';

	Log ( "%s", text2 );
}


void _SYS_Debug ( const char *file, const int line, char *fmt, ... )
{
	char		text[1024];
	char		text2[1024];
	char		*ptr, *ptr2;
	va_list		args = NULL;

	if ( NULL == fmt )
		return;

	va_start ( args, fmt );
		vsprintf ( text, fmt, args );
	va_end ( args );

	sprintf ( text2, "[Debug] %s line %d: ", file, line );
	ptr2 = text2 + strlen ( text2 );

	ptr = text;
	while ( *ptr )
	{
		*ptr2++ = *ptr++;
	}
	*ptr2 = '\0';

	Log ( "%s", text2 );
}
*/

