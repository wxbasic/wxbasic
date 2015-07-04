/*************************************************************
    Name:       literal.c
    Purpose:    Implements the literal table
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/

int wLiteralAdd( char *name, wVariant *variant );
int wLiteralAddNum( char *name, wNumber n );
int wLiteralAddStr( char *name, char *s );
char *wLiteralGetChar( int index );
int wLiteralAddPtr( char *name, wSymbol *klass, void *ptr );
void wLiteralInit( void );
