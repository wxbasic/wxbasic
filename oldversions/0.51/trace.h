/*
    Name:       trace.h
    Purpose:    Code tracing for wxBasic
    Author:     David Cuny
    Copyright:  (c) 2002 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*/

typedef struct wSourceCode wSourceCode;

struct wSourceCode {
    int         id;         /* unique identifier */
    int         fileNum;    /* file the source line came from */
    int         lineNum;    /* line number from the file */
    char        *text;      /* line of code */
    wSourceCode  *prior;    /* link to prior line of code */
};

int wSourceLineCounter = 0;  /* value of next SourceCode->id */

wSourceCode  *wLastSourceLink = NULL;     /* linked list of source code   */

int wAddSourceCode( int theFileNum, int theLineNum, char *text );
wSourceCode *wFindSource( int id );
