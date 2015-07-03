/*
    Name:       lexer.h
    Purpose:    Convert source wxBasic code into tokens
    Author:     David Cuny
    Copyright:  (c) 2002 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*/

void wPushIncludeFile( char *s, long offset );
void wPopIncludeFile();
int wFixEol( char *buffer );
char wGetChar();
void wUngetChar();
int wNextTokenIsSep();
int wLexDigits();
int wLexHexDigits();
int wLexBackquotedChar();
void wLexString();
int wIsNonBreakingChar( char c );
void wLexIdentifier( int c );
int wIdentifyWord();
int wFollows( int letter, int ifTrue, int ifFalse );
int yylex();
void yyerror( char *s );
