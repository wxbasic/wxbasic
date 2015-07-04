/*************************************************************
    Name:       list.h
    Purpose:    sequential lists for wxBasic
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/

#ifndef WXBASIC_LIST_DECLARES
#define WXBASIC_LIST_DECLARES


void wListNew( wVariant *dest, int size );
void wListInsert( wGrow *list, wVariant *src, int index );
wVariant *wListGetElement( wGrow *list, int indexCount );
void wListSlice( wVariant *dst, wVariant *src, int start, int end );
int wListIterate( wVariant *vArg1, wVariant *vArg2, wVariant *vList, wVariant *vIndex );
void wListDeref( wGrow *list );

#endif
