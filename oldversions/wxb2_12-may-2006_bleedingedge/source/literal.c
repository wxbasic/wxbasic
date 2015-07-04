/*************************************************************
    Name:       literal.c
    Purpose:    Implements the literal table
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/

/* add a variant to the literal table, return index */
int wLiteralAdd( char *name, wVariant *variant )
{
    int index;
    char *buffer;
    wSymbol *symbol;

    /* add the variant to the table */
    index = wGrowAppend( wTheLiterals, (int)variant );

    /* name? */
    if (name != NULL && strlen( name ) > 0) {
        /* convert the name to lower case */
        buffer = wCharCopyToLower( name );

        /* create a symbol */
        symbol = wSymbolNew( buffer, wTheCurrentScope, W_SYM_LITERAL );
        symbol->tokenType = index;

        /* free the buffer */
        wFree( buffer );
    }

    return index;

}

/* insert a number into the literal table, and return the index */
int wLiteralAddNum( char *name, wNumber n )
{
    int i, count;
    wVariant *variant;

    /* search for match in literal table? */
    if (strlen(name) == 0) {
        wMemTest( wTheLiterals, "wCodeAddNumber:wTheLiterals" );
        count = wTheLiterals->count;
        for (i=1; i <= count; i++ ) {
            variant = (wVariant *)wGrowGet( wTheLiterals, i );
            wMemTest( variant, "wCodeAddNumber:v" );
            if (variant->dataType == W_TYPE_NUMBER
            &&  variant->value.number == n) {
                return i;
            }
        }
    }

    /* create a new number */
    variant = (wVariant *)wMalloc( sizeof( variant ) );
    variant->dataType = W_TYPE_NUMBER;
    variant->value.number = n;
    
    /* add it to the literal table */
    return wLiteralAdd( name, variant );
}

/* insert a string into the literal table, and return it's index */
int wLiteralAddStr( char *name, char *s )
{
    int i, count, length, nameLength;
    wVariant *v, *newValue;

    /* get the length of the strings */
    length = strlen( s );
    nameLength = strlen( name );


#ifdef __WDEBUG__
    /* track the strings? */
    if (nameLength) {
        wMemAdd( (void *)name, strlen( name )+1 );
        wMemAdd( (void *)s, strlen( s )+1 );
    }
#endif

    /* search for match in string literal table? */
    if (nameLength == 0) {
        count = wTheLiterals->count;
        for (i=1; i <= count; i++ ) {
            /* deref the pointer */
            v = (wVariant *)wGrowGet( wTheLiterals, i );
            wMemTest( v, "wLiteralAddStr:v" );
            /* string? */
            if (v->dataType == W_TYPE_STRING) {
                /* same length? */
                wMemTest( v->value.string, "wCodeEmitNumber:v->value.string" );
                if (v->value.string->length == length) {
                    /* are the strings equal? */
                    if (memcmp( (void *)(s), (void *)wStringChar(v), length )==0) {
                        return i;
                    }
                }
            }
        }
    }

    /* create the string */
    newValue = (wVariant *)wMalloc( sizeof( wVariant ) );
    newValue->dataType = W_TYPE_NOTHING;

    /* turn it into a string. */
    wStringNew( newValue, s, -1 );

#ifdef __WDEBUG__
    /* stop tracking */
    if (nameLength) {
        wMemRemove( (void *)name );
        wMemRemove( (void *)s );
    }
#endif

    /* add it to the literal table */
    return wLiteralAdd( name, newValue );
}

/* return char value of string constant */
char *wLiteralGetChar( int index )
{
    wVariant *v;

    /* get the variant that holds the string */
    v = (wVariant *)wGrowGet(wTheLiterals, index);

    /* make sure it's a string */
    if (v->dataType != W_TYPE_STRING) {
        wErrorThrow( W_ERROR_INTERNAL, "wLiteralGetChar: Variant is not a string" );
    }

    /* return the char value */
    return &( v->value.string->text );
}

/* wrap a constant pointer */
int wLiteralAddPtr( char *name, wSymbol *klass, void *ptr )
{
    wVariant *variant;
    wObject *object;

    /* create an object to hold the pointer, permanent */
    object = wObjectNew( klass->index, W_FALSE );

    /* store the pointer */
    object->ptr = ptr;

    /* create the object */
    variant = (wVariant *)wMalloc( sizeof( wVariant ) );
    variant->dataType = W_TYPE_OBJECT;
    variant->value.object = object;

    /* add it to the literal table */
    return wLiteralAdd( name, variant );
}

/* initialize the builtin constants */
void wLiteralInit() {

    /* initialize the literals list */
    wTheLiterals = wGrowNew( 4096 );
    /* common */
    wLiteralAddNum( "TRUE",                             1 );
    wLiteralAddNum( "FALSE",                            W_FALSE );
    wLiteralAddNum( "PI",                               M_PI );
    wLiteralAddStr( "DELIMITER_CHAR",                   DELIMITER_STRING );
    wLiteralAddStr( "WXBASIC_VERSION",                  W_RELEASE );
    wLiteralAddStr( "WXBASIC_DATE",                     W_DATEOF );
}

/* debugging */
void wLiteralDumpTable() {
    int i;
    wVariant *v;

    /* get the count of literals in the table */
    int count = wTheLiterals->count;
printf("There are %d literals\n", count );
    /* iterate over the table */
    for (i=1; i <= count; i++ ) {
        /* deref the pointer */
        v = (wVariant *)wGrowGet( wTheLiterals, i );
        /* string? */
        if (v->dataType == W_TYPE_STRING) {
            printf( "%d %s\n", i, wStringChar(v) );
        }
    }
}

