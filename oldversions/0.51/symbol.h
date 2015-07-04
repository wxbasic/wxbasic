/*
    Name:       symbol.h
    Purpose:    Data structures for wxBasic symbols
    Author:     David Cuny
    Copyright:  (c) 2002 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*/

/* types of symbols */
enum {
    W_SYM_KEYWORD = 1,        /* keyword                          */
    W_SYM_VARIABLE,           /* variable                         */
    W_SYM_ARRAY,              /* array                            */
    W_SYM_CONSTANT,           /* constant, variant                */
    W_SYM_BUILTIN,            /* builtin function                 */
    W_SYM_FUNCTION,           /* user defined function            */
    W_SYM_SUB,                /* user defined subroutine          */
    W_SYM_FORWARD_SUB,        /* forward reference to sub         */
    W_SYM_FORWARD_FUNCTION,   /* forward reference to function    */
    W_SYM_CLASS               /* wrapped c++ class                */
};

char *wSymbolName[] = {
    "undefined",
    "keyword",
    "variable",
    "array",
    "constant",
    "function",
    "function",
    "sub",
    "sub (forward referenced)",
    "function (forward referenced)",
    "class"
};

struct wSymbol {
    char    *name;                  /* name */
    int     useCase;                /* true if case matters */
    int     symbolType;             /* type */
    int     klass;                  /* used to differentiate classes */
    wSymbol  *scope;                /* if NULL, module level */
    int     common;                 /* if true, global in scope */
    int     stackPos;               /* position of variable on stack */
    int     args;                   /* required args */
    int     optArgs;                /* optional args */
    int     locals;                 /* total count of variables */
    int     indexes;                /* count of indexes */
    wSymbol  *prior;                /* prior symbol */
    wSymbol  *child;                /* link to first child */
    wSymbol  *sibling;              /* link to next sibling */
    wNode    *code;                 /* bytecodes */
    int     forward;                /* forward reference, code undefined */
    void    (*builtin)(void);       /* builtin function */
};

wSymbol *wLastSymbol = NULL;

wSymbol *maskIfHidden( wSymbol *s );
wSymbol *findSymbol( char *name, wSymbol *scope );
void addChildSymbol( wSymbol *s, wSymbol *child );
wSymbol *addSymbol( char *name, wSymbol *scope, int symbolType, int ignoreCase );
wSymbol *findChildSymbol( wSymbol *parent, int index );
void checkArgCount( wSymbol *s, int args );
void wGenerateWarnings( void );
