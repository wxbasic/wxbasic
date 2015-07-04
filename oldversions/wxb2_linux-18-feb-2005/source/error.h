/*************************************************************
    Name:       error.h
    Purpose:    error handling routines
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/

/* a catch */
struct wCatch {
    int         stackCount;     /* height of data stack before try */
    int         callCount;      /* height of call stack before try */
    int         gosubCount;     /* height of return stack before try */
    int         jumpTo;         /* opcode to jump to on error */
    jmp_buf     jumpBuffer;     /* state data before jump */
};


/* the exceptions */
enum {
    W_ERROR_CONVERT,            /* can't convert datatype */
    W_ERROR_INDEX,              /* index outside of range */
    W_ERROR_INTERNAL,           /* internal error */
    W_ERROR_ARGS,               /* argument count mismatch */
    W_ERROR_NOTCODE,            /* parameter can't be executed */
    W_ERROR_SYNTAX,             /* syntax error */
    W_ERROR_NOSUCH,             /* no such routine, arg, etc. */
    W_ERROR_FILE,               /* bad file, mode, etc. */
    W_ERROR_MEMORY,             /* out of memory */
    W_ERROR_MATH,               /* division by zero, etc. */
    W_ERROR_LVAL                /* can't perform operation with lval */

};


char *wExceptionText[] = {
    "Conversion error",
    "Bad index error",
    "Internal error",
    "Argument count mismatch error",
    "Parameter can't be executed error",
    "Syntax error",
    "No such thing error",
    "File error",
    "Out of memory error"
    "Math error",
    "Can't do operation on lval"
};

void wErrorThrow( int theException, char *fmt, ... );
char *wErrorConcatLine( char *buffer );
void wErrorMessage( char *title, char *buffer );
void wErrorMessagef( char *title, char *fmt, ... );
static void wErrorSIGILL( int s );
static void wErrorSIGSEGV( int s );
static void wErrorSIGFPE( int s );
