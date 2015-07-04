/*************************************************************
    Name:       wrap.h
    Purpose:    routines to create wrappers for external classes
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/

/* create a symbol describing the new class */
wSymbol *wWrapClass( int flags, wSymbol *inherits, char *className );
void wWrapDerefArgs( void );
void wWrapMethod( int flags, wSymbol *klass, char *methodName, void (*routine)(void), int reqCount, int optCount );
void wWrapSetThis( wSymbol *klass, void *data );
void wWrapPushObject( wSymbol *klass, int tmpFlag, void *data );

