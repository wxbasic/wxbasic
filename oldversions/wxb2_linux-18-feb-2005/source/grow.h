/*************************************************************
    Name:       grow.h
    Purpose:    resizable pointer arrays
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/

/* a resizeable array */
struct wGrow {
    int count;		/* number of elements used */
    int free;           /* number of free slots remaining */
    int refCount;       /* used by tables */
    int isMarked;       /* prevents recursion on deletes */
    void *value;        /* start of data */
};

wGrow *wGrowNew( int chunks );
void wGrowFree( wGrow *src );
wGrow *wGrowCopy( wGrow *src );
int wGrowCount( wGrow *array );
int wGrowMakeRoom( wGrow *array );
int wGrowGet( wGrow *array, int index );
void wGrowSet( wGrow *array, int index, int value );
void wGrowInsert( wGrow *array, int index, int value );
void wGrowDelete( wGrow *array, int index );
int wGrowAppend( wGrow *array, int value );
int wGrowPeek( wGrow *array, int offset );
void wGrowIncr( wGrow *g, int n );
int wGrowPop( wGrow *array );
void wGrowDrop( wGrow *array, int n );
void wGrowConcat( wGrow *dst, wGrow *src );
void wGrowPrepend( wGrow *array, int value );
