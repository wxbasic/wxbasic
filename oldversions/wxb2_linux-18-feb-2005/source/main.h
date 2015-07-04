/*************************************************************
    Name:       main.h
    Purpose:    main routine for wxBasic
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/

void wMainPrintHelp( void );
int wMainParseDirectives( int argc, char *argv[] );
char *wMainGetPath( char *fileName );
FILE *wMainOpen(char *fileName);
int wMainGetOffset( char *fileName );
void wMainCopyArgs( int argc, char *argv[], int argStart, int tagOffset );
int main( int argc, char *argv[]) ;
