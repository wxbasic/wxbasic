/*************************************************************
    Name:       grow.c
    Purpose:    resizable pointer arrays
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/


/* create a new array */
wGrow *wGrowNew( int size )
{
    wGrow *array;

    /* minimum size */
    if (size == 0) {
        size = 32;
    }

    /* create a new structure */
    array = (wGrow *)wMalloc( sizeof( wGrow ) );
    array->count = 0;
    array->free = size;
    array->isMarked = 0;
    array->value = (void *)wMalloc( size * sizeof( int ) );
        
    return array;
}

/* free a grow table */
void wGrowFree( wGrow *src )
{
    wMemTest( src, "wGrowCopy:src" );

    wFree( src->value );
    wFree( src );
}


/* copy array value, returning pointer */
wGrow *wGrowCopy( wGrow *src )
{
    int bytes;
    wGrow *dst;

    wMemTest( src, "wGrowCopy:src" );

    /* copy structure */
    dst = (wGrow *)wMalloc( sizeof( wGrow ) );
    dst->count = src->count;
    dst->free = src->free;

    /* copy value */
    bytes = src->count * sizeof( int );
    dst->value = (void *)wMalloc( bytes );
    wMemMove( dst->value, src->value, bytes, "wGrowCopy" );
    
    return dst;
}

/* return number of items in array */        
int wGrowCount( wGrow *array )
{
    wMemTest( array, "wGrowCount:array" );
    return array->count;
}

/* allocate more space for the array, if needed */
int wGrowMakeRoom( wGrow *array )
{
    int newSize, i, newFree;
    int *value;

    wMemTest( array, "wGrowMakeRoom:array" );

    /* out of free space? */
    if (array->free == 0) {

        /* double the current size */
        newFree = array->count * 2;

        /* range check */
        if (newFree < 1 ) {
            /* was zero, set to 32 */
            newFree = 32;
        } else if (newFree > 1024) {
            /* max resize */
            newFree = 1024;
        }

        newSize = (array->count + newFree) * sizeof( int );
        array->value = (void *)wRealloc( (void *)array->value, newSize );
        array->free = newFree;

        /* initialize to zero */
        value = (int *)array->value;
        for ( i = array->count; i < array->count + array->free; i++ ) {
            value[i] = 0;
        }

    }
        
    /* return the index of the next item */
    array->free--;
    return ++array->count;
}


/* get an existing item from the given position */
int wGrowGet( wGrow *array, int index )
{
    int *value;

    wMemTest( array, "wGrowGetPointer:array" );

    /* range check */
    if (index < 1 || index > array->count) {
        wErrorThrow( W_ERROR_INDEX, "Index %d outside of array size %d (wGrowGet)", index, array->count );
    }
    
    /* calculate where object is */
    value = (int *)array->value;
    return value[index-1];
}



/* set the value of an item at the given position */
void wGrowSet( wGrow *array, int index, int newValue )
{
    int *intArray;

    /* don't test value! */
    wMemTest( array, "wGrowSet:array" );

    /* range check */
    if (index < 1 || index > array->count) {
        wErrorThrow( W_ERROR_INDEX, "Index %d outside of array size %d (wGrowSet)", index, array->count );
    }
        
    /* calculate where object is */
    intArray = (int *)array->value;
    intArray[index-1] = newValue;
}


/* insert a new item at the given position */
void wGrowInsert( wGrow *array, int index, int value )
{
    int count, bytes;
    int *intArray;
    void *src, *dst;

    /* don't test value! */
    wMemTest( array, "wGrowInsert:array" );

    /* range check */
    if (index < 1 || index > array->count) {
        wErrorThrow( W_ERROR_INDEX, "Index %d outside of array size %d (wGrowInsert)", index, array->count );
        return;
    }

    /* allocate space, but don't include it in the count */
    count = wGrowMakeRoom( array ) - 1;

    /* number of bytes to move */
    bytes = (count - index + 1) * sizeof(int);

    /* offset into where the value starts */
    intArray = (int *)array->value;
    src = (void *)&(intArray[index-1]);

    /* destination is one element (per bytes wide) */
    dst = (void *)&(intArray[index]);
    wMemTest( dst, "wGrowInsert:dst" );

    /* make room for the new element */
    wMemMove( dst, src, bytes, "wGrowInsert" );

    /* copy the new element's value */
    intArray[index-1] = value;
}
        
/* remove an index at the given position */
void wGrowDelete( wGrow *array, int index )
{
    int start, bytes;
    int *intArray;
    void *src, *dst;

    wMemTest( array, "wGrowDelete:array" );
    wMemTest( array->value, "wGrowDelete:array->value" );


    /* range check */
    if (index < 1 || index > array->count) {
        wErrorThrow( W_ERROR_INDEX, "Index %d outside of array size %d (wGrowInsert)", index, array->count );
    }

    /* only need to move if it's not the last item */
    if (index < array->count) {

        /* calculate where object is */
        intArray = (int *)array->value;
            
        /* number of bytes to move */
        bytes = (array->count - index) * sizeof( int );
        
        /* source and destination */
        dst = (void *)&(intArray[index-1]);
        src = (void *)&(intArray[index]);

        wMemTest( src, "wGrowDelete:src" );
        wMemTest( dst, "wGrowDelete:dst" );
    
        /* shove over item currently in position */
        wMemMove( dst, src, bytes, "wGrowDelete" );

    }

    /* adjust the counts */
    array->free++;
    array->count--;
        
}

        
/* append an item onto the end of the array, returns position */
int wGrowAppend( wGrow *array, int value )
{
    int index;

    /* don't test value! */
    wMemTest( array, "wGrowAppend:array" );

    /* make sure there's room for another element */
    index = wGrowMakeRoom( array );

    wGrowSet( array, index, value );

    return index;        
}

/* return value on end of array, leaving array alone */
int wGrowPeek( wGrow *array, int offset )
{
    wMemTest( array, "wGrowPeek:array" );
    return wGrowGet( array, (array->count)-offset );
}

/* increment the value on top of the array */
void wGrowIncr( wGrow *g, int n )
{
    wMemTest( g, "wGrowIncr:g" );

    if (g->count == 0) {
        wErrorThrow( W_ERROR_INDEX, "Empty array (wGrowIncr)" );
    }
    wGrowSet( g, g->count, wGrowGet( g, g->count ) + n );
}


/* return address from end, and remove from count */
int wGrowPop( wGrow *array )
{
    int result;

    wMemTest( array, "wGrowPop:array" );

    /* get value */
    result = wGrowGet( array, array->count );

    /* mark as free */
    --array->count;
    ++array->free;

    return result;
}

/* drop n items from the end of the array */
void wGrowDrop( wGrow *array, int n )
{

    wMemTest( array, "wGrowDrop:array" );

    /* range check */
    if (n > array->count || n < 0) {
        wErrorThrow( W_ERROR_INDEX, "Can't drop %d items, size is %d (wGrowDrop)",
            n, array->count );
    }

    if (n > 0) {
        /* mark as free */
        array->count -= n;
        array->free += n;
    }
}



/* concat one grow array onto another */
void wGrowConcat( wGrow *dst, wGrow *src )
{
    int newSize, diff, bytes;
    void *startMove;

    wMemTest( src, "wGrowConcat:src" );
    wMemTest( dst, "wGrowConcat:dst" );

    /* trivial case? */
    if (src->count == 0) {
        return;
    }

    /* allocate space, if needed */
    diff = src->count - dst->free;
    if (diff > 0) {
        newSize = (dst->count + dst->free + diff) * sizeof( int );
        dst->value = (void *)wRealloc( (void *)dst->value, newSize );
        dst->free += diff;
    }

    /* number of bytes to move */
    bytes = src->count * sizeof( int );

    /* offset into where the value ends */
    startMove = ((char *)dst->value) + (dst->count * sizeof( int ) );
    wMemTest( startMove, "wGrowConcat:startMove" );
    wMemTest( src->value, "wGrowConcat:src->value" );

    /* copy the new element's value */
    wMemMove( (void *)startMove, src->value, bytes, "wGrowConcat" ); 

    /* update the counts */
    dst->count += src->count;
    dst->free -= src->count;

}


/* preappend an item onto the beginning of the array */
void wGrowPrepend( wGrow *array, int value )
{

    wMemTest( array, "wGrowPrepend:array" );

    /* if empty, append */
    if (array->count == 0) {
        wGrowAppend( array, value );
    } else {        
        /* insert at position 1 */
        wGrowInsert( array, 1, value );
    }
}

