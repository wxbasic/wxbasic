/*
    Name:       class.c
    Purpose:    wrappers to interface C++ classes to wxBasic
    Author:     David Cuny
    Copyright:  (c) 2002 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*/


/* compute hash value for string */
unsigned int wHashVal( char *str )
{
    unsigned int    h;
    unsigned char   *p;

    h = 0;
    for (p= (unsigned char *) str; *p != '\0'; p++ ) {
        h = W_HASH_MULTIPLIER * h + *p;
    }
    return h % W_HASH_MAX_HASH;
}


/* return the index to the class; -1 on failure */
int wFindClass( char *name )
{
    int             i, nameHash;
    wWrappedClass   *theClass;

    nameHash = wHashVal( name );
    for ( i = wNextClass-1; i >= 0; i-- ) {
        theClass = wClassList[i];
    if (strcmp( theClass->name, name ) == 0) {
            return i;
        }
    }
    return -1;
}

/* add a class, return the index */
int wAddClass( int superIndex, char *name ) 
{
    wWrappedClass   *theClass;
    wSymbol         *s;

    /* array size is static */
    if (wNextClass > W_MAX_CLASSES){
        wFatal( W_RUNTIME, "wAddClass: reached class limit of %d",
            W_MAX_CLASSES);
    }
        
    /* create class */
    theClass = (wWrappedClass *)wMalloc( sizeof( wWrappedClass ) );
    theClass->name          = wCopyString( name );
    theClass->super         = superIndex;
    theClass->lastMethod    = NULL;
    wClassList[wNextClass]  = theClass;

    #ifdef __WXBASIC__
        /* add to symbol table */
        s = wAddSymbol( name, NULL, W_SYM_CLASS, W_TRUE );
        s->klass = wNextClass;
    #endif

    return wNextClass++;
}

/* add a method to a class */
void wAddMethod( int classIndex, char *name, void (*routine)(void),
                    int minArgs, int maxArgs )
{
    wWrappedMethod       *theMethod;

    theMethod = (wWrappedMethod *)wMalloc( sizeof( wWrappedMethod ) );

    theMethod->name     = wCopyString( name );
    theMethod->hash     = wHashVal( name );
    theMethod->routine  = routine;
    theMethod->minArgs  = minArgs;
    theMethod->maxArgs  = maxArgs;

    theMethod->prior = wClassList[classIndex]->lastMethod;
    wClassList[classIndex]->lastMethod = theMethod;
}

/* search class for method */
wWrappedMethod *wFindClassMethod( int classIndex, char *name, int hash )
{        
    wWrappedMethod       *theMethod;
    
    for ( theMethod = wClassList[classIndex]->lastMethod;
          theMethod != NULL;
          theMethod = theMethod->prior ) {
        if ( hash == theMethod->hash && strcmp( name, theMethod->name ) == 0 ) {
                return theMethod;
        }
    }
    return NULL;
}

/* search inheritance tree for method, return NULL on failure */
wWrappedMethod *wFindMethod( int classIndex, char *name )
{
    int hash;
    wWrappedMethod       *theMethod;

    /* name hash for speed */
    hash = wHashVal( name );

    /* search for match */
    for ( ; classIndex != 0; classIndex = wClassList[classIndex]->super ) {
    theMethod = wFindClassMethod( classIndex, name, hash );
        if (theMethod != NULL) {
            return theMethod;
        }
    }
    return NULL;
}


/* get pointer */
int wGetObject( wNumber objectIndex )
{
    int i;

    /* null is a special case */
    if (objectIndex == 0.0) {
        return 0;
    }

    /* convert to integer */
    i = (int)objectIndex;
    if (i != objectIndex) {
        wFatal( W_RUNTIME, "wGetObject: %Lf is not a valid handle (not integer)", objectIndex );

    } else if (objectIndex < 0 || objectIndex >= wNextObject) {
        wFatal( W_RUNTIME, "wGetObject: %d is not a valid handle (out of range)", i );

    } else if (wObjectList[i] == NULL) {
        wFatal( W_RUNTIME, "wGetObject: %d is NULL (possibly destroyed)", i );
    }

    return wObjectList[i]->pointer;
}

/* pop object index off stack, and return pointer */
int wPopPointer( int matchClassIndex )
{
    /* at some point, it should verify the class */
    int     handle, objectIndex, classIndex, i;

    /* return the pointer; check range */
    objectIndex = (int)wPopNumber();
    if (objectIndex == 0 ){
        /* null */
        return 0;
    }
    handle = wGetObject( objectIndex );

    /* correct class? */
    classIndex = wObjectList[objectIndex]->classIndex;
    for( i = classIndex; i != 0; i = wClassList[i]->super ) {
        if (i == matchClassIndex) {
            break;
        }
    }
    if (i == 0) {
        wFatal( W_RUNTIME, "wPopPointer: expected %s, not %s",
            wClassList[matchClassIndex]->name, wClassList[classIndex]->name );
    }
    return handle;
}


/* determine class of method and run it */
void wResolveMethod( int objectIndex, char *name )
{
    int             classIndex;

    /* get pointer, check range */
    wMe = wGetObject( objectIndex );

    /* null? */
    if (objectIndex == 0) {
        wFatal( W_RUNTIME, "Can't resolve method null.%s", name );
    }

    /* get the class */
    classIndex = wObjectList[objectIndex]->classIndex;

    /* run it */
    wRunMethod( classIndex, name );
}


/* find and execute a method */
void wRunMethod( int classIndex, char *name )
{
    wWrappedMethod  *method;

    /* find the method */
    method = wFindMethod( classIndex, name );
    if (method == NULL) {
        wFatal( W_RUNTIME, "Can't find method %s.%s", wClassList[classIndex]->name, name );
    }

    /* check args */
    if (wArgCount < method->minArgs || wArgCount > method->maxArgs ) {
        if (method->minArgs == method->maxArgs) {
            wFatal( W_RUNTIME, "Method %s.%s expected %d args, not %d args",
                wClassList[classIndex]->name, method->name,
                method->minArgs, wArgCount );

        } else {
            wFatal( W_RUNTIME, "Method %s.%s expected %d to %d args, not %d args",
                wClassList[classIndex]->name, method->name,
                method->minArgs, method->maxArgs, wArgCount );
        }
    }

    /* execute, leave result on stack */
    (*method->routine)();
}


/* add an object of a given class */
wNumber wAddObject( int classIndex, int pointer )
{
    int             i, objectIndex;
    wWrappedObject  *theObject;

    /* note objects start at 1, not 0 */
    objectIndex = 0;

    /* search for an empty slot to reuse */
    for ( i = 1; i < wNextObject; i++ ) {
        if (wObjectList[i] == NULL) {
            objectIndex = i;
                break;
        }
    }
    /* no old slots free? */
    if (objectIndex == 0) {
        if (wNextObject == W_MAX_OBJECTS) {
            wFatal( W_RUNTIME, "wAddObject: reached object limit of %d",
                W_MAX_OBJECTS);
        }
        objectIndex = wNextObject++;
    }

    theObject = (wWrappedObject *)wMalloc( sizeof( wWrappedObject ) );
    theObject->pointer      = pointer;
    theObject->classIndex   = classIndex;
    theObject->id           = 0;

    wObjectList[objectIndex] = theObject;
    return (wNumber)objectIndex;
}

/* remove object from list, don't run destructor */
void wRemoveObject( int objectIndex )
{
    /* get pointer, check range */
    wMe = wGetObject( objectIndex );

    /* free */
    wFree( wObjectList[objectIndex] );
    wObjectList[objectIndex] = NULL;
}


/* run destructor */
void wRunDestructor( int objectIndex, int typeOf )
{
    wWrappedObject   *object;
    wWrappedMethod   *method;

    /* get pointer, check range */
    wMe = wGetObject( objectIndex );

    object = wObjectList[objectIndex];
    switch (typeOf) {
    case W_OP_DELETE:
        method = wFindMethod( object->classIndex, "del" );
        if (method == NULL) {
            wFatal( W_RUNTIME, "wRunDestructor: can't find %s.delete method",
                wClassList[object->classIndex]->name );
        }
        break;
    case W_OP_DESTROY:
        method = wFindMethod( object->classIndex, "dtor" );
        if (method == NULL) {
            wFatal( W_RUNTIME, "wRunDestructor: can't find %s.destroy method",
                wClassList[object->classIndex]->name );
        }
        break;
    default:
        wFatal( W_RUNTIME, "wRunDestructor: bad opcode of %d\n", typeOf );
    }

    /* execute */
    (*method->routine)();

    /* free */
    wFree( object );
    wObjectList[objectIndex] = NULL;

}

/* returns true if safe to create on stack */
int wClassSafeOnStack( int classIndex )
{
#ifdef __WXWIN__
    /* not zero (marker) */
    if (classIndex) {
        while( classIndex != 0) {
            /* can't inherit from wxWindow */
            if (classIndex == _wxWindow ) {
                return 0;
            }
            classIndex = wClassList[classIndex]->super;
        }
    }
#endif
    return 1;
}


/* add an object to the create stack */
void wPushCreateStack( int i )
{
    wCreateTos++;
    if (wCreateTos >= W_MAX_CREATE_STACK ) {
        wFatal( W_RUNTIME, "wPushCreateStack: limit of %d exceeded",
            W_MAX_CREATE_STACK );
    }

    wCreateStack[wCreateTos] = i;
}

/* pop (and destroy) objects on create stack */
void wClearCreateStack()
{
    /* destroy objects on stack */
    while (wCreateStack[wCreateTos]) {
        wRunDestructor( wCreateStack[wCreateTos], W_OP_DELETE );
        wCreateTos--;
    }
    wCreateTos--;
}
