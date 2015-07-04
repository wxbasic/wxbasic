/*************************************************************
    Name:       wroutine.h
    Purpose:    W_TYPE_ROUTINE datatype
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/


void wRoutineCopy( wVariant *dst, wVariant *src );
int wRoutineFromChar( wVariant *dst, char *text );
char *wRoutineToChar( wVariant *src, int useQuotes, int limit );
int wRoutineEqual( wVariant *v1, wVariant *v2 );
void wRoutineRegisterMethods( void );
