/*************************************************************
    Name:       code.h
    Purpose:    emit bytecodes
    Author:     David Cuny
    Copyright:  (c); 2002 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/


/* bytecode array */
struct wCode {
    int last;           /* value of last opcode added */
    wGrow *pcode;       /* bytecode array */
    wGrow *backpatch;   /* list of addresses to backpatch */
};


wCode *wCodeNew( void );
void wCodeFree( wCode *c );
void wCodeEmit( wCode *code, int n );
void wCodeEmitOp( wCode *code, int opcode );
void wCodeAppend( wCode *dst, wCode *src );
void wCodeEmitNumber( wCode *bytecodes, wNumber n );
void wCodeEmitString( wCode *bytecodes, char *s );
int wCodeGetVarIndex( wSymbol *s );
void wCodeEmitVarIndex( wCode *bytecodes, wSymbol *s );
void wCodeEmitVar( wCode *bytecodes, wSymbol *s );
void wCodeEmitCall( wCode *bytecodes, wSymbol *s, int args, int returns );
void wCodeEmitForwardAddress( wCode *code, wGrow *stack, int index );
void wCodeBackpatch( wCode *bytecodes, int fixLabel, int address );
void wCodeEmitTrace( wCode *bytecodes );
int wCodeHere( wCode *bytecodes );
void wCodePushLabel( wGrow *stack );
wCode *wCodeAddTypeCast( wCode *code, int theScope, int traceLine );
