/*
    Name:       eval.h
    Purpose:    evaluates nodes generated by parser for wxBasic
    Author:     David Cuny
    Copyright:  (c) 2002 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*/

/* control loop flags */
int     wExitForFlag = 0;
int     wExitRoutineFlag = 0;
int     wExitWhileFlag = 0;
int     wContinueFlag = 0;


/* comparisons */
enum {
    W_EQ = 1,
    W_NE,
    W_GT,
    W_LT,
    W_GE,
    W_LE
};

/* print flags */
enum {
    W_PRINT,
    W_PRINT_TAB,
    W_PRINT_NEWLINE
};

/* opcodes */
enum {
    W_OP_ADD = 1,
    W_OP_AND,
    W_OP_ARGLIST,
    W_OP_ARRAY_GET,
    W_OP_ARRAY_PTR,
    W_OP_ARRAY_SET,
    W_OP_ASSIGN,
    W_OP_BUILTIN,
    W_OP_BUILTIN_CALL,
    W_OP_CASE_CMP,
    W_OP_CASE_ELSE,
    W_OP_CASE_RANGE,
    W_OP_CASE_SELECT,
    W_OP_CLASS_METHOD,
    W_OP_CLASS_METHOD_CALL,
    W_OP_CLOSE,
    W_OP_CMP,
    W_OP_COMMA,
    W_OP_CONCAT,
    W_OP_CONST_GET,
    W_OP_CONST_Set,
    W_OP_CONTINUE,
    W_OP_DELETE,
    W_OP_DESTROY,
    W_OP_DIV,
    W_OP_END,
    W_OP_ERASE,
    W_OP_EXIT_FOR,
    W_OP_EXIT_ROUTINE,
    W_OP_EXIT_WHILE,
    W_OP_FLOAT,
    W_OP_FOR,
    W_OP_FOR_EACH,
    W_OP_FOR_STEP,
    W_OP_FUNCTION,
    W_OP_FUNCTION_CALL,
    W_OP_IDIV,
    W_OP_IF,
    W_OP_IF_TRUE,
    W_OP_IN,
    W_OP_INIT_ARRAY,
    W_OP_INPUT,
    W_OP_INT,
    W_OP_INV,
    W_OP_LINE_INPUT,
    W_OP_METHOD,
    W_OP_METHOD_CALL,
    W_OP_MOD,
    W_OP_MUL,
    W_OP_NEGATE,
    W_OP_NEW,
    W_OP_NEW_TMP,
    W_OP_NOOP,
    W_OP_NOT,
    W_OP_OPEN,
    W_OP_OR,
    W_OP_OR_BITS,
    W_OP_POWER,
    W_OP_PRINT,
    W_OP_PRINT_VALUE,
    W_OP_RETURN_VALUE,
    W_OP_RETURN_SET_VALUE,
    W_OP_SHL,
    W_OP_SHR,
    W_OP_STRING,
    W_OP_SUB,
    W_OP_UNDEFINED,
    W_OP_VAR,
    W_OP_WHILE,
    W_OP_XOR
};

/* opcodes */
char *wOpcodeName[] = {
    "Undefined",
    "W_OP_ADD",
    "W_OP_AND",
    "W_OP_ARGLIST",
    "W_OP_ARRAY_GET",
    "W_OP_ARRAY_PTR",
    "W_OP_ARRAY_SET",
    "W_OP_ASSIGN",
    "W_OP_BUILTIN",
    "W_OP_BUILTIN_CALL",
    "W_OP_CASE_CMP",
    "W_OP_CASE_ELSE",
    "W_OP_CASE_RANGE",
    "W_OP_CASE_SELECT",
    "W_OP_CLASS_METHOD",
    "W_OP_CLASS_METHOD_CALL",
    "W_OP_CLOSE",
    "W_OP_CMP",
    "W_OP_COMMA",
    "W_OP_CONCAT",
    "W_OP_CONST_GET",
    "W_OP_CONST_Set",
    "W_OP_CONTINUE",
    "W_OP_DELETE",
    "W_OP_DESTROY",
    "W_OP_DIV",
    "W_OP_END",
    "W_OP_ERASE",
    "W_OP_EXIT_FOR",
    "W_OP_EXIT_ROUTINE",
    "W_OP_EXIT_WHILE",
    "W_OP_FLOAT",
    "W_OP_FOR",
    "W_OP_FOR_EACH",
    "W_OP_FOR_STEP",
    "W_OP_FUNCTION",
    "W_OP_FUNCTION_CALL",
    "W_OP_IDIV",
    "W_OP_IF",
    "W_OP_IF_TRUE",
    "W_OP_IN",
    "W_OP_INIT_ARRAY",
    "W_OP_INPUT",
    "W_OP_INT",
    "W_OP_INV",
    "W_OP_LINE_INPUT",
    "W_OP_METHOD",
    "W_OP_METHOD_CALL",
    "W_OP_MOD",
    "W_OP_MUL",
    "W_OP_NEGATE",
    "W_OP_NEW",
    "W_OP_NEW_TMP",
    "W_OP_NOOP",
    "W_OP_NOT",
    "W_OP_OPEN",
    "W_OP_OR",
    "W_OP_OR_BITS",
    "W_OP_POWER",
    "W_OP_PRINT",
    "W_OP_PRINT_VALUE",
    "W_OP_RETURN_VALUE",
    "W_OP_RETURN_SET_VALUE",
    "W_OP_SHL",
    "W_OP_SHR",
    "W_OP_STRING",
    "W_OP_SUB",
    "W_OP_UNDEFINED",
    "W_OP_VAR",
    "W_OP_WHILE",
    "W_OP_XOR"
};

void wStringCompare( int op, int popFlag );
void wNumberCompare( int op, int popFlag );
void wStringRangeCompare(void);
void wNumberRangeCompare(void);
void wEval( wNode *node );
