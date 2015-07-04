/*************************************************************
    Name:       console.h
    Purpose:    portable console routines
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/

#ifndef WXBASIC_CONSOLE_DECLARES
#define WXBASIC_CONSOLE_DECLARES

void wConsolePrint( char *buffer );
void wConsolePrintf( char *fmt, ... );
void wConsoleDebugf( char *fmt, ... );

#endif
