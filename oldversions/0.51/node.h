/*
    Name:       node.h
    Purpose:    Parse tree data structure for wxBasic
    Author:     David Cuny
    Copyright:  (c) 2002 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*/


struct wNode {
    int     op;             /* operation */
    union {
        int     iValue;     /* integer data */
        wNumber  fValue;    /* float data */
        char    *string;    /* string */
        wSymbol  *symbol;   /* symbol */
    } value;
    int     trace;
    wNode   *left;
    wNode   *right;
    wNode   *next;
};

wNode *wOpNode( int op, wNode *left, wNode *right );
wNode *wIntNode( int op, int value, wNode *left, wNode *right );
wNode *wFloatNode( int op, wNumber value, wNode *left, wNode *right );
wNode *wStringNode( int op, char *string, wNode *left, wNode *right );
wNode *wSymbolNode( int op, wSymbol *symbol, wNode *left, wNode *right );
void wFreeNode( wNode *node );
