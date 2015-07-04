/*************************************************************
    Name:       call.h
    Purpose:    support for calling user defined routines
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/

/* a call */
struct wCall {
    int         parmCount;      /* number of parameters passed to routine */
    int         returnCount;    /* number of items being returned */
    wSymbol     *routine;       /* routine being executed */
    int         sourceLine;     /* id of code being run */
    wObject     *self;          /* pointer to object, if class call */
    wVariant    *vSelf;         /* pointer to variant, if builtin datatype */
    int         localCount;     /* count of local variables */
    wVariant    local[1];       /* local variables */
};

void wCallInit( void );
void wCallRoutine( wSymbol *sRoutine, int parmCount, int returnCount, wObject *o, wVariant *v );
void wCallRestoreStack( int depth );
char *wCallConcatTrace( char *buffer, int unroll, int showLocals );

