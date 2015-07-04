/*************************************************************
    Name:       keyword.c
    Purpose:    keywords for wxBasic
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/

#ifndef WXBASIC_KEYWORD_DECLARES
#define WXBASIC_KEYWORD_DECLARES


typedef struct wKeyword wKeyword;

struct wKeyword {
    char    *name;
    int     value;
};

wKeyword wKeywordList[] = {
    { "abstract",   W_TOKEN_ABSTRACT	},
    { "and",        W_TOKEN_AND         },
    { "as",         W_TOKEN_AS          },
    { "break",      W_TOKEN_BREAK       },
    { "case",       W_TOKEN_CASE        },
    { "catch",      W_TOKEN_CATCH       },
    { "class",      W_TOKEN_CLASS       },
    { "close",      W_TOKEN_CLOSE       },
    { "const",      W_TOKEN_CONST       },
    { "constant",   W_TOKEN_CONST       },
    { "continue",   W_TOKEN_CONTINUE    },
    { "dim",        W_TOKEN_DIM         },
    { "do",         W_TOKEN_DO          },
    { "each",       W_TOKEN_EACH        },
    { "else",       W_TOKEN_ELSE        },
    { "elseif",     W_TOKEN_ELSEIF      },
    { "elsif",      W_TOKEN_ELSEIF      },
    { "end",        W_TOKEN_END         },
    { "erase",      W_TOKEN_ERASE       },
    { "exit",       W_TOKEN_EXIT        },
    { "finally",    W_TOKEN_FINALLY     },
    { "for",        W_TOKEN_FOR         },
    { "function",   W_TOKEN_FUNCTION    },
    { "global",     W_TOKEN_GLOBAL      },
    { "handles",    W_TOKEN_HANDLES     },
    { "if",         W_TOKEN_IF          },
    { "in",         W_TOKEN_IN          },
    { "inherits",   W_TOKEN_INHERITS    },
    { "input",      W_TOKEN_INPUT       },
    { "inv",        W_TOKEN_INV         },
    { "is",         W_TOKEN_IS          },
    { "line",       W_TOKEN_LINE        },
    { "me",         W_TOKEN_ME          },
    { "mod",        W_TOKEN_MOD         },
    { "mybase",     W_TOKEN_MYBASE      },
    { "new",        W_TOKEN_NEW         },
    { "next",       W_TOKEN_NEXT        },
    { "noconsole",  W_TOKEN_NOCONSOLE   },
    { "not",        W_TOKEN_NOT         },
    { "nothing",    W_TOKEN_NOTHING     },
    { "open",       W_TOKEN_OPEN        },
    { "option",     W_TOKEN_OPTION      },
    { "or",         W_TOKEN_OR          },
    { "output",     W_TOKEN_OUTPUT      },
    { "print",      W_TOKEN_PRINT       },
    { "qbasic",     W_TOKEN_QBASIC      },
    { "redo",       W_TOKEN_REDO        },
    { "return",     W_TOKEN_RETURN      },
    { "select",     W_TOKEN_SELECT      },
    { "self",       W_TOKEN_SELF        },
    { "shared",     W_TOKEN_SHARED      },
    { "shl",        W_TOKEN_SHL         },
    { "shr",        W_TOKEN_SHR         },
    { "static",     W_TOKEN_STATIC      },
    { "step",       W_TOKEN_STEP        },
    { "sub",        W_TOKEN_SUB         },
    { "then",       W_TOKEN_THEN        },
    { "throw",      W_TOKEN_THROW       },
    { "to",         W_TOKEN_TO          },
    { "try",        W_TOKEN_TRY         },
    { "until",      W_TOKEN_UNTIL       },
    { "virtual",    W_TOKEN_VIRTUAL	},
    { "wend",       W_TOKEN_WEND        },
    { "while",      W_TOKEN_WHILE       },
    { "xor",        W_TOKEN_XOR         },
    { NULL,         0                   }
};


void wKeywordInit(void);

#endif
