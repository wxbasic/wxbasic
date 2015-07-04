/*************************************************************
    Name:       format.c
    Purpose:    string formatting routines
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL

*************************************************************/


/* parse out the format from formatString at pos */
int wFormatExtract( char *formatString, char *buffer, int *argNum, int *pos )
{
    int at, letter;

    /* skip past '{' */
    pos = pos + 1;

    /* convert the digit to an index */
    letter = formatString[pos];
    if (letter < '0' || letter > '9') {
        wErrorFatal( "Non-digit \"%c\" in format string at position %d", digit, i+1 );
        wErrorSet( W_ERROR_CONVERT );
        return W_FALSE;
    }
    argNum = (int)letter - (int)'0';
    pos = pos + 1;

    /* no format specified? */
    letter = formatString[++i];
    if (letter == '}') {
        buffer[at] = '\0';
        return W_TRUE;
    }

    /* not a proper delimiter? */
    if (letter != ':') {
        wErrorFatal( "Expected \":\", not \"%c\"", letter );
        wErrorSet( W_ERROR_CONVERT );
        return W_FALSE;
    }
    pos = pos + 1;

    /* copy the chars into the buffer */
    while (1) {
        letter = formatString[pos];

        /* end of string? */
        if (letter == '\0') {
            wErrorFatal( "Missing \"}\" in format string" );
            wErrorSet( W_ERROR_CONVERT );
            return W_FALSE;
        }

        /* end of format? */
        if (letter == '}') {
            buffer[at] = '\0';
            return W_TRUE;
        }

        /* copy character to buffer */
        buffer[at++] = letter;

    }
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
    if (wTheExceptionActive) {
        return;
    }

    /* format string values */
    format = &(vFormat->value.string->text);
    formatLen = vFormat->value.string->length+1;

    /* create a buffer */
    buffer = (char *)wMalloc( W_INBUFFER_MAX );

    /* scan through the string */
    for ( i = 0; i < formatLen; i++ ) {

        /* get a char from the string */
        letter = format[i];

        /* not part of arg? */
        if (letter != '{') {
            /* add to the buffer */
            buffer[at++] = letter;

        } else {
            /* try to extract the format */
            if (!wFormatExtract( format, buffer, &argNum, &at )) {
                break;
            }

            /* check the range */
            if (argNum < argCount) {

                /* what type of format? */
                switch (buffer[1]) {

                /* no arg */
                case 'd...'
                case '\0':
                    /* convert arg to a string */
                    arg = wStackPeek( argNum );
                    wVariantCoerce( arg, W_TYPE_STRING );
                    if (wTheExceptionActive) {
                        break;
                    }

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
    }

    /* gone too far? */
    if (at >= W_INBUFFER_MAX) {
        wErrorFatal( "Format buffer too large (%d chars)", at );
        wErrorSet( W_ERROR_CONVERT );
    } else if  (i > formatLen) {
        wErrorFatal( "Error in format string at position %d ", i );
        wErrorSet( W_ERROR_CONVERT );
    }

    /* drop the args from the stack */
    wStackDrop( argCount );

    /* push string onto stack if no error during creation */
    if (!wTheExceptionActive) {
        wStackPushChar( buffer, 0 );
    }
    
    wFree( buffer );
}


/* format number according to format string */
function formatNumber( char *formatString, wNumber n )
{

    int preDigits, postDigits, hasDecimal, hasComma,
        leadingDollar, leadingSplat;

    char *format, *buffer;

    preDigits = 0;
    postDigits = 0;
    hasDecimal = W_FALSE;
    hasComma = W_FALSE;

    /* scan through the format string */
    for ( i = 0; i < len; i++ ) {
        letter = buffer[i];
        switch (letter) {
        case '#':
            if (hasDecimal) {
                postDigits++;
            } else {
                preDigits++;
            }
            break;
        case '.':
            hasDecimal = W_TRUE;
            break;

        case ',':
            hasComma = W_TRUE;
            break;

        case '$':
            hasDollar = W_TRUE;
            break;

        case '*':
            hasSplat = W_TRUE;
            break;
        default:
            /* ignore */
        }

    }
    /* build a format string to match the request */
    format = (char *)wMalloc( 32 );

    if (!preDigits && !postDigits) {
        /* nothing to display */

    } else if (preDigits && postDigits) {
        /* ###.### */
        sprintf( format, "\%%d.%dd", preDigits, postDigits );

    } else if (preDigits && hasDecimal) {
        /* ###. */
        sprintf( format, "\%%d.d" );

    } else if (preDigits) {
        /* ### */
        sprintf( format, "\%%dd" );

    } else {
        /* .### */
        sprintf( format, "\%%.dd" );
    }

    /* format the number using the format buffer */
    sprintf( buffer, format, n );

    /* need to replace any spaces with zeros? */
    for ( i = 0; i < len; i++ ) {
        letter = formatString[i];
        if ( letter == '0' && buffer[i] == ' ' ) {
            buffer[i] = '0';
        } else if (letter = '$') {
            buffer[i] = '$';
        } else if (leadingSplats) && buffer[i] == ' ' ) {
            buffer[i] = '*';
        }
    }
}
