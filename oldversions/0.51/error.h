/*
    Name:       error.h
    Purpose:    error support routines
    Author:     David Cuny
                Partially derived from Brian Kernighan and Rob Pike
                The Practice of Programming
*/


typedef struct wMemLink wMemLink;


struct wMemLink {
    int     start;     /* start of allocated block */
    int     end;       /* end of allocated block */
    wMemLink *next;    /* in list */
};

wMemLink *wLastMemLink = NULL;

enum {
    W_INIT,       /* initialization error */
    W_SYNTAX,     /* syntax error */
    W_RUNTIME     /* runtime error */
};

void wShutdown( int errorlevel );
void wPrintf( int errType, char *fmt, ... );
void wConsole( char *fmt, ... );
void wAddMemLinkDebug( void *p, int n );
void wRemoveMemLinkDebug( void *address );
wMemLink *wLookupMemLink( void *p );
void wMemTestDebug( char *message, void *address );
void wFreeAllDebug( void );
char *wCopyString(char *s);
void wExpected( char *expect );
void *wMalloc(size_t size);
void *wRealloc( void *old, size_t size);
void wFreeDebug( void *address );
