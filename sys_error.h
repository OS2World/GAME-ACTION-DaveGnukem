/*
 * File:    sys_error.h
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

#ifndef __SYS_ERROR_H_RTFB__
#define __SYS_ERROR_H_RTFB__


// DJ: Visual C++ 6 (I don't know about .NET) does not seem to allow variable
// argument lists as parameters of function macros. Since having __FILE__, __LINE__
// is nice but not critical, we just make it unavailable on a VC build
#ifdef VISUALC6

void SYS_Error( const char *fmt, ... );
void SYS_Warning( const char *fmt, ... );
void SYS_Debug( const char *fmt, ... );

#else

#define SYS_Error(rest,...) {_SetFileAndLine ( __FILE__, __LINE__ );\
	_SYS_Error(## rest);}
#define SYS_Warning(args) {_SetFileAndLine ( __FILE__, __LINE__ );\
	_SYS_Warning(## args);}

#if !defined(DAVE_RELEASE)
#define SYS_Debug(rest...) {_SetFileAndLine ( __FILE__, __LINE__ );\
	_SYS_Debug(## rest);}
#else
#define SYS_Debug
//#define SYS_Debug(rest...)
#endif

#endif // #ifdef VISUALC6

void _SetFileAndLine ( const char *filename, const int linenum );
void _SYS_Error ( char *fmt, ... );
void _SYS_Warning ( char *fmt, ... );
void _SYS_Debug ( char *fmt, ... );


#endif			// #ifndef __SYS_ERROR_H_RTFB__

