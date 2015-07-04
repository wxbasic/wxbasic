/*
    Name:       lexer.c
    Purpose:    Convert source wxBasic code into tokens
    Author:     David Cuny
    Copyright:  (c) 2002 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*/


#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define W_INBUFFER_MAX 1024             /* maximum size of line of code */

char    wLineBuffer[W_INBUFFER_MAX];     /* line from source code */
char    wWord[W_INBUFFER_MAX];          /* token parsed from source */
int     wWordPos = 0;
int     wLineBufferPos = -1;             /* position in line buffer */
int     wEofFlag = 0;                    /* end of file flag */


typedef struct wIncludeData wIncludeData;
struct wIncludeData {
    FILE    *handle;        /* file handle */
    int     fileNum;        /* index to name in wIncludeList */
    int     lineNum;        /* line number last read */
};

wIncludeData wIncludeStack[W_INCLUDE_MAX_DEPTH];
int wIncludeTos = -1;

/* set file to be parsed */
void wPushIncludeFile( char *s, long offset )
{
    char    fileName[256];

    /* save line number */
    if (wIncludeTos > -1) {
        wIncludeStack[wIncludeTos].lineNum = wLineNum;
    }

    wIncludeTos++;
    if (wIncludeTos == W_INCLUDE_MAX_DEPTH) {
        wFatal( W_RUNTIME, "Can't include %s, include stack depth of %d exceeded",
            s, W_INCLUDE_MAX_DEPTH );
    }

    /* save name */
    if (wIncludeCount > W_INCLUDE_MAX) {
        wFatal( W_RUNTIME, "Can't include %s, maximum number of include files is %d",
            s, W_INCLUDE_MAX );
    }
    wIncludeList[wIncludeCount] = wCopyString(s);
    wFileNum = wIncludeCount;
    wIncludeCount++;

    /* open new */
    wInFile = fopen( s, "rt" );
    wLineNum = 0;
    if (wInFile != NULL) {
        strcpy( fileName, s );

    } else {
        /* try full file name */
        if (wCwd != NULL && strlen(wCwd)) {
            strcpy( fileName, wCwd );
            strcat( fileName, s );

            wInFile = fopen( fileName, "rt" );
            if (wInFile == NULL) {
                wFatal( W_INIT, "Unable to open file %s", fileName );
            }
        }
    }

    /* offset into the file? */
    if (offset != 0) {
        /* seek to position in file */
        fseek( wInFile, offset, 0 );
    }

    /* save handle */
    wIncludeStack[wIncludeTos].handle = wInFile;

}

/* popIncludeFile: pop to prior file on stack */
void popIncludeFile()
{
    /* close file */
    fclose( wInFile );
    wEofFlag = 0;

    /* pop stack */
    wIncludeTos--;
    if (wIncludeTos > -1 ) {
        /* restore prior settings */
        wFileNum = wIncludeStack[wIncludeTos].fileNum;
        wLineNum = wIncludeStack[wIncludeTos].lineNum;
        wInFile = wIncludeStack[wIncludeTos].handle;
    }

    wWordPos = 0;
    wLineBufferPos = -1;

}


/* fix the eol char to work under DOS and Linux */
int wFixEol( char *buffer )
{
    int len;

    len = strlen( buffer );
    if (len > 1) {
        /* need to adjust for linux or mac eol? */
        if ((buffer[len-2] == '\r' && buffer[len-1] == '\n') ||
            (buffer[len-2] == '\n' && buffer[len-1] == '\r' )) {
            buffer[len-2] = '\n';
            buffer[len-1] = '\0';
            len--;

        /* missing eol? */
        } else if (buffer[len-1] != '\r' && buffer[len-1] != '\n') {
            buffer[len] = '\n';
            buffer[len+1] = '\0';
            len++;
        }
    }
    return len;
}

/* read a char from the input file */
char wGetChar()
{
    /* end of file? */
    if (wEofFlag) {
        return EOF;
    }

    /* end of buffer? */
    if (wLineBufferPos == -1 || wLineBuffer[wLineBufferPos+1] == '\0') {
        wLineBufferPos = -1;
        if (fgets( wLineBuffer, W_INBUFFER_MAX-2, wInFile ) == 0) {
            popIncludeFile();
            if (wIncludeTos == -1) {
                wEofFlag = 1;
                return EOF;
            } else {
                /* sort of hacky, but it works */
                return wGetChar();
            }
        }

        wFixEol( wLineBuffer );

        /* save */
        wLineNum++;
        wParseLineId = wAddSourceCode( wFileNum, wLineNum, wLineBuffer );

        /* shell comment? */
        if (wLineNum == 1 && wLineBuffer[0] == '#' ) {
            /* skip this line */
            wLineBufferPos = -1;
            return wGetChar();
        }
    }
    wLineBufferPos++;
    return wLineBuffer[wLineBufferPos];
}

/* move buffer back one char */
void wUngetChar()
{
    wLineBufferPos--;
}

/* true if next token is '\n' or ':' */
int wNextTokenIsSep()
{
    int     i = wLineBufferPos+1;

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
        c = wGetChar();

        /* exit if not a digit */
        if (!isdigit(c)) {
            break;
        }

        /* add to buffer */
        wWord[wWordPos++] = c;
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
        c = wGetChar();

        /* exit if not a digit */
        if (isdigit(c) || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f')) {
            /* add to buffer */
            wWord[wWordPos++] = c;

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

    c = wGetChar();
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
            /* fatal */
            wFatal( W_SYNTAX, "Unknown escape code: \\%c", c );
            break;
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
        c = wGetChar();

        if (c=='\n' || c == EOF) {
            /* fatal */
            wFatal( W_SYNTAX, "End of line reached before closing quote" );
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
        wWord[wWordPos++] = c;
    }

    /* pad end */
    wWord[wWordPos] = '\0';
}

/* true for char that breaks a token */
int wIsNonBreakingChar( char c )
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
    int     i;

    while ( wIsNonBreakingChar(c) ){
        wWord[wWordPos++] = c;
        c = wGetChar();
    }

    /* replace last char */
    wUngetChar();

    /* terminate string */
    wWord[wWordPos] = '\0';

    /* save token */
    strcpy( wCurrToken, wWord );

}

/* identify type, and set data value */
int wIdentifyWord()
{
    wSymbol  *s;

    /* in symbol table? */
    s = NULL;
    if (wCurrentScope != NULL) {
        s = wFindSymbol( wWord, wCurrentScope );
    }
    if (s==NULL) {
        s = wFindSymbol( wWord, NULL );
    }
    if (s==NULL) {
        /* copy to private buffer */
        yylval.strValue = wCopyString( wWord );
        return W_TOKEN_UNDEFINED;
    }

    switch( s->symbolType ) {
    case W_SYM_KEYWORD:
        if (s->klass == W_TOKEN_END && wNextTokenIsSep()) {
            /* end statement */
            return W_TOKEN_ENDX;
        } else {
            /* datatype holds symbol value */
            return s->klass;
        }

    case W_SYM_BUILTIN:
        yylval.symbol = s;
        return W_TOKEN_BUILTIN_NAME;

    case W_SYM_CONSTANT:
        yylval.symbol = s;
        return W_TOKEN_CONSTANT_NAME;

    case W_SYM_VARIABLE:
        yylval.symbol = s;
        return W_TOKEN_VARIABLE_NAME;

    case W_SYM_ARRAY:
        yylval.symbol = s;
        return W_TOKEN_ARRAY_NAME;

    case W_SYM_FUNCTION:
        yylval.symbol = s;
        return W_TOKEN_FUNCTION_NAME;

    case W_SYM_SUB:
        yylval.symbol = s;
        return W_TOKEN_SUB_NAME;

    case W_SYM_FORWARD_SUB:
        yylval.symbol = s;
        return W_TOKEN_FORWARD_SUB_NAME;

    case W_SYM_FORWARD_FUNCTION:
        yylval.symbol = s;
        return W_TOKEN_FORWARD_FUNCTION_NAME;

    case W_SYM_CLASS:
        yylval.symbol = s;
        return W_TOKEN_CLASS_NAME;

    default:
        wFatal( W_SYNTAX, "Bad data type: %s", wWord );
    }

    /* can't get here */
    return 0;
}

/* returns ifTrue if letter is next in string, else ifFalse */
int wFollows( int letter, int ifTrue, int ifFalse )
{
    char    nextChar;

    nextChar = wGetChar();
    if (nextChar == letter ) {
        /* add to current token */
        wCurrToken[1] = letter;
        wCurrToken[2] = '\0';

        return ifTrue;
    } else {
        wUngetChar();
        return ifFalse;
    }
}


int yylex()
{
    int     c, nextChar;

    /* reset position of built word */
    wWordPos = 0;
    wWord[wWordPos] = 0;

    /* skip whitespace */
    while (1) {
        c = wGetChar();
        if (c != ' ' && c != '\t' ) {
                break;
        }
    }

    /* save as token */
    wCurrToken[0] = c;
    wCurrToken[1] = '\0';

    /* what are we parsing? */
    switch (c) {

    case '\'':
        /* basic-style comment */
        strcpy( wCurrToken, "end-of-line");
        wLineBufferPos = -1;
        return '\n';

    case '/':
        c = wGetChar();
        switch (c) {
        case '=':
            yylval.iValue = W_OP_DIV;
            return W_TOKEN_INCR_SELF;
        case '/':
            /* c++ style comment */
            strcpy( wCurrToken, "end-of-line");
            wLineBufferPos = -1;
            return '\n';
        default:
            wUngetChar();
            return '/';
        }

    case '\n':
        strcpy( wCurrToken, "end-of-line");
        wLineBufferPos = -1;
        return c;

    /* end of file */
    case EOF:
        strcpy( wCurrToken, "end-of-file" );
        return 0;

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

        /* add to buffer */
        wWord[wWordPos++] = c;

        /* hex number? */
        if (c=='0') {
            c = wGetChar();

            if (c == 'x' || c == 'X') {
                wWord[wWordPos++] = c;
                c = wLexHexDigits();

                /* replace last non-digit */
                wUngetChar();
        
                /* terminate string */
                wWord[wWordPos] = 0;

                /* convert to a hex number */
                sscanf( wWord, "%x", &yylval.iValue );
                return W_TOKEN_INTEGER;

            } else {
                wUngetChar();
            }
        }
            

        /* read remaining digits */
        c = wLexDigits();

        /* floating point? */
        if (c=='.') {

            /* add chars to buffer */
            wWord[wWordPos++] = c;

            /* get remaining digits */
            c = wLexDigits();

        }

        /* replace last non-digit */
        wUngetChar();

        /* terminate string */
        wWord[wWordPos] = '\0';

        /* save as current token */
        strcpy( wCurrToken, wWord );

        /* convert string to number */
        sscanf( wWord, W_NUMBER_FLOAT_FORMAT, &(yylval.fValue) );
        return W_TOKEN_FLOAT;

    /* float or method name */
    case '.':
        /* add to buffer */
        wWord[wWordPos++] = c;

        /* read next char */
        c = wGetChar();

        /* floating point number? */
        if (isdigit(c)) {
            /* add to string */
            wWord[wWordPos++] = c;

            /* read remaining digits */
            wLexDigits();

            /* replace last char read */
            wUngetChar();

            /* terminate string */
            wWord[wWordPos] = 0;

            /* save as current token */
            strcpy( wCurrToken, wWord );

            /* convert string to number */
            sscanf( wWord, W_NUMBER_FLOAT_FORMAT, &(yylval.fValue) );
            return W_TOKEN_FLOAT;

        } else {
            /* method name? */
            if (isalnum(c)) {
                /* clear buffer */
                wWordPos = 0;

                /* read method */
                wLexIdentifier( c );

                /* copy to private buffer */
                yylval.strValue = wCopyString( wWord );
                return W_TOKEN_METHOD_NAME;

            } else {
                /* breaks word */
                wUngetChar();
                return '.';
            }
        }

    /* string */
    case '\"':
        /* parse the string */
        wLexString();

        /* copy to private buffer */
        yylval.strValue = wCopyString( wWord );

        /* save as current token */
        strcpy( wCurrToken, wWord );
        return W_TOKEN_STRING;

    case '!':
        return wFollows('=', W_TOKEN_NE, '!');

    case '<':
        nextChar = wGetChar();

        switch (nextChar) {
        case '>':
            strcpy( wCurrToken, "<>" );
            return W_TOKEN_NE;

        case '=':
            strcpy( wCurrToken, "<=" );
            return W_TOKEN_LE;

        case '<':
            strcpy( wCurrToken, "<<" );
            return W_TOKEN_SHL;

        default:
            wUngetChar();
            return W_TOKEN_LT;
        }

    case '>':
        nextChar = wGetChar();

        switch (nextChar) {
        case '=':
            strcpy( wCurrToken, ">=" );
            return W_TOKEN_GE;

        case '>':
            strcpy( wCurrToken, ">>" );
            return W_TOKEN_SHR;

        default:
            wUngetChar();
            return W_TOKEN_GT;
        }


    /* division is handled elsewhere */
    case '+':
    case '-':
    case '*':
    case '\\':
    case '%':
    case '&':

        switch (c){
        case '+':   yylval.iValue = W_OP_ADD;
                    break;

        case '-':   yylval.iValue = W_OP_SUB;
                    break;

        case '*':   yylval.iValue = W_OP_MUL;
                    break;

        /* /= is handled elsewhere, with // */

        case '\\': yylval.iValue = W_OP_IDIV;
                    break;

        case '%':   yylval.iValue = W_OP_MOD;
                    break;

        case '&':   yylval.iValue = W_OP_CONCAT;
                    break;

        default:    wFatal( W_SYNTAX, "Lexer failed parsing %c", c );
                    break;

        }

        return wFollows('=', W_TOKEN_INCR_SELF, c );

    case '=':
        return W_TOKEN_EQ;

    default:
        /* alpha? */
        if (wIsNonBreakingChar(c)) {
            /* identifier */
            wLexIdentifier(c);
            return wIdentifyWord();

        } else {
            /* seperator */
            return c;
        }
    }

}

void yyerror( char *s )
{
    wErrFlag = 1;
    s = NULL;
}

