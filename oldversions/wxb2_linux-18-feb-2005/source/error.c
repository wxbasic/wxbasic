/*************************************************************
    Name:       error.c
    Purpose:    error handling routines
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/

void wErrorThrow( int theException, char *fmt, ... )
{
    int         activeHandler;
    char        *buffer, *message;
    va_list     args;
    wCatch      *aCatch;
    FILE        *errFile;

    /* set flag true if there is an active Catch */
    activeHandler = (wTheCatchStack != NULL && wTheCatchStack->count > 0);

    /* set the exception number */
    wTheException = theException;

    /* allocate space for the message */
    message = wCharMalloc( W_INBUFFER_MAX );

    /* format args */
    va_start(args, fmt);
    vsprintf( message, fmt, args );
    va_end(args);

    /* add a newline to the end */
    message = wCharConcat( message, "\n" );

    /* copy the message to the buffer */
    buffer = wCharCopy( message );

    /* was it in a call? */
    if (wTheCall != NULL) {
        /* display only line, no trace or locals */
        buffer = wCallConcatTrace( buffer, W_FALSE, W_FALSE );
    } else {
        /* interpreting error */
        buffer = wErrorConcatLine( buffer );
    }

    /* clear prior error message */
    if (wTheExceptionText != NULL) {
        wFree( wTheExceptionText );
    }
    
    /* copy the buffer text to wTheExeceptionText */
    wTheExceptionText = wCharCopy( buffer );

    /* free the buffers */
    wFree( buffer );

    /* if there is an active error handler, use it */
    if (activeHandler) {
        /* free the error message buffer */
        wFree( message );

        /* get the jump buffer */
        aCatch = (wCatch *)wGrowPeek( wTheCatchStack, 0 );

        /* goto jump address */
        longjmp(aCatch->jumpBuffer, 1 );

    }

    /* display the error */
    wErrorMessage( wExceptionText[theException], wTheExceptionText );

    /* append it to the error file */
    errFile = fopen( "wx.err", "wb" );

    /* failed to create error file? */
    if (!errFile) {
        /* display error */
        wErrorMessagef( "File Error", "Unable to create error log file" );
    } else {
        /* error type */
        fprintf( errFile, "%s: ", wExceptionText[theException]  );

        /* syntax error? */
        if (wTheCall == NULL) {
            /* echo the exception */
            fputs( wTheExceptionText, errFile );
            fclose( errFile );

        /* runtime error */
        } else {
            /* echo the error message to the file */
            fputs( message, errFile );

            /* create a full trace */
            buffer = wCharMalloc( W_INBUFFER_MAX );
            buffer = wCallConcatTrace( buffer, W_TRUE, W_TRUE );
            fputs( buffer, errFile );
            wFree( buffer );
        }
        fclose( errFile );
    }

    /* free the error message buffer */
    wFree( message );

    /* goto parse error jump address */
    longjmp(wTheParseJump, 1);

}



/* concat parsed line with the error to the buffer */
char *wErrorConcatLine( char *buffer )
{
    int     i, errLine, errPos;
    wSource *source;

    /* where the error occured */
    errLine = wReadLine;

    /* make sure source has been loaded, and the error line is in range */
    if (errLine && errLine > wSourceFile->count) {
        /* backup to last line in file */
        errLine = wSourceFile->count;
    }

    /* text to display? */
    if (errLine > 0) {
        /* get the line from the file */
        source = wSourceGet( errLine );

        /* build the description */
        buffer = wCharConcat( buffer, "in file \"" );
        buffer = wCharConcat( buffer, source->fileName );
        buffer = wCharConcat( buffer, "\", line " );
        buffer = wCharConcatInt( buffer, source->lineNum );
        buffer = wCharConcat( buffer, ":\n" );

        /* add source code */
        buffer = wCharConcat( buffer, source->text );

        /* point to the errant position, if known */
        if (wLineBufferPos > 0) {
            errPos = wLineBufferPos;
        } else {
            errPos = strlen( source->text );
        }

        /* point to error */
        for ( i = 0; i < errPos; i++ ) {
            buffer = wCharConcat( buffer, " " );
        }
        buffer = wCharConcat( buffer, "^\n" );
    }

    return buffer;
}


/* print an error message */
void wErrorMessage( char *title, char *buffer )
{
#ifdef __WXWIN__
    wxMessageBox( buffer, title, wxOK | wxICON_ERROR, (wxWindow *)NULL );
#else
    fprintf( stderr, "[%s]\n", title );
    fprintf( stderr, buffer );
    fprintf( stderr, "\n" );
    fflush(stdout);
#endif
}



/* print a formatted error message */
void wErrorMessagef( char *title, char *fmt, ... )
{
    char       *buffer;
    va_list     args;

    /* allocate the buffer */
    buffer = wCharMalloc( W_INBUFFER_MAX );

    va_start(args, fmt);
    vsprintf( buffer, fmt, args );
    va_end(args);

    wErrorMessage( title, buffer );

    /* free the buffer */
    wFree( buffer );

}


static void wErrorSIGILL( int s ) {
    /* set the trap again */
    signal( SIGILL, wErrorSIGILL );

    /* handle the error */
    wErrorThrow( W_ERROR_INTERNAL, "Illegal instruction (SIGILL)");
}

static void wErrorSIGSEGV( int s ) {
    /* set the trap again */
    signal( SIGSEGV, wErrorSIGSEGV );

    /* throw an error */
    wErrorThrow( W_ERROR_INTERNAL, "Memory error (SIGSEGV)");
}

static void wErrorSIGFPE( int s ) {
    /* set the trap again */
    signal( SIGFPE, wErrorSIGFPE );

    wErrorThrow( W_ERROR_INTERNAL, "Math error (SIGFPE)");
}
