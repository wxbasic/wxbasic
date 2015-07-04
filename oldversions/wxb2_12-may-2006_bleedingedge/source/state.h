/*************************************************************
    Name:       state.h
    Purpose:    state stacks for parser
    Author:     David Cuny
    Copyright:  (c) 2002 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/

#ifndef WXBASIC_STATE_DECLARES
#define WXBASIC_STATE_DECLARES


/* indexes of various wStateStacks */
enum {	
    W_BLOCK_STACK = 0,		/* type of block (while, for, etc.) */
    W_ARG_COUNT_STACK,      /* count of arguments on stack */
    W_CONTINUE_STACK,		/* stack with CONTINUE jump label */
    W_ELSE_STACK,           /* stack with ELSE jump label */
    W_BREAK_STACK,          /* stack with BREAK jump label */
    W_MISC_STACK            /* miscellaneous */
};

char *wStateStackName[] = {
    "code block stack",
    "arg count stack",
    "address start stack",
    "else stack",
    "end stack"
};

void wStateInit( void );
void wStateRangeCheck( int stackNumber );
void wStatePush( int stackNumber, int value );
int wStatePop( int stackNumber );
int wStatePeek( int stackNumber );
int wStateIsEmpty( int stackNumber );
void wStateIncr( int stackNumber, int value );
int wStateFind( int stackNumber, int value );
void wStateClear( int stackNumber );


#endif
