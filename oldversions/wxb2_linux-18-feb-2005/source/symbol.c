/*************************************************************
    Name:       symbol.c
    Purpose:    symbol table for wxBasic
    Author:     David Cuny
    Copyright:  (c) 2002 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/

/* initialize symbol table */
void wSymbolInit()
{
    int i;
    wSymbol *s;

    if (wTheSymbols != NULL) {
        wErrorThrow( W_ERROR_INTERNAL, "Can't reinitialize symbol table (wSymbolInit)" );
    }

    /* create the symbol table */
    wTheSymbols = wGrowNew( W_HASHTABLE_SIZE );

    /* clear the hash table */
    for ( i = 0; i < W_HASHTABLE_SIZE; i++ ) {
        wSymbolHashTable[i] = NULL;
    }

    /* create the global scope */
    s = wSymbolNew( "_global", 0, W_SYM_FUNCTION );

    /* resolve global scope */
    s->scope = s->index;
    wTheGlobalScope = s->index;

    /* make it the current scope */
    wTheCurrentScope = wTheGlobalScope;
}


/* compute a hash value for a character string */
int wSymbolHash( char *letters )
{
    unsigned int    key;
    unsigned char   *letter;

    /* clear key value */
    key = 0;

    /* iterate through the string */
    for ( letter = (unsigned char *)letters; *letter != '\0'; letter++ ) {
        key = (W_HASH_MULTIPLER*key) + *letter;
    }

    /* use mod to ensure it fits into the table */
    return (int)(key % W_HASHTABLE_SIZE);
}

/* add a symbol to the hash table */
void wSymbolAddToHashTable( wSymbol *symbol )
{
    int hashKey;
    wSymbol *prior;

    /* calculate the hash */
    hashKey = wSymbolHash( symbol->name );

    /* last element in chain */
    symbol->next = 0;

    /* look in the table */
    prior = wSymbolHashTable[hashKey];
    if (prior == NULL) {
        /* first item in table */
        wSymbolHashTable[hashKey] = symbol;
    } else {

        /* look for the end of the chain */
        while (prior->next) {
            /* go to the next link */
            prior = wSymbolLookup( prior->next  );
        }
        /* attach to the end of the chain */
        prior->next = symbol->index;
    }
}


/* error out if name is being used */
void wSymbolUnused( char *name )
{
    wSymbol *symbol, *parent;

    /* skip if system assigned name */
    if (name[0] == '_') {

    /* first char must be alphanumeric */
    } else if (!isalnum(name[0])) {
        wErrorThrow( W_ERROR_SYNTAX, "\"%s\" is not a valid name", name );

    } else {
        /* check to see if it's already defined */
        symbol = wSymbolFind( name, wTheCurrentScope );

        /* undefined? */
        if (symbol == NULL) {
            /* safe */

        /* symbol is a global variable, but scope is local */
        } else if (wTheCurrentScope != wTheGlobalScope
                && symbol->scope == wTheGlobalScope
                && symbol->type == W_SYM_VARIABLE ) {
            /* can also ignore */

        /* symbol is a global, but inside a class */
        } else if (wTheClassScope != 0 && symbol->scope != wTheClassScope) {
            /* can safely ignore */

        } else {
            /* can't ignore conflict */
            parent = wSymbolLookup( symbol->scope );
            wErrorThrow( W_ERROR_SYNTAX, "\"%s\" is already defined as %s of %s",
                name, wSymbolName[symbol->type], parent->name );
        }
    }
}

/* add symbol to symbol list */
wSymbol *wSymbolNew( char *name, int scope, int symbolType )
{
    int index, hashKey;
    wSymbol  *symbol;

    /* don't wMemTest name, it's often from a string constant */

    /* make sure it doesn't exist already */
    wSymbolUnused( name );

    /* create an entry in the symbol table */
    symbol = (wSymbol *)wMalloc( sizeof( wSymbol ) );
    index = wGrowAppend( wTheSymbols, (int)symbol );
    wMemTest( symbol, "wSymbolNew:symbol(2)" );

    /* assign values */
    symbol->name = wCharCopy( name );
    symbol->next = 0;
    symbol->tokenType = 0;
    symbol->index = index;
    symbol->type = symbolType;
    symbol->typeCast = W_TYPE_VARIANT;
    symbol->scope = scope;
    symbol->children = NULL;
    symbol->alias = 0;
    symbol->inherits = 0;
    symbol->flags = 0;
    symbol->stackPos = 0;
    symbol->args = 0;
    symbol->optArgs = 0;
    symbol->varArgs = W_FALSE;
    symbol->method = NULL;
    symbol->builtin = NULL;
    symbol->pcode = NULL;
    symbol->children = NULL;
    symbol->called = 0;

    /* add child list if it needs it */
    if (symbolType == W_SYM_FUNCTION
    ||  symbolType == W_SYM_SUB
    ||  symbolType == W_SYM_USER_CLASS ) {
        symbol->children = wGrowNew( 1 );
    }

    /* insert it into the hash table */
    wSymbolAddToHashTable( symbol );

    return symbol;
}



/* look up symbol by index */
wSymbol *wSymbolLookup( int index  )
{
    wSymbol *symbol;

    symbol = (wSymbol *)wGrowGet( wTheSymbols, index );
    wMemTest( symbol, "wSymbolLookup:symbol" );

    return symbol;

}

/* find symbol in symbol list */
wSymbol *wSymbolFind( char *name, int scope )
{
    int     hashKey, i, count, result;
    wSymbol *symbol, *match;

    /* don't wMemTest name, it's often from a literal constant */

    /* in hash table? */
    hashKey = wSymbolHash( name );
    symbol = wSymbolHashTable[hashKey];
    if (symbol == NULL) {
        return NULL;
    }

    /* clear match */
    match = NULL;

    /* walk chain */
    while (W_TRUE) {

        wMemTest( symbol, "wSymbolFind:symbol" );

        /* in scope or global? */
        if (symbol->scope == scope
        || symbol->scope == wTheGlobalScope
        ||  symbol->scope == wTheClassScope ) {
            /* match? */
            if (strcmp( name, symbol->name ) == 0 ) {
                /* exact match? */
                if (symbol->scope == scope) {
                    return symbol;

                /* strong match, but may be overridden */
                } else {
                    match = symbol;
                }
            }
        }

        /* final link? */
        if (!symbol->next) {
            break;
        }

        /* next link */
        symbol = wSymbolLookup( symbol->next );
    }

    return match;
}


wSymbol *wSymbolFindMethod( wSymbol *klass, int stringIndex )
{
    char *methodChar;
    wVariant *methodName;

    wMemTest( klass, "wSymbolFindMethod:klass" );

    /* get the string representing the method name */
    methodName = (wVariant *)wGrowGet(wTheLiterals, stringIndex);
    wMemTest( methodName, "wSymbolFindMethod:methodName" );

    /* get the text from the string */
    methodChar = &(methodName->value.string->text);
    wMemTest( methodChar, "wSymbolFindMethod:methodChar" );

    return wSymbolFindMethodChar( klass, methodChar );
}

wSymbol *wSymbolFindMethodChar( wSymbol *klass, char *methodChar )
{
    int i, index;
    wGrow *methodList;
    wSymbol *symbol;    
    wMemTest( klass, "wSymbolFindMethodChar:klass" );

    while (1) {
        methodList = klass->method;
        wMemTest( methodList, "wSymbolFindMethodChar:methodList" );
        for ( i = 1; i <= methodList->count; i++ ) {
            /* get the method index from the list */
            index = wGrowGet( methodList, i );

            /* get the symbol from the symbol table */
            symbol = wSymbolLookup( index  );

            /* compare strings */
            if (strcmp( methodChar, symbol->name ) == 0 ) {
                return symbol;
            }
        }

        /* no superclass? */
        if (klass->inherits == 0) {
            return (wSymbol *)NULL;
        }

        /* look in superclass */
        klass = wSymbolLookup( klass->inherits );
    }
}


int wSymbolFindPropPos( wSymbol *klass, int stringIndex )
{
    char *propChar;
    wVariant *propName;

    /* get the name of the property */
    propName = (wVariant *)wGrowGet(wTheLiterals, stringIndex);
    wMemTest( propName, "wSymbolFindPropPos:propName" );

    /* get the text from the string */
    propChar = &(propName->value.string->text);
    wMemTest( propChar, "wSymbolFindMethod:propChar" );

    return wSymbolFindPropPosChar( klass, propChar );

}

int wSymbolFindPropPosChar( wSymbol *klass, char *name )
{
    int i;
    wSymbol *prop;

    /* check for no properties */
    if (klass->children == NULL) {
        return 0;
    }

    /* search children for property */


    /* search children for property */
    for ( i = 1; i <= klass->children->count; i++ ) {
        prop = wSymbolGetChild( klass, i );
        /* compare strings */
        if (strcmp( name, prop->name ) == 0 ) {
            return prop->stackPos;
        }
    }

    wErrorThrow( W_ERROR_NOSUCH, "Can't find property %s.%s", klass->name, name );
    return 0;
}


/* return what symbol is */
char *wSymbolGetName( char *name, int scope )
{
    wSymbol *symbol;
    symbol = wSymbolFind( name, scope );
    if (symbol == NULL) {
        return "a punctuation mark";
    } else {
        return wSymbolName[ symbol->type ];
    }
}



/* set as a child of the scope */
void wSymbolAddChild( wSymbol *parent, wSymbol *child )
{
    int index;

    wMemTest( parent, "wSymbolAddChild:parent" );
    wMemTest( child, "wSymbolAddChild:child" );

    /* does the parent have any children yet? */
    if (parent->children == NULL) {
        parent->children = wGrowNew( 8 );
    }

    /* add child's index to the array */
    wMemTest( parent->children, "wSymboAddChild:parent->children" );

    index = wGrowAppend( parent->children, child->index );
    child->stackPos = index;
}

/* find local variable with given index */
wSymbol *wSymbolGetChild( wSymbol *parent, int index )
{
    wGrow *children;

    wMemTest( parent, "wSymbolGetChild:parent" );

    /* get the parent symbol (current scope) */
    children = parent->children;

    /* no children? */
    if (children == NULL) {
        return NULL;
    }

    /* check the range */
    wMemTest( children, "wSymbolGetChild:children" );
    if (index > children->count) {
        wErrorThrow( W_ERROR_INTERNAL, "Index of child %d exceeds array for %s (wSymbolFindLocal)",
            index, parent->name );
    }

    /* get index of child */
    index = wGrowGet( children, index );

    return wSymbolLookup( index );
}


/* create local variable */
wSymbol *wSymbolNewLocal( char *name, int alias )
{
    int index, scope;
    wSymbol  *symbol;

    /* don't wMemTest name, it could be from a constant */

    /* ensure the name is good */
    wSymbolUnused( name );

    /* create an entry in the symbol table */
    symbol = (wSymbol *)wMalloc( sizeof( wSymbol ) );
    index = wGrowAppend( wTheSymbols, (int)symbol );
    wMemTest( symbol, "wSymbolNewLocal:symbol" );
    
    /* determine scope */
    scope = wParseGetScope();

    /* assign values */
    symbol->name = wCharCopy( name );
    symbol->tokenType = 0;
    symbol->index = index;
    symbol->next = 0;
    symbol->type = W_SYM_VARIABLE;
    symbol->typeCast = W_TYPE_VARIANT;
    symbol->scope = scope;
    symbol->children = NULL;
    symbol->alias = alias;
    symbol->inherits = 0;
    symbol->flags = 0;
    symbol->stackPos = 0;
    symbol->args = 0;
    symbol->optArgs = 0;
    symbol->varArgs = W_FALSE;
    symbol->method = NULL;
    symbol->builtin = NULL;
    symbol->pcode = NULL;
    symbol->called = 0;

    /* insert it into the hash table */
    wSymbolAddToHashTable( symbol );

    /* not an alias? */
    if (alias == 0) {
        /* make it a child of the current scope */
        wSymbolAddChild( wSymbolLookup( scope ), symbol );
    }
    return symbol;
}


/* aborts with error if arg count doesn't match */
void wSymbolCheckArgCount( wSymbol *symbol, int args )
{
    int minArgs, maxArgs;


    /* get the acceptable range of args */
    minArgs = symbol->args;
    maxArgs = minArgs + (symbol->optArgs);

    /* fixed number of arguments? */
    if (symbol->optArgs == 0 && !symbol->varArgs) {
        /* mismatch? */
        if (args != symbol->args ) {
            wErrorThrow( W_ERROR_ARGS, "Routine %s expects %d arguments, not %d (wSymbolCheckArgCount)",
                symbol->name, symbol->args, args );
        }

    /* too few arguments? */
    } else if (args < minArgs ) {
        wErrorThrow( W_ERROR_ARGS, "Routine %s expects at least %d arguments, not %d (wSymbolCheckArgCount)",
            symbol->name, symbol->args, args );
            
    /* too many arguments? */
    } else if (args > maxArgs && !symbol->varArgs) {
        wErrorThrow( W_ERROR_ARGS, "Routine %s expects only %d arguments, not %d (wSymbolCheckArgCount)",
            symbol->name, symbol->args, args );
    }
}


/* generate an error report for undefined routines */
void wSymbolUndefinedRoutines()
{
    int     count, i;
    wSymbol *symbol;

    /* look through symbol table */
    count = wTheSymbols->count;
    for ( i = 1; i <= count; i++ ) {
        symbol = wSymbolLookup( i );

        /* user routine? */
        if (symbol->type == W_SYM_FUNCTION || symbol->type == W_SYM_SUB) {
            /* undefined */
            if (symbol->pcode == NULL) {
                wErrorMessagef( "Warning", "Routine %s is referenced, but never defined" );
            }
        }
    }
}

/* returns true if symbol inherits class */
int wSymbolInherits( wSymbol *klass, int classIndex )
{
    while (1) {
        /* match? */
        if (klass->index == classIndex) {
            return W_TRUE;
        }

        /* can go to superclass? */
        if (klass->inherits) {
            /* set class to superclass */
            klass = wSymbolLookup( klass->inherits );
        } else {
            /* no match found */
            return W_FALSE;
        }

    }
}

/* ensure that all abstract methods in class are defined */
void wSymbolCheckAbstract( wSymbol *klass )
{
    int i, count, methodIndex;
    wSymbol *superclass, *theMethod, *latestMethod;

    /* if this class is abstract or doesn't inherit, skip the tests */
    if ((klass->flags & W_SYM_ISABSTRACT) 
    ||  (klass->inherits == 0)) {
        return;
    }

    /* get the superclass */
    superclass = wSymbolLookup( klass->inherits );

    /* skip test if superclass is not abstract */
    if (!(superclass->flags & W_SYM_ISABSTRACT)) {
        return;
    }

    /* walk the tree down */
    while (1) {
        /* look at each method */
        count = superclass->method->count;
        for (i = 1; i <= count; i++) {
            /* get a method */
            methodIndex = wGrowGet( superclass->method, i );
            theMethod = wSymbolLookup( methodIndex );

            /* is this an abstract method? */
            if (theMethod->flags & W_SYM_ISABSTRACT) {
                /* find the latest definition */
                latestMethod = wSymbolFindMethodChar( klass, theMethod->name );
                if (latestMethod->flags & W_SYM_ISABSTRACT) {
                    wErrorThrow( W_ERROR_SYNTAX, "Class %s must define abstract method %s",
                        klass->name, theMethod->name );
                }
            }
        }

        /* end of inheritance? */
        if (superclass->inherits == 0) {
            break;
        }

        /* get the superclass */
        superclass = wSymbolLookup( superclass->inherits );
    }
}
