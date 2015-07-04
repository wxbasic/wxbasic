/*************************************************************
    Name:       stack.h
    Purpose:    datastack for wxBasic
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/

void wStackNew( int size );
wVariant *wStackPushNothing( void );
void wStackPushNumber( wNumber n );
void wStackPushNumberFromRoutine( wNumber n, char *routine );
void wStackPushChar( char *s, int isRaw );
void wStackPushDateTime( time_t t );
void wStackPush( wVariant *src );
wVariant *wStackItem( int index );
wVariant *wStackPeek( int index );
wNumber wStackPopNumber( void );
wVariant *wStackPopString( void );
char *wStackPopChar( void );
time_t wStackPopDateTime( void );
wVariant *wStackPopLval( void );
wVariant *wStackPop( void );
void wStackDrop( int n );
void wStackDropExtra( int n );
void wStackSwap( int i1, int i2 );
void *wStackPopObjectPtr( wSymbol *memberOfKlass );

