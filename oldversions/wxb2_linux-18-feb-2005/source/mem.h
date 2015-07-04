/*************************************************************
    Name:       mem.h
    Purpose:    memory handling routines
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/

/* chunks of memory allocated, for debugging */
struct wMemItem {
    void *memStart;
    void *memEnd;
    wMemItem *next;
    wMemItem *prior;
};


/* list of memory items being tracked */
wMemItem *wMemList = NULL;

/* last match of memory find */
wMemItem *wMemLastFind = NULL;


void wMemInit( void );
wMemItem *wMemFind( void *ptr );
void wMemIsGood( void *ptr, char *where );
void wMemAdd( void *ptr, int size );
void wMemDelete( wMemItem *link );
void wMemRemove( void *ptr );
void *wMalloc( int size );
void *wRealloc( void *ptr, int size );
void wFree( void *ptr );
void wMemMoveSafe( void *dst, void *src, int bytes, char *where );
