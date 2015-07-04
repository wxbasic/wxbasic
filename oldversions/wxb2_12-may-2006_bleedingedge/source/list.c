/*************************************************************
    Name:       list.c
    Purpose:    sequential lists for wxBasic
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/

/* create a list of the requested size */
void wListNew( wVariant *dst, int size )
{
    int i;
    wGrow *list;
    wVariant *value;

    /* deref the destination */
    wVariantDeref( dst );

    /* allocate requested size */
    list = wGrowNew( size );
    list->count = size;
    list->free = 0;

    /* fill the list with nothing */
    for ( i = 1; i <= size; i++ ) {
        /* create a variant */
        value = (wVariant *)wMalloc( sizeof( wVariant ) );
        value->dataType = W_TYPE_NOTHING;
        value->typeCast = W_TYPE_VARIANT;

        /* set in into the list */
        wGrowSet( list, i, (int)value );
    }

    /* change default grow size */
    list->chunks = 32;

    /* set the destination */
    dst->dataType = W_TYPE_LIST;
    dst->value.list = list;
    dst->value.list->refCount = 1;
}



/* insert element into a list */
void wListInsert( wGrow *list, wVariant *src, int index )
{
    wVariant *dst;

    /* check the range */
    if (index < 1 || index > list->count) {
        wErrorFatal( "Index %d outside list size %d", index, list->count );
        wErrorSet( W_ERROR_INDEX );

    } else {
        /* get the destination */
        dst = (wVariant *)wGrowGet( list, index );
    
        /* replace the prior value, don't refcount the source */
        wVariantCopy( dst, src );
    }
}



/* returns pointer to element, or NULL if element doesn't exist */
wVariant *wListGetElement( wGrow *list, int indexCount )
{
    int i, index;
    wVariant *key, *result;

    /* indexes are ordered on stack backwards */
    for ( i=indexCount; i>0; i-- ) {
        /* get key from stack */
        key = wStackPeek(i-1);

        /* coerce it to a number */
        wVariantCoerce( key, W_TYPE_NUMBER );
        if (key->dataType != W_TYPE_NUMBER ) {
            /* FIXME! Make sure error flag is set */
            return NULL;
        }

        /* convert it to an integer */
        index = (int)key->value.number;
        if (index < 1 || index > list->count ) {
            /* stop looking */
            result = NULL;
            break;
        }

        /* fetch the table element */
        result = (wVariant *)wGrowGet( list, index );

        /* not the final index? */
        if (i > 1) {
            /* not a list? */
            if (result->dataType != W_TYPE_LIST) {
                /* stop looking */
                result = NULL;
                break;
            } else {
                /* set to the list */
                list = result->value.list;
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


/* returns new slice from list */
void wListSlice( wVariant *dst, wVariant *src, int start, int end )
{
    int srcIndex, dstIndex;
    wGrow *srcList, *dstList;
    
    /* get the list */
    srcList = src->value.list;

    /* clip start range */
    if (start < 1) {
        start = 1;
    }

    /* clip end range */
    if (end > srcList->count) {
        end = srcList->count;
    }

    /* start larger than end? */
    if (start > end) {
        /* return an empty slice */
        wListNew( dst, 0 );
        return;
    }

    /* allocate a new slice to hold the value */
    wListNew( dst, (end-start)+1 );
    dstList = dst->value.list;

    /* copy value from source to destination */
    for ( srcIndex = start, dstIndex = 1; srcIndex <= end; srcIndex++, dstIndex++ ) {
        /* copy from source to destination */
        wVariantCopy(
            (wVariant *)wGrowGet( dstList, dstIndex ),
            (wVariant *)wGrowGet( srcList, srcIndex ) );
    }

}

/* return next item in list */
int wListIterate( wVariant *vArg1, wVariant *vArg2, wVariant *vList, wVariant *vIndex )
{
    int i;
    wGrow *list;

    /* increment index */
    i = (int)++vIndex->value.number;

    /* get list */
    list = vList->value.list;

    /* outside of range? */
    if (i > list->count ) {
        /* zap the list */
        wVariantDeref( vList );

        /* return false to mark end of list */
        return W_FALSE;

    /* only return a single value? */
    } else if (vArg2 == NULL) {
        /* copy element to value */
        wVariantCopy( vArg1, (wVariant *)wGrowGet( list, i ) );

    /* return index and key */
    } else {
        /* index in arg1 */
        wVariantCopy( vArg1, vIndex );

        /* value in arg2 */
        wVariantCopy( vArg2, (wVariant *)wGrowGet( list, i ) );
    }

    /* return true to mark got an element */
    return W_TRUE;

}

/* dereference list */
void wListDeref( wGrow *list )
{
    int i, count;
    wVariant *element;

    /* already marked? */
    if (list->isMarked) {
        /* don't read through again */
        return;
    }

    /* dereference */
    list->refCount--;
    
    /* no more references? */
    if (list->refCount < 1) {

        /* mark, so it's not recursively called */
        list->isMarked = W_TRUE;

        /* free the elements from the list */
        count = list->count;
        for ( i = 1; i <= count; i++ ) {
            /* get the list element */
            element = (wVariant *)wGrowGet( list, i );

            /* free the element */
            wFree( element );
        }
        /* free the list */
        wGrowFree( list );
    }
}


