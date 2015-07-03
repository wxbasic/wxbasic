/*
    Name:       node.c
    Purpose:    Parse tree data structure for wxBasic
    Author:     David Cuny
    Copyright:  (c) 2002 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*/

/* create a node with an operand and two arguments */
wNode *wOpNode( int op, wNode *left, wNode *right )
{
    wNode    *node;

    node = (wNode *) wMalloc( sizeof( wNode ) );
    node->op = op;
    node->left = left;
    node->right = right;
    node->next = NULL;
    node->trace = -1;    
    return node;
}

/* create a node with an integer data value */
wNode *wIntNode( int op, int value, wNode *left, wNode *right )
{
    wNode    *node;

    node = wOpNode( op, left, right );
    node->value.iValue = value;
    return node;
}

/* create a node with an float data value */
wNode *wFloatNode( int op, wNumber value, wNode *left, wNode *right )
{
    wNode    *node;

    node = wOpNode( op, left, right );
    node->value.fValue = value;
    return node;
}

/* create a node with an string data value */
wNode *wStringNode( int op, char *string, wNode *left, wNode *right )
{
    wNode    *node;

    node = wOpNode( op, left, right );
    node->value.string = string;
    return node;
}

/* create a node with an symbol data value */
wNode *wSymbolNode( int op, wSymbol *symbol, wNode *left, wNode *right )
{
    wNode    *node;

    node = wOpNode( op, left, right );
    node->value.symbol = symbol;
    return node;
}


/* release a node (and it's children) from memory */
void wFreeNode( wNode *node )
{
    if (node != NULL) {
        wFreeNode( node->left );
        wFreeNode( node->right );
    }
    wFree( node );
}
