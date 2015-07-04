/*************************************************************
    Name:       file.c
    Purpose:    file support for wxBasic
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/

/* ensure handle is valid */
int wFileCheckHandle( int handle, int mustBeOpen )
{
    if (handle < 1 || handle > W_FILE_MAX_HANDLE) {
        wErrorThrow( W_ERROR_FILE, "Bad file number #%d", handle);
        return W_FALSE;
    }

    /* only check if flag set */
    if (mustBeOpen) {
        if (wFileHandles[handle-1] == NULL) {
            wErrorThrow( W_ERROR_FILE, "File #%d is not open", handle );
            return W_FALSE;
        }
    }
    return W_TRUE;
}

/* return index of next free handle */
int wFileNextHandle()
{
    int     i;
    for( i = 1; i <= W_FILE_MAX_HANDLE; i++ ) {
        if (wFileHandles[i-1] == NULL) {
            return i;
        }
    }
    return 0;
}


/* add current working directory if path not specified */
char *wFileGetFullName( char *fileName )
{
    int     len;
    char    *fullName;

    wMemTest( fileName, "wFileGetFullName:fileName" );

    // full path specified?
    if ( strchr( fileName, '/' ) || strchr( fileName, '\\' ) ) {
        return wCharCopy(fileName);
    }

    // no working directory?
    if (wTheCwd == NULL) {
        return wCharCopy(fileName);
    }

    /* prepend the current working directory */
    len = strlen( wTheCwd ) + strlen( fileName ) + 2;
    fullName = (char *)wMalloc( len );        
    strcpy( fullName, wTheCwd );
    strcat( fullName, fileName );

    return fullName;
}
        

/* open a file */
void wFileOpen( char *name, int mode, int handle )
{
    char *fullName;

    wFileCheckHandle( handle, W_FALSE );

    if (wFileHandles[handle-1] != NULL) {
        wErrorThrow( W_ERROR_FILE, "File #%d is already open", handle );
    }

    fullName = wFileGetFullName( name );

    wFileMode[handle-1] = mode;
    switch (mode) {
    case W_FILE_MODE_INPUT:
        wFileHandles[handle-1] = fopen( fullName, "rb" );
        break;
    case W_FILE_MODE_OUTPUT:
        wFileHandles[handle-1] = fopen( fullName, "wb" );
        break;
    case W_FILE_MODE_APPEND:
        wFileHandles[handle-1] = fopen( fullName, "ab" );
        break;
    default:
        /* should not happen */
        wErrorThrow( W_ERROR_FILE, "Unknown file mode" );
    }

    if (wFileHandles[handle-1] == NULL) {
        wErrorThrow( W_ERROR_FILE, "Error opening file #%d", handle );
    }

    wFree( fullName );

}

/* open a file, return the handle */
int wFileOpenCStyle( char *name, char *mode )
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
    	/* otherwise, the compiler complains */
        modeFlag = 0;
        wErrorThrow( W_ERROR_FILE, "Unknown file mode" );
    }

    /* try opening it on next available handle */
    handle = wFileNextHandle();
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
            wErrorThrow( W_ERROR_FILE, "Error closing file #%d (%d)", handle, result );
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
    char    *fullName;

    /* get full name */
    fullName = wFileGetFullName( name );

    /* try to open the file */
    handle = fopen( fullName, "rb" );

    /* assume if you can't open it, it doesn't exist */
    result = (int)(handle != (int)NULL);
    if (result) {
        /* close the file */
        if (fclose(handle) != 0) {
            wErrorThrow( W_ERROR_FILE, "Can't close file #%s", name );
        }
    }

    wFree( fullName );

    return result;
}


/* load a string from the file into wTheFileBuffer */
void wFileLineInput( int handle )
{
    int len;
    char *buffer;

    wFileCheckHandle( handle, W_TRUE );

    if (wFileMode[handle-1] != W_FILE_MODE_INPUT) {
        wErrorThrow( W_ERROR_FILE, "File #%d is not open for Input", handle );
    }

    /* need to allocate the buffer? */
    if (wTheFileBuffer == NULL) {
        /* allocate a buffer */
        wTheFileBuffer = (char *)wMalloc( W_FILE_BUFFER_MAX );
    }
    
    wMemTest( wTheFileBuffer, "wFileLineInput:wTheFileBuffer" );

    /* read from the file */
    if (fgets( wTheFileBuffer, W_FILE_BUFFER_MAX-1, wFileHandles[handle-1] ) == NULL) {
        wErrorThrow( W_ERROR_FILE, "Error reading from file" );
    }

    /* ensure dos-style eol */
    len = wSourceFixEol( wTheFileBuffer );
    if (len > 0) {
        /* now remove it */
        wTheFileBuffer[len-1] = '\0';
    }
}

/* load a string from stdin into wTheFileBuffer */
void wFileKeyboardInput()
{
    int len;
    char *buffer, *result;


    /* need to allocate the buffer? */
    if (wTheFileBuffer == NULL) {
        /* allocate a buffer */
        wTheFileBuffer = (char *)wMalloc( W_FILE_BUFFER_MAX );
    }

    /* read from the file */
    if (fgets( wTheFileBuffer, W_FILE_BUFFER_MAX-1, stdin ) == NULL) {
        wErrorThrow( W_ERROR_FILE, "Error reading from keyboard" );
    }

    /* ensure dos-style eol */
    len = wSourceFixEol( wTheFileBuffer );
    if (len > 0) {
        /* now remove it */
        wTheFileBuffer[len-1] = '\0';
    }

}


/* print a string to a file */
void wFilePrintString( int handle, char *text )
{
    wFileCheckHandle( handle, W_TRUE );
    switch ( wFileMode[handle-1] ) {
    case W_FILE_MODE_INPUT:
        wErrorThrow( W_ERROR_FILE, "Bad file mode: file #%d is Input, not Output or Append", handle );
        break;
    case W_FILE_MODE_OUTPUT:
    case W_FILE_MODE_APPEND:
        if (fputs(text, wFileHandles[handle-1]) == EOF) {
            wErrorThrow( W_ERROR_FILE, "Error writing to file #d (wFilePrintString)", handle );
        }
        break;
    default:
        /* should not happen */
        wErrorThrow( W_ERROR_FILE, "Unknown file mode (wFilePrintString)" );
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
        wErrorThrow( W_ERROR_FILE, "Bad file mode" );
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
        wErrorThrow( W_ERROR_FILE, "Bad file mode" );
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
        wErrorThrow( W_ERROR_FILE, "Bad file mode" );
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
        wErrorThrow( W_ERROR_FILE, "Bad file mode" );
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
