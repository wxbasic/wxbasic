/*************************************************************
    Name:       wobject.h
    Purpose:    W_TYPE_OBJECT datatype - instances of class objects
    Author:     David Cuny
    Copyright:  (c); 2002 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/

#ifndef WXBASIC_WOBJECT_DECLARES
#define WXBASIC_WOBJECT_DECLARES


/* user-defined instance of a class */
struct wObject {
    int refCount;       /* reference count */
    int tmpFlag;        /* if true, uses refCount */
    wSymbol *klass;     /* object class */
    void *ptr;          /* pointer to external object */
    int propCount;      /* count of properties */
    wVariant prop[1];   /* array of properties */
};

void wObjectRegisterMethods( void );
wObject *wObjectNew( int klass, int tmpFlag );
void wObjectRef( wVariant *src );
int wObjectInheritsWxWindow( wSymbol *klass );
void wObjectDeref( wVariant *src );
void wObjectFree( wObject *o );
void wObjectCopy( wVariant *dst, wVariant *src );
void wObjectClone( wVariant *dst, wVariant *src );
char *wObjectToChar( wVariant *src, int useQuotes, int limit );
int wObjectEqual( wVariant *v1, wVariant *v2 );

#endif
