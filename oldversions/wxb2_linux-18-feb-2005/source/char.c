/*************************************************************
    Name:       char.c
    Purpose:    char buffer handling routines
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/

/* copy C string to a new buffer, return address */
char *wCharCopy( char *text )
{
    int len;
    char *buffer;

    /* don't memtest, used for moving constants */

    /* get length, create a buffer */
    len = strlen( text );
    buffer = (char *)wMalloc( len+1 );

    /* copy to new buffer */
    memmove( (void *)buffer, (void *)text, len+1 );

    return buffer;
}

/* allocate an empty string */
char *wCharMalloc( int length )
{
	char *buffer;

	buffer = (char *)wMalloc( length );
	buffer[0] = '\0';

	return buffer;
}


/* concat src text to dst */
char *wCharConcat( char *dst, char *src )
{
    int dstLen, srcLen;

    /* calculate size needed */
    dstLen = strlen( dst );
    srcLen = strlen( src );

    /* ensure the dst buffer is large enough */
    dst = (char *)wRealloc( (void *)dst, dstLen + srcLen + 2 );

    /* concat the src into the dst buffer */
    strcat( dst, src );

    return dst;
}

char *wCharConcatInt( char *dst, int i )
{
    char buffer[32];

    /* format the int */
    sprintf( buffer, "%d", i );
    return wCharConcat( dst, buffer );
}

char *wCharConcatPtr( char *dst, void *ptr )
{
    char buffer[32];

    /* format the pointer */
    sprintf( buffer, "%p", ptr );
    return wCharConcat( dst, buffer );
}



/* convert buffer to lower case */
void wCharToLower( char *text )
{
    int len, i;

    wMemTest( text, "wToLowerChar:text" );

    /* create lower case version of name */
    len = strlen( text );
    for ( i = 0; i < len; i++ ) {
        text[i] = tolower( text[i] );
    }
}


/* copy C string to lower case */
char *wCharCopyToLower( char *text )
{
    int len, i;
    char *buffer;

    /* create lower case version of name */
    len = strlen( text );
    buffer = (char *)wMalloc( len+1 );
    for ( i = 0; i < len; i++ ) {
        buffer[i] = tolower( text[i] );
    }
    buffer[len] = '\0';

    return buffer;
}


