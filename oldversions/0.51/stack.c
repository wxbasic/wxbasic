/*
    Name:       stack.c
    Purpose:    Integer stacks for wxBasic
    Author:     David Cuny
    Copyright:  (c) 2002 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*/

/* create a new stack */
wStack *wNewStack( int size )
{
    wStack *stack;

    /* allocate stack */
    stack = (wStack *)wMalloc( sizeof( wStack ) +
                (sizeof(int) * (size)) );

    stack->tos = -1;
    stack->size = size;
    return stack; 
}

/* push an item on the stack */
void wPushStack( wStack *stack, int value )
{
    if (stack->tos == stack->size) {
        wFatal( W_RUNTIME, "pushStack: stack overflow");
    }
    stack->tos++;
    stack->data[stack->tos] = value;
}

/* increment the value on the stack */
void wIncrStack( wStack *stack, int value )
{
    stack->data[stack->tos] += value;
}

/* decrement the value on the stack */
void wDecrStack( wStack *stack, int value )
{
    stack->data[stack->tos] -= value;
}


/* swap top two stack items */
void wSwapStack( wStack *stack  )
{
    int tmp;

    if (stack->tos < 1) {
        wFatal( W_RUNTIME, "swapStack: stack underflow");
    }

    tmp = stack->data[stack->tos];
    stack->data[stack->tos] = stack->data[stack->tos-1];
    stack->data[stack->tos-1] = tmp;
}

/* duplicate top stack item */
void wDupStack( wStack *stack  )
{
    if (stack->tos < 0) {
        wFatal( W_RUNTIME, "dupStack: underflow" );
    } else if (stack->tos == stack->size) {
        wFatal( W_RUNTIME, "dupStack: overflow" );
    }
    stack->tos++;
    stack->data[stack->tos] = stack->data[stack->tos-1];
}


/* return copy of top stack item */
int wPeekStack( wStack *stack  )
{
    if (stack->tos < 0) {
        wFatal( W_RUNTIME, "peekStack: underflow" );
    }
    return stack->data[stack->tos];
}


/* pop an item off the stack */
int wPopStack( wStack *stack  )
{
    if (stack->tos < 0) {
        wFatal( W_RUNTIME, "popStack: underflow" );
    }
    stack->tos--;
    return stack->data[stack->tos+1];
}


/* return nonzero if stack is not empty */
int wIsEmptyStack( wStack *stack  )
{
    return (stack->tos == -1);
}

/* return true if item is in the stack */
int wInStack( wStack *stack, int val  )
{
    int     i;
    for ( i = stack->tos; i > -1; i-- ) {
        if (stack->data[i] == val) {
            return 1;
        }
    }
    return 0;
}


/* pop all elements off the stack */
void wClearStack( wStack *stack  )
{
    stack->tos = -1;
}


/* destroy a stack */
void wFreeStack( wStack *stack )
{
    free( stack );
}
