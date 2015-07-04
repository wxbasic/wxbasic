/*************************************************************
    Name:       source.c
    Purpose:    source code routines
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/

/* initialize source data structures */
void wSourceInit()
{
    wInclude = wGrowNew( 8 );
    wSourceFile = wGrowNew( 32 );
}

/* return number of lines in source file */
int wSourceCount()
{
    return wGrowCount( wSourceFile );
}

/* return line of text of source */
wSource *wSourceGet( int id )
{
    return (wSource *)wGrowGet( wSourceFile, id );
}

char *wSourceGetChar( int id )
{
    wSource *source;
    source = (wSource *)wGrowGet( wSourceFile, id );
    wMemTest( source, "wSourceGetChar:source" );
    return source->text;
}


/* fix the eol char to work under DOS and Linux */
int wSourceFixEol( char *buffer )
{
    int len;

    wMemTest( buffer, "wSourceFixEol:buffer" );

    len = strlen( buffer );

    /* empty string */
    if (len == 0) {
        /* add newline character */
        buffer[1] = '\n';
        buffer[len+1] = '\0';
        return 1;
    }

    /* possibly two character eol? */
    if (len > 1) {
        /* need to adjust for linux or mac eol? */
        if ((buffer[len-2] == '\r' && buffer[len-1] == '\n') ||
            (buffer[len-2] == '\n' && buffer[len-1] == '\r' )) {
            buffer[len-2] = '\n';
            buffer[len-1] = '\0';
            len--;
        }
    }

    /* missing eol? */
    if (buffer[len-1] != '\r' && buffer[len-1] != '\n') {
        /* add missing eol */
        buffer[len] = '\n';
        buffer[len+1] = '\0';
        len++;
    }

    return len;
}

/* return true if include file, and include in source */
int wSourceInclude( char *text )
{
    int len;
    char *lcase;
    char *nameStart, *nameEnd;

    wMemTest( text, "wSourceInclude:text" );

    /* skip whitespace */
    while (text[0] == ' ' || text[0] == '\t' ) {
        text++;
    }

    /* length of string */
    len = strlen( text );

    /* early out */
    if (len < 10) {
        return 0;
    }

    /* convert to lower case for comparison */
    lcase = wCharCopyToLower( text );
    if (strncmp( lcase, "include ", 8 ) == 0) {
        /* release the string */
        wFree( lcase );

        /* file name is quoted */
        nameStart = strchr( text, '\"' );
        nameEnd = strrchr( text, '\"' );
        if (nameStart == NULL || nameEnd == NULL) {
            wErrorThrow( W_ERROR_SYNTAX, "Error in include filename - missing quotes" );
        }

        /* get the string */
        nameStart++;
        nameEnd[0] = '\0';

        /* include it */
        wSourceLoad( nameStart, 0 );

        /* flag that it's not part of the source file */
        return 1;
    }
    wFree( lcase );
    return 0;
}

/* read the source files */
void wSourceLoad( char *fname, int fileOffset )
{
    int i, len, lineCount;
    FILE *handle;
    char *fileName, *fullFileName, *includeName, *buffer;
    wSource *line;

    wMemTest( fname, "wSourceLoad:fname" );

    /* try opening the file */
    handle = fopen( fname, "rt" );

    /* failed? */
    if (handle == NULL) {

        /* no working directory to fall back on? */
        if (wTheCwd == NULL) {
            wErrorThrow( W_ERROR_SYNTAX, "Unable to open \"%s\"", fname );
        }

        /* create full file name */
        fullFileName = wCharCopy( wTheCwd );
        fullFileName = wCharConcat( fullFileName, fname );

        /* try opening the file */
        handle = fopen( fullFileName, "rt" );

        /* failed? */
        if (handle == NULL) {
            wErrorThrow( W_ERROR_SYNTAX, "Unable to open \"%s\" or \"%s\"",
                fname, fullFileName );
        } else {
            /* use full name */
            fileName = fullFileName;
        }
    } else {
        /* use name */
        fileName = wCharCopy( fname );
    }

    /* was this file already included? */
    for ( i = 1; i <= wInclude->count; i++ ) {
        includeName = (char *)wGrowGet( wInclude, i );
        if (strcmp( includeName, fileName ) == 0 ) {
            wFree( fileName );
            return;
        }
    }

    /* add to include list */
    wGrowAppend( wInclude, (int)fileName );

    /* offset into the file? */
    if (fileOffset != 0) {
        /* seek to position in file */
        fseek( handle, fileOffset, 0 );
    }

    /* allocate the buffer */
    buffer = (char *)wMalloc( W_INBUFFER_MAX );

    /* load file */
    lineCount = 0;
    while (1) {
        /* read a line into the buffer */
        lineCount++;
        if (fgets( buffer, W_INBUFFER_MAX-2, handle ) == 0) {
            break;
        }

        /* fix line end character */
        wSourceFixEol( buffer );

        /* make sure it's not an include statement */
        if (wSourceInclude( buffer ) == 0) {

            /* create an entry */
            line = (wSource *)wMalloc( sizeof( wSource ) );
            line->lineNum = lineCount;
            line->fileName = fileName;
            line->text = wCharCopy( buffer );

            /* append to source line */
            wGrowAppend( wSourceFile, (int)line );
        }
    }

    /* close the file */
    fclose( handle );

    /* free the buffer */
    wFree( buffer );
}

/* point the lexer to the next line in the buffers */
int wSourceReadNextLine()
{
        /* end of file? */
        if (wReadLine > wSourceFile->count ) {
            return W_FALSE;
        } else {
            /* get the next line of source code */
            wLineBufferPos = W_BUFFER_EMPTY;
            wLexToken();
            return W_TRUE;
        }
}


/* skip through an expression */
void wSourceSkipExpression()
{
    int parenCount;

    /* reset paren count */
    parenCount = 0;

    /* scan until end of file */
    while ( !wParseTokenIs(W_TOKEN_EOF) ) {
        /* end of expression? */
        if (parenCount == 0 && (wParseTokenIs(')') ||  wParseTokenIs(','))) {
                return;

        /* opening/closing brace? */
        } else if (wParseTokenIs('[')
        ||  wParseTokenIs('(')
        ||  wParseTokenIs('{')) {
            parenCount++;

        } else if (wParseTokenIs(']')
               ||  wParseTokenIs(')')
               ||  wParseTokenIs('}')) {
            parenCount--;

        }
        /* move to next token */
        wLexToken();
    }
}

/* scan source code for routine names */
void wSourceScanForRoutines()
{
    int i, j, wordStart, wordLen, len, inClass, symType, flags;
    char *buffer, *word;
    wSymbol *s, *klass, *inherits, *prior;
	
    /* reset buffer position */
    wReadLine = 0;
    wLineBufferPos = W_BUFFER_EMPTY;

    /* not inside a class definition */
    klass = NULL;    

    /* parse until end of file */
    while (wSourceReadNextLine()) {

        /* set flag? */
        if (wParseTokenIs(W_TOKEN_ABSTRACT) && klass != NULL) {
            /* abstract */
            flags = W_SYM_ISABSTRACT;
            wParseSkip();

        } else if (wParseTokenIs(W_TOKEN_SHARED) && klass != NULL) {
            /* shared */
            flags = W_SYM_ISSHARED;
            wParseSkip();

        } else if (wParseTokenIs(W_TOKEN_VIRTUAL) ) {
            /* virtual */
            flags = W_SYM_ISVIRTUAL;
            wParseSkip();

        } else {
            /* no flags */
            flags = 0;
        }


        /* sub or function */
        if (wParseTokenIs(W_TOKEN_SUB)
        ||  wParseTokenIs(W_TOKEN_FUNCTION)) {
            /* if abstract method, ensure class is abstract */
            if (klass && (!klass->flags) && (flags & W_SYM_ISABSTRACT)) {
                wErrorThrow( W_ERROR_SYNTAX, "Abstract methods can only be defined in Abstract Classes" );
            }

            /* save the symbol type (not the token type!) */
            if (wTheToken.type == W_TOKEN_SUB) {
                symType = W_SYM_SUB;
            } else if (wTheToken.type == W_TOKEN_FUNCTION) {
                symType = W_SYM_FUNCTION;
            } else {
                wErrorThrow( W_ERROR_SYNTAX, "Expected \"Sub\" or \"Function\", not \"%s\"",
                    wTheToken.text );
            }

            /* get the name */
            wLexToken();

            /* validate it */
            wSymbolUnused( wTheToken.text );

            /* inherit VIRTUAL if prior declaration was VIRTUAL or ABSTRACT */
            if (klass) {
                prior = wSymbolFindMethodChar( klass, wTheToken.text );
                if (prior != NULL) {
                    if (prior->flags & (W_SYM_ISVIRTUAL | W_SYM_ISABSTRACT)) {
                        flags &= W_SYM_ISVIRTUAL;
                    }
                }
            }

            /* create a symbol for it */
            if (wTheDebugOnFlag) {
                if (klass==NULL) {
                    wConsoleDebugf("defining \"%s\" as a routine\n", wTheToken.text );
                } else {
                    wConsoleDebugf("defining \"%s.%s\" as a method\n", klass->name, wTheToken.text );
                }
            }

            /* create a symbol for it */
            s = wSymbolNew( wTheToken.text, wTheCurrentScope, symType );

            /* set the flag */
            s->flags = flags;

            /* add method to class? */
            if (klass != NULL) {
                wGrowAppend( klass->method, s->index );
            }

            /* move to next token */
            wLexToken();

            /* scan for the opening paren */
            wParseExpect('(', "an opening \"(\"");

            /* not empty list? */
            s->args = 0;
            if (!wParseTokenIs(')')) {

                /* count the args */
                while (1) {
                    /* elipsis? */
                    if (wParseTokenIs(W_TOKEN_3DOTS)) {
                        /* end of list */
                        wLexToken();
                        s->varArgs = W_TRUE;
                        break;
    
                    } else {
                        /* move ahead */
                        wLexToken();

                        /* AS <datatype> */
                        if (wParseTokenIs(W_TOKEN_AS)) {
                            wParseSkip();
                            wParseSkip();
                        }

                        /* assign default value? */
                        if (wParseTokenIs(W_TOKEN_EQ)) {
                            /* skip the "=" sign */
                            wLexToken();
    
                            /* add to optional argument count */
                            s->optArgs++;
    
                            /* skip the expression */
                            wSourceSkipExpression();
    
                        /* should have been assigned? */
                        } else if (s->optArgs) {
                            wErrorThrow( W_ERROR_SYNTAX, "Expected an \"=\"" );
            
                        } else {
                            /* increment arg count */
                            s->args++;
                        }
    
                        /* exit if not a comma, otherwise skip */
                        if (wParseTokenIs(',')) {
                            wLexToken();
                            /* FIXME: should this allow an optional seperator? */
                        } else {
                            break;
                        }
                    } /* type of arg */
                }  /* while */
            } /* if */
            wParseExpect(')', "a closing \")\"");

        /* start of class? */
        } else if (wParseTokenIs(W_TOKEN_CLASS)
               || (wParseTokenIs(W_TOKEN_ABSTRACT) && klass == NULL)) {
	
            if (wParseTokenIs(W_TOKEN_ABSTRACT)) {
                flags = W_SYM_ISABSTRACT;
                wParseSkip();
            } else {
                flags = 0;
            }

            /* skip to name of class */
            wParseExpect(W_TOKEN_CLASS, "\"Class\"");       

            /* validate it */
            wSymbolUnused( wTheToken.text );

            /* create a symbol for it */
            if (wTheDebugOnFlag) {
                wConsoleDebugf("defining \"%s\" as a class\n", wTheToken.text );                
            }
            klass = wSymbolNew( wTheToken.text, wTheGlobalScope, W_SYM_USER_CLASS );
            klass->method = wGrowNew( 8 );
            klass->flags = flags;
            wTheClassScope = klass->index;
            wTheCurrentScope = wTheClassScope;
	    
            wParseSkip();

            /* Inherits? */
            if (wParseTokenIs(W_TOKEN_INHERITS)) {
                wParseSkip();

                /* must be a class */
                if (!wParseTokenIs(W_TOKEN_CLASS_NAME)) {
                    wErrorThrow( W_ERROR_SYNTAX, "Expected a class name, not \"%s\"",
                        wTheToken.text );
                }

                /* abstract classes can only inherit other abstract classes */
                if ((klass->flags & W_SYM_ISABSTRACT)
                && !(wTheToken.symbol->flags & W_SYM_ISABSTRACT)) {
                    wErrorThrow( W_ERROR_SYNTAX, "Abstract class %s can't inherit non-abstract class %s",
                        klass->name, wTheToken.symbol->name );
                }

                /* set the inherited class */
                inherits = wTheToken.symbol;
                klass->inherits = inherits->index;
        
                /* inherit the properties */
                klass->children = wGrowCopy( inherits->children );
        		
                wParseSkip();
            }

        /* end of class? */
        } else if (wParseTokenIs(W_TOKEN_END)) {

            /* read next word */
            wLexToken();
            if (wParseTokenIs(W_TOKEN_CLASS)) {

                /* make sure all inherited abstract methods are defined */
                wSymbolCheckAbstract( klass );

                klass = NULL;
                wTheClassScope = 0;
                wTheCurrentScope = wTheGlobalScope;
            }
        } /* token type */

    } /* while reading tokens */

    /* reset buffer position */
    wReadLine = 0;
    wLineBufferPos = W_BUFFER_EMPTY;
}
