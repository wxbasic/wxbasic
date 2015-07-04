/*************************************************************
    Name:       wnumber.c
    Purpose:    NUMBER datatype
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/

/* assign methods */
void wNumberRegisterMethods()
{
    /* register the routines */
    wTheHandler[W_TYPE_NUMBER]->isNumeric       = W_TRUE;
    wTheHandler[W_TYPE_NUMBER]->ref             = NULL;
    wTheHandler[W_TYPE_NUMBER]->deref           = NULL;
    wTheHandler[W_TYPE_NUMBER]->copy            = wNumberCopy;
    wTheHandler[W_TYPE_NUMBER]->clone           = wNumberCopy;
    wTheHandler[W_TYPE_NUMBER]->fromNumber      = wNumberFromNumber;
    wTheHandler[W_TYPE_NUMBER]->toNumber        = wNumberToNumber;
    wTheHandler[W_TYPE_NUMBER]->fromChar        = wNumberFromChar;
    wTheHandler[W_TYPE_NUMBER]->toChar          = wNumberToChar;
    wTheHandler[W_TYPE_NUMBER]->compare         = wNumberCompare;
    wTheHandler[W_TYPE_NUMBER]->equal           = wNumberEqual;
    wTheHandler[W_TYPE_NUMBER]->isTrue          = NULL;
    wTheHandler[W_TYPE_NUMBER]->count           = NULL;
    wTheHandler[W_TYPE_NUMBER]->index           = NULL;
    wTheHandler[W_TYPE_NUMBER]->find            = NULL;
    wTheHandler[W_TYPE_NUMBER]->remove          = NULL;
    wTheHandler[W_TYPE_NUMBER]->append          = NULL;
    wTheHandler[W_TYPE_NUMBER]->prepend         = NULL;
    wTheHandler[W_TYPE_NUMBER]->slice           = NULL;
    wTheHandler[W_TYPE_NUMBER]->iterate         = NULL;
}



/* copy value in data */
void wNumberCopy( wVariant *dst, wVariant *src )
{
	dst->value.number = src->value.number;
}


/* convert a number into a number */
void wNumberFromNumber( wVariant *dst, wNumber n )
{
    dst->value.number = n;
}

/* return value of number */
wNumber wNumberToNumber( wVariant *src )
{
    return (wNumber)src->value.number;
}



/* convert a char string to a number */
int wNumberFromChar( wVariant *dst, char *text )
{
    wNumber n;
    if (sscanf( text, "%f", &n ) == 0) {
        return W_FALSE;
    }
    dst->value.number = n;
    return W_TRUE;
}

/* format a number into a char */
char *wNumberToChar( wVariant *src, int useQuotes, int limit )
{
    int i;
    char *buffer;
    wNumber n;
    
    /* get the number */
    n = src->value.number;
    
    buffer = (char *)wMalloc( 32 );
    /* no floating point? */
    if (floor(n) == n) {
        sprintf( buffer, "%.0f", n );
    } else {
        sprintf( buffer, "%g", n );           
        /* search for non-zero */
        for( i = strlen( buffer )-1; i > 0; i++) {
            if (buffer[i] != '0') {
                break;
            } else if (buffer[i-1] == '.') {
                buffer[i] = '\0';
                break;
            }
        }
    }
    return buffer;
}


/* checks if two numbers are equal */
int wNumberEqual( wVariant *v1, wVariant *v2 )
{

	/* test for exact equality */
	if (fabs(v1->value.number == v2->value.number)) {
		return W_TRUE;
	}

	/* equal if difference is less than FLT_EPSILON */
    return (fabs(v1->value.number - v2->value.number) < FLT_EPSILON );
}

/* compares two numbers */
int wNumberCompare( wVariant *v1, wVariant *v2 )
{
    wNumber diff;
	
	/* compare the numbers */
    diff = (v1->value.number - v2->value.number);
	
    /* adjust for rounding errors */
    if (fabs( diff ) < FLT_EPSILON) {
        return 0;
    } else if (diff > 0) {
        return 1;
    } else {
        return -1;
    }
}


/* compares two numbers */
int wNumberCompareNumbers( wNumber n1, wNumber n2 )
{
    wNumber diff;
	
	/* compare the numbers */
    diff = (n1 - n2);
	
    /* adjust for rounding errors */
    if (fabs( diff ) < FLT_EPSILON) {
        return 0;
    } else if (diff > 0) {
        return 1;
    } else {
        return -1;
    }
}

