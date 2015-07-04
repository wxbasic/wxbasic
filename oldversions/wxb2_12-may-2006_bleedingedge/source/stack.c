/*************************************************************
    Name:       stack.c
    Purpose:    datastack for wxBasic
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/

void wStackNew( int size )
{
    int i;
    wVariant *variant;

    /* create a grow array */
    wTheStack = wGrowNew( size );

    /* initialize the stack */
    for (i=0; i < size; i++) {
        wGrowAppend( wTheStack, 0 );
    }

    /* set stack down to zero */
    wTheStack->count = 0;
    wTheStack->free = size;
    
}

/* push undefined on stack, return address */
wVariant *wStackPushNothing()
{
    int index;
    wVariant *variant;

    index = wGrowMakeRoom( wTheStack );

    /* initialized? */
    if (wGrowGet( wTheStack, index ) == 0) {
        variant = (wVariant *)wMalloc( sizeof( wVariant ) );
        wGrowSet( wTheStack, index, (int)variant );
    } else {
        /* get the address of the new item */
        variant = (wVariant *)wGrowGet( wTheStack, index );
    }

	/* set it as undefined */
    variant->dataType = W_TYPE_NOTHING;

	return variant;
}


void wStackPushNumber( wNumber n )
{
    wVariant *variant;

    /* create a slot for the data */
    variant = wStackPushNothing();

    /* set the datatype and value */
    variant->dataType = W_TYPE_NUMBER;
    variant->value.number = n;
}

/* push results, trigger error if math flag set */
void wStackPushNumberFromRoutine( wNumber n, char *routine )
{                                                 
    wVariant *variant;

    /* check for math error flag */
    if (errno == EDOM) {
        wErrorThrow( W_ERROR_MATH, "Argument to %s out of range", routine );

    } else {

        /* create a slot for the data */
        variant = wStackPushNothing();
    
        /* set the datatype and value */
        variant->dataType = W_TYPE_NUMBER;
        variant->value.number = n;
   }
}



/* push a C string onto the stack */
void wStackPushChar( char *s, int isRaw )
{
    wVariant *variant;

#ifdef __WDEBUG__
    /* track the "raw" C string? */
    if (isRaw) {
        wMemAdd( (void *)s, strlen( s )+1 );
    }
#endif

    /* create a slot for the value */
    variant = wStackPushNothing();
    /* create a string at that spot */
    wStringNew( variant, s, -1 );

#ifdef __WDEBUG__
    /* stop tracking the "raw" C string */
    if (isRaw) {
        wMemRemove( (void *)s );
    }
#endif

}


/* push a time_t value onto the stack */
void wStackPushDateTime( time_t t )
{
    wVariant *dst;

    /* create a slot for the value */
    dst = wStackPushNothing();

    /* set the value */
    dst->dataType = W_TYPE_DATETIME;
    dst->value.time = t;
}



/* push an variant onto the stack */
void wStackPush( wVariant *src )
{
    int index;
    wVariant *dst;

    wMemTest( src, "wStackPush:src" );

    /* create a slot for the value */
    dst = wStackPushNothing();

    wMemTest( dst, "wStackPush:dst" );

    /* push onto stack */
    wVariantCopy( dst, src );
}


/* push pointer to a variant onto the stack */
void wStackPushPtr( wVariant *src )
{
    int index;
    wVariant *dst;

    wMemTest( src, "wStackPushPtr:src" );

    /* create a slot for the value */
    dst = wStackPushNothing();

    wMemTest( dst, "wStackPush:dst" );

    /* push the variant's pointer onto the stack */
    wVariantRef( src );
    dst->dataType = W_TYPE_VARPTR;
    dst->value.varptr = src;
}

/* return pointer to requested stack item */
wVariant *wStackItem( int index )
{
    wVariant *variant;

    /* check for underflow */
    if (index < 1 || index > wTheStack->count) {
        wErrorThrow( W_ERROR_INTERNAL, "Index out of range (wStackItem)" );
    }

    /* get the item */
    variant = (wVariant *)wGrowGet( wTheStack, index );
    wMemTest( variant, "wStackPushItem:variant" );

    return variant;

}

/* return pointer to the nth stack item. Item remains on the stack */
wVariant *wStackPeek( int index )
{
    int tos;
    wVariant *variant;

    /* find top of stack */
    tos = wTheStack->count;

    /* check for underflow */
    if (tos < 1 || tos-index < 1) {
        wErrorThrow( W_ERROR_INTERNAL, "Stack underflow (wStackPeek)" );
    }

    /* get the item */
    variant = (wVariant *)wGrowGet( wTheStack, tos-index );
    wMemTest( variant, "wStackPushPeek:variant" );

    return variant;
}

/* return pointer to top stack item, and lower stack. Item remains on the stack */
wVariant *wStackPop()
{
    int tos;
    wVariant *variant;

    /* find top of stack */
    tos = wTheStack->count;

    /* check for underflow */
    if (tos < 1) {
        wErrorThrow( W_ERROR_INTERNAL, "Stack underflow (wStackPop)" );
    }

    /* get the item */
    variant = (wVariant *)wGrowGet( wTheStack, tos );
    wMemTest( variant, "wStackPop:variant" );

    /* adjust the stack size */
    wTheStack->free++;
    wTheStack->count--;
    
    return variant;
    
}

/* return number from top of stack */
wNumber wStackPopNumber()
{
    wVariant *variant;
    wNumber n;

    variant = wStackPop();
    wMemTest( variant, "wStackPopNumber:variant" );

    n = wVariantGetNumber( variant );
    wVariantDeref( variant );
    return n;
}

/* return string from top of stack, leaves on stack */
wVariant *wStackPopString()
{

    wVariant *variant;

    variant = wStackPop();
    wMemTest( variant, "wStackPopString:variant" );
    wVariantCoerce( variant, W_TYPE_STRING );
    return variant;
}

/* return pointer to char string, leaves wString on stack */
char *wStackPopChar()
{
    return wStringChar( wStackPopString() );
}


/* return time from top of stack */
time_t wStackPopDateTime()
{
    char        *buffer;
    time_t        t;
    wVariant    *v;

    /* get the value from the stack */
    v = wStackPop();
    wMemTest( v, "wStackPopNumber:v" );

    /* if not already TIME, coerce */
    if (v->dataType != W_TYPE_DATETIME) {
        wVariantCoerce( v, W_TYPE_DATETIME );
    }
    return v->value.time;
}



/* return value of lval on stack */
wVariant *wStackPopLval()
{
    wVariant *v1, *v2;

    /* get the value on the stack */
    v1 = wStackPop();

    /* varptr or object? */
    if (v1->dataType != W_TYPE_VARPTR) {
        wErrorThrow( W_ERROR_INTERNAL, "Expected VarPtr, not %s",
                wDataTypeName[v1->dataType] );
    }

    /* get pointer address */
    v2 = v1->value.varptr;
    
    /* zap the pointer so it won't get deref'd */
    v1->dataType = W_TYPE_NOTHING;
    
    return v2;
}

/* pop and destroy an element on the top of the stack */
void wStackDrop( int n )
{
    int tos, i;
    wVariant *variant;

    /* find top of stack */
    tos = wTheStack->count;

    /* check for underflow */
    if (tos < n) {
        wErrorThrow( W_ERROR_INTERNAL, "Stack underflow (wStackDrop)" );
    }

    for ( i = 0; i < n; i++ ) {

        /* get the item */
        variant = (wVariant *)wGrowGet( wTheStack, tos-i );
        wMemTest( variant, "wStackDrop:variant" );
    
        /* dereference the item */
        wVariantDeref( variant );
    }

    /* lower the stack - this is a bit of a hack! */
    wTheStack->free = wTheStack->free + n;
    wTheStack->count = wTheStack->count - n;
}


/* pop and destroy an element on the top of the stack, but keep objects */
void wStackDropExtra( int n )
{
	
    /* this is used to drop "extra" items left on the stack after a call  */
    /* to wxCallRoutine(). Unlike wStackDrop(), Objects left on the stack */
    /* are not destroyed, which reflects the C++ behavior.                */
	
    int tos, i;
    wVariant *variant;

    /* find top of stack */
    tos = wTheStack->count;

    /* check for underflow */
    if (tos < n) {
        wErrorThrow( W_ERROR_INTERNAL, "Stack underflow (wStackDrop)" );
    }

    for ( i = 0; i < n; i++ ) {

        /* get the item */
        variant = (wVariant *)wGrowGet( wTheStack, tos-i );
        wMemTest( variant, "wStackDrop:variant" );
    
        /* leaving object on stack? */
        if (variant->dataType == W_TYPE_OBJECT) {
            /* ensure it doesn't get refcounted away */
            variant->value.object->tmpFlag = W_FALSE;
        }

        /* dereference the item */
        wVariantDeref( variant );
    }

    /* lower the stack - this is a bit of a hack! */
    wTheStack->free = wTheStack->free + n;
    wTheStack->count = wTheStack->count - n;
}


/* swap the two top items on the stack */
void wStackSwap( int i1, int i2 )
{
    wVariant *a, *b, *tmp;
    
    /* allocate extra spot on top of stack */
    tmp = wStackPushNothing();
    
    /* elements to swap */
    a = wStackPeek( i1+1 );
    b = wStackPeek( i2+1 );
    
    /* swap */
    wVariantMove( tmp, a );
    wVariantMove( a, b );
    wVariantMove( b, tmp );
    
    /* zap tmp */    
    wStackPop();    
}

/* return pointer to object, leave object on stack */
void *wStackPopObjectPtr( wSymbol *memberOfKlass )
{
    wVariant *variant;
    wObject *object;
    wSymbol *klass;

    /* get the value on the stack */
    variant = wStackPop();

    /* nothing? */
    if (variant->dataType == W_TYPE_NOTHING) {
        /* treat as null */
        return NULL;
    }

    /* object? */
    if (variant->dataType != W_TYPE_OBJECT) {
        wErrorThrow( W_ERROR_INTERNAL, "Expected Object, not %s",
                wDataTypeName[variant->dataType] );
    }

    /* get the object */
    object = variant->value.object;

    /* verify the class? */
    if (memberOfKlass != NULL) {
        klass = object->klass;
        while (W_TRUE) {
            /* member of class? */
            if (klass == memberOfKlass) {
                break;
            }
    
            /* superclass? */
            if (klass->inherits) {
                /* get the superclass */
                klass = wSymbolLookup( klass->inherits  );
            } else {
                wErrorThrow( W_ERROR_INTERNAL, "Expected %s, not %s",
                    memberOfKlass->name, object->klass->name );
            }
        }
    }

    /* return pointer address */
    return object->ptr;
}
