/*************************************************************
    Name:       method.c
    Purpose:    methods for non-class objects
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/

void wMethod( wVariant *v, int stringIndex, int argCount, int returnCount )
{
    int returns, i;
    char *method;

    wMemTest( v, "wMethod:v" );

    /* get the method name */
    method = wLiteralGetChar( stringIndex );

    /* find the datatype */
    switch( v->dataType ) {
    case W_TYPE_LIST:
        wMemTest( v->value.list, "wMethod:v->value.list" );
        v->value.list->refCount--;
        returns = wMethodList( v, method, argCount );
        break;

    case W_TYPE_TABLE:
        wMemTest( v->value.table, "wMethod:v->value.table" );
        v->value.table->refCount--;
        returns = wMethodTable( v, method, argCount );
        break;

    case W_TYPE_STRING:
        wMemTest( v->value.string, "wMethod:v->value.table" );
        v->value.string->refCount--;
        returns = wMethodString( v, method, argCount );
        break;

    default:
        wErrorFatal( "Datatype %s does not support methods",
            wDatatypeName[v->dataType] );
        wErrorSet( W_ERROR_CONVERT );
    }

    /* need to fix the return values? */
    if (returns < returnCount) {
        /* push undefined on the stack */
        for ( i = returns; i <= returnCount; i++ ) {
            wStackPushNothing();
        }

    } else if (returns > returnCount) {
        /* drop items from stack */
        for ( i = returnCount; i <= returns; i++ ) {
            /* pop and dereference */
            wVariantDeref( wStackPop() );
        }
            
    }
}

/* ensure the arg count matches the expected number */
int wMethodCheckArgs( char *name, int expect, int actual )
{
    if (expect != actual) {
        wErrorFatal( "The method %s expects %d arguments, not %d",
            name, expect, actual );
        wErrorSet( W_ERROR_ARGS );
        return W_FALSE;
    }
    return W_TRUE;
}


/* list methods */
int wMethodList( wVariant *list, char *name, int argCount )
{
    int index;
    wVariant *item, *element;

    /* append? */
    if (strcmp( name, "append" ) == 0 ) {

        /* check arg count */
        if (!wMethodCheckArgs( "List:append", 1, argCount )) {
            return 0;
        }

        /* get the item to append */
        item = wStackPop();
    
        /* create an element for the list */
        element = (wVariant *)wMalloc( sizeof( wVariant ) );
        element->dataType = W_TYPE_NOTHING;
    
        /* move item into the element */
        wVariantMove( element, item );
    
        /* append the element into the list */
        wGrowAppend( list->value.list, (int)element );

        /* return count */
        return 0;

    } else if (strcmp( name, "count" ) == 0 ) {
        /* check arg count */
        if (!wMethodCheckArgs( "List:count", 0, argCount )) {
            return 0;
        }

        /* get the count */
        wStackPushNumber( list->value.list->count );
        return 1;
    
    } else if (strcmp( name, "insert" ) == 0 ) {

        /* check arg count */
        if (!wMethodCheckArgs( "List:insert", 1, argCount )) {
            return 0;
        }

        /* get the item and collection to insert it into */
        index = (int)wStackPopNumber();
        item = wStackPop();

        /* create an element for the list */
        element = (wVariant *)wMalloc( sizeof( wVariant ) );
        element->dataType = W_TYPE_NOTHING;

        /* move item into the element */
        wVariantMove( element, item );

        /* insert into the list */
        wGrowInsert( list->value.list, index, (int)element );

        /* return count */
        return 0;

    } else if (strcmp( name, "prepend" ) == 0 ) {
        /* check the arg count */
        if (!wMethodCheckArgs( "List:prepend", 1, argCount )) {
            return 0;
        }

        /* get the item to prepend */
        item = wStackPop();

        /* create an element for the list */
        element = (wVariant *)wMalloc( sizeof( wVariant ) );
        element->dataType = W_TYPE_NOTHING;

        /* move item into the element */
        wVariantMove( element, item );

        /* prepend the element into the list */
        wGrowPrepend( list->value.list, (int)element );

        /* return count */
        return 0;

    } else {
        wErrorFatal( "Method List:%s not found", name );
        wErrorSet( W_ERROR_NOSUCH );
        return 0;
    }
}

/* table methods */
int wMethodTable( wVariant *table, char *name, int argCount )
{
    int index;

    if (strcmp( name, "count" ) == 0 ) {

        /* check arg count */
        if (!wMethodCheckArgs( "count", 0, argCount )) {
            return 0;
        }

        wStackPushNumber( table->value.table->count );
        return 1;

    } else {
        wErrorFatal( "Method Table:%s not found", name );
        wErrorSet( W_ERROR_NOSUCH );
        return 0;
    }
}

/* string methods */
int wMethodString( wVariant *string, char *name, int argCount )
{
    int index;
    wVariant *item;

    /* append? */
    if (strcmp( name, "append" ) == 0 ) {

        /* check arg count */
        if (!wMethodCheckArgs( "String:append", 1, argCount )) {
            return 0;
        }

        /* get the item to append */
        item = wStackPop();

        /* concat them */
        wStringConcat( string, item );

        /* deref the item */
        wVariantDeref( item );

        /* return count */
        return 0;

    } else if (strcmp( name, "count" ) == 0 ) {
        /* check arg count */
        if (!wMethodCheckArgs( "String:count", 0, argCount )) {
            return 0;
        }

        /* get the count */
        wStackPushNumber( string->value.string->length );
        return 1;

    /* FIXME : should add an INSERT at some point */

    } else if (strcmp( name, "prepend" ) == 0 ) {
        /* check arg count */
        if (!wMethodCheckArgs( "String:prepend", 1, argCount )) {
            return 0;
        }

        /* get the item to append */
        item = wStackPop();

        /* concat them */
        wStringConcat( item, string );

        /* move the item */
        wVariantMove( string, item );

        /* return count */
        return 0;

    } else {
        wErrorFatal( "Method String:%s not found", name );
        wErrorSet( W_ERROR_NOSUCH );
        return 0;
    }
}
