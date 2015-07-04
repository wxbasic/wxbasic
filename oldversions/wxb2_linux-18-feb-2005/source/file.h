/*************************************************************
    Name:       file.h
    Purpose:    file support for wxBasic
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/

#define W_FILE_MODE_INPUT       0
#define W_FILE_MODE_OUTPUT      1
#define W_FILE_MODE_APPEND      2
#define W_FILE_MAX_HANDLE       32
#define W_FILE_BUFFER_MAX       1024

/* handles are 1 relative */
FILE    *wFileHandles[W_FILE_MAX_HANDLE+1];
int     wFileMode[W_FILE_MAX_HANDLE+1];

int wFileCheckHandle( int handle, int mustBeOpen );
int wFileNextHandle( void );
char *wFileGetFullName( char *fileName );
void wFileOpen( char *name, int mode, int handle );
int wFileOpenCStyle( char *name, char *mode );
void wFileClose( int handle );
void wFileCloseAll( void );
int wFileExists( char *name );
void wFileLineInput( int handle );
void wFileKeyboardInput( void );
void wFilePrintString( int handle, char *text );
int wFileEof( int handle );
int wFileReadByte( int handle );
void wFileWriteByte( int handle, char c );
long wFileSeek( int handle, long pos );
long wFileSize( int handle );
long wFilePosition( int handle );
