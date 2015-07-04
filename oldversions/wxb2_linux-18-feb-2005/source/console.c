/*************************************************************
    Name:       console.c
    Purpose:    portable console routines
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/


/* print buffer */
void wConsolePrint( char *buffer )
{
    /* redirect to log file? */
    if (wTheRedirectConsoleFlag) {

        /* need to open log file? */
        if (wTheLogFile == NULL) {
            wTheLogFile = fopen( "wx.log", "w" );
            if (wTheLogFile == NULL) {
                wErrorThrow( W_ERROR_FILE, "Can't create log file" );
            }
        }

        /* write to the log file */
        fputs( buffer, wTheLogFile );
        fflush( wTheLogFile );

        return;
    }

#ifdef __WXWIN__
    int linesOnConsole, removeTo, i;

    if (!wTheNoConsoleFlag) {
        if (!wConsoleExists) {
            wConsoleClass *wConsole = new wConsoleClass();
        }

        /* add text to buffer */
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
    printf( buffer );
#endif
}

/* cross-platform version of printf */
void wConsolePrintf( char *fmt, ... )
{
    char    buffer[W_INBUFFER_MAX];
    va_list args;

    /* find number of args */
    va_start(args, fmt);
    vsprintf( buffer, fmt, args );
    va_end(args);

    /* print the buffer */
    wConsolePrint( buffer );
}


/* write to log file */
void wConsoleDebugf( char *fmt, ... )
{
    char    buffer[W_INBUFFER_MAX];
    int     priorFlag;
    va_list args;

    /* find number of args */
    va_start(args, fmt);
    vsprintf( buffer, fmt, args );
    va_end(args);

    /* redirect console */
    priorFlag = wTheRedirectConsoleFlag;
    wTheRedirectConsoleFlag = W_TRUE;
    

    /* print the buffer */
    wConsolePrint( buffer );

    /* restore */
    wTheRedirectConsoleFlag = priorFlag;

}


