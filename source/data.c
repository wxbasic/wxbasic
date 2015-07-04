/*************************************************************
    Name:       data.c
    Purpose:    implementation of datatypes for wxBasic
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/

wVariant *wVariantNew()
{
    wVariant *variant;

    variant = (wVariant *)wMalloc( sizeof( wVariant ) );
    variant->dataType = W_TYPE_NOTHING;
    return variant;
}

/* reference count a variant */
void wVariantRef( wVariant *src )
{    

    wMemTest( src, "wVariantRef:src" );

    /* what sort of value? */
    switch (src->dataType) {
    case W_TYPE_NOTHING:
    case W_TYPE_INTEGER:
    case W_TYPE_NUMBER:
    case W_TYPE_ROUTINE:
    case W_TYPE_DATETIME:
        /* nothing to do */
        break;

    case W_TYPE_STRING:
        wMemTest( src->value.string, "wVariantRef:src->value.string" );
        src->value.string->refCount++;
        break;

    case W_TYPE_OBJECT:
        wMemTest( src->value.object, "wVariantRef:src->value.object" );
        src->value.object->refCount++;
        break;

    case W_TYPE_ARRAY:
        wMemTest( src->value.array, "wVariantRef:src->value.array" );
        src->value.array->refCount++;
        break;

    case W_TYPE_TABLE:
        wMemTest( src->value.table, "wVariantRef:src->value.table" );
        src->value.table->refCount++;
        break;

    case W_TYPE_LIST:
        wMemTest( src->value.list, "wVariantRef:src->value.list" );
        src->value.list->refCount++;
        break;

    case W_TYPE_VARPTR:
        wVariantRef( src->value.varptr );
        break;

    default:
        wErrorFatal( "Unknown datatype %d (wVariantRef)", src->dataType );
        wErrorSet( W_ERROR_INTERNAL );
        break;
        
    }

}


/* dereference value, free variable */
inline void wVariantDeref( wVariant *variant )
{
    int i, count;
    wGrow *g;

    wMemTest( variant, "wVariantDeref:variant" );

    switch (variant->dataType) {
    case W_TYPE_NOTHING:
    case W_TYPE_INTEGER:
    case W_TYPE_NUMBER:
    case W_TYPE_ROUTINE:
    case W_TYPE_DATETIME:
        /* nothing to do */
        break;
            
    case W_TYPE_STRING:
        wStringDeref( variant );
        break;

    case W_TYPE_OBJECT:
        wMemTest( variant->value.object, "wVariantDeref:variant->value.object" );
        wObjectDeref( variant->value.object );
        break;
        
    case W_TYPE_ARRAY:
        wMemTest( variant->value.array, "wVariantDeref:variant->value.array" );
        wArrayDeref( variant->value.array );
        break;

    case W_TYPE_TABLE:
        wMemTest( variant->value.table, "wVariantDeref:variant->value.table" );
        wTableDeref( variant->value.table );
        break;
		
    case W_TYPE_LIST:
        wMemTest( variant->value.list, "wVariantDeref:variant->value.list" );
        wListDeref( variant->value.list );
        break;

    case W_TYPE_VARPTR:
        wVariantDeref( variant->value.varptr );
        break;


    default:
        wErrorFatal( "Unknown datatype %d (wVariantDeref)", variant->dataType );
        wErrorSet( W_ERROR_INTERNAL );
        break;
        
    }
	
    /* mark as undefined */
    variant->dataType = W_TYPE_NOTHING;
}


/* copy from source to destination variant */
void wVariantCopy( wVariant *dst, wVariant *src )
{    

    wMemTest( src, "wVariantCopy:src" );
    wMemTest( dst, "wVariantCopy:dst" );

    /* make sure destination is clean */
    wVariantDeref( dst );

    /* copy datatype */
    dst->dataType = src->dataType;

    /* copy value */
    switch (src->dataType) {
    case W_TYPE_NOTHING:
        // wErrorFatal( "Can't assign an undefined value (wVariantCopy)" );
        break;

    case W_TYPE_INTEGER:
        dst->value.integer = src->value.integer;
        break;

    case W_TYPE_NUMBER:        
        dst->value.number = src->value.number;
        break;
    
    case W_TYPE_STRING:
        wMemTest( src->value.string, "wVariantCopy:src->value.string" );
        dst->value.string = src->value.string;
        dst->value.string->refCount++;
        break;

    case W_TYPE_OBJECT:
        wMemTest( src->value.object, "wVariantCopy:src->value.object" );
        dst->value.object = src->value.object;
        dst->value.object->refCount++;
        break;

    case W_TYPE_ARRAY:
        wMemTest( src->value.array, "wVariantCopy:src->value.array" );
        dst->value.array = src->value.array;
        dst->value.array->refCount++;
        break;

    case W_TYPE_TABLE:
        wMemTest( src->value.table, "wVariantCopy:src->value.table" );
        dst->value.table = src->value.table;
        dst->value.table->refCount++;
        break;

    case W_TYPE_LIST:
        wMemTest( src->value.list, "wVariantCopy:src->value.list" );
        dst->value.list = src->value.list;
        dst->value.list->refCount++;
        break;

    case W_TYPE_VARPTR:
        wMemTest( src->value.varptr, "wVariantCopy:src->value.varptr" );
        wVariantRef( src->value.varptr );
        dst->value.varptr = src->value.varptr;
        break;

    case W_TYPE_ROUTINE:
        wMemTest( src->value.routine, "wVariantCopy:src->value.routine" );
        dst->value.routine = src->value.routine;
        break;

    case W_TYPE_DATETIME:
        dst->value.time = src->value.time;
        break;

    default:
        wErrorFatal( "Unknown datatype %d (wVariantCopy)", src->dataType );
        wErrorSet( W_ERROR_INTERNAL );
        break;
        
    }

}


/* same as wVariantCopy, but no refcount modifications */
void wVariantMove( wVariant *dst, wVariant *src )
{    
    wMemTest( src, "wVariantMove:src" );
    wMemTest( dst, "wVariantMove:dst" );

    /* make sure destination is clean */
    wVariantDeref( dst );

    /* copy datatype */
    dst->dataType = src->dataType;

    /* copy value */
    switch (src->dataType) {
    case W_TYPE_NOTHING:
        break;

    case W_TYPE_INTEGER:
        dst->value.integer = src->value.integer;
        break;

    case W_TYPE_NUMBER:        
        dst->value.number = src->value.number;
        break;
    
    case W_TYPE_STRING:
        wMemTest( src->value.string, "wVariantMove:src->value.string" );
        dst->value.string = src->value.string;
        break;

    case W_TYPE_OBJECT:
        wMemTest( src->value.object, "wVariantMove:src->value.object" );
        dst->value.object = src->value.object;
        break;

    case W_TYPE_ARRAY:
        wMemTest( src->value.array, "wVariantMove:src->value.array" );
        dst->value.array = src->value.array;
        break;

    case W_TYPE_TABLE:
        wMemTest( src->value.table, "wVariantMove:src->value.table" );
        dst->value.table = src->value.table;
        break;

    case W_TYPE_LIST:
        wMemTest( src->value.varptr, "wVariantCopy:src->value.varptr" );
        dst->value.varptr = src->value.varptr;
        break;

    case W_TYPE_DATETIME:
        dst->value.time = src->value.time;
        break;

    default:
        wErrorFatal( "Unknown datatype %d (wVariantCopy)", src->dataType );
        wErrorSet( W_ERROR_INTERNAL );
        break;
        
    }

    src->dataType = W_TYPE_NOTHING;

}



/* coerce src into the given datatype */
void wVariantCoerce( wVariant *variant, int dataType )
{
    time_t t;
    wNumber n;
	char *buffer;

    wMemTest( variant, "wVariantCoerce:variant" );

	/* this shouldn't happen - only call if need to convert */
    if (variant->dataType == dataType) {
		return;
	}

    /* DEBUGGING: Make sure INTEGER types don't slip through...
    printf("wVariantCoerce: convert a %s to a %s\n",
        wDatatypeName[variant->dataType],
        wDatatypeName[dataType] );
    */

    /* what type of value? */
    if (variant->dataType == W_TYPE_NUMBER
    &&  dataType == W_TYPE_STRING ) {
		/* convert to text */
        buffer = wNumberFormat( variant->value.number );

        /* create a new string */
        wStringNew( variant, buffer, -1 );

        /* free the buffer */
        wFree( buffer );

    } else if (variant->dataType == W_TYPE_STRING
           &&  dataType == W_TYPE_DATETIME ) {
        /* get the string char data */
        buffer = wVariantGetStringChar( variant );

        /* convert to time */
        t = wDateTimeParse( buffer );

        /* release the string */
        wVariantDeref( variant );
        
        /* make it a time */
        variant->dataType = W_TYPE_DATETIME;
        variant->value.time = t;

    } else if (variant->dataType == W_TYPE_STRING
           &&  dataType == W_TYPE_NUMBER ) {

		/* make it a number */
        n = wStringToNumber( variant );
        wVariantDeref( variant );
        variant->dataType = W_TYPE_NUMBER;
        variant->value.number = n;

    } else if (variant->dataType == W_TYPE_DATETIME
           &&  dataType == W_TYPE_STRING) {
        /* format the time */
        buffer = wDateTimeFormat( "%c", variant->value.time );

        /* create a new string */
        wStringNew( variant, buffer, -1 );

        /* free the buffer */
        wFree( buffer );

	} else {
        wErrorFatal( "Can't convert %s to %s",
            wDatatypeName[variant->dataType],
            wDatatypeName[dataType] );
        wErrorSet( W_ERROR_CONVERT );
	}

}


/* compare one variant to another */
int wVariantCompare( wVariant *v1, wVariant *v2 )
{
	int result;
    wVariant *v;

    wMemTest( v1, "wVariantCompare:v1" );
    wMemTest( v2, "wVariantCompare:v2" );

	/* FIXME: This should be made more efficient */

    /* undefined is a special case */
    if (v1->dataType == W_TYPE_NOTHING || v2->dataType == W_TYPE_NOTHING) {
        if (v1->dataType == v2->dataType) {
            return 0;
        } else if (v1->dataType == W_TYPE_NOTHING) {
            return 1;
        } else {
            return -1;
        }
    }

	/* need to coerce? */
    if (v1->dataType != v2->dataType) {

        /* allocate memory for the variant */
        v = (wVariant *)wMalloc( sizeof( wVariant ) );

		/* attempt to coerce */
        wVariantCopy( v, v1 );
        wVariantCoerce( v, v2->dataType );

        switch (v->dataType) {
		case W_TYPE_NUMBER:
            result = wNumberCompare( v->value.number, v2->value.number );
			break;
		
		case W_TYPE_STRING:
            wMemTest( v->value.string, "wVariantCompare:v->value.string" );
            wMemTest( v2->value.string, "wVariantCompare:v2->value.string" );
            result = wStringCompare( v->value.string, v2->value.string );
			
			/* dereference */
            wVariantDeref( v );
			break;
		
		default:
            wErrorFatal( "Can't coerce datatypes (wVariantCompare)" );
            wErrorSet( W_ERROR_CONVERT );
			break;
		}

        /* release the variant */
        wFree( v );
		
	} else {
		
        switch (v1->dataType) {
		case W_TYPE_NUMBER:
            result = wNumberCompare( v1->value.number, v2->value.number );              
			break;
		
		case W_TYPE_STRING:
            wMemTest( v1->value.string, "wVariantCompare:v1->value.string" );
            wMemTest( v2->value.string, "wVariantCompare:v2->value.string" );
            result = wStringCompare( v1->value.string, v2->value.string );
			break;

        case W_TYPE_DATETIME:
            result = (int)difftime( v1->value.time, v2->value.time );
            break;

		default:
            wErrorFatal( "Can't coerce datatypes (wVariantCompare)" );
            wErrorSet( W_ERROR_CONVERT );
			break;
		}

	}

	return result;
	
}

/* convert variant to a number */
wNumber wVariantGetNumber( wVariant *variant )
{    

    wMemTest( variant, "wVariantGetNumber:variant" );

    switch (variant->dataType) {
    case W_TYPE_NOTHING:
        wErrorFatal( "Can't convert nothing into a number (wNumberGet)" );
        wErrorSet( W_ERROR_CONVERT );
        
    case W_TYPE_NUMBER:
        return variant->value.number;
        /* break; */
        
    case W_TYPE_STRING:
        return wStringToNumber( variant );
        /* break; */
        
    case W_TYPE_OBJECT:
    case W_TYPE_ARRAY:
    case W_TYPE_TABLE:
    case W_TYPE_LIST:
    case W_TYPE_VARPTR:
    case W_TYPE_ROUTINE:
    case W_TYPE_DATETIME:
        wErrorFatal( "Can't convert %s into a number",
            wDatatypeName[variant->dataType] );
        wErrorSet( W_ERROR_CONVERT );
        break;

    default:
        wErrorFatal( "Unknown datatype %d (wNumberGet)", variant->dataType );
        wErrorSet( W_ERROR_INTERNAL );
        break;        
    }

    /* default value */
    return (wNumber)0;
}


/* return char pointer from string */
char *wVariantGetStringChar( wVariant *variant )
{
    wMemTest( variant, "wVariantGetStringChar:variant" );

    if (variant->dataType != W_TYPE_STRING) {
        wErrorFatal( "Variant is not a string (wVariantGetStringChar)");
        wErrorSet( W_ERROR_CONVERT );
    }
    wMemTest( variant->value.string, "wVariantGetStringChar:variant->value.string" );
    return &(variant->value.string->text);
}

/* print a value to a file */
void wVariantFilePrint( FILE *theFile, wVariant *v, int showQuotes )
{
    int i, count;
    char *buffer;
    wGrow *table;
    wGrow *list;
    wTableElement *element;
    wVariant *variant;
    wSymbol *s1, *s2;

    wMemTest( v, "wVariantPrint:v" );

    /* FIXME: This whole thing is a quick hack */


    /* determine type of value */
    switch (v->dataType) {
    case W_TYPE_NOTHING:
        fprintf( theFile, "nothing");
        break;

    case W_TYPE_INTEGER:
        fprintf( theFile, "%d", v->value.integer );
        break;

    case W_TYPE_NUMBER:
        buffer = wNumberFormat( v->value.number );
        fprintf( theFile, "%s", buffer );
        wFree( buffer );
        break;
    
    case W_TYPE_STRING:
        wMemTest( v->value.string, "wVariantPrint:v->value.string" );
        if (showQuotes) {
            fprintf( theFile,  "\"%s\"", wStringData( v->value.string ) );
        } else {
            fprintf( theFile,  "%s", wStringData( v->value.string ) );
        }
        break;

    case W_TYPE_OBJECT:
        wMemTest( v->value.string, "wVariantPrint:v->value.object" );
        if (showQuotes) {            
            fprintf( theFile,  "[%s ref:%d ", v->value.object->klass->name, v->value.object->refCount );

            /* iterate through the properties */
            list = v->value.object->klass->children;
            count = list->count;
            for ( i = 1; i <= count; i++ ) {
                /* name of property */
                fprintf( theFile, " %s:", wSymbolLookup( wGrowGet( list, i ) )->name  );

                /* value */
                wVariantPrint( &(v->value.object->prop[i-1]), W_TRUE );

            }
            fprintf( theFile, "]" );

        } else {
            fprintf( theFile,  "[%s]", v->value.object->klass->name );
        }
        break;

    case W_TYPE_ARRAY:
        wMemTest( v->value.array, "wVariantPrint:v->value.array" );
        printf ("[array]");

    case W_TYPE_TABLE:
        wMemTest( v->value.table, "wVariantPrint:v->value.table" );

        /* get the table */
        table = v->value.table;

        /* is it marked? */
        if (table->isMarked) {
            /* avoid an infinite loop */
            printf ("{...}" );

        } else {
            /* mark it to prevent recursion */
            table->isMarked = W_TRUE;
    
            /* display each element */
            fprintf( theFile,  "{" );
            for ( i = 1; i <= table->count; i++ ) {
                /* get the element */
                element = (wTableElement *)wGrowGet( table, i );
    
                /* print the key */
                wVariantPrint( &(element->key), W_TRUE );
    
                /* print the value */
                fprintf( theFile, ":");
                wVariantPrint( &(element->value), W_TRUE );
    
                /* trailing comma? */
                if (i < table->count) {
                    fprintf( theFile, ", ");
                }
            }
            fprintf( theFile, "}");
    
            /* clear the mark */
            table->isMarked = W_FALSE;

        }

		break;

    case W_TYPE_LIST:
        wMemTest( v->value.list, "wVariantPrint:v->value.list" );

        /* get the list */
        list = v->value.list;

        /* is it marked? */
        if (list->isMarked) {
            /* avoid an infinite loop */
            printf ("[...]" );

        } else {
            /* mark it to prevent recursion */
            list->isMarked = W_TRUE;
    
            /* display each element */
            fprintf( theFile,  "[" );
            for ( i = 1; i <= list->count; i++ ) {
                /* get the element */
                variant = (wVariant *)wGrowGet( list, i );
    
                /* print the value */
                wVariantPrint( variant, W_TRUE );
    
                /* trailing comma? */
                if (i < list->count) {
                    fprintf( theFile, ", ");
                }
            }
            fprintf( theFile, "]");
    
            /* clear the mark */
            list->isMarked = W_FALSE;

        }

		break;


    case W_TYPE_VARPTR:
        fprintf( theFile,  "%p (varptr->", v->value.varptr );
        wVariantPrint( v->value.varptr, W_TRUE );
        fprintf( theFile,  ")" );
        break;

    case W_TYPE_ROUTINE:
        /* get the routine name and the scope */
        s1 = v->value.routine;
        s2 = wSymbolLookup( s1->scope );

        /* format and display with fprintf */
        fprintf( theFile, "%s.%s", s2->name, s1->name );

        break;

    case W_TYPE_DATETIME:
        /* format the time */
        buffer = wDateTimeFormat( "%c", variant->value.time );

        /* format and display with fprintf */
        fprintf( theFile, "%s", buffer );

        /* free the buffer */
        wFree( buffer );

        break;


    default:
        wErrorFatal( "Unknown datatype %d (wVariantPrint)", v->dataType );
        wErrorSet( W_ERROR_INTERNAL );
        break;
        
    }
}


/* print a value to stdout */
void wVariantPrint( wVariant *v, int showQuotes )
{
    wVariantFilePrint( stdout, v, showQuotes );
}
