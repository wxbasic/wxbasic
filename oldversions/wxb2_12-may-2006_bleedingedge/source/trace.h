/*************************************************************
    Name:       trace.h
    Purpose:    debugging routines
    Author:     David Cuny
    Copyright:  (c) 2005 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/

#ifndef WXBASIC_TRACE_DECLARES
#define WXBASIC_TRACE_DECLARES

void wTraceOpToConsole( void );
void wTrace( int lineNumber );
void wTraceDebug( void );
void wTraceRun( void );
void wTraceStop( void );
void wTraceStepInto( void );
void wTraceStepOver( void );
void wTraceStepOut( void );

#endif
