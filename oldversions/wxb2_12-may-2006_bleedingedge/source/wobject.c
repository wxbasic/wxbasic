/*************************************************************
    Name:       wobject.c
    Purpose:    W_TYPE_OBJECT datatype - instances of class objects
    Author:     David Cuny
    Copyright:  (c); 2002 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/

/* assign methods */
void wObjectRegisterMethods()
{
    /* register the routines */
    wTheHandler[W_TYPE_OBJECT]->isNumeric       = W_FALSE;
    wTheHandler[W_TYPE_OBJECT]->ref             = wObjectRef;
    wTheHandler[W_TYPE_OBJECT]->deref           = wObjectDeref;
    wTheHandler[W_TYPE_OBJECT]->copy            = wObjectCopy;
    wTheHandler[W_TYPE_OBJECT]->clone           = wObjectClone;
    wTheHandler[W_TYPE_OBJECT]->fromNumber      = NULL;
    wTheHandler[W_TYPE_OBJECT]->toNumber        = NULL;
    wTheHandler[W_TYPE_OBJECT]->fromChar        = NULL;
    wTheHandler[W_TYPE_OBJECT]->toChar          = wObjectToChar;
    wTheHandler[W_TYPE_OBJECT]->compare         = NULL;
    wTheHandler[W_TYPE_OBJECT]->equal           = wObjectEqual;
    wTheHandler[W_TYPE_OBJECT]->isTrue          = NULL;
    wTheHandler[W_TYPE_OBJECT]->count           = NULL;
    wTheHandler[W_TYPE_OBJECT]->index           = NULL;
    wTheHandler[W_TYPE_OBJECT]->find            = NULL;
    wTheHandler[W_TYPE_OBJECT]->remove          = NULL;
    wTheHandler[W_TYPE_OBJECT]->append          = NULL;
    wTheHandler[W_TYPE_OBJECT]->prepend         = NULL;
    wTheHandler[W_TYPE_OBJECT]->slice           = NULL;
    wTheHandler[W_TYPE_OBJECT]->iterate         = NULL;
}

/* create a new user-defined object */
wObject *wObjectNew( int klass, int tmpFlag )
{
    int propCount, i, bytes;
    wObject *o;
    wSymbol *s, *child;

    /* lookup the symbol */
    s = wSymbolLookup( klass );
    wMemTest( s, "wObjectNew:s" );

    /* error if this is abstract */
    if (s->flags & W_SYM_ISABSTRACT) {
        wErrorThrow( W_ERROR_NOSUCH, "Can't create abstract class %s", s->name );
        return NULL;
    }

    /* user-defined class? */
    if (s->children == NULL) {
        /* no properties */
        propCount = 0;

    } else {
        /* get the number of objects in the class */
        wMemTest( s->children, "wObjectNew:s->children" );
        propCount = s->children->count;
    }

    /* calculate size of extra space needed */
    if (propCount) {
        /* space to hold variants, less initial one allotted */
        bytes = sizeof( wVariant ) * (propCount-1);
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
    o->propCount = propCount;

    /* initialize the properties to undefined */
    for ( i = 0; i < propCount; i++ ) {
        /* get the symbol for the local */
        child = wSymbolGetChild( s, i+1 );
        wMemTest( child, "wObjectNew:child" );

        /* set the initial value to nothing */
        o->prop[i].dataType = W_TYPE_NOTHING;

        /* store the datatype */
        o->prop[i].typeCast = child->typeCast;
    }

    /* display destruction for debugging */
    if (wTheDebugOnFlag) {
        //wConsoleDebugf("created %s at %p\n", o->klass->name, o );
    }

    return o;
}


/* refcount an object */
void wObjectRef( wVariant *src )
{ 
	wMemTest( src->value.object, "wObjectRef:src->value.object" );
    src->value.object->refCount++;
}


int wObjectInheritsWxWindow( wSymbol *klass )
{
#ifdef __WXWIN__
    wSymbol *wxWindowClass, *super;

    /* need to look up the index of wxWindow class? */
    if (wTheWxWindowClassIndex == 0) {
        /* find the wxWindow class */
        wxWindowClass = wSymbolFind( "wxwindow", wTheGlobalScope );

        /* not found? */
        if (wxWindowClass == NULL) {
            /* this is bad */
            wErrorThrow( W_ERROR_INTERNAL, "Can't find wxWindow class" );
        }

        /* save the index */
        wTheWxWindowClassIndex = wxWindowClass->index;
    }

    /* set as the super */
    super = klass;

    /* walk up inheritance chain */
    while (1) {
        /* wxWindow? */
        if (super->index == wTheWxWindowClassIndex) {
            return W_TRUE;
        }

        /* end of inheritance? */
        if (super->inherits == 0) {
            break;
        }

        /* move up */
        super = wSymbolLookup( super->inherits );
    }

#endif
    /* doesn't inherit from wxWindow */
    return W_FALSE;
}


/* deref an object; calls finalize method when destroyed */
void wObjectDeref( wVariant *src )
{
    int index;
	wObject *o;
    wSymbol *method;

	/* get the object */
	o = src->value.object;
    wMemTest( o, "wObjectDeref:o" );

    /* is this a reference counted object? */
    if (o->tmpFlag) {
// wConsolePrintf("%s is a temp object\n", o->klass->name );
        /* dereference */
        o->refCount--;
// wConsolePrintf("refCount of %s is %d\n", o->klass->name, o->refCount );
        /* no more references? */
        if (o->refCount == 0) {
#ifdef __WXWIN__
            /* don't run finalize if inherits from wxWindow */
            if (!wObjectInheritsWxWindow(o->klass)) {
#else
            /* always run finalize */
            if (W_TRUE) {
#endif
// wConsolePrintf("finalizing the object %s\n", o->klass->name );
                /* lookup the "finalize" method */
                method =  wSymbolFindMethodChar( o->klass, "finalize" );
                if (method != NULL) {
                    /* call the finalize routine */
                    wCallRoutine( method, 0, 0, o, NULL );
                }
#ifdef __WXWIN__
            } else {
                /* need to disconnect all events */
                // void wDisconnectAll( int id, int useId )
#endif
            }
// wConsolePrintf("freeing the object %s\n", o->klass->name );
            /* free the object */
            wObjectFree( o );
        }
} else {
    //wConsolePrintf("%s is not temporary, no dereferencing\n", o->klass->name);
    }

}

/* free an object, ignoring reference count */
void wObjectFree( wObject *o )
{
    int i;
    wSymbol *s;

    wMemTest( o, "wObjectFree:o" );

    /* display destruction for debugging */
    if (wTheDebugOnFlag) {
        //wConsoleDebugf("destroying the %s at %p\n", o->klass->name, o );
    }

    /* are there children? */
    if (o->propCount) {

        /* free each child */
        for ( i = 0; i < o->propCount; i++ ) {
            /* dereference each item */
            wVariantDeref( &(o->prop[i]) );
        }
    }
    wFree( o );
}


void wObjectCopy( wVariant *dst, wVariant *src )
{
	wMemTest( src->value.object, "wVariantCopyData:src->value.object" );
    dst->value.object = src->value.object;
}


void wObjectClone( wVariant *dst, wVariant *src )
{
    int i;
    wObject *srcObject, *dstObject;
    wSymbol *s;
    
    /* get the object */
    srcObject = src->value.object;
        
    /* can't clone external objects yet */
    if (srcObject->propCount == 0) {
        /* throw an exception */
        wErrorThrow( W_ERROR_NOSUCH, "Can't clone external class %s yet", 
            srcObject->klass->name );
    }
    
    /* deref the destination */
    wVariantDeref( dst );
    
    /* set the type */
    dst->dataType = W_TYPE_OBJECT;
    
    /* create a new object of the same type */
    dstObject = wObjectNew( srcObject->klass->index, W_FALSE );
    dst->value.object = dstObject;

    /* clone the properties */    
    for ( i = 0; i < srcObject->propCount; i++ ) {
        wVariantClone( &(dstObject->prop[i]), &(srcObject->prop[i]) );
    }
}


char *wObjectToChar( wVariant *src, int useQuotes, int limit )
{
	int i, count;
    char *buffer, *tmpBuffer;
	wGrow *list;
    wObject *object;

    /* get the object */
    object = src->value.object;

	/* no quotes? */
	if (!useQuotes) {
        /* just return the name of the object's class */
        return wCharCopy( object->klass->name );
	}

	/* create a buffer to hold the result */
    buffer = wCharMalloc( W_INBUFFER_MAX );

	/* name, class name and reference count */
    buffer = wCharConcat( buffer, "[" );
    buffer = wCharConcat( buffer, object->klass->name );
    buffer = wCharConcat( buffer, " @" );
    if (object->ptr == NULL) {
        /* object pointer address */
        buffer = wCharConcatPtr( buffer, object );
    } else {
        /* raw pointer address */
        buffer = wCharConcatPtr( buffer, object->ptr );
    }

	/* iterate through the properties */
    list = object->klass->children;
    if (list != NULL) {
        count = list->count;
        // FIXME: what if there are no properties?
        for ( i = 1; i <= count; i++ ) {
            /* leading space */
            buffer = wCharConcat( buffer, " " );

            /* name of property */              
            buffer = wCharConcat( buffer,
                wSymbolLookup( wGrowGet( list, i ) )->name );
    
            /* add colon seperator */
            buffer = wCharConcat( buffer, ":" );
    
            /* value of property */
            tmpBuffer = wVariantToChar( &(object->prop[i-1]), W_TRUE, 0);
            buffer = wCharConcat( buffer, tmpBuffer );
            wFree( tmpBuffer );
    
            /* add comma? */
            if (i < count) {
                buffer = wCharConcat( buffer, "," );
            }
        }
    }

	/* closing paren */
    buffer = wCharConcat( buffer, "]" );

	return buffer;
}

int wObjectEqual( wVariant *v1, wVariant *v2 )
{
    /* builtin class? */
	return (v1->value.object == v2->value.object );
}
