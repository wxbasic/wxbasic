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

    wVariantAddMethod( W_TYPE_TABLE, "insert", wTableMethodInsert, 2, 0 );
    wVariantAddMethod( W_TYPE_TABLE, "remove", wTableMethodRemove, 1, 0 );
    wVariantAddMethod( W_TYPE_TABLE, "haskey", wTableMethodHasKey, 1, 0 );

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
    wTableElement *element, *nextElement;

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
        for ( i = 1; i <= W_HASHTABLE_SIZE; i++ ) {

            /* get the first element in the chain */
            element = (wTableElement *)wGrowGet( table, i );

            /* not null? */
            while (element) {
                /* deref the key and value */
                wVariantDeref( &(element->key) );
                wVariantDeref( &(element->value) );

                /* get pointer to the next element */
                nextElement = (wTableElement *)(element->next);

                /* free the element */
                wFree( element );

                /* point to next */
                element = nextElement;
            }
        }

        /* free the table */
// wConsoleDebug("freeing table\n");
        wGrowFree( table );
    } else {
// wConsoleDebug("not freeing table, refcount = %d\n", table->refCount );
    }
}


/* create a table element with the given key */
wTableElement *wTableElementCreate( wGrow *table, wTableElement *prior, wVariant *key, wVariant *value )
{
    wTableElement *element;

    /* create an element to hold it */
    element = (wTableElement*)wMalloc( sizeof( wTableElement ) );

    /* set the key */
    switch (key->dataType) {
    case W_TYPE_NUMBER:
        element->key.dataType = W_TYPE_INTEGER;
        element->key.typeCast = W_TYPE_VARIANT;
        element->key.value.integer = (int)key->value.number;
        break;

    case W_TYPE_INTEGER:
        element->key.dataType = W_TYPE_INTEGER;
        element->key.typeCast = W_TYPE_VARIANT;
        element->key.value.integer = key->value.integer;
        break;

    case W_TYPE_STRING:
        element->key.dataType = W_TYPE_STRING;
        element->key.value.string = key->value.string;
        break;

    default:
        wErrorThrow( W_ERROR_CONVERT, "Key must be string or number, not %s",
            wDataTypeName[key->dataType] );
        break;
    }

    /* the value holds an undefined value */
    element->value.dataType = W_TYPE_NOTHING;
    element->value.typeCast = W_TYPE_VARIANT;

    /* assign a value? */
    if (value) {
        /* copy the value */
        wVariantCopy( &(element->value), value );
    }

    /* new end of chain */
    element->next = NULL;
    element->prior = (void *)prior;

    /* link to prior */
    if (prior) {
        prior->next = (void *)element;
    } else {
        /* first item in the table */
        wGrowSet( table, wTableGetHashValue( key ), (int)element );
    }

    return element;

}


/* copy table data */
void wTableCopy( wVariant *dst, wVariant *src )
{
	wMemTest( src->value.table, "wTableCopy:src->value.table" );
	dst->value.table = src->value.table;
}


void wTableClone( wVariant *dst, wVariant *src )
{
    int count, i, first;
    wGrow *dstTable, *srcTable;
    wTableElement *dstElement, *srcElement, *priorElement;
    wVariant *item;
    
    /* get the source table */
    srcTable = src->value.table;
    
    /* create a table large enough to hold it */
    dstTable = wGrowNew( W_HASHTABLE_SIZE );
    dstTable->count = W_HASHTABLE_SIZE;
    dstTable->free = 0;


    /* set refcount */
    dstTable->refCount = 1;

    /* walk through the hash table */
    for ( i = 1; i <= W_HASHTABLE_SIZE; i++ ) {

        /* get the table element */
        srcElement = (wTableElement *)wGrowGet( srcTable, i );
        priorElement = NULL;
        first = W_TRUE;

        /* walk through the linked list */
        while (srcElement) {

            /* need to refcount the key and value */
            wVariantRef( &(srcElement->key) );
            wVariantRef( &(srcElement->value) );

            /* create a copy */
            dstElement = wTableElementCreate( dstTable, priorElement, &(srcElement->key), &(srcElement->value) );

            /* move to next link */
            priorElement = dstElement;
            srcElement = (wTableElement *)srcElement->next;

        }

    }

    /* assign the table to the destination */
    wVariantDeref( dst );
    dst->dataType = W_TYPE_TABLE;
    dst->value.table = dstTable;

}


/* convert table data into char */
char *wTableToChar( wVariant *vSrc, int useQuotes, int limit )
{
    int i, addComma, count;
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

    /* first item gets no comma */
    addComma = W_FALSE;

    /* walk through the hash table */
    count = 0;
    for ( i = 1; i <= W_HASHTABLE_SIZE; i++ ) {

        /* past limit? */
        if (limit > 0 && count > limit) {
            break;
        }

        /* get the head of the chain */
        element = (wTableElement *)wGrowGet( table, i );

        /* walk the chain */
        while (element) {

            /* need comma? */
            if (addComma) {
                buffer = wCharConcat( buffer, ", " );
            } else {
                addComma = W_TRUE;
            }

            /* is there a limit? */
            if (limit > 0) {
                /* increment count of printed elements */
                count++;

                /* past limit? */
                if (count > limit) {
                    /* add elipsis */
                    buffer = wCharConcat( buffer, " ... " );

                    /* leave loop */
                    break;
                }
            }


            /* convert key to a string and add to the buffer */
            tmpBuffer = wVariantToChar( &(element->key), W_TRUE, 0 );
            buffer = wCharConcat( buffer, tmpBuffer );
            wFree( tmpBuffer );
    
            /* add colon as seperator */
            buffer = wCharConcat( buffer, ":" );
    
            /* convert value to a string */
            tmpBuffer = wVariantToChar( &(element->value), W_TRUE, limit );
            buffer = wCharConcat( buffer, tmpBuffer );
            wFree( tmpBuffer );

            element = (wTableElement *)element->next;
        }
    }

    /* closing '}' */
    buffer = wCharConcat( buffer, "}" );

    /* clear the mark */
    table->isMarked = W_FALSE;

    return buffer;
}


/* compute a hash value for an integer */
int wTableGetIntHashValue( int i )
{
    /* hash position starts at 1, not zero */
    return (int)(i % W_HASHTABLE_SIZE) + 1;
}


/* compute a hash value for a character string */
int wTableGetCharHashValue( char *letters )
{
    unsigned int    key;
    unsigned char   *letter;

    /* clear key value */
    key = 0;

    /* iterate through the string */
    for ( letter = (unsigned char *)letters; *letter != '\0'; letter++ ) {
        key = (W_HASH_MULTIPLER*key) + *letter;
    }

    /* ensure it fits into the table */
    return (int)(key % W_HASHTABLE_SIZE) + 1;
}


/* return hash of key */
int wTableGetHashValue( wVariant *key )
{
    switch (key->dataType) {
    case W_TYPE_STRING:
        return wTableGetCharHashValue( wStringChar( key )  );

    case W_TYPE_INTEGER:
        return wTableGetIntHashValue( key->value.integer );

    case W_TYPE_NUMBER:
        return wTableGetIntHashValue( (int)key->value.number );

    default:
        wErrorThrow( W_ERROR_CONVERT, "Key must be string or number, not %s",
           wDataTypeName[key->dataType] );
        return 0;
    }
}



/* return position of integer key */
wTableElement *wTableFindIntKey( wGrow *table, int key, int *flag )
{
    int i;
    wTableElement *element;

    /* get the hash value */
    i = wTableGetIntHashValue( key );

    /* find start of chain */
    element = (wTableElement *)wGrowGet( table, i );

    /* assume failure */
    *flag = W_FALSE;
    
    /* walk chain */
    while (element) {
        /* numeric? */
        if (element->key.dataType == W_TYPE_INTEGER) {
            /* equal? */
            if (key == element->key.value.integer) {
                /* match */
                *flag = W_TRUE;
                break;
            }
        }

        /* exit if last link */
        if (!element->next) {
            break;
        }

        /* get next link */
        element = (wTableElement *)element->next;
    }

    return element;
}


/* return true if key found */
wTableElement *wTableFindStringKey( wGrow *table, wVariant *key, int *flag )
{
    int             i;
    wTableElement   *element;

    /* get the hash value */
    i = wTableGetCharHashValue( wStringChar( key ) );

    /* get the start of the chain */
    element = (wTableElement *)wGrowGet( table, i );

    /* assume failure */
    *flag = W_FALSE;

    /* walk chain */
    while (element) {
        /* string? */
        if (element->key.dataType == W_TYPE_STRING) {
            /* compare the wStrings */
            if (wStringEqual( key, &(element->key) )) {
                *flag = W_TRUE;
                break;
            }
        }

        /* exit if last link */
        if (!element->next) {
            break;
        }

        /* get next link */
        element = (wTableElement *)element->next;

    }

    return element;
}


/* support for wTableIndex: address key, or -address of where to attach */
wTableElement *wTableLookup( wGrow *table, wVariant *key, int *flag )
{
    switch (key->dataType) {
    case W_TYPE_STRING:
        return wTableFindStringKey( table, key, flag );

    case W_TYPE_INTEGER:
        return wTableFindIntKey( table, key->value.integer, flag );

    case W_TYPE_NUMBER:
        return wTableFindIntKey( table, (int)key->value.number, flag );

    default:
        wErrorThrow( W_ERROR_CONVERT, "Key must be string or number, not %s",
           wDataTypeName[key->dataType] );
        return 0;
    }
}

    
/* returns pointer to key in table */
wVariant *wTableIndex( wVariant *vSrc, int indexCount )
{
    int i, found, createIfNotFound;
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
        element = wTableLookup( table, key, &found );

        if (!found) {
			/* don't create the key? */
			if (!createIfNotFound) {
			    /* deref keys left on the stack */
                for ( ; indexCount > 0; indexCount-- ) {
                    key = wStackPeek(indexCount-1);
					wVariantDeref( key );
				}

				/* key not found */
				return NULL;
			}

            /* need to refcount the key */
            wVariantRef( key );

            /* create an element to hold it */
            element = wTableElementCreate( table, element, key, NULL );
        }

        /* deref the key */
        wVariantDeref( key );

        /* get the value of the element */
        result = &(element->value);

        /* not the final index? */
        if (i > 1) {
            /* not a table? */
            if (result->dataType != W_TYPE_TABLE) {
                /* dereference the value */
                wVariantDeref( &(element->value) );

                /* replace it with a table */
                wTableNew( &(element->value) );
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
    int index, found;
    wGrow *table;
    wTableElement *element;
    
    /* get the table */
    table = vSrc->value.table;
    
    /* seek it in the table */
    element = wTableLookup( table, key, &found );
    if (found) {
        /* create an empty key/value */
        element = wTableElementCreate( table, element, key, NULL );
    }

    /* deref the key */
    wVariantDeref( key );

    /* return value */
    return &(element->value);
}


/* add element to the table */
void wTableInsert( wVariant *vSrc, wVariant *key, wVariant *value )
{
    int found;
    wGrow *table;
    wTableElement *element;

    /* get the table */
    table = vSrc->value.table;

    /* is it in the table? */
    element = wTableLookup( table, key, &found );
    if (found) {
        /* replace the key */
        wVariantCopy( &(element->value), value );

    } else {
        /* create a keyed element to hold the values */
        element = wTableElementCreate( table, element, key, value );
    }
}


/* remove element from the table */
void wTableRemove( wVariant *vSrc, wVariant *vKey )
{
    int index, hashValue, found;
    wGrow *table;
    wTableElement *element, *linkElement;

    /* get the table */
    table = vSrc->value.table;

    /* find the element matching the key */
    element = wTableLookup( table, vKey, &found );
    if (found) {

        /* deref the key */
        wVariantDeref( &(element->key) );

        /* deref the value */
        wVariantDeref( &(element->value) );

        /* prior item? */
        if (element->prior) {
            /* fix it's next link */
            linkElement = (wTableElement *)element->prior;
            linkElement->next = (void *)element->next;

        } else {
            /* find position */
            hashValue = wTableGetHashValue( vKey );

            /* make new head of chain (could be NULL) */
            wGrowSet( table, hashValue, (int)element->next );
        }

        /* item follows? */
        if (element->next) {
            /* fix it's prior link */
            linkElement = (wTableElement *)element->next;
            linkElement->prior = (void *)element->prior;
        }

        /* free the element */
        wFree( element );
    }
}


/* create a table of the requested size */
void wTableNew( wVariant *dest )
{
    wGrow *table;

    /* deref the destination */
    wVariantDeref( dest );

    /* allocate */
    table = wGrowNew( W_HASHTABLE_SIZE );
    table->count = W_HASHTABLE_SIZE;
    table->free = 0;

    /* set the destination */
    dest->dataType = W_TYPE_TABLE;
    dest->value.table = table;
    dest->value.table->refCount = 1;
}


/* return next item in table */
int wTableIterate( wVariant *vTable, wVariant *vIndex, wVariant *vArg1, wVariant *vArg2  )
{
    int i, startFrom;
    wGrow *table;
    wTableElement *element;

    /* get the table */
    table = vTable->value.table;

    /* get the current index */
    i = vIndex->value.integer;

    /* first time? */
    if (i == 0) {
        startFrom = 1;

    } else {
        /* get the element */
        element = (wTableElement *)i;

        /* nothing follows? */
        if (!element->next) {
            /* start from next hash key */
            startFrom = wTableGetHashValue( &(element->key) ) + 1;
        } else {
            /* get next element on chain */
            element = (wTableElement *)(element->next);

            /* don't need to search */
            startFrom = 0;
        }
    }


    /* need to search the keys? */
    if (startFrom) {
        element = NULL;

        /* search for the first non-empty slot */
        for ( i = startFrom; i <= W_HASHTABLE_SIZE; i++ ) {
            element = (wTableElement *)wGrowGet( table, i );
            if (element) {
                break;
            }
        }

        /* nothing found? */
        if (!element) {
            /* end of table */
            return W_FALSE;
        }
    }

    /* only asking for a single value? */
    if (vArg2 == NULL) {
       wVariantCopy( vArg1, &(element->value) );
        
    } else {
        /* place key in arg1 */
        wVariantCopy( vArg1, &(element->key) );

        /* place value in arg2 */
        wVariantCopy( vArg2, &(element->value) );
    }

    /* update index */
    vIndex->value.integer = (int)element;

    /* return true to mark got an element */
    return W_TRUE;

}

/* number of elements in table */
int wTableCount( wVariant *vTable )
{
    int i, count;
	wGrow *table;
    wTableElement *element;

    /* verify it's a table */
    wMemTest( vTable->value.table, "wTableCount:vTable->value.table" );

    /* get the table */
    table = vTable->value.table;

    /* clear the count */
    count = 0;

    /* walk through the table */
    for ( i = 1; i <= W_HASHTABLE_SIZE; i++ ) {

        /* get the first element in the chain */
        element = (wTableElement *)wGrowGet( table, i );

        /* not null? */
        while (element) {
            /* increment the count */
            count++;

            /* get pointer to the next element */
            element = (wTableElement *)(element->next);
        }
    }

    /* return the count */
    return count;

}


void wTableMethodRemove()
{
    wVariant *arg;

    arg = wStackPop();
    wTableRemove( wTheCall->vSelf, arg );

    wVariantDeref( arg );
}


void wTableMethodInsert()
{
    wVariant *key, *value;

    value = wStackPop();
    key = wStackPop();
    wTableInsert( wTheCall->vSelf, key, value );

    wVariantDeref( key );
    wVariantDeref( value );
}

/* return true if table holds the key */
int wTableHasKey( wVariant *source, wVariant *key )
{
    int flag;
    wGrow *table;

    /* get the table */
    table = source->value.table;

    /* look for it in the table */
    wTableLookup( table, key, &flag );

    /* return the result */
    return flag;
}


/* return true if table holds the key */
void wTableMethodHasKey()
{
    int flag;
    wVariant *key;
    wGrow *table;

    /* get the key */
    key = wStackPop();

    /* get the table */
    table = wTheCall->vSelf->value.table;

    /* look for it in the table */
    wTableLookup( table, key, &flag );

    /* deref the key */
    wVariantDeref( key );

    /* return the result */
    wStackPushNumber( flag );
}
