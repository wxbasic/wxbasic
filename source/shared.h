/*************************************************************
    Name:       shared.h
    Purpose:    assorted global values
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/

#ifndef WXBASIC_SHARED_DECLARES
#define WXBASIC_SHARED_DECLARES

#ifdef _WIN32
    #define DELIMITER '\\'
    #define DELIMITER_STRING "\\"
    #define PATH_DELIMITER ';'
#else
    #define DELIMITER '/'
    #define DELIMITER_STRING "/"
    #define PATH_DELIMITER ':'
#endif

#define wNumber float                   /* datatype of wNumber */
#define W_INBUFFER_MAX 1024             /* maximum size of line of code */
#define W_BUFFER_EMPTY -2               /* flag that buffer is empty */
#define W_VARIANT_MAX 32                /* maximum number of variants */
#define W_STATE_COUNT 10
#define W_STATE_MAX 100
#define W_TRUE -1
#define W_FALSE 0
#define W_MAX_CONSOLE_LINES 256   /* maximum number of lines shown in console */
#define W_EXTRA_CONSOLE_LINES 64  /* amount to remove at a time */

/* interface to wMemoryIsGood */
#ifdef __WDEBUG__
    #define wMemTest( a, b ); wMemIsGood( (void *)a, b );
    #define wMemMove( a, b, c, d ); wMemMoveSafe( a, b, c, d );
#else
    #define wMemTest( a, b );
    #define wMemMove( a, b, c, d ); memmove( a, b, c );

#endif

jmp_buf wTheParseJump;                  /* jmp address for parse errors */

/* Values set by MAIN.C */
char   *wTheCwd = NULL;                 /* current working directory */
int     wTheArgc = 0;                   /* argc */
char    *wTheArgv[32];                  /* argv */
char    *wTheFileName = NULL;           /* file being loaded */


wGrow   *wTheLiterals = NULL;           /* constants table */
int     wTheGlobalFlag = 0;             /* if true, global keyword used */
wGrow   *wTheStack = NULL;              /* data stack for interpreter */
wGrow   *wTheSymbols = NULL;            /* symbol table */
int     wTheCurrentScope = 0;           /* current scope index */
int     wTheGlobalScope = 0;            /* global scope index */
int     wTheClassScope = 0;             /* index to class being defined */
wGrow   *wTheCallStack = NULL;          /* call stack */
wCall   *wTheCall = NULL;               /* the current call */
wCall   *wTheGlobal = NULL;             /* the global call */
int     wTheNextLabel = 0;              /* next label id */
wGrow   *wTheLocal = NULL;              /* the local variable stack */
int     wTheHaltFlag = W_FALSE;         /* halts the application */
int     wTheListFlag = 0;               /* list bytecodes instead of running them */
int     wTheRedirectConsoleFlag = 0;    /* redirect console output to file */
wGrow   *wTheCatchStack = NULL;         /* list of catch addresses */
int     wTheException = 0;              /* exception error */
char    *wTheExceptionText = NULL;      /* text of the exception */
int     wTheStackTmpCount = 0;          /* count of temp items on stack */

/* OPTION xxx */
int     wTheOptionExplicit = W_FALSE;   /* option explicit defaults to false */
int     wTheOptionStrict = W_FALSE;     /* option strict defaults to false */
int     wTheOptionBackslash = W_TRUE;   /* option backslash defaults to true */
int     wTheNoConsoleFlag = W_FALSE;    /* suppress console output? */

/* FILE I/O */
char    *wTheFileBuffer = NULL;         /* buffer for file i/o */
FILE    *wTheOutputFile = NULL;         /* file to write to */
FILE    *wTheLogFile = NULL;            /* pointer to log file */

wVariant *wTheLval = NULL;              /* the left hand value */
int     wTheReturnFlag = W_FALSE;       /* return from routine */
wVariantHandler *wTheHandler[W_VARIANT_MAX];  /* handle variant methods */
int     wTheLastBuiltinTypeIndex = 0;   /* index of last builtin type */
int     wTheClassIndexToDataType[32];    /* convert class index to datatype */
wGrow   *wTheSubroutineStack = NULL;    /* stack of subroutine calls */
wVariant *wTheIndexedString = NULL;     /* holds addresses of sliced strings */
int     wTheWxWindowClassIndex = 0;     /* index of wxWindow class */
int     wTheMaxCallDepth = 1024;        /* maximum nesting of calls */

/* TRACING AND DEBUGGING */
int     wTheTraceOpFlag = W_TRUE;         /* generate trace opcodes? */
int     wTheDebugOnFlag = W_FALSE;         /* print debug information? */
int     wTheTraceOnFlag = W_FALSE;         /* in trace mode? */
int     wTheTraceWaitFlag = W_FALSE;       /* wait in debugger */
int     wTheTraceGotoNextBreak = W_FALSE;  /* overrides trace wait flag */
int     wTheTraceDownFlag = W_FALSE;       /* step into calls */
int     wTheTraceUpFlag = W_FALSE;         /* trace on exit */

/* DISPLAYING THE OPCODES */
int     wTheOpCode;                         /* the current opcode */
int     wTheOpPC;                           /* program counter */
int     wTheOpArgCount;                     /* number of args for opcode */
int     wTheOpArg1;                         /* the args (numeric) */
int     wTheOpArg2;
int     wTheOpArg3;
char    *wTheOpComment = NULL;              /* comment about the opcode */

#endif
