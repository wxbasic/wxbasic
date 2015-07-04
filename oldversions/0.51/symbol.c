/*
    Name:       symbol.c
    Purpose:    Data structures for wxBasic symbols
    Author:     David Cuny
    Copyright:  (c) 2002 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*/

/* don't return symbol if hidden */
wSymbol *wMaskIfHidden( wSymbol *s ) {

    /* only applies to variables and arrays */
    if (s->symbolType != W_SYM_VARIABLE &&
        s->symbolType != W_SYM_ARRAY ) {
            return s;
    }

    /* visible if in current scope or common */
    if (s->scope == wCurrentScope || s->common ) {
        return s;
    }

    /* visible global? */
    if (wCurrentScope != NULL) {
        /* can see if no explict option set */
        if (!wExplicitFlag) {
            return s;
        }

        /* visible if not shared */
        if (wInStack(wSharedStack, (int)s )) {
            return s;
        }
    }

    return NULL;

}    


/* find symbol in symbol list */
wSymbol *wFindSymbol( char *name, wSymbol *scope )
{
    int     i, len, result;
    char    *lcase;
    wSymbol *s;

    /* name isn't tested, because it can come from a static table */
    wMemTest( "wFindSymbol: scope", scope );

    /* create lower case version of name */
    len = strlen( name );
    lcase = (char *)wMalloc( len+1 );
    for ( i = 0; i < len; i++ ) {
        lcase[i] = tolower( name[i] );
    }
    lcase[len] = '\0';

    for ( s = wLastSymbol; s != NULL; s = s->prior ) {
        /* in scope or common? */
        if (s->scope == scope || s->common ) {
            /* take case into account? */
            if (s->useCase) {
                result = strcmp( s->name, name);
            } else {
                result = strcmp( s->name, lcase);
            }

            if (result == 0) {
                wFree( lcase );
                /* hidden? */
                return wMaskIfHidden(s);
            }
        }
    }
    wFree( lcase );
    return NULL;
}

/* add sibling to symbol */
void wAddChildSymbol( wSymbol *s, wSymbol *child )
{
    wMemTest( "addChildSymbol: parent", s );
    wMemTest( "addChildSymbol: child", child );

    /* first child? */
    if (s->child == NULL) {
        s->child = child;
        return;
    }

    /* walk to end of sibling chain */
    for ( s = s->child; s->sibling != NULL; s = s->sibling ) {
        wMemTest( "wAddChildSymbol: sibling", s );
    }
    s->sibling = child;
}


/* add symbol to symbol list */
wSymbol *wAddSymbol( char *name, wSymbol *scope, int symbolType, int useCase )
{
    wSymbol  *s;

    /* name isn't tested, because it can come from a static table */
    wMemTest( "wAddSymbol: scope", scope );

    s = wFindSymbol( name, scope );
    if (s != NULL) {
        wFatal( W_RUNTIME, "wAddSymbol: %s %s is already defined as %s",
            wSymbolName[symbolType], name, wSymbolName[s->symbolType] );
    }

    s = (wSymbol *)wMalloc( sizeof( wSymbol ) );
    s->name = wCopyString( name );
    s->useCase = useCase;
    s->symbolType = symbolType;
    s->klass = 0;
    s->scope = scope;
    s->common = wCommonFlag;
    s->stackPos = 0;
    s->args = 0;
    s->optArgs = 0;
    s->locals = 0;
    s->prior = wLastSymbol;
    s->child = NULL;
    s->sibling = NULL;
    s->forward = 0;
    s->code = NULL;
    s->builtin = NULL;
    wLastSymbol = s;

    return s;
}


/* find symbol in symbol list with given index */
wSymbol *wFindChildSymbol( wSymbol *parent, int index )
{

    wSymbol  *child;

    wMemTest( "wAddChildSymbol: parent", parent );

    /* get child */
    index--;
    child = parent->child;
    wMemTest( "wAddChildSymbol: child", child );

    if (index==0) {
        return child;
    }

    while (index > 0) {
        index--;

        /* get next sibling */
        child = child->sibling;
        wMemTest( "wAddChildSymbol: sibling", child );

        /* end of chain? */
        if (child == NULL) {
            break;
        }
    }
    return child;
}



/* aborts with error if arg count doesn't match */
void wCheckArgCount( wSymbol *s, int args )
{
    int     minArgs = s->args,
            maxArgs = minArgs + s->optArgs;

    wMemTest( "wCheckArgCount: s", s );

    if (s->optArgs == 0) {
        if (args != s->args ) {
            wFatal( W_SYNTAX, "%s %s expects %d args, not %d",
                wSymbolName[s->symbolType], s->name, s->args, args );
        }
    } else if (args < minArgs ) {
            wFatal( W_SYNTAX, "%s %s expects at least %d args, not %d",
                wSymbolName[s->symbolType], s->name, minArgs, args );
            
    } else if (args > maxArgs ) {
            wFatal( W_SYNTAX, "%s %s expects at most %d args, not %d",
                wSymbolName[s->symbolType], s->name, maxArgs, args );
    }
}


/* generate an error report for undefined routines */
void wGenerateWarnings()
{
    int     count = 0;
    char    message[40];
    wSymbol *s;
    FILE    *errFile = NULL;

    for ( s = wLastSymbol; s != NULL; s = s->prior ) {
        /* unresolved forward ref? */
        if (s->forward) {

            /* open the error file? */
            if (errFile == NULL) {
                errFile = fopen( "wx.err", "w" );
                if (errFile == NULL) {
                    wFatal( W_RUNTIME, "wReportUndefinedRoutines: Can't create wx.err" );
                }
            }
            count++;
            fprintf( errFile, "Warning: routine %s is undefined\n", s->name );            
        }
    }
    if (count) {
        sprintf( message, "Warning: There were %d undefined routines - see wx.err.", count );
#ifdef __WXWIN__
    wxMessageBox( message, W_PROGNAME, wxOK, (wxWindow *)NULL );
#else
    fprintf( stderr, message );
#endif
    }
}
