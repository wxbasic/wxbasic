/*************************************************************
    Name:       vm.h
    Purpose:    virtual machine
    Author:     David Cuny
    Copyright:  (c) 2002 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/

#ifndef WXBASIC_VM_DECLARES
#define WXBASIC_VM_DECLARES

/* opcodes */
enum {
    W_OP_UNDEFINED = 0,     /* error, undefined op */
    W_OP_NOOP,              /* no op */
    W_OP_TRACE,             /* trace */
    W_OP_HALT,              /* halt execution */
    W_OP_END,               /* end of code */
    W_OP_DROP,              /* drop stack item */
    W_OP_MISSING,           /* return true if parm not passed in list */
    W_OP_FIRSTTIME,         /* return true if first time running routine */

    /* push constant values onto the stack */
    W_OP_NOTHING,           /* push undefined value onto the stack */
    W_OP_LITERAL,           /* push a literal onto the stack */
    W_OP_EMPTYSTRING,       /* push an empty string onto the stack */
    W_OP_INTEGER,           /* push following integer onto the stack */

    /* for loop */
    W_OP_FORPREP,           /* set up for loop */
    W_OP_FORPREP1,          /* set up for loop, no step */
    W_OP_FORSTEP,           /* increment for loop */
    W_OP_FORSTEP1,          /* increment for loop by 1 */
    W_OP_FOREACHPREP,       /* for each test */
    W_OP_FOREACHLOOP,       /* for increment for each loop */

    /* routine calls */
    W_OP_ROUTINE,           /* push routine id onto stack */
    W_OP_CALL,              /* call a routine */
    W_OP_RETURN,            /* return from a call */

    /* input/output */
    W_OP_FILECLOSE,         /* close file */
    W_OP_FILECLOSEALL,      /* close all files */
    W_OP_FILEOPEN,          /* open a file */
    W_OP_FILEREAD,          /* read a line from the file */
    W_OP_READ,              /* read from stdin */
    W_OP_REDIRECT,          /* redirect output of print */
    W_OP_STDIO,             /* redirect back to standard i/o */
    W_OP_PRINT,             /* print a value */
    W_OP_PRINTLN,           /* print a linefeed */
    W_OP_PRINTTAB,          /* print with trailing space */
    W_OP_EMITTAB,           /* print a space, no data */
    W_OP_EMITLN,            /* print a linefeed, no data */
    
    /* jumps */
    W_OP_JMP,               /* unconditional jump */
    W_OP_JMPT,              /* jump on true */
    W_OP_JMPF,              /* jump on false */
    W_OP_JMPONT,            /* jump on true, drop if false */
    W_OP_JMPONF,            /* jump on false, drop if true */

    /* subroutines */
    W_OP_JSR,               /* jump to a subroutine */
    W_OP_RET,               /* exit from subroutine */

    /* exception handling */
    W_OP_STARTCATCH,        /* push catch address onto the catch stack */
    W_OP_ENDCATCH,          /* pop catch address off the catch stack, jump */
    W_OP_JMPCATCHF,         /* jump if expression is not exception */
    W_OP_THROW,             /* throw an exception */
    W_OP_RETHROW,           /* pop catch and rethrow current exception */
    W_OP_EXCEPTION,         /* push exception onto stack */

    /* class related */
    W_OP_DTOR,              /* object destructor */
    W_OP_DELETE,            /* delete an object */
    W_OP_VIRTUAL,           /* resolve a virtual method */
    W_OP_MYVIRTUAL,         /* resolve virtual method with Me */
    W_OP_CALLMETHOD,        /* call method with object on stack*/
    W_OP_CALLMYMETHOD,      /* call method belonging to Me */
    W_OP_NEW,               /* call to new */
    W_OP_NEWTEMP,           /* call to new, create on stack */

    /* math ops */
    W_OP_POWER,             /* power */
    W_OP_NEGATE,            /* negate value */
    W_OP_ADD,               /* addition */
    W_OP_SUB,               /* subtraction */
    W_OP_MUL,               /* multiplication */
    W_OP_DIV,               /* division */
    W_OP_IDIV,              /* integer division */
    W_OP_MOD,               /* modulus */
    W_OP_SHL,               /* bitwise left shift */
    W_OP_SHR,               /* bitwise right shift */
    W_OP_INV,               /* inverse */
    W_OP_CONCAT,            /* string concatenation */
    W_OP_OR_BITS,           /* bitwise or */
    W_OP_AND_BITS,          /* bitwise and */
    W_OP_ADD_SET ,          /* increment lval */
    W_OP_SUB_SET ,          /* decrement lval */
    W_OP_MUL_SET ,          /* multiply lval */
    W_OP_DIV_SET ,          /* divide lval */
    W_OP_IDIV_SET ,         /* integer divide lval */
    W_OP_MOD_SET ,          /* mod lval */
    W_OP_CONCAT_SET ,       /* concat lval */
    
    /* tests */
    W_OP_EQ,                /* equality */
    W_OP_NE,                /* inequality */
    W_OP_LT,                /* less than */
    W_OP_LE,                /* less or equal than */
    W_OP_GT,                /* greater than */
    W_OP_GE,                /* greater or equal than */
    W_OP_NOT,               /* logical not */
    W_OP_DUP,               /* duplicate stack value */
    W_OP_AND,               /* logical and */
    W_OP_OR,                /* logical or */
    W_OP_XOR,               /* logical exclusive or */

    /* case tests */
    W_OP_CASERANGE,         /* range of case values */
    W_OP_CASE,              /* case test */

    W_OP_IN,                /* element is in array */

    /* arrays */
    W_OP_CREATEARRAY,       /* create an indexed array */
    W_OP_INITARRAY,         /* create an array with default values */
    W_OP_ERASEARRAY,        /* reset array back to default values */

    /* tables */
    W_OP_CREATETABLE,       /* create a table */
    W_OP_SETLIST,           /* copy items from stack into table */
    W_OP_SETMAP,            /* map keys and values into table */

    /* lists */
    W_OP_CREATELIST,        /* create a list */
    W_OP_GETSLICE,          /* return a slice from a list */
    W_OP_SETSLICE,          /* set a slice in a list */

    /* variables */
    W_OP_FREE,               /* set variable to undefined */

    /* accessing values */
    W_OP_VARIABLE,          /* return pointer to variable */
    W_OP_INDEX,             /* return pointer to value at index position */
    W_OP_PROP,              /* return pointer to property by index */
    W_OP_PROPBYNAME,        /* return pointer to property by name */
    W_OP_ME,                /* return pointer to current object */

    /* modifiers */
    W_OP_GET,               /* put value of pointer onto stack */
    W_OP_SET,               /* store value on stack into pointer */
    W_OP_LVAL,              /* put pointer on stack */
    W_OP_SETTYPE,           /* set datatype for variable */

    /* callbacks */
    W_OP_HANDLES,            /* set a callback for an object */
    W_OP_HANDLESID           /* set a callback for an object with an id */
};

/* opcode names */
char *wOpcodeName[] = {
    "UNDEFINED",         /* no such op */
    "NOOP",              /* no op */
    "TRACE",             /* trace */
    "HALT",              /* halt execution */
    "END",               /* end of code */
    "DROP",              /* drop stack item */
    "MISSING",           /* return true if parm not passed in list */
    "FIRSTTIME",         /* return true if function has not been called before */
    "NOTHING",           /* push undefined value onto the stack */
    "LITERAL",           /* push a literal onto the stack */
    "EMPTYSTRING",       /* push an empty string onto the stack */
    "INTEGER",           /* push following integer onto the stack */
    "FORPREP",           /* set up for loop */
    "FORPREP1",          /* set up for loop", no step */
    "FORSTEP",           /* increment for loop */
    "FORSTEP1",          /* increment for loop by 1 */
    "FOREACHPREP",       /* for each test */
    "FOREACHLOOP",       /* for increment for each loop */
    "ROUTINE",           /* push routine id onto stack */
    "CALL",              /* call a routine */
    "RETURN",            /* return from a call */
    "FILECLOSE",         /* close file */
    "FILECLOSEALL",      /* close all files */
    "FILEOPEN",          /* open a file */
    "FILEREAD",          /* read a line from the file */
    "READ",              /* read from stdin */
    "REDIRECT",          /* redirect output of print */
    "STDIO",             /* redirect back to standard i/o */
    "PRINT",             /* print a value */
    "PRINTLN",           /* print a linefeed */
    "PRINTTAB",          /* print with trailing space */
    "EMITTAB",           /* print a space", no data */
    "EMITLN",            /* print a linefeed", no data */
    "JMP",               /* unconditional jump */
    "JMPT",              /* jump on true */
    "JMPF",              /* jump on false */
    "JMPONT",            /* jump on true", drop if false */
    "JMPONF",            /* jump on false", drop if true */
    "JSR",               /* jump to a subroutine */
    "RET",               /* exit from subroutine */
    "STARTCATCH",        /* push catch address onto the catch stack */
    "ENDCATCH",          /* pop catch address off the catch stack", jump */
    "JMPCATCHF",         /* jump if expression is not exception */
    "THROW",             /* throw an exception */
    "RETHROW",           /* pop catch and rethrow current exception */
    "EXCEPTION",         /* push exception onto stack */
    "DTOR",              /* object destructor */
    "DELETE",            /* delete an object */
    "VIRTUAL",           /* resolve a virtual method */
    "MYVIRTUAL",         /* resolve virtual method with Me */
    "CALLMETHOD",        /* call method with object on stack*/
    "CALLMYMETHOD",      /* call method belonging to Me */
    "NEW",               /* call to new */
    "NEWTEMP",           /* call to new", create on stack */
    "POWER",             /* power */
    "NEGATE",            /* negate value */
    "ADD",               /* addition */
    "SUB",               /* subtraction */
    "MUL",               /* multiplication */
    "DIV",               /* division */
    "IDIV",              /* integer division */
    "MOD",               /* modulus */
    "SHL",               /* bitwise left shift */
    "SHR",               /* bitwise right shift */
    "INV",               /* inverse */
    "CONCAT",            /* string concatenation */
    "OR_BITS",           /* bitwise or */
    "AND_BITS",          /* bitwise and */
    "ADD_SET ",          /* increment lval */
    "SUB_SET ",          /* decrement lval */
    "MUL_SET ",          /* multiply lval */
    "DIV_SET ",          /* divide lval */
    "IDIV_SET ",         /* integer divide lval */
    "MOD_SET ",          /* mod lval */
    "CONCAT_SET ",       /* concat lval */
    "EQ",                /* equality */
    "NE",                /* inequality */
    "LT",                /* less than */
    "LE",                /* less or equal than */
    "GT",                /* greater than */
    "GE",                /* greater or equal than */
    "NOT",               /* logical not */
    "DUP",               /* duplicate stack value */
    "AND",               /* logical and */
    "OR",                /* logical or */
    "XOR",               /* logical exclusive or */
    "CASERANGE",         /* range of case values */
    "CASE",              /* case test */
    "IN",                /* element is in array */
    "CREATEARRAY",       /* create an indexed array */
    "INITARRAY",         /* create an array with default values */
    "ERASEARRAY",        /* reset array back to default values */
    "CREATETABLE",       /* create a table */
    "SETLIST",           /* copy items from stack into table */
    "SETMAP",            /* map keys and values into table */
    "CREATELIST",        /* create a list */
    "GETSLICE",          /* return a slice from a list */
    "SETSLICE",          /* set a slice in a list */
    "FREE",               /* set variable to undefined */
    "VARIABLE",          /* return pointer to variable */
    "INDEX",             /* return pointer to value at index position */
    "PROP",              /* return pointer to property by index */
    "PROPBYNAME",        /* return pointer to property by name */
    "ME",                /* return pointer to current object */
    "GET",               /* put value of pointer onto stack */
    "SET",               /* store value on stack into pointer */
    "LVAL",              /* put pointer on stack */
    "SETTYPE",           /* set datatype for variable */
    "HANDLES",           /* set a callback for an object */
    "HANDLESID",         /* set a callback for an object with an ID */

};



wVariant *wVmGetVariable( int index );
char *wVmVariableName( wSymbol *s, int index );
void wVmTypeCast( wVariant *variant );
void wVmExecute( wSymbol *sRoutine );
void wVmDecompile( wSymbol *sRoutine );
int wVmDecompileOp( wSymbol *sRoutine, int *pcode, int pc );
void wVmDecompileAll( void );
void wVmOpFormat( int pc, int opcode, int args, int arg1, int arg2, int arg3, char *commentFmt, ... );

#endif
