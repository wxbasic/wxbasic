/*************************************************************
    Name:       object.c
    Purpose:    class objects for wxBasic
    Author:     David Cuny
    Copyright:  (c); 2002 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/


/* create a new user-defined object */
wObject *wObjectNew( int klass, int tmpFlag )
{
    int args, i, bytes;
    wObject *o;
    wSymbol *s, *child;
printf("in object new\n");
    /* lookup the symbol */
    s = wSymbolLookup( klass );
    wMemTest( s, "wObjectNew:s" );

    /* error if this is abstract */
    if (s->flags & W_SYM_ISABSTRACT) {
        wErrorFatal( "Can't create abstract class %s", s->name );
        wErrorSet( W_ERROR_NOSUCH );
        return NULL;
    }

    /* get the number of args in the class */
    wMemTest( s->children, "wObjectNew:s->children" );
    args = s->children->count;

    /* calculate size of extra space needed */
    if (args) {
        /* space to hold variants, less initial one allotted */
        bytes = sizeof( wVariant ) * (args-1);
    } else {
        bytes = 0;
    }

    /* allocate in memory */
    o = (wObject *)wMalloc( sizeof( wObject ) + bytes );

    /* initialize */
    o->klass = s;

    /* reference count information */
    o->tmpFlag = tmpFlag;
    o->refCount = 1;


    /* initialized the properties to undefined */
    for ( i = 0; i < args; i++ ) {
        /* get the symbol for the local */
        child = wSymbolGetChild( s, i+1 );
        wMemTest( child, "wObjectNew:child" );

        /* set the initial value to nothing */
        o->prop[i].dataType = W_TYPE_NOTHING;

        /* store the datatype */
        o->prop[i].typeCast = child->typeCast;
    }

    /* display destruction for debugging */
    if (wTheDebugFlag) {
        wConsoleDebug("created %s at %p\n", o->klass->name, o );
    }

wConsolePrintf("refCount of wObjectNew %s is %d\n", o->klass->name, o->refCount );
    return o;
}


/* deref an object; calls finalize method when destroyed */
void wObjectDeref( wObject *o )
{
    int index;
    wSymbol *method;

    wMemTest( o, "wObjectDeref:o" );

    /* is this a reference counted object? */
    if (o->tmpFlag) {
        /* dereference */
        o->refCount--;
wConsolePrintf("wObjectDeref: refCount of %s is %d\n", o->klass->name, o->refCount );
        /* no more references? */
        if (o->refCount == 0) {
wConsolePrintf("wObjectDeref: freeing the object %s\n", o->klass->name );
            /* lookup the "finalize" method */
            method =  wSymbolFindMethodChar( o->klass, "finalize" );
            if (method != NULL) {
wConsoleDebug("calling finalize of %s\n", o->klass->name );
                /* call the new routine */
                wCallRoutine( method, 0, 0, o );
            }

            wObjectFree( o );
        }
} else {
wConsolePrintf("%s is not temporary, no dereferencing\n", o->klass->name);
    }

}

void wObjectFree( wObject *o )
{
    int i, args;

    wMemTest( o, "wObjectNew:o" );

    /* display destruction for debugging */
    if (wTheDebugFlag) {
        wConsoleDebug("destroying the %s at %p\n", o->klass->name, o );
    }

    /* get the number of args in the class */
    args = o->klass->children->count;
    for ( i = 0; i < args; i++ ) {
        /* dereference each item */
        wVariantDeref( &(o->prop[i]) );
    }
    wFree( o );
}
