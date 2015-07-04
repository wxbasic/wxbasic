/*************************************************************
    Name:       keyword.c
    Purpose:    keywords for wxBasic
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/



/* add keywords to the symbol table */
void wKeywordInit()
{
    int i;
    wSymbol  *s;

    /* add each keyword in the list to the symbol table */
    for (i = 0; wKeywordList[i].name != NULL; i++) {
        /* already there? */
        s = wSymbolFind( wKeywordList[i].name, wTheCurrentScope );
        if (s==NULL) {
            s = wSymbolNew( wKeywordList[i].name, wTheGlobalScope, W_SYM_KEYWORD );
            s->tokenType = wKeywordList[i].value;
        } else {
            wErrorThrow( W_ERROR_INTERNAL, "wInitKeywords: keyword %s is already declared as a %s",
                wSymbolName[s->type] );
        }
    }
}
