/*************************************************************
    Name:       wvarptr.h
    Purpose:    W_TYPE_VARPTR datatype
	Author:     David Cuny
	Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
	Licence:    LGPL
*************************************************************/

#ifndef WXBASIC_WVARPTR_DECLARES
#define WXBASIC_WVARPTR_DECLARES


void wVarPtrRef( wVariant *src );
void wVarPtrDeref( wVariant *src );
void wVarPtrCopyData( wVariant *dst, wVariant *src );
char *wVarPtrToChar( wVariant *src, int useQuotes, int limit );
void wVarPtrRegisterMethods( void );

#endif
