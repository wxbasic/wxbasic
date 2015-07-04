/*************************************************************
    Name:       wroutine.c
    Purpose:    W_TYPE_ROUTINE datatype
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/


/* assign methods */
void wRoutineRegisterMethods()
{
    /* register the routines */
    wTheHandler[W_TYPE_ROUTINE]->isNumeric      = W_FALSE;
    wTheHandler[W_TYPE_ROUTINE]->ref            = NULL;
    wTheHandler[W_TYPE_ROUTINE]->deref          = NULL;
    wTheHandler[W_TYPE_ROUTINE]->copy           = wRoutineCopy;
    wTheHandler[W_TYPE_ROUTINE]->clone          = wRoutineCopy;
    wTheHandler[W_TYPE_ROUTINE]->fromNumber     = NULL;
    wTheHandler[W_TYPE_ROUTINE]->toNumber       = NULL;
    wTheHandler[W_TYPE_ROUTINE]->fromChar       = wRoutineFromChar;
    wTheHandler[W_TYPE_ROUTINE]->toChar         = wRoutineToChar;
    wTheHandler[W_TYPE_ROUTINE]->compare        = NULL;
    wTheHandler[W_TYPE_ROUTINE]->equal          = wRoutineEqual;
    wTheHandler[W_TYPE_ROUTINE]->isTrue         = NULL;
    wTheHandler[W_TYPE_ROUTINE]->count          = NULL;
    wTheHandler[W_TYPE_ROUTINE]->index          = NULL;
    wTheHandler[W_TYPE_ROUTINE]->find           = NULL;
    wTheHandler[W_TYPE_ROUTINE]->remove         = NULL;
    wTheHandler[W_TYPE_ROUTINE]->append         = NULL;
    wTheHandler[W_TYPE_ROUTINE]->prepend        = NULL;
    wTheHandler[W_TYPE_ROUTINE]->slice          = NULL;
    wTheHandler[W_TYPE_ROUTINE]->iterate        = NULL;
}

/* copy routine */
void wRoutineCopy( wVariant *dst, wVariant *src )
{
	dst->value.routine = src->value.routine;
}

/* convert a char string to a routine */
int wRoutineFromChar( wVariant *dst, char *text )
{
	wSymbol *symbol;

	/* FIXME: this only finds things in global scope */
	symbol = wSymbolFind( text, wTheGlobalScope );	
	if (symbol == NULL || (symbol->type != W_SYM_FUNCTION && symbol->type != W_SYM_SUB)) {
		/* failed */
		return W_FALSE;
	} else {
		dst->value.routine = symbol;
		return W_TRUE;
	}
}

/* return char buffer with routine name */
char *wRoutineToChar( wVariant *src, int useQuotes, int limit )
{
	/* return char buffer of routine name */
    return wCharCopy( src->value.routine->name );
}


/* compare two routines */
int wRoutineEqual( wVariant *v1, wVariant *v2 )
{	
    /* test values for equality */
    return (v1->value.routine == v2->value.routine );
}
