/*************************************************************
    Name:       wnothing.h
    Purpose:    implement W_TYPE_NOTHING methods
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/

#ifndef WXBASIC_WNOTHING_DECLARES
#define WXBASIC_WNOTHING_DECLARES


void wNothingCopy( wVariant *dst, wVariant *src );
char *wNothingToChar( wVariant *src, int useQuotes, int limit );
int wNothingFromChar( wVariant *dst, char *buffer );
int wNothingEqual( wVariant *v1, wVariant *v2 );
int wNothingIsTrue( wVariant *src );
void wNothingRegisterMethods( void );
int wNothingIterate( wVariant *vNothing, wVariant *vIndex, wVariant *vArg1, wVariant *vArg2  );

#endif
