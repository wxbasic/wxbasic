/*
    Name:       trace.c
    Purpose:    Code tracing for wxBasic
    Author:     David Cuny
    Copyright:  (c) 2002 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*/

/* add a line of source code to the linked list */
int wAddSourceCode( int theFileNum, int theLineNum, char *text )
{
    wSourceCode  *link;

    /* fill in the link */
    link = (wSourceCode *)wMalloc( sizeof( wSourceCode ) );
    link->id = wSourceLineCounter;
    link->fileNum = theFileNum;
    link->lineNum = theLineNum;
    link->text = wCopyString( text );
    link->prior = wLastSourceLink;
    wLastSourceLink = link;
    return wSourceLineCounter++;
}

/* search source for line of text */
wSourceCode *wFindSource( int id )
{
    wSourceCode  *code;
    code = wLastSourceLink;
    while (code != NULL) {
        if (code->id == id) {
            return code;
        }
        code = code->prior;
    }
    return NULL;
}
