 /*************************************************************
    Name:       wrap.c
    Purpose:    routines to create wrappers for external classes
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/

/* create a symbol describing the new class */
wSymbol *wWrapClass( int flags, wSymbol *inherits, char *className )
{
    wSymbol *theClass;

    /* validate it */
    wSymbolUnused( className );

    /* create a symbol for the class */
    wTheCurrentScope = wTheGlobalScope;
    theClass = wSymbolNew( className, wTheGlobalScope, W_SYM_BUILTIN_CLASS );
    theClass->method = wGrowNew( 8 );
    // FIXME: the flags should be set to indicate the method type
    theClass->flags = flags;


    /* set the superclass */
    if (inherits != NULL) {
        theClass->inherits = inherits->index;
    }

    /* return the class */
    return theClass;
}

/* dereference the args */
void wWrapDerefArgs()
{
    int n;

    /* get the arg count */
    n = wTheCall->parmCount;

    /* skip if there are no args */
    if (n) {

        /* restore them on the stack */
        wTheStack->count = wTheStack->count + n;
        wTheStack->free = wTheStack->free - n;
    
        /* drop them */
        wStackDrop( n );
    }

}


/* attach a method to a class */
void wWrapMethod( int flags, wSymbol *klass, char *methodName, void (*routine)(void), int reqCount, int optCount )
{
    wSymbol *s;

    /* set the current scope and class scope to the class */
    wTheCurrentScope = klass->index;
    wTheClassScope = wTheCurrentScope;

    /* create symbol for the method */
    s = wSymbolNew( methodName, klass->index, W_SYM_BUILTIN );

    /* set the values */
    s->builtin = routine;
    s->args = reqCount;
    s->optArgs = optCount;
    s->flags = flags;

    /* add the method to the class */
    wGrowAppend( klass->method, s->index );

    /* restore the scope */
    wTheCurrentScope = wTheGlobalScope;
    wTheClassScope = 0;

}

/* set wTheCall->self to the object */
void wWrapSetThis( wSymbol *klass, void *data )
{
    int args, i, bytes;
    wSymbol *s, *child;
    wVariant *v;
    wObject *o;

    /* get self */
    o = wTheCall->self;

    /* store the pointer */
    o->ptr = data;
// wConsolePrintf("refCount of wWrapSetThis %s is %d\n", o->klass->name, o->refCount );    

    /* display destruction for debugging */
    if (wTheDebugOnFlag) {
        wConsolePrintf("created %s at %p\n", o->klass->name, o );
    }
}

/* push a new object onto the stack */
void wWrapPushObject( wSymbol *klass, int tmpFlag, void *data )
{
    wVariant *variant;
    wObject *object;

    /* create an object to hold the pointer */
    object = wObjectNew( klass->index, tmpFlag );

    /* store the pointer */
    object->ptr = data;
//wConsolePrintf("refCount of wWrapPushObject %s is %d\n", object->klass->name, object->refCount );
    /* get a variant from the stack */
    variant = wStackPushNothing();

    /* cast it into an object */
    variant->dataType = W_TYPE_OBJECT;
    variant->value.object = object;
}
