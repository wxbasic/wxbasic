/*************************************************************
    Name:       lexer.c
    Purpose:    tokenize wxBasic source code
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/


/* set up lexer defaults */
void wLexInit()
{
    /* set aside a large buffer for the token */
    wTheToken.text = (char *)wMalloc( 1024 );
}

/* read a char from the input file */
char wLexGetChar()
{
    /* clear end of file flag */
    wEofFlag = W_FALSE;

    /* end of file? */
    if (wReadLine > wSourceFile->count) {
        /* treat eof as eof */
        wEofFlag = W_TRUE;
        return EOF;
    }

    /* end of buffer? */
    if (wLineBufferPos == W_BUFFER_EMPTY
    ||  wLineBuffer[wLineBufferPos+1] == '\0') {
        /* reset position and move ahead */
        wLineBufferPos = -1;
        wReadLine++;

        /* end of file? */
        if (wReadLine > wSourceFile->count ) {
            wEofFlag = W_TRUE;
            return EOF;
        } else {
            /* get the next line of source code */
            wLineBuffer = wSourceGetChar(wReadLine); 
        }
    }

    /* move to next position in buffer and return character there */
    wLineBufferPos++;
    return wLineBuffer[wLineBufferPos];
}

/* move buffer back one char */
void wLexUngetChar()
{
    wLineBufferPos--;
}

/* look at next char without moving ahead */
int wLexPeekChar()
{
    return wLineBuffer[wLineBufferPos+1];
}

/* true if next token is '\n' or ':' */
int wLexNextTokenIsSep()
{
    int i = wLineBufferPos+1;

    while (1) {
        switch (wLineBuffer[i++]) {
        case '\n':
        case ':':
            return 1;

        case ' ':
        case '\t':
            break;

        default:
            return 0;
        }
    }
}

int wLexDigits()
{
    /* read digits into the word buffer */
    /* returns last non-digit char read */

    char   c;

    /* read digits */
    while (1){
        /* get the next char */
        c = wLexGetChar();

        /* exit if not a digit */
        if (!isdigit(c)) {
            break;
        }

        /* add to buffer */
        wTheToken.text[wWordPos++] = c;
    }

    /* return last (non-digit) char read */
    return c;

}

int wLexHexDigits()
{
    /* read digits into the word buffer */
    /* returns last non-digit char read */

    char   c;

    /* read digits */
    while (1){
        /* get the next char */
        c = wLexGetChar();

        /* exit if not a digit */
        if (isdigit(c) || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f')) {
            /* add to buffer */
            wTheToken.text[wWordPos++] = c;

        } else {
            break;
        }
    }

    /* return last (non-digit) char read */
    return c;

}


/* read special char */
int wLexBackquotedChar()
{
    char c;

    c = wLexGetChar();
    switch (c) {
        case 'n':
            return '\n';

        case 'r':
            return '\r';

        case 't':
            return '\t';

        case '\'':
            return '\'';

        case '\"':
            return '\"';

        case '\\':
            return '\\';

        default:
            /* generate error if option backslash is true */
            if (wTheOptionBackslash) {
                /* fatal */
                wErrorThrow( W_ERROR_SYNTAX, "Unknown escape code: \\%c", c );
            } else {
                /* put the character back */
                wLexUngetChar();

                /* pass backslash */
                return '\\';
                break;
            }
    }

    /* can't get here */
    return ' ';
}

/* read string into buffer */
void wLexString()
{

   char c;

    /* clear buffer */
    wWordPos = 0;

    while (1) {
        /* read a char */
        c = wLexGetChar();

        if (c=='\n' || wEofFlag) {
            /* fatal */
            wErrorThrow( W_ERROR_SYNTAX, "End of line reached before closing quote" );
        }

        /* if end of string, leave loop */
        if (c=='\"') {
            break;
        }

        /* special character */
        if (c == '\\') {
            c = wLexBackquotedChar();
        }

        /* add to string */
        wTheToken.text[wWordPos++] = c;
    }

    /* pad end */
    wTheToken.text[wWordPos] = '\0';
}

/* true for char that breaks a token */
int wLexIsNonBreakingChar( char c )
{
    if (isalnum(c)) {
        return 1;
    }

    switch (c) {
    case '$':
    case '_':
        return 1;
    default:
        return 0;
    }
}

/* parse remainder of token as identifier */
void wLexIdentifier( int c )
{
    /* read until end of identifier */
    while ( wLexIsNonBreakingChar(c) ){
        /* save in lower case */
        wTheToken.text[wWordPos++] = tolower( c );

        c = wLexGetChar();
    }

    /* replace last char */
    wLexUngetChar();

    /* terminate string */
    wTheToken.text[wWordPos] = '\0';

}

/* identify type, and set data value */
int wLexIdentifyWord()
{
    char c;
    wSymbol  *s;

    /* look for token */
    s = wSymbolFind( wTheToken.text, wTheCurrentScope );
    if (s==NULL) {
        /* function or variable? */
        c = wLexGetChar();
        wLexUngetChar();

        if (c == '(') {
            return W_TOKEN_UNDEFINED_FUNCTION_NAME;
        } else {
            return W_TOKEN_UNDEFINED;
        }
    }

    switch( s->type ) {
    case W_SYM_KEYWORD:
        if (s->tokenType == W_TOKEN_END && wLexNextTokenIsSep()) {
            /* end statement */
            return W_TOKEN_ENDX;
        } else {
            /* return type of token */
            return s->tokenType;
        }

    case W_SYM_LITERAL:
        wTheToken.iValue = s->tokenType;
        return W_TOKEN_LITERAL;

    case W_SYM_BUILTIN:
        wTheToken.symbol = s;
        return W_TOKEN_BUILTIN_NAME;

    case W_SYM_CONSTANT:
        wTheToken.symbol = s;
        return W_TOKEN_CONSTANT_NAME;

    case W_SYM_VARIABLE:
        wTheToken.symbol = s;
        return W_TOKEN_VARIABLE_NAME;

    case W_SYM_FUNCTION:
        wTheToken.symbol = s;
        return W_TOKEN_FUNCTION_NAME;

    case W_SYM_SUB:
        wTheToken.symbol = s;
        return W_TOKEN_SUB_NAME;

    case W_SYM_USER_CLASS:
    case W_SYM_BUILTIN_CLASS:
        wTheToken.symbol = s;
        return W_TOKEN_CLASS_NAME;

    default:
        wErrorThrow( W_ERROR_SYNTAX, "Bad data type: %s", wTheToken.text );
    }

    /* can't get here */
    return 0;
}

/* parse a number */
void wLexNumber( char c ) {
    int noFloat;
    
    /* allow floating point */
    noFloat = 0;

    /* add to buffer */
    wTheToken.text[wWordPos++] = c;

    /* hex number? */
    if (c=='0') {
        c = wLexGetChar();

        if (c == 'x' || c == 'X') {
            wTheToken.text[wWordPos++] = c;
            wLexHexDigits();

            /* replace last non-digit */
            wLexUngetChar();

            /* terminate string */
            wTheToken.text[wWordPos] = 0;

            /* convert to a hex number */
            sscanf( wTheToken.text, "%x", &wTheToken.iValue );
            wTheToken.type = W_TOKEN_INTEGER;

            /* disallow floating point */
            noFloat = 1;

        } else {
            wLexUngetChar();
        }
    }

    /* allow float? */
    if (!noFloat) {
        /* read remaining digits */
        c = wLexDigits();

        /* floating point? */
        if (c=='.') {
            /* add chars to buffer */
            wTheToken.text[wWordPos++] = c;

            /* get remaining digits */
            wLexDigits();

        }

        /* replace last non-digit */
        wLexUngetChar();

        /* terminate string */
        wTheToken.text[wWordPos] = '\0';

        /* convert string to number */
        // FIXME: This should be factored as part of wNumber...
        sscanf( wTheToken.text, "%f", &wTheToken.fValue );
        wTheToken.type = W_TOKEN_FLOAT;

    }    
}

/* returns ifTrue if letter is next in string, else ifFalse */
int wLexFollows( int letter, int ifTrue, int ifFalse )
{
    char    nextChar;

    nextChar = wLexGetChar();
    if (nextChar == letter ) {
        /* add to current token */
        wTheToken.text[1] = letter;
        wTheToken.text[2] = '\0';

        return ifTrue;
    } else {
        wLexUngetChar();
        return ifFalse;
    }
}


/* used by wLexChar to ignore strings */
void wLexSkipString()
{
    char c;

    while (1) {
        /* read a char */
        c = wLexGetChar();

        if (c=='\n' || wEofFlag) {
            /* fatal */
            wErrorThrow( W_ERROR_SYNTAX, "End of line reached before closing quote" );
        }

        /* if end of string, leave loop */
        if (c=='\"') {
            break;
        }

        /* special character */
        if (c == '\\') {
            /* skip it */
            c = wLexGetChar();
        }

    }
}



/* returns true if token has target character */
int wLexHasChar( char target )
{

    /* this is a bit messy, because (in theory) the */
    /* token could have indexes, so the full token  */
    /* would be spread over several lines.          */

    int currentLine, currentPos, depth;
    char c;

    /* position in buffer */
    currentLine = wReadLine;
    currentPos = wLineBufferPos;

    /* mark paren depth */
    depth = 0;

    /* get current char */
    c = wLineBuffer[wLineBufferPos];

    /* scan from current position */
    while (1) {

        /* skip strings */
        if (c == '\"') {
            /* skip the string */
            wLexSkipString();

        /* skip indexes */
        } else if (c == '[') {
            depth++;

        } else if (c == ']' && depth) {
            depth--;

        } else if (depth) {
            /* end of file? */
            if (wEofFlag) {
                break;

            /* string */
            } else if (c == '\"') {
                /* skip the string */
                wLexSkipString();

            /* comment */
            } else if (c == '\'') {
                /* skip rest of the line */
                wLineBufferPos = W_BUFFER_EMPTY;

            /* C++ style comment */
            } else if (c == '/' && wLexPeekChar() == '/') {
                /* skip rest of the line */
                wLineBufferPos = W_BUFFER_EMPTY;
            }

        /* exit if breaking char (except for '.') or matches target */
        } else if ((!wLexIsNonBreakingChar(c) && c != '.')
        ||  c == target) {
            break;
        }

        /* get char at current position */
        c = wLexGetChar();
    }


    /* restore the line, if changed */
    if (wReadLine != currentLine) {
        wLineBuffer = wSourceGetChar(currentLine);
    };


    /* restore the position in the line */
    wLineBufferPos = currentPos;

    /* return true if stopped on a target char */
    return (c == target);
}


int wLexToken()
{
    int     c, nextChar;

    /* reset position of built word */
    wWordPos = 0;
    wTheToken.text[wWordPos] = 0;

    /* clear symbol */
    wTheToken.symbol = NULL;

    /* skip whitespace */
    while (1) {
        c = wLexGetChar();
        if (c != ' ' && c != '\t' ) {
            break;
        }
    }

    /* save as token */
    wTheToken.text[0] = c;
    wTheToken.text[1] = '\0';

    /* what are we parsing? */
    switch (c) {

    case '\'':
        /* basic-style comment */
        strcpy( wTheToken.text, "end-of-line");
        wLineBufferPos = W_BUFFER_EMPTY;
        wTheToken.type = '\n';
        break;

    case '/':
        c = wLexGetChar();
        switch (c) {
        case '=':
            wTheToken.iValue = '/';
            wTheToken.type = W_TOKEN_INCR_SELF;
            break;

        case '/':
            /* c++ style comment */
            strcpy( wTheToken.text, "end-of-line");
            wLineBufferPos = W_BUFFER_EMPTY;
            wTheToken.type = '\n';
            break;

        default:
            wLexUngetChar();
            wTheToken.type = '/';
            break;

        }
        break;

    case '\n':
        strcpy( wTheToken.text, "end-of-line");
        wLineBufferPos = W_BUFFER_EMPTY;
        wTheToken.type = c;
        break;

    /* integer */
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        wLexNumber(c);
        break;

    /* float or method name */
    case '.':
        /* add to buffer */
        wTheToken.text[wWordPos++] = c;

        /* read next char */
        c = wLexGetChar();

        /* floating point number? */
        if (isdigit(c)) {
            /* add to string */
            wTheToken.text[wWordPos++] = c;

            /* read remaining digits */
            wLexDigits();

            /* replace last char read */
            wLexUngetChar();

            /* terminate string */
            wTheToken.text[wWordPos] = '\0';

            /* convert string to number */
            // FIXME: This should be factored as part of wNumber...
            sscanf( wTheToken.text, "%f", &wTheToken.fValue );
            wTheToken.type = W_TOKEN_FLOAT;

        } else {
            /* dot name? */
            if (isalnum(c)) {

                /* clear buffer */
                wWordPos = 0;

                /* read method */
                wLexIdentifier( c );

                /* peek ahead to the next character */
                c = wLexGetChar();
                wLexUngetChar();
                
                /* ends with an open paren? '(' */
                if (c == '(') {
                    /* method */
                    wTheToken.type = W_TOKEN_METHOD_NAME;
                } else {
                    /* property */
                    wTheToken.type = W_TOKEN_PROPERTY_NAME;
                }

            } else {
                /* breaks word */
                wLexUngetChar();
                wTheToken.type = '.';

                /* is it three dots? (...) */
                /* this prevents having linefeed issues */
                if (wLineBuffer[wLineBufferPos+1] == '.'
                &&  wLineBuffer[wLineBufferPos+2] == '.' ) {
                    strcpy( wTheToken.text, "..." );
                    wLineBufferPos += 2;
                    wTheToken.type = '.';
                    wTheToken.type = W_TOKEN_3DOTS;
                }
            }
        }
        break;

    /* string */
    case '\"':
        /* parse the string */
        wLexString();
        wTheToken.type = W_TOKEN_STRING;

        break;

    case '!':
        wTheToken.type = wLexFollows('=', W_TOKEN_NE, '!');
        break;

    case '<':
        nextChar = wLexGetChar();

        switch (nextChar) {
        case '>':
            strcpy( wTheToken.text, "<>" );
            wTheToken.type = W_TOKEN_NE;
            break;

        case '=':
            strcpy( wTheToken.text, "<=" );
            wTheToken.type = W_TOKEN_LE;
            break;

        case '<':
            strcpy( wTheToken.text, "<<" );
            wTheToken.type = W_TOKEN_SHL;
            break;

        default:
            wLexUngetChar();
            wTheToken.type = W_TOKEN_LT;
            break;
        }
        break;

    case '>':
        nextChar = wLexGetChar();

        switch (nextChar) {
        case '=':
            strcpy( wTheToken.text, ">=" );
            wTheToken.type = W_TOKEN_GE;
            break;

        case '>':
            strcpy( wTheToken.text, ">>" );
            wTheToken.type = W_TOKEN_SHR;
            break;


        default:
            wLexUngetChar();
            wTheToken.type = W_TOKEN_GT;
            break;
        }
        break;


    /* division is handled elsewhere */
    case '+':
    case '-':
    case '*':
    case '\\':
    case '%':
    case '&':
        wTheToken.iValue = c;
        wTheToken.type = wLexFollows('=', W_TOKEN_INCR_SELF, c );
        break;

    case '=':
        wTheToken.type = W_TOKEN_EQ;
        break;

    default:
        /* end of file? */
        if (wEofFlag) {
            strcpy( wTheToken.text, "end-of-file" );
            wTheToken.type = W_TOKEN_EOF;
            break;
        }

        /* alpha? */
        if (wLexIsNonBreakingChar(c)) {
            /* dotted commands emit a special token before being parsed */
            if ( wLexHasChar( '.' )
            &&   wTheToken.type != W_TOKEN_DOTMETHOD
            &&   wTheToken.type != W_TOKEN_DOTPROPERTY ) {
                /* has an open paren in it? */
                if (wLexHasChar('(')) {
                    /* it's a command */
                    wTheToken.type = W_TOKEN_DOTMETHOD;
                } else {
                    /* it's a property */
                    wTheToken.type = W_TOKEN_DOTPROPERTY;
                }
                /* unget the last character */
                wLexUngetChar();
                break;
            }

            /* identifier */
            wLexIdentifier(c);
            wTheToken.type = wLexIdentifyWord();

        } else {
            /* seperator */
            wTheToken.type = c;
        }
        break;
    }

    /* return the type */
    return wTheToken.type;

}

