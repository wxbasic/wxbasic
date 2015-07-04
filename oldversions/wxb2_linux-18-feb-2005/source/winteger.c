/*************************************************************
    Name:       winteger.c
    Purpose:    W_TYPE_INTEGER implementation
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/


void wIntegerRegisterMethods()
{
    /* register the routines */
    wTheHandler[W_TYPE_INTEGER]->isNumeric      = W_TRUE;
    wTheHandler[W_TYPE_INTEGER]->ref            = NULL;
    wTheHandler[W_TYPE_INTEGER]->deref          = NULL;
    wTheHandler[W_TYPE_INTEGER]->copy           = wIntegerCopy;
    wTheHandler[W_TYPE_INTEGER]->clone          = wIntegerCopy;
    wTheHandler[W_TYPE_INTEGER]->fromNumber     = wIntegerFromNumber;
    wTheHandler[W_TYPE_INTEGER]->toNumber       = wIntegerToNumber;
    wTheHandler[W_TYPE_INTEGER]->fromChar       = wIntegerFromChar;
    wTheHandler[W_TYPE_INTEGER]->toChar         = wIntegerToChar;
    wTheHandler[W_TYPE_INTEGER]->compare        = wIntegerCompare;
    wTheHandler[W_TYPE_INTEGER]->equal          = wIntegerEqual;
    wTheHandler[W_TYPE_INTEGER]->isTrue         = NULL;
    wTheHandler[W_TYPE_INTEGER]->count          = NULL;
    wTheHandler[W_TYPE_INTEGER]->index          = NULL;
    wTheHandler[W_TYPE_INTEGER]->find           = NULL;
    wTheHandler[W_TYPE_INTEGER]->remove         = NULL;
    wTheHandler[W_TYPE_INTEGER]->append         = NULL;
    wTheHandler[W_TYPE_INTEGER]->prepend        = NULL;
    wTheHandler[W_TYPE_INTEGER]->slice          = NULL;
    wTheHandler[W_TYPE_INTEGER]->iterate        = NULL;
}


/* copy value in data */
void wIntegerCopy( wVariant *dst, wVariant *src )
{
    dst->value.integer = src->value.integer;
}


/* convert a number into an integer */
void wIntegerFromNumber( wVariant *dst, wNumber n )
{
    dst->value.integer = (int)n;
}

/* return value of integer */
wNumber wIntegerToNumber( wVariant *src )
{
    return (wNumber)src->value.integer;
}

/* convert a char string to a number */
int wIntegerFromChar( wVariant *dst, char *text )
{
    int i;
    if (sscanf( text, "%d", &i ) == 0) {
        return W_FALSE;
    }
    dst->value.integer = (int)i;
    return W_TRUE;
}

/* format a number into a char */
char *wIntegerToChar( wVariant *src, int useQuotes, int limit )
{
    int i;
    char *buffer;

    buffer = (char *)wMalloc( 32 );
    sprintf( buffer, "%d", src->value.integer );           
    return buffer;
}


/* test two integer variants for equality */
int wIntegerEqual( wVariant *v1, wVariant *v2 )
{
	/* test for equality */
    return (v1->value.integer == v2->value.integer);
}

/* compares two integer variants */
int wIntegerCompare( wVariant *v1, wVariant *v2 )
{	
	int diff;

	/* compare the numbers */
    diff = (v1->value.integer - v2->value.integer);
	    
    if ( diff == 0) {
        return 0;
    } else if (diff > 0) {
        return 1;
    } else {
        return -1;
    }
}
