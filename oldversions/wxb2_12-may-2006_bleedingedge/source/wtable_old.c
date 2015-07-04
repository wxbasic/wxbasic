/*************************************************************
    Name:       wtable.c
    Purpose:    W_TYPE_TABLE datatype: table datatype
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/

void wTableRegisterMethods()
{
    /* register the routines */
    wTheHandler[W_TYPE_TABLE]->isNumeric       = W_FALSE;
    wTheHandler[W_TYPE_TABLE]->ref             = wTableRef;
    wTheHandler[W_TYPE_TABLE]->deref           = wTableDeref;
    wTheHandler[W_TYPE_TABLE]->copy            = wTableCopy;
    wTheHandler[W_TYPE_TABLE]->clone           = wTableClone;
    wTheHandler[W_TYPE_TABLE]->fromNumber      = NULL;
    wTheHandler[W_TYPE_TABLE]->toNumber        = NULL;
    wTheHandler[W_TYPE_TABLE]->fromChar        = NULL;
    wTheHandler[W_TYPE_TABLE]->toChar          = wTableToChar;
    wTheHandler[W_TYPE_TABLE]->compare         = NULL;
    wTheHandler[W_TYPE_TABLE]->equal           = NULL;
    wTheHandler[W_TYPE_TABLE]->isTrue          = NULL;
    wTheHandler[W_TYPE_TABLE]->count           = wTableCount;
    wTheHandler[W_TYPE_TABLE]->index           = wTableIndex;
    wTheHandler[W_TYPE_TABLE]->insert          = wTableInsert;
    wTheHandler[W_TYPE_TABLE]->find            = wTableFind;
    wTheHandler[W_TYPE_TABLE]->remove          = wTableRemove;
    wTheHandler[W_TYPE_TABLE]->append          = NULL;
    wTheHandler[W_TYPE_TABLE]->prepend         = NULL;
    wTheHandler[W_TYPE_TABLE]->slice           = NULL;
    wTheHandler[W_TYPE_TABLE]->iterate         = wTableIterate;
    wTheHandler[W_TYPE_TABLE]->method          = wTableMethod;
}


void wTableRef( wVariant *src )
{
	wMemTest( src->value.table, "wTableRef:src->value.table" );
	src->value.table->refCount++;
}

/* dereference table */
void wTableDeref( wVariant *vSrc )
{
    int i, count;
	wGrow *table;
    wTableElement *element;

    wMemTest( vSrc->value.table, "wTableDeref:vSrc->value.table" );

    /* get the table */
    table = vSrc->value.table;

    /* already marked? */
    if (table->isMarked) {
        /* don't recurse */
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

            /* deref the key and value */
            wVariantDeref( &(element->key) );            
            wVariantDeref( &(element->value) );

            /* free the element */
            wFree( element );
        }
        /* free the table */
// wConsoleDebug("freeing table\n");
        wFree( table );
    } else {
// wConsoleDebug("not freeing table, refcount = %d\n", table->refCount );
    }
}


/* copy table data */
void wTableCopy( wVariant *dst, wVariant *src )
{
	wMemTest( src->value.table, "wTableCopy:src->value.table" );
	dst->value.table = src->value.table;
}

void wTableClone( wVariant *dst, wVariant *src )
{
    int count, i;
    wGrow *dstTable, *srcTable;
    wTableElement *dstElement, *srcElement;
    wVariant *item;
    
    /* get the source table */
    srcTable = src->value.table;
    
    /* create a table large enough to hold it */
    dstTable = wGrowNew( srcTable->count + srcTable->free );
    dstTable->count = srcTable->count;
    dstTable->free = srcTable->free;

    /* set refcount */
    dstTable->refCount = 1;
    
    /* copy the table elements (rest of table is NULL) */
    count = srcTable->count;
    for ( i = 1; i <= count; i++ ) {
        /* get the table element */
        srcElement = (wTableElement *)wGrowGet( srcTable, i );

        /* allocate space for a copy */
        dstElement = (wTableElement *)wMalloc( sizeof( wTableElement ) );
            
        /* initialize the key to nothing and copy */
        /* don't need to clone - can't be a collection */
        item = &(dstElement->key);
        item->dataType = W_TYPE_NOTHING;
        item->typeCast = W_TYPE_VARIANT;
        wVariantCopy( item, &(srcElement->key) );

        /* initialize the value to nothing and copy */
        item = &(dstElement->value);
        item->dataType = W_TYPE_NOTHING;
        item->typeCast = W_TYPE_VARIANT;
        wVariantClone( item, &(srcElement->value) );
            
        /* add to the table */
        wGrowSet( dstTable, i, (int)dstElement );
    }

    /* assign the table to the destination */
    wVariantDeref( dst );
    dst->dataType = W_TYPE_TABLE;
    dst->value.table = dstTable;
}


/* convert table data into char */
char *wTableToChar( wVariant *vSrc, int useQuotes )
{
    int i;
	char *buffer, *tmpBuffer;
    wGrow *table;
    wTableElement *element;
       
	/* get the table */
    table = vSrc->value.table;
    wMemTest( table, "wVariantToChar:table" ); 

	/* is it marked? */
	if (table->isMarked) {
		/* avoid an infinite loop */
        return wCharCopy( "..." );
	}
    
	/* create a buffer to hold the data */
    buffer = wCharMalloc( W_INBUFFER_MAX );

	/* mark it to prevent recursion */
	table->isMarked = W_TRUE;
    
	/* display each element */
    buffer = wCharConcat( buffer, "{" ); 
    for ( i = 1; i <= table->count; i++ ) {
        /* get the element */
        element = (wTableElement *)wGrowGet( table, i );

        /* convert key to a string and add to the buffer */
        tmpBuffer = wVariantToChar( &(element->key), W_TRUE );
        buffer = wCharConcat( buffer, tmpBuffer );
        wFree( tmpBuffer );

        /* add colon as seperator */
        buffer = wCharConcat( buffer, ":" );

        /* convert value to a string */
        tmpBuffer = wVariantToChar( &(element->value), W_TRUE );
        buffer = wCharConcat( buffer, tmpBuffer );
        wFree( tmpBuffer );

        /* trailing comma? */
        if (i < table->count) {
            buffer = wCharConcat( buffer, ", " );
        }
    }

    /* closing '}' */
    buffer = wCharConcat( buffer, "}" );

    /* clear the mark */
    table->isMarked = W_FALSE;

    return buffer;
}


/* support for wTableLookup: return position of integer key, or -n where n is where it should go */
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


/* support for wTableLookup: return position of string key, or -n where n is where it should go */
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
        } else if (cell->key.dataType == W_TYPE_STRING) {
            /* compare the strings */
            c = wStringCompareString( key, cell->key.value.string );
        } else {
            wErrorThrow( W_ERROR_CONVERT, "Found key with bad datatype of %s",
                wDatatypeName[cell->key.dataType] );
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

/* support for wTableIndex: index of key, or 0 if not found */
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
        wErrorThrow( W_ERROR_CONVERT, "Key must be string or number, not %s",
           wDatatypeName[key->dataType] );
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

/* returns pointer to key in table */
wVariant *wTableIndex( wVariant *vSrc, int indexCount )
{
    int i, index, createIfNotFound;
    wVariant *key, *result;
    wTableElement *element;
    wGrow *table;

    /* always create if not found */
    createIfNotFound = 1;

    /* get the table */
    table = vSrc->value.table;

    /* indexes are on the stack backwards */
    for ( i=indexCount; i>0; i-- ) {
        /* get key from stack */
        key = wStackPeek(i-1);

        /* seek it in the table */
        index = wTableLookup( table, key );

        /* not found in the table? */
        if (index < 1) {

			/* don't create the key? */
			if (!createIfNotFound) {

			    /* deref keys left on the stack */
				for ( ; index > 0; index-- ) {
					key = wStackPeek(index-1);
					wVariantDeref( key );
				}

				/* key not found */
				return NULL;
			}

            /* create an element to hold it */
            element = (wTableElement*)wMalloc( sizeof( wTableElement ) );

            /* set the key */
            if (key->dataType == W_TYPE_NUMBER) {
                element->key.dataType = W_TYPE_INTEGER;
                element->key.typeCast = W_TYPE_VARIANT;
                element->key.value.integer = (int)key->value.number;

            } else if (key->dataType == W_TYPE_INTEGER) {
                element->key.dataType = W_TYPE_INTEGER;
                element->key.typeCast = W_TYPE_VARIANT;
                element->key.value.integer = key->value.integer;

            } else if (key->dataType == W_TYPE_STRING) {
                /* don't need to refcount, because key wasn't deref'ed */
                element->key.dataType = W_TYPE_STRING;
                element->key.value.string = key->value.string;

            } else {
                wErrorThrow( W_ERROR_CONVERT, "Key must be string or number, not %s",
                    wDatatypeName[key->dataType] );
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
                wTableNew( &(element->value), 0 );
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


/* return pointer to element in table */
wVariant *wTableFind( wVariant *vSrc, wVariant *key )
{
    int index;
    wGrow *table;
    wTableElement *element;
    
    /* get the table */
    table = vSrc->value.table;
    
    /* seek it in the table */
    index = wTableLookup( table, key );

    /* nothing? */
    if (index < 1 ) {
        /* create an element to hold it */
        element = (wTableElement*)wMalloc( sizeof( wTableElement ) );

        /* set the key */
        if (key->dataType == W_TYPE_INTEGER) {
            element->key.dataType = W_TYPE_INTEGER;
            element->key.typeCast = W_TYPE_VARIANT;
            element->key.value.integer = key->value.integer;

        } else if (key->dataType == W_TYPE_NUMBER) {
            element->key.dataType = W_TYPE_INTEGER;
            element->key.typeCast = W_TYPE_VARIANT;
            element->key.value.integer = (int)key->value.number;

        } else if (key->dataType == W_TYPE_STRING) {
            /* don't need to refcount, because key wasn't deref'ed */
            element->key.dataType = W_TYPE_STRING;
            element->key.value.string = key->value.string;

        } else {
            wErrorThrow( W_ERROR_CONVERT, "Key must be string or number, not %s",
                wDatatypeName[key->dataType] );
            return NULL;
        }

        /* set the value to NOTHING */
        element->value.dataType = W_TYPE_NOTHING;
        element->value.typeCast = W_TYPE_VARIANT;

        /* insert new element into table */
        wTableInsertElementAt( table, element, -index );

    } else {
        /* deref the key */
        wVariantDeref( key );

        /* fetch the table element */
        element = (wTableElement *)wGrowGet( table, index );
    }

    /* get address the element */
    return &(element->value);
}


/* add element to the table */
void wTableInsert( wVariant *vSrc, wVariant *key, wVariant *value )
{
    wGrow table;
    wVariant *oldValue;

    /* nothing? */
    if (value->dataType == W_TYPE_NOTHING) {
        /* remove the value */
        wTableRemove( vSrc, key );
        return;
    }

    /* find prior value (create if doesn't exist) */
    oldValue = wTableFind( vSrc, key );

    /* replace the old value */
    wVariantCopy( oldValue, value );
}


/* remove key and value from the table */
void wTableRemove( wVariant *vSrc, wVariant *key )
{
    int index;
    wGrow *table;
    wTableElement *element;
    wString *s;

    /* get the table */
    table = vSrc->value.table;

    /* seek key in the table */
    index = wTableLookup( table, key );

    /* is the key in the table? */
    if (index > 0) {
        /* get the table element */
        element = (wTableElement *)wGrowGet( table, index );

        /* deref the key */
        wVariantDeref( &(element->key) );

        /* deref the value */
        wVariantDeref( &(element->value) );

        /* free the element */
        wFree( element );

        /* delete it from the table */
        wGrowDelete( table, index );

    }
}

/* create a table of the requested size */
void wTableNew( wVariant *dest, int size )
{
    wGrow *table;

    /* deref the destination */
    wVariantDeref( dest );

    /* allocate requested size plus padding */
    table = wGrowNew( size + 32 );
    table->count = 0;
    table->free = size + 32;

    /* set the destination */
    dest->dataType = W_TYPE_TABLE;
    dest->value.table = table;
    dest->value.table->refCount = 1;
}


/* return next item in table */
int wTableIterate( wVariant *vTable, wVariant *vIndex, wVariant *vArg1, wVariant *vArg2  )
{
    int i;
    wGrow *table;
    wTableElement   *cell;

    /* increment index */
    i = ++vIndex->value.integer;

    /* get the table */
    table = vTable->value.table;

    /* outside of range? */
    if (i > table->count ) {
        /* return false to mark end of list */
        return W_FALSE;

    } else if (vArg2 == NULL) {

        /* place value in arg1 */
        cell = (wTableElement *)wGrowGet( table, i );
        /* place value in arg1 */
        wVariantCopy( vArg1, &(cell->value) );
        
    } else {
        /* place key in arg1 */
        cell = (wTableElement *)wGrowGet( table, i );
        wVariantCopy( vArg1, &(cell->key) );

        /* place value in arg2 */
        wVariantCopy( vArg2, &(cell->value) );
    }

    /* return true to mark got an element */
    return W_TRUE;

}

/* number of elements in table */
int wTableCount( wVariant *vSrc )
{
    /* return the count */
    return vSrc->value.table->count;
}



/* table methods */
int wTableMethod( wVariant *vSrc, char *name, int argCount )
{
    int index;
    wVariant *item;

    if (strcmp( name, "remove" ) == 0 ) {
        /* check arg count */
        wVariantMethodCheckArgs( "Table:remove", 1, argCount );

        /* get the item to remove */
        item = wStackPeek(0);

        wTableRemove( vSrc, item );

        /* remove key from stack */
        wStackDrop( 1 );

        /* number of items returned */
        return 0;

    } else {
        wErrorThrow( W_ERROR_NOSUCH, "Method Table:%s not found", name );
        return 0;
    }
}

