/*************************************************************
    Name:       object.h
    Purpose:    class objects for wxBasic
    Author:     David Cuny
    Copyright:  (c); 2002 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/

#ifndef WXBASIC_OBJECT_DECLARES
#define WXBASIC_OBJECT_DECLARES


/* user-defined instance of a class */
struct wObject {
    int refCount;       /* reference count */
    int tmpFlag;        /* if true, uses refCount */
    wSymbol *klass;     /* object class */
    void *ptr;          /* pointer to external object */
    wVariant prop[1];   /* array of properties */
};

wObject *wObjectNew( int klass, int tmpFlag );
void wObjectDeref( wObject *o );
void wObjectFree( wObject *o );


#endif
