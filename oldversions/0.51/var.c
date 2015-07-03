/*
    Name:       var.c
    Purpose:    wxBasic simple variables
    Author:     David Cuny
    Copyright:  (c) 2002 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*/



/* return symbol for var, can optionally create it. */
wSymbol *wReturnVar( char *name, int symType, int create )
{
    wSymbol  *s;

    /* look in scope */
    s = wFindSymbol( name, wCurrentScope );

    /* global? */
    if (s==NULL && wCurrentScope != NULL && !create) {
        s = wFindSymbol( name, NULL );
    }

    /* create request, but already exists? */
    if (create && s != NULL) {
        wFatal( W_SYNTAX, "%s already exists as %s",
            name, wSymbolName[s->symbolType]);
            
    }

    /* validate before passing back */
    if (s != NULL) {
        if (s->symbolType != symType) {
            wFatal( W_SYNTAX, "%s is a %s, not a %s",
                s->name, wSymbolName[s->symbolType], wSymbolName[symType] );
        } else {
            return s;
        }
    }

    /* can't implicitly create it? */
    if (!create && wExplicitFlag) {
        wFatal( W_SYNTAX, "%s has not been declared\n", name );
    }

    s = wAddSymbol( name, wCurrentScope, symType, W_TRUE );

    if (wCurrentScope==NULL) {
        /* create as global */
        s->stackPos = wAddGlobalToStack();
        wData[s->stackPos].datatype = W_DATA_UNDEFINED;

    } else {
        /* create as local */
        wCurrentScope->locals++;
        s->stackPos = wCurrentScope->locals + wCurrentScope->optArgs;

        /* set as child */
        wAddChildSymbol( wCurrentScope, s );
    }

    return s;
}

/* create constant */
wSymbol *wCreateConst( char *name )
{
    wSymbol *s = NULL;

    s = wAddSymbol( name, wCurrentScope, W_SYM_CONSTANT, W_TRUE );

    /* create as global */
    s->stackPos = wAddGlobalToStack();

    wData[s->stackPos].datatype = W_DATA_NUMBER;
    wData[s->stackPos].value.number = 0;

    return s;
}

/* add numeric constant */
void wCreateNumConst( char *name, int value )
{
    int     pos;
    wSymbol *s;

    s = wCreateConst( name );
    pos = s->stackPos;
    wData[pos].datatype = W_DATA_NUMBER;
    wData[pos].value.number = value;
}

/* add string constant */
void wCreateStrConst( char *name, char *value )
{
    int     pos;
    wSymbol *s;

    s = wCreateConst( name );
    pos = s->stackPos;
    wData[pos].datatype = W_DATA_STRING;
    wData[pos].value.string = wCopyString(value);
}


/* create a parameter for a routine */
wSymbol *wCreateParm( char *name, int symType )
{
    wSymbol  *s;

    s = wReturnVar( name, symType, 1 );
    if (symType == W_SYM_ARRAY) {
        s->args = 1;
        s->optArgs = W_MAX_OPT_ARGS;
    }

    wCurrentScope->args++;
    wCurrentScope->locals = wCurrentScope->args;

    return s;
}


/* return position of var on stack */
int wVarStackPos( wSymbol *s )
{
    /* function return values are at the start of locals */
    if (s->symbolType == W_SYM_FUNCTION) {
        return wLocalStart;
    }

    if (s->scope == NULL) {
        /* absolute position */
        return s->stackPos;
    } else {
        /* relative position */
        return wLocalStart+(s->stackPos);
    }
}

/* store tos value at index */
void wSetStack( int index )
{
    wVariant *source, *dest;

    /* should not happen */
    if (index < 0) {
        wFatal( W_RUNTIME, "wSetStack: stack error" );
    }

    source = wGetStackPointer( wTos );
    dest = wGetStackPointer( index );

    /* free string currently stored? */
    if (dest->datatype == W_DATA_STRING) {
        wFree( dest->value.string );
    }

    if (source->datatype == W_DATA_STRING) {
        dest->datatype = W_DATA_STRING;
        dest->value.string = wPopString();

    } else if (source->datatype == W_DATA_NUMBER) {
        dest->datatype= W_DATA_NUMBER;
        dest->value.number = wPopNumber();

    } else if (source->datatype == W_DATA_OBJECT) {
        dest->datatype= W_DATA_OBJECT;
        dest->value.number = wPopNumber();

    } else {
        wFatal( W_RUNTIME, "wSetStack: can't fetch %s", wDatumName[dest->datatype] );
    }
}

/* store tos in local variable */
void wSetVar( wSymbol *s )
{
    wSetStack( wVarStackPos( s ) );
}

/* store tos in return area of stack (wLocalStart-1) */
void wSetReturn()
{
    wSetStack( wLocalStart-1 );
}

/* push variable pointer or value onto stack */
void wGetVar( wSymbol *s )
{
    wCopyStackItem( wVarStackPos( s ) );
}
