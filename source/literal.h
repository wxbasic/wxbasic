/*************************************************************
    Name:       literal.c
    Purpose:    Implements the literal table
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/

#ifndef WXBASIC_LITERAL_DECLARES
#define WXBASIC_LITERAL_DECLARES

int wLiteralAdd( char *name, wVariant *variant );
int wLiteralAddNum( char *name, wNumber n );
int wLiteralAddStr( char *name, char *s );
char *wLiteralGetChar( int index );
int wLiteralAddPtr( char *name, wSymbol *klass, void *ptr );
void wLiteralInit( void );
void wLiteralDumpTable( void );

#endif
