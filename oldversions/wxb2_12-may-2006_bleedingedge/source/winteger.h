/*************************************************************
    Name:       winteger.h
    Purpose:    W_TYPE_INTEGER implementation
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/

#ifndef WXBASIC_WINTEGER_DECLARES
#define WXBASIC_WINTEGER_DECLARES


void wIntegerCopy( wVariant *dst, wVariant *src );
void wIntegerFromNumber( wVariant *dst, wNumber n );
wNumber wIntegerToNumber( wVariant *src );
int wIntegerFromChar( wVariant *dst, char *text );
char *wIntegerToChar( wVariant *src, int useQuotes, int limit );
int wIntegerEqual( wVariant *v1, wVariant *v2 );
int wIntegerCompare( wVariant *v1, wVariant *v2 );
void wIntegerRegisterMethods(void);

#endif
