/*************************************************************
    Name:       wnumber.h
    Purpose:    W_TYPE_NUMBER datatype
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/

#ifndef WXBASIC_NUMBER_DECLARES
#define WXBASIC_NUMBER_DECLARES


void wNumberRegisterMethods( void );
void wNumberCopy( wVariant *dst, wVariant *src );
void wNumberFromNumber( wVariant *dst, wNumber n );
wNumber wNumberToNumber( wVariant *src );
int wNumberFromChar( wVariant *dst, char *text );
char *wNumberToChar( wVariant *src, int useQuotes, int limit );
int wNumberEqual( wVariant *v1, wVariant *v2 );
int wNumberCompare( wVariant *v1, wVariant *v2 );
int wNumberCompareNumbers( wNumber n1, wNumber n2 );

#endif
