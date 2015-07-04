/*************************************************************
    Name:       parse.c
    Purpose:    wxBasic grammar parser
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/

void dumpCode( wCode *code )
{
    int i;
    wGrow *pcode;
    pcode = code->pcode;
    wConsoleDebugf("code dump: ");
    for ( i = 1; i <= pcode->count; i++ ) {
        wConsoleDebugf( "%d=%d, ", i, wGrowGet( pcode, i ) );
    }
    wConsoleDebugf( "\n" );
}

/* initialize the parse state stacks */
void wParseInit()
{
    wArgCountStack  = wGrowNew( 10 );
    wBreakStack     = wGrowNew( 10 );
    wCaseStack      = wGrowNew( 10 );
    wCatchStack     = wGrowNew( 10 );
    wContinueStack  = wGrowNew( 10 );
    wElseStack      = wGrowNew( 10 );
    wEndIfStack     = wGrowNew( 10 );
    wForStack       = wGrowNew( 10 );
    wBlockTypeStack = wGrowNew( 10 );
    wMiscStack      = wGrowNew( 10 );
    wRedoStack      = wGrowNew( 10 );
    wTryStack       = wGrowNew( 10 );
    wFinallyStack   = wGrowNew( 10 );
}

/* return the current scope */
int wParseGetScope()
{
    /* inside class if global scope, but class scope is not zero */
    if (wTheCurrentScope == wTheGlobalScope && wTheClassScope != 0 ) {
        /* inside a class definition */
        return wTheClassScope;
    } else {
        /* use current scope */
        return wTheCurrentScope;
    }
}




char *wGetTokenName( int tokenType )
{
    if (tokenType < 0) {
        /* symbol */
        return wTokenName[tokenType+1024];

    } else {
        return "ASCII";
    }
}

/* return true if token matches id */
int wParseTokenIs( int id )
{
    return (wTheToken.type == id);
}

/* move to next token */
void wParseSkip()
{
// wConsoleDebugf("skipping token \"%s\"\n", wTheToken.text );
    /* parse next token */
    wLexToken();

    if (wTheDebugOnFlag) {
        wConsoleDebugf("after skip, token is \"%s\" (%s)\n",
            wTheToken.text, wGetTokenName( wTheToken.type ) );
    }
}

/* expect a token of a given type */
void wParseExpect( int expect, char *name )
{
if (wTheDebugOnFlag) {
    wConsoleDebugf("token expect, expecting \"%s\"\n", wTheToken.text );
}
    /* expected type? */
    if (wTheToken.type != expect ) {
        /* fatal error */
        wErrorThrow( W_ERROR_SYNTAX, "Expected %s, not \"%s\"", name, wTheToken.text );
    }

    /* move ahead */
    wLexToken();

    if (wTheDebugOnFlag) {
        wConsoleDebugf("after expect, token is \"%s\" (%s)\n",
            wTheToken.text, wGetTokenName( wTheToken.type ) );
    }
}


/* parse until reaching the end of file */
wCode *wParseFile()
{
    wCode *code;
    /* initialize the code */
    code = wCodeNew();

    /* move to the first token */
    wParseSkip();

    /* check if it's a shell script command */
    if (wParseTokenIs('#')) {
        /* read until a seperator */
        while (!wLexNextTokenIsSep()) {
            /* eat the character */
            wLexGetChar();
        }
        /* discard token */
        wParseSkip();
    }

    /* parse until end of file */
    while (!wParseTokenIs(W_TOKEN_EOF)) {
        /* parse a statement */
        wCodeAppend( code, wParseStatement() );
    }

    /* add typecasts to global scope */
    code = wCodeAddTypeCast( code, wTheGlobalScope, 1 );

    return code;
}


/* parse a block of code */
wCode *wParseBlock()
{
    wCode *code;

    /* in case of an empty block */
    code = wCodeNew();

    /* parse statements until end block delimiter */
    while (1) {
        switch (wTheToken.type) {
            case W_TOKEN_END:
            case W_TOKEN_WEND:
            case W_TOKEN_NEXT:
            case W_TOKEN_ELSE:
            case W_TOKEN_ELSEIF:
            case W_TOKEN_CATCH:
            case W_TOKEN_FINALLY:
            case W_TOKEN_EOF:
            case W_TOKEN_CASE:
                return code;
                /* break; */
        }

        /* unreachable code? */
//        if (code->last == W_OP_RETURN) {
//            wErrorThrow( W_ERROR_SYNTAX,  "Unreachable code" );
//        }

        
        /* parse another statement */
        wCodeAppend( code, wParseStatement() );
    }        
}

/* destroy an object */
wCode *wParseStatementDestroy() {

    wCode *code;

    /* move to the next token */
    wParseSkip();

    /* parse the expression to be destroyed */
    code = wParseExpression( 0 );

    /* emit a DTOR */
    wCodeEmitOp( code, W_OP_DTOR );

    return code;
}

/* create a local if option explicit is not set */
wSymbol *wParseCreateUndeclaredLocal( char *name )
{
    /* option explicit set? */
    if (wTheOptionExplicit) {
        wErrorThrow( W_ERROR_SYNTAX,  "Variable \"%s\" not declared", name );
    }
    return wSymbolNewLocal( name, 0 );
}


/* Me.property */
wCode *wParseMeProperty()
{
    int index;
    wSymbol *theProperty, *theKlass;
    wCode *code;
    
    /* only allowable in class definitions */
    if (wTheClassScope == 0 ) {
        wErrorThrow( W_ERROR_SYNTAX,  "Can't reference Me outside of class definition");
    }

    /* property must follow */
    if (!wParseTokenIs(W_TOKEN_PROPERTY_NAME)) {
        wErrorThrow( W_ERROR_SYNTAX,  "Expected a property, not \"%s\"", wTheToken.text );
    }

    /* find the class */
    theKlass = wSymbolLookup( wTheClassScope );

    /* find the symbol for the property */
    index = wSymbolFindPropPosChar( theKlass, wTheToken.text);
    if (index) {
        /* found the property */
        theProperty = wSymbolLookup( index );
    } else {
        /* is it a shared variable? */
        theProperty = wSymbolFind( wTheToken.text, wTheClassScope );
        if (theProperty) {
            /* variable or constant? */
            if (theProperty->type == W_SYM_VARIABLE ||
                theProperty->type == W_SYM_CONSTANT) {
                /* skip token */
                wParseSkip();

                /* emit it as a variable */
                /* don't call wCodeEmitVar, it tries to make it a property */
                wCodeEmitOp( code, W_OP_VARIABLE );
                wCodeEmit( code, wCodeGetVarIndex( theProperty ) );
                return code;
            }
        }

        /* FIXME: this error message could be better */
        wErrorThrow( W_ERROR_SYNTAX,  "\"%s\" is not a property of the class \"%s\"",
            wTheToken.text, theKlass->name );
    }
    wParseSkip();

    /* emit a PROP */
    code = wCodeNew();
    wCodeEmitOp( code, W_OP_PROP );
    wCodeEmit( code, index );

    /* the caller needs to add a GET, SET or LVAL */

    return code;
}


wCode *wParseLval()
{
    int count, isProperty;
    wCode *code;
    wSymbol *s;

    code = wCodeNew();

    /* property? */
    isProperty = wParseTokenIs(W_TOKEN_DOTPROPERTY);
    if (isProperty) {

        /* inside a shared routine? */
        if (wTheCurrentScope) {
            /* can't access me if in shared routine */
            if (wSymbolLookup( wTheCurrentScope  )->flags & W_SYM_ISSHARED) {
                wErrorThrow( W_ERROR_SYNTAX,  "Can't reference Properties in a Shared method");
            }
        }
        
        /* skip past */
        wParseSkip();
    }

    /* Me.property */
    if (isProperty && wParseTokenIs(W_TOKEN_ME)) {
        /* skip past */
        wParseSkip();
    
        /* parse the following property */
        code = wParseMeProperty();

   /* variable.property or undefined.property */
   } else if (isProperty
          && ( wParseTokenIs(W_TOKEN_VARIABLE_NAME)
          ||   wParseTokenIs(W_TOKEN_UNDEFINED) ) ) {

        /* variable? */
        if (wParseTokenIs(W_TOKEN_VARIABLE_NAME)) {
            /* accept token */
            s = wTheToken.symbol;

        /* undefined */
        } else {
            /* create a variable on the fly */
            s = wParseCreateUndeclaredLocal( wTheToken.text );
        }
        wParseSkip();

        /* emit variable LVAL */
        wCodeEmitVar( code, s );
        wCodeEmitOp( code, W_OP_LVAL );

        /* emit PROPBYNAME */
        wCodeEmitOp( code, W_OP_PROPBYNAME );
        wCodeEmit( code, wLiteralAddStr( "", wTheToken.text ) );
        wParseSkip();

    /* invalid property */
    } else if (isProperty) {
        wErrorThrow( W_ERROR_SYNTAX,  "\"%s\" is not a valid lval", wTheToken.text );

    /* variable */
    } else {
        /* get (or create) the variable */
        s = wParseVariableName();
        wParseSkip();
        
        /* emit the variable */
        wCodeEmitVar( code, s );
    }

    /* indexed? */
    if (wParseTokenIs('[')) {

        /* get the value of the lval */
        wCodeEmitOp( code, W_OP_GET );

        /* read all the indexes */
        count = wParseIndexes( code );
        wCodeEmitOp( code, W_OP_INDEX );
        wCodeEmit( code, count );

    }
        
    return code;
}


/* parse xxx.method( ... ) */
wCode *wParseDotMethod( int impliedMeFlag )
{
    int     count, meCall, sharedCall;
    wSymbol *klass, *method, *varKlass;
    wCode   *code, *arglistCode;

    /* set flags to defaults */
    meCall = W_FALSE;
    sharedCall = W_FALSE;

    /* method() or Me.method() or myBase.method() */
    if (impliedMeFlag
    || wParseTokenIs(W_TOKEN_ME)
    || wParseTokenIs(W_TOKEN_MYBASE)) {

        /* not in class definition? */
        if (wTheClassScope == 0) {
            wErrorThrow( W_ERROR_SYNTAX,  "Can't reference \"%s\" outside of class definition",
                wTheToken.text );
        }

        /* inside a shared routine? */
        if (wTheCurrentScope) {
            /* get the current method's symbol */
            method = wSymbolLookup( wTheCurrentScope );

            /* current method shared? */
            if (method->flags & W_SYM_ISSHARED) {
                wErrorThrow( W_ERROR_SYNTAX, "Can't reference \"Me\" in Shared method \"%s\"", method->name );
            }
        }

        /* flag as a call using Me */
        meCall = W_TRUE;

        /* get the current class */
        klass = wSymbolLookup( wTheClassScope );

        /* MyBase refers to the parent class */
        if (wParseTokenIs(W_TOKEN_MYBASE)) {
            /* is there a superclass? */
            if (klass->inherits == 0) {
                wErrorThrow( W_ERROR_SYNTAX,  "The class \"%s\" doesn't inherit any classes",
                    klass->name );
            }
            klass = wSymbolLookup( klass->inherits );
        }

        /* need to skip Me or MyBase? */
        if (!impliedMeFlag) {
            /* skip token */
            wParseSkip();
        }

        /* look up the method */
        method = wSymbolFindMethodChar( klass, wTheToken.text );
        if (method == NULL) {
            wErrorThrow( W_ERROR_SYNTAX,  "Can't find method %s.%s", klass->name, wTheToken.text );
        }

        /* code holder */
        code = wCodeNew();

        /* virtual or abstract method? */
        if (method->flags & (W_SYM_ISVIRTUAL | W_SYM_ISABSTRACT) ) {
            /* emit a MYVIRTUAL lookup */
            wCodeEmitOp( code, W_OP_MYVIRTUAL );
            wCodeEmit( code, wLiteralAddStr( "", wTheToken.text ) );

        } else {
            /* shared? */
            if (method->flags & W_SYM_ISSHARED) {
                /* flag as a plain call */
                meCall = W_FALSE;
                sharedCall = W_TRUE;
            }

            /* emit a ROUTINE */
            wCodeEmit( code, W_OP_ROUTINE );
            wCodeEmit( code, method->index );
        }
        wParseSkip();

    /* className.sharedMethodName() */
    } else if (wParseTokenIs(W_TOKEN_CLASS_NAME)) {
        /* store the class */
        klass = wTheToken.symbol;
        wParseSkip();
    
        /* find the method */
        method = wSymbolFindMethodChar( klass, wTheToken.text );
        if (method == NULL) {
            /* no such method */
            wErrorThrow( W_ERROR_SYNTAX,  "Can't find method %s.%s", klass->name, wTheToken.text );
        }
        wParseSkip();
    
        /* code holder */
        code = wCodeNew();
    
        /* not shared? */
        if (!(method->flags & W_SYM_ISSHARED)) {
            /* throw error */
            wErrorThrow( W_ERROR_SYNTAX,  "Method %s.%s is not Shared", klass->name, wTheToken.text );
        }

        /* set flags */
        meCall = W_FALSE;
        sharedCall = W_TRUE;

        /* emit a ROUTINE */
        wCodeEmit( code, W_OP_ROUTINE );
        wCodeEmit( code, method->index );

    /* expression.methodName */
    } else {
        /* doesn't use Me */
        meCall = W_FALSE;

        /* known variable typecast to a class? */
        if (wParseTokenIs(W_TOKEN_VARIABLE_NAME)
        &&  wTheToken.symbol->typeCast < 0) {
            /* code holder */
            code = wCodeNew();

            /* get the class (was stored as negative value) */
            varKlass = wSymbolLookup( -(wTheToken.symbol->typeCast) );

            /* emit the variable as an LVAL */
            wCodeEmitVar( code, wTheToken.symbol );
            wCodeEmitOp( code, W_OP_LVAL );

            wParseSkip();

            /* find the method */
            method = wSymbolFindMethodChar( varKlass, wTheToken.text );
            if (method == NULL) {
                /* no such method */
                wErrorThrow( W_ERROR_SYNTAX,  "Can't find method %s.%s", varKlass->name, wTheToken.text );
            }

            /* virtual or abstract method? */
            if (method->flags & (W_SYM_ISVIRTUAL | W_SYM_ISABSTRACT) ) {
                /* emit a MYVIRTUAL lookup */
                wCodeEmitOp( code, W_OP_VIRTUAL );
                wCodeEmit( code, wLiteralAddStr( "", wTheToken.text ) );

            } else {
                /* emit a ROUTINE */
                wCodeEmit( code, W_OP_ROUTINE );
                wCodeEmit( code, method->index );
            }
            wParseSkip();

        } else {

            /* parse the expression as an LVAL */
            code = wParseLval();
            wCodeEmitOp( code, W_OP_LVAL );

            
            /* ensure a method name follows */
            if (!wParseTokenIs(W_TOKEN_METHOD_NAME)) {
                wErrorThrow( W_ERROR_SYNTAX,  "Expected a method name, not \"%s\"", wTheToken.text );
            }
    
            /* emit a VIRTUAL lookup */
            wCodeEmit( code, W_OP_VIRTUAL );
            wCodeEmit( code, wLiteralAddStr( "", wTheToken.text ) );
            wParseSkip();
        }
    }
    
    /* parse the arglist */
    arglistCode = wParseArgList();
    count = wGrowPop( wArgCountStack );

    /* move the object pointer code to the end */
    wCodeAppend( arglistCode, code );
    code = arglistCode;

    /* what type of call? */
    if (meCall) {
        /* emit CALLMYMETHOD */
        wCodeEmitOp( code, W_OP_CALLMYMETHOD );

    } else if (sharedCall) {
        /* emit plain CALL */
        wCodeEmitOp( code, W_OP_CALL );

    } else {
        /* emit CALLMETHOD */
        wCodeEmitOp( code, W_OP_CALLMETHOD );
    }
        
    /* emit number of args in and out */
    wCodeEmit( code, count );
    wCodeEmit( code, 1 );

    return code;
}

/* fail if arg count doesn't match */
void wParseCheckArgCount( wSymbol *s, int parmCount )
{
	/* too few args? */
    if (!s->varArgs && s->optArgs == 0 ) {
		if (parmCount != s->args) {
            wErrorThrow( W_ERROR_ARGS, "The routine \"%s\" expects %d arguments, not %d",
				s->name, s->args, parmCount );
		}

	} else if (parmCount < s->args) {
        wErrorThrow( W_ERROR_ARGS, "The routine \"%s\" expects at least %d arguments, not %d",
			s->name, s->args, parmCount );

	/* too many args? */
    } else if (!s->varArgs && parmCount > s->args + s->optArgs ) {
        wErrorThrow( W_ERROR_ARGS, "The routine \"%s\" expects no more than %d arguments, not %d",
			s->name, s->args+s->optArgs, parmCount );
	}

}



/* assigment statement */
wCode *wParseStatementAssign()
{
    int returnCount, hasCommas, op;
    wToken t;
    wCode *code, *lhs, *rhs;
    wSymbol *s;

    returnCount = 0;
    hasCommas = W_FALSE;
    lhs = wCodeNew();
    while (1) {

        /* parse a left-hand side value */
        code = wParseLval();
        returnCount++;

        /* += type operator? */
        if (wParseTokenIs( W_TOKEN_INCR_SELF )) {
            /* get the operator */
            op = wTheToken.iValue;
            wParseSkip();
    
            /* can't have commas */
            if (hasCommas) {
                wErrorThrow( W_ERROR_SYNTAX,  "Can't declare multiple assignments with %c=", op );
            }

            /* get value to assign */
            rhs = wParseExpression( 0 );
    
            switch (op) {
            case '+':
                wCodeEmitOp( code, W_OP_ADD_SET );
                break;
    
            case '-':
                wCodeEmitOp( code, W_OP_SUB_SET );
                break;
    
            case '*':
                wCodeEmitOp( code, W_OP_MUL_SET );
                break;
    
            case '/':
                wCodeEmitOp( code, W_OP_DIV_SET );
                break;
    
            case '\\':
                wCodeEmitOp( code, W_OP_IDIV_SET );
                break;
    
            case '%':
                wCodeEmitOp( code, W_OP_MOD_SET );
                break;
    
            case '&':
                wCodeEmitOp( code, W_OP_CONCAT_SET );
                break;
    
    
            default:
                wErrorThrow( W_ERROR_SYNTAX,  "Operation %c= undefined", op );
            }

            /* swap order */
            wCodeAppend( rhs, code );
    
            return rhs;
        }

        /* add set opcode */
        wCodeEmitOp( code, W_OP_SET );

        /* reverse order of assignment */
        wCodeAppend( code, lhs );
        lhs = code;

        /* continue looping if there is a comma */
        if (wParseTokenIs(',')) {
            hasCommas = W_TRUE;
            wParseSkip();
            wParseOptionalSeperator();
        } else {
            break;
        }

    }


    /* simple assignment? */
    if (wParseTokenIs( W_TOKEN_EQ )) {
        wParseSkip();

        /* normal simple assignment */
        rhs = wParseExpression( 0 );
        returnCount--;
    
        if (wParseTokenIs(',')) {
            /* read args */
            while (1) {   
                /* remove comma */
                wParseSkip();
    
                /* FIXME: should this allow an optional seperator? */
    
                wCodeAppend( rhs, wParseExpression( 0 ) );
                returnCount --;
        
                /* continue looping if there is a comma */
                if (!wParseTokenIs(',')) {
                    break;
                }
            }
                       
        } else if (returnCount > 0
               && (   rhs->last == W_OP_CALL
                   || rhs->last == W_OP_CALLMETHOD
                   || rhs->last == W_OP_CALLMYMETHOD)) {
    
            /* adjust call to match expected number of returns */
            wGrowPop( rhs->pcode );
            wGrowAppend( rhs->pcode, returnCount+1 );
    
            /* prevent from adjusting in next section */
            returnCount = 0;
        }

    /* failure */
    } else {
        wParseExpect( '=', "an \"=\" sign" );
    }
    wParseSeperator();

    /* not enough parms returned? */
    for ( ; returnCount > 0; returnCount-- ) {
        wCodeEmitOp( rhs, W_OP_NOTHING );
    }
        
    /* too many parms returned? */
    if ( returnCount < 0 ) {
        wCodeEmitOp( rhs, W_OP_DROP );
        wCodeEmit( rhs, -returnCount );
    }

    /* combine both sides */
    wCodeAppend( rhs, lhs );
    return rhs;
}

void wParseCleanupTryBlocks( wCode *code, int isReturn )
{
    int i, finallyCount;

    /* process any Try clauses on the stack */
    finallyCount = 0;
    for ( i = 0; i < wBlockTypeStack->count; i++ ) {

        /* Try/Catch? */
        if (wGrowPeek( wBlockTypeStack, i ) == W_TOKEN_TRY
        ||  wGrowPeek( wBlockTypeStack, i ) == W_TOKEN_CATCH) {

            /* need to drop catch from stack? */
            if (wGrowPeek( wBlockTypeStack, i ) == W_TOKEN_TRY) {

                /* drop it, but don't go anywhere */
                wCodeEmit( code, W_OP_ENDCATCH );
                wCodeEmit( code, 1 );
            }

            /* execute Finally subroutine */
            wCodeEmit( code, W_OP_JSR );
            wCodeEmitForwardAddress( code, wFinallyStack, finallyCount );
            finallyCount++;

        } else {
            /* if it's not a RETURN statement, stop processing */
            if (!isReturn) {
                break;
            }
        }
    }

}


/* parse break, continue and redo: jump */
wCode *wParseJump( wGrow *stack, char *name )
{
    int i, finallyCount;
    wCode *code;

    /* parse remainder of statement */
    wParseSkip();
    wParseSeperator();

    /* out of scope? */
    if (!stack->count) {
        wErrorThrow( W_ERROR_SYNTAX,  "%s encountered outside of loop", name );
    }

    code = wCodeNew();

    /* process any Try clauses on the stack */
    wParseCleanupTryBlocks( code, W_FALSE );

    /* unconditional jump */
    wCodeEmitOp( code, W_OP_JMP );
    wCodeEmitForwardAddress( code, stack, 0 );

    return code;
}


/* break statement */
wCode *wParseStatementBreak()
{
    return wParseJump( wBreakStack, "Break" );
}

/* class statement */
wCode *wParseStatementClass()
{
    wCode *code;
    wSymbol *klass, *inherits;

    /* The class symbol is already created by the scanner in source.c */
    /* As a result, the error checking is minimal                     */

    /* ABSTRACT class */
    if (wParseTokenIs(W_TOKEN_ABSTRACT)) {
        wParseSkip();
    }

	wParseExpect(W_TOKEN_CLASS, "\"Class\"" );
	
    /* make sure it's not already in a class */
    if (wTheClassScope != 0) {
        wErrorThrow( W_ERROR_SYNTAX,  "Can't declare Class %s inside Class \"%s\"",
            wTheToken.text, wSymbolLookup( wTheClassScope )->name );
    }

    /* must be a class name */
    if (!wParseTokenIs(W_TOKEN_CLASS_NAME)) {
        wErrorThrow( W_ERROR_SYNTAX,  "\"%s\" is already defined", wTheToken.text );
    }
    klass = wTheToken.symbol;
    wParseSkip();

    /* Inherits? */
    if (wParseTokenIs(W_TOKEN_INHERITS)) {
        wParseSkip();

        /* must be a class */
        if (!wParseTokenIs(W_TOKEN_CLASS_NAME)) {
            wErrorThrow( W_ERROR_SYNTAX,  "Expected a class name, not \"%s\"",
                wTheToken.text );
        }

        /* copy the inherited properties */        
        inherits = wTheToken.symbol;
        klass->children = wGrowCopy( inherits->children );


        wParseSkip();
    }
    wParseSeperator();

    /* set scope to class */
    wTheClassScope = klass->index;

    /* code to build */
    code = wCodeNew();

    /* parse the block */
    while (1) {
        if (wParseIsSeperator()) {
            wParseSeperator();

        } else if (wParseTokenIs(W_TOKEN_END)) {
            wParseSkip();
            break;

        } else if (wParseTokenIs(W_TOKEN_DIM)) {
            wParseSkip();

            /* shared? */
            if (wParseTokenIs(W_TOKEN_SHARED)) {
                wParseSkip();

                /* parse shared properties declaration */
                wParseSharedProperties();
            } else {
                /* parse properties declaration */
                wParseProperties();
            }


        } else if (wParseTokenIs(W_TOKEN_SUB)
               ||  wParseTokenIs(W_TOKEN_FUNCTION)
               ||  wParseTokenIs(W_TOKEN_ABSTRACT)
               ||  wParseTokenIs(W_TOKEN_VIRTUAL)
               ||  wParseTokenIs(W_TOKEN_SHARED)) {

                /* parse method */
                wParseStatementDef();

        } else {
            wErrorThrow( W_ERROR_SYNTAX,  "Expected \"Function\" or \"Sub\", not \"%s\"",
                wTheToken.text );

        }

    }

    /* finish parsing End Class */
    wParseExpect(W_TOKEN_CLASS, "\"Class\"" );
    wParseSeperator();

    /* assign the code to the class */
    wMemTest( code, "wParseStatementClass: code @assign to class" );
    wMemTest( code->pcode, "wParseStatementClass: code->pcode @assign to class" );

    klass->pcode = wGrowCopy( code->pcode );
    wCodeFree( code );

    /* clear class scope */
    wTheClassScope = 0;

    /* nothing to execute */
    return wCodeNew();

}

/* class properties declaration */
void wParseProperties() {

    /* NOTE: this declares the properties, but doesn't allow */
    /*       for them to be initialized to start values.     */

    int symbolStartIndex, symbolEndIndex;
    wSymbol *property;

    /* range of properties of same type */
    symbolStartIndex = 0;

    /* parse list of properties */
    while (1) {

        /* create the property */
        property = wSymbolNewLocal( wTheToken.text, 0 );
        wParseSkip();

        /* start range? */
        if (symbolStartIndex == 0) {
            symbolStartIndex = property->index;
        }
        symbolEndIndex = property->index;

        /* parse the optional AS clause */
        if (wParseAsClause( symbolStartIndex, symbolEndIndex )) {
            /* reset the range */
            symbolStartIndex = 0;
        }

        /* end of list? */
        if (!wParseTokenIs(',')) {
            break;
        }

        wParseSkip();
        wParseOptionalSeperator();
    }
    wParseSeperator();

}

/* shared class properties declaration */
void wParseSharedProperties() {

    /* NOTE: this declares the properties, but doesn't allow */
    /*       for them to be initialized to start values.     */

    int scope, symbolStartIndex, symbolEndIndex;
    wSymbol *alias, *property;

    /* range of properties of same type */
    symbolStartIndex = 0;

    /* parse list of properties */
    while (1) {

        /* temporarily set the scope to global */
        scope = wTheCurrentScope;
        wTheCurrentScope = wTheGlobalScope;

        /* create a global variable to hold the value */
        alias = wSymbolNewLocal( "_shared_property", 0 );

        /* restore the scope */
        wTheCurrentScope = scope;

        /* create an aliased variable to point to the global */
        wSymbolNewLocal( wTheToken.text, alias->index );
        wParseSkip();

        /* start range? */
        if (symbolStartIndex == 0) {
            symbolStartIndex = property->index;
        }
        symbolEndIndex = property->index;

        /* parse the optional AS clause */
        if (wParseAsClause( symbolStartIndex, symbolEndIndex )) {
            /* reset the range */
            symbolStartIndex = 0;
        }

        /* end of list? */
        if (!wParseTokenIs(',')) {
            break;
        }

        wParseSkip();
        wParseOptionalSeperator();
    }
    wParseSeperator();

}


/* CLOSE statement */
wCode *wParseStatementClose()
{
    /* CLOSE            close all files */
    /* CLOSE #n         close file n    */

    wCode *code;

    wParseSkip();

    /* optional file handle */
    if (wParseTokenIs('#')) {
        wParseSkip();

        /* parse the handle number */
        code = wParseExpression( 0 );

        /* emit a FILECLOSE */
        wCodeEmitOp( code, W_OP_FILECLOSE );

    } else {
        /* emit a FILECLOSEALL to close all files */
        code = wCodeNew();
        wCodeEmitOp( code, W_OP_FILECLOSEALL );
    }
    wParseSeperator();

    return code;
}

/* CONST name [= expr] [ ... ] */
wCode *wParseStatementConst()
{
    wCode *code;
    wSymbol *symbol;

    wParseSkip();
    wParseOptionalSeperator();
    
    code = wCodeNew();
    while (1) {
        /* undefined token? */
        if (!wParseTokenIs(W_TOKEN_UNDEFINED)) {
            /* error */
            wErrorThrow( W_ERROR_SYNTAX,  "\"%s\" is already defined", wTheToken.text );
        }

        /* create a new variable */
        symbol = wSymbolNewLocal( wTheToken.text, 0 );

        /* mark it as a constant */
        symbol->type = W_SYM_CONSTANT;
        wParseSkip();

        /* parse '=' sign */
        wParseExpect( W_TOKEN_EQ, "\"=\"" );

        /* get the expression */
        wCodeAppend( code, wParseExpression( 0 ) );

        /* assign to the constant */
        wCodeEmitOp( code, W_OP_VARIABLE );
        wCodeEmit( code, symbol->stackPos );
        wCodeEmitOp( code, W_OP_SET );

        /* comma? */
        if (!wParseTokenIs(',')) {
            break;
        }
        wParseSkip();
        wParseOptionalSeperator();
    }
    wParseSeperator();

    return code;
}

/* continue statement */
wCode *wParseStatementContinue()
{
    return wParseJump( wContinueStack, "Continue" );
}

/* FUNCTION or SUB ... */
wCode *wParseStatementDef()
{

    int flags, symType, traceLine;
    wSymbol *s, *parm, *klass;
	wCode *code, *handlesCode;

    /* get the trace line for SETTYPE */
    traceLine = wReadLine;

    /* SHARED? */
    if (wParseTokenIs(W_TOKEN_SHARED)) {
        if (!wTheClassScope) {
            wErrorThrow( W_ERROR_SYNTAX,  "Can't define a Shared method outside a Class" );
        }
        flags = W_SYM_ISSHARED;
        wParseSkip();

    } else if (wParseTokenIs(W_TOKEN_ABSTRACT)) {
        flags = W_SYM_ISABSTRACT;
        wParseSkip();

    /* VIRTUAL? */
    } else if (wParseTokenIs(W_TOKEN_VIRTUAL)) {
        flags = W_SYM_ISVIRTUAL;
        wParseSkip();

    } else {
        flags = 0;
    }

    /* FUNCTION or SUB? */
    if (wParseTokenIs(W_TOKEN_SUB)) {
        symType = W_SYM_SUB;

    } else if (wParseTokenIs(W_TOKEN_FUNCTION)) {
        symType = W_SYM_FUNCTION;

    } else {
        wErrorThrow( W_ERROR_SYNTAX,  "Expected \"Sub\" or \"Function\", not \"%s\"",
            wTheToken.text );
    }
    wParseSkip();

    /* check scope */
    if (wTheCurrentScope != wTheGlobalScope) {
        wErrorThrow( W_ERROR_SYNTAX,  "Can't define a routine inside \"%s\"",
            wSymbolLookup( wTheCurrentScope  )->name );
    }

    /* SUB NEW( ... ) */
    if (wParseTokenIs(W_TOKEN_NEW)) {
        if (!wTheClassScope) {
            wErrorThrow( W_ERROR_SYNTAX,  "Can't define a New method outside a Class" );
        }

        /* try to find the NEW method */
        wTheToken.symbol = wSymbolFind( "new", wTheClassScope );
    }

    /* not defined? */
    if (wTheToken.symbol == NULL) {
        wErrorThrow( W_ERROR_SYNTAX,  "Source scanner failed to register routine \"%s\"",
            wTheToken.text );
    }

    /* get defined symbol */
    s = wTheToken.symbol;

    /* zap the args */
    s->args = 0;
    s->optArgs = 0;
    s->varArgs = W_FALSE;

    /* set as current scope */
    wTheCurrentScope = s->index;

    /* move past the method name */
    wParseSkip();

    /* init code */
    code = wCodeNew();
    handlesCode = wCodeNew();


    /* parse the arg list */
    wParseExpect('(', "an opening \"(\"");
    if (!wParseTokenIs(')')) {

        while (1) {
            /* elipsis? */
            if (wParseTokenIs(W_TOKEN_3DOTS)) {
                wParseSkip();
                s->varArgs = W_TRUE;
                break;
            }
            
            /* add to the local list */
            parm = wSymbolNewLocal( wTheToken.text, 0 );
            wParseSkip();

            /* optional AS <datatype> */
            wParseAsClause( parm->index, parm->index );

            /* assignment? */
            if (wParseTokenIs(W_TOKEN_EQ)) {
                /* increment optional arg count */
                s->optArgs++;

                /* skip the "=" sign */
                wParseSkip();

                /* next free label */
                wCodePushLabel( wMiscStack );

                /* jump past if arg not missing */
                wCodeEmitOp( code, W_OP_MISSING );
                wCodeEmit( code, s->args+s->optArgs );

                wCodeEmitOp( code, W_OP_JMPF );
                wCodeEmitForwardAddress( code, wMiscStack, 0 );

                /* parse the expression that follows */
                wCodeAppend( code, wParseExpression( 0 ) );

                /* create an assignment */
                wCodeEmitOp( code, W_OP_VARIABLE );
                wCodeEmit( code, s->args+s->optArgs );
                wCodeEmitOp( code, W_OP_SET );

                /* backpatch */
                wCodeBackpatch( code, wGrowPop( wMiscStack ), wCodeHere( code ) );

            /* should have been assigned? */
            } else if (s->optArgs) {
                wErrorThrow( W_ERROR_SYNTAX,  "Expected an \"=\"" );

            } else {
                /* increment arg count */
                s->args++;
            }


            /* exit if not a comma, otherwise skip */
            if (wParseTokenIs(',')) {
                wParseSkip();
                /* FIXME: should this allow an optional seperator? */
            } else {
                break;
            }
        }
    }
    wParseExpect(')', "a closing \")\"");
	
    /* optional HANDLES callback */
    wParseHandles(handlesCode, s);
	
    wParseSeperator();

    /* no body if ABSTRACT */
    if (s->flags & W_SYM_ISABSTRACT) {
        /* no code in body */
        wCodeFree( code );

    } else {

        /* get the code */
        wCodeAppend( code, wParseBlock() );
    
        /* add a final return */
        /* can't test for prior RETURN, because it may be inside an ENDIF */
        wCodeEmitOp( code, W_OP_RETURN );
    
        wParseExpect(W_TOKEN_END, "\"End\"");
        if (symType == W_SYM_FUNCTION) {
            wParseExpect(W_TOKEN_FUNCTION, "\"Function\"");
        } else {
            wParseExpect(W_TOKEN_SUB, "\"Sub\"");
        }
    
        /* add typecasts to the code */
        code = wCodeAddTypeCast( code, s->index, traceLine );
    
        /* assign the code to the function */
        s->pcode = wGrowCopy( code->pcode );
        wCodeFree( code );

    }

    /* restore scope */
    wTheCurrentScope = wTheGlobalScope;

    /* code to execute */
    return handlesCode;
}


/* HANDLES directive */
wCode *wParseHandles( wCode *code, wSymbol *s )
{
    /* creates deferred handles code */

    int handlesEvent, eventName;
    char *lowerCaseName;
    wSymbol *handlesObject;

    /* HANDLES? */
    if (wParseTokenIs(W_TOKEN_HANDLES)) {
        /* move past HANDLES */
        wParseSkip();

        /* there can be multiple callbacks */
        while (W_TRUE) {

            /* expect OBJECT.EVENT */
            if (!wParseTokenIs(W_TOKEN_DOTPROPERTY)
             && !wParseTokenIs(W_TOKEN_DOTMETHOD)) {
                wErrorThrow( W_ERROR_SYNTAX,  "Expected <control>.<event>, not \"%s\"", wTheToken.text );
            }
            wParseSkip();

            /* the variable holding the control */
            handlesObject = wSymbolFind( wTheToken.text, wTheCurrentScope );
            if (handlesObject == NULL) {
            }
            if (wParseTokenIs(W_TOKEN_VARIABLE_NAME)
            || wParseTokenIs(W_TOKEN_CONSTANT_NAME)) {
                wCodeEmitVar( code, wTheToken.symbol );
                wCodeEmitOp( code, W_OP_GET );
            } else {
                wErrorThrow( W_ERROR_SYNTAX,  "\"%s\" must be a variable or constant", wTheToken.text );
            }
            wParseSkip();

            /* emit the event name in lower case */
            lowerCaseName = wCharCopyToLower( wTheToken.text );
            wCodeEmitString( code, lowerCaseName );
            wFree( lowerCaseName );
            wParseSkip();

            /* if there's an id, it's in parenthesis */
            if (wParseTokenIs('(')) {
                wParseSkip();
                wParseOptionalSeperator();

                /* parse the id */
                wCodeAppend( code, wParseOperand() );

                /* parse the closing paren */
                wParseExpect(')', "a closing \")\"" );

                /* emit HANDLESID opcode and routine index */
                wCodeEmitOp( code, W_OP_HANDLESID );
                wCodeEmit( code, s->index );


            } else {
                /* emit HANDLES opcode and routine index */
                wCodeEmitOp( code, W_OP_HANDLES );
                wCodeEmit( code, s->index );
            }

            /* exit if no comma */
            if (!wParseTokenIs(',')) {
                break;
            }
            wParseSkip();
            wParseOptionalSeperator();
        }
    }

    return code;
}


/* DIM statement */
wCode *wParseStatementDim()
{
    int indexCount, symbolStartIndex, symbolEndIndex;
    wCode *code, *tmpCode;
    wSymbol *s;

    code = wCodeNew();

    wParseSkip();
    wParseOptionalSeperator();

    /* count of variables in dim clause of same type */
    symbolStartIndex = 0;

    /* parse the names */
    while (1) {
        /* valid token? */
        if (wParseTokenIs(W_TOKEN_VARIABLE_NAME)
        ||  wParseTokenIs(W_TOKEN_UNDEFINED)) {

            /* create a new variable */
            s = wSymbolNewLocal( wTheToken.text, 0 );

            /* add to count */
            if (symbolStartIndex == 0) {
                /* start range */
                symbolStartIndex = s->index;
            }
            symbolEndIndex = s->index;
    
        } else {
            wErrorThrow( W_ERROR_SYNTAX,  "Expected a variable name, not \"%s\"", wTheToken.text );
        }
        wParseSkip();

        /* array? */
        if (wParseTokenIs('[')) {

            indexCount = 1;
            wParseSkip();

            while( 1 ) {
                /* parse the index */
                tmpCode = wParseExpression( 0 );

                /* to? */
                if (wParseTokenIs(W_TOKEN_TO)) {
                    /* skip 'TO' */
                    wParseSkip();

                    /* add low end */
                    wCodeAppend( code, tmpCode );

                    /* add high end */
                    wCodeAppend( code, wParseExpression( 0 ) );

                } else {
                    /* default low end */
                    /* FIXME: should be able to set default to 1 or 0 */
                    wCodeEmitNumber( code, 0 );
                    /* add high end */
                    wCodeAppend( code, tmpCode );
                }

                if (wParseTokenIs(']')) {
                    break;
                } else if (wParseTokenIs(',')) {
                    indexCount++;
                    wParseSkip();
                } else {
                    wErrorThrow( W_ERROR_SYNTAX,  "Expected \"]\" or \",\", not \"%s\"",
                        wTheToken.text );
                }
            }
            wParseSkip();
            if (indexCount > 4) {
                wErrorThrow( W_ERROR_SYNTAX,  "Arrays can only have 4 indexes" );
            }

            /* optional AS <datatype> */
            if (wParseAsClause( symbolStartIndex, symbolEndIndex )) {
                /* done with variables of this type */
                symbolStartIndex = 0;
            }

            /* default value? */
            if (wParseTokenIs(W_TOKEN_EQ)) {
                wParseSkip();
                /* push expression on stack */
                wCodeAppend( code, wParseExpression( 0 ) );

                /* create initialized array */
                wCodeEmitOp( code, W_OP_INITARRAY );
                wCodeEmit( code, indexCount );

            } else {
                /* create uninitialized array */
                wCodeEmitOp( code, W_OP_CREATEARRAY );
                wCodeEmit( code, indexCount );

            }

            /* assign it to the variable */
            wCodeEmitVar( code, s );
            wCodeEmitOp( code, W_OP_SET );


        } else {

            /* optional AS <datatype> clause */
            if (wParseAsClause( symbolStartIndex, symbolEndIndex )) {
                /* done with variables of this type */
                symbolStartIndex = 0;
            }

            /* optional assignment */
            if (wParseTokenIs(W_TOKEN_EQ)) {
                wParseSkip();
                /* parse the expression */
                wCodeAppend( code, wParseExpression( 0 ) );
    
                /* assign it to the variable */
                wCodeEmitVar( code, s );
                wCodeEmitOp( code, W_OP_SET );
    
            }

        }

        if (!wParseTokenIs(',')) {
            break;
        }
        wParseSkip();
        wParseOptionalSeperator();
    }
    wParseSeperator();

    return code;

}


/* END statement */
wCode *wParseStatementEnd()
{
    wCode *code;

    wParseSkip();

    /* emit a HALT */
    code = wCodeNew();
    wCodeEmitOp( code, W_OP_HALT );

    wParseSeperator();

    return code;
}

/* ERASE statement */
wCode *wParseStatementErase()
{
    wCode *code;
    wSymbol *symbol;

    /* skip ERASE */
    wParseSkip();

    /* get value to erase */
    code = wParseExpression( 0 );

    /* opcode */
    wCodeEmitOp( code, W_OP_ERASEARRAY );

    return code;
}

/* EXIT statement */
wCode *wParseStatementExit()
{
    wCode *code;
    wSymbol *symbol;

    /* skip exit */
    wParseSkip();

    /* code holder */
    code = wCodeNew();

    /* exit function? */
    if (wParseTokenIs( W_TOKEN_FUNCTION )) {
        /* in a function? */
        symbol = wSymbolLookup( wTheCurrentScope );
        if (symbol->type != W_SYM_FUNCTION ) {
            wErrorThrow( W_ERROR_SYNTAX,  "EXIT FUNCTION encountered outside of Function" );
        }
        wParseSkip();
        wParseSeperator();

        /* process any Try clauses on the stack */
        wParseCleanupTryBlocks( code, W_TRUE );

        /* emit a return */
        wCodeEmitOp( code, W_OP_RETURN );
        return code;
    }

    /* exit sub? */
    if (wParseTokenIs( W_TOKEN_SUB )) {
        /* in a sub? */
        symbol = wSymbolLookup( wTheCurrentScope );
        if (symbol->type != W_SYM_SUB ) {
            wErrorThrow( W_ERROR_SYNTAX,  "EXIT SUB encountered outside of Sub" );
        }
        wParseSkip();
        wParseSeperator();

        /* process any Try clauses on the stack */
        wParseCleanupTryBlocks( code, W_TRUE );

        /* emit a return */
        wCodeEmitOp( code, W_OP_RETURN );
        return code;        
    }


    /* make sure there's a loop to exit from */
    if (wBreakStack->count == 0) {
        wErrorThrow( W_ERROR_SYNTAX,  "EXIT encountered outside of FOR or WHILE" );
    }


    /* match to type */
    if (wGrowPeek( wBlockTypeStack, 0 ) == W_TOKEN_FOR) {
        wParseExpect( W_TOKEN_FOR, "\"For\"" );
        /* nothing on stack */

    } else if (wGrowPeek( wBlockTypeStack, 0 ) == W_TOKEN_FOREACH ) {
        /* FIXME: should this allow End For Each ? */
        wParseExpect( W_TOKEN_FOR, "\"For\"" );

    } else if (wGrowPeek( wBlockTypeStack, 0 ) == W_TOKEN_WHILE) {
        wParseExpect( W_TOKEN_WHILE, "\"While\"" );

    } else {
        wErrorThrow( W_ERROR_SYNTAX,  "Internal error, bad data on BlockType stack" );
    }
    wParseSeperator();

    /* unconditional jump back to break */
    wCodeEmitOp( code, W_OP_JMP );
    wCodeEmitForwardAddress( code, wBreakStack, 0 );

    return code;
}

/* for statement */
wCode *wParseStatementFor()
{
    int continueTo, breakTo, elseTo, forTo, loopOp, explicitFlag;
    wCode *code;
    wSymbol *s1, *sLoopMax, *sLoopStep;

    wParseSkip();

    /* FOR EACH? */
    if (wParseTokenIs(W_TOKEN_EACH)) {
        return wParseStatementForEach();
    }

    /* labels */
    wGrowAppend( wForStack, --wTheNextLabel );
    wGrowAppend( wRedoStack, --wTheNextLabel );
    wGrowAppend( wContinueStack, --wTheNextLabel );
    wGrowAppend( wBreakStack, --wTheNextLabel );
    wGrowAppend( wElseStack, --wTheNextLabel );

    /* loop type */
    wGrowAppend( wBlockTypeStack, W_TOKEN_FOR );

    /* flag that it's not set */
    elseTo = 0;
    continueTo = 0;

    /* loop variables don't have to be declared */
    explicitFlag = wTheOptionExplicit;
    wTheOptionExplicit = W_FALSE;

    /* loop index: variable does not have to be declared */
    s1 = wParseVariableName();
    wParseSkip();

    /* restore option explicit state */
    wTheOptionExplicit = explicitFlag;


    wParseExpect(W_TOKEN_EQ, "\"=\"");

    /* start value */
    code = wParseExpression( 0 );

    wParseExpect( W_TOKEN_TO, "\"To\"" );

    /* to value */
    wCodeAppend( code, wParseExpression( 0 ) );

    /* step? */
    if (wParseTokenIs(W_TOKEN_STEP)) {
        wParseSkip();
        wCodeAppend( code, wParseExpression( 0 ) );        
        wCodeEmitOp( code, W_OP_FORPREP );
        loopOp = W_OP_FORSTEP;

        /* needs two locals */
        sLoopMax  = wSymbolNewLocal( "_loopMax", 0 );
        sLoopStep = wSymbolNewLocal( "_loopStep", 0 );

    } else {
        /* no step value */
        wCodeEmitOp( code, W_OP_FORPREP1 );
        loopOp = W_OP_FORSTEP1;

        /* only needs loop max */
        sLoopMax  = wSymbolNewLocal( "_loopMax", 0 );
    }

    /* the loop index */
    wCodeEmitVarIndex( code, s1 );
    wCodeEmitVarIndex( code, sLoopMax );

    /* jump out of loop */
    wCodeEmitOp( code, W_OP_JMPF );
    wCodeEmitForwardAddress( code, wBreakStack, 0 );

    /* jump target for FORLOOP */
    forTo = wCodeHere( code );

    /* parse block inside loop */
    wCodeAppend( code, wParseBlock() );

    /* else statement? */
    if (wParseTokenIs(W_TOKEN_ELSE)) {
        wCodeEmitTrace( code );
        wParseSkip();
        wParseSeperator();

        /* jump target for continue */
        continueTo = wCodeHere( code );

        /* LOOPSTEP - the loop index and max */
        wCodeEmitOp( code, loopOp );
        wCodeEmitVarIndex( code, s1 );
        wCodeEmitVarIndex( code, sLoopMax );

        /* jump to the top of the loop */
        wCodeEmitOp( code, W_OP_JMPT );
        wCodeEmitForwardAddress( code, wForStack, 0 );

        /* set the else label address */
        elseTo = wCodeHere( code );

        /* parse the else clause */
        wCodeAppend( code, wParseBlock() );
    }

    /* no else clause? */
    if (elseTo == 0) {

        /* jump target for continue */
        continueTo = wCodeHere( code );

        /* LOOPSTEP - the loop index and max */
        wCodeEmitOp( code, loopOp );
        wCodeEmitVarIndex( code, s1 );
        wCodeEmitVarIndex( code, sLoopMax );

        /* jump to the top of the loop */
        wCodeEmitOp( code, W_OP_JMPT );
        wCodeEmitForwardAddress( code, wForStack, 0 );

        /* else label jumps to break label */
        elseTo = wCodeHere( code );
    }

    /* break jumps to end of code */
    breakTo = wCodeHere( code );

    if (wParseTokenIs(W_TOKEN_END)) {
        wParseSkip();
        wParseExpect(W_TOKEN_FOR, "\"End\"" );
    } else {
        wParseExpect(W_TOKEN_NEXT, "\"Next\"" );
        if (wParseTokenIs(W_TOKEN_VARIABLE_NAME)) {
            if (wTheToken.symbol != s1) {
                wErrorThrow( W_ERROR_SYNTAX,  "Expected NEXT %s, not NEXT %s",
                    s1->name, wTheToken.text );
            }
            wParseSkip();
        }
    }
    wParseSeperator();

    /* backpatch for */
    wCodeBackpatch( code, wGrowPop( wForStack ), forTo );
    wCodeBackpatch( code, wGrowPop( wRedoStack ), forTo );
    wCodeBackpatch( code, wGrowPop( wContinueStack ), continueTo );
    wCodeBackpatch( code, wGrowPop( wBreakStack ), breakTo );
    wCodeBackpatch( code, wGrowPop( wElseStack ), elseTo );

    /* remove from loop type stack */
    wGrowPop( wBlockTypeStack );

    return code;
}

/* for each statement */
wCode *wParseStatementForEach()
{
    int continueTo, breakTo, elseTo, forTo, var1, var2, var3;
    wCode *code;
    wSymbol *s1;

    wParseSkip();

    /* labels */
    wGrowAppend( wForStack, --wTheNextLabel );
    wGrowAppend( wContinueStack, --wTheNextLabel );
    wGrowAppend( wBreakStack, --wTheNextLabel );
    wGrowAppend( wElseStack, --wTheNextLabel );

    /* loop type */
    wGrowAppend( wBlockTypeStack, W_TOKEN_FOREACH );

    /* flag that it's not set */
    elseTo = 0;
    continueTo = 0;

    /* locals to hold the collection and the index */
    s1  = wSymbolNewLocal( "_collection", 0 );
    var1 = wCodeGetVarIndex( s1 );
    s1  = wSymbolNewLocal( "_index", 0 );

    /* first variable */
    s1 = wParseVariableName();
    var2 = wCodeGetVarIndex( s1 );
    wParseSkip();

    /* optional second variable */
    if (wParseTokenIs(',')) {
        wParseSkip();

        /* second variable */
        s1 = wParseVariableName();
        var3 = wCodeGetVarIndex( s1 );
        wParseSkip();

    } else {
        /* no second arg */
        var3 = 0;
    }

    wParseExpect(W_TOKEN_IN, "In");
    /* expression */
    code = wParseExpression( 0 );

    /* prep for loop */
    wCodeEmitOp( code, W_OP_FOREACHPREP );
    wCodeEmit( code, var1 );
    wCodeEmit( code, var2 );
    wCodeEmit( code, var3 );

    /* jump out of loop? */
    wCodeEmitOp( code, W_OP_JMPF );
    wCodeEmitForwardAddress( code, wBreakStack, 0 );

    /* jump target for FOREACHLOOP */
    forTo = wCodeHere( code );

    /* parse block inside loop */
    wCodeAppend( code, wParseBlock() );

    /* else statement? */
    if (wParseTokenIs(W_TOKEN_ELSE)) {
        wCodeEmitTrace( code );
        wParseSkip();
        wParseSeperator();

        /* jump target for continue */
        continueTo = wCodeHere( code );

        /* FOREACHLOOP */
        wCodeEmitOp( code, W_OP_FOREACHLOOP );
        wCodeEmit( code, var1 );
        wCodeEmit( code, var2 );
        wCodeEmit( code, var3 );
    
        /* jump out of loop? */
        wCodeEmitOp( code, W_OP_JMPF );
        wCodeEmitForwardAddress( code, wForStack, 0 );

        /* set the else label address */
        elseTo = wCodeHere( code );

        /* parse the else clause */
        wCodeAppend( code, wParseBlock() );
    }

    /* no else clause? */
    if (elseTo == 0) {

        /* jump target for continue */
        continueTo = wCodeHere( code );

        /* FOREACHLOOP */
        wCodeEmitOp( code, W_OP_FOREACHLOOP );
        wCodeEmit( code, var1 );
        wCodeEmit( code, var2 );
        wCodeEmit( code, var3 );
    
        /* jump out of loop? */
        wCodeEmitOp( code, W_OP_JMPF );
        wCodeEmitForwardAddress( code, wForStack, 0 );

        /* else label jumps to break label */
        elseTo = wCodeHere( code );
    }

    /* break jumps to end of code */
    breakTo = wCodeHere( code );

    /* clean up */
    wCodeEmitOp( code, W_OP_FREE );
    wCodeEmit( code, var1 );    

    if (wParseTokenIs(W_TOKEN_END)) {
        wParseSkip();
        wParseExpect(W_TOKEN_FOR, "\"End\"" );
    } else {
        wParseExpect(W_TOKEN_NEXT, "\"Next\"" );
        if (wParseTokenIs(W_TOKEN_VARIABLE_NAME)) {
            if (wTheToken.symbol != s1) {
                wErrorThrow( W_ERROR_SYNTAX,  "Expected NEXT %s, not NEXT %s",
                    s1->name, wTheToken.text );
            }
            wParseSkip();
        }
    }
    wParseSeperator();

    /* backpatch for */
    wCodeBackpatch( code, wGrowPop( wForStack ), forTo );
    wCodeBackpatch( code, wGrowPop( wContinueStack ), continueTo );
    wCodeBackpatch( code, wGrowPop( wBreakStack ), breakTo );
    wCodeBackpatch( code, wGrowPop( wElseStack ), elseTo );

    /* remove from loop type stack */
    wGrowPop( wBlockTypeStack );

    return code;
}

/* INPUT ["prompt";] lval */
wCode *wParseStatementInput()
{
    wCode *code;

    wParseSkip();

    /* initialize */
    code = wCodeNew();

    /* optional string for prompt */
    if (wParseTokenIs(W_TOKEN_STRING)) {
        /* emit the string and code to print it */
        wCodeEmitString( code, wTheToken.text );
        wParseSkip();

        /* print the prompt */
        wCodeEmitOp( code, W_OP_PRINT );

        /* followed by semicolon or comma */
        if (!wParseTokenIs(',') && !wParseTokenIs(';')) {
            wErrorThrow( W_ERROR_SYNTAX,  "Expected \";\" or \",\", not \"%s\"", wTheToken.text );
        }
        wParseSkip();
    }

    /* value to store into */
    wCodeAppend( code, wParseLval() );
    wCodeEmitOp( code, W_OP_LVAL );


    /* encode a keyboard read */
    wCodeEmit( code, W_OP_READ );

    return code;
}



/* OPEN file FOR mode AS # handle */
wCode *wParseStatementOpen()
{
    wCode *code;

    wParseSkip();

    /* file name */
    code = wParseExpression( 0 );

    wParseExpect(W_TOKEN_FOR, "For" );

    /* mode */
    wCodeEmitOp( code, W_OP_INTEGER );
    switch (wTheToken.type) {
    case W_TOKEN_INPUT:
        wCodeEmit( code, W_FILE_MODE_INPUT );
        break;
    case W_TOKEN_OUTPUT:
        wCodeEmit( code, W_FILE_MODE_OUTPUT );
        break;    
    default:
        /* append isn't defined as a token so the append() function won't conflict */
        if (strcmp( "append", wTheToken.text ) == 0 ) {
            wCodeEmit( code, W_FILE_MODE_APPEND );
            break;
        } else {
            wErrorThrow( W_ERROR_SYNTAX,  "Expected Input, Output or Append, not \"%s\"", wTheToken.text );
        }
    }
    wParseSkip();

    wParseExpect(W_TOKEN_AS, "As" );
    wParseExpect('#', "\"#\"");

    /* filename */
    wCodeAppend( code, wParseExpression( 0 ) );

    wCodeEmit( code, W_OP_FILEOPEN );

    return code;

}


/* call FUNCTION NAME */
wCode *wParseStatementRoutineName( int returnCount )
{
    int argCount = 0;
    wSymbol *s;
    wCode *code;

    /* get the routine name */
    s = wTheToken.symbol;

    /* class method */
    if (s->scope == wTheClassScope) {
        if (!(s->flags & W_SYM_ISSHARED)) {
            return wParseDotMethod( W_TRUE );
        }
    }

    /* move to next token */
    wParseSkip();

    /* parse the args */
    wParseExpect('(', "an opening \"(\"" );

    code = wCodeNew();
    if (!wParseTokenIs(')')) {
        while (1) {
            /* read an expression */
            wCodeAppend( code, wParseExpression( 0 ) );
            argCount++;
    
            /* exit if no comma */
            if (!wParseTokenIs(',')) {
                break;
            }
            wParseSkip();
            wParseOptionalSeperator();
        }
    }
    wParseExpect(')', "a closing \")\"" );

    /* check args */
    wParseCheckArgCount( s, argCount );

    /* the call */
    wCodeEmitCall( code, s, argCount, returnCount );

    return code;
}


/* SHARED globalName ... */
wCode *wParseStatementShared()
{
    wParseSkip();
    wParseOptionalSeperator();

    /* not in a routine? */
    if (wTheCurrentScope == wTheGlobalScope) {
        wErrorThrow( W_ERROR_SYNTAX,  "Illegal outside Sub or Function" );
    }

    while (1) {

        /* variable? */
        if (!wParseTokenIs(W_TOKEN_VARIABLE_NAME)) {
            wErrorThrow( W_ERROR_SYNTAX,  "Expected a global variable, not \"%s\"\n",
                wTheToken.text );
        }

        /* not global? */
        if (wTheToken.symbol->scope != wTheGlobalScope) {
            wErrorThrow( W_ERROR_SYNTAX,  "\"%s\" is not global", wTheToken.text );
        }

        /* create a local symbol that points to the global */
        wSymbolNewLocal( wTheToken.text, wTheToken.symbol->index );
        wParseSkip();

        /* comma? */
        if (!wParseTokenIs(',')) {
            break;
        }
        wParseSkip();
        wParseOptionalSeperator();
    }
    wParseSeperator();

    /*  doesn't generate any executable code */
    return wCodeNew();
}

/* if statement */
wCode *wParseStatementIf()
{
    int token;
    wCode *code;

    wParseSkip();

    /* push state pointers */
    wGrowAppend( wElseStack, --wTheNextLabel );
    wGrowAppend( wEndIfStack, --wTheNextLabel );

    code = wParseExpression( 0 );
    wCodeEmitOp( code, W_OP_JMPF );
    wCodeEmitForwardAddress( code, wElseStack, 0 );
    wParseExpect(W_TOKEN_THEN, "\"Then\"");

    // statement follows?
    if (!wParseIsSeperator()) {
        // single line IF statement
        wCodeAppend( code, wParseStatement() );

        /* backpatch else, leaving on stack */
        wCodeBackpatch( code, wGrowPeek( wElseStack, 0 ), wCodeHere(code) );

    } else {

        wParseSeperator();
    
        while (1) {
            wCodeAppend( code, wParseBlock() );
    
            /* "end if" */
            if (wParseTokenIs(W_TOKEN_END)) {
                break;
    
            /* "elseif" */
            } else if (wParseTokenIs(W_TOKEN_ELSEIF)) {
                wParseSkip();
                token = W_TOKEN_ELSEIF;
    
            /* "else" or "else if"? */
            } else if (wParseTokenIs(W_TOKEN_ELSE)) {
                wParseSkip();
                if (wParseTokenIs(W_TOKEN_IF)) {
                    wParseSkip();
                    /* elseif */
                    token = W_TOKEN_ELSEIF;
                } else {
                    /* else */
                    token = W_TOKEN_ELSE;
                }
            }
        
            /* parse the remainder of the else/elseif */
            if (token == W_TOKEN_ELSE) {
                wParseSeperator();
    
                /* jump to end */
                wCodeEmitOp( code, W_OP_JMP );
                wCodeEmitForwardAddress( code, wEndIfStack, 0 );
    
                /* backpatch else, leaving on stack */
                wCodeBackpatch( code, wGrowPeek( wElseStack, 0 ), wCodeHere(code) );
    
            /* elseif */
            } else {
                /* code a jump to the end */
                wCodeEmitOp( code, W_OP_JMP );
                wCodeEmitForwardAddress( code, wEndIfStack, 0 );
    
                /* backpatch else, leaving on stack */
                wCodeBackpatch( code, wGrowPeek( wElseStack, 0 ), wCodeHere(code) );
    
                /* expression */
                wCodeAppend( code, wParseExpression( 0 ) );
                wParseExpect( W_TOKEN_THEN, "\"Then\"" );
                wParseSeperator();
    
                /* test */
                wCodeEmitOp( code, W_OP_JMPF );
                wCodeEmitForwardAddress( code, wElseStack, 0 );
    
            }                                            
        }
    
        wParseExpect(W_TOKEN_END, "\"End\"" );
        wParseExpect(W_TOKEN_IF, "\"If\"" );
        wParseSeperator();

    }

    /* backpatch */
    wCodeBackpatch( code, wGrowPop( wEndIfStack ), wCodeHere( code ) );
    wCodeBackpatch( code, wGrowPop( wElseStack ), wCodeHere( code ) );
    return code;
}

/* option ... */
wCode *wParseStatementOption()
{
    int option, flag, value, parseOnOffToken;
    wParseSkip();

    /* by default, assume has on/off parameter */
    parseOnOffToken = 1;

    /* I didn't want to declare EXPLICT, STRICT, ON and OFF as keywords */

    /* which option? */
    if (strcmp( wTheToken.text, "explicit") == 0) {
        option = 1;

    } else if (strcmp( wTheToken.text, "strict") == 0) {
        option = 2;

    } else if (strcmp( wTheToken.text, "backslash") == 0) {
        option = 3;

    } else if (strcmp( wTheToken.text, "stack") == 0) {
        option = 4;

        /* get the call depth */
        wParseSkip();
        if (wParseTokenIs(W_TOKEN_FLOAT)) {
            wTheMaxCallDepth = wTheToken.fValue;

        } else {
            wErrorThrow( W_ERROR_SYNTAX,  "Expected integer value, not \"%s\"",
                wTheToken.text );
        }

        /* don't parse on/off */
        parseOnOffToken = 0;

    } else {
        wErrorThrow( W_ERROR_SYNTAX,  "Expected \"Backslash\", \"Explicit\", \"Stack\" or \"Strict\" not \"%s\"",
            wTheToken.text );
    }
    wParseSkip();


    /* ON or OFF? */

    if (parseOnOffToken) {
        if (strcmp( wTheToken.text, "on") == 0) {
            flag = W_TRUE;
            wParseSkip();
        } else if (strcmp( wTheToken.text, "off") == 0) {
            flag = W_FALSE;
            wParseSkip();
        } else {
            /* none specified, assume ON */
            flag = W_TRUE;
        }
    }
    wParseSeperator();


    /* set the value */
    switch (option) {
    case 1:
        wTheOptionExplicit = flag;
        break;
    case 2:
        wTheOptionStrict = flag;
        break;
    case 3:
        wTheOptionBackslash = flag;
        break;
    }

    /* no executable code generated */
    return wCodeNew();
}

/* LINE INPUT #handle, lval */
wCode *wParseStatementLine()
{
    wCode *code;

    wParseSkip();

    /* INPUT */
    wParseExpect(W_TOKEN_INPUT, "Input" );

    /* file handle */
    wParseExpect('#', "\"#\"" );
    code = wParseExpression( 0 );

    /* comma */
    wParseExpect(',', "\",\"" );

    /* value to store into */
    wCodeAppend( code, wParseLval() );
    wCodeEmitOp( code, W_OP_LVAL );


    /* encode a file read */
    wCodeEmit( code, W_OP_FILEREAD );

    return code;
}

/* print statement */
wCode *wParseStatementPrint()
{
    wCode *code;
    int redirected;

    wParseSkip();

    if (wParseTokenIs('#')) {
        wParseSkip();
        /* direct print to requested output */
        code = wParseExpression( 0 );
        wCodeEmitOp( code, W_OP_REDIRECT );
        wParseExpect(',', "a comma (\",\")");
        redirected = W_TRUE;

    } else {
        /* direct code to standard output */
        code = wCodeNew();
        redirected = W_FALSE;
    }

    /* empty? */
    if (wParseIsSeperator()) {
        wCodeEmitOp( code, W_OP_EMITLN );
        return code;
    }

    /* parse the expressions */
    while (1) {

        /* preceeding ; */
        if (wParseTokenIs(';')) {
            wParseSkip();
            if (wParseIsSeperator()) {
                break;
            }

        /* preceeding , */
        } else if (wParseTokenIs(',')) {
            wParseSkip();
            wCodeEmitOp( code, W_OP_EMITTAB );
            if (wParseIsSeperator()) {
                wCodeEmitOp( code, W_OP_EMITLN );
                break;
            }

        /* end of print block */
        } else if (wParseIsSeperator()) {
            break;

        } else {
            wCodeAppend( code, wParseExpression( 0 ) );

            /* trailing ; */
            if (wParseTokenIs(';')) {
                wParseSkip();
                wCodeEmitOp( code, W_OP_PRINT );

            /* trailing , */
            } else if (wParseTokenIs(',')) {
                wParseSkip();
                wCodeEmitOp( code, W_OP_PRINTTAB );
                if (wParseIsSeperator()) {
                    wCodeEmit( code, W_OP_EMITLN );
                }

            } else {
                wCodeEmitOp( code, W_OP_PRINTLN );
                break;
            }
        }
    }
    wParseSeperator();

    /* restore output to stdio? */
    if (redirected) {
        wCodeEmitOp( code, W_OP_STDIO );
    }

    return code;
}


/* REDO */
wCode *wParseStatementRedo()
{
    return wParseJump( wRedoStack, "Redo" );
}


/* RETURN statement */
wCode *wParseStatementReturn()
{
    int i, finallyCount;
    wCode *code;

    code = wCodeNew();

    wParseSkip();

    if (!wParseIsSeperator()) {
        /* SUBs can't return values */
        if (wSymbolLookup( wTheCurrentScope )->type == W_SYM_SUB) {
            wErrorThrow( W_ERROR_SYNTAX,  "Can't return values from a Sub" );
        }

        /* can have multiple items */
        while (1) {
            wCodeAppend( code, wParseExpression( 0 ) );
            if (!wParseTokenIs(',')) {
                break;
            }
            wParseSkip();
            wParseOptionalSeperator();
        }
    }

    wParseSeperator();

    /* process any Try clauses on the stack */
    wParseCleanupTryBlocks( code, W_TRUE );

    /* emit return */
    wCodeEmitOp( code, W_OP_RETURN );

    return code;
}

/* static statement */
wCode *wParseStatementStatic()
{
    int scope, here;
    wSymbol *sLocal, *sGlobal;
    wCode *code;

    /* only allow in routines */
    if (wTheCurrentScope == wTheGlobalScope) {
        wErrorThrow( W_ERROR_SYNTAX, "Static variables not allowed outside routines" );
    }

    wParseSkip();

    /* store current scope */
    scope = wTheCurrentScope;

    /* clear here (backpatch) */
    here = 0;

    /* initialize code */
    code = wCodeNew();

    /* read names of static vars */
    while (1) {
        /* create a global variable to hold the value */
        wTheCurrentScope = wTheGlobalScope;
        sGlobal = wSymbolNewLocal( "_static", 0 );
        wTheCurrentScope = scope;

        /* create an aliased variable to point to the global */
        sLocal = wSymbolNewLocal( wTheToken.text, sGlobal->index );

        /* FIXME: need to add AS clause */

        /* move ahead */
        wParseSkip();

        /* assignment? */
        if (wParseTokenIs(W_TOKEN_EQ)) {

            /* move past the "=" */
            wParseSkip();

            /* first assignment encountered? */
            if (here == 0) {
                /* jump past if not first time */
                wCodeEmitOp( code, W_OP_FIRSTTIME );
                wCodeEmitOp( code, W_OP_JMPF );

                /* emit zero instead of address */
                wCodeEmit( code, 0 );
                here = code->pcode->count;
            }

            /* the expression */
            wCodeAppend( code, wParseExpression( 0 ) );

            /* assign to the aliased variable */
            wCodeEmitVar( code, sLocal );
            wCodeEmitOp( code, W_OP_SET );
        }

        /* comma follows? */
        if (wParseTokenIs(',')) {
            /* parse it and optional seperator */
            wParseSkip();
            wParseOptionalSeperator();                
        } else {
            /* leave the loop */
            break;
        }
    }
    wParseSeperator();

    /* need to resolve jump address? */
    if (here != 0) {
        /* replace with relative address */
        wGrowSet( code->pcode, here, (code->pcode->count)-here+1);
    }

    return code;
}

/* SELECT statement */
wCode *wParseStatementSelect()
{
    int op, hasPriorCase;
    wSymbol *s;
    wCode *code;

    /* push state pointers */
    wGrowAppend( wCaseStack, --wTheNextLabel );
    wGrowAppend( wElseStack, --wTheNextLabel );
    wGrowAppend( wEndIfStack, --wTheNextLabel );

    /* no prior case */
    hasPriorCase = 0;

    /* parse SELECT CASE <expr> */
    wParseSkip();
    wParseExpect( W_TOKEN_CASE, "Case" );
    code = wParseExpression( 0 );
    wParseSeperator();

    /* set the test value */
    s = wSymbolNewLocal( "_select", 0 );    
    wCodeEmitVar( code, s );
    wCodeEmitOp( code, W_OP_SET );


    /* parse various cases */
    while (wParseTokenIs(W_TOKEN_CASE)) {
        wParseExpect( W_TOKEN_CASE, "Case" );

        /* jump out of the prior case */
        if (hasPriorCase) {
            wCodeEmitOp( code, W_OP_JMP );
            wCodeEmitForwardAddress( code, wEndIfStack, 0 );
        }        

        /* resolve else targets, leaving on stack */
        wCodeBackpatch( code, wGrowPeek( wElseStack, 0 ), wCodeHere(code) );

        /* emit a trace */
        wCodeEmitTrace( code );

        /* ELSE */
        if (wParseTokenIs(W_TOKEN_ELSE)) {
            wParseSkip();
            wParseSeperator();

            /* parse the block */
            wCodeAppend( code, wParseBlock() );
            break;

        } else {
            /* parse the clauses */
            while (1) {
                if (wParseTokenIs(W_TOKEN_IS)) {
                    wParseSkip();
                    wCodeEmitVar( code, s );
                    wCodeEmitOp( code, W_OP_GET );

                    /* what conditional? */
                    if (wParseTokenIs(W_TOKEN_EQ)) {
                        op = W_OP_EQ;

                    } else if (wParseTokenIs(W_TOKEN_NE)) {
                        op = W_OP_NE;

                    } else if (wParseTokenIs(W_TOKEN_GT)) {
                        op = W_OP_GT;

                    } else if (wParseTokenIs(W_TOKEN_LT)) {
                        op = W_OP_LT;

                    } else if (wParseTokenIs(W_TOKEN_GE)) {
                        op = W_OP_GE;

                    } else if (wParseTokenIs(W_TOKEN_LE)) {
                        op = W_OP_LE;

                    } else {
                        wErrorThrow( W_ERROR_SYNTAX,  "Expected \"<\", \"<=\", \">\", \">=\", \"=\" or \"<>\"" );
                    }
                    wParseSkip();
                    wCodeAppend( code, wParseExpression( 0 ) );
                    wCodeEmitOp( code, op );
                    wCodeEmitOp( code, W_OP_JMPT );
                    wCodeEmitForwardAddress( code, wCaseStack, 0 );

                } else {
                    wCodeAppend( code, wParseExpression( 0 ) );

                    if (wParseTokenIs(W_TOKEN_TO)) {
                        wParseSkip();
                        wCodeAppend( code, wParseExpression( 0 ) );

                        /* generate test */
                        wCodeEmitOp( code, W_OP_CASERANGE );
                        wCodeEmitVarIndex( code, s );
                        wCodeEmitForwardAddress( code, wCaseStack, 0 );

                    } else {
                        /* generate test */
                        wCodeEmitOp( code, W_OP_CASE );
                        wCodeEmitVarIndex(code, s );
                        wCodeEmitForwardAddress( code, wCaseStack, 0 );
                    }
                }

                /* more? */
                if (wParseTokenIs(',')) {
                    wParseSkip();
                    wParseOptionalSeperator();
                } else {
                    break;
                }
            }
            /* jump on failure */
            wParseSeperator();
            wCodeEmit(code, W_OP_JMP );
            wCodeEmitForwardAddress( code, wElseStack, 0 );

            /* resolve case targets, leaving on stack */
            wCodeBackpatch( code, wGrowPeek( wCaseStack, 0 ), wCodeHere(code) );
            wCodeAppend( code, wParseBlock() );

            /* flag so jump will be generated */
            hasPriorCase = W_TRUE;

        }
    }

    /* parse END SELECT */
    wParseExpect(W_TOKEN_END, "\"End\"" );
    wParseExpect(W_TOKEN_SELECT, "\"Select\"" );
    wParseSeperator();

    /* backpatch */
    wCodeBackpatch( code, wGrowPop( wCaseStack ), wCodeHere(code) );
    wCodeBackpatch( code, wGrowPop( wElseStack ), wCodeHere(code) );
    wCodeBackpatch( code, wGrowPop( wEndIfStack ), wCodeHere(code) );

    /* clear variable */
    wCodeEmitOp( code, W_OP_FREE );
    wCodeEmitVarIndex( code, s );

    return code;

}


/* THROW statement */
wCode *wParseStatementThrow()
{
    wCode *code;

    wParseSkip();
    code = wParseExpression( 0 );
    wCodeEmitOp( code, W_OP_THROW );

    return code;

}

/* TRY statement */
wCode *wParseStatementTry()
{
    int finallyTo, tryTo, catchTo, hasCatchAll, redoCatchTo, redoTo;
    wCode *code;

    finallyTo = 0;
    catchTo = 0;
    hasCatchAll = W_FALSE;

    code = wCodeNew();

    wParseSkip();

    /* push onto BlockType stack */
    wGrowAppend( wBlockTypeStack, W_TOKEN_TRY );

    /* setup labels */
    wGrowAppend( wFinallyStack, --wTheNextLabel );
    wGrowAppend( wTryStack, --wTheNextLabel );
    wGrowAppend( wCatchStack, --wTheNextLabel );
    wGrowAppend( wRedoStack, --wTheNextLabel );

    /* redo marker when inside catch */
    redoCatchTo = wCodeHere( code );
	
    /* set catch */
    wCodeEmitOp( code, W_OP_STARTCATCH );
    wCodeEmitForwardAddress( code, wCatchStack, 0 );

    /* redo marker when prior to catch */
    redoTo = wCodeHere( code );

    /* parse block */
    wCodeAppend( code, wParseBlock() );

    /* change BlockType to CATCH */
    wGrowPop( wBlockTypeStack );
    wGrowAppend( wBlockTypeStack, W_TOKEN_CATCH );


    /* start of catch? */
    if (wParseTokenIs(W_TOKEN_CATCH)
    ||  wParseTokenIs(W_TOKEN_ELSE)) {
        /* drop catch, jump to end */
        wCodeEmitOp( code, W_OP_ENDCATCH );
        wCodeEmitForwardAddress( code, wTryStack, 0 );
	    
	/* patch redo not to trigger catch again */
    wCodeBackpatch( code, wGrowPeek( wRedoStack, 0 ), redoTo );
    }

    /* catch? */
    while (wParseTokenIs(W_TOKEN_CATCH)
    ||  wParseTokenIs(W_TOKEN_ELSE)) {
        wParseSkip();
        wCodeEmitTrace( code );

        /* start of catch */
        catchTo = wCodeHere( code );
        wCodeBackpatch( code, wGrowPeek( wCatchStack, 0 ), catchTo );

        /* test? */
        if (!wParseIsSeperator()) {
            /* create test */
            wCodeAppend( code, wParseExpression( 0 ) );
            wCodeEmit( code, W_OP_JMPCATCHF );
            wCodeEmitForwardAddress( code, wCatchStack, 0 );
        } else {
            /* unconditional match */
            hasCatchAll = W_TRUE;
        }
        wParseSeperator();

        /* parse the catch block */
        wCodeAppend( code, wParseBlock() );

        /* jump to end of block */
        wCodeEmitOp( code, W_OP_JMP );
        wCodeEmitForwardAddress( code, wTryStack, 0 );
    }


    /* no final catch? */
    if (!hasCatchAll) {
        /* last try jumps to here... */
        catchTo = wCodeHere( code );

        /* run finally */
        wCodeEmitOp( code, W_OP_JSR );
        wCodeEmitForwardAddress( code, wFinallyStack, 0 );

        /* rethrow the exception */
        wCodeEmitOp( code, W_OP_RETHROW );
    }

    /* finally? */
    if (wParseTokenIs(W_TOKEN_FINALLY)) {
        /* block starts here */
        finallyTo = wCodeHere( code );
        wCodeEmitTrace( code );

        /* skip token */
        wParseSkip();
        wParseSeperator();

        /* need a catch clause */
        if (catchTo == 0) {
            wErrorThrow( W_ERROR_SYNTAX,  "Finally without a Catch" );
        }

        /* parse the finally block */
        wCodeAppend( code, wParseBlock() );

        /* return from finally */
        wCodeEmit( code, W_OP_RET );
    }

    /* end try */
    wParseExpect(W_TOKEN_END, "\"End\"" );
    wParseExpect(W_TOKEN_TRY, "\"Try\"" );
    wParseSeperator();


    /* no catch? */
    if (catchTo == 0 ) {
        wErrorThrow( W_ERROR_SYNTAX,  "End Try without a Catch" );
    }

    /* no finally? */
    if (finallyTo == 0) {
        /* create dummy finally in case of return in try clauses */
        finallyTo = wCodeHere( code );

        /* return from dummy finally */
        wCodeEmit( code, W_OP_RET );

        /* end of try, no need to jump to dummy finally */
        tryTo = wCodeHere( code );

    } else {
        /* end of try */
        tryTo = wCodeHere( code );

        /* finally exists, need to run */
        wCodeEmitOp( code, W_OP_JSR );
        wCodeEmitForwardAddress( code, wFinallyStack, 0 );

    }

    /* backpatch */
    wCodeBackpatch( code, wGrowPop( wFinallyStack ), finallyTo );
    wCodeBackpatch( code, wGrowPop( wTryStack ), tryTo );
    wCodeBackpatch( code, wGrowPop( wCatchStack ), catchTo );
    wCodeBackpatch( code, wGrowPop( wRedoStack ), redoCatchTo );

    /* pop of type stack */
    wGrowPop( wBlockTypeStack );


    return code;

}

/* while statement */
wCode *wParseStatementWhile()
{
    int continueTo, breakTo, elseTo, redoTo;
    wCode *code;

    /* labels */
    wGrowAppend( wElseStack, --wTheNextLabel );
    wGrowAppend( wContinueStack, --wTheNextLabel );
    wGrowAppend( wBreakStack, --wTheNextLabel );
    wGrowAppend( wRedoStack, --wTheNextLabel );

    /* loop type */
    wGrowAppend( wBlockTypeStack, W_TOKEN_WHILE );

    /* flag that it's not set */
    elseTo = -1;

    wParseSkip();

    code = wCodeNew();
    continueTo = wCodeHere( code );

    code = wParseExpression( 0 );
    wParseSeperator();

    /* conditional jump to else */
    wCodeEmitOp( code, W_OP_JMPF );
    wCodeEmitForwardAddress( code, wElseStack, 0 );

    /* redo */
    redoTo = wCodeHere( code );

    /* parse block */
    wCodeAppend( code, wParseBlock() );

    /* else statement? */
    if (wParseTokenIs(W_TOKEN_ELSE)) {
        wCodeEmitTrace( code );
        wParseSkip();
        wParseSeperator();

        /* jump to the top of the while loop */
        wCodeEmitOp( code, W_OP_JMP );
        wCodeEmitForwardAddress( code, wContinueStack, 0 );

        /* set the else label address */
        elseTo = wCodeHere( code );

        /* parse the else clause */
        wCodeAppend( code, wParseBlock() );
    }

    /* End While or Wend */
    if (wParseTokenIs(W_TOKEN_END)) {
        wParseSkip();
        wParseExpect(W_TOKEN_WHILE, "\"While\"" );
    } else {
        wParseExpect(W_TOKEN_WEND, "\"End While\" or \"Wend\"" );
    }
    wParseSeperator();

    /* no else clause? */
    if (elseTo == -1) {
        /* jump to the top of the while loop */
        wCodeEmitOp( code, W_OP_JMP );
        wCodeEmitForwardAddress( code, wContinueStack, 0 );

        /* else label jumps to break label */
        elseTo = wCodeHere( code );
    }

    /* break jumps to end of code */
    breakTo = wCodeHere( code );
    /* backpatch while */
    wCodeBackpatch( code, wGrowPop( wContinueStack ), continueTo );
    wCodeBackpatch( code, wGrowPop( wBreakStack ), breakTo );
    wCodeBackpatch( code, wGrowPop( wElseStack ), elseTo );
    wCodeBackpatch( code, wGrowPop( wRedoStack ), redoTo );

    /* pop loop type */
    wGrowPop( wBlockTypeStack );

    return code;
}


/* parse a single statement (or statement block) */
wCode *wParseStatement()
{
    int follows;
    wCode *code, *traceCode;

    /* this doesn't generate any trace */
    if (wParseIsSeperator()) {        
        /* empty line */
        wParseSeperator();
        return wCodeNew();
    }

    /* add optional trace? */
    if (wTheTraceOpFlag) {
        traceCode = wCodeNew();
        wCodeEmitTrace( traceCode );
    }

    /* what's the statement? */
    if (wParseTokenIs('~')) {
        code = wParseStatementDestroy();

    } else if (wParseTokenIs(W_TOKEN_ABSTRACT)) {
        /* ABSTRACT function is handled elsewhere */
        code = wParseStatementClass();
	    
    } else if (wParseTokenIs(W_TOKEN_BREAK)) {
        code = wParseStatementBreak();

    } else if (wParseTokenIs(W_TOKEN_BUILTIN_NAME)) {
        code = wParseStatementRoutineName(0);

    } else if (wParseTokenIs(W_TOKEN_CLASS)) {
        code = wParseStatementClass();

    } else if (wParseTokenIs(W_TOKEN_CLOSE)) {
        code = wParseStatementClose();

    } else if (wParseTokenIs(W_TOKEN_CONST)) {
        code = wParseStatementConst();

    } else if (wParseTokenIs(W_TOKEN_CONTINUE)) {
        code = wParseStatementContinue();

    } else if (wParseTokenIs(W_TOKEN_DIM)) {
        code = wParseStatementDim();

    } else if (wParseTokenIs(W_TOKEN_DOTMETHOD)) {
        code = wParseExpression( 0 );

        /* call or method? */
        if (code->last != W_OP_CALL
        &&  code->last != W_OP_CALLMETHOD
        &&  code->last != W_OP_CALLMYMETHOD) {
            /* this shouldn't happen! */
            wErrorThrow( W_ERROR_SYNTAX,  "Expected a routine or method, not an expression" );
        }
        wParseSeperator();

        /* change return count of the CALL so it returns nothing */
        wGrowPop( code->pcode );
        wGrowAppend( code->pcode, 0 );

    } else if (wParseTokenIs(W_TOKEN_DOTPROPERTY)) {
        code = wParseStatementAssign();

    } else if (wParseTokenIs(W_TOKEN_ENDX)) {
        code = wParseStatementEnd();

    } else if (wParseTokenIs(W_TOKEN_ERASE)) {
        code = wParseStatementErase();

    } else if (wParseTokenIs(W_TOKEN_EXIT)) {
        code = wParseStatementExit();

    } else if (wParseTokenIs(W_TOKEN_FOR)) {
        code = wParseStatementFor();

    } else if (wParseTokenIs(W_TOKEN_FUNCTION)) {
        code = wParseStatementDef();

    } else if (wParseTokenIs(W_TOKEN_FUNCTION_NAME)) {
        code = wParseStatementRoutineName(0);

    } else if (wParseTokenIs(W_TOKEN_IF)) {
        code = wParseStatementIf();

    } else if (wParseTokenIs(W_TOKEN_INPUT)) {
        code = wParseStatementInput();

    } else if (wParseTokenIs(W_TOKEN_LINE)) {
        code = wParseStatementLine();

    } else if (wParseTokenIs(W_TOKEN_OPEN)) {
        code = wParseStatementOpen();

    } else if (wParseTokenIs(W_TOKEN_OPTION)) {
        code = wParseStatementOption();

    } else if (wParseTokenIs(W_TOKEN_PRINT)
           ||  wParseTokenIs('?')) {
        code = wParseStatementPrint();

    } else if (wParseTokenIs(W_TOKEN_REDO)) {
        code = wParseStatementRedo();

    } else if (wParseTokenIs(W_TOKEN_RETURN)) {
        code = wParseStatementReturn();

    } else if (wParseTokenIs(W_TOKEN_SELECT)) {
        code = wParseStatementSelect();

    } else if (wParseTokenIs(W_TOKEN_SHARED)) {
        code = wParseStatementShared();

    } else if (wParseTokenIs(W_TOKEN_STATIC)) {
        code = wParseStatementStatic();

    } else if (wParseTokenIs(W_TOKEN_SUB)) {
        code = wParseStatementDef();

        /* zap the trace code */
        traceCode = wCodeNew();

    } else if (wParseTokenIs(W_TOKEN_SUB_NAME)) {
        code = wParseStatementRoutineName(0);

    } else if (wParseTokenIs(W_TOKEN_THROW)) {
        code = wParseStatementThrow();

    } else if (wParseTokenIs(W_TOKEN_TRY)) {
        code = wParseStatementTry();

    } else if (wParseTokenIs(W_TOKEN_WHILE)) {
        code = wParseStatementWhile();

    } else {
        /* assume it's an assignment */
        code = wParseStatementAssign();
    }

    /* add optional trace statement */
    if (wTheTraceOpFlag) {
        wCodeAppend( traceCode, code );
        code = traceCode;
    }

    return code;
}



/* join two code chunks with operand */
void wParseJoinOperands( wCode *lhs, wCode *rhs, int opToken )
{

    /* AND and OR have early outs */
    if (opToken == W_TOKEN_AND || opToken == W_TOKEN_OR) {
        /* next free label */
        wCodePushLabel( wMiscStack );

        /* early out */
        if (opToken == W_TOKEN_AND ) {
            /* jump past next expression if false */
            wCodeEmitOp( lhs, W_OP_JMPONF );
        } else {
            /* jump past next expression if true */
            wCodeEmitOp( lhs, W_OP_JMPONT );
        }

        wCodeEmitForwardAddress( lhs, wMiscStack, 0 );

        /* the next expression */
        wCodeAppend( lhs, rhs );

        /* backpatch */
        wCodeBackpatch( lhs, wGrowPop( wMiscStack ), wCodeHere( lhs ) );

        /* prevent from looking like a simple expression */
        lhs->last = W_OP_NOOP;

        return;
    }

    /* place value on stack */
    wCodeAppend( lhs, rhs );

    /* add opcode */
    switch (opToken) {

    case W_TOKEN_XOR:
        wCodeEmitOp( lhs, W_OP_XOR );
        break;

    case W_TOKEN_IN:
        wCodeEmitOp( lhs, W_OP_IN );
        break;

    case W_TOKEN_EQ:
        wCodeEmitOp( lhs, W_OP_EQ );
        break;

    case W_TOKEN_NE:
        wCodeEmitOp( lhs, W_OP_NE );
        break;

    case W_TOKEN_LT:
        wCodeEmitOp( lhs, W_OP_LT );
        break;

    case W_TOKEN_GT:
        wCodeEmitOp( lhs, W_OP_GT );
        break;

    case W_TOKEN_LE:
        wCodeEmitOp( lhs, W_OP_LE );
        break;

    case W_TOKEN_GE:
        wCodeEmitOp( lhs, W_OP_GE );
        break;

    case '+':
        wCodeEmitOp( lhs, W_OP_ADD );
        break;

    case '-':
        wCodeEmitOp( lhs, W_OP_SUB );
        break;

    case '&':
        wCodeEmitOp( lhs, W_OP_CONCAT );
        break;

    case '|':
        wCodeEmitOp( lhs, W_OP_OR_BITS );
        break;

    case W_TOKEN_INV:
        wCodeEmitOp( lhs, W_OP_INV );
        break;

    case '^':
        wCodeEmitOp( lhs, W_OP_POWER );
        break;

    case '*':
        wCodeEmitOp( lhs, W_OP_MUL );
        break;

    case '/':
        wCodeEmitOp( lhs, W_OP_DIV );
        break;

    case W_TOKEN_MOD:
    case '%':
        wCodeEmitOp( lhs, W_OP_MOD );
        break;

    case '\\':
        wCodeEmitOp( lhs, W_OP_IDIV );
        break;

    case W_TOKEN_SHL:
        wCodeEmitOp( lhs, W_OP_SHL );
        break;

    case W_TOKEN_SHR:
        wCodeEmitOp( lhs, W_OP_SHR );
        break;
    }
}

/* parse a single operand */
wCode *wParseOperand()
{
    int op, count, i;
    wCode *code;
    wSymbol *s;

    /* unary NOT */
    if (wParseTokenIs(W_TOKEN_NOT) || wParseTokenIs('!')) {
        wParseSkip();
        wParseOptionalSeperator();
        code = wParseOperand();
        wCodeEmit( code, W_OP_NOT );

    /* unary inv */
    } else if (wParseTokenIs(W_TOKEN_INV)) {
        wParseSkip();
        wParseOptionalSeperator();
        code = wParseOperand();
        wCodeEmit( code, W_OP_INV );

    /* open parens */
    } else if (wParseTokenIs('(')) {
        wParseSkip();
        wParseOptionalSeperator();

        code = wParseExpression( 0 );
        wParseExpect(')', "\")\"" );

    /* unary plus */
    } else if (wParseTokenIs('+')) {
        wParseSkip();
        wParseOptionalSeperator();

        /* parse it */
        code = wParseExpression( 0 );


    /* unary minus */
    } else if (wParseTokenIs('-')) {
        wParseSkip();
        wParseOptionalSeperator();

        /* negative number? */            
        if (wParseTokenIs(W_TOKEN_FLOAT)) {
            /* negate the value */
            wTheToken.fValue = -wTheToken.fValue;

            /* parse it */
            code = wParseExpression( 0 );

        } else if (wParseTokenIs(W_TOKEN_INTEGER)) {
            /* negate the value */
            wTheToken.iValue = -wTheToken.iValue;

            /* parse it */
            code = wParseExpression( 0 );

        } else {
            /* parse the expression and negate it */
            code = wParseExpression( 0 );
            wCodeEmitOp( code, W_OP_NEGATE );
        }

            
    /* table */
    } else if (wParseTokenIs('{')) {
        code = wParseTable();

    /* list */
    } else if (wParseTokenIs('[')) {
        code = wParseList();

    /* New className (...) */
    } else if (wParseTokenIs(W_TOKEN_NEW)) {
        wParseSkip();
        wParseOptionalSeperator();

        if (!wParseTokenIs(W_TOKEN_CLASS_NAME)) {
            wParseExpect(W_TOKEN_CLASS_NAME, "a class name" );
        }
        s = wTheToken.symbol;
        wParseSkip();

        /* error if abstract */
        if (s->flags & W_SYM_ISABSTRACT) {
            wErrorThrow( W_ERROR_SYNTAX,  "Can't create Abstract class %s\n", s->name );
        }

        code = wParseArgList();
        count = wGrowPop( wArgCountStack );

        /* create a new object */
        wCodeEmitOp( code, W_OP_NEW );
        wCodeEmitOp( code, s->index );
        wCodeEmit( code, count );

    /* className( ... ) */
    } else if (wParseTokenIs(W_TOKEN_CLASS_NAME)) {

        s = wTheToken.symbol;
        wParseSkip();
        wParseOptionalSeperator();

        /* error if abstract */
        if (s->flags & W_SYM_ISABSTRACT) {
            wErrorThrow( W_ERROR_SYNTAX,  "Can't create Abstract class %s\n", s->name );
        }

        code = wParseArgList();
        count = wGrowPop( wArgCountStack );

        /* create a new temporary object */
        wCodeEmitOp( code, W_OP_NEWTEMP );
        wCodeEmitOp( code, s->index );
        wCodeEmit( code, count );

    } else if (wParseTokenIs(W_TOKEN_UNDEFINED)) {
        /* create local if option explicit is not set */
        s = wParseCreateUndeclaredLocal( wTheToken.text );
        wParseSkip();

        code = wCodeNew();
        wCodeEmitVar( code, s );
        wCodeEmitOp( code, W_OP_GET );

    /* me */
    } else if (wParseTokenIs(W_TOKEN_ME)) {

        /* only allowable in class definitions */
        if (wTheClassScope == 0 ) {
            wErrorThrow( W_ERROR_SYNTAX,  "Can't reference Me outside of class definition");
        }

        /* make sure current method isn't shared */
        s = wSymbolLookup( wTheCurrentScope );
        if (s->flags & W_SYM_ISSHARED) {
            wErrorThrow( W_ERROR_SYNTAX, "Can't reference \"Me\" in Shared method \"%s\"", s->name );
        }

        code = wCodeNew();
        wCodeEmitOp( code, W_OP_ME );
        wCodeEmitOp( code, W_OP_GET );
        wParseSkip();

    /* variable or constant */
    } else if (wParseTokenIs(W_TOKEN_VARIABLE_NAME)
            || wParseTokenIs(W_TOKEN_CONSTANT_NAME)) {
        code = wCodeNew();
        wCodeEmitVar( code, wTheToken.symbol );
        wCodeEmitOp( code, W_OP_GET );
        wParseSkip();

    /* literal */
    } else if (wParseTokenIs(W_TOKEN_LITERAL)) {
        code = wCodeNew();
        wCodeEmitOp( code, W_OP_LITERAL );
        wCodeEmit( code, wTheToken.iValue );
        wParseSkip();

    /* integer */
    } else if (wParseTokenIs(W_TOKEN_INTEGER)) {
        code = wCodeNew();
        wCodeEmitOp( code, W_OP_INTEGER );
        wCodeEmit( code, wTheToken.iValue );
        wParseSkip();

    /* float */
    } else if (wParseTokenIs(W_TOKEN_FLOAT)) {
        code = wCodeNew();
        wCodeEmitNumber( code, wTheToken.fValue );
        wParseSkip();

    /* string */
    } else if (wParseTokenIs(W_TOKEN_STRING)) {
        code = wCodeNew();
        wCodeEmitString( code, wTheToken.text );
        wParseSkip();

    /* nothing */
    } else if (wParseTokenIs(W_TOKEN_NOTHING)) {
        code = wCodeNew();
        wCodeEmitOp( code, W_OP_NOTHING );
        wParseSkip();

    /* function */
    } else if (wParseTokenIs(W_TOKEN_FUNCTION_NAME)
           ||  wParseTokenIs(W_TOKEN_BUILTIN_NAME)) {
        code = wParseStatementRoutineName(1);

    /* method */
    } else if (wParseTokenIs(W_TOKEN_DOTMETHOD)) {
        /* pop dotmethod token off */
        wParseSkip();

        code = wParseDotMethod( W_FALSE );

    /* property */
    } else if (wParseTokenIs(W_TOKEN_DOTPROPERTY)) {
        code = wParseLval();
        wCodeEmitOp( code, W_OP_GET );

    } else {
        wErrorThrow( W_ERROR_SYNTAX,  "Expected an expression" );

    }

    /* indexed? */
    while (wParseTokenIs('[')) {
        /* parse index or slice */
         wCodeAppend( code, wParseIndexOrSlice() );
    }

    return code;

}


/* if token is binary op, return strength */
int wParseOpStrength()
{
    int theToken;

    /* returns order of binary op, if current token is a binary op */
    switch(wTheToken.type) {

	case '^':
	    return 20;
	    
	case '*':
	case '/':
	    return 19;

	case '\\':
	    return 18;
	    
	case W_TOKEN_MOD:
	case '%':
	    return 17;
		    
	case '+':
	case '-':
	    return 16;

	case W_TOKEN_SHL:
	case W_TOKEN_SHR:
	    return 15;
	    
	case '&':
	case '|':
	    /* just guessing for '|' */
	    return 14;

	case W_TOKEN_EQ:
	case W_TOKEN_NE:
	case W_TOKEN_GT:
	case W_TOKEN_LT:
	case W_TOKEN_LE:
	case W_TOKEN_GE:
	    return 13;

	case W_TOKEN_IN:
	// case W_TOKEN_IS:
	    return 12;
	
	case W_TOKEN_AND:
	    return 11;

	case W_TOKEN_OR:
	    return 10;

	case W_TOKEN_XOR:
	    return 9;

	// case W_TOKEN_EQV:
	//     return 8;
	
	// case W_TOKEN_IMP:
	//     return 7;
	
	case W_TOKEN_INV:
	    /* guessing on this one, too */
	    return 6;

	default:
	    return 0;

	}
}


/* parse expression until a binary op stronger than priorStrength is encountered */
wCode *wParseExpression( int priorStrength )
{

    wCode *lhs, *rhs;
    int op1, op2, op1Strength, op2Strength;

    /* get the first operand */
    lhs = wParseOperand();

    /* parse the chain of binary operators */
    while (1) {
        /* operator follows? */
        op1 = wTheToken.type;
        op1Strength = wParseOpStrength();
    
        /* weaker (or no operator?) */
        if (op1Strength <= priorStrength) {
            /* no operator, done */
            return lhs;
        }
    
        /* accept the operator */
        wParseSkip();
        wParseOptionalSeperator();

        /* get the next operand */
        rhs = wParseOperand();
    
        /* get next operator */
        op2 = wTheToken.type;
        op2Strength = wParseOpStrength();

        /* stronger? */
        if (op2Strength > op1Strength) {

            /* accept the operator */
            wParseSkip();
            wParseOptionalSeperator();

            /* join to the right hand side */
            wParseJoinOperands( rhs, wParseExpression( op2Strength ), op2 );
        }

        /* join the left hand side */
        wParseJoinOperands( lhs, rhs, op1 );
    
    }
}





/* return true if token is a seperator */
int wParseIsSeperator()
{
    return (wParseTokenIs('\n') ||
            wParseTokenIs(':')  ||
            wParseTokenIs(W_TOKEN_EOF));
}

/* parse a required seperator */
void wParseSeperator()
{
    if (!wParseIsSeperator()) {
        wErrorThrow( W_ERROR_SYNTAX, "Expected end of line, not \"%s\"", wTheToken.text );
    }

    if (!wParseTokenIs(W_TOKEN_EOF)) {
        wParseSkip();
    }

}



/* parse an optional seperator */
void wParseOptionalSeperator()
{
    if (wParseIsSeperator()) {
        if (!wParseTokenIs(W_TOKEN_EOF)) {
            wParseSkip();
        }        
    }
}


wCode *wParseOptionalArgList()
{
    // optional arg list?
    if (wParseTokenIs('(')) {
        return wParseArgList();
    } else {
        // don't bother calling it
        wGrowAppend( wArgCountStack, 0 );
        return wCodeNew();
    }
}


wCode *wParseArgList()
{
    wCode *code, *c1;

    // push arg count onto stack
    wGrowAppend( wArgCountStack, 0 );

    // no code yet
    code = wCodeNew();

    // ( ...
    if (!wParseTokenIs('(')) {
        wErrorThrow( W_ERROR_SYNTAX,  "Expected a '('" );
    }
    wParseSkip();

    // ()
    if (wParseTokenIs(')')) {
        wParseSkip();
        return code;
    }

    while (1) {
        c1 = wParseExpression( 0 );
        wGrowIncr( wArgCountStack, 1 );
        wCodeAppend( code, c1 );
        if (!wParseTokenIs(',')) {
            break;
        }
        wParseSkip();
        wParseOptionalSeperator();
    }

    wParseExpect(')', "a closing paren \")\"" );
    return code;

}

/* parse indexes, return count */
int wParseIndexes( wCode *code )
{
    int count;
    /* skip the opening paren */
    wParseSkip();

    /* parse until ending paren */
    count = 0;
    while (1) {
        /* read an expression */
        wCodeAppend( code, wParseExpression( 0 ) );
        count++;

        /* end? */
        if (wParseTokenIs(']')) {
            break;

        /* more? */
        } else if (wParseTokenIs(',')) {
            wParseSkip();
            wParseOptionalSeperator();

        } else {
            wErrorThrow( W_ERROR_SYNTAX,  "Expected \"]\" or \",\", not \"%s\"",
                wTheToken.text );
        }            
    }
    wParseSkip();
    return count;
}

/* parse a table */
wCode *wParseTable()
{
    int mapCount, listCount, startList, dumpList, total, exitFlag;
    wCode *code, *mapCode, *listCode, *tmpCode;

    /* This is a bit ugly, because a table can have a mixture of list   */
    /* style elements (values without keys) and map elements (values    */
    /* that have keys). In addition, the code prevents too many items   */
    /* being placed on the stack, to prevent stack overflows. wxBasic   */
    /* can resize the stack, but it's better not to accumulate a huge   */
    /* table list on the stack before putting it in the table.          */

    wParseSkip();
    wParseOptionalSeperator();

    /* initialize code */
    code = wCodeNew();

    /* empty list? */
    if (wParseTokenIs('}')) {
        wParseSkip();
        wCodeEmitOp( code, W_OP_CREATETABLE );
        return code;
    }


    /* set up for loop */
    mapCode = NULL;     /* holds accumulated map code */
    listCode = NULL;    /* holds accumulated list code */
    mapCount = 0;       /* count of mapped items */
    listCount = 0;      /* count of list items */
    startList = 1;      /* starting count for list */
    exitFlag = W_FALSE; /* if true, last element encountered */
    total = 0;          /* total number of items read */

    /* build the list */
    while (1) {

        /* parse the key */
        tmpCode = wParseExpression( 0 );
        total++;

        /* ':' denotes mapped element */
        if (wParseTokenIs(':')) {
            /* key:value pair */
            mapCount++;
            wParseSkip();
            wParseOptionalSeperator();
            if (mapCode == NULL) {
                mapCode = tmpCode;
            } else {
                wCodeAppend( mapCode, tmpCode );
            }
            wCodeAppend( mapCode, wParseExpression( 0 ) );

        } else {
            /* list:  key */
            if (listCode == NULL) {
                listCode = tmpCode;
            } else {
                wCodeAppend( listCode, tmpCode );
            }
            listCount++;
        }


        /* seperator? */
        if (wParseTokenIs(',')) {
            wParseSkip();
            wParseOptionalSeperator();
        } else {
            exitFlag = W_TRUE;
        }


        /* dump accumulated code? */
        if (tmpCode != NULL) {
            /* dump list? */
            if ((listCount && mapCount)
//            ||  (listCount && listCount % 35 == 0)
//            ||  (mapCount && mapCount % 35 == 0)
            ||  (exitFlag)) {

                /* last element or map has 35 elements in it */
                if ((exitFlag && mapCount != 0 )
                ||  (mapCount > 1)) {
                    /* write out keyed list */
                    wCodeAppend( code, mapCode );
                    wCodeEmitOp( code, W_OP_SETMAP );
                    wCodeEmit( code, mapCount );
                    mapCount = 0;
                }

                /* last element or list has 35 elements in it */
                if ((exitFlag && listCount != 0)
                ||  (listCount > 1)) {
                    /* write code for unkeyed list */
                    wCodeAppend( code, listCode );
                    wCodeEmitOp( code, W_OP_SETLIST );
                    wCodeEmit( code, startList );
                    wCodeEmit( code, listCount );
                    startList += listCount;
                    listCount = 0;
                }
            }
        }

        /* leave? */
        if (exitFlag) {
            break;
        }
    }

    wParseOptionalSeperator();
    wParseExpect('}',"a closing \"}\"" );

    // prepend CREATETABLE; some ugly swapping here...
    tmpCode = code;
    code = wCodeNew();
    wCodeEmitOp( code, W_OP_CREATETABLE );

    /* append list code */
    wCodeAppend( code, tmpCode );

    return code;

}

/* parse a list [ ... ] */
wCode *wParseList()
{
    int listCount, startList, total, exitFlag;
    wCode *code, *tmpCode;

    wParseSkip();
    wParseOptionalSeperator();

    /* holder for code */
    code = wCodeNew();

    /* empty list? */
    if (wParseTokenIs(']')) {
        wParseSkip();
        wCodeEmitOp( code, W_OP_CREATELIST );
        wCodeEmit( code, 0 );
        return code;
    }


    /* build the list */
    startList = 1;
    listCount = 0;
    exitFlag = W_FALSE;
    total = 0;

    /* read until end of list */
    while (1) {
        /* parse an element */
        wCodeAppend( code, wParseExpression( 0 ) );
        listCount++;
        total++;

        /* seperator? */
        if (wParseTokenIs(',')) {
            wParseSkip();
            wParseOptionalSeperator();
        } else {
            exitFlag = W_TRUE;
        }

        /* dump accumulated code? */
//        if ( (total % 35) == 0 || exitFlag ) {
        if ( exitFlag ) {

            /* write out keyed list */
            wCodeEmitOp( code, W_OP_SETLIST );
            wCodeEmit( code, startList );
            wCodeEmit( code, listCount );
            startList = total + 1;
            listCount = 0;

        }

        /* leave? */
        if (exitFlag) {
            break;
        }
    }

    wParseOptionalSeperator();
    wParseExpect(']',"a closing \"]\"" );


    /* prepend CREATELIST to the front of the code */
    tmpCode = code;
    code = wCodeNew();
    wCodeEmitOp( code, W_OP_CREATELIST );
    wCodeEmit( code, total );

    /* append list code */
    wCodeAppend( code, tmpCode );
    return code;

}

/* parse an index or a slice */
wCode *wParseIndexOrSlice()
{
    int count;
    wCode *code;

    /* set up holder for code */
    code = wCodeNew();

    /* skip the opening paren */
    wParseSkip();

    /* slice without start parameter? */
    if (wParseTokenIs(':')) {
        /* use default value of 1 */
        wCodeEmitOp( code, W_OP_INTEGER );
        wCodeEmit( code, 1 );

        /* set count */
        count = 1;

    /* parse index(es) */
    } else {
        count = 0;
        while (1) {
            /* read an expression */
            wCodeAppend( code, wParseExpression( 0 ) );
            count++;

            /* continue? */
            if (!wParseTokenIs(',')) {
                break;
            } else {
                wParseSkip();
                wParseOptionalSeperator();
            }
        }
    }

    /* slice? */
    if (count == 1 && wParseTokenIs(':')) {
        /* skip ':' */
        wParseSkip();

        /* no end value? */
        if (wParseTokenIs(']')) {
            /* use default value of -1 */
            wCodeEmitOp( code, W_OP_INTEGER );
            wCodeEmit( code, -1 );

        /* get parameter */
        } else {
            wCodeAppend( code, wParseExpression( 0 ) );
        }

        /* emit the opcode */
        wCodeEmitOp( code, W_OP_GETSLICE );

    /* index */
    } else {
        wCodeEmitOp( code, W_OP_INDEX );
        wCodeEmit( code, count );
        wCodeEmitOp( code, W_OP_GET );
    }

    /* closing paren */
    wParseExpect(']', "a closing \"]\"" );

    return code;

}


/* parse AS portion of DIM */
int wParseAsClause( int symbolStartIndex, int symbolEndIndex )
{
    int i;
    wSymbol *s;

    /* if there is an AS clause, the typeCast field gets set    */
    /* to the requested type. This is used to generate SETTYPE  */
    /* opcodes at the head of the codeblock.                    */

    /* typecast? */
    if (wParseTokenIs(W_TOKEN_AS)) {
        wParseSkip();

        if (!wParseTokenIs(W_TOKEN_CLASS_NAME)) {
            wErrorThrow( W_ERROR_SYNTAX,  "Expected a datatype or class name, not \"%s\"",
                wTheToken.text );
        }

        /* set typecast for symbols in range */
        for ( i = symbolStartIndex; i <= symbolEndIndex; i++ ) {
            /* find the symbol */
            s = wSymbolLookup( i );

            /* store the class */
            s->typeCast = wTheToken.symbol->index;
        }

        wParseSkip();

        /* return true */
        return 1;
    }

    /* return false */
    return 0;
}
    

/* parse a variable name, returning the symbol */
wSymbol *wParseVariableName()
{
    /* existing variable? */
    if (wParseTokenIs(W_TOKEN_VARIABLE_NAME)) {
        return wTheToken.symbol;

    /* undeclared? */
    } else if (wParseTokenIs(W_TOKEN_UNDEFINED)) {
        /* try to create it */
        return wParseCreateUndeclaredLocal( wTheToken.text );
    }

    /* error */
    wParseExpect( W_TOKEN_VARIABLE_NAME, "a variable name" );

    /* keep the compiler happy */
    return NULL;

}

