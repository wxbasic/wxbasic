/*
    Name:       core.c
    Purpose:    Core (wxWindows-less) version of wxBasic
    Author:     David Cuny
    Copyright:  (c) 2002 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*/

/*
#define __DEBUG_MEMORY__
#define __DEBUG_TRACE__
*/


#define __WXBASIC__
#define __W_IGNORE_CASE__
#define W_PROGNAME    "wxBasic"
#define W_RELEASE     "alpha 0.51 (Waltzing Interia)"
#define W_DATEOF      "January 31, 2002"
#define W_COPYRIGHT   "(c) 2002 David Cuny"
#define W_LICENSE     "Lesser GNU Public License"

#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <malloc.h>
#include <limits.h>
#include <float.h>

extern int yylex();
extern void yyerror( char* );

#include "shared.h"         /* shared routines                      */
#include "trace.h"          /* tracing code                         */
#include "error.h"          /* error messages and 'safe' routines   */
#include "stack.h"          /* integer stack                        */
#include "data.h"           /* data types                           */
#include "symbol.h"         /* symbol table                         */
#include "var.h"            /* variables                            */
#include "array.h"          /* array structures                     */
#include "node.h"           /* parse tree data structure            */
#include "file.h"           /* file support                         */
#include "builtin.h"        /* builtin routines                     */
#include "const.h"          /* builtin constants                    */
#include "eval.h"           /* parse tree evaluator                 */
#include "keyword.h"        /* keywords (defined in grammar file)   */
#include "lexer.h"          /* lexer                                */
#include "class.h"          /* class wrappers                       */
#ifdef __WXWIN__
#include "connect.hpp"      /* callback code                        */
#include "events.h"         /* classify events                      */
#endif


#include "trace.c"          /* tracing code                         */
#include "error.c"          /* error messages and 'safe' routines   */
#include "stack.c"          /* integer stack                        */
#include "data.c"           /* data types                           */
#include "symbol.c"         /* symbol table                         */
#include "var.c"            /* variables                            */
#include "array.c"          /* array structures                     */
#include "node.c"           /* parse tree data structure            */
#include "file.c"           /* file support                         */
#include "builtin.c"        /* builtin routines                     */

#ifdef __WXWIN__
#include "wrap.cpp"         /* interface to wxwindows               */
#include "connect.cpp"      /* callback code                        */
#include "events.c"         /* classify events                      */
#endif

#include "const.c"          /* builtin constants                    */

#include "eval.c"           /* parse tree evaluator                 */
#include "y_tab.c"          /* bison parser                         */
#include "keyword.c"        /* keywords (defined in grammar file)   */
#include "lexer.c"          /* lexer                                */
#include "class.c"          /* class wrappers                       */

/* set current working directory based on command line */
void wSetCwd( char *text )
{
    /* probably not portable to the Mac... */

    int     at, i;
    char    delim;

    /* copy the string */
    wCwd = wCopyString( text );

    /* what delimiter to use? */
    if (strchr(wCwd, '\\') != NULL) {
        delim = '\\';

    } else if (strchr(wCwd, '/') != NULL) {
        delim = '/';

    } else {
        wCwd[0] = '\0';
        return;
    }

    /* search */
    at = 0;
    for ( i = 0; wCwd[i] != '\0'; i++ ) {
        if (wCwd[i] == delim) {
            at = i;
        }
    }
    wCwd[at+1] = '\0';

#ifdef __WXWIN__
    /* make it the current working directory */
    wxSetWorkingDirectory( wCwd );
#endif
    
}


int wInterpret( int argc, char **argv )
{
    FILE    *file;
    char    tag[32];
    int     i;
    long    offset;

#ifndef __WXWIN__
    wConsole( "%s %s - %s\n", W_PROGNAME, W_RELEASE, W_DATEOF );
    wConsole( "%s\n", W_COPYRIGHT );
    wConsole( "Released under the %s\n", W_LICENSE );
#endif

    /* initialize */
    wArgCountStack  = wNewStack(32);    /* count of parameters */
    wBlockStack     = wNewStack(32);    /* control block stack */
    wLineStack      = wNewStack(32);    /* current line number */
    wSharedStack    = wNewStack(128);   /* list of shared variables */
    wCurrentScope   = NULL;             /* routine being defined */
    wCurrentType    = NULL;             /* no type being defined */
    wInitKeywords();                    /* builtin keywords */
    wInitBuiltins();                    /* builtin functions */
    wInitConsts();                      /* builtin constants */
#ifdef __WXWIN__
    wInitWrappers();                    /* wxWindows wrappers */
    wObjectIndex = _wxObject;           /* index of wxObject */
#endif

    /* copy command line args */
    wArgc = argc;
    for ( i = 0; i < argc; i++ ) {
        wArgv[i] = wCopyString( argv[i] );
    }

    /* set current working directory (NON-PORTABLE!) */
    wSetCwd( argv[0] );

    /* get the size of this file */
    file = fopen( argv[0], "r" );
    if (file == NULL) {
        wFatal( W_INIT, "Can't open file %s", argv[0]);
    }

    /* get tag */
    fseek( file, -18, 2 );
    fgets( tag, 18, file );
    fclose( file );

    /* examine the tag */
    if (strcmp( " wxbind", tag+10 ) == 0) {
        /* parse the number */
        sscanf( tag+2, "%d", &offset );
        if (offset == 0) {
            wFatal( W_INIT, "Tag in %s is corrupt", argv[0] );
        }

        /* shift args over by 1 */
        wArgc++;
        for ( i = wArgc; i > 0; i-- ) {
            wArgv[i] = wArgv[i-1];
        }

        /* first arg is wxBasic */
        wArgv[0] = wCopyString( "wxbasic" );

        /* load the bound file */
        wPushIncludeFile( argv[0], offset );

    } else {
        /* require file name */
        if (argc == 1) {
            wFatal( W_INIT, "Expected a file name");
        }

        /* load the file */
        wPushIncludeFile( argv[1], 0 );

    }

    /* parse the file */
    yyparse();

    /* deferred? */
    if (wDeferredCode != NULL) {
        wEval( wDeferredCode );
        wFreeNode( wDeferredCode );
    }
    return 0;
}

#ifndef __WXWIN__

int main(int argc, char **argv)
{
    return wInterpret(argc, argv);
}
#endif
