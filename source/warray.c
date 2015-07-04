/*************************************************************
    Name:       warray.c
    Purpose:    W_TYPE_ARRAY datatype: static arrays
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/


void wArrayRegisterMethods()
{
    /* register the routines */
    wTheHandler[W_TYPE_ARRAY]->isNumeric        = W_FALSE;
    wTheHandler[W_TYPE_ARRAY]->ref              = wArrayRef;
    wTheHandler[W_TYPE_ARRAY]->deref            = wArrayDeref;
    wTheHandler[W_TYPE_ARRAY]->copy             = wArrayCopy;
    wTheHandler[W_TYPE_ARRAY]->clone            = wArrayClone;
    wTheHandler[W_TYPE_ARRAY]->fromNumber       = NULL;
    wTheHandler[W_TYPE_ARRAY]->toNumber         = NULL;
    wTheHandler[W_TYPE_ARRAY]->fromChar         = NULL;
    wTheHandler[W_TYPE_ARRAY]->toChar           = wArrayToChar;
    wTheHandler[W_TYPE_ARRAY]->compare          = NULL;
    wTheHandler[W_TYPE_ARRAY]->equal            = NULL;
    wTheHandler[W_TYPE_ARRAY]->isTrue           = NULL;
    wTheHandler[W_TYPE_ARRAY]->count            = wArrayCount;
    wTheHandler[W_TYPE_ARRAY]->index            = wArrayFindIndex;
    wTheHandler[W_TYPE_ARRAY]->find             = NULL;
    wTheHandler[W_TYPE_ARRAY]->remove           = NULL;
    wTheHandler[W_TYPE_ARRAY]->append           = NULL;
    wTheHandler[W_TYPE_ARRAY]->prepend          = NULL;
    wTheHandler[W_TYPE_ARRAY]->slice            = NULL;
    wTheHandler[W_TYPE_ARRAY]->iterate          = NULL;
}




void wArrayRef( wVariant *src )
{
	wMemTest( src->value.array, "wArrayRef:src->value.array" );
    src->value.array->refCount++;
}

void wArrayDeref( wVariant *src )
{
	int i;
	wArray *array;

    wMemTest( src->value.array, "wVariantDeref:src->value.array" );

	/* get the array */
	array = src->value.array;

	/* dereference the array */
    array->refCount--;

    if (array->refCount < 1) {
		/* free the elements in the array */
        for ( i = 0; i < array->elementCount; i++ ) {
			/* free the element */
            wVariantDeref( &(array->element[i]) );
		}
        /* free the array */
        wFree( array );
    }
}


/* copy the array data */
void wArrayCopy( wVariant *dst, wVariant *src )
{
	wMemTest( src->value.array, "wVariantCopy:src->value.array" );
	dst->value.array = src->value.array;	
}

void wArrayClone( wVariant *dst, wVariant *src )
{
    int i, bytes;
    wArray *srcArray, *dstArray;
    
    /* get the source array */
    srcArray = src->value.array;
        
    /* amount of memory needed */
    bytes = sizeof( wArray ) + (srcArray->elementCount * sizeof(wVariant));
    
    /* allocate memory for the base array */
    dstArray = (wArray *)wMalloc( bytes );

    /* copy information */
    dstArray->refCount = 1;
    dstArray->indexCount = srcArray->indexCount;
    dstArray->elementCount = srcArray->elementCount;
    
    /* copy index information */
    for ( i = 0; i < 4; i++ ) {
        dstArray->lower[i] = srcArray->lower[i];
        dstArray->upper[i] = srcArray->upper[i];
        dstArray->width[i] = srcArray->width[i];
        dstArray->offset[i] = srcArray->offset[i];
    }

    /* clone the index elements */
    for (i=0; i < srcArray->elementCount; i++){
        wVariantClone( &(dstArray->element[i]), &(srcArray->element[i]) );
    }

    /* set the destination */
    wVariantDeref( dst );
    dst->dataType = W_TYPE_ARRAY;
    dst->value.array = dstArray;
}


char *wArrayToChar( wVariant *src, int UseQuotes, int limit )
{
    // FIXME...
    return wCharCopy( "[array]" );
}        

/* create a new array */
wArray *wArrayCreate( int indexCount, wVariant *variant )
{
    /* Normally, a 'new' routine will pass the address of   */
    /* a wxVariant as its destination. In the case of an    */
    /* array, a bunch of range parameters are on the stack, */
    /* so the pointer to the array is passed back instead   */
    
    int i, j, bytes, offset;
    wNumber n;
    wString *s;
    wArray *array;
    wVariant *vDst;

    /* check number of indices */
    if (indexCount > 3) {
        wErrorThrow( W_ERROR_INDEX, "Arrays can't have more than 3 indexes" );
    }

    /* allocate memory for the base array */
    array = (wArray *)wMalloc( sizeof( wArray ) );

    /* initialize */
    array->refCount = 1;
    array->indexCount = indexCount;

    /* read the indices off the stack */
    array->elementCount = 1;
    for ( i = indexCount-1; i > -1; i-- ) {
        /* get upper and lower range */
        array->upper[i] = (int)wStackPopNumber();
        array->lower[i] = (int)wStackPopNumber();

        /* check range */
        if (array->upper[i] < array->lower[i]) {
            wErrorThrow( W_ERROR_INDEX, "Index %d out of range (%d < %d)",
                i+1, array->upper[i], array->lower[i] );
        }

        /* calculate width */
        array->width[i] = (array->upper[i]-array->lower[i])+1;
        array->elementCount *= array->width[i];

    }

    /* calculate the offsets */
    offset = array->elementCount;
    for (i=0; i<array->indexCount; i++) {
        offset = offset / array->width[i];
        array->offset[i] = offset;
    }

    /* calculate space needed */
    bytes = sizeof( wArray ) + (array->elementCount * sizeof(wVariant));

    /* reallocate space for the array */
    array = (wArray *)wRealloc( (void *)array, bytes );

    /* initialize array? */
    if (variant == NULL) {
        /* default if nothing specified is zero */
        for (i=0; i < array->elementCount; i++){            
            array->element[i].typeCast = W_TYPE_VARIANT;
            array->element[i].dataType = W_TYPE_NUMBER;
            array->element[i].value.number = 0;
        }

    /* default type is nothing */
    } else if (variant->dataType == W_TYPE_NOTHING) {
        for (i=0; i < array->elementCount; i++){
            array->element[i].typeCast = W_TYPE_VARIANT;
            array->element[i].dataType = W_TYPE_NOTHING;
        }

    /* default type is integer */
    } else if (variant->dataType == W_TYPE_INTEGER) {
        j = variant->value.integer;
        for (i=0; i < array->elementCount; i++){
            array->element[i].typeCast = W_TYPE_INTEGER;
            array->element[i].dataType = W_TYPE_INTEGER;
            array->element[i].value.integer = j;
        }


    /* default type is number */
    } else if (variant->dataType == W_TYPE_NUMBER) {
        n = variant->value.number;
        for (i=0; i < array->elementCount; i++){
            array->element[i].typeCast = W_TYPE_NUMBER;
            array->element[i].dataType = W_TYPE_NUMBER;
            array->element[i].value.number = n;
        }

    /* default type is string */
    } else if (variant->dataType == W_TYPE_STRING) {
        s = variant->value.string;
        s->refCount += array->elementCount;
        for (i=0; i < array->elementCount; i++){
            array->element[i].typeCast = W_TYPE_STRING;
            array->element[i].dataType = W_TYPE_STRING;
            array->element[i].value.string = s;
        }

    } else {
        /* haven't defined yet, so can't optimize */
        for (i=0; i < array->elementCount; i++){
            array->element[i].dataType = W_TYPE_NOTHING;
            wVariantCopy( &(array->element[i]), variant );
        }
    }

    return array;
}

/* initialize an array to default */
void wArrayInit( wVariant *dst, wVariant *src )
{
    int i;
    wArray *array;

    /* get the array */
    if (dst->dataType != W_TYPE_ARRAY) {
        wErrorThrow( W_ERROR_CONVERT, "Expected an array, not %s", wDataTypeName[src->dataType] );
    }
    array = dst->value.array;

    /* initialize array to default value */
    for (i=0; i < array->elementCount; i++){
        wVariantCopy( &(array->element[i]), src );
    }
}


/* initialize an array to a value */
void wArrayErase( wVariant *dst )
{
    int i, castTo;
    wArray *array;

    /* get the array */
    if (dst->dataType != W_TYPE_ARRAY) {
        wErrorThrow( W_ERROR_CONVERT, "Expected an array, not %s", wDataTypeName[dst->dataType] );
    }
    array = dst->value.array;

    /* find the cast type */
    castTo = array->element[0].typeCast;

    /* initialize array to nothing */
    for (i=0; i < array->elementCount; i++){
        wVariantDeref( &(array->element[i]) );
    }

    /* handle special defaults */
    switch (castTo) {
    case W_TYPE_STRING:
        /* set to empty strings */
        for (i=0; i < array->elementCount; i++){
            wStringNew( &(array->element[i] ), NULL, 0 );
        }
        break;

    case W_TYPE_NUMBER:
    case W_TYPE_VARIANT:
        /* set to zero */
        for (i=0; i < array->elementCount; i++){
            array->element[i].dataType = W_TYPE_NUMBER;
            array->element[i].value.number = 0;
        }
        break;
   }
}


/* return pointer to element in an array, NULL if not found */
wVariant *wArrayFindIndex( wVariant *vSrc, int indexCount )
{
    int i, offset, index, indexes[4], base;
    wArray *array;

    /* the values of the indexes are on the stack */

    /* get the array */
    array = vSrc->value.array;

    /* check count */
    if (array->indexCount != indexCount) {
        wErrorThrow( W_ERROR_INDEX, "Array expects %d indexes, not %d",
            array->indexCount, indexCount );
        return NULL;
    }


    /* load the indexes in reverse order */
    for ( i = indexCount; i > 0; i-- ) {
        indexes[i-1] = (int)wStackPopNumber();
    }

    /* process the indexes */
    offset = 0;
    for ( i=0; i<indexCount; i++ ) {
        index = indexes[i];
        if (index > array->upper[i]) {
            wErrorThrow( W_ERROR_INDEX, "Index %d of array is above upper bounds (%d>%d)",
                i+1, index, array->upper[i] );
            return NULL;
    
        } else if (index < array->lower[i]) {
            wErrorThrow( W_ERROR_INDEX, "Index %d of array is under lower bounds (%d<%d)",
                i+1, index, array->lower[i] );
            return NULL;
        }

        /* calculate offset into index */
        base = index-(array->lower[i]);
        offset += base * array->offset[i];
    }

    /* return pointer to element */
    return &(array->element[offset]);
}


/* return length of array */
int wArrayCount( wVariant *vSrc )
{
	wArray *array;

    array = vSrc->value.array;

    /* can only count if has one index */
    if (array->indexCount != 1) {
        wErrorThrow( W_ERROR_INDEX, "Can't return count of multi-dimensional array" );
    }

    /* number of elements in the array */
    return (array->upper[0] - array->lower[0]);
}

/* return next element in an array */
int wArrayIterate( wVariant *vArray, wVariant *vIndex, wVariant *vArg1, wVariant *vArg2 )
{

    // FIXME: not finished - how to handle arrays that don't start at zero?

    int i, count;
	wArray *array;

    /* get the source array */
    array = vArray->value.array;

    /* can only iterate if has one index */
    if (array->indexCount != 1) {
        wErrorThrow( W_ERROR_INDEX, "Can't iterate a multi-dimensional array" );
    }

    /* increment index */
    i = ++vIndex->value.integer;

    /* outside of range? */
//    if (i > theString->length ) {
//        /* return false to mark end of string */
//        return W_FALSE;
//    }

    /* number of elements in the array */
//    return (array->upper[0] - array->lower[0]);





    /* copy index */
//    wVariantCopy( vArg1, vIndex );

    /* get char from string? */
//    if (vArg2) {
//        wStringSubstr( vArg2, vString, i, i);
//    }

    /* return true to mark got an element */
    return W_TRUE;

}
