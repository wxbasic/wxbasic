/*************************************************************
    Name:       state.c
    Purpose:    state stacks for parser
    Author:     David Cuny
    Copyright:  (c) 2002 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/

/* set tos of all stacks to -1 (empty) */
void wStateInit()
{
	int i;
	for ( i = 0; i < W_STATE_COUNT; i++ ) {
		wStateTos[i] = -1;
	}
}

void wStateRangeCheck( int stackNumber )
{

	/* check stack */
	if (stackNumber < 0 || stackNumber >= W_STATE_COUNT) {
        wErrorFatal( "Bad stack number %d (wStateRangeCheck)", stackNumber );
        wErrorSet( W_ERROR_INTERNAL );

	}
}

/* push a number onto one of the state stacks */
void wStatePush( int stackNumber, int value )
{
	int tos;
    
	/* check stack */
	wStateRangeCheck( stackNumber );
	
	/* increment top of stack */
	tos = ++wStateTos[stackNumber];
	if (tos >= W_STATE_MAX) {
        wErrorFatal( "Overflow on internal state %s (wStatePush)",
            wStateStackName[stackNumber] );
        wErrorSet( W_ERROR_INTERNAL );
	}

	/* set value */
	wStateStack[stackNumber][tos] = value;
}

int wStatePop( int stackNumber )
{
	int tos;

	/* check stack */
	wStateRangeCheck( stackNumber );
    
	/* decrement top of stack */
	tos = --wStateTos[stackNumber];
	if (tos < -1) {
        wErrorFatal( "Underflow on internal %s (wStatePop)",
            wStateStackName[stackNumber] );
        wErrorSet( W_ERROR_INTERNAL );

	}
	
	/* return value on prior top of stack */
	return wStateStack[stackNumber][tos+1];
}

/* return value on top of stack */
int wStatePeek( int stackNumber )
{
	int tos;
	
	/* check stack */
	wStateRangeCheck( stackNumber );

	/* get top of stack */
	tos = wStateTos[stackNumber];
	if (tos == -1) {
        wErrorFatal( "Internal %s is empty (wStatePeek)",
            wStateStackName[stackNumber] );
        wErrorSet( W_ERROR_INTERNAL );

	}
	
	/* get value */
	return wStateStack[stackNumber][tos];
}

/* return value on top of stack */
int wStateIsEmpty( int stackNumber )
{
	int tos;
	
	/* check stack */
	wStateRangeCheck( stackNumber );

	/* get top of stack */
	tos = wStateTos[stackNumber];
	
	/* get value */
	return (tos == -1);
	
}

void wStateIncr( int stackNumber, int value )
{
	int tos;

	/* check stack */
	wStateRangeCheck( stackNumber );
    
	/* add value to top of stack */
	wStateStack[stackNumber][tos] += value;
}


/* return true if in stack */
int wStateFind( int stackNumber, int value )
{
	int tos, i;
	
	/* check stack */
	wStateRangeCheck( stackNumber );

	/* get top of stack */
	tos = wStateTos[stackNumber];
	
	/* loop until bottom of stack */
	for ( i = tos; i > -1;  i-- ) {
		/* hit marker? */
		if (wStateStack[stackNumber][i] == value) {
			return -1;
		}
	}
	
	/* not found */
	return 0;
	
}


/* clear stack down to -1 marker */
void wStateClear( int stackNumber )
{
	int tos, i;
	
	/* check stack */
	wStateRangeCheck( stackNumber );

	/* get top of stack */
	tos = wStateTos[stackNumber];
	
	/* loop until 1 less than bottom of stack */
	for ( i = tos; i > 0;  i-- ) {
		/* hit marker? */
		if (wStateStack[stackNumber][i] == -1) {
			break;
		}
	}
	
	/* set value to *below* the spot where search stopped */
	wStateTos[stackNumber] = i-1;
	
}
