/*************************************************************
    Name:       parse.h
    Purpose:    wxBasic grammar parser
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/

/* state stacks for the parser */
wGrow *wArgCountStack;
wGrow *wBreakStack;
wGrow *wCaseStack;
wGrow *wCatchStack;
wGrow *wContinueStack;
wGrow *wElseStack;
wGrow *wEndIfStack;
wGrow *wForStack;
wGrow *wMiscStack;
wGrow *wBlockTypeStack;
wGrow *wRedoStack;
wGrow *wTempCountStack;
wGrow *wTryStack;
wGrow *wFinallyStack;

void dumpCode( wCode *code );
void wParseInit( void );
int wParseGetScope( void );
int wParseTokenIs( int id );
void wParseSkip( void );
void wParseExpect( int expect, char *name );
wCode *wParseFile( void );
wCode *wParseBlock( void );
wCode *wParseStatementBuiltinName( void );
wCode *wParseStatementClose( void );
wCode *wParseStatementConst( void );
wCode *wParseStatementDestroy( void );
wCode *wParseStatementDim( int isStatic );
wCode *wParseStatementEnd( void );
wCode *wParseStatementInput( void ); 
wCode *wParseStatementLine( void );  
wCode *wParseStatementOpen( void );  
wCode *wParseStatementOption( void );
wCode *wParseStatementSelect( void );
wCode *wParseStatementShared( void );
wSymbol *wParseCreateUndeclaredLocal( char *name );
wCode *wParseMeProperty( void );
wCode *wParseLval( void );
wCode *wParseDotMethod( void );
wCode *wParseStatementAssign( void );
void wParseCleanupTryBlocks( wCode *code, int isReturn );
wCode *wParseJump( wGrow *stack, char *name );
wCode *wParseStatementBreak( void );
wCode *wParseStatementClass( void );
wCode *wParseStatementContinue( void );
wCode *wParseStatementDef( void );
wCode *wParseStatementExit( void );
wCode *wParseStatementFor( void );
wCode *wParseStatementForEach( void );
wCode *wParseStatementDef();
wCode *wParseStatementIf( void );
wCode *wParseStatementInput( void );
wCode *wParseStatementPrint( void );
wCode *wParseStatementReturn( void );
wCode *wParseStatementRedo( void );
wCode *wParseStatementRoutineName( int returnCount );
void wParseCheckArgCount( wSymbol *s, int parmCount );
wCode *wParseStatementThrow( void );
wCode *wParseStatementTry( void );
wCode *wParseStatementWhile( void );
wCode *wParseStatement( void );
int wParsePeekPastLval( void );
void wParseJoinOperands( wCode *lhs, wCode *rhs, int opToken );
wCode *wParseOperand( void );
int wParseOpStrength( void );
wCode *wParseExpression( int priorStrength );
int wParseIsSeperator( void );
void wParseSeperator( void );
void wParseOptionalSeperator( void );
wCode *wParseOptionalArgList( void );
wCode *wParseArgList( void );
int wParseIndexes( wCode *code );
wCode *wParseTable( void );
wCode *wParseList( void );
wCode *wParseIndexOrSlice( void );
int wParseAsClause( int startIndex, int endIndex );
wSymbol *wParseVariableName( void );
