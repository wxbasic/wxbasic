/*
    Name:       builtin.c
    Purpose:    builtin routines for wxBasic
    Author:     David Cuny
    Copyright:  (c) 2002 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*/


void wNotYet( char *name )
{
    wFatal( W_RUNTIME, "%s is not implemented yet", name );
}

/* debugging wrapper of printStack */
void wBasPrintStack()
{
    wPrintStack();
    wPushNumber( 0 );
}

/* returns absolute value of number */
void wBasAbs()
{
    wNumber  n;
    n = wPopNumber();
    if (n < 0) {
        wPushNumber( -n );
    } else {
        wPushNumber( n );
    }
}

/* returns arccos of number */
void wBasACos()
{
    wPushNumber( acos( wPopNumber() ) );
}

/* returns bitwise 'and' of two numbers */
void wBasAndBits()
{
    wPushNumber( (wNumber)((int)wPopNumber() & (int)wPopNumber()) );
}


/* return number of args in caller */
void wBasArgc()
{
    /* arg count is at wLocalStart */
    wCopyStackItem( wLocalStart );
}

/* copy arg onto stack */
void wBasArgv()
{
    int     index, count;

    /* get arg */
    index = (int)wPopNumber();

    /* check range */
    wCopyStackItem( wLocalStart );
    count = (int)wPopNumber();
    if (index > count || index < 0) {
        wFatal( W_RUNTIME, "Argv: The routine only has %d args, not %d",
            count, index );
    }
    
    wCopyStackItem( wLocalStart+index );
}

/* returns ascii value of first char in string */
void wBasAsc()
{
    char    *string;
    string = wPopString();
    wPushNumber( string[0] );
    wFree( string );
}

/* returns arcsin of number */
void wBasASin()
{
    wPushNumber( asin( wPopNumber() ) );
}

/* returns arctan of number */
void wBasATan()
{
    wPushNumber( atan( wPopNumber() ) );
}

/* change directory */
void wBasChDir()
{
    wNotYet("ChDir");
    wPushNumber((wNumber)0);
}

/* return string corresponding to ascii key value */
void wBasChr()
{
    char    *buffer = (char *)wMalloc(sizeof(char)*2);
    buffer[0] = (char)wPopNumber();
    buffer[1] = '\0';
    wPushString( buffer );
}

/* returns requested arg from command line */
void wBasCommand()
{
    int     argNum;

    /* was an arg passed? */
    if (wArgCount == 0) {
        /* return count of args */
        wPushNumber( wArgc );

    } else {

        /* get arg number */
        argNum = wPopNumber();
        if (argNum < 0 || argNum > wArgc) {
            /* out of range */
            wPushStringCopy( "" );
    
        } else {
            /* return copy of arg */
            wPushStringCopy( wArgv[ argNum-1 ] );
        }
    }
}


/* concatenate two strings */
void wBasConcat()
{    
    int     len1, len2;
    char    *string1, *string2, *buffer;

    string2 = wPopString();
    string1 = wPopString();

    len1 = strlen( string1 ),
    len2 = strlen( string2 );

    buffer = (char *)wMalloc( len1 + len2 + 1 );

    memcpy( buffer, string1, len1 );
    memcpy( buffer+len1, string2, len2 );
    buffer[len1+len2] = '\0';
    wPushString( buffer );

    wFree( string1 );
    wFree( string2 );
}


/* returns representation from base to base */
void wBasConvBase()
{
    wNotYet("ConvBase");
    wPushNumber(0);
}


/* connect a routine to a callback */
void wBasConnect()
{
#ifdef __WXWIN__
    int     i, len, handle, id, eventType, useId;
    char    *name;
    wSymbol  *routine;

    /* get routine name */
    name = wPopString();

    /* look it up */
    routine = wFindSymbol( name, NULL );
    if (routine == NULL) {
        wFatal( W_RUNTIME, "Connect: Can't find Sub or Function %s", name );
    }
    wFree(name);

    /* function or a sub? */
    if (routine->symbolType != W_SYM_SUB &&
        routine->symbolType != W_SYM_FUNCTION ) {
            wFatal( W_RUNTIME, "Connect: %s is not a Function or a Sub");
    }

    eventType = (int)wPopNumber();

    /* optional identifier */
    if (wArgCount==4) {
        id = (int)wPopNumber();
        useId = W_TRUE;

    } else {
        id = -1;
        useId = FALSE;

    }

    handle = (int)wPopNumber();

    wConnect( id, useId, handle, eventType, routine );
    wPushNumber( 0 );

#else
    wFatal( W_RUNTIME, "Connect() is not available in console mode");
#endif
}


/* returns cos of number */
void wBasCos()
{
    wPushNumber( cos( wPopNumber() ) );
}

/* returns date in MM-DD-YYYY format */
void wBasDate()
{
    time_t      t;
    struct tm   *tmp;
    char        *buffer = (char *)wMalloc(11);

    /* get time */
    t = time(NULL);     
    tmp = localtime(&t);

    sprintf( buffer, "%02d-%02d-%04d", 
        tmp->tm_mon+1, tmp->tm_mday, tmp->tm_year+1900 );

    wPushString( buffer );
}

/* returns next file of FileSpec */
void wBasDir()
{
    wNotYet("Dir");
    wPushNumber(0);
}

/* returns true if directory exists */
void wBasDirExists()
{
    wNotYet("DirExists");
    wPushNumber(0);
}

/* returns nonzero if Eof */
void wBasEof()
{
    wPushNumber( (wNumber)wFileEof( (int)wPopNumber() ) );
}

/* returns exponential function */
void wBasExp()
{
    wPushNumber( exp( wPopNumber() ) );
}

/* c style fclose */
void wBasFClose()
{
    wFileClose( wPopNumber() );
    wPushNumber( 0 );
}


/* c style fgets */
void wBasFGets()
{
    int     handle;
    char    *buffer;

    handle = wPopNumber();
    buffer = wFileLineInput( handle );
    wPushString( buffer );
}


/* c style fopen */
void wBasFOpen()
{
    char    *fname, *fmode;

    fmode = wPopString();
    fname = wPopString();
    wPushNumber(wFOpen(fname, fmode));
    wFree( fname );
    wFree( fmode );
    
}


/* c style fputs */
void wBasFPuts()
{
    int     handle;
    char    *text;

    text = wPopString();
    handle = wPopNumber();
    wFilePrintString( handle, text );
    wFree( text );
    wPushNumber( 0 );
}


/* returns true if the file exists */
void wBasFileExists()
{
    char    *fname;

    fname = wPopString();
    wPushNumber(wFileExists(fname));
    wFree( fname );
    
}

/* truncate fractional number, rounding down towards zero */
void wBasFix()
{
    wPushNumber( floor( wPopNumber() ) );
}

/* returns formatted string with embedded args */
void wBasFormat()
{
    wNotYet("Format");
    wPushNumber(0);
}

/* return fractional portion of number */
void wBasFrac()
{
    wNumber  n;
    n = wPopNumber();
    n -= floor(n);
    wPushNumber(n);
}

/* return the handle of the next free file */
void wBasFreeFile()
{
    wPushNumber(wFileFree());
}


/* wBasGetWxApp: returns index of to wxApp */
void wBasGetWxApp()
{
    wPushNumber((wNumber)wAppIndex);
}

/* returns hexidecimal representation of number */
void wBasHex()
{
    int i;
    char    *buffer = (char *)wMalloc(16);
    i = (int)wPopNumber();
    sprintf( buffer, "%x", i);
    wPushString( buffer );
}

/* return number of indexes in array */
void wBasIndexes()
{
    int     indexes;

    /* array is on stack */
    indexes = wGetArrayIndexes();
    wPopNumber();

    wPushNumber(indexes);
}

/* insert source string to target at index */
void wBasInsert()
{
    char    *source, *target;
    int     index;
    
    index = (int)wPopNumber();    
    target = wPopString();
    source = wPopString();
    
    wNotYet("Insert");
    
    wFree( source );
    wFree( target );
}

/* returns position in source that target was found */
void wBasInstr()
{
    int     start, searchLen, findLen, i;
    char    *find, *search;

    find = wPopString();
    search = wPopString();
    if (wArgCount==3) {
        start = (int)wPopNumber()-1;
        if (start < 0) {
            start = 0;
        }

    } else {
        start = 0;
    }

    searchLen = strlen( search );
    findLen = strlen( find );

    /* searching for empty string? */
    if (searchLen == 0 || findLen == 0) {
        wFree( search );
        wFree( find );
        wPushNumber( 0 );
        return;
    }

    start = (int)floor( start );
    for ( i = start; i < searchLen; i++ ) {
        if (strncmp( search+i, find, findLen ) == 0) {
            wPushNumber( i+1 );
            wFree( search );
            wFree( find );
            return;
        }
    }

    /* not found */
    wFree( search );
    wFree( find );
    wPushNumber( 0 );
}

/* convert to 32 bit integer, truncating decimals */
void wBasInt()
{
    wPushNumber( (int)wPopNumber() );
}

/* delete filename */
void wBasKill()
{
    char    *name = wPopString();
    remove( name );
    wFree(name);
    wPushNumber(0);
}

/* convert string to lower case */
void wBasLCase()
{
    int     len, i;
    char    *string;
    
    string = wPopString();
    len = strlen( string );
    for ( i = 0; i<len; i++){ 
        string[i] = (char)tolower( (int)string[i] );
    }
    wPushString( string );
}

/* returns leftmost chars in string */
void wBasLeft()
{
    int     pos, len, newLen;
    char    *string, *left;
    
    pos = (int)wPopNumber();
    string = wPopString();
    len = strlen(string);

    if (pos > len-1) {
        wPushString( string );
        return;
    }

    if (pos < 1) {
        wFree( string );
        wPushStringCopy( "" );
        return;
    }

    newLen = (pos);
    left = (char *)wMalloc(newLen);
    memcpy(left,string,newLen);
    left[newLen] = '\0';
    wFree( string );
    wPushString( left );
}

/* return length of string */
void wBasLen()
{
    char    *string;
    string = wPopString();
    wPushNumber( strlen( string ) );
    wFree( string );
}

/* returns position in file */
void wBasLoc()
{
    wPushNumber( wFilePosition( wPopNumber() ) );
}


/* returns length of file */
void wBasLof()
{
    wPushNumber( wFileSize( wPopNumber() ) );
}


/* returns natural log of expression */
void wBasLog()
{
    wPushNumber( log( wPopNumber() ) );
}

/* returns lower bound of array */
void wBasLBound()
{
    int     index, range;

    index = wPopNumber();
    /* leave array pointer on stack */

    range = wGetArrayBound( index, 0 );

    /* pop array pointer */
    wPopNumber();

    wPushNumber(range);
}

/* returns string with left whitespace removed */
void wBasLTrim()
{
    char    *string, *trimmed;
    
    string = wPopString();
    trimmed = string;
    while ( trimmed[0] != '\0' ) {
        if (!isspace(trimmed[0])) {
            break;
        }
        trimmed++;
    }
    wPushStringCopy( trimmed );
    wFree( string );
}

/* calls wxApp::MainLoop */
void wBasMainLoop()
{
#ifdef __WXWIN__
    wResolveMethod( wAppIndex, "mainloop" );
#else
    wFatal( W_RUNTIME, "MainLoop() is not available in console mode");
#endif
}

/* returns string with chars 1..n from source */
void wBasMid()
{
    int     i, j, n, len;
    char    *string, *buffer;

    /* get args */
    n = (int)wPopNumber();
    i = (int)wPopNumber();
    string = wPopString();

    /* early outs */
    len = strlen( string );
    if ( i < 1 || i > len ) {
        wPushString( "" );
        wFree( string );
        return;
    }

    buffer = (char *)wMalloc(len+2);
    for ( j = 0; j < n; j++ ) {
        if (string[i+j-1] == '\0' ) {
            break;
        }
        buffer[j] = string[i+j-1];
    }
    buffer[j] = '\0';
    wPushString( buffer );
    wFree( string );
}

/* create a new directory */
void wBasMkDir()
{
    char    *name;
    name = wPopString();
    wNotYet("MkDir");
    wFree( name );
}

/* returns bitwise 'not' of number */
void wBasNotBits()
{
    wPushNumber( (wNumber)(~(int)wPopNumber()) );
}


/* returns bitwise 'or' of two numbers */
void wBasOrBits()
{
    wPushNumber( (wNumber)((int)wPopNumber() | (int)wPopNumber()) );
}


/* sort an array */
void wBasQuickSort()
{
    wNotYet("QuickSort");
    wPushNumber(0);
}

/* reseed the random number generator */
void wBasRandomize()
{
    int seed;
    if (wArgCount==1) {
        seed = (int)wPopNumber();
    } else {
        seed = time(NULL);
    }
    srand( seed );
    wPushNumber(0);
}

/* return a byte from the file */
void wBasReadByte()
{
    wPushNumber( (wNumber)wFileReadByte( (char)wPopNumber() ) );
}

/* rename file */
void wBasRename()
{
    char    *oldName, *newName;
    newName = wPopString();
    oldName = wPopString();
    rename( oldName, newName );
    wFree( oldName );
    wFree( newName );
    wPushNumber(0);
}

/* replace string from source with replace starting at index */
void wBasReplace()
{    
    int        i;
    char    *s, *r;
    
    s = wPopString();
    r = wPopString();
    if (wArgCount == 3){
            i = (int)wPopNumber();
    } else {
            i = -1;
    }
        
    wNotYet("Replace");
    
    wFree( s );
    wFree( r );
}

/* replace substring in source with withstring */
void wBasReplaceSubStr()
{
    char    *source, *replace, *with;
    
    with = wPopString();
    replace = wPopString();
    source = wPopString();
    
    wNotYet("ReplaceSubStr");
    
    wFree( with );
    wFree( replace );
    wFree( source );

    wPushStringCopy("");
}

/* reverse a string */
void wBasReverse()
{
    int     len, i, j;
    char    *string, *buffer; 
    
    string = wPopString();
    len = strlen( string );
    
    buffer = (char *)wMalloc(len+1);
    j = len-1;
    for( i = 0; i < len; i++ ) {
        buffer[j--] = string[i];
    }
    buffer[len] = '\0';
    
    wPushString(buffer);
    wFree( string );
}

/* returns rightmost chars in string */
void wBasRight()
{
    int     pos, len, newLen;
    char    *string, *right;
    
    pos = (int)wPopNumber();
    string = wPopString();
    len = strlen(string);
    
    if (pos >= len) {
        wPushString( string );
        return;
    }

    if (pos < 1) {
        wFree( string );
        wPushStringCopy( "" );
        return;
    }

    newLen = (pos)+1;
    right = (char *)wMalloc((len-newLen)+1);
    memcpy(right,string+(len-pos),newLen);
    wPushString( right );
    wFree( string );
}

/* reverse Instr function, search from end to start */
void wBasRInstr()
{
    int     start, searchLen, findLen, i;
    char    *find, *search;

    find = wPopString();
    search = wPopString();

    findLen = strlen( find );
    searchLen = strlen( search );

    /* optional starting position */
    if (wArgCount==3) {
        start = (int)wPopNumber()-1;
        if (start > searchLen ) {
            start = searchLen-1;
        }
    } else {
        start = searchLen-1;
    }

    /* searching for empty string? */
    if (searchLen == 0 || findLen == 0) {
        wPushNumber( 0 );
        wFree( find );
        wFree( search );
        return;
    }


    /* search */
    for ( i = start; i >= 0; i-- ) {
        if (strncmp( search+i, find, findLen ) == 0) {
            wFree( find );
            wFree( search );
            wPushNumber( i+1 );
            return;
        }
    }

    /* not found */
    wFree( find );
    wFree( search );
    wPushNumber( 0 );
}

/* remove directory */
void wBasRmDir()
{
    char    *name;
    name = wPopString();
    wNotYet("RmDir");
    wFree(name);
}

/* return an random number */
void wBasRnd()
{
    int upper, result;

    result = rand();
    if (wArgCount==1) {
        upper = (int)wPopNumber();
        result = (result % (upper-1))+1;
    }
    wPushNumber( (wNumber)result );
}

/* round to nearest integer */
void wBasRound()
{
    wNumber n1, n2;
    n1 = wPopNumber();
    n2 = floor(n1);
    if (n2 == 0) {
        /* leave it alone */

    } else if (n2 > 0) {
        if ((n1 - n2) > 0.5) {
            n2++;
        }
    } else {
        if (-(n2 - n1) > 0.5) {
            n2++;
        }
    }
    wPushNumber( n2 );
}

/* right trim string */
void wBasRTrim()
{
    int     len, i;
    char    *string;
    string = wPopString();
    len = strlen(string);
    for ( i = len-1; i > -1; i-- ) {
        if (!isspace(string[i])) {
            string[i+1] = '\0';
            wPushString( string );
            return;
        }
    }
    string[0] = '\0';
    wPushString( string );
}

/* run command on new thread */
void wBasRun()
{
    wNotYet("Run");
    wPushNumber(0);
}

/* seek file position/return current file position */
void wBasSeek()
{
    int     file, pos;

    /* which version? */
    if (wArgCount==2) {
        /* seek to position */
        pos = wPopNumber();
        file = wPopNumber();
        wPushNumber( wFileSeek( file, pos ));

    } else {
        /* return position in file */
        file = wPopNumber();
        wPushNumber( wFilePosition( file ) );
    }
}

/* returns sign of numeric expression */
void wBasSgn()
{
    wNumber  n;
    n = wPopNumber();
    if (n < 0) {
        wPushNumber(-1);
    } else if (n > 0) {
        wPushNumber(1);
    } else {
        wPushNumber(0);
    }
}

/* execute command, wait until finished */
void wBasShell()
{
    char    *string;
    string = wPopString();
    system(string);
    wFree(string);
    wPushNumber(0);
}

/* returns sine of given angle in radians */
void wBasSin()
{
    wPushNumber( sin( wPopNumber() ) );
}

/* return string with n spaces in it */
void wBasSpace()
{
    char    *string;
    int     n;
    n = (int)wPopNumber();
    if (n<0) {
        n = 0;
    }
    string = (char *)wMalloc((unsigned int)n+1);
    memset(string,' ',n);
    string[n] = '\0';
    wPushString(string);
}

/* return square root - make sure it's non-negative */
void wBasSqr()
{
    wPushNumber( sqrt( wPopNumber() ) );
}

/* return string representation of numeric expression */
void wBasStr()
{
    char    *string;
    string = wPopString();
    wPushString( string );
}

/* converts a floating point or number value to a string */
void wBasStrF()
{
    char    *string;
    string = wPopString();
    wPushString( string );
}

/* returns string m chars wide with n in it */
void wBasString()
{
    int     m, n;
    char    *string, *buffer;
    
    if (wData[wTos].datatype == W_DATA_STRING) {
        string = wPopString();
        m = (int)wPopNumber();
        n = string[0];
        wFree( string );
    } else {
        n = (char)wPopNumber();
        m = (int)wPopNumber();
    }
    buffer = (char *)wMalloc(m+1);
    memset(buffer, n, m);
    buffer[m] = '\0';
    wPushString( buffer );
}    

/* returns number of occurances of matchstring */
void wBasTally()
{
    char    *search, *match;
    match = wPopString();
    search = wPopString();
    wNotYet("Tally");
    wFree( match );
    wFree( search );
    wPushNumber(0);
}

/* return tanget of given angle in radians */
void wBasTan()
{
    wPushNumber( tan( wPopNumber() ) );
}

/* returns current timer value */
void wBasTicks()
{
    wPushNumber( clock() );
}


/* return time in HH:MM:SS format */
void wBasTime()
{
    time_t      t;
    struct tm   *tmp;
    char        *buffer = (char *)wMalloc(9);

    /* get time */
    t = time(NULL);     
    tmp = localtime(&t);

    sprintf( buffer, "%02d:%02d:%02d",
        tmp->tm_hour, tmp->tm_min, tmp->tm_sec );

    wPushString( buffer );
}


/* returns string with datatype */
void wBasTypeOf()
{
    int         datatype;
    wVariant    *v;
    v = wGetStackPointer( wTos );
    datatype = v->datatype;
    wDropTos();
    switch(datatype) {
    case W_DATA_NUMBER:
        wPushStringCopy( "number" );
        break;

    case W_DATA_STRING:
        wPushStringCopy( "string" );
        break;

    case W_DATA_OBJECT:
        wPushStringCopy( "object" );
        break;

    default:
        wPushStringCopy( "unknown" );
        break;
    }
}


/* upperbound of array */
void wBasUBound()
{
    int     index, range;

    index = wPopNumber();
    /* leave array pointer on stack */

    range = wGetArrayBound( index, 1 );

    /* pop array pointer */
    wPopNumber();

    wPushNumber(range);
}

/* convert string to upper case */
void wBasUCase()
{
    int     len, i;
    char    *string;
    
    string = wPopString();
    len = strlen( string );
    for ( i = 0; i<len; i++){ 
        string[i] = toupper( string[i] );
    }
    wPushString( string );
}

/* returns closest numeric representation of number */
void wBasVal()
{
    char    *string;
    string = wPopString();
    wPushNumber( atof(string) );
    wFree( string );
}

/* return a byte from the file */
void wBasWriteByte()
{
    char    c;
    int     fileNum;

    c = wPopNumber();
    fileNum = wPopNumber();
    wFileWriteByte( fileNum, c );
    wPushNumber( 0 );
}

/* returns bitwise 'xor' of two numbers */
void wBasXorBits()
{
    wPushNumber( (wNumber)((int)wPopNumber() ^ (int)wPopNumber()) );
}


/* add a builtin to the dictionary */
wSymbol *wAddBuiltin( char *name, void (*routine)(void), int args, int optArgs )
{
    wSymbol  *s;
    s = wFindSymbol( name, NULL );
    if (s==NULL) {
        s = wAddSymbol( name, NULL, W_SYM_BUILTIN, W_TRUE );
        s->builtin = routine;
        s->args = args;
        s->optArgs = optArgs;

    } else {
        wFatal( W_RUNTIME, "Builtin %s is already declared as a %s",
            s->name, wSymbolName[s->symbolType] );
    }

    return s;
}

/* install all the builtins to the dictionary */
void wInitBuiltins()
{
    int     i;
    wSymbol *s;

    for (i = 0; wBuiltin[i].name != NULL; i++) {  
        s = wAddBuiltin( wBuiltin[i].name,
                         wBuiltin[i].routine,
                         wBuiltin[i].args,
                         wBuiltin[i].optArgs );
        s->useCase = W_FALSE;
    }
}
