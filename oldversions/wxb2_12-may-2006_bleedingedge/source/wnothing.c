/*************************************************************
    Name:       nothing.c
    Purpose:    implement W_TYPE_NOTHING methods
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/


void wNothingRegisterMethods()
{
    /* register the routines */
    wTheHandler[W_TYPE_NOTHING]->isNumeric      = W_FALSE;
    wTheHandler[W_TYPE_NOTHING]->ref            = NULL;
    wTheHandler[W_TYPE_NOTHING]->deref          = NULL;
    wTheHandler[W_TYPE_NOTHING]->copy           = wNothingCopy;
    wTheHandler[W_TYPE_NOTHING]->clone          = NULL;
    wTheHandler[W_TYPE_NOTHING]->fromNumber     = NULL;
    wTheHandler[W_TYPE_NOTHING]->toNumber       = NULL;
    wTheHandler[W_TYPE_NOTHING]->fromChar       = wNothingFromChar;
    wTheHandler[W_TYPE_NOTHING]->toChar         = wNothingToChar;
    wTheHandler[W_TYPE_NOTHING]->compare        = NULL;
    wTheHandler[W_TYPE_NOTHING]->equal          = wNothingEqual;
    wTheHandler[W_TYPE_NOTHING]->isTrue         = wNothingIsTrue;
    wTheHandler[W_TYPE_NOTHING]->count          = NULL;
    wTheHandler[W_TYPE_NOTHING]->index          = NULL;
    wTheHandler[W_TYPE_NOTHING]->find           = NULL;
    wTheHandler[W_TYPE_NOTHING]->remove         = NULL;
    wTheHandler[W_TYPE_NOTHING]->append         = NULL;
    wTheHandler[W_TYPE_NOTHING]->prepend        = NULL;
    wTheHandler[W_TYPE_NOTHING]->slice          = NULL;
    wTheHandler[W_TYPE_NOTHING]->iterate        = wNothingIterate;
}

/* copy value in data */
void wNothingCopy( wVariant *dst, wVariant *src )
{
    /* nothing to do */
}


char *wNothingToChar( wVariant *src, int useQuotes, int limit )
{
	/* return buffer with string "Nothing" */
    return wCharCopy( "Nothing" );
}

int wNothingFromChar( wVariant *dst, char *buffer )
{
	/* always succeed */
	return W_TRUE;
}

int wNothingEqual( wVariant *v1, wVariant *v2 )
{
    /* always true */
    return W_TRUE;
}


int wNothingIsTrue( wVariant *src )
{
    /* always false */
    return W_FALSE;
}

/* iterate */
int wNothingIterate( wVariant *vNothing, wVariant *vIndex, wVariant *vArg1, wVariant *vArg2  )
{
    /* return false to exit the loop */
    return W_FALSE;
}

