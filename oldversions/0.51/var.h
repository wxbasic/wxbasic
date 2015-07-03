/*
    Name:       var.h
    Purpose:    wxBasic simple variables
    Author:     David Cuny
    Copyright:  (c) 2002 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*/


wSymbol *wReturnVar( char *name, int symType, int create );
wSymbol *wCreateConst( char *name );
void wCreateNumConst( char *name, int value );
void wCreateStrConst( char *name, char *value );
wSymbol *wCreateParm( char *name, int symType );
int wVarStackPos( wSymbol *s );
void wSetStack( int index );
void wSetVar( wSymbol *s );
void wSetReturn();
wNumber wFetchNumber( int index );
char *wFetchString( int index );
void wGetVar( wSymbol *s );
