/*************************************************************
    Name:       token.h
    Purpose:    list of tokens in wxBasic
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/


/* token */
struct wToken {
    int type;           /* type of token */
    char *text;         /* token text */
    wSymbol *symbol;    /* symbol */
    int iValue;         /* integer value */
    wNumber fValue;     /* float value */
};


/* tokens recognized by the parser */


enum {
    /* end of file */
    W_TOKEN_EOF = -1024,

    /* datatypes reported by the lexer */
    W_TOKEN_NOTHING,
    W_TOKEN_STRING,
    W_TOKEN_INTEGER,
    W_TOKEN_FLOAT,
    W_TOKEN_LITERAL,

    /* token names */
    W_TOKEN_FUNCTION_NAME,
    W_TOKEN_SUB_NAME,
    W_TOKEN_BUILTIN_NAME,
    W_TOKEN_CONSTANT_NAME,
    W_TOKEN_VARIABLE_NAME,
    W_TOKEN_STATIC_NAME,
    W_TOKEN_ARRAY_NAME,
    W_TOKEN_CLASS_NAME,
    W_TOKEN_METHOD_NAME,
    W_TOKEN_PROPERTY_NAME,
    W_TOKEN_UNDEFINED,
    W_TOKEN_UNDEFINED_FUNCTION_NAME,

    /* keywords */
    W_TOKEN_ABSTRACT,
    W_TOKEN_AND,
    W_TOKEN_AS,
    W_TOKEN_BREAK,
    W_TOKEN_CASE,
    W_TOKEN_CATCH,
    W_TOKEN_CLASS,
    W_TOKEN_CLOSE,
    W_TOKEN_CONST,
    W_TOKEN_CONTINUE,
    W_TOKEN_DECLARE,
    W_TOKEN_DIM,
    W_TOKEN_DO,
    W_TOKEN_EACH,
    W_TOKEN_ELSE,
    W_TOKEN_ELSEIF,
    W_TOKEN_END,
    W_TOKEN_ENDX,
    W_TOKEN_ERASE,
    W_TOKEN_EXIT,
    W_TOKEN_FINALLY,
    W_TOKEN_FOR,
    W_TOKEN_FOREACH,        /* not really a token */
    W_TOKEN_FUNCTION,
    W_TOKEN_GLOBAL,
    W_TOKEN_IF,
    W_TOKEN_IN,
    W_TOKEN_INHERITS,
    W_TOKEN_INPUT,
    W_TOKEN_INV,
    W_TOKEN_IS,
    W_TOKEN_LINE,
    W_TOKEN_ME,
    W_TOKEN_MOD,
    W_TOKEN_MYBASE,
    W_TOKEN_NEW,
    W_TOKEN_NEXT,
    W_TOKEN_NOCONSOLE,
    W_TOKEN_NOT,
    W_TOKEN_OR,
    W_TOKEN_OPEN,
    W_TOKEN_OPTION,
    W_TOKEN_OUTPUT,
    W_TOKEN_PRINT,
    W_TOKEN_QBASIC,
    W_TOKEN_REDIM,
    W_TOKEN_REDO,
    W_TOKEN_RETURN,
    W_TOKEN_SELECT,
    W_TOKEN_SELF,
    W_TOKEN_SHARED,
    W_TOKEN_SHL,
    W_TOKEN_SHR,
    W_TOKEN_STATIC,
    W_TOKEN_STEP,
    W_TOKEN_SUB,
    W_TOKEN_THEN,
    W_TOKEN_THROW,
    W_TOKEN_TO,
    W_TOKEN_TRY,
    W_TOKEN_UNTIL,
    W_TOKEN_VIRTUAL,
    W_TOKEN_WEND,
    W_TOKEN_WHILE,
    W_TOKEN_XOR,

    /* special tokens */
    W_TOKEN_EQ,
    W_TOKEN_NE,                     /* != */
    W_TOKEN_GT,                     /* > */
    W_TOKEN_LT,                     /* < */
    W_TOKEN_GE,                     /* >= */
    W_TOKEN_LE,                     /* <= */
    W_TOKEN_INCR_SELF,              /* class of +=, *= , etc. */
    W_TOKEN_3DOTS,                  /* ... */
    W_TOKEN_DOTMETHOD,              /* xxx.yyy(...) */
    W_TOKEN_DOTPROPERTY             /* xxx.yyy */
};

/* need to offset by -1024 */
char *wTokenName[] = {
    /* end of file */
    "EOF",

    /* datatypes reported by the lexer */
    "NOTHING",
    "STRING",
    "INTEGER",
    "FLOAT",
    "LITERAL",

    /* token names */
    "FUNCTION_NAME",
    "SUB_NAME",
    "BUILTIN_NAME",
    "CONSTANT_NAME",
    "VARIABLE_NAME",
    "STATIC_NAME",
    "ARRAY_NAME",
    "CLASS_NAME",
    "METHOD_NAME",
    "PROPERTY_NAME",
    "UNDEFINED",
    "UNDEFINED_FUNCTION_NAME",

    /* keywords */
    "ABSTRACT",
    "AND",
    "AS",
    "BREAK",
    "CASE",
    "CATCH",
    "CLASS",
    "CLOSE",
    "CONST",
    "CONTINUE",
    "DECLARE",
    "DIM",
    "DO",
    "EACH",
    "ELSE",
    "ELSEIF",
    "END",
    "ENDX",
    "ERASE",
    "EXIT",
    "FINALLY",
    "FOR",
    "FOREACH",        /* not really a token */
    "FUNCTION",
    "GLOBAL",
    "IF",
    "IN",
    "INHERITS",
    "INPUT",
    "INV",
    "IS",
    "LINE",
    "ME",
    "MOD",
    "MYBASE",
    "NEW",
    "NEXT",
    "NOCONSOLE",
    "NOT",
    "OR",
    "OPEN",
    "OPTION",
    "OUTPUT",
    "PRINT",
    "QBASIC",
    "REDIM",
    "REDO",
    "RETURN",
    "SELECT",
    "SELF",
    "SHARED",
    "SHL",
    "SHR",
    "STATIC",
    "STEP",
    "SUB",
    "THEN",
    "THROW",
    "TO",
    "TRY",
    "UNTIL",
    "VIRTUAL",
    "WEND",
    "WHILE",
    "XOR",

    /* special tokens */
    "EQ",
    "NE",                     /* != */
    "GT",                     /* > */
    "LT",                     /* < */
    "GE",                     /* >= */
    "LE",                     /* <= */
    "INCR_SELF",              /* class of +=", *= ", etc. */
    "3DOTS",                  /* ... */
    "DOTMETHOD",              /* xxx.yyy(...) */
    "DOTPROPERTY"             /* xxx.yyy */
};
