/*
    Name:       array.c
    Purpose:    array structures for wxBasic
    Author:     David Cuny
    Copyright:  (c) 2002 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*/


/* create an array; indexes are on stack */
wArray *wCreateStaticArray( wSymbol *s )
{

    int     indexes, i, arraySize, stackPos;
    int     indexSize[W_MAX_INDEXES], lower[W_MAX_INDEXES],
            upper[W_MAX_INDEXES];
    wArray  *array;

    /* stack holds:
            index count (on top)
            lower range of index 1
            upper range of index 1
            lower range of index 2
            upper range of index 2
            ...
            lower range of index n
            upper range of index n
    */


    /* paranoia */
    wMemTest( "wCreateStaticArray: symbol", s );

    /* get the index */
    indexes = (int)wPopNumber();
    if (indexes > W_MAX_INDEXES) {
        wFatal( W_RUNTIME, "array %s has %d dimensions, maximum is %d",
                    s->name, indexes, W_MAX_INDEXES );
    }

    /* get the ranges */
    arraySize = 1;
    for (i=0; i < indexes; i++) {
        lower[i] = (int)wPopNumber();
        upper[i] = (int)wPopNumber();

        if (lower[i] > upper[i]) {
            wFatal( W_RUNTIME, "index %d of array %s: lower index (%d) greater than upper(%d) index",
                i+1, lower[i], upper[i] );
        }

        indexSize[i] = (upper[i]-lower[i])+1;
        arraySize *= indexSize[i];
    }

    /* allocate space for structure */
    array = (wArray *)wMalloc(sizeof(wArray));
    array->isDynamic = 0;
    array->data.item = (wVariant *)wMalloc(arraySize * sizeof(wVariant)) ;

    /* initialize array */
    for (i=0; i < arraySize; i++){
        array->data.item[i].datatype = W_DATA_NUMBER;
        array->data.item[i].value.number = 0;
    }

    /* store values in structure */
    array->indexes = indexes;
    array->elements = arraySize;
    for (i=0; i<indexes; i++) {
        array->lower[i] = lower[i];
        array->upper[i] = upper[i];
        arraySize = arraySize/indexSize[i];
        array->offset[i] = arraySize;
    }

    /* store pointer in variable */
    stackPos = wVarStackPos( s );
    wData[stackPos].datatype = W_DATA_ARRAY;
    wData[stackPos].value.array = array;

    return array;
}

/* create a dynamic array */
wArray *wCreateDynamicArray( wSymbol *s )
{

    int     i, arraySize, stackPos;
    wArray   *array;

    /* paranoia */
    wMemTest( "wCreateDynamicArray: symbol", s );

    /* allocate space for structure */
    array = (wArray *)wMalloc(sizeof(wArray));
    array->isDynamic = 1;

    /* get the ranges */
    arraySize = 32;
    array->lower[0]        = 0;         /* count of used cells */
    array->upper[0]        = 32;        /* count of free cells */

    array->data.cell = (wArrayCell *)wMalloc(arraySize * sizeof(wArrayCell)) ;

    /* initialize array */
    for (i=0; i < arraySize; i++){
        array->data.cell[i].key = NULL;
        array->data.cell[i].data.datatype = W_DATA_UNDEFINED;
    }

    /* store pointer in variable */
    stackPos = wVarStackPos( s );
    wData[stackPos].datatype = W_DATA_ARRAY;
    wData[stackPos].value.array = array;

    return array;
}



/* create an array symbol */
wSymbol *wCreateArraySymbol( char *name, int args )
{
    wSymbol  *s = NULL;

    /* already exists in scope? */
    s = wFindSymbol( name, wCurrentScope );
    if (s != NULL) {
        if (s->symbolType != W_SYM_ARRAY) {
            wFatal( W_SYNTAX, "%s is already defined as %s",
                s->name, wDatumName[s->symbolType] );
        } else {
            return s;
        }
    }

    s = wAddSymbol( name, wCurrentScope, W_SYM_ARRAY, W_TRUE );

    /* how many args? */
    if (args == 0) {
        /* dynamic */
        s->args = 1;
        s->optArgs = W_MAX_INDEXES;
    } else {
        s->args = args;
    }

    if (wCurrentScope==NULL) {
        /* create as global */
        s->stackPos = wAddGlobalToStack();
        wData[s->stackPos].datatype = W_DATA_ARRAY;
        wData[s->stackPos].value.array = NULL;

    } else {
        /* create as local */
        wCurrentScope->locals++;
        s->stackPos = wCurrentScope->locals;
    }

    return s;
}

/* return pointer to array */
wArray *wGetArray( wSymbol *s )
{
    int stackPos;

    /* position of pointer on stack */
    stackPos = wVarStackPos( s );

    /* verify the type */
    if (wData[stackPos].datatype != W_DATA_ARRAY) {
        wFatal( W_RUNTIME, "getArray: %s is %s, not an Array",
            s->name, wDatumName[wData[stackPos].datatype] );
    }

    return wData[stackPos].value.array;
}


/* get the address of the data element */
int wGetStaticIndex( wArray *array, wSymbol *s )
{
    int     offset;
    int     indexes;
    int     i;
    int     index;
    int     base;

    /* paranoia */
    wMemTest( "getStaticIndex: symbol", s );
    wMemTest( "getStaticIndex: array", array );

    indexes = (int)wPopNumber();
    if (indexes != array->indexes) {
        wFatal( W_RUNTIME, "getStaticIndex: array %s expects %d indexes, not %d",
            s->name, array->indexes, indexes );
    }

    offset = 0;
    for ( i=0; i<indexes; i++ ) {
        index = (int)wPopNumber();
        if (index > array->upper[i]) {
            wFatal( W_RUNTIME, "wGetStaticIndex: index %d of array %s above upper bounds (%d>%d)",
                i+1, s->name, index, array->upper[i] );
    
        } else if (index < array->lower[i]) {
            wFatal( W_RUNTIME, "getStaticIndex: index %d of array %s under lower bounds (%d<%d)",
                i+1, s->name, index, array->lower[i] );
        }

        base = index-(array->lower[i]);
        offset += base * array->offset[i];
    }
    return offset;
}

/* build string key from stack data */
char *wBuildKey( wArray *array, wSymbol *s )
{
    int     args, i, keyLen;
    char    *index, *buffer;

/* FIX: should eventually just realloc when size is exceeded */

    /* create a buffer */
    buffer = (char *)wMalloc( 256 );
    buffer[0] = '\0';

    /* check arg count */
    args = (int)wPopNumber();

    /* there must be at least one index */
    if (args == 0) {
        wFatal( W_RUNTIME, "Array %s[]x expects at least 1 index, not 0" );
    }

    /* build the key backwards, for speed */
    keyLen = 0;
    for ( i = 1; i <= args; i++ ) {

        /* get index */
        index = wPopString();

        /* make sure it fits in the buffer */
        keyLen += strlen( index );
        if (keyLen >= 256) {
            wFatal( W_RUNTIME, "Array key exceeds 256 characters" );
        }

        /* append to key */
        strcat( buffer, index );
        if (i < args) {
            /* add delimiter */
            keyLen += 1;
            if (keyLen >= 256) {
                wFatal( W_RUNTIME, "wArray key exceeds 256 characters" );
            }
            /* replace with ASCII 34 eventually */
            strcat( buffer, "," );
        }
    }

    /* resize the buffer */
    return (char *)wRealloc( buffer, keyLen+1 );
}


/* return the index of cell with key, or -1 */
int wFindKey( wArray *array, wSymbol *s, char *key )
{
    int         hi, lo, mid, c;
    wArrayCell  *cell;

    /* binary search */
    lo = 0;
    hi = array->lower[0]-1;
    while (lo <= hi) {
        mid = floor( (lo + hi) / 2 );
        cell = array->data.cell+mid;

        c = strcmp( key, cell->key );
        if (c < 0) {
            hi = mid - 1;

        } else if (c > 0) {
            lo = mid + 1;

        } else {
            return mid;

        }
    }
    return -1;
}


/* push value of cell onto stack */
void wGetDynamicValue( wArray *array, wSymbol *s )
{
    int         index;
    char        *key;
    wArrayCell  *cell;

    /* create the key */
    key = wBuildKey( array, s );

    /* look for key */
    index = wFindKey( array, s, key );
    wFree( key );

    if (index == -1) {
        /* no item */
        wPushStringCopy("");

    } else {
        /* address of the cell */
        cell = array->data.cell + index;

        wTos++;
        wData[wTos].datatype = cell->data.datatype;

        /* copy data to stack */
        switch (cell->data.datatype) {
        case W_DATA_NUMBER:
            wData[wTos].value.number = cell->data.value.number;
            break;

        case W_DATA_STRING:
            wData[wTos].value.string = wCopyString( cell->data.value.string );
            break;

        default:
            wFatal( W_RUNTIME, "getDynamicElement: Array %s[%s] is corrupt",
                s->name, cell->key );
            break;

        }
    }
}

/* push key of cell onto stack */
int wGetDynamicKey( wArray *array, int index )
{
    wArrayCell  *cell;

    if (index < 0 || index >= array->lower[0]) {
        /* failure */
        return 0;

    } else {
        /* address of the cell */
        cell = array->data.cell + index;

        /* copy string to stack */
        wTos++;
        wData[wTos].datatype = W_DATA_STRING;
        wData[wTos].value.string = wCopyString( cell->key );

        /* success */
        return 1;
    }
}


/* resize array, if needed */
void wResizeDynamicArray( wArray *array )
{
    int         i, oldSize, newSize;

    oldSize = array->upper[0];

    /* out of room? */
    if (array->lower[0] >= oldSize-1) {
    
        /* double space */
        newSize = oldSize * 2;
    
        array->data.cell = (wArrayCell *)wRealloc(
            (void *)(array->data.cell),
            newSize * sizeof(wArrayCell) );

        /* initialize new area */
        for ( i = oldSize; i < newSize; i++ ) {
            array->data.cell[i].key = NULL;
            array->data.cell[i].data.datatype = W_DATA_UNDEFINED;
        }
    
        /* set size */
        array->upper[0] = newSize;

    }
}

/* insert a new cell at location */
void wInsertDynamicCell( wArray *array, int index )
{
    int         usedCells, bytes;
    wArrayCell  *cell;

    /* if needed */
    wResizeDynamicArray( array );

    usedCells = array->lower[0];
    bytes = sizeof( wArrayCell ) * ((usedCells+1) - index);

    /* cell to start move from */
    cell = array->data.cell + index;

    /* move memory, overlapping */
    memmove( (void *)(cell+1), (void *)cell, bytes );

    /* kill prior value */
    cell->key = NULL;
    cell->data.datatype = W_DATA_UNDEFINED;

    /* increment cell count */
    array->lower[0] += 1;

}


/* set cell at index to value on stack */
void wSetDynamicValue( wArray *array, wSymbol *s )
{
    int         index, hi, lo, isNew, c;
    char        *key;
    wVariant    *stackData;
    wArrayCell  *cell;

    /* make sure there is a value to set */
    if (wTos == 0) {
        wFatal( W_RUNTIME, "wSetDynamicValue: stack underflow" );
    }

    /* create the key */
    key = wBuildKey( array, s );

    /* assume it will be a new key */
    isNew = 1;

    /* binary search */
    lo = 0;
    hi = array->lower[0]-1;
    index = 0;
    while (lo <= hi) {
        index = floor((lo + hi) / 2);
        cell = array->data.cell+index;
        c = strcmp( key, cell->key );
        if (c < 0) {
            hi = index - 1;
        } else if (c > 0) {
            lo = index + 1;
        } else {
            /* found prior key */
            isNew = 0;
            break;
        }
    }

    /* no prior key? */
    if (isNew) {
        /* create empty cell */
        index = lo;
        wInsertDynamicCell( array, index );

    }

    /* address of cell */
    cell = array->data.cell + index;

    /* need to set key? */
    if (isNew) {
        /* use key (already unique copy) */
        cell->key = key;
    } else {
        /* don't need key */
        wFree( key );

        /* clean up old value? */
        if (cell->data.datatype == W_DATA_STRING) {
            wFree( cell->data.value.string );
        }

    }

    /* resolve datatype */
    stackData = wGetStackPointer( wTos );
    cell->data.datatype = stackData->datatype;

    if (stackData->datatype == W_DATA_STRING) {
        /* ref? */
        if (wData[wTos].datatype == W_DATA_REF) {
            /* need to make a unique copy */
            cell->data.value.string = wCopyString( stackData->value.string );
        } else {
            /* use directly */
            cell->data.value.string = stackData->value.string;
        }

    } else if (stackData->datatype == W_DATA_NUMBER) {
            cell->data.value.number = stackData->value.number;

    } else {
        /* oops */
        wFatal( W_RUNTIME, "Can't assign %s to a dynamic Array",
            wDatumName[stackData->datatype] );
            
    }
    wTos--;
}



/* put pointer to array element on stack */
void wGetArrayElement( wSymbol *s )
{
    int         index;
    wArray      *array;
    wVariant    *v;

    wMemTest( "wGetArrayElement: symbol", s );
    array = wGetArray( s );

    /* dynamic or static? */
    if (array->isDynamic) {
        wGetDynamicValue( array, s );

    } else {
        /* static array */

        index = wGetStaticIndex( array, s );
        v = array->data.item+index;
        wMemTest( "getArrayElement: array element", v );

        wTos++;
        wData[wTos].datatype = W_DATA_REF;
        wData[wTos].value.ref = v;

    }
}

/* set an item in the array */
void wSetArrayElement( wSymbol *s )
{
    int         offset, type;
    wArray      *array;
    wVariant    *element;

    wMemTest( "wSetArrayElement: symbol", s );

    array = wGetArray( s );
    wMemTest( "wSetArrayElement: array", array );

    if (array->isDynamic) {
        wSetDynamicValue( array, s );

    } else {

/* this should be implemented as a seperate routine */

        offset = wGetStaticIndex( array, s );
        element = array->data.item+offset;
        wMemTest( "wSetArrayElement: array element", element );


        /* need to free string? */
        if (element->datatype == W_DATA_STRING) {
            wFree( element->value.string );
        }
    
        /* get the tos */
        type = wGetStackType( wTos );
        switch (type) {
        case W_DATA_NUMBER:
            element->datatype = W_DATA_NUMBER;
            element->value.number = wPopNumber();
            break;
    
        case W_DATA_STRING:
            element->datatype = W_DATA_STRING;
            element->value.string = wPopString();
            break;
    
        default:
            wFatal( W_RUNTIME, "setArrayElement: can't store %s %s into Array",
                wDatumName[type], s->name );
            break;
        }
    }
}

/* push an array pointer onto the stack */
void wPushArray( wSymbol *s )
{
    int stackPos, type;

    if (wTos == W_STACK_MAX) {
        wFatal( W_RUNTIME, "wPushArray: stack overflow" );
    }

    wTos++;
    stackPos = wVarStackPos( s );
    type = wGetStackType( stackPos );
    if (type != W_DATA_ARRAY) {
        wFatal( W_RUNTIME, "wPushArray: %s %s is not an Array",
            wDatumName[type], s->name );
    }
    wData[wTos].datatype = W_DATA_ARRAY;
    wData[wTos].value.array = wData[stackPos].value.array;
}


/* Returns true if key is in array */
int wInArray( wSymbol *s )
{
    int         index;
    char        *key;
    wArray      *array;

    /* get the array */
    array = wGetArray( s );

    wMemTest( "wInArray: array", array );

    if (!array->isDynamic) {
        wFatal( W_RUNTIME, "%s is a static array", s->name );
    }

    /* get key */
    key = wPopString();
    index = wFindKey( array, s, key );
    wFree( key );

    /* found key? */
    if (index == -1) {
        return 0;
    } else {
        return 1;
    }

}


/* erase a single item from an array */
void wEraseArrayElement( wSymbol *s )
{
    int         index, usedCells, bytes;
    char        *key;
    wArray      *array;
    wArrayCell  *cell;
    wVariant    *element;

    /* get the array */
    array = wGetArray( s );

    wMemTest( "wEraseArrayElement: array", array );

    /* dynamic or static array? */
    if (array->isDynamic) {

        /* get key */
        key = wBuildKey( array, s );
        index = wFindKey( array, s, key );
        wFree( key );

        /* found the key? */
        if (index != -1) {
            /* cell to delete */
            cell = array->data.cell+index;

            /* remove any string data */
            wFree( cell->key );
            if (cell->data.datatype == W_DATA_STRING) {
                wFree( cell->data.value.string );
            }

            /* calculate chunk of memory to move */
            usedCells = array->lower[0];
            bytes = sizeof( wArrayCell ) * ((usedCells) - index);

            /* move memory, overlapping */
            memmove( (void *)(cell), (void *)(cell+1), bytes );

            /* last cell is now redundant */
            cell = array->data.cell+usedCells;

            /* zap prior value */
            cell->key = NULL;
            cell->data.datatype = W_DATA_UNDEFINED;

            /* decrease count */
            (array->lower[0])--;

        }

    } else {

        /* get index */
        index = wGetStaticIndex( array, s );
        element = array->data.item+index;
        wMemTest( "wEraseArrayElement: array element", element );

        /* need to free string? */
        if (element->datatype == W_DATA_STRING) {
            wMemTest( "wEraseArrayElement: array element string", element->value.string );
            wFree( element->value.string );
        }

        /* set to zero */
        element->datatype = W_DATA_NUMBER;
        element->value.number = 0;

    }

}



/* erase an entire array */
void wEraseArray( wSymbol *s )
{
    int         i;
    char        *string;
    wArray      *array;
    wVariant    *item;
    wArrayCell  *cell;

    /* get the array */
    array = wGetArray( s );

    wMemTest( "wEraseArray: array", array );

    /* dynamic or static array? */
    if (array->isDynamic) {

        /* free the strings */
        for ( i = 0; i < array->upper[0]; i++ ) {
            cell = array->data.cell + i;
            wMemTest( "wEraseArray: cell[]", cell );

            /* free the key */
            wFree( cell->key );
            cell->key = NULL;

            /* free the data */
            if (cell->data.datatype == W_DATA_STRING) {
                string = cell->data.value.string;
                if (string != NULL) {
                    wFree( string );
                }
            }
            cell->data.datatype = W_DATA_UNDEFINED;
        }

        /* reset count */
        array->lower[0] = 0;

        /* perhaps this should free allocated memory, too */

    } else {


        /* examine each element */
        for ( i = 0; i < array->elements; i++ ) {
            item = array->data.item+i;
            wMemTest( "wFreeArray: item[]", item );

            /* free the strings */
            if (item->datatype == W_DATA_STRING) {
                string = item->value.string;
                if (string != NULL) {
                    wFree( string );
                }
            }
            /* set element value to zero */
            item->datatype = W_DATA_NUMBER;
            item->value.number = 0;
        }
    }
}


/* free an array, if local to routine */
void wFreeArray( wArray *array )
{
    int         i;
    char        *string;
    wVariant    *item;
    wArrayCell  *cell;

    wMemTest( "wFreeArray: array", array );

    /* dynamic or static array? */
    if (array->isDynamic) {

        /* free the strings */
        for ( i = 0; i < array->upper[0]; i++ ) {
            cell = array->data.cell + i;
            wMemTest( "wFreeArray: cell[]", cell );

            /* free the key */
            wFree( cell->key );
            if (cell->data.datatype == W_DATA_STRING) {
                string = cell->data.value.string;
                if (string != NULL) {
                    wFree( string );
                }
            }
        }

    } else {

        /* free the strings */
        for ( i = 0; i < array->elements; i++ ) {
            item = array->data.item+i;
            wMemTest( "wFreeArray: item[]", item );
            if (item->datatype == W_DATA_STRING) {
                string = item->value.string;
                if (string != NULL) {
                    wFree( string );
                }
            }
        }
    }
    wFree( array );
}

/* return number of indexes */
int wGetArrayIndexes()
{
    int     datatype;
    wArray  *array;

    datatype = wData[wTos].datatype;
    if (datatype != W_DATA_ARRAY) {
        wFatal( W_RUNTIME, "First argument must be an Array, not %s",
            wDatumName[datatype] );
    }

    array = wData[wTos].value.array;

    if (array->isDynamic) {
        return 1;
    } else {
        return array->indexes;
    }
}


/* return upper bound of index */
int wGetArrayBound( int index, int upper )
{
    int     datatype;
    wArray  *array;

    datatype = wData[wTos].datatype;
    if (datatype != W_DATA_ARRAY) {
        wFatal( W_RUNTIME, "First argument must be an Array, not %s",
            wDatumName[datatype] );
    }

    array = wData[wTos].value.array;

    /* dynamic array? */
    if (array->isDynamic) {
        if (index < 1 || index > 1) {
            wFatal( W_RUNTIME, "Subscript %d out of range", index );
        }
        if (upper) {
            /* used count stored in lower bound */
            return array->lower[index-1];
        } else {
            return 1;
        }
    }

    if (index < 1 || index > array->indexes) {
        wFatal( W_RUNTIME, "Subscript %d out of range", index );
    }

    if (upper) {
        return array->upper[index-1];
    } else {
        return array->lower[index-1];
    }
}
