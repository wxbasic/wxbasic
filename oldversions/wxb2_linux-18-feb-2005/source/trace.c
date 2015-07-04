/*************************************************************
    Name:       trace.c
    Purpose:    debugging routines
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/



char *wTraceStackShowItem( int index )
{
	char *buffer;

    /* FIXME: check stack height */
    if (index < 0 || index > wTheStack->count) {
        wErrorThrow( W_ERROR_INTERNAL,
            "Stack index error: %s (wTraceStackShowItem)", index );
    }

	/* convert to char */
    return wVariantToChar( wStackItem(index), showQuotes, 0 );
}


void wTraceDumpStack() {
    /* print data on stack */
    count = wTheStack->count;
    if (count != 0) {
        wConsolePrint("Stack:");
        for( i = 1; i <= count; i++ ) {
            wConsolePrintf("[%d:", i );
            wVariantPrint( wStackItem(i), W_TRUE );
            wConsolePrint("] ");
        }
        wConsolePrint("\n");
        fflush(stdout);
    }
}

void wTraceDumpLocals() {

    /* get symbol of current routine on callstack */
    wSymbol *sRoutine = wTheCall->routine;

    /* iterate through the locals */
    int count = sRoutine->children->count;
    if (count != 0) {
        wConsolePrint("Locals:\n");
        for( i = 1; i <= count; i++ ) {
            /* name of local */
            wConsolePrintf("    %s:", wVmVariableName( sRoutine, i ) );
    
            /* value */
            wVariantPrint( wVmGetVariable( i ), W_TRUE );
            wConsolePrint("\n");
        }
        wConsolePrint("\n");
    }
    fflush(stdout);


/* print trace information for the current bytecode */
void wVmTrace( wSymbol *sRoutine, int *pcode, int pc )
{
    int opcode, count, i;

    /* get the opcode */
    opcode = pcode[pc];

    /* print the opcode */
    wConsolePrintf("Current opcode: opcode #%d->%d\n", pc, opcode );
    fflush(stdout);
    wVmDecompileOp( sRoutine, pcode, pc );

}

