/*************************************************************
    Name:       warray.h
    Purpose:    W_TYPE_ARRAY datatype: static arrays
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/

#ifndef WXBASIC_WARRAY_DECLARES
#define WXBASIC_WARRAY_DECLARES


/* static array */
struct wArray {
    int         refCount;           /* reference count */
    int         indexCount;         /* count of indexes */
    int         elementCount;       /* total number of elements */
    int         lower[4];           /* lower range of index */
    int         upper[4];           /* upper range of index */
    int         width[4];           /* offset per index */
    int         offset[4];          /* offset into index */
    wVariant    element[1];         /* variant static value array */
};

void wArrayRegisterMethods( void );
void wArrayRef( wVariant *src );
void wArrayDeref( wVariant *src );
void wArrayCopy( wVariant *dst, wVariant *src );
void wArrayClone( wVariant *dst, wVariant *src );
char *wArrayToChar( wVariant *src, int UseQuotes, int limit );
wArray *wArrayCreate( int indexCount, wVariant *variant );
void wArrayInit( wVariant *dst, wVariant *src );
void wArrayErase( wVariant *dst );
wVariant *wArrayFindIndex( wVariant *vSrc, int indexCount );
int wArrayCount( wVariant *vSrc );


#endif
