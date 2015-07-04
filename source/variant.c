/*************************************************************
    Name:       variant.c
    Purpose:    implementation of datatypes for wxBasic
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/

/* initialize the variant handlers */
void wVariantInit()
{
    int i, classIndex;
    wSymbol *baseClass;
    
    /* allocate space for the variant handlers */
    for ( i = 0; i < W_VARIANT_MAX; i++ ) {
        /* FIXME: this should NULL them out, too */
        wTheHandler[i] = (wVariantHandler *)wMalloc( sizeof( wVariantHandler ) );
    }

    /* set up the classes to inherit from Variant */
    baseClass = wWrapClass( W_SYM_ISNATIVE, NULL, "variant" );
    wTheHandler[W_TYPE_VARIANT]->klass  = baseClass;
    wTheHandler[W_TYPE_NOTHING]->klass  = wWrapClass( W_SYM_ISNATIVE, baseClass, "nil" );
    wTheHandler[W_TYPE_INTEGER]->klass  = wWrapClass( W_SYM_ISNATIVE, baseClass, "integer" );
    wTheHandler[W_TYPE_NUMBER]->klass  = wWrapClass( W_SYM_ISNATIVE, baseClass, "number" );
    wTheHandler[W_TYPE_STRING]->klass  = wWrapClass( W_SYM_ISNATIVE, baseClass, "string" );
    wTheHandler[W_TYPE_OBJECT]->klass  = wWrapClass( W_SYM_ISNATIVE, baseClass, "object" );
    wTheHandler[W_TYPE_ARRAY]->klass  = wWrapClass( W_SYM_ISNATIVE, baseClass, "array" );
    wTheHandler[W_TYPE_TABLE]->klass  = wWrapClass( W_SYM_ISNATIVE, baseClass, "table" );
    wTheHandler[W_TYPE_LIST]->klass  = wWrapClass( W_SYM_ISNATIVE, baseClass, "list" );
    wTheHandler[W_TYPE_VARPTR]->klass  = wWrapClass( W_SYM_ISNATIVE, baseClass, "varptr" );
    wTheHandler[W_TYPE_ROUTINE]->klass  = wWrapClass( W_SYM_ISNATIVE, baseClass, "routine" );
    wTheHandler[W_TYPE_DATETIME]->klass  = wWrapClass( W_SYM_ISNATIVE, baseClass, "datetime" );

    /* for converting class back to type */
    for ( i = W_TYPE_VARIANT; i <= W_TYPE_DATETIME; i++ ) {
        classIndex = wTheHandler[i]->klass->index;
        wTheClassIndexToDataType[classIndex] = i;
    }

    /* store index of last builtin type for type checking */
    wTheLastBuiltinTypeIndex = wTheHandler[W_TYPE_DATETIME]->klass->index;

    /* set up the datatype handlers */
    wNothingRegisterMethods();
    wIntegerRegisterMethods();
    wNumberRegisterMethods();
    wStringRegisterMethods();
    wDateTimeRegisterMethods();
    wObjectRegisterMethods();
    wRoutineRegisterMethods();
    wArrayRegisterMethods();
    wTableRegisterMethods();
    wListRegisterMethods();
    wVarPtrRegisterMethods();

    // default methods
    wVariantAddMethod( W_TYPE_VARIANT, "gettype", wVariantMethodGetType, 0, 0 );
    wVariantAddMethod( W_TYPE_VARIANT, "tostring", wVariantMethodToString, 0, 0 );
    wVariantAddMethod( W_TYPE_VARIANT, "equal", wVariantMethodEqual, 1, 0 );
    wVariantAddMethod( W_TYPE_VARIANT, "compare", wVariantMethodCompare, 1, 0 );
    wVariantAddMethod( W_TYPE_VARIANT, "istrue", wVariantMethodIsTrue, 0, 0 );
    wVariantAddMethod( W_TYPE_VARIANT, "append", wVariantMethodAppend, 1, 0 );
    wVariantAddMethod( W_TYPE_VARIANT, "prepend", wVariantMethodPrepend, 1, 0 );
    wVariantAddMethod( W_TYPE_VARIANT, "clone", wVariantMethodClone, 0, 0 );
    wVariantAddMethod( W_TYPE_VARIANT, "count", wVariantMethodCount, 0, 0 );
    wVariantAddMethod( W_TYPE_VARIANT, "length", wVariantMethodCount, 0, 0 );
    wVariantAddMethod( W_TYPE_VARIANT, "isnumeric", wVariantMethodIsNumeric, 0, 0 );

}


void wVariantAddMethod( int dataType, char *method, void (*routine)(void), int reqCount, int optCount )
{
    wWrapMethod( 0, wTheHandler[dataType]->klass, method, routine, reqCount, optCount );
}

wVariant *wVariantNew()
{
    wVariant *variant;

	/* allocate memory */
    variant = (wVariant *)wMalloc( sizeof( wVariant ) );

	/* default value is NOTHING */
    variant->dataType = W_TYPE_NOTHING;

    return variant;
}


/* reference count a variant */
void wVariantRef( wVariant *src )
{    
	int myDataType;

    wMemTest( src, "wVariantRef:src" );

	/* get the datatype */
	myDataType = src->dataType;

	/* does this datatype support the ref method? */
    if (wTheHandler[myDataType]->ref) {
		/* call the ref method */
		(*(wTheHandler[myDataType]->ref))( src );
	}

}

/* dereference a variant */
void wVariantDeref( wVariant *src )
{    
	int myDataType;
    wMemTest( src, "wVariantDeref:src" );

	/* get the datatype */
	myDataType = src->dataType;

	/* does this datatype support the deref method? */
    if (wTheHandler[myDataType]->deref) {
		/* call the deref method */
		(*(wTheHandler[myDataType]->deref))( src );
	}

    /* set to NOTHING */
    src->dataType = W_TYPE_NOTHING;
}


/* copy from source to destination variant */
void wVariantCopy( wVariant *dst, wVariant *src )
{    

    /* Note: This differs from wVariantMove in that it refcounts   */
    /*        and doesn't clear the source.                        */
	wMemTest( src, "wVariantCopy:src" );
    wMemTest( dst, "wVariantCopy:dst" );

    /* make sure destination is clean */
    wVariantDeref( dst );

    /* copy datatype */
    dst->dataType = src->dataType;

	/* does this datatypehave a copy method? */
    if (wTheHandler[(src->dataType)]->copy) {
		/* call the copy method */
		(*(wTheHandler[(src->dataType)]->copy))( dst, src );
	}

	/* refcount the source */
	wVariantRef( src );
	
}


/* clone from source to destination variant */
void wVariantClone( wVariant *dst, wVariant *src )
{    

    /* for simple datatypes, it's the same as the copy operation */
	wMemTest( src, "wVariantClone:src" );
    wMemTest( dst, "wVariantClone:dst" );

    /* the dest is deref'ed in the clone operation */

	/* does this datatypehave a clone method? */
    if (wTheHandler[(src->dataType)]->clone) {
		/* call the clone method */
		(*(wTheHandler[(src->dataType)]->clone))( dst, src );
    } else {
        /* throw an error */
        wErrorThrow( W_ERROR_CONVERT, "Can't clone %s", wDataTypeName[src->dataType] );
    }
}


/* move source to destination, and set source to nothing */
void wVariantMove( wVariant *dst, wVariant *src )
{    
	wMemTest( src, "wVariantCopy:src" );
    wMemTest( dst, "wVariantCopy:dst" );

    /* make sure destination is clean */
    wVariantDeref( dst );


	/* does this datatypehave a copy method? */
    if (wTheHandler[src->dataType]->copy) {
        /* copy datatype */
        dst->dataType = src->dataType;

		/* call the copy method */
		(*(wTheHandler[src->dataType]->copy))( dst, src );

    } else {
        /* throw an error */
        wErrorThrow( W_ERROR_CONVERT, "Can't copy %s", wDataTypeName[src->dataType] );
    }
	
	/* zap datatype */
	src->dataType = W_TYPE_NOTHING;
}


/* coerce src into the given datatype */
void wVariantCoerce( wVariant *variant, int coerceTo )
{

    // FIXME: this should return a boolean result, so routines
    // that call it can check the return value and exit in case
    // of an error.

    int coerceFrom;
	char *buffer;
	wNumber n;

    wMemTest( variant, "wVariantCoerce:variant" );

    /* what type of value? */
    coerceFrom = variant->dataType;

	/* check to see if it's already of the given type */
    if (coerceFrom == coerceTo) {
		return;
	}

	/* can this be converted to a number? */
    if (wTheHandler[coerceFrom]->isNumeric
    && wTheHandler[coerceTo]->isNumeric) {

	    /* get the numeric value */
        n = (*(wTheHandler[coerceFrom]->toNumber))(variant);
        
        /* store the data as the new type */
        (*(wTheHandler[coerceTo]->fromNumber))(variant, n );

        /* set the new datatype */
        variant->dataType = coerceTo;

    /* convert to char, and then to native type */
    } else if (wTheHandler[coerceFrom]->toChar
            && wTheHandler[coerceTo]->fromChar) {

    	/* get a buffer representing the value as text */
        buffer = wVariantToChar( variant, W_FALSE, 0 );

        /* deref the original value */
        wVariantDeref( variant );

    	/* convert the char string to the native datatype */
        wVariantFromChar( variant, buffer, coerceFrom, coerceTo );
	    
	    /* free the buffer */
	    wFree( buffer );
	    
    } else {
   	    /* throw an error */
   	    wErrorThrow( W_ERROR_CONVERT, "Can't convert %s to %s ",
            wDataTypeName[coerceFrom], wDataTypeName[coerceTo] );
    }

}

/* compare one variant to another */
int wVariantCompare( wVariant *v1, wVariant *v2 )
{
	wNumber n1, n2;

    wMemTest( v1, "wVariantCompare:v1" );
    wMemTest( v2, "wVariantCompare:v2" );

	/* are they both numeric? */
	if (wTheHandler[v1->dataType]->isNumeric
    && wTheHandler[v2->dataType]->isNumeric) {
	    n1 = (*(wTheHandler[v1->dataType]->toNumber))( v1 );
        n2 = (*(wTheHandler[v2->dataType]->toNumber))( v2 );
        return wNumberCompareNumbers( n1, n2 );
     }

    /* different types? */
    if (v1->dataType != v2->dataType) {
        /* throw an error */
        wErrorThrow( W_ERROR_CONVERT, "Can't perform inequality test on %s against %s",
            wDataTypeName[v1->dataType], wDataTypeName[v2->dataType] );
    }

    /* make sure there is a convert to native method */ 
    if (!wTheHandler[v1->dataType]->compare) {
        wErrorThrow( W_ERROR_CONVERT, "Can't perform inequality test on %s",
            wDataTypeName[v1->dataType] );
    }

    /* compare */
    return (*(wTheHandler[v1->dataType]->compare))( v1, v2 );
}


/* equality test */
int wVariantEqual( wVariant *v1, wVariant *v2 )
{
	int result;
    wVariant *v;
    wNumber n1, n2;

    wMemTest( v1, "wVariantEqual:v1" );
    wMemTest( v2, "wVariantEqual:v2" );

	/* are they of the same type? */
	if (v1->dataType == v2->dataType) {

		/* is there an equal method? */
        if (wTheHandler[v1->dataType]->equal) {
			return (*(wTheHandler[v1->dataType]->equal))( v1, v2 );
		}
	}

	/* are they both numeric? */
	if (wTheHandler[v1->dataType]->isNumeric
    && wTheHandler[v2->dataType]->isNumeric) {

	    n1 = (*(wTheHandler[v1->dataType]->toNumber))( v1 );
        n2 = (*(wTheHandler[v2->dataType]->toNumber))( v2 );

        return (wNumberCompareNumbers( n1, n2 ) == 0);
     }

    /* not equal */
    return W_FALSE;
}


/* truth test */
int wVariantIsTrue( wVariant *src )
{
    wMemTest( src, "wVariantIsTrue:src" );

    /* isTrue routine exists? */
    if (wTheHandler[src->dataType]->isTrue) {
        /* call it */
        return (*(wTheHandler[src->dataType]->isTrue))( src );

    } else {
        /* true if non-zero */
        return (wVariantGetNumber( src ) != (wNumber)0.0);
    }
}



/* convert variant to a number */
wNumber wVariantGetNumber( wVariant *src )
{   
	wNumber result;
    wVariant *v;

    wMemTest( src, "wVariantGetNumber:src" );

	/* is there a toNumber method? */
    if (wTheHandler[src->dataType]->toNumber) {
		/* use toNumber method */
		return (*(wTheHandler[src->dataType]->toNumber))( src );
	}

    /* allocate space */
    v = (wVariant *)wMalloc( sizeof( wVariant ) );

	/* create a copy of the variant */
    v->dataType = W_TYPE_NOTHING;
    wVariantCopy( v, src );

	/* coerce to number */
    wVariantCoerce( v, W_TYPE_NUMBER );

	/* get the result */
    result = v->value.number;

    /* free the temp */
    wFree( v );

    return result;

}


/* return char pointer from string */
char *wVariantToChar( wVariant *src, int useQuotes, int limit )
{
    char* (*toCharRoutine)(wVariant*, int, int);

    wMemTest( src, "wVariantToChar:src" );

    /* make sure the routine exists */
    if (!wTheHandler[src->dataType]->toChar) {
        wErrorThrow( W_ERROR_CONVERT, "%s has no ToChar routine",  wDataTypeName[src->dataType] );
        return wCharCopy( "" );
    }

    /* convert the data to a string */
    toCharRoutine = *(wTheHandler[src->dataType]->toChar);
    return toCharRoutine( src, useQuotes, limit );
}


/* create a native datatype from string */
void wVariantFromChar( wVariant *dst, char *buffer, int coerceFrom, int coerceTo )
{
    wMemTest( dst, "wVariantFromChar:dst" );

    /* deref the destination */
    wVariantDeref( dst );

    /* no converter? */
    if (!wTheHandler[coerceTo]->fromChar) {
   	    /* throw an error */
        wErrorThrow( W_ERROR_CONVERT, "Can't convert %s to %s ",
            wDataTypeName[coerceFrom], wDataTypeName[coerceTo] );
    }

	/* convert the data */
	if (!(*(wTheHandler[coerceTo]->fromChar))( dst, buffer )) {
	   /* deref just in case */
	   wVariantDeref( dst );

	   /* throw an error */
        wErrorThrow( W_ERROR_CONVERT, "Can't convert %s to %s ",
            wDataTypeName[coerceFrom], wDataTypeName[coerceTo] );
    }

    /* set the new datatype */
    dst->dataType = coerceTo;

}



/* print a value to a file */
void wVariantFilePrint( FILE *theFile, wVariant *src, int showQuotes )
{
	char *buffer;

    wMemTest( src, "wVariantPrint:src" );

	/* convert to char */
    buffer = wVariantToChar( src, showQuotes, 0 );

	/* print */
    if (theFile) {
        fprintf( theFile, "%s", buffer );
    } else {
        wConsolePrint( buffer );
    }

	/* free the buffer */
	wFree( buffer );
}


/* print a value to stdout */
void wVariantPrint( wVariant *v, int showQuotes )
{
    wVariantFilePrint( NULL, v, showQuotes );
}

/* return the variant pointed to by the key, or NULL */
wVariant *wVariantFindKey( wVariant *src, int indexCount )
{
    // FIXME: this should be coded at some point
    return NULL;
}

/* like findKey, but adds key if it doesn't exist */
wVariant *wVariantAddKey( wVariant *src, int indexCount )
{
    // FIXME: this should be coded at some point
    return NULL;
}	


/* ensure the arg count matches the expected number */
void wVariantMethodCheckArgs( char *name, int expect, int actual )
{
    if (expect != actual) {
        wErrorThrow( W_ERROR_ARGS, "The method %s expects %d arguments, not %d",
            name, expect, actual );
    }
}

/* return pointer to value indexed in collection */
wVariant *wVariantIndex( wVariant *vSrc, int indexCount )
{
    /* make sure the routine exists */
    if (!wTheHandler[vSrc->dataType]->index) {
        wErrorThrow( W_ERROR_INDEX, "Can't index %s",  wDataTypeName[vSrc->dataType] );
        return NULL;
    }

    /* call the handler, return a pointer */
    return (*(wTheHandler[vSrc->dataType]->index))( vSrc, indexCount );

}

wVariant *wVariantFind( wVariant *vSrc, wVariant *key )
{
    /* make sure the routine exists */
    if (!wTheHandler[vSrc->dataType]->find ) {
        wErrorThrow( W_ERROR_INDEX, "Can't find in %s",  wDataTypeName[vSrc->dataType] );
        return NULL;
    }

    /* call the handler, return a pointer */
    return (*(wTheHandler[vSrc->dataType]->find))( vSrc, key );

}

void wVariantInsert( wVariant *vSrc, wVariant *key, wVariant *value )
{
    /* make sure the routine exists */
    if (!wTheHandler[vSrc->dataType]->insert) {
        wErrorThrow( W_ERROR_INDEX, "Can't insert into %s",  wDataTypeName[vSrc->dataType] );
        return;
    }

    /* call the handler */
    (*(wTheHandler[vSrc->dataType]->insert))( vSrc, key, value );

}

/* iterate through a collection, return TRUE if there is another item */
int wVariantIterate( wVariant *vSrc, wVariant *vIndex, wVariant *vArg1, wVariant *vArg2 )
{
    /* make sure the routine exists */
    if (!wTheHandler[vSrc->dataType]->iterate) {
        wErrorThrow( W_ERROR_INDEX, "Can't iterate through a %s",  wDataTypeName[vSrc->dataType] );
        return 0;
    }
    /* call the handler */
    return (*(wTheHandler[vSrc->dataType]->iterate))( vSrc, vIndex, vArg1, vArg2 );

}

void wVariantSlice( wVariant *vDst, wVariant *vSrc, int startOf, int endOf )
{
    /* make sure the routine exists */
    if (!wTheHandler[vSrc->dataType]->slice) {
        wErrorThrow( W_ERROR_INDEX, "Can't slice %s",  wDataTypeName[vSrc->dataType] );
        return;
    }

    /* call the handler */
    (*(wTheHandler[vSrc->dataType]->slice))( vDst, vSrc, startOf, endOf );

}

void wVariantAppend( wVariant *vDst, wVariant *value )
{
    /* make sure the routine exists */
    if (!wTheHandler[vDst->dataType]->append) {
        wErrorThrow( W_ERROR_INDEX, "Can't append %s",  wDataTypeName[vDst->dataType] );
        return;
    }

    /* call the handler */
    (*(wTheHandler[vDst->dataType]->append))( vDst, value );

}

void wVariantPrepend( wVariant *vDst, wVariant *value )
{
    /* make sure the routine exists */
    if (!wTheHandler[vDst->dataType]->prepend) {
        wErrorThrow( W_ERROR_INDEX, "Can't prepend %s",  wDataTypeName[vDst->dataType] );
        return;
    }

    /* call the handler */
    (*(wTheHandler[vDst->dataType]->prepend))( vDst, value );

}


int wVariantCount( wVariant *vSrc )
{
    /* make sure the routine exists */
    if (!wTheHandler[vSrc->dataType]->count) {
        wErrorThrow( W_ERROR_INDEX, "Can't count %s",  wDataTypeName[vSrc->dataType] );
    }

    /* call the handler */
    return (*(wTheHandler[vSrc->dataType]->count))( vSrc );

}


/******************/
/* Shared Methods */
/******************/

/* return the variant's type, as a string */
void wVariantMethodGetType()
{
    /* push string onto stack */
    wStackPushChar( wDataTypeName[ wTheCall->vSelf->dataType ], W_TRUE );
}

/* convert the variant's value to a string */
void wVariantMethodToString()
{
    char *buffer;

    /* convert it to a string */
    buffer = wVariantToChar( wTheCall->vSelf, W_FALSE, 0 );

    /* push "raw" string onto stack */
    wStackPushChar( buffer, W_FALSE );

    /* free the buffer */
    wFree( buffer );
}

/* test a variant for equality with another */
void wVariantMethodEqual()
{
    int         result;
    wVariant    *v1;

    /* get the arg */
    v1 = wStackPop();

    /* equality test */
    result = wVariantEqual( wTheCall->vSelf, v1 );

    /* deref the value */
    wVariantDeref( v1 );

    /* push the result */
    wStackPushNumber( (wNumber)result );
}

/* compare a variant with another */
void wVariantMethodCompare()
{
    int         result;
    wVariant    *v1;

    /* get the arg */
    v1 = wStackPop();

    /* compare */
    result = wVariantCompare( wTheCall->vSelf, v1 );

    /* deref the value */
    wVariantDeref( v1 );

    /* push the result */
    wStackPushNumber( (wNumber)result );
}


/* test a variant for truth */
void wVariantMethodIsTrue()
{
    int         result;

    /* test */
    wStackPushNumber( wVariantIsTrue( wTheCall->vSelf ) );
}

/* append a value to a variant */
void wVariantMethodAppend()
{
    int         result;
    wVariant    *v1;

    /* get the arg */
    v1 = wStackPop();

    /* append */
    wVariantAppend( wTheCall->vSelf, v1 );

    /* deref the value */
    // wVariantDeref( v1 );

}

/* prepend a value to a variant */
void wVariantMethodPrepend()
{
    int         result;
    wVariant    *v1;

    /* get the arg */
    v1 = wStackPop();

    /* append */
    wVariantPrepend( wTheCall->vSelf, v1 );

    /* deref the value */
    wVariantDeref( v1 );

}


/* clone a variant */
void wVariantMethodClone()
{
    wVariant    *v1;

    /* push the destination */
    v1 = wStackPushNothing();

    /* clone the source */
    wVariantClone( v1, wTheCall->vSelf );
}


/* return the count of a variant */
void wVariantMethodCount()
{
    /* FIXME: this shouldn't be defined at this level */
    /* push the count onto the stack */
    wStackPushNumber( (wNumber)wVariantCount(wTheCall->vSelf) );
}

/* return true if datatype is numeric */
void wVariantMethodIsNumeric()
{
    int dataType = wTheCall->vSelf->dataType;
    wStackPushNumber( (wNumber)wTheHandler[dataType]->isNumeric );
}
