/*************************************************************
    Name:       vm.c
    Purpose:    virtual machine
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/

/* initialize the return stack */
void wVmInit()
{
    wTheSubroutineStack  = wGrowNew( 10 );
}


/* return address of variant at stack position. Negative indices are globals */
wVariant *wVmGetVariable( int index )
{
    if (index < 0) {
        /* global variable */
        index = -index;
        return &(wTheGlobal->local[index-1]);
    } else {
        return &(wTheCall->local[index-1]);
    }                
}

/* return the name of the variable. Negative indices are globals */
char *wVmVariableName( wSymbol *sRoutine, int index )
{
    wSymbol *scope;
    /* global or local? */
    if (index < 0) {
        /* use the global scope */
        scope = wSymbolLookup( wTheGlobalScope );

        /* remove bias */
        index = -index;

    } else {
        /* use the current scope */
        scope = sRoutine;
    }
    return wSymbolGetChild( scope, index )->name;
}


/* ensure the variable is being assigned to the right type */
void wVmTypeCast( wVariant *variant )
{
    int castToClass, castDataType;

    /* get class index to cast to */
    castToClass = variant->typeCast;

    /* no cast? */
    if ((castToClass == 0)
    || (variant->dataType == W_TYPE_NOTHING)){
        return;
    }

    /* builtin? */
    if (castToClass <= wTheLastBuiltinTypeIndex) {

        /* get the native datatype */
        castDataType = wTheClassIndexToDataType[castToClass];

        /* skip if typecast is Variant or data is Nothing or already matches */
        if ( castDataType == variant->dataType
        ||   castDataType == W_TYPE_VARIANT
        ||   castDataType == W_TYPE_NOTHING ) {
            /* nothing to do */
            return;
        }

        /* coerce it, if possible */
        wVariantCoerce( variant, castDataType );

    /* not a native datatype */
    } else {

        /* not an object? */
        if (variant->dataType != W_TYPE_OBJECT) {
            wErrorThrow( W_ERROR_CONVERT, "Can't convert %s to %s",
                wDataTypeName[variant->dataType],
                wSymbolLookup( castToClass )->name );
        }
    
        /* not the right object? */
        if (!wSymbolInherits( variant->value.object->klass, castToClass )) {
            wErrorThrow( W_ERROR_CONVERT, "Can't convert %s to %s",
                variant->value.object->klass->name,
                wSymbolLookup( castToClass )->name );
        }
    }
}


/* print trace information for the current bytecode */
void wVmTrace( wSymbol *sRoutine, int *pcode, int pc )
{
    int opcode, count, i;

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

    /* get the opcode */
    opcode = pcode[pc];

    /* print the opcode */
    wVmDecompileOp( sRoutine, pcode, pc );

    /* dump the locals */
    count = sRoutine->children->count;
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


void wVmExecute( wSymbol *sRoutine )
{
    int opcode, pc, arg1, arg2, arg3, i, j, flag, modifier;
    wNumber n1, n2, n3;
    wVariant *v1, *v2, *v3, *v4, *lval;
    int *pcode;
    wString *aString;
    wGrow *code;
    wArray *array;
    wGrow *table;
    wGrow *list;
    wSymbol *s, *klass;
    wObject *o;
    wCatch *aCatch;
#ifdef __WXWIN__
    wxWindow *topWindow;
#endif

    code = sRoutine->pcode;
    if (code == NULL) {
        wErrorThrow( W_ERROR_INTERNAL, "Routine %s has no bytecodes (wRunCode)", sRoutine->name );
    }
	
    /* get the code section */
    pcode = (int *)code->value;
    pc = 0;

    /* turn off modifier flag */
    modifier = 0;

    /* turn off halt flag */
    wTheHaltFlag = W_FALSE;

    /* main loop */
    while (!wTheHaltFlag) {

        /* check limits */
        if (pc < 0 || pc > code->count) {
            wErrorThrow( W_ERROR_INTERNAL, "Program counter out of bounds at %d running %s (wRunCode)",
                pc, sRoutine->name );
        }
        opcode = pcode[pc];


        /* debugging prints the stack and opcode */
        if (wTheDebugFlag) {
            wVmTrace( sRoutine, pcode, pc );
        }

        switch (opcode) {
        case W_OP_EQ:
        case W_OP_NE:

            v2 = wStackPop();
            wMemTest( v2, "BINOP v2" );

            v1 = wStackPop();
            wMemTest( v1, "BINOP v1" );

            n1 = wVariantEqual( v1, v2 );
            wVariantDeref( v1 );
            wVariantDeref( v2 );

            /* reverse result for not equal */
            if (opcode == W_OP_NE) {
                n1 = !n1;
            }

            /* put the result onto the stack */
            wStackPushNumber( n1 );
            
            break;

        case W_OP_GT:
        case W_OP_LT:
        case W_OP_GE:
        case W_OP_LE:
            v2 = wStackPop();
            wMemTest( v2, "BINOP v2" );

            v1 = wStackPop();
            wMemTest( v1, "BINOP v1" );

            arg1 = wVariantCompare( v1, v2 );
            wVariantDeref( v1 );
            wVariantDeref( v2 );

            switch (opcode) {
            case W_OP_GT:
                wStackPushNumber( arg1 > 0 );
                break;
            case W_OP_LT:
                wStackPushNumber( arg1 < 0 );
                break;
            case W_OP_GE:
                wStackPushNumber( arg1 >= 0 );
                break;
            case W_OP_LE:
                wStackPushNumber( arg1 <= 0 );
                break;
            }

            break;

        case W_OP_ADD:
            /* add two values on the stack */
            v1 = wStackPop();
            wMemTest( v1, "ADD v1" );

            v2 = wStackPop();
            wMemTest( v2, "ADD v2" );

            /* add two numbers */
            n1 = wVariantGetNumber( v2 ) + wVariantGetNumber( v1 );

            wVariantDeref( v1 );
            wVariantDeref( v2 );
            wStackPushNumber( n1 );

            break;

        case W_OP_CALL:
            /* pop routine id off the stack */
            v1 = wStackPop();
            if (v1->dataType != W_TYPE_ROUTINE) {
                wErrorThrow( W_ERROR_INTERNAL, "Expected a routine, not %s",
                    wDataTypeName[v1->dataType] );
                break;
            }
            s = v1->value.routine;

            arg2 = pcode[++pc];     /* the parameter count */
            arg3 = pcode[++pc];     /* the return count */

            wCallRoutine( s, arg2, arg3, NULL, NULL );

            break;

        case W_OP_CASE:
            /* get variable index and jump address */
            arg1 = pcode[++pc];
            arg2 = pcode[++pc];

            /* get the variable */
            v1 = wVmGetVariable( arg1 );
            wMemTest( v1, "CASE v1" );

            /* get value to compare to */
            v2 = wStackPop();
            wMemTest( v2, "CASE v2" );

            /* do the comparison */
            if (wVariantCompare( v1, v2 ) == 0) {
                /* jump */
                pc += arg2 - 1;
            }
            /* 

            /* deref the value on the stack, but not the case variable */
            wVariantDeref( v2 );

            break;


        case W_OP_CASERANGE:
            /* get variable index and jump address */
            arg1 = pcode[++pc];
            arg2 = pcode[++pc];

            /* get the variable */
            v1 = wVmGetVariable( arg1 );
            wMemTest( v1, "CASERANGE v1" );

            /* get the low range off the stack */
            v2 = wStackPop();
            wMemTest( v2, "CASERANGE v2" );

            /* get the high range off the stack */
            v3 = wStackPop();
            wMemTest( v3, "CASERANGE v3" );

            /* compare range */
            if (wVariantCompare( v3, v1 ) != 1) {
                if (wVariantCompare( v2, v1 ) != -1) {
                    /* set jump */
                    pc += arg2 - 1;
                }
            }

            /* deref the variables, but not the case variable */
            wVariantDeref( v2 );
            wVariantDeref( v3 );

            break;


        case W_OP_CONCAT:
            /* get source string, don't deref */
            v1 = wStackPopString();
            wMemTest( v1, "CONCAT v1" );

            /* get destination string, leave on stack */
            v2 = wStackPeek(0);
            wMemTest( v2, "CONCAT v2" );
            wVariantCoerce( v2, W_TYPE_STRING );

            /* concat them */
            wStringConcat( v2, v1 );

            /* deref the source, but not the destination */
            wVariantDeref( v1 );

            break;

        case W_OP_CREATEARRAY:
            /* count of indexes */
            arg1 = pcode[++pc];

            /* index ranges on stack, so can't pass destination */
            array = wArrayCreate( arg1, NULL );
            wMemTest( array, "CREATEARRAY array" );

            /* set the array on the stack */
            v1 = wStackPushNothing();
            wMemTest( v1, "CREATEARRAY v1" );

            v1->dataType = W_TYPE_ARRAY;
            v1->value.array = array;

            break;

        case W_OP_CREATELIST:
            arg1 = pcode[++pc];
            v1 = wStackPushNothing();
            wMemTest( v1, "CREATELIST v1" );
            wListNew( v1, arg1 );
            break;

        case W_OP_CREATETABLE:
            v1 = wStackPushNothing();
            wMemTest( v1, "CREATETABLE v1" );
            wTableNew( v1 );
            break;

        case W_OP_DIV:
            /* divide two values on the stack */
            n1 = wStackPopNumber();
            n2 = wStackPopNumber();

            /* check for division by zero */
            if (n1 == 0 ) {
                wErrorThrow( W_ERROR_MATH, "Division by zero" );
                break;
            }

            wStackPushNumberFromRoutine( n2/n1, "Divide" );
            break;

		case W_OP_DROP:
            /* drop items from the stack */
            arg1 = pcode[++pc];
            wStackDrop( arg1 );
			break;

        case W_OP_DTOR:
			/* object destructor */

            /* get the value */
            v1 = wStackPop();

            /* not an object? */
            if (v1->dataType != W_TYPE_OBJECT) {
                wErrorThrow( W_ERROR_CONVERT, "Not an object" );
            }
    
            /* get the class */
            klass = v1->value.object->klass;

            /* lookup the "del" method */
            s = wSymbolFindMethodChar( klass, "finalize" );
            if (s == NULL) {
                wErrorThrow( W_ERROR_NOSUCH, "%s.finalize() not found", klass->name );
            }


            /* native (user defined?) */
            if (klass->flags && W_SYM_ISNATIVE) {
                wErrorThrow( W_ERROR_NOSUCH, "DTOR for user classes not yet implemented" );

            } else {
                // get the object
                o = v1->value.object;
                wMemTest( o, "DTOR o" );

                /* run the method */
                wCallRoutine( s, 0, 0, o, NULL );

            }

			break;
		
        case W_OP_EMITLN:
            wConsolePrint( "\n" );
            break;

        case W_OP_EMITTAB:
            wConsolePrint( " " );
            break;

		case W_OP_EMPTYSTRING:
			/* push an empty string onto the stack */
            v1 = wStackPushNothing();
            wMemTest( v1, "EMPTYSTRING v1" );

            wStringNew( v1, NULL, 0 );
			break;

        case W_OP_END:
            /* end of code encountered */
#ifdef __WXWIN__
            /* enter mainloop? */
            topWindow = wxGetApp().GetTopWindow();
            if (topWindow) {
                /* need to show it? */
                if (!topWindow->IsShown()) {
                    topWindow->Show(W_TRUE);
                }
                /* call mainloop */
                wxGetApp().MainLoop();
            }
#endif
            /* halt */
            wTheHaltFlag = W_TRUE;
            break;

        case W_OP_ENDCATCH:
            /* get the address to jump to */
            arg1 = pcode[++pc];

            /* drop the data from the catch stack */
            wFree( (void *)wGrowPop( wTheCatchStack ));

			/* +1 accounts for auto increment of pc */
            pc += arg1 - 1;

            break;

        case W_OP_ERASEARRAY:
            /* get the top of stack */
            v1 = wStackPop();
            wMemTest( v1, "ERASEARRAY v1" );

            /* erase the array */
            wArrayErase( v1 );

            /* deref */
            wVariantDeref( v1 );
            break;

        case W_OP_EXCEPTION:
            wStackPushNumber( wTheException );
            break;

        case W_OP_FORPREP:
        case W_OP_FORPREP1:

            /* get loop variable and max/step */
            arg1 = pcode[++pc];
            arg2 = pcode[++pc];

            /* step? */
            if (opcode == W_OP_FORPREP1) {
                /* default step size */
                n3 = 1;
            } else {
                /* get the step value */
                n3 = wStackPopNumber();

                /* assign it to the step local (at arg+1) */
                v1 = wVmGetVariable( arg2+1 );
                v1->dataType = W_TYPE_NUMBER;
                v1->value.number = n3;
            }

            /* set the max value */
            n2 = wStackPopNumber();
            v1 = wVmGetVariable( arg2 );
            v1->dataType = W_TYPE_NUMBER;
            v1->value.number = n2;

            /* set the index value */
            n1 = wStackPopNumber();
            v1 = wVmGetVariable( arg1 );
            wVariantDeref( v1 );
            v1->dataType = W_TYPE_NUMBER;
            v1->value.number = n1;

            /* what direction is the loop? */
            if (n3 > 0) {
                /* positive step. is start greater than end? */
                n1 = (n1 > n2);

            } else {
                /* negative step. is start less than end? */
                n1 = (n1 < n2);
            }

            /* next instruction is JMPF */
            pc++;
            arg1 = pcode[++pc];

            /* jump? */
            if (n1) {
                pc += arg1 - 1;
            }
            break;
            
        case W_OP_FORSTEP:
        case W_OP_FORSTEP1:

            /* get loop variable and max/step */
            arg1 = pcode[++pc];
            arg2 = pcode[++pc];

            /* get index value */
            v1 = wVmGetVariable( arg1 );
            wVariantCoerce( v1, W_TYPE_NUMBER );
            n1 = v1->value.number;

            /* get step size */
            if (opcode == W_OP_FORSTEP1) {
                /* step 1 */
                n2 = 1;
            } else {
                /* step is at arg2+1 */
                v2 = wVmGetVariable( arg2+1 );
                n2 = v2->value.number;
            }

            /* increment */
            v1->value.number = v1->value.number + n2;

            /* get max */
            v2 = wVmGetVariable( arg2 );

            /* step direction? */
            if (n2 > 0) {
                /* positive step */
                n1 = (v1->value.number <= v2->value.number );
            } else {
                /* negative step */
                n1 = (v1->value.number >= v2->value.number );
            }

            /* next instruction is JMPT */
            pc++;
            arg1 = pcode[++pc];

            /* jump? */
            if (n1) {
                pc += arg1 - 1;
            }
            break;

        case W_OP_FILECLOSE:
			/* close file */
            arg1 = (int)wStackPopNumber();
            wFileClose( arg1 );
			break;
		
        case W_OP_FILECLOSEALL:
			/* close all files */
			wFileCloseAll();
			break;
		
        case W_OP_FILEOPEN:
			/* file open */
			arg1 = (int)wStackPopNumber();
            arg2 = (int)wStackPopNumber();
            v1 = wStackPopString();
            wFileOpen( wStringChar( v1 ), arg2, arg1 );
			wVariantDeref( v1 );
			break;

        case W_OP_FILEREAD:
			/* read from a file */
			
			/* get the address to store the result into */
            v1 = wStackPopLval();
            wMemTest( v1, "FILEREAD v1" );

            /* deref the value */
            wVariantDeref( v1 );

            /* get the file handle */
            arg1 = (int)wStackPopNumber();

            /* read the line from the file */
            wFileLineInput( arg1 );
            wStringNew( v1, wTheFileBuffer, -1 );

			break;

        case W_OP_FIRSTTIME:
            /* push true if first time calling routine */
            wStackPushNumber(sRoutine->called == 1);
            break;

        case W_OP_FREE:
            /* deref a variable */
            arg1 = pcode[++pc];
            v1 = wVmGetVariable( arg1 );
            wMemTest( v1, "FREE v1" );

            wVariantDeref( v1 );
            break;

        case W_OP_GET:
            wErrorThrow( W_ERROR_INTERNAL, "GET opcode encountered without val" );
            break;

        case W_OP_HALT:
            /* compare to END */
#ifdef __WXWIN__
            /* need to leave mainloop? */
            if (wxGetApp().GetTopWindow() != NULL) {
                /* leave mainloop */
                wxGetApp().ExitMainLoop();
            }
#endif
            /* set halt flag */
            wTheHaltFlag = W_TRUE;
            break;

        case W_OP_IDIV:
            /* divide two values on the stack, leave integer result */
            n1 = wStackPopNumber();
            n2 = wStackPopNumber();

            /* check for division by zero */
            if (n1 == 0 ) {
                wErrorThrow( W_ERROR_MATH, "Division by zero" );
                break;
            }

            wStackPushNumberFromRoutine( floor(n2 / n1), "IDivide" );

            break;


        case W_OP_INDEX:
            /* careful! lots of stuff on the stack */
            arg1 = pcode[++pc];
            modifier = pcode[++pc];

            v1 = wStackPeek(arg1);
            wMemTest( v1, "INDEX v1" );

            /* index into the collection, return the lval */
            lval = wVariantIndex( v1, arg1 );
            wStackDrop(1);

            /* check for error */
            if (lval==NULL) {
                wErrorThrow( W_ERROR_INDEX, "Bad index" );
            } else {
                wMemTest( lval, "INDEX lval" );
            }

            break;

        case W_OP_GETSLICE:
            /* get indexes */
            arg2 = (int)wStackPopNumber();
            arg1 = (int)wStackPopNumber();

            /* free up spot on stack */
            v2 = wStackPeek(0);
            v1 = wStackPushNothing();
            wVariantMove( v1, v2 );

            /* negative index? */
            if (arg2 < 0) {
                arg2 = (v1->value.string->length)+arg2+1;
            }

            /* put slice into v2 */
            wVariantSlice( v2, v1, arg1, arg2 );

            /* drop source from stack */
            wStackDrop(1);

            break;

        case W_OP_INITARRAY:

            /* count of indexes */
            arg1 = pcode[++pc];

            /* default value */
            v1 = wStackPop();
            wMemTest( v1, "INITARRAY v1" );

            /* index ranges on stack, so can't pass destination */
            array = wArrayCreate( arg1, v1 );

            /* free the default value */
            wVariantDeref( v1 );

            /* set the array on the stack */
            v1 = wStackPushNothing();
            wMemTest( v1, "INITARRAY v1 (pushUndef)" );

            v1->dataType = W_TYPE_ARRAY;
            v1->value.array = array;

            break;

        case W_OP_INTEGER:
            pc++;
            arg1 = pcode[pc];
            wStackPushNumber( arg1 );
            break;

        case W_OP_JMP:
			/* unconditional jump */
            arg1 = pcode[++pc];
			/* +1 accounts for auto increment of pc */
            pc += arg1 - 1;
			break;

        case W_OP_JMPCATCHF:
            /* address to jump to on false */
            arg1 = pcode[++pc];

            /* value on stack doesn't match then exception? */
            if ((int)wStackPopNumber() != wTheException) {
                /* jump, offsetting for auto-increment */
                pc += arg1 - 1;
            }            
            break;

        case W_OP_JMPF:
            /* conditional jump, drop value if true */
            arg1 = pcode[++pc];

            /* get the top of stack */
            v1 = wStackPop();
            wMemTest( v1, "JMPF v1" );

            if (!wVariantIsTrue( v1 )) {
                pc += arg1 - 1;
            }

            /* deref */
            wVariantDeref( v1 );

            break;

        case W_OP_JMPONF:
            /* conditional jump */
            arg1 = pcode[++pc];

            /* get the top of stack */
            v1 = wStackPeek(0);
            wMemTest( v1, "JMPONF v1" );

            if (!wVariantIsTrue( v1 )) {
                pc += arg1 - 1;
            } else {
                wStackDrop(1);
            }
            break;

        case W_OP_JMPONT:
            /* conditional jump, drop value if false */
            arg1 = pcode[++pc];

            /* get the top of stack */
            v1 = wStackPeek(0);
            wMemTest( v1, "JMPONT v1" );

            if (wVariantIsTrue( v1 )) {
                pc += arg1 - 1;
            } else {
                wStackDrop(1);
            }
            break;

        case W_OP_JMPT:
            /* conditional jump */
            arg1 = pcode[++pc];

            /* get the top of stack */
            v1 = wStackPop();
            wMemTest( v1, "JMPT v1" );

            if (wVariantIsTrue( v1 )) {
                pc += arg1 - 1;
            }

            /* deref */
            wVariantDeref( v1 );

            break;

        case W_OP_JSR:
            /* jump to subroutine */

            /* get address of subroutine */
            arg1 = pcode[++pc];

            /* push return address onto subroutine stack */
            wGrowAppend( wTheSubroutineStack, pc );

            /* jump to the new address */
            pc += arg1 - 1;

            break;

        case W_OP_FOREACHPREP:
        case W_OP_FOREACHLOOP:

            /* arg1 is the local that holds the collection */
            arg1 = pcode[++pc];
            v1 = wVmGetVariable( arg1 );

            /* the local following arg1 is the index */
            v2 = wVmGetVariable( arg1+1 );

            /* arg2 is the first loop variable */
            arg2 = pcode[++pc];
            v3 = wVmGetVariable( arg2 );

            /* arg3 is the optional loop variable */
            arg3 = pcode[++pc];
            if (arg3) {
                v4 = wVmGetVariable( arg3 );
            } else {
                v4 = NULL;
            }


            /* need to prep? */ 
            if (opcode == W_OP_FOREACHPREP) {
                /* get the collection from the stack */
                wVariantMove( v1, wStackPop() );

                /* initialize index */
                v2->dataType = W_TYPE_INTEGER;
                v2->value.integer = 0;
            }
            

            /* iterate */
            flag = wVariantIterate( v1, v2, v3, v4 );

            /* next instruction is JMPF */
            pc++;
            arg1 = pcode[++pc];

            /* invert the flag if LOOP op */
            if (opcode == W_OP_FOREACHLOOP) {
                flag = !flag;
            }

            /* jump? */
            if (!flag) {
                pc += arg1 - 1;
            }
            break;
            
        case W_OP_LVAL:
            wErrorThrow( W_ERROR_INTERNAL, "LVAL opcode encountered without lval" );
            break;

        case W_OP_ME:
        
            /* what opcode follows? */
            opcode = pcode[++pc];
            switch (opcode) {
            case W_OP_GET:
                v1 = wStackPushNothing();
                v1->dataType = W_TYPE_OBJECT;
                v1->value.object = wTheCall->self;
                break;

            case W_OP_SET:
            case W_OP_LVAL:
                /* this is an illegal operation */
                break;
            }
            break;


        case W_OP_MOD:
            /* get the numbers */
            n1 = wStackPopNumber();
            n2 = wStackPopNumber();

            /* check for division by zero */
            if (n1 == 0 ) {
                wErrorThrow( W_ERROR_MATH, "Division by zero" );

            } else {
                wStackPushNumber( (long)n2 % (long)n1 );
            }

            break;

        case W_OP_VIRTUAL:
            arg1 = pcode[++pc];     /* string with routine name */

            /* look at the object on the stack */
            v1 = wStackPeek(0);

            /* needs to be a varptr */
            if (v1->dataType != W_TYPE_VARPTR) {
                wErrorThrow( W_ERROR_INTERNAL, "Expected varptr on stack (VIRTUAL)" );
                break;
            }

            /* resolve the varptr */
            v1 = v1->value.varptr;
            wMemTest( v1, "VIRTUAL v1" );

            /* user defined object? */
            if (v1->dataType == W_TYPE_OBJECT) {
                /* get the class from the object */
                klass = v1->value.object->klass;
            } else {
                /* get the class from the datatype */
                klass = wTheHandler[v1->dataType]->klass;
            }
                
            /* find the method */            
            s = wSymbolFindMethod( klass, arg1 );
            if (s == NULL) {
                wErrorThrow( W_ERROR_NOSUCH, "Method %s:%s not found",
                    klass->name, wLiteralGetChar( arg1 ) );
            }

            /* push routine onto stack */
            v1 = wStackPushNothing();
            v1->dataType = W_TYPE_ROUTINE;
            v1->value.routine = s;

            break;


        case W_OP_MYVIRTUAL:
            arg1 = pcode[++pc];     /* string with routine name */

            /* get the object */
            o = wTheCall->self;

            /* lookup the method */
            s = wSymbolFindMethod( o->klass, arg1 );
            if (s == NULL) {
                wErrorThrow( W_ERROR_NOSUCH, "Method %s:%s not found",
                    o->klass->name, wLiteralGetChar( arg1 ) );
            }

            /* push routine onto stack */
            v1 = wStackPushNothing();
            v1->dataType = W_TYPE_ROUTINE;
            v1->value.routine = s;

            break;


        case W_OP_CALLMETHOD:

            v1 = wStackPop();           /* routine or string index */
            arg2 = pcode[++pc];         /* parameter count */
            arg3 = pcode[++pc];         /* return count */

            /* make sure it's the correct datatype */
            if (v1->dataType != W_TYPE_ROUTINE) {
                wErrorThrow( W_ERROR_INTERNAL, "Expected Routine on stack (CALLMETHOD)" );
                break;
            }

            /* get the routine's symbol */
            s = v1->value.routine;

            /* get the object off the stack */
            v1 = wStackPopLval();
            wMemTest( v1, "CALLMETHOD v1" );

            /* object? */
            if (v1->dataType == W_TYPE_OBJECT ) {
                o = v1->value.object;
                wMemTest( o, "CALLMETHOD o" );

                /* run the method */
                wCallRoutine( s, arg2, arg3, o, NULL );

                /* deref the object */
                wObjectDeref( v1 );

            } else {
                /* run the method as a builtin datatype */
                /* v1 will automatically be dereferenced */
                wCallRoutine( s, arg2, arg3, NULL, v1 );

            }
            break;


        case W_OP_CALLMYMETHOD:

            /* pop routine address */
            v1 = wStackPop();           
            s = v1->value.routine;

            /* parameter count */
            arg2 = pcode[++pc];

            /* return count */
            arg3 = pcode[++pc];         

            /* get self */
            o = wTheCall->self;

            /* run the method */
            wCallRoutine( s, arg2, arg3, o, NULL );

            break;

        case W_OP_MISSING:
            /* push true if missing from parm list */
            arg1 = pcode[++pc];
            wStackPushNumber( arg1 > wTheCall->parmCount );
            break;


        case W_OP_MUL:
            /* multiply two values on the stack */
            v1 = wStackPop();
            wMemTest( v1, "MUL v1" );

            v2 = wStackPop();
            wMemTest( v1, "MUL v1" );

            n1 = wVariantGetNumber( v2 ) * wVariantGetNumber( v1 );
            wVariantDeref( v1 );
            wVariantDeref( v2 );
            wStackPushNumber( n1 );
            break;

        case W_OP_NEGATE:
            /* negate value on top of stack */
            v1 = wStackItem( wTheStack->count );
            wMemTest( v1, "NEGATE v1" );

            wVariantCoerce( v1, W_TYPE_NUMBER );
            v1->value.number = -v1->value.number;
            break;

        case W_OP_NEW:
        case W_OP_NEWTEMP:
            /* get the class index and arg count */
            arg1 = pcode[++pc];
            arg2 = pcode[++pc];

            /* temporary? */
            arg3 = (opcode == W_OP_NEWTEMP);

            /* find the class */
            klass = wSymbolLookup( arg1 );

            /* lookup the "new" method */
            s = wSymbolFindMethodChar( klass, "new" );

            /* native datatype? */
            if (klass->flags && W_SYM_ISNATIVE) {

                /* make sure "new" method exists */
                if (s == NULL) {
                    wErrorThrow( W_ERROR_NOSUCH, "%s.new() not found", klass->name );
                }

                /* call the "new" method */
                wCallRoutine( s, arg2, 1, NULL, NULL );

            /* not a native datatype */
            } else {
                /* create the object; fail if abstract */
                o = wObjectNew( arg1, arg3 );
                if (o == NULL) {
                    break;
                }

                /* optionally call the "new" method */
                if (s != NULL) {
                    /* call the new routine */
                    wCallRoutine( s, arg2, 0, o, NULL );
                }

                /* push the object onto the stack */
                v1 = wStackPushNothing();
                wMemTest( v1, "NEW v1" );
    
                v1->dataType = W_TYPE_OBJECT;
                v1->value.object = o;

            }

			break;

        case W_OP_OR_BITS:
            /* bitwise OR two integers */
            n1 = (wNumber)((int)wStackPopNumber() | (int)wStackPopNumber());
            wStackPushNumber( n1 );

            break;

        case W_OP_POWER:
            /* n1^n2 two values on the stack */
            n1 = wStackPopNumber();
            n2 = wStackPopNumber();

            /* call pow() with error checking */
            wStackPushNumberFromRoutine( pow( n2, n1 ), "Power" );
            break;

		case W_OP_PRINT:
        case W_OP_PRINTLN:
        case W_OP_PRINTTAB:
            /* get value and print it */
            v1 = wStackPop();
            wMemTest( v1, "PRINT v1" );

            /* direct to file? */
            wVariantFilePrint( wTheOutputFile, v1, W_FALSE );
            wVariantDeref( v1 );

            /* seperator? */
            if (opcode == W_OP_PRINTTAB) {
                if (wTheOutputFile == NULL) {
                    wConsolePrint( " " );
                } else {
                    fprintf( wTheOutputFile, " " );
                }

            } else if (opcode == W_OP_PRINTLN) {
                if (wTheOutputFile == NULL) {
                    wConsolePrint( "\n" );
                } else {
                    fprintf( wTheOutputFile, "\n" );
                }
            }

			break;

        case W_OP_PROP:
            arg1 = pcode[++pc];
            modifier = pcode[++pc];
            lval = &(wTheCall->self->prop[arg1-1]);
            break;

        case W_OP_PROPBYNAME:
            /* get string index */
            arg1 = pcode[++pc];
            modifier = pcode[++pc];
    
            /* get object from stack */
            v1 = wStackPeek(0);
            wMemTest( v1, "PROPBYNAME v1" );

            /* objects should be passed by pointer */
            if (v1->dataType != W_TYPE_VARPTR) {
                wErrorThrow( W_ERROR_INTERNAL, "Expected varptr on stack (PROPBYNAME)" );
            }

            /* resolve the varptr */
            v1 = wStackPopLval();
            wMemTest( v1, "VIRTUAL v1" );

            /* user defined object? */
            if (v1->dataType == W_TYPE_OBJECT) {
                /* get the class from the object */
                klass = v1->value.object->klass;
            } else {
                /* get the class from the datatype */
                klass = wTheHandler[v1->dataType]->klass;
            }

            /* find the position of the property */
            i = wSymbolFindPropPos( klass, arg1 );
            if (i == 0 ) {
                wErrorThrow( W_ERROR_NOSUCH, "Property %s.%s not found",
                    klass->name,
                    wStringChar((wVariant *)wGrowGet(wTheLiterals, arg1)) );
            }

            /* get the object */
            o = v1->value.object;
            wMemTest( o, "PROPBYNAME o" );

            /* object's property */
            lval = &(o->prop[i-1]);

            /* deref */
            o->refCount--;

            break;

        case W_OP_NOT:
            /* NOT the value on the stack */
            wStackPushNumber( !(int)wStackPopNumber() );
			break;

        case W_OP_NOTHING:
            /* push undefined onto stack */
            wStackPushNothing();
			break;


        case W_OP_RET:
            /* return from subroutine */

            /* check return stack size */
            if (wTheSubroutineStack->count > 1) {
                wErrorThrow( W_ERROR_INTERNAL, "Underflow on subroutine stack" );
            }

            /* get return address from subroutine stack */
            pc = wGrowPop( wTheSubroutineStack );

            break;


        case W_OP_ROUTINE:
            pc++;
            arg1 = pcode[pc];
            v1 = wStackPushNothing();
            v1->dataType = W_TYPE_ROUTINE;
            v1->value.routine = wSymbolLookup( arg1 );
            break;

        case W_OP_SETTYPE:
            arg1 = pcode[++pc];
            arg2 = pcode[++pc];

            /* get the variable */
            v1 = wVmGetVariable( arg1 );

            /* set the datatype */
            v1->typeCast = arg2;

            /* typecast the data */
            wVmTypeCast( v1 );

            break;


        case W_OP_LITERAL:
			/* push a literal onto the stack */
            pc++;
            arg1 = pcode[pc];
            v1 = wStackPushNothing();
            wMemTest( v1, "LITERAL v1" );

            v2 = (wVariant *)wGrowGet(wTheLiterals, arg1);
            wMemTest( v2, "LITERAL v2" );

            wVariantCopy( v1, v2 );
            break;

        case W_OP_READ:
            /* read from keyboard, see FILEREAD */
			
			/* get the address to store the result into */
            v1 = wStackPopLval();
            wMemTest( v1, "READ v1" );

            /* deref the value */
            wVariantDeref( v1 );

            /* print a prompt */
            printf( "? " );

            /* get the line from the keyboard */
            wFileKeyboardInput();
            wStringNew( v1, wTheFileBuffer, -1 );

			break;

        case W_OP_REDIRECT:
			/* redirect output of print */
            arg1 = (int)wStackPopNumber();

            /* ensure it is open */
            wFileCheckHandle( arg1, W_TRUE );

            /* set it */
            wTheOutputFile = wFileHandles[arg1-1];

			break;
		
        case W_OP_RETHROW:
            /* reactiveate current exception */
            wErrorThrow( wTheException, wTheExceptionText );
            break;
    
		case W_OP_RETURN:
			/* return from a call */
            return;
            /* break; */

        case W_OP_SET:
            wErrorThrow( W_ERROR_INTERNAL, "SET opcode encountered without lval" );
            break;

        case W_OP_SETLIST:
            arg1 = pcode[++pc];
            arg2 = pcode[++pc];

            /* get destination */
            v1 = wStackPeek( arg2 );
            wMemTest( v1, "SETLIST v1" );

            /* malloc a variant to hold the index key value */
            v3 = (wVariant *)wMalloc( sizeof( wVariant ) );
            v3->dataType = W_TYPE_INTEGER;

            /* the value is in reverse order, so it can't be popped */
            for ( i = arg1; i <= arg2; i++ ) {                
                /* don't deref, since value isn't refcounted in routine */
                v2 = wStackPeek( arg2-i );
                wMemTest( v1, "SETLIST v1 (reading table values)" );
                
                /* set the key value */
                v3->value.integer = i;

                /* insert it into the collection */
                wVariantInsert( v1, v3, v2 );
            }

            /* free the variant holding the index */
            wFree( v3 );
            

            /* adjust the stack */
            i = (arg2-arg1)+1;
            wTheStack->free += i;
            wTheStack->count -= i;

            break;


        case W_OP_SETMAP:
            /* careful! lots of stuff on the stack */

            /* get the index (will use as a key) */
            arg1 = pcode[++pc];
            v1 = wStackPeek(arg1*2);
            wMemTest( v1, "SETMAP v1" );

            /* load it with value */
            for ( i = arg1; i > 0; i-- ) {

                /* get the value in reverse order */
                v2 = wStackPeek((i*2)-1);
                wMemTest( v1, "SETMAP v1 (key)" );

                /* get the value */
                v3 = wStackPeek((i*2)-2);
                wMemTest( v1, "SETMAP v2 (value)" );

                /* add it into the collection */
                wVariantInsert( v1, v2, v3 );

            }

            /* deref the value */
            // wVariantDeref( v1 );
            wVariantDeref( v2 );

             /* adjust the stack */
            i = (arg1*2);
            wTheStack->free += i;
            wTheStack->count -= i;

            break;


        case W_OP_STARTCATCH:
            /* get the jump offset */
            arg1 = pcode[++pc];

            aCatch = (wCatch *)wMalloc( sizeof( wCatch ) );
            aCatch->stackCount = wTheStack->count;
            aCatch->callCount = wGrowCount( wTheCallStack );
            aCatch->gosubCount = wGrowCount( wTheSubroutineStack );

            aCatch->jumpTo = pc+arg1-1;
            
            /* store catch data on catch stack */
            wGrowAppend( wTheCatchStack, (int)aCatch );

            /* set address to return to on error */
            if (setjmp(aCatch->jumpBuffer)) {            

                /* print exception */
                if (wTheDebugFlag) {
                    wConsoleDebugf("EXCEPTION: %s\n", wTheExceptionText );
                }

                /* restore, just in case */
                aCatch = (wCatch *)wGrowPop( wTheCatchStack );

                /* need to remove items? negative values throw another error */
                i = wTheStack->count - aCatch->stackCount;
                wStackDrop( i );

                /* restore the call stack to it's prior size */
                wCallRestoreStack( aCatch->callCount );

                /* restore the subroutine stack to it's prior size */
                i = wTheSubroutineStack->count - aCatch->gosubCount;
                wGrowDrop( wTheSubroutineStack, i );

                /* get the jump address off the stack */
                pc = aCatch->jumpTo;

                /* free the catch */
                wFree(aCatch);

                /* reset the modifier, if set */
                modifier = 0;
            }
            break;

        case W_OP_STDIO:
            /* redirect output of print back to stdio */
            wTheOutputFile = NULL;
			break;

        case W_OP_SUB:
            /* subtract two values on the stack */
            v1 = wStackPop();
            wMemTest( v1, "SUB v1" );

            v2 = wStackPop();
            wMemTest( v2, "SUB v2" );

            n1 = wVariantGetNumber( v2 ) - wVariantGetNumber( v1 );

            wVariantDeref( v1 );
            wVariantDeref( v2 );

            wStackPushNumber( n1 );

            break;


        case W_OP_THROW:
            /* throw a user exception */
            arg1 = (int)wStackPopNumber();
            wErrorThrow( arg1, "User thrown exception" );
            break;

        case W_OP_TRACE:
            arg1 = pcode[++pc];
            wTheCall->sourceLine = arg1;

            if (wTheTraceFlag) {
                wConsolePrintf( "TRACE: %-16s:%-04d %s",
                    wSourceGet( arg1 )->fileName,
                    wSourceGet( arg1 )->lineNum,
                    wSourceGet( arg1 )->text );
            }
            break;

        case W_OP_VARIABLE:
            arg1 = pcode[++pc];
            modifier = pcode[++pc];

            /* store the pointer in lval */
            lval = wVmGetVariable( arg1 );
            wMemTest( lval, "VARIABLE lval" );
            break;

		default:
            wErrorThrow( W_ERROR_INTERNAL, "Unknown opcode %d at position %d", pcode[pc], pc );
			break;
		}

        /* if debug is on, show this as an opcode */
        if (wTheDebugFlag && modifier) {
            wVmTrace( sRoutine, pcode, pc );
        }
        
        /* handle the modifier */
        // FIXME: this should probably really be an opcode.
        // the ME opcode works a bit differently, so perhaps
        // it needs an additional opcode?

        switch (modifier) {
        case 0:
            /* no modifier */
            break;
        case W_OP_GET:
            /* fetch the lval and put it on the stack */
            wStackPush( lval );
            modifier = 0;
            break;

        case W_OP_SET:
            /* get the value off the stack */
            v1 = wStackPop();

            /* move the data to the lval */
            wVariantMove( lval, v1 );

            /* typecast the value */
            wVmTypeCast( lval );

            modifier = 0;
            break;

        case W_OP_LVAL:
            /* put the pointer on the stack */
            wStackPushPtr( lval );
            modifier = 0;
            break;

        case W_OP_ADD_SET:
        case W_OP_SUB_SET:
        case W_OP_MUL_SET:
        case W_OP_DIV_SET:
        case W_OP_IDIV_SET:
        case W_OP_MOD_SET:

            /* add value on stack to lval */
            n1 = wStackPopNumber();

            /* coerce lval to a number */
            wVariantCoerce( lval, W_TYPE_NUMBER );


            /* division by zero? */
            switch (modifier) {
            case W_OP_DIV_SET:
            case W_OP_IDIV_SET:
            case W_OP_MOD_SET:
                if (n1 == 0 ) {
                    wErrorThrow( W_ERROR_MATH, "Division by zero" );
                    break;
                }                    
            }

            switch (modifier) {
                case W_OP_ADD_SET:
                    lval->value.number += n1;
                    break;
                case W_OP_SUB_SET:
                    lval->value.number -= n1;
                    break;
                case W_OP_MUL_SET:
                    lval->value.number *= n1;
                    break;
                case W_OP_DIV_SET:
                    lval->value.number /= n1;
                    break;
                case W_OP_IDIV_SET:
                    lval->value.number = floor(lval->value.number / n1);
                    break;
                case W_OP_MOD_SET:
                    lval->value.number = ( (long)n2 % (long)n1 );
                    break;
            }

            /* coerce the destination to a number */
            wVmTypeCast( lval );

            modifier = 0;
            break;

        case W_OP_CONCAT_SET:
            /* get source string, don't deref */
            v1 = wStackPopString();

            /* coerce the destination to a string */
            wVariantCoerce( lval, W_TYPE_STRING );
            wVmTypeCast( lval );

            /* concat them */
            wStringConcat( lval, v1 );

            /* deref the source */
            wVariantDeref( v1 );

            modifier = 0;
            break;

        default:
            wErrorThrow( W_ERROR_INTERNAL, "Bad opcode following lval");        

        }

		/* move to next opcode */
		pc++;
	}
}



void wVmDecompile( wSymbol *sRoutine )
{
    int pc, i;
    int *pcode;

    wGrow *code;

    wMemTest( sRoutine, "wVmDecompile:sRoutine" );
    wMemTest( sRoutine->pcode, "wVmDecompile:sRoutine->pcode" );
    code = sRoutine->pcode;
    pcode = (int *)code->value;

    /* raw dump */
    for (i=0; i < code->count; i++ ) {
        wConsolePrintf("%d ", pcode[i] );
    }
    wConsolePrintf("\n");

    pc = 0;
	while (pc < code->count) {
        pc = wVmDecompileOp( sRoutine, pcode, pc );
    }
 }

int wVmDecompileOp( wSymbol *sRoutine, int *pcode, int pc )
{
    wSymbol *s1, *s2;
    char *buffer;
    int opcode, at, arg1, arg2, arg3;

    /* save position */
    at = pc;

    /* get the opcode */
    opcode = pcode[pc];
    switch (opcode) {

    /* opcodes that have no args */
    case W_OP_NOOP:
    case W_OP_ADD:
    case W_OP_ADD_SET:
    case W_OP_SUB:
    case W_OP_SUB_SET:
    case W_OP_MUL:
    case W_OP_MUL_SET:
    case W_OP_DIV:
    case W_OP_DIV_SET:
    case W_OP_CONCAT:
    case W_OP_CONCAT_SET:
    case W_OP_MOD:
    case W_OP_MOD_SET:
    case W_OP_OR_BITS:
    case W_OP_POWER:
    case W_OP_EMPTYSTRING:
    case W_OP_HALT:
    case W_OP_END:
    case W_OP_STDIO:
    case W_OP_PRINT:
    case W_OP_PRINTLN:
    case W_OP_PRINTTAB:
    case W_OP_EMITLN:
    case W_OP_EMITTAB:
    case W_OP_REDIRECT:
    case W_OP_EQ:
    case W_OP_NE:
    case W_OP_GT:
    case W_OP_LT:
    case W_OP_GE:
    case W_OP_LE:
    case W_OP_IDIV:
    case W_OP_IDIV_SET:
    case W_OP_NEGATE:
    case W_OP_RETURN:
    case W_OP_NOT:
    case W_OP_NOTHING:
    case W_OP_ME:
    case W_OP_THROW:
    case W_OP_RETHROW:
    case W_OP_EXCEPTION:
    case W_OP_ERASEARRAY:
    case W_OP_GETSLICE:
    case W_OP_GET:
    case W_OP_SET:
    case W_OP_LVAL:
    case W_OP_FILECLOSE:
    case W_OP_FILECLOSEALL:
    case W_OP_FILEOPEN:
    case W_OP_FILEREAD:
    case W_OP_READ:
    case W_OP_RET:
    case W_OP_CREATETABLE:
    case W_OP_DTOR:
    case W_OP_FIRSTTIME:

        wVmShowOp( at, opcode, 0, 0, 0, 0, "" );
        break;

    /* jump opcodes */
    case W_OP_JMP:
    case W_OP_JMPT:
    case W_OP_JMPONT:
    case W_OP_JMPF:
    case W_OP_JMPONF:
    case W_OP_STARTCATCH:
    case W_OP_ENDCATCH:
    case W_OP_JMPCATCHF:
    case W_OP_JSR:
        arg1 = pcode[++pc];
        wVmShowOp( at, opcode, 1, arg1, 0, 0, "to %d", arg1+pc );
        break;


    case W_OP_INTEGER:
        pc++;
        arg1 = pcode[pc];
        wVmShowOp( at, opcode, 1, arg1, 0, 0, "%d", arg1);
        break;

     case W_OP_LITERAL:
        /* push a literal onto the stack */
        pc++;
        arg1 = pcode[pc];
        buffer = wVariantToChar(
            (wVariant *)wGrowGet(wTheLiterals, arg1), W_TRUE, 0 );
        wVmShowOp( at, opcode, 1, arg1, 0, 0, "%s", buffer );
        wFree( buffer );
        break;

    case W_OP_PROP:
        arg1 = pcode[++pc];
        s1 = wSymbolLookup( sRoutine->scope );
        wVmShowOp( at, opcode, 1, arg1, 0, 0,
            "%s", wSymbolGetChild( s1, arg1 )->name );
        break;

    case W_OP_PROPBYNAME:
        arg1 = pcode[++pc];
        buffer = wVariantToChar(
            (wVariant *)wGrowGet(wTheLiterals, arg1), W_TRUE, 0 );
        wVmShowOp( at, opcode, 1, arg1, 0, 0, "%s", buffer );
        wFree( buffer );
        break;
    
    case W_OP_FREE:
        arg1 = pcode[++pc];
        wVmShowOp( at, opcode, 1, arg1, 0, 0,
            "%s", wVmVariableName( sRoutine, arg1 ) );
        break;

    case W_OP_FORPREP:
    case W_OP_FORPREP1:
    case W_OP_FORSTEP:
    case W_OP_FORSTEP1:
        arg1 = pcode[++pc];
        arg2 = pcode[++pc];
        wVmShowOp( at, opcode, 2, arg1, arg2, 0,
            "%s, %s",
            wVmVariableName( sRoutine, arg1 ),
            wVmVariableName( sRoutine, arg2 ) );
        break;

    case W_OP_FOREACHPREP:
    case W_OP_FOREACHLOOP:
        arg1 = pcode[++pc];
        arg2 = pcode[++pc];
        arg3 = pcode[++pc];

        if (arg3) {
            /* show 3 ops */
            wVmShowOp( at, opcode, 3, arg1, arg2, arg3,
                "%s, %s, %s",
                wVmVariableName( sRoutine, arg1 ),
                wVmVariableName( sRoutine, arg2 ),
                wVmVariableName( sRoutine, arg3 ) );
        } else {
            /* show 2 ops */
            wVmShowOp( at, opcode, 3, arg1, arg2, arg3,
                "%s, %s",
                wVmVariableName( sRoutine, arg1 ),
                wVmVariableName( sRoutine, arg2 ) );
        }
        break;

    case W_OP_ROUTINE:
        arg1 = pcode[++pc];
        s1 = wSymbolLookup( arg1 );
        s2 = wSymbolLookup( s1->scope );
        wVmShowOp( at, opcode, 1, arg1, 0, 0,
            "%s.%s", s2->name, s1->name );
        break;

    case W_OP_VIRTUAL:
    case W_OP_MYVIRTUAL:
        arg1 = pcode[++pc];
        buffer = wVariantToChar(
            (wVariant *)wGrowGet(wTheLiterals, arg1), W_TRUE, 0 );
        wVmShowOp( at, opcode, 1, arg1, 0, 0, "%s", buffer );
        wFree( buffer );
        break;

    case W_OP_CALL:
        arg1 = pcode[++pc];
        arg2 = pcode[++pc];
        wVmShowOp( at, opcode, 2, arg1, arg2, 0,
            "%d in %d out", arg1, arg2 );
        break;

    case W_OP_CALLMETHOD:
    case W_OP_CALLMYMETHOD:
        arg1 = pcode[++pc];
        arg2 = pcode[++pc];
        wVmShowOp( at, opcode, 2, arg1, arg2, 0,
            "%d in, %d out", arg1, arg2);
        break;

    case W_OP_DROP:
        arg1 = pcode[++pc];
        wVmShowOp( at, opcode, 1, arg1, 0, 0,
            "drop %d item(s) from the stack", arg1 );
        break;

    case W_OP_NEW:
        arg1 = pcode[++pc];
        arg2 = pcode[++pc];
        wVmShowOp( at, opcode, 2, arg1, arg2, 0,
            "%s, %d in", wSymbolLookup(arg1)->name, arg2 );
        break;

    case W_OP_NEWTEMP:
        arg1 = pcode[++pc];
        arg2 = pcode[++pc];
        wVmShowOp( at, opcode, 2, arg1, arg2, 0,
            "%s, %d in", wSymbolLookup(arg1)->name, arg2 );
        break;

    case W_OP_TRACE:
        arg1 = pcode[++pc];
        /* FIX: should remove linefeed */
        wVmShowOp( at, opcode, 1, arg1, 0, 0,
            "%s", wSourceGet( arg1 )->text );
        break;

    case W_OP_CASE:
        arg1 = pcode[++pc];
        arg2 = pcode[++pc];
        wVmShowOp( at, opcode, 2, arg1, arg2, 0,
            "%s, to %d", wVmVariableName( sRoutine, arg1 ), arg2+pc );
        break;

    case W_OP_CASERANGE:
        arg1 = pcode[++pc];
        arg2 = pcode[++pc];
        wVmShowOp( at, opcode, 2, arg1, arg2, 0,
            "%s, to %d", wVmVariableName( sRoutine, arg1 ), arg2+pc );
        break;

    case W_OP_CREATEARRAY:
        arg1 = pcode[++pc];
        wVmShowOp( at, opcode, 1, arg1, 0, 0, "%d indexes", arg1 );
        break;

    case W_OP_INITARRAY:
        arg1 = pcode[++pc];
        wVmShowOp( at, opcode, 1, arg1, 0, 0, "%d indexes", arg1 );
        break;

    case W_OP_INDEX:
        arg1 = pcode[++pc];
        wVmShowOp( at, opcode, 1, arg1, 0, 0, "%d indexes", arg1 );
        break;

    case W_OP_CREATELIST:
        arg1 = pcode[++pc];
        wVmShowOp( at, opcode, 1, arg1, 0, 0, "%d elements", arg1 );
        break;

    case W_OP_SETLIST:
        arg1 = pcode[++pc];
        arg2 = pcode[++pc];
        wVmShowOp( at, opcode, 2, arg1, arg2, 0,
            "starting at %d, copy %d elements", arg1, arg2 );
        break;

    case W_OP_SETMAP:
        arg1 = pcode[++pc];
        wVmShowOp( at, opcode, 1, arg1, 0, 0,
            "map %d elements to table", arg1 );
        break;

    case W_OP_MISSING:
        arg1 = pcode[++pc];
        wVmShowOp( at, opcode, 1, arg1, 0, 0,
            "%s", wVmVariableName( sRoutine, arg1 ) );
        break;

    case W_OP_VARIABLE:
        arg1 = pcode[++pc];
        wVmShowOp( at, opcode, 1, arg1, 0, 0, 
            "%s", wVmVariableName( sRoutine, arg1 ) );
        break;
 
    case W_OP_SETTYPE:
        /* set datatype of a variable */
        arg1 = pcode[++pc];
        arg2 = pcode[++pc];
        wVmShowOp( at, opcode, 1, arg1, arg2, 0, 
            "%s must be %s",
            wVmVariableName( sRoutine, arg1 ),
            wSymbolLookup(arg2)->name );
        break;

    default:
        wErrorThrow( W_ERROR_INTERNAL, "Bad opcode %d  (wVmDecompile)", pcode[pc] );
        break;
    }

    /* move to next opcode */
    return pc+1;
}


void wVmDecompileAll()
{
    int i;
    wSymbol *sRoutine;

    for ( i = 1; i <= wTheSymbols->count; i++ ) {
        sRoutine = wSymbolLookup( i );
        if (sRoutine->type == W_SYM_FUNCTION
        ||  sRoutine->type == W_SYM_SUB) {
            wConsolePrintf("%s:%s, parms: %d, locals: %d\n",
                wSymbolLookup( sRoutine->scope )->name,
                sRoutine->name,
                sRoutine->args,
                sRoutine->children->count );
            if (sRoutine->flags & W_SYM_ISABSTRACT) {
                wConsolePrint("ABSTRACT METHOD\n");
            } else {
                wVmDecompile( wSymbolLookup( i ) );
            }
            wConsolePrint("\n");
        }
    }
}


void wVmShowOp( int pc, int opcode, int args, int arg1, int arg2, int arg3, char *commentFmt, ... )
{
    char        *buffer, *comment;
    va_list     argList;

    /* allocate space for the comment */
    comment = wCharMalloc( W_INBUFFER_MAX );

    /* format args */
    va_start(argList, commentFmt);
    vsprintf( comment, commentFmt, argList );
    va_end(argList);

    /* chose the format based on the number of args */
    switch (args) {
    case 0:
        /* no args */
        wConsolePrintf( "%-4d \t%-16s%3d             ; %s\n", pc, wOpcodeName[opcode], opcode, comment );
        break;
    case 1:
        /* one arg */
        wConsolePrintf( "%-4d \t%-16s%3d %3d         ; %s\n", pc, wOpcodeName[opcode], opcode, arg1, comment );
        break;
    case 2:                  
        wConsolePrintf( "%-4d \t%-16s%3d %3d %3d     ; %s\n", pc, wOpcodeName[opcode], opcode, arg1, arg2, comment );
        break;
    case 3:
        wConsolePrintf( "%-4d \t%-16s%3d %3d %3d %3d ; %s\n", pc, wOpcodeName[opcode], opcode, arg1, arg2, arg3, comment );
        break;
    }

    /* free the comment buffer */
  wFree( comment );

}
