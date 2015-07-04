/*************************************************************
    Name:       lexer.h
    Purpose:    tokenize wxBasic source code
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/


int     wReadLine = 0;                      /* source line being read */
char    *wLineBuffer = NULL;                /* pointer to source code */
int     wLineBufferPos = W_BUFFER_EMPTY;    /* position in line buffer */
int     wWordPos = 0;                       /* position in word */
int     wEofFlag = 0;                       /* true if EOF char mean EOF */
wToken  wTheToken;                          /* current token */

void wLexInit( void );
char wLexGetChar( void );
void wLexUngetChar( void );
int wLexPeekChar( void );
int wLexNextTokenIsSep( void );
int wLexDigits( void );
int wLexHexDigits( void );
int wLexBackquotedChar( void );
void wLexString( void );
int wLexIsNonBreakingChar( char c );
void wLexIdentifier( int c );
int wLexIdentifyWord( void );
int wLexFollows( int letter, int ifTrue, int ifFalse );
void wLexSkipString( void );
int wLexHasChar( char target );
int wLexToken( void );
