/*************************************************************
    Name:       main.c
    Purpose:    main routine for wxBasic
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/

// FIXME:
// should the flags be suppressed if there is a tag?

// #define __WDEBUG__
// #define __SQLITE__

#define W_PROGNAME    "wxBasic"
#define W_RELEASE     "alpha 2.5 (Handles, Anyone?)"
#define W_DATEOF      "May 12, 2006"
#define W_COPYRIGHT   "(c) 2006 David Cuny"
#define W_LICENSE     "Lesser GNU Public License"

/* standard libraries */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <float.h>
#include <time.h>
#include <errno.h>
#include <limits.h>
#include <signal.h>
#include <setjmp.h>

#ifdef _WIN32
    #include <dir.h>
#else
    #include <unistd.h>
#endif

/* sqlite database support */
#ifdef __SQLITE__
    #include "sqlite.h"
#endif

/* support library headers */
#include "typedef.h"
#include "shared.h"
#include "mem.h"
#include "char.h"
#include "error.h"
#include "console.h"
#include "grow.h"
#include "wstring.h"    /* need to declare, used in wVariant */
#include "variant.h"
#include "wnothing.h"
#include "winteger.h"
#include "wnumber.h"
#include "wobject.h"
#include "wroutine.h"
#include "warray.h"
#include "wtable.h"
#include "wlist.h"
#include "wdatetime.h"
#include "wvarptr.h"
#include "stack.h"
#include "symbol.h"
#include "source.h"
#include "trace.h"
#include "vm.h"
#include "literal.h"
#include "code.h"
#include "eval.h"
#include "token.h"
#include "lex.h"
#include "keyword.h"
#include "parse.h"
#include "call.h"
#include "file.h"
#include "builtin.h"
#include "wrap.h"
#include "main.h"

/* wxWindows specific */
#ifdef __WXWIN__
#include "connect.hpp"
#include "events.h"
#endif


/* include libraries */
#include "mem.c"
#include "char.c"
#include "error.c"
#include "console.c"
#include "grow.c"
#include "variant.c"
#include "wnothing.c"
#include "winteger.c"
#include "wnumber.c"
#include "wstring.c"
#include "wobject.c"
#include "wroutine.c"
#include "warray.c"
#include "wtable.c"
#include "wlist.c"
#include "wdatetime.c"
#include "wvarptr.c"
#include "stack.c"
#include "symbol.c"
#include "code.c"
#include "literal.c"
#include "source.c"
#include "trace.c"
#include "vm.c"
// #include "token.c"
#include "lex.c"
#include "keyword.c"
#include "parse.c"
#include "call.c"
#include "file.c"
#include "builtin.c"
#include "wrap.c"


/* wxWindows specific */
#ifdef __WXWIN__
    #include "wrap.cpp"         /* wxWindows wrappers   */
    #include "events.c"         /* classify events      */
    #include "connect.cpp"      /* callback code        */
#endif

/* print help message and exit */
void wMainPrintHelp()
{
    char *buffer;

    buffer = wCharMalloc( W_INBUFFER_MAX );

    /* build the message */
    buffer = wCharConcat( buffer, "wxbasic [options] filename. Available options are:\n" );
    buffer = wCharConcat( buffer,"  -d   -debug    Print debug information\n");
    buffer = wCharConcat( buffer,"  -t   -trace    Display trace lines\n");
    buffer = wCharConcat( buffer,"  -h   -help     Print this help message\n" );
    buffer = wCharConcat( buffer,"  -l   -list     Print bytecodes\n");
    buffer = wCharConcat( buffer,"  -n   -notrace  Don't add trace bytecodes\n");
    buffer = wCharConcat( buffer,"  -v   -version  Print version information\n");

    wErrorMessage( "Usage", buffer );
    wFree( buffer );

}



/* parse directives, return index where directives stop */
int wMainParseDirectives( int argc, char *argv[] )
{
    int i, flag;
    char *arg;
        
    /* copy command line args */
    for ( i = 1; i < argc; i++ ) {

        /* get an arg */
        arg = argv[i];

        /* strip the leading '-' if it's a directive */
        flag = W_FALSE;
        while (arg[0] == '-') {
            arg++;
            flag = W_TRUE;
        }

        if (flag) {

            /* debug */
            if (strcmp( arg, "d") == 0
            ||  strcmp( arg, "debug") == 0) {
                wTheDebugOnFlag = W_TRUE;

            /* trace */
            } else if (strcmp( arg, "t" ) == 0
              ||       strcmp( arg, "trace") == 0) {
                wTheTraceOnFlag = W_TRUE;
                wTheTraceDownFlag = W_TRUE;

            /* help */
            } else if (strcmp( arg, "h" ) == 0
              ||       strcmp( arg, "help") == 0) {
                wMainPrintHelp();
                exit(1);

            /* list */
            } else if (strcmp( arg, "l" ) == 0
            ||         strcmp( arg, "list") == 0) {
                wTheListFlag = W_TRUE;
#ifdef __WXWIN__
                    wTheRedirectConsoleFlag = W_TRUE;
#endif

            /* no trace */
            } else if (strcmp( arg, "n" ) == 0
            ||         strcmp( arg, "notrace") == 0) {
                wTheTraceOnFlag = W_FALSE;
                wTheTraceOpFlag = W_FALSE;

            /* version */
            } else if (strcmp( arg, "v" ) == 0
            ||         strcmp( arg, "ver") == 0
            ||         strcmp( arg, "version") == 0) {
                wConsoleDebugf( "wxBasic %s %s", W_RELEASE, W_DATEOF );
                exit(1);


            } else {
                wConsoleDebugf("Unknown directive -%s\n", arg );
                exit(0);

            }

        /* end of directives */
        } else {
            return i;
        }
    }

    return 1;
    
}


/* return path from filename */
char *wMainGetPath( char *fileName )
{
    int i;
    char *path, delim;

    /* assume failure */
    path = NULL;

    /* search for the last occurance of the delimiter */
    for ( i = strlen(fileName); i > 0; i-- ) {
        if (fileName[i] == DELIMITER) {
            /* copy to path */
            path = wCharCopy( fileName );

            /* ignore text following the delimiter */
            path[i+1] = '\0';

            /* leave the loop */
            break;
        }
    }

    return path;
}


/* open the main file, use PATH if needed */
FILE *wMainOpen(char *fileName)
{
    char *path;
    int posInPath;
    char *fullFileName;
    int posInFileName;
    char letter;
    FILE *file;

    /* try opening using given name */
    file = fopen( fileName, "r" );
    if (file) {
        /* return the file, full path was given */
        return file;
    }

    /* if there is a delimiter, don't bother looking in the path */
    if (strchr(fileName, DELIMITER)) {
        return NULL;
    }

    /* get the path from the environment variable */
    path = getenv("PATH");
    if (path == NULL) {
        return NULL;
    }

    /* allocate space for the fully qualified name */
    fullFileName = wCharMalloc( W_INBUFFER_MAX );

    /* read the names out of the path */
    posInFileName = 0;
    for ( posInPath = 0; path[posInPath] != '\0'; posInPath++ ) {
        /* get the character from the path */
        letter = path[posInPath];

        /* seperator? */
        if (letter == PATH_DELIMITER || letter == '\0') {
            /* accumulated path? */
            if (posInPath > 0) {
                /* append filename */
                fullFileName[posInFileName++] = DELIMITER;
                fullFileName[posInFileName++] = '\0';
                strcat( fullFileName, fileName );

                /* try to open the file */
                file = fopen( fullFileName, "r" );
                if (file) {
                    /* free the buffer */
                    wFree( fullFileName );

                    /* return the pointer */
                    return file;

                } else {
                    /* didn't open, start building buffer again */
                    posInFileName = 0;
                }
            }

        } else {
            /* accumulate */
            fullFileName[posInFileName++] = letter;
        }
	}

    /* release buffer */
    wFree( fullFileName );

    return NULL;
}



/* return offset into file if bound, or zero */
int wMainGetOffset( char *fileName )
{
    FILE    *file;
    char    tag[32];
    int     i, j, tagOffset;

    /* open the file */
    file = wMainOpen(fileName);
    if (file == NULL) {
        wErrorThrow( W_ERROR_FILE, "Can't open file %s", fileName);
    }

    /* look to see if it ends with a bind tag */
    fseek( file, -18, 2 );
    fgets( tag, 18, file );
    fclose( file );

    /* examine the tag */
    if (strcmp( " wxbind", tag+10 ) == 0) {
        /* parse the number */
        sscanf( tag+2, "%d", &tagOffset );
        if (tagOffset == 0) {
            wErrorThrow( W_ERROR_FILE, "Tag in %s is corrupt", fileName );
        }

        /* return the offset */
        return tagOffset;

    } else {
        /* no offset */
        return 0;
    }

}

/* get command line args, return offset if main file is tagged */
void wMainCopyArgs( int argc, char *argv[], int argStart, int tagOffset )
{
    int     i, j, fileIndex;
    char    *path;

    /* copy command line args */
    wTheArgv[0] = argv[0];
    for ( i = argStart, j = 1; i < argc; i++, j++ ) {
        wTheArgv[j] = wCharCopy( argv[i] );
    }
    wTheArgc = j;

    /* bound file? */
    if (tagOffset != 0) {

        /* shift args over by 1 */
        wTheArgc++;
        for ( i = wTheArgc; i > 0; i-- ) {
            wTheArgv[i] = wTheArgv[i-1];
        }

        /* first arg is cwd + "wxbasic" */
        wTheArgv[0] = wCharCopy( wTheCwd );
        wTheArgv[0] = wCharConcat( wTheArgv[0], "wxbasic" );

        /* the second arg is the first arg *without* the cwd */
        wTheArgv[1] = wCharCopy( wTheArgv[1] + strlen( wTheCwd ) );

        /* but use the arg 0 as the file to open */
        wTheFileName = wCharCopy( argv[0] );

    } else {
        /* get the path from the arg */
        path = wMainGetPath( argv[argStart] );
        if (path != NULL) {
            /* get the filename, without the path */
            wTheFileName = wCharCopy( argv[argStart] + strlen( path ) );

            /* free the path */
            wFree( path );
        } else {
            /* get the filename; no path */
            wTheFileName = wCharCopy( argv[argStart] );
        }
    }

}


int wMainInterpret( int argc, char *argv[] )
{
    int i, scope, argStart, tagOffset;
    char *fileName, *path;
    wCode *code;
    wSymbol *s, *child;
    wSource *source;

    /* initialize memory tracking */
    wMemInit();

    /* set jump address for parser */
    if (setjmp(wTheParseJump)) {
        /* return 0 for failure */
        return 0;
    }

    /* find out if the file is bound */
    tagOffset = wMainGetOffset( argv[0] );

    /* no args and not bound? */
    if (argc == 1 && tagOffset == 0) {
        wMainPrintHelp();
        return 1;
    }

    /* handle the command line directives */
    argStart = wMainParseDirectives( argc, argv );

    /* set the current working directory */

    /* check to see if name has path */
    wTheCwd = NULL;

    /* if not bound, try to get the path from the source file */
    if (tagOffset ==  0) {
        wTheCwd = wMainGetPath( argv[argStart] );
    }

    /* none specified in source file? */
    if (!wTheCwd) {
        /* use the current working directory */
        wTheCwd = getcwd( NULL, W_INBUFFER_MAX );
        wMemAdd( wTheCwd, strlen(wTheCwd ) );
        wTheCwd = wCharConcat( wTheCwd, DELIMITER_STRING );
    }

    #ifdef __WXWIN__
        /* make it the current working directory */
        wxSetWorkingDirectory( wTheCwd );
    #endif

    /* copy command line args for command() routine */
// wErrorMessage( "Debug:", "copy the args" );
    wMainCopyArgs( argc, argv, argStart, tagOffset );

// wErrorMessage( "Debug:", "initialize modules" );
    /* initialize modules */
    wStackNew( 1024 );
    wSymbolInit();
    wVariantInit();
    wKeywordInit();
    wSourceInit();
    wLexInit();
    wParseInit();
    wCallInit();
    wBuiltinInit();
    wLiteralInit();
    wVmInit();

#ifdef __WXWIN__
    /* load the wrappers */
    wInitWrappers();
#endif

    /* load a file */
    if (wTheDebugOnFlag) {
        wConsoleDebugf("--- LOADING THE SOURCE ---\n" );
    }

// wErrorMessage( "Debug:", "load source" );
    wSourceLoad( wTheFileName, tagOffset );

    /* scan for routine names */
    if (wTheDebugOnFlag) {
        wConsoleDebugf("--- SCANNING THE SOURCE ---\n" );
    }

// wErrorMessage( "Debug:", "scan for routines" );
    wSourceScanForRoutines();

    /* parse the file */
    if (wTheDebugOnFlag) {
        wConsoleDebugf("--- PARSING THE SOURCE ---\n" );
    }

// wErrorMessage( "Debug:", "parse file" );

    code = wParseFile();

    /* end statement */
    wCodeEmit( code, W_OP_END );

    /* assign it to the current scope */
    wSymbolLookup( wTheCurrentScope )->pcode = wGrowCopy( code->pcode );
    wCodeFree( code );

    /* show bytecodes, or run? */
    if (wTheListFlag) {

// wErrorMessage( "Debug:", "dump the bytecodes" );

        /* dump the bytecodes */
        if (wTheDebugOnFlag) {
            wConsoleDebugf("--- DUMPING THE BYTECODES ---\n" );
        }

        /* set the file to output to */
        wTheOutputFile = fopen( "listing", "wb" );

        /* decompile */
        wVmDecompileAll();

        /* close the output file */
        fclose( wTheOutputFile );
        wTheOutputFile = NULL;

#ifdef __WXWIN__
        wxMessageBox(wxT("Created output file \"wx.log\""));
#endif

    } else {
        /* set error traps */
        signal( SIGILL, wErrorSIGILL );
        signal( SIGSEGV, wErrorSIGSEGV );
        signal( SIGFPE, wErrorSIGFPE );

        /* run the code */
        if (wTheDebugOnFlag) {
            wConsoleDebugf("--- RUNNING THE CODE ---\n" );
        }

// wErrorMessage( "Debug:", "run the code" );
        /* FIXME: need to set call parms first */
        wCallRoutine( wSymbolLookup( wTheCurrentScope ), 0, 0, NULL, NULL );
    }


// wErrorMessage( "Debug:", "exit" );
    return 1;
}


#ifndef __WXWIN__

int main(int argc, char **argv)
{
// wErrorMessage( "Debug:", "calling wMainInterpret" );
    return wMainInterpret(argc, argv);
}
#endif
