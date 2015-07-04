/*************************************************************
    Name:       wlist.c
    Purpose:    sequential lists for wxBasic
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/


void wListRegisterMethods()
{
    /* register the routines */
    wTheHandler[W_TYPE_LIST]->isNumeric     = W_FALSE;
    wTheHandler[W_TYPE_LIST]->ref          = wListRef;
    wTheHandler[W_TYPE_LIST]->deref         = wListDeref;
    wTheHandler[W_TYPE_LIST]->copy          = wListCopy;
    wTheHandler[W_TYPE_LIST]->clone         = wListClone;
    wTheHandler[W_TYPE_LIST]->fromNumber    = NULL;
    wTheHandler[W_TYPE_LIST]->toNumber      = NULL;
    wTheHandler[W_TYPE_LIST]->fromChar      = NULL;
    wTheHandler[W_TYPE_LIST]->toChar        = wListToChar;
    wTheHandler[W_TYPE_LIST]->compare       = NULL;
    wTheHandler[W_TYPE_LIST]->equal         = NULL;
    wTheHandler[W_TYPE_LIST]->isTrue        = NULL;
    wTheHandler[W_TYPE_LIST]->count         = wListCount;
    wTheHandler[W_TYPE_LIST]->index         = wListIndex;
    wTheHandler[W_TYPE_LIST]->insert        = wListInsert;
    wTheHandler[W_TYPE_LIST]->find          = NULL;
    wTheHandler[W_TYPE_LIST]->remove        = NULL;
    wTheHandler[W_TYPE_LIST]->append        = wListAppend;
    wTheHandler[W_TYPE_LIST]->prepend       = wListPrepend;
    wTheHandler[W_TYPE_LIST]->slice         = wListSlice;
    wTheHandler[W_TYPE_LIST]->iterate       = wListIterate;
}


/* create a list of the requested size */
void wListNew( wVariant *dst, int size )
{
    int i;
    wGrow *list;
    wVariant *value;

    /* deref the destination */
    wVariantDeref( dst );

    /* allocate requested size plus padding */
    list = wGrowNew( size + 32 );
    list->count = size;
    list->free = 32;

    /* fill the list with nothing */
    for ( i = 1; i <= size; i++ ) {
        /* create a variant */
        value = (wVariant *)wMalloc( sizeof( wVariant ) );
        value->dataType = W_TYPE_NOTHING;
        value->typeCast = W_TYPE_VARIANT;

        /* set in into the list */
        wGrowSet( list, i, (int)value );
    }

    /* set the destination */
    dst->dataType = W_TYPE_LIST;
    dst->value.list = list;
    dst->value.list->refCount = 1;
}

void wListRef( wVariant *src )
{
	wMemTest( src->value.list, "wListRef:src->value.list" );
	src->value.list->refCount++;
}


/* dereference list */
void wListDeref( wVariant *src )
{
    int i, count;
    wVariant *element;
    wGrow *list;
    
    /* get the list */
    list = src->value.list;

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
            /* get the pointer to the list element */
            element = (wVariant *)wGrowGet( list, i );

            /* dereference and free the element */
            wVariantDeref( element );
        }
        /* free the list */
        wGrowFree( list );
    }
}


/* copy list data */
void wListCopy( wVariant *dst, wVariant *src )
{
	wMemTest( src->value.list, "wTableCopy:src->value.list" );
	dst->value.list = src->value.list;
}


/* clone the list data */
void wListClone( wVariant *dst, wVariant *src )
{
    int i, count;
    wGrow *srcList, *dstList;
    wVariant *srcElement, *dstElement;
    
    /* get the source list */
    srcList = src->value.list;
    
    /* create a list large enough to hold it */
    dstList = wGrowNew( srcList->count + srcList->free );
    dstList->count = srcList->count;
    dstList->free = srcList->free;

    /* set refcount */
    dstList->refCount = 1;

    /* clone the elements from the list */
    count = srcList->count;
    for ( i = 1; i <= count; i++ ) {
        /* get the pointer to the list element */
        srcElement = (wVariant *)wGrowGet( srcList, i );
        
        /* create a variant pointer to hold the copy */
        dstElement = wVariantNew();
        
        /* clone the element */
        wVariantClone( dstElement, srcElement );
        
        /* place it in the destination */
        wGrowSet( dstList, i, (int)dstElement );
    }
    
    /* assign it to the destination */
    wVariantDeref( dst );
    dst->dataType = W_TYPE_LIST;
    dst->value.list = dstList;

}

/* convert table data into char */
char *wListToChar( wVariant *vSrc, int useQuotes, int limit )
{
    int i, count;
	char *buffer, *tmpBuffer;
    wGrow *list;
    wVariant *element;

	/* get the list */
    list = vSrc->value.list;
    wMemTest( list, "wListToChar" ); 

	/* is it marked? */
	if (list->isMarked) {
		/* avoid an infinite loop */
        return wCharCopy( "..." );
	}
    
	/* create a buffer to hold the data */
    buffer = wCharMalloc( W_INBUFFER_MAX );

	/* mark it to prevent recursion */
	list->isMarked = W_TRUE;

    /* limit count */
    count = 0;

	/* display each element */
    buffer = wCharConcat( buffer, "[" ); 
    for ( i = 1; i <= list->count; i++ ) {

        /* limit? */
        if (limit > 0) {
            /* increment count */
            count++;
            if (count > limit) {
                buffer = wCharConcat( buffer, " ... " );
                break;
            }
         }

        /* get the element */
        element = (wVariant *)wGrowGet( list, i );

        /* convert value to a string */
        tmpBuffer = wVariantToChar( element, W_TRUE, limit );
        buffer = wCharConcat( buffer, tmpBuffer );
        wFree( tmpBuffer );

        /* trailing comma? */
        if (i < list->count) {
            buffer = wCharConcat( buffer, ", " );
        }
    }

    /* closing ']' */
    buffer = wCharConcat( buffer, "]" );

    /* clear the mark */
    list->isMarked = W_FALSE;

    return buffer;
}



/* insert element into a list */
void wListInsert( wVariant *src, wVariant *key, wVariant *value )
{
    int index;
    wVariant *dst;
    wGrow *list;
    
    /* get the numeric value of the key */
    index = (int)wVariantGetNumber( key );

    /* get the list */
    list = src->value.list;

    /* check the range */
    if (index < 1 || index > list->count) {
        wErrorThrow( W_ERROR_INDEX, "Index %d outside list size %d", index, list->count );

    } else {
        /* get the destination */
        dst = (wVariant *)wGrowGet( list, index );
    
        /* replace the prior value, don't refcount the source */
        wVariantCopy( dst, value );
    }
}

/* append element into a list */
void wListAppend( wVariant *src, wVariant *value )
{
    int index;
    wGrow *list;
    wVariant *dst;    

    /* malloc a variant to hold the data */
    dst = (wVariant *)wMalloc( sizeof( wVariant ) );
    dst->dataType = W_TYPE_NOTHING;
    dst->typeCast = W_TYPE_VARIANT;
    
    /* copy value to destination */
    wVariantCopy( dst, value );

    /* get the list */
    list = src->value.list;

    /* position to place the pointer */
    index = wGrowMakeRoom( list );

    /* set the pointer into the list*/
    wGrowSet( list, index, (int)dst );
}

/* prepend element into a list */
void wListPrepend( wVariant *src, wVariant *value )
{
    int index;
    wVariant *dst;
    wGrow *list;
    
    /* get the list */
    list = src->value.list;

    /* malloc a variant to hold the data */
    dst = (wVariant *)wMalloc( sizeof( wVariant ) );
    dst->dataType = W_TYPE_NOTHING;
    dst->typeCast = W_TYPE_VARIANT;
    
    /* copy value to destination */
    wVariantCopy( dst, value );

    /* insert the pointer into the list */
    wGrowInsert( list, 1, (int)dst );
}


/* returns pointer to element, or NULL if element doesn't exist */
wVariant *wListIndex( wVariant *src, int indexCount )
{
    int i, index;
    wVariant *key, *result;
    wGrow *list;
    
    /* get the list */
    list = src->value.list;

    /* indexes are ordered on stack backwards */
    for ( i=indexCount; i>0; i-- ) {
        /* get key from stack */
        key = wStackPeek(i-1);

        /* coerce it to an integer */
        index = (int)wVariantGetNumber( key );

        /* out of range? */
        if (index < 1 || index > list->count ) {
            /* set to NULL and break out of loop */
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
int wListIterate( wVariant *vList, wVariant *vIndex, wVariant *vArg1, wVariant *vArg2 )
{
    int i;
    wGrow *list;

    /* increment index */
    i = ++vIndex->value.integer;

    /* get list */
    list = vList->value.list;

    /* outside of range? */
    if (i > list->count ) {
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

/* return count of list elements */
int wListCount( wVariant *vSrc )
{
    /* return the count of elements */
    return vSrc->value.list->count;
}
