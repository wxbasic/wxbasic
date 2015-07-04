/* join two code chunks with operand */
void wParseJoinOperands( wCode *lhs, wCode *rhs, int opToken )
{
    switch(opToken) {

    /* AND and OR have early outs */
    case W_TOKEN_AND:
    case W_TOKEN_OR:
        /* next free label */
        wCodePushLabel( wMiscStack );

        /* early out */
        if (operand == W_TOKEN_AND ) {
            /* jump past next expression if false */
            wCodeEmitOp( lhs, W_OP_JMPONF );
        } else {
            /* jump past next expression if true */
            wCodeEmitOp( lhs, W_OP_JMPONT );
        }

        wCodeEmitForwardAddress( lhs, wMiscStack );

        /* the next expression */
        wCodeAppend( lhs, rhs );

        /* backpatch */
        wCodeBackpatch( lhs, wGrowPop( wMiscStack ), wCodeHere( lhs ) );

        /* prevent from looking like a simple expression */
        lhs->last = W_OP_NOOP;

        return lhs;
        break;

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

    wCodeAppend( lhs, rhs );
}

// parse an operand
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

        code = wParseExpression(1);
        wParseExpect(')', "\")\"" );

    /* unary plus */
    } else if (wParseTokenIs('+')) {
        wParseSkip();
        wParseOptionalSeperator();

        /* parse it */
        code = wParseExpression(1);


    /* unary minus */
    } else if (wParseTokenIs('-')) {
        wParseSkip();
        wParseOptionalSeperator();

        /* negative number? */            
        if (wParseTokenIs(W_TOKEN_FLOAT)) {
            /* negate the value */
            wTheToken.fValue = -wTheToken.fValue;

            /* parse it */
            code = wParseExpression(1);

        } else if (wParseTokenIs(W_TOKEN_INTEGER)) {
            /* negate the value */
            wTheToken.iValue = -wTheToken.iValue;

            /* parse it */
            code = wParseExpression(1);

        } else {
            /* parse the expression and negate it */
            code = wParseExpression(1);
            wCodeEmitOp( code, W_OP_NEGATE );
        }

            
    /* table */
    } else if (wParseTokenIs('{')) {
        code = wParseTable();

    /* list */
    } else if (wParseTokenIs('[')) {
        code = wParseList();

    /* New className (...)
    if (wParseTokenIs(W_TOKEN_NEW)) {
        wParseSkip();
        wParseOptionalSeperator();

        if (!wParseTokenIs(W_TOKEN_CLASS_NAME)) {
            wParseExpect(W_TOKEN_CLASS_NAME, "a class name" );
        }
        s = wTheToken.symbol;
        wParseSkip();

        /* error if abstract */
        if (s->flags & W_SYM_ISABSTRACT) {
            wParseError( "Can't create Abstract class %s\n", s->name );
        }

        code = wParseArgList();
        count = wGrowPop( wArgCountStack );

        /* create a new object */
        wCodeEmitOp( code, W_OP_NEW );
        wCodeEmitOp( code, s->index );
        wCodeEmit( code, count );

        break;

    /* className( ... ) */
    } else if (wParseTokenIs(W_TOKEN_CLASS_NAME)) {
        s = wTheToken.symbol;
        wParseSkip();
        wParseOptionalSeperator();

        /* error if abstract */
        if (s->flags & W_SYM_ISABSTRACT) {
            wParseError( "Can't create Abstract class %s\n", s->name );
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
            wParseError( "Can't reference Me outside of class definition");
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
        code = wParseDotMethod();

    /* property */
    } else if (wParseTokenIs(W_TOKEN_DOTPROPERTY)) {
        code = wParseLval();
        wCodeEmitOp( code, W_OP_GET );


    } else {
        wParseError( "Expected an expression" );

    }

    // indexed?
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

    /* check to see if the token is a binary operator */
    switch(wTheToken.type) {
        case W_TOKEN_XOR:
        case W_TOKEN_IN:
        case W_TOKEN_OR:
        case W_TOKEN_AND:
        case W_TOKEN_EQ:
        case W_TOKEN_NE:
        case W_TOKEN_LT:
        case W_TOKEN_GT:
        case W_TOKEN_LE:
        case W_TOKEN_GE:
        case '+':
        case '-':
        case '&':
        case '|':
        case W_TOKEN_INV:
        case '^':
        case '*':
        case '/':
        case W_TOKEN_MOD:
        case '\\':
        case '%':
        case W_TOKEN_SHL:
        case W_TOKEN_SHR:
            return 1;
            break;
    }

    return 0;
}


/* parse expression until a binary op stronger than priorStrength is encountered */
wCode *parseExpression( int priorStrength )

    wCode *lhs, *rhs;
    int op1, op2, nextStrength;

    /* get the first operand */
    lhs = wParseOperand();

    /* parse the chain of binary operators */
    while (1) {
    
        /* operator follows? */
        op1 = wTheToken.type;
        op1Strenth = wParseOpStrength()
    
        /* weaker (or no operator?) */
        if (op1Strength < priorStrength) {
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
        op2Strenth = wParseOpStrength()
    
        /* stronger? */
        if (op2Strength > op1Strength) {
            /* join to the right hand side */
            wParseJoinOperands( rhs, parseExpression( op2Strength ), op2 );
        }
    
        /* join the left hand side */
        wParseJoinOperands( lhs, rhs, op1 );
    
    }
}

