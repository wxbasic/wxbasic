/*************************************************************
    Name:       method.h
    Purpose:    methods for non-class objects
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/

void wMethod( wVariant *v, int stringIndex, int argCount, int returnCount );
int wMethodCheckArgs( char *method, int expect, int actual );
int wMethodList( wVariant *list, char *methodName, int argCount );
int wMethodTable( wVariant *table, char *methodName, int argCount );
int wMethodString( wVariant *string, char *name, int argCount );
