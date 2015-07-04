/*
    Name:       error.c
    Purpose:    error support routines
    Author:     David Cuny
                Partially derived from Brian Kernighan and Rob Pike
                The Practice of Programming
*/


/* which version to use? */
#ifdef __DEBUG_MEMORY__
    #define wAddMemLink(a,n)        wAddMemLinkDebug(a,n)
    #define wRemoveMemLink(a)       wRemoveMemLinkDebug(a)
    #define wMemTest(s,a)           wMemTestDebug(s,a)
    #define wFree(a)                wFreeDebug(a)
#else
    #define wAddMemLink(a,n)
    #define wRemoveMemLink(a)
    #define wMemTest(s,a)
    #define wFree(a)                free(a)
#endif


/* close the application gracefully */
void wShutdown( int errorlevel )
{
    /* close files opened by user */
    wFileCloseAll();

    /* handle warnings? */
    if (!wFatalFlag && !wWarningsFlag) {
        wGenerateWarnings();
    }

    exit(errorlevel);
}

/* print an error message and exit */
void wFatal( int errType, char *fmt, ... )
{
    char        buffer[512], message[512];
    va_list     args;
    FILE        *errFile;
    wSourceCode  *source = NULL;

    /* close files opened by user */
    wFileCloseAll();

    /* set fatal flag */
    wFatalFlag = 1;

#ifndef __WXWIN__
    fflush(stdout);
    fprintf(stderr, "\n" );
#endif

    switch (errType) {
    case W_INIT:
        sprintf( message, "Initialization error\n" );
        break;

    case W_SYNTAX:
        source = wFindSource( wParseLineId );
        if (source == NULL) {
            sprintf( message, "Syntax error, source code lookup corrupted\n" );
        } else {
            sprintf( message, "Syntax error on line number %d of %s\n", source->lineNum, wIncludeList[source->fileNum] );
        }
        break;

    case W_RUNTIME:
        source = wFindSource( wRunLineId );
        if (source == NULL) {
            sprintf( message, "Runtime error, source code lookup corrupted\n" );
        } else {
            sprintf( message, "Runtime error on line number %d of %s\n", source->lineNum, wIncludeList[source->fileNum] );
        }
        break;

    default:
        sprintf( message, "Unknown error type\n" );

    }

    va_start(args, fmt);
    vsprintf( buffer, fmt, args );
    va_end(args);
    strcat( message, buffer );

    if (fmt[0] != '\0' && fmt[strlen(fmt)-1] == ':') {
        sprintf( message, "\n%s", strerror(errno));
        strcat( buffer, message );
    }
    strcat( buffer, "\n");

    /* show the line */
    if (errType != W_INIT) {
        if (source == NULL) {
            strcat( message, "\n<<Can't Find Source Line>>" );

        } else {
            sprintf( buffer, "\n%s", source->text);
            strcat( message, buffer );
        }
    }

#ifdef __WXWIN__
    wxMessageBox( message, W_PROGNAME, wxOK, (wxWindow *)NULL );
#else
    fprintf( stderr, message );
#endif

    /* open the error file */
    errFile = fopen( "wx.err", "w" );
    if (errFile != NULL) {
        fprintf( errFile, message );
        fclose( errFile );
    }

    wShutdown(2); /* conventional for failed execution */
}

/* cross-platform version of printf */
void wConsole( char *fmt, ... )
{
    char    buffer[512];
    int     i, linesOnConsole, removeTo;
    va_list args;

    va_start(args, fmt);
    vsprintf( buffer, fmt, args );
    va_end(args);

#ifdef __WXWIN__
    if (wConsoleFlag) {
        if (!wConsoleExists) {
            wConsoleClass *wConsole = new wConsoleClass();
        }
        /* add text */
        wConsoleText->AppendText( buffer );
        linesOnConsole = wConsoleText->GetNumberOfLines();

        /* need to delete lines? */
        if (linesOnConsole > W_MAX_CONSOLE_LINES) {
            /* count number of characters to delete */
            removeTo = 0;
            for ( i = 1; i <= W_EXTRA_CONSOLE_LINES; i++ ) {
                removeTo += wConsoleText->GetLineLength(i) + 1;
            }

            /* remove the text */
            wConsoleText->SetEditable(1);
            wConsoleText->Remove( 0, removeTo );
            wConsoleText->SetEditable(0);
        }
        /* move to end of console */
        wConsoleText->SetInsertionPointEnd();
    }
#else
    fprintf( stdout, buffer );
#endif
}




/* add memory chunk to tracking list */
void wAddMemLinkDebug( void *p, int n )
{
    wMemLink     *link;

    /* malloc the link */
    link = (wMemLink *)malloc(sizeof(wMemLink));
    if (link == NULL) {
        wFatal( W_RUNTIME, "wMalloc: malloc of wMemLink failed:" );
    }

    /* set values */
    link->start = (int)p;
    link->end = link->start+(n-1);
    link->next = wLastMemLink;
    wLastMemLink = link;

}

/* remove memory chunk from tracking list */
void wRemoveMemLinkDebug( void *address )
{
    wMemLink    *link;
    wMemLink    *prev;

    if (address == NULL) {
        return;
    }

    prev = NULL;
    for ( link = wLastMemLink; link != NULL; link = link->next ) {
        if (link->start == (int)address) {

            if (prev == NULL) {
                wLastMemLink = link->next;
            } else {
                prev->next = link->next;
            }
            return;
        }
        prev = link;
    }
    wFatal( W_RUNTIME, "wRemoveMemLink: memory address %p not in list", address );
}

/* sequential search through wMemLink list */
wMemLink *wLookupMemLink( void *p )
{
    wMemLink *link = wLastMemLink;

    for ( ; link != NULL; link = link->next ) {
        if ((int)p >= link->start && (int)p <= link->end) {
            return link;
        }
    }
    return NULL; /* no match */
}

/* ensure that the memory was allocated */
void wMemTestDebug( char *message, void *address )
{
    if (address != NULL) {
        if (wLookupMemLink(address) == NULL) {
            wFatal( W_RUNTIME, "wMemTest: %s: address %p not allocated",
                message, address );
        }
    }
}

/* free all the elements in list */
void wFreeAllDebug()
{
    wMemLink *link = wLastMemLink;
    wMemLink *next;

    for ( ; link != NULL; link = next) {
        next = link->next;
        free( (void*)(link->start) );     /* the chunk */
        free( link );                   /* the link */
    }
}

/* copy a string, report if error */
char *wCopyString(char *s)
{
    char    *t;

    t = (char *)wMalloc(strlen(s)+1);
    strcpy(t, s);
    return t;
}

/* handle unexpected token - print error and die */
void wExpected( char *expect )
{
    wFatal( W_SYNTAX, "Parse error: expected %s, but got %s", expect, wCurrToken );
}

/* malloc and report if error */
void *wMalloc(size_t size)
{
    void        *p;

    /* malloc the chunk */
    p = (void *)malloc(size);
    if (p == NULL) {
        wFatal( W_RUNTIME, "wMalloc: malloc of %u bytes failed:", size );
    }
    wAddMemLink( p, size );
    return p;

}

/* realloc and report if error */
void *wRealloc( void *theOld, size_t size)
{
    void        *theNew;

    /* realloc the chunk */
    theNew = (void *)realloc(theOld,size);
    if (theNew == (void *)NULL) {
        wFatal( W_RUNTIME, "eRealloc: realloc of %u bytes failed:", size );
    }

#ifdef __DEBUG_MEMORY__
    if (theNew != theOld) {
        wRemoveMemLink(theOld);
        wAddMemLink(theNew,size);
    }
#endif

    return theNew;

}

/* free chunk of memory */
void wFreeDebug( void *address )
{
    if (address != NULL) {
        wRemoveMemLink( address );
        free( address );
    }
}

