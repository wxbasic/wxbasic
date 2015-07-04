/*************************************************************
    Name:       trace.c
    Purpose:    debugging routines
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/

void wTraceOpToConsole() {

    /* choose the format based on the number of args */
    switch (wTheOpArgCount) {
    case 0:
        /* no args */
        wConsolePrintf( "%-4d \t%-16s%3d             ; %s\n", wTheOpPC, wOpcodeName[wTheOpCode], wTheOpCode, wTheOpComment );
        break;
    case 1:
        /* one arg */
        wConsolePrintf( "%-4d \t%-16s%3d %3d         ; %s\n", wTheOpPC, wOpcodeName[wTheOpCode], wTheOpCode, wTheOpArg1, wTheOpComment );
        break;
    case 2:                  
        wConsolePrintf( "%-4d \t%-16s%3d %3d %3d     ; %s\n", wTheOpPC, wOpcodeName[wTheOpCode], wTheOpCode, wTheOpArg1, wTheOpArg2, wTheOpComment );
        break;
    case 3:
        wConsolePrintf( "%-4d \t%-16s%3d %3d %3d %3d ; %s\n", wTheOpPC, wOpcodeName[wTheOpCode], wTheOpCode, wTheOpArg1, wTheOpArg2, wTheOpArg3, wTheOpComment );
        break;
    }

}


#ifdef __WXWIN__
/* GUI version of trace */
void wTrace( int lineNumber )
{
    int i;    

    /* wait */
    wTheTraceWaitFlag = W_TRUE;

    /* no trace window? */
    if (wTraceWindow == NULL) {
        /* create the trace window */
        wTraceWindow = new wTraceWindowClass();        
    }

    /* point to the line of code being executed */
    wTraceWindow->GotoLine( lineNumber );

    /* clear the variable list */
    wTraceWindow->variableList->DeleteAllItems();

    /* get the active tab */
    int activeTab = wTraceWindow->notebook->GetSelection();

    /* hide the list during the inserts */
    wTraceWindow->variableList->Hide();

    /* get symbol of current routine on callstack */
    wSymbol *sRoutine = wTheCall->routine;

    /* iterate through the locals */
    int count = sRoutine->children->count;
    for( i = 1; i <= count; i++ ) {

        /* get the name */
        char *name = wVmVariableName( sRoutine, i );

        /* get the value */
        wVariant *value = wVmGetVariable( i );

        /* convert the value to a string */
        char *buffer = wVariantToChar( value, W_TRUE, W_INBUFFER_MAX );

        /* add the name and value to the list */
        wTraceWindow->AddVariable( name, buffer );

        wFree( buffer );
    }

    /* show the list inserts */
    wTraceWindow->variableList->Show();

    /* restore the active tab */
    wTraceWindow->notebook->SetSelection(activeTab);

}

#else
/* console version of trace */
void wTrace( int lineNumber ) {

    int i, count;
    wSymbol *sRoutine;

    wConsolePrintf( "TRACE: %-16s:%-04d %s",
        wSourceGet( lineNumber )->fileName,
        wSourceGet( lineNumber )->lineNum,
        wSourceGet( lineNumber )->text );

    /* get symbol of current routine on callstack */
    sRoutine = wTheCall->routine;

    /* iterate through the locals */
    count = sRoutine->children->count;
    for ( i = 1; i <= count; i++ ) {

        /* get the name */
        char *name = wVmVariableName( sRoutine, i );

        /* get the value */
        wVariant *value = wVmGetVariable( i );

        /* print name of local */
        wConsolePrintf("    %s:", name );

        /* print value */
        wVariantPrint( value, W_TRUE );
        wConsolePrint("\n");
    }

    /* print an extra line */
    wConsolePrint("\n");
    fflush(stdout);
}
#endif


#ifdef __WXWIN__
/* GUI version of wTraceDebug */
void wTraceDebug()
{

    int count, i;
    char *buffer = wCharMalloc( W_INBUFFER_MAX );

    /* wait after displaying information */
    wTheTraceWaitFlag = W_TRUE;

    /* no trace window? */
    if (wTraceWindow == NULL) {
        /* create the trace window */
        wTraceWindow = new wTraceWindowClass();        
    }

    /* get the active tab */
    int activeTab = wTraceWindow->notebook->GetSelection();

    /* clear the stack list */
    wTraceWindow->stackList->DeleteAllItems();

    /* hide the lists during the inserts */
    wTraceWindow->stackList->Hide();
    wTraceWindow->variableList->Hide();

    /* opcode information */
    wTraceWindow->AddStack( "Opcode", wOpcodeName[wTheOpCode] );
    wTraceWindow->AddStack( "Details", wTheOpComment );

    /* arg1 ? */
    if (wTheOpArgCount > 0) {
        sprintf( buffer, "%d", wTheOpArg1 );
        wTraceWindow->AddStack( "Arg1", buffer );
    }

    /* arg2 */
    if (wTheOpArgCount > 1) {
        sprintf( buffer, "%d", wTheOpArg2 );
        wTraceWindow->AddStack( "Arg2", buffer );

    }

    /* arg3 */
    if (wTheOpArgCount > 2) {
        sprintf( buffer, "%d", wTheOpArg3 );
        wTraceWindow->AddStack( "Arg3", buffer );
    }

    /* values on the stack */
    for ( i = 1; i < wTheStack->count; i++ ) {

        /* title */
        sprintf( buffer, "Stack[ %d ]", i );

        /* convert the value to a string */
        char *string = wVariantToChar( wStackItem(i), W_TRUE, W_INBUFFER_MAX );

        /* add the name and value to the list */
        wTraceWindow->AddStack( buffer, string );

        /* free the item */
        wFree( string );
    }

    /* get the current routine */
    wSymbol *sRoutine = wTheCall->routine;

    /* count the children */
    count = sRoutine->children->count;

    /* iterate through the locals */
    for ( i = 1; i <= count; i++ ) {

        /* get the name */
        char *name = wVmVariableName( sRoutine, i );

        /* get the value */
        wVariant *value = wVmGetVariable( i );

        /* convert the value to a string */
        char *string = wVariantToChar( value, W_TRUE, W_INBUFFER_MAX );

        /* add the name and value to the list */
        wTraceWindow->AddVariable( name, string );

        /* free the buffer */
        wFree( string );

    }

    wFree( buffer );

    /* show the items */
    wTraceWindow->stackList->Show();
    wTraceWindow->variableList->Show();

    /* restore the active tab */
    wTraceWindow->notebook->SetSelection(activeTab);

}

#else

/* console version of debug */
void wTraceDebug()
{
    int count, i;
    wSymbol *sRoutine;

    /* flush the buffer, in case of a crash */
    fflush(stdout);

    /* print stack results from prior operation */
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

    /* write to the console */
    wTraceOpToConsole();

    /* get the currently running routine */
    sRoutine = wTheCall->routine;

    /* count the children */
    count = sRoutine->children->count;

    /* dump the locals */
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
}
#endif


void wTraceRun() {
    /* don't stop until next break */
    wTheTraceGotoNextBreak = W_TRUE;

    /* stop waiting */
    wTheTraceWaitFlag = 0;
}

void wTraceStop() {
    /* set the halt flag to true */
    wTheHaltFlag = W_TRUE;

    /* stop waiting */
    wTheTraceWaitFlag = W_FALSE;
}

void wTraceStepInto() {
    /* turn on trace down flag */
    wTheTraceDownFlag = W_TRUE;

    /* stop waiting */
    wTheTraceWaitFlag = W_FALSE;
}

void wTraceStepOver() {
    /* zap the trace down flag */
    wTheTraceDownFlag = W_FALSE;

    /* stop waiting */
    wTheTraceWaitFlag = W_FALSE;
}

void wTraceStepOut() {
    /* kill tracing at this level */
    wTheTraceOnFlag = W_FALSE;

    /* zap trace into */
    wTheTraceDownFlag = W_FALSE;

    /* restore tracing at prior level */
    wTheTraceUpFlag = W_TRUE;

    // stop waiting
    wTheTraceWaitFlag = W_FALSE;
}

