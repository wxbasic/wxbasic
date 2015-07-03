/*
    Name:       file.c
    Purpose:    file support for wxBasic
    Author:     David Cuny
    Copyright:  (c) 2002 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*/

/* ensure handle is valid */
void wFileCheckHandle( int handle, int mustBeOpen )
{
    if (handle < 1 || handle > W_FILE_MAX_HANDLE) {
        wFatal( W_RUNTIME, "Bad file number #%d", handle);
    }

    /* only check if flag set */
    if (mustBeOpen) {
        if (wFileHandles[handle-1] == NULL) {
            wFatal( W_RUNTIME, "File #%d is not open", handle );
        }
    }

}

/* return index of next free file */
int wFileFree()
{
    int     i;
    for( i = 1; i <= W_FILE_MAX_HANDLE; i++ ) {
        if (wFileHandles[i-1] == NULL) {
            return i;
        }
    }
    return 0;
}


/* open a file */
void wFileOpen( char *name, int mode, int handle )
{
    wFileCheckHandle( handle, W_FALSE );

    if (wFileHandles[handle-1] != NULL) {
        wFatal( W_RUNTIME, "file #%d is already open", handle );
    }

    wFileMode[handle-1] = mode;
    switch (mode) {
    case W_FILE_MODE_INPUT:
        wFileHandles[handle-1] = fopen( name, "rb" );
        break;
    case W_FILE_MODE_OUTPUT:
        wFileHandles[handle-1] = fopen( name, "wb" );
        break;
    case W_FILE_MODE_APPEND:
        wFileHandles[handle-1] = fopen( name, "ab" );
        break;
    default:
        /* should not happen */
        wFatal( W_RUNTIME, "unknown file mode" );
    }

    if ((int)(wFileHandles[handle-1] ) == (int)NULL) {
        wFatal( W_RUNTIME, "Error opening file #%d", handle );
    }
}

/* open a file, return the handle */
int wFOpen( char *name, char *mode )
{
    int     handle, modeFlag;

    /* determine mode */
    switch (mode[0]) {
    case 'r':
        modeFlag = W_FILE_MODE_INPUT;
        break;
    case 'w':
        modeFlag = W_FILE_MODE_OUTPUT;
        break;
    case 'a':
        modeFlag = W_FILE_MODE_APPEND;
        break;
    default:
        wFatal( W_RUNTIME, "unknown file mode" );
    }

    /* try opening it on next available handle */
    handle = wFileFree();
    wFileOpen( name, modeFlag, handle );
    return handle;

}


/* close an open file */
void wFileClose( int handle )
{
    int result;

    wFileCheckHandle( handle, W_FALSE );
    if (wFileHandles[handle-1] != NULL) {
        result = fclose( wFileHandles[handle-1] );
        if (result != 0) {
            wFatal( W_RUNTIME, "Error closing file #%d (%d)", handle, result );
        }
        wFileHandles[handle-1] = NULL;
    }
}

/* close all open files */
void wFileCloseAll()
{
    int     i;

    for( i = 1; i <= W_FILE_MAX_HANDLE; i++ ) {
        wFileClose( i );
    }
}

/* see if a file exists */
int wFileExists( char *name )
{
    FILE    *handle;
    int     result;

    /* try to open the file */
    handle = fopen( name, "rb" );

    /* assume if you can't open it, it doesn't exist */
    result = (int)(handle != (int)NULL);
    if (result) {
        /* close the file */
        if (fclose(handle) != 0) {
            wFatal( W_RUNTIME, "Error closing file #%s", name );
        }
    }
    return result;
}


/* return a string from the file */
char *wFileLineInput( int handle )
{
    int len;
    char buffer[W_FILE_BUFFER_MAX];

    wFileCheckHandle( handle, W_TRUE );

    if (wFileMode[handle-1] != W_FILE_MODE_INPUT) {
        wFatal( W_RUNTIME, "File #d is not open for Input", handle );
    }

    buffer[0] = '\0';
    fgets( buffer, W_FILE_BUFFER_MAX-1, wFileHandles[handle-1] );

    /* ensure dos-style eol */
    len = wFixEol( buffer );
    if (len > 0) {
        /* now remove it */
        buffer[len-1] = '\0';
    }

    return wCopyString( buffer );
}

/* print a string to a file */
void wFilePrintString( int handle, char *text )
{
    wFileCheckHandle( handle, W_TRUE );
    switch ( wFileMode[handle-1] ) {
    case W_FILE_MODE_INPUT:
        wFatal( W_RUNTIME, "Bad file mode: file #%d is Input, not Output or Append", handle );
        break;
    case W_FILE_MODE_OUTPUT:
    case W_FILE_MODE_APPEND:
        if (fputs(text, wFileHandles[handle-1]) == 0) {
            wFatal( W_RUNTIME, "wFilePrintString: error writing to file #d", handle );
        }
        break;
    default:
        /* should not happen */
        wFatal( W_RUNTIME, "wFilePrintString: unknown file mode" );
    }
}

/* return true if end of file */
int wFileEof( int handle )
{
    char    byte;
    FILE    *fp;

    wFileCheckHandle( handle, W_TRUE );
    fp = wFileHandles[handle-1];

    /* feof isn't very good in DOS */
    if (fread( &byte, 1, 1, fp ) == 0) {
        return W_TRUE;
    }
    /* move back one byte */
    fseek( fp, -1, 1 );
    return W_FALSE;
}

/* return a byte from the file */
int wFileReadByte( int handle )
{
    FILE    *fp;

    wFileCheckHandle( handle, W_TRUE );
    fp = wFileHandles[handle-1];

    if (wFileMode[handle-1] != W_FILE_MODE_INPUT) {
        wFatal( W_RUNTIME, "Bad file mode" );
    }
    return fgetc( fp );
}

/* write a byte to the file */
void wFileWriteByte( int handle, char c )
{
    FILE    *fp;

    wFileCheckHandle( handle, W_TRUE );
    fp = wFileHandles[handle-1];

    if (wFileMode[handle-1] == W_FILE_MODE_INPUT) {
        wFatal( W_RUNTIME, "Bad file mode" );
    }
    fputc( c, fp );
}


/* seek to a file position */
long wFileSeek( int handle, long pos )
{
    FILE    *fp;

    wFileCheckHandle( handle, W_TRUE );
    fp = wFileHandles[handle-1];

    if (wFileMode[handle-1] != W_FILE_MODE_INPUT) {
        wFatal( W_RUNTIME, "Bad file mode" );
    }

    return fseek( fp, pos-1, 0 );
}

/* return size of file in bytes */
long wFileSize( int handle )
{
    long    currentPos, endPos;
    FILE    *fp;

    wFileCheckHandle( handle, W_TRUE );
    fp = wFileHandles[handle-1];

    if (wFileMode[handle-1] != W_FILE_MODE_INPUT) {
        wFatal( W_RUNTIME, "Bad file mode" );
    }

    /* save current position */
    currentPos = ftell( fp );

    /* seek to end */
    fseek( fp, 0, 2 );
    endPos = ftell( fp );

    /* restore prior position */
    fseek( fp, currentPos, 0 );

    return endPos;
}


/* return current file position */
long wFilePosition( int handle )
{
    long    pos;
    FILE    *fp;

    wFileCheckHandle( handle, W_TRUE );
    fp = wFileHandles[handle-1];

    pos = ftell( fp );
    if (pos != -1) {
        /* offset starts at 1, not zero */
        pos++;
    }
    return pos;
}
