/*************************************************************
    Name:       char.h
    Purpose:    char buffer handling routines
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/

char *wCharCopy( char *text );
char *wCharMalloc( int length );
char *wCharConcat( char *dst, char *src );
char *wCharConcatInt( char *dst, int i );
char *wCharConcatPtr( char *dst, void *ptr );
void wCharToLower( char *text );
char *wCharCopyToLower( char *text );
