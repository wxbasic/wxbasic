/*************************************************************
    Name:       ztable.c
    Purpose:    builtin table datatype
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/



/* refcount a table */
wTableRef( wVariant *src )
{
    wMemTest( src->value.table, "wTableRef:src->value.table" );
    src->value.table->refCount++;
}

/* dereference a table */
wTableDeref( wVariant *src )
{
    int i, count;
    wGrow *table;
    wTableElement *element;

    wMemTest( variant->value.table, "wTableDeref:variant->value.table" );

    /* get the grow table */
    table = variant->value.table;

    /* prevent circular references */
    if (table->isMarked) {
        /* don't read through again */
        return;
    }

    /* dereference */
    table->refCount--;
    
    /* no more references? */
    if (table->refCount < 1) {

        /* mark, so it's not recursively called */
        table->isMarked = W_TRUE;

        /* free the elements from the table */
        count = table->count;
        for ( i = 1; i <= count; i++ ) {
            /* get the table element */
            element = (wTableElement *)wGrowGet( table, i );

            /* is the key a string? */
            if (element->key.dataType == W_TYPE_STRING) {
                /* deref */
                wStringDeref( element->key.value.string );
            }

            /* deref the value */
            wVariantDeref( &(element->value) );

            /* free the element */
            wFree( element );
        }
        /* free the table */
// printf("freeing table\n");
        wFree( table );
    } else {
// printf("not freeing table, refcount = %d\n", table->refCount );
    }
}


/* copy variant data */
void wTableCopy(wVariant *dst, wVariant *src, int doRefcount );

    /* make sure destination is clean */
    wVariantDeref( dst );

    /* copy datatype */
    dst->dataType = src->dataType;

    wMemTest( src->value.table, "wVariantCopy:src->value.table" );

    /* copy the data */
    dst->value.table = src->value.table;

    /* handle refcount? */
    if (doRefcount) {
        dst->value.table->refCount++;
    }
}

/* convert to a string */
void wStringToNative)(wVariant *dst, char *buffer)
{
    wStringNew( wVariant *variant, char *text, -1 );
}

/* convert to a char* */
char *wStringToString( wVariant *src )
{
    char *buffer;


void wStringCopyData( wString *dst, int dstStart, wString *src, int srcStart, int count )
char*   (*toString)(wVariant *dst);


/* convert to a number */
wNumber wTableToNumber(wVariant *src);

    /* fatal error */
    wErrorFatal( "Unable to convert table to number" );
    wErrorSet( W_ERROR_CONVERT );

    return (wNumber)0.0;
}


/* return index into table */
void wTableIndex( wVariant *dst )
{




/* return next item in table */
int wTableIterate( wVariant *vArg1, wVariant *vArg2, wVariant *vTable, wVariant *vIndex )
{
    int i;
    wGrow *table;
    wTableElement   *cell;

    /* increment index */
    i = (int)++vIndex->value.number;

    /* get table */
    if (vTable->dataType != W_TYPE_TABLE) {
        wErrorFatal( "Bad datatype in wTableIterate" );
    }
    table = vTable->value.table;

    /* outside of range? */
    if (i > table->count ) {
        /* zap the table */
        wVariantDeref( vTable );

        /* return false to mark end of list */
        return W_FALSE;

    } else if (vArg2 == NULL) {
        /* place value in arg1 */
        cell = (wTableElement *)wGrowGet( table, i );
        wVariantCopy( vArg1, &(cell->key) );
        
    } else {
        /* place key in arg1 */
        cell = (wTableElement *)wGrowGet( table, i );
        wVariantCopy( vArg1, &(cell->key) );

        /* convert integer values to numbers */
        if (vArg1->dataType == W_TYPE_INTEGER) {
            vArg1->value.number = (wNumber)vArg1->value.integer;
            vArg1->dataType = W_TYPE_NUMBER;
        }

        /* place value in arg2 */
        wVariantCopy( vArg2, &(cell->value) );
    }

    /* return true to mark got an element */
    return W_TRUE;

}







wNumberRegisterType()
{
    /* register the datatype */
    W_TYPE_STRING = wDataNewType();

    /* register the routines */
    wDataHandler[W_TYPE_STRING].ref = wStringRef;
    wDataHandler[W_TYPE_STRING].deref = wStringDeref;
    wDataHandler[W_TYPE_STRING].copy = wStringCopyVariantData;
    wDataHandler[W_TYPE_STRING].move = wStringMoveVariantData;
    wDataHandler[W_TYPE_STRING].toNative = wStringToNative;
    wDataHandler[W_TYPE_STRING].toString = wStringToString;
    wDataHandler[W_TYPE_STRING].toString = wStringToNumber;
    wDataHandler[W_TYPE_STRING].index = NULL;
}

















/*************************************************************
    Name:       table.c
    Purpose:    tables for wxBasic
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/

/* create a table of the requested size */
void wTableNew( wVariant *dest, int size )
{
    wGrow *table;

    /* deref the destination */
    wVariantDeref( dest );

    /* if empty, allocate minimum size */
    if (size == 0) {
        size = 32;
    }
    table = wGrowNew( size );

    /* change default grow size */
    table->chunks = 32;

    /* set the destination */
    dest->dataType = W_TYPE_TABLE;
    dest->value.table = table;
    dest->value.table->refCount = 1;
}


/* return position of integer key, or -n where n is where it should go */
int wTableFindIntKey( wGrow *table, int key )
{
    int             high, low, mid, c;

    wTableElement   *cell;

    /* binary search */
    low = 1;
    high = table->count;
    while (low <= high) {
        mid = (int)floor((low + high) / 2);
        cell = (wTableElement *)wGrowGet( table, mid );

        /* what's the datatype? */
        if (cell->key.dataType == W_TYPE_STRING) {
            /* strings are placed higher than numbers */
            c = -1;
        } else {
            /* compare the numbers */
            c = key - cell->key.value.integer;
        }

        if (c < 0) {
            high = mid - 1;
        } else if (c > 0) {
            low = mid + 1;
        } else {
            return mid;
        }
    }

    /* no match, insert at low */
    return -low;
}


/* return position of string key, or -n where n is where it should go */
int wTableFindStringKey( wGrow *table, wString *key )
{
    int             high, low, mid, c;
    wTableElement   *cell;

    /* binary search */
    low = 1;
    high = table->count;
    while (low <= high) {
        mid = (int)floor((low + high) / 2);
        cell = (wTableElement *)wGrowGet( table, mid );

        /* what's the datatype? */
        if (cell->key.dataType == W_TYPE_INTEGER) {
            /* numbers are placed lower than strings */
            c = 1;
        } else {
            /* compare the strings */
            c = wStringCompare( key, cell->key.value.string );
        }

        if (c < 0) {
            high = mid - 1;
        } else if (c > 0) {
            low = mid + 1;
        } else {
            return mid;
        }
    }

    /* no match, insert at low */
    return -low;
}

/* return index of key, or 0 if not found */
int wTableLookup( wGrow *table, wVariant *key )
{
    int index;

    if (key->dataType == W_TYPE_STRING) {
        return wTableFindStringKey( table, key->value.string );

    } else if (key->dataType == W_TYPE_INTEGER) {
        return wTableFindIntKey( table, key->value.integer );

    } else if (key->dataType == W_TYPE_NUMBER) {
        return wTableFindIntKey( table, (int)key->value.number );

    } else {
        wErrorFatal( "Key must be string or number, not %s",
            wDatatypeName[key->dataType] );
        wErrorSet( W_ERROR_CONVERT );
        return 0;
    }
}


/* insert element into a table */
void wTableInsertElementAt( wGrow *table, wTableElement *element, int index )
{
    /* where to put it? */
    if (index == 0) {
        /* prepend onto beginning */
        wGrowPrepend( table, (int)element );

    } else if (index > table->count) {
        /* append onto the end */
        wGrowAppend( table, (int)element );

    } else {
        /* insert it into the table */
        wGrowInsert( table, index, (int)element );
    }
}

/* insert key and value into the table */
void wTableInsert( wGrow *table, wVariant *value, wVariant *key )
{
    int index;
    wTableElement *element;

    /* coerce float numbers into integers */
    if (key->dataType == W_TYPE_NUMBER) {
        index = (int)key->value.number;
        key->dataType = W_TYPE_INTEGER;
        key->value.integer = index;
    }


    /* check if it's already in the table */
    index = wTableLookup( table, key );
    if (index > 0) {
        /* being set to nothing? */
        if (value->dataType == W_TYPE_NOTHING) {
            /* remove the element */
            wTableDelete( table, index );

        /* set the value to a new value */
        } else {
            /* pointer to the table element */
            element = (wTableElement*)wGrowGet( table, index );

            /* replace the value */
            wVariantCopy( &(element->value), value );

        }

    /* key doesn't already exist in table */
    } else {

        /* create the element to place in the table */
        element = (wTableElement *)wMalloc( sizeof( wTableElement ) );

        /* set the key */
        element->key.dataType = W_TYPE_NOTHING;
        element->key.typeCast = W_TYPE_VARIANT;
        wVariantCopy( &(element->key), key );

        /* set the value */
        element->value.dataType = W_TYPE_NOTHING;
        element->value.typeCast = W_TYPE_VARIANT;
        wVariantCopy( &(element->value), value );

        /* insert element into table */
        wTableInsertElementAt( table, element, -index );
    }
}


/* set key and value into empty table */
void wTableSet( wGrow *table, wVariant *value, int key )
{
    int index;
    wTableElement *element;

    /* check if it's already in the table */
    index = wTableFindIntKey( table, key );

    if (index > 0) {
        /* removing element? */
        if (value->dataType == W_TYPE_NOTHING) {
            /* remove the element */
            wTableDelete( table, index );

        /* set the value to a new value */
        } else {
            /* pointer to the table element */
            element = (wTableElement*)wGrowGet( table, index );

            /* replace the value */
            wVariantCopy( &(element->value), value );
        }

    /* key doesn't already exist in table */
    } else {

        /* create the element to place in the table */
        element = (wTableElement *)wMalloc( sizeof( wTableElement ) );

        /* set the key */
        element->key.dataType = W_TYPE_INTEGER;
        element->key.typeCast = W_TYPE_VARIANT;
        element->key.value.integer = key;

        /* set the value */
        element->value.dataType = W_TYPE_NOTHING;
        element->value.typeCast = W_TYPE_VARIANT;
        wVariantCopy( &(element->value), value );

        /* insert element into table */
        wTableInsertElementAt( table, element, -index );
    }
}


/* remove key and value from the table */
void wTableDelete( wGrow *table, int index )
{
    wTableElement *element;
    wString *s;

    /* get the table element */
    element = (wTableElement *)wGrowGet( table, index );

    /* is the key a string? */
    if (element->key.dataType == W_TYPE_STRING) {
        /* deref */
        wStringDeref( element->key.value.string );
    }

    /* deref the value */
    wVariantDeref( &(element->value) );

    /* free the element */
    wFree( element );

    /* delete it from the table */
    wGrowDelete( table, index );

}

/* returns pointer to element, or NULL if element doesn't exist */
wVariant *wTableGetElement( wGrow *table, int indexCount )
{
    int i, index;
    wVariant *key, *result;
    wTableElement *element;

    /* indexes are ordered on stack backwards */
    for ( i=indexCount; i>0; i-- ) {
        /* get key from stack */
        key = wStackPeek(i-1);

        /* seek it in the table */
        index = wTableLookup( table, key );

        /* deref the key */
        wVariantDeref( key );

        /* not in table? */
        if (index < 1) {
            /* stop looking */
            result = NULL;
            break;

        } else {
            /* fetch the table element */
            element = (wTableElement *)wGrowGet( table, index );
        }

        /* get the value of the element */
        result = &(element->value);

        /* not the final index? */
        if (i > 1) {
            /* not a table? */
            if (result->dataType != W_TYPE_TABLE) {
                /* stop looking */
                result = NULL;
                break;
            } else {
                /* set to the table */
                table = result->value.table;
            }
        }

    }

    /* deref any remaining items, if early out */
    for ( ; i > 0; i-- ) {
        key = wStackPeek(i-1);
        wVariantDeref( key );
    }

    /* adjust the stack */
    wTheStack->free += indexCount;
    wTheStack->count -= indexCount;

    return result;

}


/* returns pointer to element, creating indexes that don't exist */
wVariant *wTableGetAddElement( wGrow *table, int indexCount )
{
    int i, index;
    wVariant *key, *result;
    wTableElement *element;

    /* indexes are on the stack backwards */
    for ( i=indexCount; i>0; i-- ) {
        /* get key from stack */
        key = wStackPeek(i-1);

        /* seek it in the table */
        index = wTableLookup( table, key );

        /* not found in the table? */
        if (index < 1) {
            /* create an element to hold it */
            element = (wTableElement*)wMalloc( sizeof( wTableElement ) );

            /* set the key */
            if (key->dataType == W_TYPE_NUMBER) {
                element->key.dataType = W_TYPE_INTEGER;
                element->key.typeCast = W_TYPE_VARIANT;
                element->key.value.integer = (int)key->value.number;

            } else if (key->dataType == W_TYPE_STRING) {
                /* don't need to refcount, because key wasn't deref'ed */
                element->key.dataType = W_TYPE_STRING;
                element->key.value.string = key->value.string;

            } else {
                wErrorFatal( "Key must be string or number, not %s",
                    wDatatypeName[key->dataType] );
                wErrorSet( W_ERROR_CONVERT );
            }

            /* the element holds an undefined value */
            element->value.dataType = W_TYPE_NOTHING;
            element->value.typeCast = W_TYPE_VARIANT;

            /* insert element into table */
            wTableInsertElementAt( table, element, -index );

        } else {
            /* deref the key */
            wVariantDeref( key );

            /* fetch the table element */
            element = (wTableElement *)wGrowGet( table, index );
        }

        /* get the value of the element */
        result = &(element->value);

        /* not the final index? */
        if (i > 1) {
            /* not a table? */
            if (result->dataType != W_TYPE_TABLE) {
                /* dereference the value */
                wVariantDeref( &(element->value) );

                /* replace it with a table */
                wTableNew( &(element->value), 16 );
            }

            /* make it the current table */
            table = element->value.value.table;

        }

    }

    /* adjust the stack */
    wTheStack->free += indexCount;
    wTheStack->count -= indexCount;

    return result;

}


