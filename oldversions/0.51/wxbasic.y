%{

/* return a sequence of items to execute */
wNode *wComma( wNode *node1, wNode *node2 )
{
    return wOpNode( W_OP_COMMA, node1, node2 );
}

/* returns name of block */
char *wBlockName( int klass )
{
    switch(klass) {
    case -1:                return wCopyString( "end-of-file" );
    case W_TOKEN_FOR:       return wCopyString( "End For/Next" );
    case W_TOKEN_FUNCTION:  return wCopyString( "End Function" );
    case W_TOKEN_IF:        return wCopyString( "End If" );
    case W_TOKEN_WHILE:     return wCopyString( "End While" );
    case W_TOKEN_SELECT:    return wCopyString( "End Select" );
    case W_TOKEN_SUB:       return wCopyString( "End Sub" );
    default:                return wCopyString("block");
    }
}

/* make sure the block ends correctly */
void wCheckBlockEnd(int got)
{
    int     wanted;
    char    *wantedName, *gotName;

    if (wIsEmptyStack(wBlockStack)) {
        switch (got) {
        case W_TOKEN_FOR:       wFatal( W_SYNTAX, "End For without For");
        case W_TOKEN_FUNCTION:  wFatal( W_SYNTAX, "End Function without Function");
        case W_TOKEN_IF:        wFatal( W_SYNTAX, "End If without If");
        case W_TOKEN_WHILE:     wFatal( W_SYNTAX, "End While without While");
        case W_TOKEN_SELECT:    wFatal( W_SYNTAX, "End Select without Select");
        case W_TOKEN_SUB:       wFatal( W_SYNTAX, "End Sub without Sub");
        }
    }

    wanted = wPeekStack(wBlockStack);
    if (got != wanted){
        wFatal( W_SYNTAX, "Expected %s, not %s", wBlockName(wanted), wBlockName(got));
    }
}

%}

/* %no_lines */
%union {
    int     iValue;         /* integer value */
    wNumber  fValue;        /* float value */
    char    *strValue;      /* string pointer */
    wNode    *node;         /* parse node */
    wSymbol  *symbol;       /* symbol */
}

%token <iValue>     W_TOKEN_INTEGER
%token <fValue>     W_TOKEN_FLOAT
%token <strValue>   W_TOKEN_STRING
%token <symbol>     W_TOKEN_FUNCTION_NAME
%token <symbol>     W_TOKEN_SUB_NAME
%token <symbol>     W_TOKEN_FORWARD_SUB_NAME
%token <symbol>     W_TOKEN_FORWARD_FUNCTION_NAME
%token <symbol>     W_TOKEN_BUILTIN_NAME
%token <symbol>     W_TOKEN_CONSTANT_NAME
%token <symbol>     W_TOKEN_VARIABLE_NAME
%token <symbol>     W_TOKEN_ARRAY_NAME
%token <symbol>     W_TOKEN_CLASS_NAME
%token <strValue>   W_TOKEN_METHOD_NAME
%token <strValue>   W_TOKEN_UNDEFINED

%type <node> block
%type <node> command
%type <node> statement
%type <node> elseIf
%type <node> expr
%type <node> argList
%type <node> argItems
%type <node> printList
%type <node> subList
%type <node> indexList
%type <node> cases
%type <node> caseTests
%type <node> caseTail
%type <node> loopTail
%type <node> dimList
%type <node> dimItem
%type <node> dimIndexList
%type <node> dimIndexItems
%type <node> indexListTail
%type <node> lval
%type <iValue> fileMode
%type <node> constList
%type <node> constItem
%type <node> fileHandle

%token W_TOKEN_AND
%token W_TOKEN_APPEND
%token W_TOKEN_AS
%token W_TOKEN_CASE
%token W_TOKEN_CLOSE
%token W_TOKEN_COMMON
%token W_TOKEN_CONST
%token W_TOKEN_CONTINUE
%token W_TOKEN_DECLARE
%token W_TOKEN_DELETE
%token W_TOKEN_DIM
%token W_TOKEN_DO
%token W_TOKEN_EACH
%token W_TOKEN_ELSE
%token W_TOKEN_ELSEIF
%token W_TOKEN_END
%token W_TOKEN_ENDX
%token W_TOKEN_ERASE
%token W_TOKEN_EXIT
%token W_TOKEN_EXPLICIT
%token W_TOKEN_FOR
%token W_TOKEN_FUNCTION
%token W_TOKEN_IF
%token W_TOKEN_IN
%token W_TOKEN_INCLUDE_FILE
%token W_TOKEN_INPUT
%token W_TOKEN_INV
%token W_TOKEN_IS
%token W_TOKEN_LINE
%token W_TOKEN_MOD
%token W_TOKEN_NEW
%token W_TOKEN_NEXT
%token W_TOKEN_NOCONSOLE
%token W_TOKEN_NOT
%token W_TOKEN_OR
%token W_TOKEN_OPEN
%token W_TOKEN_OPTION
%token W_TOKEN_OUTPUT
%token W_TOKEN_PRINT
%token W_TOKEN_QBASIC
%token W_TOKEN_REDIM
%token W_TOKEN_RETURN
%token W_TOKEN_SELECT
%token W_TOKEN_SHARED
%token W_TOKEN_SHL
%token W_TOKEN_SHR
%token W_TOKEN_STATIC
%token W_TOKEN_STEP
%token W_TOKEN_SUB
%token W_TOKEN_THEN
%token W_TOKEN_TO
%token W_TOKEN_UNTIL
%token W_TOKEN_WEND
%token W_TOKEN_WHILE
%token W_TOKEN_XOR

/* two character tokens */
%token W_TOKEN_GE
%token W_TOKEN_LE
%token W_TOKEN_NE
%token <iValue> W_TOKEN_INCR_SELF        /* +=, -=, *=, /=, &= */

%nonassoc UMinus

/* precedence, weakest to strongest */
%left W_TOKEN_AND W_TOKEN_OR W_TOKEN_XOR
%left W_TOKEN_IN
%left W_TOKEN_EQ W_TOKEN_NE W_TOKEN_LT W_TOKEN_GT W_TOKEN_LE W_TOKEN_GE
%left '+' '-' '!' W_TOKEN_NOT '&' '|' W_TOKEN_MOD W_TOKEN_INV
%left '*' '/' '\\' '%' W_TOKEN_SHL W_TOKEN_SHR
%left '^'

%%

program:

      program statement
        {
            /* should be empty at this point */
            if (!wIsEmptyStack(wBlockStack)) {
                    wCheckBlockEnd(-1);
            }

            /* print error? */
            if (wErrFlag) {
                wFatal( W_SYNTAX, "syntax error");
            }

            /* code? */
            if ($2 != NULL) {
                /* defer or execute */
                if (wQBasicFlag) {
                    if (wDeferredCode == NULL) {
                        wDeferredCode = $2;
                    } else {
                        wDeferredCode = wComma( wDeferredCode, $2 );
                    }
                } else {
                    wEval( $2 );
                    wFreeNode( $2 );
                }
            } }

    | /* nothing */
        {   wEval( wDeferredCode );
            wFreeNode( wDeferredCode ); }
    ;

block:

      W_TOKEN_END W_TOKEN_IF
        {   wCheckBlockEnd(W_TOKEN_IF);
            $$ = NULL; }

    | W_TOKEN_END W_TOKEN_FOR
        {   wCheckBlockEnd(W_TOKEN_FOR);
            $$ = NULL; }

    | W_TOKEN_END W_TOKEN_FUNCTION
        {   wClearStack( wSharedStack );
            wCheckBlockEnd(W_TOKEN_FUNCTION);
            $$ = NULL; }

    | W_TOKEN_END W_TOKEN_SUB
        {   wClearStack( wSharedStack );
            wCheckBlockEnd(W_TOKEN_SUB);
            $$ = NULL; }

    | W_TOKEN_END W_TOKEN_WHILE
        {   wCheckBlockEnd(W_TOKEN_WHILE);
            $$ = NULL; }

    | W_TOKEN_END W_TOKEN_SELECT
        {   wCheckBlockEnd(W_TOKEN_SELECT);
            $$ = NULL; }

    | W_TOKEN_NEXT
        {   wCheckBlockEnd(W_TOKEN_FOR);
            $$ = NULL; }

    | W_TOKEN_WEND
        {   wCheckBlockEnd(W_TOKEN_WHILE);
            $$ = NULL; }

    | statement block
            {   if (wErrFlag) {
                    wFatal( W_SYNTAX, "Syntax error");
                }
                if ($1 == NULL) {
                    $$ = $2;
                } else {
                    $$ = wComma( $1, $2 );
                } }

    | /* nothing */
        { $$ = NULL; }
    ;


statement:
    command
        {   if ($$ != NULL) {
                $1->trace = wParseLineId;
            }
            $$ = $1; }
    ;

command:

      '~' expr '(' ')' sep
        {   $$ = wOpNode( W_OP_DESTROY, $2, NULL ); }

    | '~' expr error
        {   wExpected("("); }

    | '~' expr '(' error
        {   wExpected(")"); }

    | expr sep
        {   /* convert to call (drop result) */
            switch ($1->op) {
            case W_OP_METHOD:
                $1->op = W_OP_METHOD_CALL;
                break;
            case W_OP_CLASS_METHOD:
                $1->op = W_OP_CLASS_METHOD_CALL;
                break;
            default:
                wFatal( W_SYNTAX, "result of expression not assigned");
                break;
            }
            $$ = $1; }

    | W_TOKEN_CONSTANT_NAME W_TOKEN_EQ
        {   wFatal( W_SYNTAX, "duplicate definition of %s", $1->name); }

    | W_TOKEN_FUNCTION_NAME W_TOKEN_EQ expr
        {   if ($1 != wCurrentScope || !wInStack(wBlockStack,W_TOKEN_FUNCTION)) {
                wFatal( W_SYNTAX, "Assignment outside Function");
            }
            $$ = wOpNode( W_OP_RETURN_SET_VALUE, $3, NULL ); }


    | W_TOKEN_FUNCTION_NAME '('
        {   wPushStack( wArgCountStack, 0 ); }

          argList sep
        {   int args = wPopStack( wArgCountStack );
            wCheckArgCount( $1, args );
            $$ = wSymbolNode( W_OP_FUNCTION_CALL, $1, $4, NULL ); }

    | W_TOKEN_SUB_NAME '('
        {   wPushStack( wArgCountStack, 0 ); }

          argList sep
        {   int args = wPopStack( wArgCountStack );
            wCheckArgCount( $1, args );
            $$ = wSymbolNode( W_OP_FUNCTION_CALL, $1, $4, NULL ); }

    | W_TOKEN_FORWARD_FUNCTION_NAME '('
        {
            wPushStack( wArgCountStack, 0 ); }

          argList sep
        {   wCheckArgCount( $1, wPopStack( wArgCountStack ) );
            $$ = wSymbolNode( W_OP_FUNCTION_CALL, $1, $4, NULL ); }

    | W_TOKEN_FORWARD_SUB_NAME '('
        {
            wPushStack( wArgCountStack, 0 ); }

          argList sep
        {   wCheckArgCount( $1, wPopStack( wArgCountStack ) );
            $$ = wSymbolNode( W_OP_FUNCTION_CALL, $1, $4, NULL ); }


    | W_TOKEN_FUNCTION_NAME sep
        { if ($1->args != 0) {
              wExpected("'('");
        }
        $$ = wSymbolNode( W_OP_FUNCTION_CALL, $1, NULL, NULL ); }

    | W_TOKEN_SUB_NAME sep
        { if ($1->args != 0) {
              wExpected("'('");
        }
        $$ = wSymbolNode( W_OP_FUNCTION_CALL, $1, NULL, NULL ); }


    | W_TOKEN_FORWARD_FUNCTION_NAME sep
        { if ($1->args != 0) {
              wExpected("'('");
        }
        $$ = wSymbolNode( W_OP_FUNCTION_CALL, $1, NULL, NULL ); }

    | W_TOKEN_FORWARD_SUB_NAME sep
        { if ($1->args != 0) {
              wExpected("'('");
        }
        $$ = wSymbolNode( W_OP_FUNCTION_CALL, $1, NULL, NULL ); }


    | W_TOKEN_BUILTIN_NAME '('
        { wPushStack( wArgCountStack, 0 ); }

          argList sep
        { int args = wPopStack( wArgCountStack );
          wCheckArgCount( $1, args );
          $$ = wSymbolNode( W_OP_BUILTIN_CALL, $1, $4, NULL ); }

    | W_TOKEN_BUILTIN_NAME sep
        { if ($1->args != 0) {
              wExpected("'('");
          }
          $$ = wSymbolNode( W_OP_BUILTIN_CALL, $1, NULL, NULL ); }

    | W_TOKEN_CLOSE fileHandle sep
        {   $$ = wOpNode( W_OP_CLOSE, $2, NULL ); }

    | W_TOKEN_CLOSE sep
        {   $$ = wOpNode( W_OP_CLOSE, NULL, NULL ); }

    | W_TOKEN_CONST constList sep
        { $$ = $2 }

    | W_TOKEN_COMMON
        {   if (wCurrentScope != NULL) {
                wFatal( W_SYNTAX, "Can't use Common in Sub or Function" );
            }
            wCommonFlag = 1; }

        dimList sep
        {   $$ = $3;
            wCommonFlag = 0; }

    | W_TOKEN_CONTINUE sep
        {   if (!wInStack(wBlockStack,W_TOKEN_FOR) && !wInStack(wBlockStack,W_TOKEN_WHILE)) {
                wFatal( W_SYNTAX, "Continue outside For or While");
            }
            $$ = wOpNode( W_OP_CONTINUE, NULL, NULL ); }

    | W_TOKEN_DELETE expr sep
        { $$ = wOpNode( W_OP_DELETE, $2, NULL ) }

    /* same as Dim Common */
    | W_TOKEN_DIM W_TOKEN_COMMON
        {   if (wCurrentScope != NULL) {
                wFatal( W_SYNTAX, "Can't use Common in Sub or Function" );
            }
            wCommonFlag = 1; }

        dimList sep
        {   $$ = $4;
            wCommonFlag = 0; }

    /* same as Shared */
    | W_TOKEN_DIM W_TOKEN_SHARED
        {   if (wCurrentScope == NULL) {
                wFatal( W_SYNTAX, "Shared illegal outside Sub or Function");
            }
            wPushStack(wBlockStack, (int)wCurrentScope );
            wCurrentScope = NULL; }
        sharedList sep
        {   wCurrentScope = (wSymbol *)wPopStack(wBlockStack);
            $$ = NULL; }

    | W_TOKEN_DIM dimList sep
        {   $$ = $2; }

    | W_TOKEN_ENDX sep
        { $$ = wOpNode( W_OP_END, NULL, NULL ); }

    | W_TOKEN_ERASE W_TOKEN_ARRAY_NAME optBrackets sep
        {   $$ = wSymbolNode( W_OP_ERASE, $2, NULL, NULL ); }

    | W_TOKEN_ERASE W_TOKEN_ARRAY_NAME '[' indexList sep
        {   wCheckArgCount( $2, wPopStack( wArgCountStack ) );
            $$ = wSymbolNode( W_OP_ERASE, $2, $4, NULL ); }

    | W_TOKEN_EXIT W_TOKEN_DO
        {   if (!wInStack(wBlockStack,W_TOKEN_WHILE)) {
                wFatal( W_SYNTAX, "Exit outside While loop");
            }
            $$ = wOpNode( W_OP_EXIT_WHILE, NULL, NULL ); }

    | W_TOKEN_EXIT W_TOKEN_FOR
        {   if (!wInStack(wBlockStack,W_TOKEN_FOR)) {
                wFatal( W_SYNTAX, "Exit outside For loop");
            }
            $$ = wOpNode( W_OP_EXIT_FOR, NULL, NULL ); }

    | W_TOKEN_EXIT W_TOKEN_FUNCTION
        {   if (!wInStack(wBlockStack,W_TOKEN_FUNCTION)) {
                wFatal( W_SYNTAX, "Exit Function outside Function");
            }
            $$ = wOpNode( W_OP_EXIT_ROUTINE, NULL, NULL ); }

    | W_TOKEN_EXIT W_TOKEN_SUB
        {   if (!wInStack(wBlockStack,W_TOKEN_SUB)) {
                wFatal( W_SYNTAX, "Exit Sub outside Sub");
            }
            $$ = wOpNode( W_OP_EXIT_ROUTINE, NULL, NULL ); }

    | W_TOKEN_EXIT W_TOKEN_WHILE
        {   if (!wInStack(wBlockStack,W_TOKEN_WHILE)) {
                wFatal( W_SYNTAX, "Exit outside While loop");
            }
            $$ = wOpNode( W_OP_EXIT_WHILE, NULL, NULL ); }

    | W_TOKEN_EXIT error
        {   wExpected("Do, For, Sub, Function or While"); }


    /* If <expr> Then ... ElseIf <expr> ... Else ... End If */
    | W_TOKEN_IF
        {   wPushStack(wBlockStack,W_TOKEN_IF); }

      expr W_TOKEN_THEN sep block elseIf sep
        {   wPopStack(wBlockStack);
            $$ = wOpNode( W_OP_IF, wOpNode( W_OP_IF_TRUE, $3, $6 ), $7 ); }

    /* For Each <var> In <expr> */
    | W_TOKEN_FOR W_TOKEN_EACH W_TOKEN_VARIABLE_NAME W_TOKEN_IN W_TOKEN_ARRAY_NAME optBrackets
        {   wPushStack(wBlockStack,W_TOKEN_FOR); }

        sep block
        {   wPopStack(wBlockStack);
            $$ = wSymbolNode( W_OP_FOR_EACH, $3,
                wSymbolNode( W_OP_NOOP, $5, NULL, NULL ), $9 ); }

    | W_TOKEN_FOR W_TOKEN_EACH W_TOKEN_VARIABLE_NAME W_TOKEN_IN error
        {   wExpected("an Array") };
                               

    | W_TOKEN_FOR W_TOKEN_EACH W_TOKEN_UNDEFINED W_TOKEN_IN W_TOKEN_ARRAY_NAME
        {   wPushStack(wBlockStack,W_TOKEN_FOR); }

        sep block
        {   wPopStack(wBlockStack);
            $$ = wSymbolNode( W_OP_FOR_EACH, wReturnVar($3, W_SYM_VARIABLE, 0),
                wSymbolNode( W_OP_NOOP, $5, NULL, NULL ), $8 ); }

    | W_TOKEN_FOR W_TOKEN_EACH W_TOKEN_UNDEFINED W_TOKEN_IN error
        {   wExpected("an Array") };

    | W_TOKEN_FOR W_TOKEN_EACH W_TOKEN_VARIABLE_NAME error
        {   wExpected("In") };

    | W_TOKEN_FOR W_TOKEN_EACH W_TOKEN_UNDEFINED error
        {   wExpected("In") };

    | W_TOKEN_FOR W_TOKEN_EACH error
        {   wExpected("a variable") };

    /* For <var> = <expr> To <expr> [step <expr>] ... next */
    | W_TOKEN_FOR W_TOKEN_VARIABLE_NAME 
        {   wPushStack(wBlockStack,W_TOKEN_FOR); }

      loopTail sep
        {   wPopStack(wBlockStack);
            $4->value.symbol = $2;
            $$ = $4; }

    | W_TOKEN_FOR W_TOKEN_UNDEFINED
        {   wPushStack(wBlockStack,W_TOKEN_FOR);
            wReturnVar($2, W_SYM_VARIABLE, 0); }

        loopTail sep
        {   wPopStack(wBlockStack);
            $4->value.symbol = wFindSymbol($2, wCurrentScope);
            wFree( $2 );
            $$ = $4; }

    | W_TOKEN_FOR error
        {   wExpected("Each or a variable") };


    | W_TOKEN_DECLARE W_TOKEN_FUNCTION W_TOKEN_UNDEFINED
        {   if (wCurrentScope != NULL) {
                wFatal( W_SYNTAX, "Can't define function %s in %s", $3, wCurrentScope->name );
            }
            wCurrentScope = wAddSymbol( $3, NULL, W_SYM_FUNCTION, W_TRUE );
        }

      parmlist sep
        {   wCurrentScope->code = NULL;
            wCurrentScope->forward = 1;
            $$ = NULL;
            wFree( $3 );
            wCurrentScope = NULL; }

    | W_TOKEN_DECLARE W_TOKEN_SUB W_TOKEN_UNDEFINED
        {   if (wCurrentScope != NULL) {
                wFatal( W_SYNTAX, "Can't define Sub %s in %s", $3, wCurrentScope->name );
            }
            wCurrentScope = wAddSymbol( $3, NULL, W_SYM_SUB, W_TRUE );
        }

      parmlist sep
        {   wCurrentScope->code = NULL;
            wCurrentScope->forward = 1;
            $$ = NULL;
            wFree( $3 );
            wCurrentScope = NULL; }

    | W_TOKEN_DECLARE error
        {   wExpected("Sub or Function"); }


    | W_TOKEN_FUNCTION W_TOKEN_UNDEFINED
        {   if (wCurrentScope != NULL) {
                wFatal( W_SYNTAX, "Can't define Function %s in %s", $2, wCurrentScope->name );
            }
            wCurrentScope = wAddSymbol( $2, NULL, W_SYM_FUNCTION, W_TRUE );
            wPushStack( wBlockStack, W_TOKEN_FUNCTION );
        }

      parmlist sep  block sep
        {   wPopStack( wBlockStack );
            wCurrentScope->code = $6;
            $$ = NULL;
            wFree( $2 );
            wCurrentScope = NULL; }

    | W_TOKEN_SUB W_TOKEN_UNDEFINED
        {   if (wCurrentScope != NULL) {
                wFatal( W_SYNTAX, "Can't define Sub %s in %s", $2, wCurrentScope->name );
            }

            wCurrentScope = wAddSymbol( $2, NULL, W_SYM_SUB, W_TRUE );
            wPushStack( wBlockStack, W_TOKEN_SUB );
        }

      parmlist sep  block sep
        {   wPopStack( wBlockStack );
            wCurrentScope->code = $6;
            $$ = NULL;
            wFree( $2 );
            wCurrentScope = NULL; }


    | W_TOKEN_FUNCTION W_TOKEN_FUNCTION_NAME
        {   if (wCurrentScope != NULL) {
                wFatal( W_SYNTAX, "Can't define Function %s in %s",
                    $2->name, wCurrentScope->name );
            }
            if (!$2->forward) {
                wFatal( W_SYNTAX, "Function %s has already been declared", $2->name );
            }

            wCurrentScope = $2;
            wPushStack( wArgCountStack, 0 );
        }

        declaredList
        {   if (wPopStack( wArgCountStack ) != wCurrentScope->args) {
                wFatal( W_SYNTAX, "%s arg count does not match declaration - too few args", wCurrentScope->name);
            }
            wPushStack( wBlockStack, W_TOKEN_FUNCTION );
        }
        block sep
        {   wPopStack( wBlockStack );
            wCurrentScope->code = $6;
            wCurrentScope->forward = 0;
            $$ = NULL;
            wCurrentScope = NULL; }

    | W_TOKEN_FUNCTION W_TOKEN_FORWARD_FUNCTION_NAME
        {   if (wCurrentScope != NULL) {
                wFatal( W_SYNTAX, "Can't define Function %s in %s",
                    $2->name, wCurrentScope->name );
            }

            /* change to function */
            $2->symbolType = W_SYM_FUNCTION;
            wCurrentScope = $2;
            wPushStack( wBlockStack, W_TOKEN_FUNCTION );

            /* save var count and clear */
            wPushStack( wArgCountStack, wCurrentScope->args);
            wCurrentScope->args = 0;
        }

        parmlist sep  block sep
        {   wCheckArgCount( $2, wPopStack( wArgCountStack ) );
            wPopStack( wBlockStack );
            wCurrentScope->code = $6;
            wCurrentScope->forward = 0;
            $$ = NULL;
            wCurrentScope = NULL; }


    | W_TOKEN_SUB W_TOKEN_SUB_NAME
        {   if (wCurrentScope != NULL) {
                wFatal( W_SYNTAX, "Can't define Sub %s in %s",
                    $2->name, wCurrentScope->name );
            }
            if (!wCurrentScope->forward) {
                wFatal( W_SYNTAX, "Sub %s has already been declared", $2->name );
            }
            wCurrentScope = $2;
            wPushStack( wArgCountStack, 0 );
        }

        declaredList
        {   if (wPopStack( wArgCountStack ) != wCurrentScope->args) {
                wFatal( W_SYNTAX, "%s arg count does not match declaration - too few args", wCurrentScope->name);
            }
            wPushStack( wBlockStack, W_TOKEN_SUB );
        }

        block sep
        {   wPopStack( wBlockStack );
            wCurrentScope->code = $6;
            wCurrentScope->forward = 0;
            $$ = NULL;
            wCurrentScope = NULL; }


    | W_TOKEN_SUB W_TOKEN_FORWARD_SUB_NAME
        {   if (wCurrentScope != NULL) {
                wFatal( W_SYNTAX, "Can't define Sub %s in %s",
                    $2->name, wCurrentScope->name );
            }

            /* change to sub */
            $2->symbolType = W_SYM_SUB;
            wCurrentScope = $2;
            wPushStack( wBlockStack, W_TOKEN_SUB );

            /* save var count and wClear */
            wPushStack( wArgCountStack, wCurrentScope->args);
            wCurrentScope->args = 0;
        }

      parmlist sep  block sep
        {   wCheckArgCount( $2, wPopStack( wArgCountStack ) );
            wPopStack( wBlockStack );
            wCurrentScope->code = $6;
            wCurrentScope->forward = 0;
            $$ = NULL;
            wCurrentScope = NULL; }

    | W_TOKEN_FUNCTION error
        {   wExpected("Function name"); }

    | W_TOKEN_SUB error
        {   wExpected("Sub name"); }


    | W_TOKEN_INCLUDE_FILE W_TOKEN_STRING sep
        {   wPushIncludeFile( wCopyString($2), 0 );
            $$ = NULL;
            wFree( $2 ); }

    | W_TOKEN_LINE W_TOKEN_INPUT fileHandle ',' lval sep
        {   /* set into lval */
            $5->right = wIntNode( W_OP_INPUT, 1, $3, NULL );
            $$ = $5; }

    | W_TOKEN_LINE W_TOKEN_INPUT fileHandle error
        {   wExpected(", "); }

    | W_TOKEN_LINE error
        {   wExpected("Input"); }

    | W_TOKEN_OPEN expr W_TOKEN_FOR fileMode W_TOKEN_AS fileHandle sep
        {   $$ = wIntNode( W_OP_OPEN, $4, $2, $6 ); }

    | W_TOKEN_OPEN expr W_TOKEN_FOR fileMode W_TOKEN_AS error
        {   wExpected("#"); }

    | W_TOKEN_OPEN expr error
        {   wExpected("For"); }

    | W_TOKEN_OPTION W_TOKEN_EXPLICIT
        {   wExplicitFlag = 1;
            $$ = NULL; }

    | W_TOKEN_OPTION W_TOKEN_NOCONSOLE
        {   wConsoleFlag = 0;
            $$ = NULL; }


    | W_TOKEN_OPTION W_TOKEN_QBASIC
        {   wQBasicFlag = 1;
            $$ = NULL; }


    | W_TOKEN_PRINT printList sep
        {   $$ = wOpNode( W_OP_PRINT, NULL, $2 ); }

    | '?' printList sep
        {   $$ = wOpNode( W_OP_PRINT, NULL, $2 ); }

    | W_TOKEN_PRINT '#' expr ',' printList sep
        {   $$ = wOpNode( W_OP_PRINT, $3, $5 ); }

    | W_TOKEN_PRINT '#' expr error
        {   wExpected(", "); }

    | W_TOKEN_RETURN W_TOKEN_ARRAY_NAME '\n'
        {   wFatal( W_SYNTAX, "Array values cannot be returned" ); }

    | W_TOKEN_RETURN W_TOKEN_ARRAY_NAME optBrackets '\n'
        {   wFatal( W_SYNTAX, "Array values cannot be returned" ); }

    | W_TOKEN_RETURN expr sep
        {   if (!wInStack(wBlockStack,W_TOKEN_FUNCTION)) {
                wFatal( W_SYNTAX, "Return outside Function");
            }
            $$ = wOpNode( W_OP_RETURN_VALUE, $2, NULL ); }

    | W_TOKEN_RETURN sep
        {   if (!wInStack(wBlockStack,W_TOKEN_SUB) &&
                !wInStack(wBlockStack,W_TOKEN_FUNCTION)) {
                wFatal( W_SYNTAX, "Return outside Sub or Function");
            }
            $$ = wOpNode( W_OP_EXIT_ROUTINE, NULL, NULL ); }

    | W_TOKEN_SELECT W_TOKEN_CASE
        {   wPushStack(wBlockStack,W_TOKEN_SELECT); }

      expr sep cases sep
        {   wPopStack(wBlockStack);
            $$ = wOpNode( W_OP_CASE_SELECT, $4, $6 ); }


    | W_TOKEN_SELECT error
        {   wExpected( "Case" ); }

    | W_TOKEN_SHARED 
        {   if (wCurrentScope == NULL) {
                wFatal( W_SYNTAX, "Shared illegal outside Sub or Function");
            }
            wPushStack(wBlockStack, (int)wCurrentScope );
            wCurrentScope = NULL; }
        sharedList sep
        {   wCurrentScope = (wSymbol *)wPopStack(wBlockStack);
            $$ = NULL; }

    | W_TOKEN_WHILE
        {   wPushStack(wBlockStack,W_TOKEN_WHILE); }

      expr sep block sep
        {   wPopStack(wBlockStack);
            $$ = wOpNode( W_OP_WHILE, $3, $5 ); }

    | lval W_TOKEN_EQ expr sep
        {   $1->right = $3;
            $$ = $1; }

    | lval W_TOKEN_INCR_SELF expr sep
        {   /* simple var or array? */
            switch ($1->op) {
            case W_OP_ASSIGN:
                /* create a node to hold the operation */
                $1->right = wOpNode( $2,
                    wSymbolNode( W_OP_VAR, $1->value.symbol, NULL, NULL ), $3 );
                break;

            case W_OP_ARRAY_SET:
                /* create a node to hold the operation */
                $1->right = wOpNode( $2,
                        wSymbolNode( W_OP_ARRAY_GET, $1->value.symbol, $1->left, NULL ),
                        $3 );
                break;

            default:
                wFatal( W_SYNTAX, "IncrSelf: can't apply operation to %s",
                    $2, $1->value.symbol->name );
                break;
            }

            /* value to assign */
            $$ = $1; }

    /* obvious errors */

/*  old version
    | W_TOKEN_UNDEFINED '('
        {   wFatal( W_SYNTAX, "%s() is not defined", $1 ); }
*/

    | W_TOKEN_UNDEFINED '('
        {   wPushStack( wArgCountStack, 0 ); }

          argList sep
        {   wSymbol *s = wAddSymbol( $1, NULL, W_SYM_FORWARD_SUB, W_TRUE );
            s->forward = 1;
            s->code = NULL;
            s->args = wPopStack( wArgCountStack );
            wFree( $1 );

            $$ = wSymbolNode( W_OP_FUNCTION_CALL, s, $4, NULL );
        }




    | sep
        {  $$ = NULL; }

    ;

/* Note: the value to be assigned to the LVAL is */
/* placed in the right node, not the left        */

lval:
      W_TOKEN_UNDEFINED
        {   $$ = wSymbolNode( W_OP_ASSIGN, wReturnVar($1, W_SYM_VARIABLE, 0), NULL, NULL );
            wFree( $1 ); }

    | W_TOKEN_VARIABLE_NAME
        {   $$ = wSymbolNode( W_OP_ASSIGN, $1, NULL, NULL ); }

    | W_TOKEN_ARRAY_NAME '[' indexList
        { wCheckArgCount( $1, wPopStack( wArgCountStack ) );
          $$ = wSymbolNode( W_OP_ARRAY_SET, $1, $3, NULL ); }

    | W_TOKEN_ARRAY_NAME error
        {   wExpected("'['"); }

    ;

sep:
      '\n'
    | ':'
    | error
        {   if (strcmp(wCurrToken, "end-of-file") == 0 ) {
                wCheckBlockEnd(-1);
            }
            wExpected("end-of-line" ); }
    ;

elseIf:

    W_TOKEN_ELSEIF expr W_TOKEN_THEN sep block elseIf
      { $$ = wOpNode( W_OP_IF,
                wOpNode( W_OP_IF_TRUE, $2, $5 ),
                $6 ); }

    |  W_TOKEN_ELSE sep block
      { $$ = $3; }

    | /* none */
      { $$ = NULL; }
    
    ;

cases:
     W_TOKEN_CASE caseTests sep block cases
        { $$ = wComma( wComma( $2, $4 ), $5 ); }

    | W_TOKEN_CASE W_TOKEN_ELSE sep block
        { $$ = wComma(  wComma( wOpNode( W_OP_CASE_ELSE, NULL, NULL ), $4 ),
                        NULL ); }

    | /* nothing */
        { $$ = NULL; }
    ;


caseTests:
      expr W_TOKEN_TO expr caseTail
        { $$ = wOpNode( W_OP_CASE_RANGE, wComma( $1, $3 ), $4 ); }

    | expr caseTail
        { $$ = wIntNode( W_OP_CASE_CMP, W_EQ, $1, $2 ); }

    | W_TOKEN_IS W_TOKEN_EQ expr caseTail
        { $$ = wIntNode( W_OP_CASE_CMP, W_EQ, $3, $4 ); }

    | W_TOKEN_IS W_TOKEN_NE expr caseTail
        { $$ = wIntNode( W_OP_CASE_CMP, W_NE, $3, $4 ); }

    | W_TOKEN_IS W_TOKEN_GT expr caseTail
        { $$ = wIntNode( W_OP_CASE_CMP, W_GT, $3, $4 ); }

    | W_TOKEN_IS W_TOKEN_LT expr caseTail
        { $$ = wIntNode( W_OP_CASE_CMP, W_LT, $3, $4 ); }

    | W_TOKEN_IS W_TOKEN_LE expr caseTail
        { $$ = wIntNode( W_OP_CASE_CMP, W_LE, $3, $4 ); }

    | W_TOKEN_IS W_TOKEN_GE expr caseTail
        { $$ = wIntNode( W_OP_CASE_CMP, W_GE, $3, $4 ); }

    ;

caseTail:
      ',' caseTests
        { $$ = $2; }

    | /* nothing */
        { $$ = NULL; }
    ;


expr:

    '(' expr ')'
        { $$ = $2; }

    /* precedence 1 */

    | expr '^' optSep expr
        { $$ = wOpNode( W_OP_POWER, $1, $4 ); }

    | '-' expr %prec UMinus
        { $$ = wOpNode( W_OP_NEGATE, $2, NULL ); }


        /* precedence 2 */


    | expr '*' optSep expr
        { $$ = wOpNode( W_OP_MUL, $1, $4 ); }

    | expr '/' optSep expr
        { $$ = wOpNode( W_OP_DIV, $1, $4 ); }

    | expr '\\' optSep expr
        { $$ = wOpNode( W_OP_IDIV, $1, $4 ); }

    | expr '%' optSep expr
        { $$ = wOpNode( W_OP_MOD, $1, $4 ); }

    | expr W_TOKEN_SHL optSep expr
        { $$ = wOpNode( W_OP_SHL, $1, $4 ); }

    | expr W_TOKEN_SHR optSep expr
        { $$ = wOpNode( W_OP_SHR, $1, $4 ); }


        /* precedence 3 */


    | expr W_TOKEN_MOD optSep expr
        { $$ = wOpNode( W_OP_MOD, $1, $4 ); }

    | expr W_TOKEN_INV optSep expr
        { $$ = wOpNode( W_OP_INV, $1, $4 ); }


        /* precedence 4 */


    | expr '+' optSep expr
        { $$ = wOpNode( W_OP_ADD, $1, $4 ); }

    | expr '&' optSep expr
        { $$ = wOpNode( W_OP_CONCAT, $1, $4 ); }

    | expr '-' optSep expr
        { $$ = wOpNode( W_OP_SUB, $1, $4 ); }

    | expr '|' optSep expr
        { $$ = wOpNode( W_OP_OR_BITS, $1, $4 ); }


        /* precedence 5 */


    | expr W_TOKEN_EQ optSep expr
        { $$ = wIntNode( W_OP_CMP, W_EQ, $1, $4 ); }

    | expr W_TOKEN_NE optSep expr
        { $$ = wIntNode( W_OP_CMP, W_NE, $1, $4 ); }

    | expr W_TOKEN_LT optSep expr
        { $$ = wIntNode( W_OP_CMP, W_LT, $1, $4 ); }

    | expr W_TOKEN_GT optSep expr
        { $$ = wIntNode( W_OP_CMP, W_GT, $1, $4 ); }

    | expr W_TOKEN_LE optSep expr
        { $$ = wIntNode( W_OP_CMP, W_LE, $1, $4 ); }

    | expr W_TOKEN_GE optSep expr
        { $$ = wIntNode( W_OP_CMP, W_GE, $1, $4 ); }


        /* precedence 6 */

    | W_TOKEN_NOT expr
      { $$ = wOpNode( W_OP_NOT, $2, NULL ); }

    | '!' expr
      { $$ = wOpNode( W_OP_NOT, $2, NULL ); }


        /* precedence 7 */


    | expr W_TOKEN_AND optSep expr
      { $$ = wOpNode( W_OP_AND, $1, $4 ); }


        /* precedence 8 */


    | expr W_TOKEN_OR optSep expr
      { $$ = wOpNode( W_OP_OR, $1, $4 ); }


        /* precedence 9 */


    | expr W_TOKEN_XOR optSep expr
      { $$ = wOpNode( W_OP_XOR, $1, $4 ); }

    | expr W_TOKEN_IN optSep W_TOKEN_ARRAY_NAME optBrackets
        {   $$ = wSymbolNode( W_OP_IN, $4, $1, NULL ); }


        /* precedence 10 */


    | W_TOKEN_CLASS_NAME W_TOKEN_METHOD_NAME '('
        { wPushStack( wArgCountStack, 0 ); }

        argList
        {   wPopStack( wArgCountStack );
            $$ = wStringNode( W_OP_CLASS_METHOD, $2,
                    wSymbolNode( W_OP_COMMA, $1, NULL, NULL ), $5 ); }


    | W_TOKEN_CLASS_NAME W_TOKEN_METHOD_NAME
        {   $$ = wStringNode( W_OP_CLASS_METHOD, $2,
                    wSymbolNode( W_OP_COMMA, $1, NULL, NULL ), NULL ); }

    | expr W_TOKEN_METHOD_NAME '('
        { wPushStack( wArgCountStack, 0 ); }

        argList
        {   wPopStack( wArgCountStack );
            $$ = wStringNode( W_OP_METHOD, $2, $1, $5 ); }

    | expr W_TOKEN_METHOD_NAME
        {   $$ = wStringNode( W_OP_METHOD, $2, $1, NULL ); }


        /* lowest precedence */

    | W_TOKEN_NEW W_TOKEN_CLASS_NAME '('
        {   wPushStack( wArgCountStack, 0 ); }

        argList
        {   wPopStack( wArgCountStack );
            $$ = wSymbolNode( W_OP_NEW, $2, $5, NULL ); }

    | W_TOKEN_NEW W_TOKEN_CLASS_NAME
        {   $$ = wSymbolNode( W_OP_NEW, $2, NULL, NULL ); }

    | W_TOKEN_NEW
        { wExpected("a Class"); }

    | W_TOKEN_CLASS_NAME '('
        {   if (!wClassSafeOnStack( $1->klass )) {
                wFatal( W_SYNTAX, "Can't create %s on stack", $1->name );
            }
            wPushStack( wArgCountStack, 0 ); }
        argList
        {   wPopStack( wArgCountStack );
            $$ = wSymbolNode( W_OP_NEW_TMP, $1, $4, NULL ); }

    | W_TOKEN_CLASS_NAME
        {   wExpected("("); }

    | W_TOKEN_UNDEFINED
        { $$ = wSymbolNode( W_OP_VAR, wReturnVar($1, W_SYM_VARIABLE, 0), NULL, NULL );
          wFree($1); }

    | W_TOKEN_VARIABLE_NAME
        { $$ = wSymbolNode( W_OP_VAR, $1, NULL, NULL ); }

    | W_TOKEN_ARRAY_NAME optBrackets
        { $$ = wSymbolNode( W_OP_ARRAY_PTR, $1, NULL, NULL ); }

    | W_TOKEN_ARRAY_NAME '[' indexList
        { int args = wPopStack( wArgCountStack );
          wCheckArgCount( $1, args );
          $$ = wSymbolNode( W_OP_ARRAY_GET, $1, $3, NULL ); }

    | W_TOKEN_ARRAY_NAME
        {   wExpected("'['"); }

    | W_TOKEN_CONSTANT_NAME
        {   $$ = wSymbolNode( W_OP_CONST_GET, $1, NULL, NULL ); }

    | W_TOKEN_INTEGER
        { $$ = wIntNode( W_OP_INT, $1, NULL, NULL ); }

    | W_TOKEN_FLOAT
        { $$ = wFloatNode( W_OP_FLOAT, $1, NULL, NULL ); }

    | W_TOKEN_STRING
        { $$ = wStringNode( W_OP_STRING, $1, NULL, NULL ); }

    | W_TOKEN_BUILTIN_NAME '('
        { wPushStack( wArgCountStack, 0 ); }

          argList
        { int args = wPopStack( wArgCountStack );
          wCheckArgCount( $1, args );
          $$ = wSymbolNode( W_OP_BUILTIN, $1, $4, NULL ); }

    | W_TOKEN_BUILTIN_NAME
        { wCheckArgCount( $1, 0 );
          $$ = wSymbolNode( W_OP_BUILTIN, $1, NULL, NULL ); }

    | W_TOKEN_BUILTIN_NAME error
        {   wExpected("'('"); }

    | W_TOKEN_FUNCTION_NAME '('
        {   wPushStack( wArgCountStack, 0 ); }
            argList

        {   int args = wPopStack( wArgCountStack );
            wCheckArgCount( $1, args );
            $$ = wSymbolNode( W_OP_FUNCTION, $1, $4, NULL ); }

    | W_TOKEN_FUNCTION_NAME
        {   wCheckArgCount( $1, 0 );
            $$ = wSymbolNode( W_OP_FUNCTION, $1, NULL, NULL ); }

    | W_TOKEN_FUNCTION_NAME error
        {   wExpected("'('"); }

    | W_TOKEN_FORWARD_FUNCTION_NAME '('
        {   wPushStack( wArgCountStack, 0 ); }
            argList

        {   int args = wPopStack( wArgCountStack );
            wCheckArgCount( $1, args );
            $$ = wSymbolNode( W_OP_FUNCTION, $1, $4, NULL ); }

    | W_TOKEN_FORWARD_FUNCTION_NAME error
        {   wExpected("'('"); }

    | W_TOKEN_UNDEFINED '('
        {   wPushStack( wArgCountStack, 0 ); }
            argList

        {   wSymbol *s = wAddSymbol( $1, NULL, W_SYM_FORWARD_FUNCTION, W_TRUE );
            s->forward = 1;
            s->code = NULL;
            s->args = wPopStack( wArgCountStack );
            wFree( $1 );

            $$ = wSymbolNode( W_OP_FUNCTION, s, $4, NULL );
        }

    | error
        {   wExpected("an expression"); }
    ;

argList:
      ')'
        { $$ = NULL; }

    | argItems ')'
        { $$ = $1; }

    | argItems error
        {   wExpected("')'"); }
    ;

argItems:
      expr ',' optSep argItems
        { wIncrStack( wArgCountStack, 1 );
          $$ = wComma( $1, $4 ); }

    | expr
        { wIncrStack( wArgCountStack, 1 );
          $$ = $1; }

    | error
        { wExpected("an expression"); }
    ;

subList:
      expr ',' optSep subList
        { wIncrStack( wArgCountStack, 1 );
          $$ = wComma( $1, $4 ); }

    | expr
        { wIncrStack( wArgCountStack, 1 );
          $$ = $1; }

    | /* nothing */
        { $$ = NULL }
    ;


parmlist:
    | '(' ')'
    | '(' parmitem
    | /* nothing */
    ;

parmitem:
      W_TOKEN_UNDEFINED '[' ']'
        { wCreateParm( $1, W_SYM_ARRAY );
          wFree( $1 ); }
        parmtail

    | W_TOKEN_VARIABLE_NAME '[' ']'
        { wCreateParm( $1->name, W_SYM_ARRAY ); }
        parmtail

    | W_TOKEN_ARRAY_NAME '[' ']'
        { wCreateParm( $1->name, W_SYM_ARRAY ); }
        parmtail

    | W_TOKEN_UNDEFINED
        { wCreateParm( $1, W_SYM_VARIABLE );
          wFree( $1 ); }
        parmtail

    | W_TOKEN_VARIABLE_NAME
        { wCreateParm( $1->name, W_SYM_VARIABLE ); }
        parmtail

    | W_TOKEN_ARRAY_NAME
        { wCreateParm( $1->name, W_SYM_VARIABLE ); }
        parmtail

    | '.' '.' '.' ')'
        {   wCurrentScope->optArgs = W_MAX_OPT_ARGS; }


    | /* nothing */
        { wExpected("a parameter name"); }
    ;

parmtail:
      ',' optSep parmitem
    | ')'
    | error
        { wExpected("')'"); }
    ;

loopTail:
      W_TOKEN_EQ expr W_TOKEN_TO expr W_TOKEN_STEP expr sep block 
        { $$ = wSymbolNode( W_OP_FOR_STEP, NULL,
                    wComma( $2, wComma($4, $6) ),
                    $8 ); }

    | W_TOKEN_EQ expr W_TOKEN_TO expr W_TOKEN_STEP expr sep block 
        { $$ = wSymbolNode( W_OP_FOR_STEP, NULL,
                    wComma( $2, wComma($4, $6) ),
                    $8 ); }

    | W_TOKEN_EQ expr W_TOKEN_TO expr sep block 
        { $$ = wSymbolNode( W_OP_FOR, NULL, wComma( $2, $4 ), $6 ); }

    | W_TOKEN_EQ expr W_TOKEN_TO expr sep block 
        { $$ = wSymbolNode( W_OP_FOR, NULL, wComma( $2, $4 ), $6 ); }

    | W_TOKEN_EQ expr W_TOKEN_TO expr error
        { wExpected("Step"); }

    | W_TOKEN_EQ expr error
        { wExpected("To"); }

    | error
        { wExpected("'='"); }
    ;

printList:
      ';' printList
        { $$ = $2 }

    | ',' printList
        { $$ = wIntNode( W_OP_PRINT_VALUE, W_PRINT_TAB, NULL, $2 ); }

    | expr ',' printList
        { $$ = wIntNode( W_OP_PRINT_VALUE, W_PRINT_TAB, $1, $3 ); }

    | expr ';' printList
        { $$ = wIntNode( W_OP_PRINT_VALUE, W_PRINT, $1, $3 ); }

    | expr
        { $$ = wIntNode( W_OP_PRINT_VALUE, W_PRINT_NEWLINE, $1, NULL ); }

    | /* nothing */
        { $$ = NULL; }
    ;

indexList:
      { wPushStack( wArgCountStack, 0 ); }
      indexListTail
        { int args = wPeekStack( wArgCountStack );
          $$ = wComma( $2, wIntNode( W_OP_INT, args, NULL, NULL ) ); }
    ;

/* place items on stack in fifo order */
indexListTail:
      expr ']'
        { wIncrStack( wArgCountStack, 1 );
          $$ = wComma( $1, NULL ); }
                        
    | expr ',' optSep indexListTail
        { wIncrStack( wArgCountStack, 1 );
          $$ = wComma( $4, $1 ); }
    ;


dimList:
      dimItem ',' optSep dimList
        {   if ($1==NULL) {
                $$ = $4;
            } else if ($4==NULL) {
                $$ = $1;
            } else {
                $$ = wComma( $1, $4 );
            } }

    | dimItem
        { $$ = $1; }
    ;

dimItem:
       W_TOKEN_UNDEFINED '[' ']'
        { wSymbol *s = wCreateArraySymbol( $1, 0 );
          $$ = wSymbolNode( W_OP_INIT_ARRAY, s, NULL, NULL );
          wFree( $1 ); }

    | W_TOKEN_UNDEFINED '[' dimIndexList
        { int args = wPopStack( wArgCountStack );
          wSymbol *s = wCreateArraySymbol( $1, args );
          $$ = wSymbolNode( W_OP_INIT_ARRAY, s, $3, NULL );
          wFree( $1 ); }

    | W_TOKEN_VARIABLE_NAME '[' ']'
        { wSymbol *s = wCreateArraySymbol( $1->name, 0 );
          $$ = wSymbolNode( W_OP_INIT_ARRAY, s, NULL, NULL ); }

    | W_TOKEN_VARIABLE_NAME '[' dimIndexList
        { int args = wPopStack( wArgCountStack );
          wSymbol *s = wCreateArraySymbol( $1->name, args );
          $$ = wSymbolNode( W_OP_INIT_ARRAY, s, $3, NULL ); }

    | W_TOKEN_ARRAY_NAME '[' ']'
        { wSymbol *s = wCreateArraySymbol( $1->name, 0 );
          $$ = wSymbolNode( W_OP_INIT_ARRAY, s, NULL, NULL ); }

    | W_TOKEN_ARRAY_NAME '[' dimIndexList
        { int args = wPopStack( wArgCountStack );
          wSymbol *s = wCreateArraySymbol( $1->name, args );
          $$ = wSymbolNode( W_OP_INIT_ARRAY, s, $3, NULL ); }

    | W_TOKEN_UNDEFINED W_TOKEN_EQ expr
        {   $$ = wSymbolNode( W_OP_ASSIGN, wReturnVar($1, W_SYM_VARIABLE, 1), NULL, $3 );
            wFree( $1 ); }

    | W_TOKEN_UNDEFINED
        {   wReturnVar($1, W_SYM_VARIABLE, 1);
            wFree( $1 );
            $$ = NULL; }

    | W_TOKEN_VARIABLE_NAME W_TOKEN_EQ expr
        {   $$ = wSymbolNode( W_OP_ASSIGN, wReturnVar($1->name, W_SYM_VARIABLE, 1), NULL, $3 ); }

    | W_TOKEN_VARIABLE_NAME
        {   wReturnVar($1->name, W_SYM_VARIABLE, 1);
            $$ = NULL; }

    | W_TOKEN_ARRAY_NAME W_TOKEN_EQ expr
        {   $$ = wSymbolNode( W_OP_ASSIGN, wReturnVar($1->name, W_SYM_VARIABLE, 1), NULL, $3 ); } 

    | W_TOKEN_ARRAY_NAME
        {   wReturnVar($1->name, W_SYM_VARIABLE, 1);
            $$ = NULL; }

    | error
        {   wExpected("a name"); }
    ;

/* expr To expr | expr */
dimIndexList:
      { wPushStack( wArgCountStack, 0 ); }
      dimIndexItems
        { int args = wPeekStack( wArgCountStack );
          $$ = wComma( $2, wIntNode( W_OP_INT, args, NULL, NULL ) ); }
    ;

dimIndexItems:
      expr ']'
        { wIncrStack( wArgCountStack, 1 );
          $$ = wComma( $1, wIntNode( W_OP_INT, 0, NULL, NULL) ); }
                        
    | expr W_TOKEN_TO expr ']'
        { wIncrStack( wArgCountStack, 1 );
          $$ = wComma( $3, $1 ); }

    | expr W_TOKEN_TO expr ',' optSep dimIndexItems
        { wIncrStack( wArgCountStack, 1 );
          $$ = wComma( $6, wComma( $3, $1) ); }

    | expr ',' optSep dimIndexItems
        { wIncrStack( wArgCountStack, 1 );
          $$ = wComma( $4, wComma( $1, wIntNode( W_OP_INT, 0, NULL, NULL)) ); }
    ;


sharedList:
      sharedItem ',' optSep sharedList
    | sharedItem
    ;

sharedItem:
      W_TOKEN_VARIABLE_NAME
        {   if ($1->scope != NULL) {
                wFatal( W_SYNTAX, "Can't share local variable %s", $1->name );

            } else if (wInStack(wSharedStack,(int)$1)) {
                wFatal( W_SYNTAX, "Variable %s is already shared", $1->name );

            } else {
                wPushStack( wSharedStack, (int)$1 );

            } }


    | W_TOKEN_ARRAY_NAME '[' ']'
        {   if ($1->scope != NULL) {
                wFatal( W_SYNTAX, "Can't share local array %s", $1->name );

            } else if (wInStack(wSharedStack,(int)$1)) {
                wFatal( W_SYNTAX, "Array %s is already shared", $1->name );

            } else {
                wPushStack( wSharedStack, (int)$1 );

            } }

    | W_TOKEN_ARRAY_NAME '[' error
        {   wExpected("']'"); }

    | W_TOKEN_ARRAY_NAME error
        {   wExpected("'['"); }

    | error
        {   wExpected("a Variable name"); }
    ;


declaredList:
    | '(' ')'
    | '(' declaredItem
    | /* nothing */
    ;


declaredItem:
      ')'

    | W_TOKEN_VARIABLE_NAME ')'
        {   wIncrStack( wArgCountStack, 1 );
            if ($1->stackPos != wPeekStack(wArgCountStack) ) {
                wFatal( W_SYNTAX, "Variable %s does not match declaration", $1->name);
            } };

    | W_TOKEN_VARIABLE_NAME ',' optSep 
        {   wIncrStack( wArgCountStack, 1 );
            if ($1->stackPos != wPeekStack(wArgCountStack) ) {
                wFatal( W_SYNTAX, "Variable %s does not match declaration", $1->name);
            } }
        declaredItem

    | W_TOKEN_VARIABLE_NAME error
        {   wFatal( W_SYNTAX, "Parm list does not match declaration" ); }


    | W_TOKEN_ARRAY_NAME '[' ']' ')'
        {   wIncrStack( wArgCountStack, 1 );
            if ($1->stackPos != wPeekStack(wArgCountStack) ) {
                wFatal( W_SYNTAX, "Array %s does not match declaration", $1->name);
            } }

    | W_TOKEN_ARRAY_NAME '[' ']' ',' optSep
        {   wIncrStack( wArgCountStack, 1 );
            if ($1->stackPos != wPeekStack(wArgCountStack) ) {
                wFatal( W_SYNTAX, "Array %s does not match declaration", $1->name);
            } }
        declaredItem

    | W_TOKEN_ARRAY_NAME '[' ']' error
        {   wFatal( W_SYNTAX, "Parm list does not match declaration" ); }


    | W_TOKEN_ARRAY_NAME '[' error
        {   wExpected("']'"); }

    | W_TOKEN_ARRAY_NAME error
        {   wExpected("'['"); }

    | '.' '.' '.' ')'
        {   if (wCurrentScope->optArgs != W_MAX_OPT_ARGS) {
                wFatal( W_SYNTAX, "... does not match declaration" );
            } };
    | error
        {   wFatal( W_SYNTAX, "Parm list does not match declaration" ); }

    ;


optSep:
      '\n'
    | /* nothing */
    ;


optBrackets
    :   /* nothing */
    |   '[' ']'
    ;

fileMode:
      W_TOKEN_INPUT
        { $$ = W_FILE_MODE_INPUT; }

    | W_TOKEN_OUTPUT
        { $$ = W_FILE_MODE_OUTPUT; }

    | W_TOKEN_APPEND
        { $$ = W_FILE_MODE_APPEND; }

    | error
        {   wExpected("a File Mode: Input, Output or Append"); }
    ;

constList:
      constItem ',' optSep constList
        {   if ($4 == NULL) {
                $$ = $1;
            } else {
                $$ = wComma( $1, $4 );
            }
        }

    | constItem
        { $$ = $1; }
    ;

constItem:
      W_TOKEN_UNDEFINED W_TOKEN_EQ expr
        {   $$ = wSymbolNode( W_OP_CONST_Set, wCreateConst( $1 ), $3, NULL );
            wFree( $1 ); }

    | W_TOKEN_UNDEFINED error
        {   wExpected("'='"); }

    | error
        {   wFatal( W_SYNTAX, "Duplicate definition"); }
    ;

fileHandle
    : '#' expr
        {   $$ = $2 }
    | expr
        {   $$ = $1 }
    ;

