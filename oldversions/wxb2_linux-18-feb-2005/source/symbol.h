/*************************************************************
    Name:       symbol.c
    Purpose:    symbol table for wxBasic
    Author:     David Cuny
    Copyright:  (c) 2002 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/

#define W_HASHTABLE_SIZE 4094
#define W_HASH_MULTIPLER 31

/* hash table for symbols */
wSymbol *wSymbolHashTable[W_HASHTABLE_SIZE];

struct wSymbol {
    char    *name;                  /* name */
    int     index;                  /* index in symbol table */
    int     next;                   /* next symbol in chain */
    int     tokenType;              /* token type */
    int     type;                   /* type */
    int     typeCast;               /* if variable, value to cast to */
    int     scope;                  /* index of parent */
    int     stackPos;               /* position of variable on stack */
    wGrow   *children;              /* int array of children */
    int     alias;                  /* index of symbol this aliases */
    int     inherits;               /* index of superclass */
    int     flags;                  /* Public, Abstract, Virtual */
    int     args;                   /* count of normal arguments */
    int     optArgs;                /* optional args */
    int     varArgs;                /* has variable numbers of args? */
    wGrow   *method;                /* pointers to methods */
    wGrow   *pcode;                 /* pointer to bytecode */
    void    (*builtin)(void);       /* builtin function */
    int     called;                 /* if non-zero, function was referenced */
};


/* flags */
#define W_SYM_ISNATIVE      1   /* native datatype */
#define W_SYM_ISPRIVATE     2   /* not publicly visible */
#define W_SYM_ISABSTRACT    4   /* applies to Class or method */
#define W_SYM_ISVIRTUAL     8   /* applies to method */

/* types of symbols */
enum {
    W_SYM_KEYWORD = 1,          /* keyword                      */
    W_SYM_LITERAL,              /* literal                      */
    W_SYM_VARIABLE,             /* variable                     */
    W_SYM_CONSTANT,             /* constant                     */
    W_SYM_BUILTIN,              /* builtin function             */
    W_SYM_FUNCTION,             /* user defined function        */
    W_SYM_SUB,                  /* user defined sub             */
    W_SYM_USER_CLASS,           /* user class name              */
    W_SYM_BUILTIN_CLASS,        /* builtin class name           */
    W_SYM_OBJECT                /* instance of a class object   */
};

char *wSymbolName[] = {
    "an undefined",
    "a builtin constant",
    "a keyword",
    "a variable",
    "a constant",
    "a builtin routine",
    "a function",
    "a sub",
    "a class",
    "a builtin class",
    "an object"
};

void wSymbolInit( void );
int wSymbolHash( char *letters );
void wSymbolAddToHashTable( wSymbol *symbol );
void wSymbolUnused( char *name );
wSymbol *wSymbolNew( char *name, int scope, int symbolType );
wSymbol *wSymbolLookup( int index  );
wSymbol *wSymbolFind( char *name, int scope );
wSymbol *wSymbolFindMethod( wSymbol *klass, int stringIndex );
wSymbol *wSymbolFindMethodChar( wSymbol *klass, char *methodChar );
int wSymbolFindPropPos( wSymbol *klass, int stringIndex );
int wSymbolFindPropPosChar( wSymbol *klass, char *name );
char *wSymbolGetName( char *name, int scope );
void wSymbolAddChild( wSymbol *parent, wSymbol *child );
wSymbol *wSymbolGetChild( wSymbol *parent, int index );
wSymbol *wSymbolNewLocal( char *name, int alias );
void wSymbolCheckArgCount( wSymbol *symbol, int args );
void wSymbolUndefinedRoutines( void );
int wSymbolInherits( wSymbol *klass, int classIndex );
void wSymbolCheckAbstract( wSymbol *klass );
