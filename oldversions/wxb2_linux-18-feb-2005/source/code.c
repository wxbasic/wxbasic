/*************************************************************
    Name:       code.c
    Purpose:    emit bytecodes
    Author:     David Cuny
    Copyright:  (c) 2002 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/

/* create holder for bytecodes */
wCode *wCodeNew()
{
    wCode *code;

    /* create it */
    code = (wCode *)wMalloc( sizeof( wCode ) );

    /* assign values */
    code->pcode = wGrowNew( 8 );
    code->backpatch = wGrowNew( 1 );

    return code;
}


/* free a chunk of code */
void wCodeFree( wCode *c )
{
    wMemTest( c, "wCodeFree:c" );

    wFree( c->pcode );
    wFree( c->backpatch );
    wFree( c );
}


/* insert a value into the code */
void wCodeEmit( wCode *code, int n )
{
    wMemTest( code, "wCodeEmit:code" );

    /* append the bytecode */
    wGrowAppend( code->pcode, n );
}


/* insert a bytecode into the code */
void wCodeEmitOp( wCode *code, int opcode )
{
    wMemTest( code, "wCodeEmitOp:code" );

    /* append the bytecode */
    wGrowAppend( code->pcode, opcode );
    code->last = opcode;
}

/* concat code, and free source */
void wCodeAppend( wCode *dst, wCode *src )
{
    int i, count;
    wGrow *backpatch;

    wMemTest( src, "wCodeAppend:src" );
    wMemTest( dst, "wCodeAppend:dst" );

    /* need to adjust backpatches */
    backpatch = src->backpatch;
    wMemTest( backpatch, "wCodeAppend:backpatch" );
    count = dst->pcode->count;

    /* fix backpatches in source */
    for ( i = 1; i <= backpatch->count; i++ ) {
        /* offset address */
        wGrowSet( backpatch, i, wGrowGet( backpatch, i ) + count );
    }        

    /* concat the bytecodes */
    wMemTest( dst->pcode, "wCodeAppend:dst->pcode" );
    wGrowConcat( dst->pcode, src->pcode );

    /* concat backpatches */
    wMemTest( dst->backpatch, "wCodeAppend:dst->backpatch" );
    wGrowConcat( dst->backpatch, src->backpatch );

    /* last code */
    dst->last = src->last;

    /* free the prior code segment */
    wCodeFree( src );
}



/* insert a number into the literal table, and emit bytecodes pointing to it */
void wCodeEmitNumber( wCode *code, wNumber n )
{
    wMemTest( code, "wCodeEmitNumber:code" );

    /* integer? */
    if (n == floor(n)) {
        wCodeEmitOp( code, W_OP_INTEGER );
        wCodeEmit( code, (int)n );

    } else {
        /* literal */
        wCodeEmitOp( code, W_OP_LITERAL );
        wCodeEmit( code, wLiteralAddNum( "", n ) );
    }
}


/* insert a string into the literal table, and emit bytecodes pointing to it */
void wCodeEmitString( wCode *code, char *s )
{
    wMemTest( code, "wCodeEmitString:code" );

    /* zero length string? */
    if (strlen( s ) == 0) {
        wCodeEmitOp( code, W_OP_EMPTYSTRING );

    } else {
        /* emit code */
        wCodeEmitOp( code, W_OP_LITERAL );
        wCodeEmit( code, wLiteralAddStr( "", s ) );
    }
}

/* insert an object into the literal table, and return it's index */
int wCodeAddObject( void *ptr )
{
    int i, count, length;
    return i;
}

/* return the index of a variable */
int wCodeGetVarIndex( wSymbol *s )
{
    int scope;

    wMemTest( s, "wCodeEmitVarSet:s" );

    scope = s->scope;

    /* global variable referenced in local scope? */
    if (scope == wTheGlobalScope && wTheCurrentScope != wTheGlobalScope) {
        return -s->stackPos;

    /* aliased variable? */
    } else if (s->alias) {
        return -wSymbolLookup( s->alias )->stackPos;

    } else {
        /* local */
        return s->stackPos;
    }
}


/* emit the index of a variable */
void wCodeEmitVarIndex( wCode *code, wSymbol *s )
{
    /* emit var index */
    wMemTest( s, "wCodeEmitVarSet:s" );
    wCodeEmit( code, wCodeGetVarIndex( s ) );
}

/* emit the variable */
void wCodeEmitVar( wCode *code, wSymbol *s )
{
    wMemTest( code, "wCodeEmitVar:code" );
    wMemTest( s, "wCodeEmitVar:s" );

    if (s->scope == wTheClassScope) {
        /* property */
        wCodeEmitOp( code, W_OP_PROP );
        wCodeEmit( code, s->stackPos );
    } else {
        /* normal variable */
        wCodeEmitOp( code, W_OP_VARIABLE );
        wCodeEmit( code, wCodeGetVarIndex( s ) );
    }
}


/* emit a call to a routine */
void wCodeEmitCall( wCode *code, wSymbol *s, int args, int returns )
{
    wMemTest( code, "wCodeEmitCall:code" );
    wMemTest( s, "wCodeEmitCall:s" );

    /* push the routine index onto the stack */
    wCodeEmitOp( code, W_OP_ROUTINE );
    wCodeEmit( code, s->index );

    /* call the routine */
    wCodeEmitOp( code, W_OP_CALL );
    wCodeEmit( code, args );
    wCodeEmit( code, returns );
}

/* emit an address that will be backpatched later */
void wCodeEmitForwardAddress( wCode *code, wGrow *stack, int index )
{
    int here;

    wMemTest( code, "wCodeEmitForwardAddress:code" );
    wMemTest( stack, "wCodeEmitForwardAddress:stack" );

    /* emit the label on the stack */
    wCodeEmit( code, wGrowPeek( stack, index ) );

    /* get address where label was placed */
    here = code->pcode->count;

    /* append it to the backpatch list */
    wGrowAppend( code->backpatch, here );
}

/* backpatch addresses on stack until -1 is found on stack */
void wCodeBackpatch( wCode *code, int fixLabel, int address )
{
    int i, at, label;
    wGrow *backpatch, *pcode;

    wMemTest( code, "wCodeBackpatch:code" );

    /* get the backpatch addresses and code */
    pcode = code->pcode;
    backpatch = code->backpatch;

    /* fix addresses last to first */
    for ( i = backpatch->count; i > 0; i-- ) {

        /* address to fix */
        at = wGrowGet( backpatch, i );

        /* label at that address */
        label = wGrowGet( pcode, at );

        /* label to backpatch? */
        if (label == fixLabel) {
            /* replace with relative address */
            wGrowSet( pcode, at, address-at );

            /* remove label from list */
            wGrowDelete( backpatch, i );
        }
    }
}


/* optionally insert a trace into the code of the current line */
void wCodeEmitTrace( wCode *code )
{
    wMemTest( code, "wCodeEmitTrace:code" );

    if (wTheTraceOpFlag) {
        wCodeEmitOp( code, W_OP_TRACE );
        wCodeEmit( code, wReadLine );
    }
}


/* return address of next bytecode */
int wCodeHere( wCode *code )
{
    wMemTest( code, "wCodeHere:code" );

    return (code->pcode->count)+1;
}

/* push for a single stack */
void wCodePushLabel( wGrow *stack )
{
    wMemTest( stack, "wCodePushLabel:stack" );

    wTheNextLabel -= 1;
    wGrowAppend( stack, wTheNextLabel );
}


/* append local typecasts to the code */
wCode *wCodeAddTypeCast( wCode *code, int theScope, int traceLine )
{
    int count, i;
    wSymbol *parent, *child;
    wCode *newCode;

    wMemTest( code, "wCodeAddTypeCast:code" );

    /* look up the scope */
    parent = wSymbolLookup( theScope );


    /* get the count of the locals */
    count = parent->children->count;


    /* no locals? */
    if (count == 0) {
        return code;
    }


    /* holds new code */
    newCode = wCodeNew();


    /* set trace? */
    if (wTheTraceFlag) {
        wCodeEmitOp( newCode, W_OP_TRACE );
        wCodeEmit( newCode, traceLine );
    }


    /* scan through local variables */
    for ( i = count; i > 0; i-- ) {
        /* get the symbol for the local */
        child = wSymbolGetChild( parent, i );
        /* does it have a typecast? */
        if (child->typeCast != W_TYPE_VARIANT) {
            /* emit SETTYPE */
            wCodeEmit( newCode, W_OP_SETTYPE );
            wCodeEmit( newCode, i );
            wCodeEmit( newCode, child->typeCast );
        }
    }


    /* prepend the typecast code */
    wCodeAppend( newCode, code );

    return newCode;
}

