/*
    Name:       shared.h
    Purpose:    Forward declarations for wxBasic
    Author:     David Cuny
    Copyright:  (c) 2002 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*/

typedef long double wNumber;    /* internal value numbers are stored as */
#define W_NUMBER_FLOAT_FORMAT   "%Lf"
#define W_NUMBER_INT_FORMAT     "%.0Lf"
#define W_ALLOWABLE_ERROR       DBL_EPSILON

typedef struct wStack wStack;     /* integer stack, for misc. tasks       */
typedef union wValue wValue;      /* union of types data stack can hold   */
typedef struct wVariant wVariant; /* type + value                         */
typedef struct wArrayCell wArrayCell; /* cell of associative array        */
typedef struct wArray wArray;     /* array                                */
typedef struct wSymbol wSymbol;   /* token descriptor                     */
typedef struct wNode wNode;       /* parse tree node                      */
typedef struct wType wType;       /* core datatypes                       */

#define W_MAX_INDEXES 4           /* number of indexes allowed            */
#define W_MAX_OPT_ARGS 8          /* max number of optional args          */
#define W_INCLUDE_MAX 32          /* maximum number of include files */
#define W_INCLUDE_MAX_DEPTH 16    /* maximum nesting of include files */
#define W_MAX_CONSOLE_LINES 256   /* maximum number of lines shown in console */
#define W_EXTRA_CONSOLE_LINES 64  /* amount to remove at a time */
#define W_TRUE  1
#define W_FALSE 0

int     wIgnoreCase = 1;            /* if true, ignore case */
int     wArgc;                      /* argc from command line */
char    *wArgv[32];                 /* argv from command line */
FILE    *wInFile;                   /* handle to file being parsed */
char    *wCwd = NULL;               /* current working directory */
char    wCurrToken[256];            /* current token */
int     wFatalFlag = 0;             /* true if fatal shutdown */
int     wErrFlag = 0;               /* set by yyerror */
int     wWarningsFlag = 0;          /* if false, suppress warnings */
int     wConsoleFlag = 1;           /* if false, supress console */
int     wExplicitFlag = 0;          /* Option Explicit */
int     wCommonFlag = 0;            /* common declaration */
int     wQBasicFlag = 0;            /* Option QBasic */
int     wFileNum = 0;               /* current file number */
int     wLineNum = 0;               /* current line number of current file */
int     wParseLineId = 0;           /* id of line being parsed */
int     wRunLineId = 0;             /* id of line being run */
int     wIncludeCount = 0;          /* number of source files read */
char    *wIncludeList[W_INCLUDE_MAX];      /* names of files included */
int     wVisibleWindow = 0;         /* true if any window is visible */
int     wArgCount = 0;              /* count of args being passed on stack */
wSymbol *wCurrentScope;             /* routine being defined */
wSymbol *wCurrentTypeDef;           /* type being defined */
wSymbol *wCurrentType;              /* type being referenced */
int     wMe;                        /* pointer to object for current method */
int     wAppIndex = 0;              /* handle to wxApp */


wStack *wArgCountStack;             /* arg count in parser */
wStack *wBlockStack;                /* block type */
wStack *wLineStack;                 /* line number */
wStack *wSharedStack;               /* shared symbols */
wNode *wDeferredCode = NULL;        /* deferred code */
