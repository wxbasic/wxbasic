/*************************************************************
    Name:       builtin.c
	Purpose:    builtin routine for wxBasic
	Author:     David Cuny
	Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
	Licence:    LGPL
*************************************************************/


void wNotYet( char *name )
{
	wErrorThrow( W_ERROR_INTERNAL, "%s is not implemented yet", name );
}

/* returns absolute value of number */
void wBuiltinAbs()
{
	wNumber  n;
	n = wStackPopNumber();
	if (n < 0) {
		wStackPushNumber( -n );
	} else {
		wStackPushNumber( n );
	}
}

/* returns arccos of number */
void wBuiltinACos()
{
    /* get value */
    wNumber n = wStackPopNumber();

    /* check range */
    if (n > 1 || n < -1) {
        wErrorThrow( W_ERROR_MATH, "acos() range error" );
    }

    wStackPushNumber( acos( n ) );
}

/* returns bitwise 'and' of two numbers */
void wBuiltinAndBits()
{
	wStackPushNumber( (wNumber)((int)wStackPopNumber() & (int)wStackPopNumber()) );
}

/* append two items, returning the result */
void wBuiltinAppend()
{
    wVariant *result, *object1, *object2;
    
    /* place to store the result */
    wStackPushNothing();
    result = wStackPeek(0);
    
    /* value to append */
    object1 = wStackPeek(1);

    /* value to append to */
    object2 = wStackPeek(2);

    /* clone the object so it's unique */
    wVariantClone( result, object2 );
            
    /* append */
    wVariantAppend( result, object1 );
    
    /* swap position on stack */
    wStackSwap( 0,2 );

    /* drop top items */
    wStackDrop(2);

}

/* return number of args in caller */
void wBuiltinArgc()
{
    int argCount;
	wCall *call;

	/* get the call on the stack */
	call = (wCall*)wGrowGet( wTheCallStack, wTheCallStack->count );

// FIXME: check why I have this weird logic here...
//    /* number of args */
//    argCount = call->routine->args + call->routine->optArgs;
//    if (call->parmCount > argCount) {
//        argCount = call->parmCount;
//    }

	/* push the parameter count of that call */
    wStackPushNumber( call->parmCount );
}


/* copy arg onto stack */
void wBuiltinArgv()
{
    int index, minCount, argCount, childCount;
	wCall *call;

	/* get arg number */
	index = (int)wStackPopNumber();

	/* fetch the call on the call stack */
	call = (wCall*)wGrowGet( wTheCallStack, wTheCallStack->count );

    /* number of args */
    minCount = call->routine->args + call->routine->optArgs;
    if (call->parmCount < minCount) {
        argCount = minCount;
    } else {
        argCount = call->parmCount;
    }

	/* check range */
    if (index > argCount || index < 1) {
		wErrorThrow( W_ERROR_ARGS, "Argv: The routine %s only has %d args, not %d",
            call->routine->name, argCount, index );
	}

	/* optional arg? */
    if (index > minCount ) {
		/* optional args are placed after all the other locals */

		/* subtract the required fields */
        index -= minCount;

		/* how many locals? */
		if (call->routine->children == NULL) {
			childCount = 0;
		} else {
			childCount = call->routine->children->count;
		}

		/* offset from the end */
		index = childCount + index;
	}

	/* push that arg onto the stack */
	wStackPush( &(call->local[index-1]) );
}

/* get upper or lower bounds of array */
void wBuiltinArrayBound( int getUpper )
{
    int index, count;
    wVariant *variant;

    /* get the index number */
    index = (int)wStackPopNumber()-1;

    /* pop the array */
    variant = wStackPop();
    if (variant->dataType != W_TYPE_ARRAY) {
        wErrorThrow( W_ERROR_CONVERT, "Expected an Array, not a %s",
            wDataTypeName[variant->dataType] );
    }

    /* check number of indices */
    if (index < 0 || index > variant->value.array->indexCount) {
        wErrorThrow( W_ERROR_INDEX, "Array has %d indexes, not %d",
            variant->value.array->indexCount, index+1 );
    }

    /* which bound? */
    if (getUpper) {
        count = variant->value.array->upper[index];
    } else {
        count = variant->value.array->lower[index];
    }

	/* deref the object */
    wVariantDeref( variant );

    /* push the result */
    wStackPushNumber( count );
    
}


/* returns ascii value of first char in string */
void wBuiltinAsc()
{
	int         i;
	char        *string;
	wVariant    *src;

	/* get the string */
	src = wStackPopString();

    /* get the value */
    string = wStringChar( src );
	i = string[0];

	/* deref */
	wVariantDeref( src );

	/* push the first character in the string */
	wStackPushNumber( (wNumber)i );
}


/* returns arcsin of number */
void wBuiltinASin()
{
    /* get value */
    wNumber n = wStackPopNumber();

    /* check range */
    if (n > 1 || n < -1) {
        wErrorThrow( W_ERROR_MATH, "acos() range error" );
    }

    wStackPushNumber( asin( n ) );
}

/* returns arctan of number */
void wBuiltinATan()
{
	wStackPushNumber( atan( wStackPopNumber() ) );
}


/* return string corresponding for a number in a given base */
void wBuiltinBase()
{
    int     base, value, at, digit, isSigned;
    char    *buffer = (char *)wMalloc(128);

    /* base */
    base = (int)wStackPopNumber();

    /* value to convert */
    value = (int)wStackPopNumber();

    /* check base */
    if (base < 2) {
        wErrorThrow( W_ERROR_MATH, "Bad base of %d", base );
    }

    /* position in buffer */
    at = 127;

    /* add string terminator */
    buffer[at--] = '\0';

    /* signed? */
    if (value < 0) {
        /* flag as signed */
        isSigned = 1;

        /* negate */
        value = -value;
    } else {
        /* not signed */
        isSigned = 0;
    }

    /* handle zero */
    if (value == 0) {
        buffer[at--] = '0';
    }

    /* convert digits */
    while (value > 0) {

        /* don't overflow the buffer */
        if (at < 0) {
            wErrorThrow( W_ERROR_MATH, "Too many digits error" );
        }

        /* get a digit */
        digit = value % base;
        value /= base;

        /* convert digit */
        if (digit > 9) {
            /* use alpha */
            digit += 'a' - 9;
        } else {
            /* use numeric */
            digit += '0';
        }

        /* add to buffer */
        buffer[at--] = digit;
    }

    /* signed? */
    if (isSigned) {
        buffer[at--] = '-';
    }

    /* push the result */
    wStackPushChar( buffer+at+1, 0 );
	wFree( buffer );
}


/* return string corresponding to binary representation of number */
void wBuiltinBin()
{
    int value;

    /* push base 2 onto stack */
    wStackPushNumber( 2 );

    /* call builting wBuiltinBase to convert */
    wBuiltinBase();
}


/* change directory */
void wBuiltinChDir()
{
	wNotYet("ChDir");
}


/* return string corresponding to ascii key value */
void wBuiltinChr()
{
	char        *buffer;
	wVariant    *variant;

	buffer = (char *)wMalloc(sizeof(char)*2);
	buffer[0] = (char)wStackPopNumber();
	buffer[1] = '\0';

    wStackPushChar( buffer, 0 );
	wFree( buffer );
}

/* return a clone of an object */
void wBuiltinClone()
{
    wVariant *src, *dst;

    /* allocate spot for result on stack */
    dst = wStackPushNothing();
    
    /* clone the source */
    wVariantClone( dst, wStackPeek(1) );
    
    /* swap and drop the source */
    wStackSwap(0,1);
    wStackDrop(1);
}


/* returns requested arg from command line */
void wBuiltinCommand()
{
    int     argNum;

    /* no args? */
    if (wTheCall->parmCount==0) {
        /* return count of args */
        wStackPushNumber( wTheArgc );

    } else {

        /* get arg number */
        argNum = (int)wStackPopNumber();
        if (argNum < 0 || argNum > wTheArgc) {
            /* out of range */
            wStackPushChar( "", W_TRUE );
    
        } else {
            /* return copy of arg */
            wStackPushChar( wTheArgv[ argNum-1 ], W_TRUE );
        }
    }
}

/* concatenate two strings */
void wBuiltinConcat()
{    

	wVariant    *src, *dst;

	src = wStackPopString();

	dst = wStackPeek( 0 );
	wVariantCoerce( dst, W_TYPE_STRING );

	/* concat */
	wStringConcat( dst, src );

	/* deref source */
	wVariantDeref( src );
}


/* connect a routine to a callback */
void wBuiltinConnect()
{
#ifdef __WXWIN__
    int     id, eventType, useId;
    char    *name, *lowerCaseName;
    void    *handle;
	wSymbol  *routine;

    /* get routine name */
    name = wStackPopChar();

    /* set it to lower case */
    lowerCaseName = wCharCopyToLower( name );

	/* look it up */
    routine = wSymbolFind( lowerCaseName, wTheGlobalScope );
	if (routine == NULL) {
        wErrorThrow( W_ERROR_NOSUCH, "Connect: Can't find Sub or Function %s",
            lowerCaseName );
	}
    wFree( lowerCaseName );

	/* function or a sub? */
    if (routine->type != W_SYM_SUB &&
        routine->type != W_SYM_FUNCTION ) {
            wErrorThrow( W_ERROR_NOSUCH, "Connect: %s is not a Function or a Sub",
                routine->name );
	}

    /* get the event type */
	eventType = (int)wStackPopNumber();

	/* optional identifier */
    if (wTheCall->parmCount==4) {
		id = (int)wStackPopNumber();
		useId = W_TRUE;

	} else {
		id = -1;
		useId = FALSE;
	}

    /* get the object sending the event */
    handle = wStackPopObjectPtr( NULL );

    /* connect */
	wConnect( id, useId, handle, eventType, routine );

    /* dereference the args */
    wWrapDerefArgs();
   
#else
	wErrorThrow( W_ERROR_INTERNAL, "Connect() is not available in console mode");
#endif
}


/* returns cos of number */
void wBuiltinCos()
{
	wStackPushNumber( cos( wStackPopNumber() ) );
}


/* return count of a collection */
void wBuiltinCount()
{
    int result;
    wVariant *src;

    /* get source object */
    src = wStackPeek(0);
    
    /* count it */
    result = wVariantCount( src );

    /* drop the source */
    wStackDrop(1);
    
    wStackPushNumber( result );
}


/* returns date in MM-DD-YYYY format */
void wBuiltinDate()
{
    char *buffer;

    /* format the current time */
    buffer = wDateTimeFormat( "%m:%d:%Y", time(NULL) );

	/* push onto stack as string */
    wStackPushChar( buffer, W_FALSE );
	wFree( buffer );
}


/* returns day number of time */
void wBuiltinDay()
{
    wDateTimePush( 'd', wStackPopDateTime() );
}


/* returns next file of FileSpec */
void wBuiltinDir()
{
	wNotYet("Dir");
}

/* returns true if directory exists */
void wBuiltinDirExists()
{
	wNotYet("DirExists");
}

/* disconnect a routine to a callback */
void wBuiltinDisconnect()
{
#ifdef __WXWIN__
    int     id, eventType, useId;
    void    *handle;

    /* get the event type */
	eventType = (int)wStackPopNumber();

	/* optional identifier */
    if (wTheCall->parmCount==3) {
		id = (int)wStackPopNumber();
		useId = W_TRUE;

	} else {
		id = -1;
		useId = FALSE;
	}

    /* get the object sending the event */
    handle = wStackPopObjectPtr( NULL );

    /* connect */
    wDisconnect( id, useId, handle, eventType );

    /* dereference the args */
    wWrapDerefArgs();
   
#else
    wErrorThrow( W_ERROR_INTERNAL, "Disconnect() is not available in console mode");
#endif
}


/* returns nonzero if Eof */
void wBuiltinEof()
{
	wStackPushNumber( (wNumber)wFileEof( (int)wStackPopNumber() ) );
}

/* returns exponential function */
void wBuiltinExp()
{
    /* call exp with error checking */
    wStackPushNumberFromRoutine( exp( wStackPopNumber() ) , "Exp" );
}

/* c style fclose */
void wBuiltinFClose()
{
	wFileClose( (int)wStackPopNumber() );
}


/* c style fgets */
void wBuiltinFGets()
{
	int     handle;

	/* get the handle */
	handle = (int)wStackPopNumber();

	/* get a buffer from wFileLineInput */
	wFileLineInput( handle );

    /* error? */
    if (wTheFileBuffer == NULL) {
        /* push an empty string onto the stack */        
        wStringNew( wStackPushNothing(), NULL, 0 );
    } else {
        /* push the string onto the stack */
        wStackPushChar( wTheFileBuffer, 0 );
    }
}


/* c style fopen */
void wBuiltinFOpen()
{
	int         result;
	wVariant    *name, *mode;
	char        *fname, *fmode;

	mode = wStackPopString();
	name = wStackPopString();

	fname = wStringChar(name);
	fmode = wStringChar(mode);

	result = wFileOpenCStyle( fname, fmode );

	wVariantDeref( mode );
	wVariantDeref( name );

	wStackPushNumber( result );
	
}


/* c style fputs */
void wBuiltinFPuts()
{
	int         handle;
	char        *text;
	wVariant    *variant;

	/* FIXME: popstring doesn't need to be done to numeric types */
	variant = wStackPopString();
	text = wStringChar( variant );
	handle = (int)wStackPopNumber();
	wFilePrintString( handle, text );
	wVariantDeref( variant );
}


/* returns true if the file exists */
void wBuiltinFileExists()
{
	int         result;
	char        *name;
	wVariant    *variant;

	variant = wStackPopString();
	name = wStringChar(variant);
	result = wFileExists(name);
	wVariantDeref( variant );
	wStackPushNumber( result );
	
}

/* truncate fractional number, rounding down towards zero */
void wBuiltinFix()
{
	wStackPushNumber( floor( wStackPopNumber() ) );
}

/* returns formatted string with embedded args */
void wBuiltinFormat()
{
    int i, at, argCount, argNum, formatLen, srcLen, bufferLen;
    char letter, digit, *format, *buffer, *src;
    wVariant *vFormat, *arg;

    /* get the count of parameters */
    argCount = wTheCall->parmCount;
    
    /* format string is on the bottom */
    vFormat = wStackPeek(argCount-1);
    wVariantCoerce( vFormat, W_TYPE_STRING );

    /* format string values */
    format = &(vFormat->value.string->text);
    formatLen = vFormat->value.string->length+1;

    /* create a buffer */
    buffer = (char *)wMalloc( W_INBUFFER_MAX );

    /* scan through the string */
    at = 0;
    for ( i = 0; i < formatLen; i++ ) {

        /* range check */
        if (at >= W_INBUFFER_MAX || i > formatLen) {
            break;
        }

        /* get a char from the string */
        letter = format[i];

        /* not part of arg? */
        if (letter != '{') {
            /* add to the buffer */
            buffer[at++] = letter;

        } else {
            /* get the digit from the string */
            digit = format[++i];
            if (i > formatLen) {
                break;
            }

            /* get closing } */
            letter = format[++i];
            if (i > formatLen) {
                break;
            } else if (letter != '}') {
                wFree( buffer );
                wErrorThrow( W_ERROR_CONVERT, "Expected \"}\", not \"%c\" in format string at position %d", letter, i+1 );
                break;
            }


            /* ensure it's a digit */
            if (digit < '0' || digit > '9') {
                wFree( buffer );
                wErrorThrow( W_ERROR_CONVERT, "Non-digit \"%c\" in format string at position %d", digit, i+1 );
                break;
            }

            /* convert digit to an index */
            argNum = (argCount - 2) - ((int)digit - (int)'0');

            /* check the range */
            if (argNum < argCount) {
                /* convert arg to a string */
                arg = wStackPeek( argNum );
                wVariantCoerce( arg, W_TYPE_STRING );

                /* string data */
                src = &(arg->value.string->text);
                srcLen = arg->value.string->length;

                /* check the length */
                if (at + srcLen < W_INBUFFER_MAX ) {
                    /* copy to buffer */
                    wMemMove( buffer+at, src, srcLen, "wBuiltinFormat" );
                } else {
                    /* do nothing; error will be caught at top of loop */
                }
                at += srcLen;
            }
        }
    }

    /* free the buffer */
    wFree( buffer );

    /* gone too far? */
    if (at >= W_INBUFFER_MAX) {
        wErrorThrow( W_ERROR_CONVERT, "Format buffer too large (%d chars)", at );
    } else if  (i > formatLen) {
        wErrorThrow( W_ERROR_CONVERT, "Error in format string at position %d ", i );
    }

    /* drop the args from the stack */
    wStackDrop( argCount );

}

/* return fractional portion of number */
void wBuiltinFrac()
{
	wNumber  n;
	n = wStackPopNumber();
	n -= floor(n);
	wStackPushNumber(n);
}

/* return the handle of the next free file */
void wBuiltinFreeFile()
{
	wStackPushNumber(wFileNextHandle());
}


/* wBuiltinGetWxApp: returns index of to wxApp */
void wBuiltinGetWxApp()
{
	/* FIXME */
	wNotYet("GetWxApp");
	// wPushPtrHandle( wAppIndex );
}

/* wBuiltinGetWxHandle: get handle of wrapped wxWindows id */
void wBuiltinGetWxHandle()
{
// FIXME!
// #ifdef __WXWIN__
#if 0
	/* find handle of id and push onto stack */
	wFindHandle( wStackPopNumber() );
#else
	wErrorThrow( W_ERROR_INTERNAL, "GetWxHandle() is not available in console mode");
#endif
}

/* returns true if key is in table */
void wBuiltinHasKey()
{
    int result;
    wVariant *table, *key;

    key = wStackPop();
    table = wStackPop();

    if (table->dataType != W_TYPE_TABLE) {
        wErrorThrow( W_ERROR_CONVERT, "Expected a table, not a %s",
            wDataTypeName[table->dataType] );
    }

    /* call the routine and get the result */
    result = wTableHasKey( table, key );

    /* deref the args */
    wVariantDeref( key );
    wVariantDeref( table );

    /* return the result */
    wStackPushNumber( result );
}


/* returns hexidecimal representation of number */
void wBuiltinHex()
{
	int     i;
	char    *buffer = (char *)wMalloc(16);

	i = (int)wStackPopNumber();
	sprintf( buffer, "%x", i);
    wStackPushChar( buffer, 0 );
	wFree( buffer );
}

/* returns hour number portion of time */
void wBuiltinHour()
{
    /* pop time, push hour portion */
    wDateTimePush( 'h', wStackPopDateTime() );
}

/* return number of indexes in array */
void wBuiltinIndexes()
{
    int count;
    wVariant *variant;

    /* pop the array */
    variant = wStackPop();
    if (variant->dataType != W_TYPE_ARRAY) {
        wErrorThrow( W_ERROR_CONVERT, "Expected an Array, not a %s",
            wDataTypeName[variant->dataType] );
    }

    /* get the count */
    count = variant->value.array->indexCount;

	/* deref the object */
    wVariantDeref( variant );

    /* push the result */
    wStackPushNumber( count );
}

/* insert text into a string */
void wBuiltinInsert()
{
    wVariant *src, *key, *value, *theCopy;

    /* get args */
    value = wStackPop();
    key = wStackPop();
    src = wStackPop();

    /* create a copy of the source */
    theCopy = (wVariant *)wMalloc( sizeof( wVariant ) );
    theCopy->dataType = W_TYPE_NOTHING;
    wVariantClone( theCopy, src );

    /* do the insert */
    wVariantInsert( theCopy, key, value );

    /* deref args */
    wVariantDeref( src );
    wVariantDeref( key );
    wVariantDeref( value );

    /* move the result to the stack */    
    wVariantMove( wStackPushNothing(), theCopy );

    /* free the copy */
    wFree( theCopy );
}


/* insert item into a collection */
void wBuiltinInsertAt()
{
	/* FIXME */
    wNotYet("InsertAt");
}

/* returns true if item on stack was Nothing */
void wBuiltinIsNothing()
{
    int         result;
    wVariant    *v;

    /* get the variant */
    v = wStackPop();

    /* is it Nothing? */
    result = (v->dataType == W_TYPE_NOTHING);

    /* push result */
    wStackPushNumber( result );
}


/* returns true if item on stack was numeric */
void wBuiltinIsNumeric()
{
    int         dataType;
    wVariant    *v;

    /* get the variant */
    v = wStackPop();

    /* is the Datatype numeric? */
    wStackPushNumber( (wNumber)wTheHandler[v->dataType]->isNumeric );
}


/* returns position in source that target was found */
void wBuiltinInstr()
{
	wVariant    *vFind, *vSearch;
	int     start, result;    

	/* required args */
	vFind = wStackPopString();
	vSearch = wStackPopString();

	/* optional starting position */
	if (wTheCall->parmCount == 3) {
		start = (int)wStackPopNumber();
		if (start < 0) {
			start = 0;
		}

	} else {
		start = 0;
	}

	/* perform the search */
	result = wStringIndex( vSearch, vFind, start );

	/* deref the strings */
	wVariantDeref( vFind );
	wVariantDeref( vSearch );

	/* save the result */
	wStackPushNumber( result );

}

/* convert to 32 bit integer, truncating decimals */
void wBuiltinInt()
{
	wStackPushNumber( (int)wStackPopNumber() );
}

/* delete filename */
void wBuiltinKill()
{
	wVariant    *fileName;

	fileName = wStackPopString();
	remove( wStringChar(fileName) );
	wVariantDeref( fileName );
}

/* convert string to lower case */
void wBuiltinLCase()
{
	wVariant    *variant;

	/* get the string */
	variant = wStackPeek( 0 );
	wVariantCoerce( variant, W_TYPE_STRING );

	/* convert */
	wStringToLower( variant );
}

/* returns leftmost chars in string */
void wBuiltinLeft()
{
	int         pos;
	wVariant    *src, *dst;

	/* create a scratch variable */
	dst = (wVariant *)wMalloc( sizeof( wVariant ) );

	/* get the args */
	pos = (int)wStackPopNumber();
	src = wStackPeek( 0 );
	wVariantCoerce( src, W_TYPE_STRING );

	/* create the substring */
    dst->dataType = W_TYPE_NOTHING;
	wStringSubstr( dst, src, 1, pos );

	/* need to replace with a new string? */
    if (src->value.string != dst->value.string) {
        wStackDrop( 1 );
		wStackPush( dst );
	}
	wVariantDeref( dst );
	wFree( dst );
}

/* return length of string */
void wBuiltinLen()
{
	int         len;
	wVariant    *variant;

    /* what type of value? */
	variant = wStackPop();
    switch (variant->dataType) {
	case W_TYPE_STRING:
        len = variant->value.string->length;
		break;

	case W_TYPE_TABLE:
        len = variant->value.table->count;
		break;

	case W_TYPE_LIST:
        len = variant->value.list->count;
		break;

	default:
		len = -1;
	}

	/* deref the object */
	wVariantDeref( variant );

	/* push the length onto the stack */
    if (len == -1) {
		/* FIXME: should this throw an exception? */
		/* leave as undefined */
        wStackPushNothing();
	} else {
		/* push length onto stack */
		wStackPushNumber( (wNumber)len );
	}

}

/* returns position in file */
void wBuiltinLoc()
{
	wStackPushNumber( wFilePosition( (int)wStackPopNumber() ) );
}


/* returns length of file */
void wBuiltinLof()
{
	wStackPushNumber( wFileSize( (int)wStackPopNumber() ) );
}


/* returns natural log of expression */
void wBuiltinLog()
{
    /* call log with error checking */
    wStackPushNumberFromRoutine( log( wStackPopNumber() ) , "Log" );
}

/* returns lower bound of array */
void wBuiltinLBound()
{
    wBuiltinArrayBound(0);
}

/* returns string with left whitespace removed */
void wBuiltinLTrim()
{
	wVariant    *variant;

    /* get value and coerce into a string */
	variant = wStackPeek( 0 );
	wVariantCoerce( variant, W_TYPE_STRING );

	/* trim it */
	wStringLTrim( variant );
}


/* returns string with chars 1..n from source */
void wBuiltinMid()
{
	int         len, start;
	wVariant    *dst, *src;

	/* length is optional */
	if (wTheCall->parmCount == 3) {
		len = (int)wStackPopNumber();
	} else {
		/* keep compiler happy */
		len = 0;
	}

	/* required args */
	start = (int)wStackPopNumber();
	src = wStackPeek( 0 );
	wVariantCoerce( src, W_TYPE_STRING );

	/* if no length, use length of string */
	if (wTheCall->parmCount != 3) {
        len = src->value.string->length;
	}

	/* negative start positions return empty string */
	if (start < 1) {
		/* drop the source string */
        wStackDrop( 1 );

		/* push an empty string onto the stack */
        dst = wStackPushNothing();
		wStringNew( dst, NULL, 0 );

	} else {
		/* create a scratch variable */
		dst = (wVariant *)wMalloc( sizeof( wVariant ) );

		/* get the substring */
        dst->dataType = W_TYPE_NOTHING;
		wStringSubstr( dst, src, start, start+len-1 );

		/* drop the source string */
        wStackDrop( 1 );

		/* push the new string, and deref */
		wStackPush( dst );
		wVariantDeref( dst );
		wFree( dst );
	}
}

/* returns minute number portion of time */
void wBuiltinMinute()
{
    /* pop time, push minute portion */
    wDateTimePush( 'n', wStackPopDateTime() );
}


/* create a new directory */
void wBuiltinMkDir()
{
	wNotYet("MkDir");
}

/* returns month number portion of time */
void wBuiltinMonth()
{
    wDateTimePush( 'm', wStackPopDateTime() );
}

/* returns month name portion of time */
void wBuiltinMonthName()
{
    wDateTimePush( 'M', wStackPopDateTime() );
}

/* returns bitwise 'not' of number */
void wBuiltinNotBits()
{
	wStackPushNumber( (wNumber)(~(int)wStackPopNumber()) );
}


/* return date/time */
void wBuiltinNow()
{
    wVariant    *v;

    /* copy to stack */
    v = wStackPushNothing();
    v->dataType = W_TYPE_DATETIME;
    v->value.time = time(NULL);
}


/* return string corresponding to octal representation of number */
void wBuiltinOct()
{
	int     i;
	char    *buffer = (char *)wMalloc(16);

	i = (int)wStackPopNumber();
    sprintf( buffer, "%o", i);
    wStackPushChar( buffer, 0 );
	wFree( buffer );
}


/* returns bitwise 'or' of two numbers */
void wBuiltinOrBits()
{
	wStackPushNumber( (wNumber)((int)wStackPopNumber() | (int)wStackPopNumber()) );
}


/* prepend two items, returning the result */
void wBuiltinPrepend()
{
    wVariant *result, *object1, *object2;
    
    /* place to store the result */
    wStackPushNothing();
    result = wStackPeek(0);
    
    /* value to append */
    object1 = wStackPeek(1);

    /* value to append to */
    object2 = wStackPeek(2);

    /* clone the object so it's unique */
    wVariantClone( result, object2 );
            
    /* append */
    wVariantPrepend( result, object1 );
    
    /* swap position on stack */
    wStackSwap( 0,2 );

    /* drop top items */
    wStackDrop(2);

}


/* sort an array */
void wBuiltinQuickSort()
{
	wNotYet("QuickSort");
}

/* reseed the random number generator */
void wBuiltinRandomize()
{
	int seed;
	
	/* optional argument? */
	if (wTheCall->parmCount==1) {
		seed = (int)wStackPopNumber();
	} else {
		seed = time(NULL);
	}
	srand( seed );
	wStackPushNumber(0);
}

/* return a byte from the file */
void wBuiltinReadByte()
{
	wStackPushNumber( (wNumber)wFileReadByte( (char)wStackPopNumber() ) );
}

/* rename file */
void wBuiltinRename()
{
	wVariant    *vOldName, *vNewName;

	vNewName = wStackPopString();
	vOldName = wStackPopString();

	rename( wStringChar(vOldName), wStringChar(vNewName) );

	wVariantDeref( vOldName );
	wVariantDeref( vNewName );
}

/* returns string m chars wide with n in it */
void wBuiltinRepeat()
{
	int            reps, ascii;
	char        *buffer;
	wVariant    *src, *dst;
	
    /* first value item might be string, or number */
	src = wStackPeek( 0 );
	
    if (src->dataType == W_TYPE_NUMBER) {
		ascii = (int)wStackPopNumber();
		reps = (int)wStackPopNumber();
		
		/* create a buffer */
		buffer = (char *)wMalloc( reps + 1 );
		
		/* use memset to fill it with the requested char */
		memset( buffer, reps, ascii );

		/* push copy of buffer onto stack */
        wStackPushChar( buffer, 0 );
		wFree( buffer );
		
	} else {
		/* create a scratch variable */
		dst = (wVariant *)wMalloc( sizeof( wVariant ) );

		src = wStackPopString();
		reps = (int)wStackPopNumber();
		wStringRepeat( dst, src, reps );

		/* deref the source string */
		wVariantDeref( src );

		/* push the new string */
		wStackPush( dst );
		wVariantDeref( dst );
		wFree( dst );
	}
}

/* replace string from source with replace starting at index */
void wBuiltinReplace()
{
	int         start;
	wVariant    *vReplacement, *vReplace, *vSource, *vNewString;

	/* create a scratch variable */
	vNewString = (wVariant *)wMalloc( sizeof( wVariant ) );

	/* optional start position */
	if (wTheCall->parmCount == 4) {
			start = (int)wStackPopNumber();
	} else {
			start = 1;
	}

	/* get the args */
	vReplacement = wStackPopString();
	vReplace = wStackPopString();
	vSource = wStackPeek( 0 );

	/* do the replacement */
    vNewString->dataType = W_TYPE_NOTHING;
	wStringReplace( vNewString, vSource, vReplace, vReplacement, start );
	
	/* deref the match strings */
	wVariantDeref( vReplacement );
	wVariantDeref( vReplace );

	/* drop the source string */
    wStackDrop( 1 );

	/* push the result */
	wStackPush( vNewString );
	wVariantDeref( vNewString );
	wFree( vNewString );

}


/* reverse a string */
void wBuiltinReverse()
{
	wVariant    *src, *dst;

	/* create a scratch variable */
	dst = (wVariant *)wMalloc( sizeof( wVariant ) );

	src = wStackPopString();
    dst->dataType = W_TYPE_NOTHING;
	wStringReverse( dst, src );
	wVariantDeref( src );
	wStackPush( dst );
	wVariantDeref( dst );
	wFree( dst );
}

/* returns rightmost chars in string */
void wBuiltinRight()
{
	int         pos, len, newLen;
	wVariant    *src, *dst;

	/* create a scratch variable */
	dst = (wVariant *)wMalloc( sizeof( wVariant ) );

	/* get the position */
	pos = (int)wStackPopNumber();

	/* get the string, keeping it on the stack */
	src = wStackPeek( 0 );
	wVariantCoerce( src, W_TYPE_STRING );
    len = src->value.string->length;

	/* destination */
    dst->dataType = W_TYPE_NOTHING;

	/* get the substring */
	wStringSubstr( dst, src, len-pos+1, len );

	/* drop the source string */
    wStackDrop( 1 );

	/* push the new string */
	wStackPush( dst );
	wVariantDeref( dst );
	wFree( dst );
}


/* reverse Instr function, search from end to start */
void wBuiltinRInstr()
{
	wVariant    *lookIn, *lookFor;
	int         start, searchLen, result;

	lookFor = wStackPopString();
	lookIn = wStackPopString();
    searchLen = lookIn->value.string->length;

	/* optional starting position */
	if (wTheCall->parmCount == 3) {
		start = (int)wStackPopNumber();
		if (start > searchLen ) {
			start = searchLen;
		}
	} else {
		start = searchLen;
	}

	/* search the string */
	result = wStringRIndex( lookIn, lookFor, start );

	/* deref the strings */
	wVariantDeref( lookFor );
	wVariantDeref( lookIn );

	wStackPushNumber( result );
}

/* remove directory */
void wBuiltinRmDir()
{
	wNotYet("RmDir");
}

/* return a random number */
void wBuiltinRnd()
{
	int upper, result;

	result = rand();
	if (wTheCall->parmCount == 1) {
		upper = (int)wStackPopNumber();
		result = (result % (upper))+1;
	}
	wStackPushNumber( (wNumber)result );
}

/* round to nearest integer */
void wBuiltinRound()
{
	wNumber n1, n2;
	n1 = wStackPopNumber();
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
	wStackPushNumber( n2 );
}


/* right trim string */
void wBuiltinRTrim()
{
	wVariant *variant;
	
	variant = wStackPeek( 0 );
	wVariantCoerce( variant, W_TYPE_STRING );
	wStringRTrim( variant );
}

/* run command on new thread */
void wBuiltinRun()
{
	wNotYet("Run");
}

/* returns seconds number portion of time */
void wBuiltinSecond()
{
    wDateTimePush( 's', wStackPopDateTime() );
}

/* seek file position/return current file position */
void wBuiltinSeek()
{
	int     file, pos;

	/* which version? */
	if (wTheCall->parmCount==2) {
		/* seek to position */
		pos = (int)wStackPopNumber();
		file = (int)wStackPopNumber();
		wStackPushNumber( wFileSeek( file, pos ));

	} else {
		/* return position in file */
		file = (int)wStackPopNumber();
		wStackPushNumber( (wNumber)wFilePosition( file ) );
	}
}

/* returns sign of numeric expression */
void wBuiltinSgn()
{
	wNumber  n;
	n = wStackPopNumber();
	if (n < 0) {
		wStackPushNumber(-1);
	} else if (n > 0) {
		wStackPushNumber(1);
	} else {
		wStackPushNumber(0);
	}
}

/* execute command, wait until finished */
void wBuiltinShell()
{
	char    *text;
	wVariant *variant;
	
	variant = wStackPopString();
	system( wStringChar( variant ) );
	wVariantDeref( variant );    
}

/* returns sine of given angle in radians */
void wBuiltinSin()
{
	wStackPushNumber( sin( wStackPopNumber() ) );
}


/* return slice from a collection */
void wBuiltinSlice()
{
    int startOf, endOf;
    wVariant *dst, *src;


    /* get args */
    endOf = (int)wStackPopNumber();
    startOf = (int)wStackPopNumber();
    src = wStackPop();

    /* create a holder for the result */
    dst = (wVariant *)wMalloc( sizeof( wVariant ) );
    dst->dataType = W_TYPE_NOTHING;

    /* do the slice */
    wVariantSlice( dst, src, startOf, endOf );

    /* deref args */
    wVariantDeref( src );

    /* move the result to the stack */    
    wVariantMove( wStackPushNothing(), dst );

    /* free the destination */
    wFree( dst );
}


/* return string with n spaces in it */
void wBuiltinSpace()
{
	char    *string;
	int     n;
	n = (int)wStackPopNumber();
	if (n<0) {
		n = 0;
	}
	string = (char *)wMalloc((unsigned int)n+1);
	memset(string,' ',n);
	string[n] = '\0';
    wStackPushChar(string, 0);
	wFree( string );
}

#ifdef __SQLITE__

/* handle callbacks from sqlite3_exec() */
static int sqlCallback(void *notUsed, int argc, char **argv, char **azColName)
{
    int i;
    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

/* open a table */
void wBuiltinSqlClose()
{
    /* is a table open? */
    if (wSqlDb) {
        sqlite3_close(wSqlDb);
    }
}


/* open a table */
void wBuiltinSqlExec()
{
    int result;
    char *errorMessage;
    wVariant *command;

    /* make sure a db is open */
    if (!wSqlDb) {
        /* throw an error */
        wErrorThrow( W_ERROR_SQL, "No database is open" );
    }

	/* get the string */
    command = wStackPopString();

    /* call execute, which will trigger the callback */
    result = sqlite3_exec( wSqlDb, command, sqlCallback, 0, &errorMessage );

	/* deref */
    wVariantDeref( command );

    /* check for error */
    if ( result != SQLITE_OK ) {
        /* throw an error */
        wErrorThrow( W_ERROR_SQL, "SQL error: %s", errorMessage );
    }

}


/* open a table */
void wBuiltinSqlOpen()
{
    int result;
    wVariant *tableName;
    char *errorMessage;

	/* get the string */
    tableName = wStackPopString();

    /* try opening the table */
    result = sqlite3_open( wStringChar( tableName ), &wSqlDb );

	/* deref */
    wVariantDeref( tableName );

    /* failed? */
    if ( result ) {
        /* copy error message */
        errorMessage = wCharCopy( sqlite3_errmsg(wSqlDb) );

        /* close the file */
        sqlite3_close(wSqlDb);

        /* set the handle to null */
        wSqlDb = NULL;

        /* throw an error */
        wErrorThrow( W_ERROR_SQL, "Can't open database: %s", errorMessage );

        /* won't return here, but cleanup anyway */
        wFree( errorMessage );
    }
}

#endif


/* return square root - make sure it's non-negative */
void wBuiltinSqr()
{
    /* call sqrt with error checking */
    wStackPushNumberFromRoutine( sqrt( wStackPopNumber() ) , "Sqr" );
}

/* return string representation of the value */
void wBuiltinStr()
{
	/* coerce value to a string */
	wVariantCoerce( wStackPeek( 0 ), W_TYPE_STRING );
}

/* converts a floating point or number value to a string */
void wBuiltinStrF()
{
	/* coerce value to a string */
	wVariantCoerce( wStackPeek( 0 ), W_TYPE_STRING );
}

/* returns substring from source */
void wBuiltinSubStr()
{
	int         start, end;
	wVariant    *dst, *src;

	/* required args */
	end = (int)wStackPopNumber();
	start = (int)wStackPopNumber();

    /* swap positions with top of stack */
    dst = wStackPushNothing();
    src = wStackPeek( 1 );

    /* coerce to string */
	wVariantCoerce( src, W_TYPE_STRING );

    /* get the substring */
	wStringSubstr( dst, src, start, end );

	/* swap and drop the source string */
	wStackSwap( 0, 1 );
    wStackDrop( 1 );

}



/* returns number of occurances of matchstring */
void wBuiltinTally()
{
    int         start, result;
	wVariant    *src, *sub;    

	/* get the args */
	sub = wStackPopString();
	src = wStackPopString();
	
	/* optional start */
	if (wTheCall->parmCount == 3) {
		start = (int)wStackPopNumber();
	} else {
		start = 1;
	}

    /* call the tally routine */
    result = wStringTally( src, sub, start );
	
    /* dereference items on stack */
	wVariantDeref( src );
	wVariantDeref( sub );

    /* push the result */
    wStackPushNumber( result );
}

/* return tangent of given angle in radians */
void wBuiltinTan()
{
	wStackPushNumber( tan( wStackPopNumber() ) );
}

/* returns current timer value */
void wBuiltinTicks()
{
	wStackPushNumber( clock() );
}


/* returns string with whitespace removed on both sides */
void wBuiltinTrim()
{
	wVariant    *variant;

    /* get value and coerce into a string */
	variant = wStackPeek( 0 );
	wVariantCoerce( variant, W_TYPE_STRING );

	/* trim it */
	wStringLTrim( variant );
    wStringRTrim( variant );
}


/* return time in HH:MM:SS format */
void wBuiltinTime()
{
	time_t      t;
	struct tm   *tmp;
	char        *buffer = (char *)wMalloc(9);

	/* get time */
	t = time(NULL);     
	tmp = localtime(&t);

	sprintf( buffer, "%02d:%02d:%02d",
		tmp->tm_hour, tmp->tm_min, tmp->tm_sec );

    wStackPushChar( buffer, 0 );
	wFree( buffer );
}

/* convert string to a time */
void wBuiltinTimeValue()
{
    wVariant *v;
    
    /* look at value on stack */
    v = wStackPeek(0);

    /* coerce it to a datetime */
    wVariantCoerce( v, W_TYPE_DATETIME );
}

/* turn trace on and off */
void wBuiltinTrace()
{
    /* get the parameter */
    int parm = (int)wStackPopNumber();

    /* set the flags */
    wTheTraceOnFlag = parm;
    wTheTraceGotoNextBreak = !parm;
    
}


/* returns string with datatype */
void wBuiltinTypeOf()
{
	int         type;
    char        *typeName;
	wVariant    *variant;

	/* get the variant  from the stack */
	variant = wStackPop();

	/* get the type, and free the variant */
    type = variant->dataType;
	wVariantDeref( variant );

    /* push the type name, flag as "raw" */
    wStackPushChar( wDataTypeName[ type ], W_TRUE );
}



void wBuiltinUBound()
{
    wBuiltinArrayBound(1);
}


/* convert string to upper case */
void wBuiltinUCase()
{
	wVariant    *variant;

	/* get the string */
	variant = wStackPeek( 0 );
	wVariantCoerce( variant, W_TYPE_STRING );

	/* convert */
	wStringToUpper( variant );
}

/* returns closest numeric representation of number */
void wBuiltinVal()
{
	/* coerce the value to a number */
	wVariantCoerce( wStackPeek( 0 ), W_TYPE_NUMBER );
}

/* returns weekday number portion of time */
void wBuiltinWeekday()
{
    /* pop time, push weekday number portion */
    wDateTimePush( 'w', wStackPopDateTime() );
}

/* returns weekday name portion of time */
void wBuiltinWeekdayName()
{
    /* pop time, push weekday name portion */
    wDateTimePush( 'W', wStackPopDateTime() );
}


/* return a byte from the file */
void wBuiltinWriteByte()
{
	char    c;
	int     fileNum;

	c = (char)wStackPopNumber();
	fileNum = (int)wStackPopNumber();
	wFileWriteByte( fileNum, c );
	wStackPushNumber( 0 );
}

/* returns bitwise 'xor' of two numbers */
void wBuiltinXorBits()
{
	wStackPushNumber( (wNumber)((int)wStackPopNumber() ^ (int)wStackPopNumber()) );
}


/* returns year number portion of time */
void wBuiltinYear()
{
    /* pop time, push year number portion */
    wDateTimePush( 'y', wStackPopDateTime() );
}

/* add a builtin to the dictionary */
wSymbol *wBuiltinNew( char *name, void (*routine)(void), int args, int optArgs )
{
	wSymbol  *s;    
	s = wSymbolFind( name, wTheGlobalScope );
	if (s==NULL) {        
        s = wSymbolNew( name, wTheGlobalScope, W_SYM_BUILTIN );
		s->builtin = routine;
		s->args = args;
		s->optArgs = optArgs;

	} else {
		wErrorThrow( W_ERROR_INTERNAL, "Builtin %s is already declared as a %s",
			s->name, wSymbolName[s->type] );
	}

	return s;
}

/* install all the builtins to the dictionary */
void wBuiltinInit()
{
	int     i;
	wSymbol *s;

	for (i = 0; wBuiltin[i].name != NULL; i++) {  
		s = wBuiltinNew( wBuiltin[i].name,
						  wBuiltin[i].routine,
						  wBuiltin[i].args,
						  wBuiltin[i].optArgs );
	}
}

