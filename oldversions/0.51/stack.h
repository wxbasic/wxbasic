/*
    Name:       stack.h
    Purpose:    Integer stacks for wxBasic
    Author:     David Cuny
    Copyright:  (c) 2002 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*/

struct wStack {
    int     tos;        /* top of stack */
    int     size;       /* size of stack */
    int     data[1];    /* stack data */
};

wStack *wNewStack( int size );
void wPushStack( wStack *stack, int value );
void wIncrStack( wStack *stack, int value );
void wDecrStack( wStack *stack, int value );
void wSwapStack( wStack *stack  );
void wDupStack( wStack *stack  );
int wPeekStack( wStack *stack  );
int wPopStack( wStack *stack  );
int wIsEmptyStack( wStack *stack  );
int wInStack( wStack *stack, int val  );
void wClearStack( wStack *stack  );
void wFreeStack( wStack *stack );
