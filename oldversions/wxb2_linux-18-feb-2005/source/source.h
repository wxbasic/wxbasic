/*************************************************************
    Name:       source.h
    Purpose:    source code routines
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/

/* a line of source code */
struct wSource {
    int     lineNum;        /* line number from file */
    char    *fileName;      /* name of file */
    char    *text;          /* text from source file */
};


/* source file information */
wGrow *wInclude = NULL;
wGrow *wSourceFile = NULL;


void wSourceInit( void );
wSource *wSourceGet( int id );
char *wSourceGetChar( int id );
int wSourceFixEol( char *buffer );
int wSourceInclude( char *text );
void wSourceLoad( char *fname, int offset );
void wSourceScanNextWord( char *buffer, char *word, int *start, int *len, int lcaseFlag );
void wSourceScanLoad( int i, char *buffer, int *wordStart, int *wordLen );
int wSourceReadNextLine( void );
void wSourceSkipExpression( void );
void wSourceScanForRoutines( void );
