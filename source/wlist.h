/*************************************************************
    Name:       wlist.h
    Purpose:    sequential lists for wxBasic
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/

#ifndef WXBASIC_WLIST_DECLARES
#define WXBASIC_WLIST_DECLARES


void wListRegisterMethods( void );
void wListNew( wVariant *dst, int size );
void wListRef( wVariant *src );
void wListDeref( wVariant *src );
void wListCopy( wVariant *dst, wVariant *src );
void wListClone( wVariant *dst, wVariant *src );
char *wListToChar( wVariant *vSrc, int useQuotes, int limit );
void wListInsert( wVariant *src, wVariant *key, wVariant *value );
void wListAppend( wVariant *src, wVariant *value );
void wListPrepend( wVariant *src, wVariant *value );
wVariant *wListIndex( wVariant *src, int indexCount );
void wListSlice( wVariant *dst, wVariant *src, int start, int end );
int wListIterate( wVariant *vList, wVariant *vIndex, wVariant *vArg1, wVariant *vArg2 );
int wListCount( wVariant *vSrc );

#endif
