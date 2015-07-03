/*
    Name:       keyword.c
    Purpose:    keywords for wxBasic
    Author:     David Cuny
    Copyright:  (c) 2002 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*/

/* not in .h file because of load order */
wKeyword wKeywordList[] = {
    { "and",        W_TOKEN_AND         },
    { "append",     W_TOKEN_APPEND      },
    { "as",         W_TOKEN_AS          },
    { "case",       W_TOKEN_CASE        },
    { "close",      W_TOKEN_CLOSE       },
    { "const",      W_TOKEN_CONST       },
    { "continue",   W_TOKEN_CONTINUE    },
    { "common",     W_TOKEN_COMMON      },
    { "declare",    W_TOKEN_DECLARE     },
    { "delete",     W_TOKEN_DELETE      },
    { "dim",        W_TOKEN_DIM         },
    { "do",         W_TOKEN_DO          },
    { "each",       W_TOKEN_EACH        },
    { "else",       W_TOKEN_ELSE        },
    { "elseif",     W_TOKEN_ELSEIF      },
    { "elsif",      W_TOKEN_ELSEIF      },
    { "end",        W_TOKEN_END         },
    { "erase",      W_TOKEN_ERASE       },
    { "exit",       W_TOKEN_EXIT        },
    { "explicit",   W_TOKEN_EXPLICIT    },
    { "for",        W_TOKEN_FOR         },
    { "function",   W_TOKEN_FUNCTION    },
    { "global",     W_TOKEN_COMMON      },
    { "if",         W_TOKEN_IF          },
    { "in",         W_TOKEN_IN          },
    { "include",    W_TOKEN_INCLUDE_FILE},
    { "input",      W_TOKEN_INPUT       },
    { "inv",        W_TOKEN_INV         },
    { "is",         W_TOKEN_IS          },
    { "line",       W_TOKEN_LINE        },
    { "mod",        W_TOKEN_MOD         },
    { "new",        W_TOKEN_NEW         },
    { "next",       W_TOKEN_NEXT        },
    { "noconsole",  W_TOKEN_NOCONSOLE   },
    { "not",        W_TOKEN_NOT         },
    { "open",       W_TOKEN_OPEN        },
    { "option",     W_TOKEN_OPTION      },
    { "or",         W_TOKEN_OR          },
    { "output",     W_TOKEN_OUTPUT      },
    { "print",      W_TOKEN_PRINT       },
    { "qbasic",     W_TOKEN_QBASIC      },
    { "redim",      W_TOKEN_REDIM       },
    { "return",     W_TOKEN_RETURN      },
    { "select",     W_TOKEN_SELECT      },
    { "shared",     W_TOKEN_SHARED      },
    { "shl",        W_TOKEN_SHL         },
    { "shr",        W_TOKEN_SHR         },
    { "static",     W_TOKEN_STATIC      },
    { "step",       W_TOKEN_STEP        },
    { "sub",        W_TOKEN_SUB         },
    { "then",       W_TOKEN_THEN        },
    { "to",         W_TOKEN_TO          },
    { "until",      W_TOKEN_UNTIL       },
    { "wend",       W_TOKEN_WEND        },
    { "while",      W_TOKEN_WHILE       },
    { "xor",        W_TOKEN_XOR         },
    { 0,            0           }
};


/* add keywords to the symbol table */
void wInitKeywords()
{
    int i;
    wSymbol  *s;
    
    for (i = 0; wKeywordList[i].name != NULL; i++) {  
        s = wFindSymbol( wKeywordList[i].name, NULL );
        if (s==NULL) {
            s = wAddSymbol( wKeywordList[i].name, NULL, W_SYM_KEYWORD, W_FALSE );
            s->klass = wKeywordList[i].value;
        } else {
            wFatal( W_INIT, "wInitKeywords: keyword %s is already declared as a %s",
                wSymbolName[s->symbolType] );
        }
    }
}
