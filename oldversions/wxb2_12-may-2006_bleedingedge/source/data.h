/************************************************************
    Name:       data.h
    Purpose:    implementation of datatypes for wxBasic
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/

#ifndef WXBASIC_DATA_DECLARES
#define WXBASIC_DATA_DECLARES

/* variant data element */
struct wVariant {
    int dataType;           /* type of data */
    int typeCast;          /* expected datatype */
    union {
        wString *string;    /* W_TYPE_STRING */
        int integer;        /* W_TYPE_INTEGER */
        wNumber number;     /* W_TYPE_NUMBER */
        wObject *object;    /* W_TYPE_OBJECT */
        wArray *array;      /* W_TYPE_ARRAY */
        wGrow *table;       /* W_TYPE_TABLE */
        wGrow *list;        /* W_TYPE_LIST */
        wVariant *varptr;   /* W_TYPE_VARPTR */
        wSymbol *routine;   /* W_TYPE_ROUTINE */
        time_t time;        /* W_TYPE_DATETIME */
        int literal;        /* W_TYPE_LITERAL */
    } value ;
};


struct wVariantHandler {
    int     isNumeric;                  /* true for numeric datatypes */
    void    (*ref)(wVariant *dst);
    void    (*deref)(wVariant *dst);
    void    (*copy)(wVariant *dst, wVariant *src);
    void    (*move)(wVariant *dst, wVariant *src);
    void    (*fromChar)(wVariant *dst, char *buffer);
    char*   (*toChar)(wVariant *dst, int useQuotes );
    wNumber (*toNumber)(wVariant *src);
    int     (*compare)(wVariant *v1, wVariant *v2 );
    int     (*equal)(wVariant *v1, wVariant *v2 );
    void    (*index)(void);
    void    (*append)(void);     /* append item into collection */
    void    (*prepend)(void);    /* prepend item into collection */
    void    (*insertAt)(void);   /* insert item into collection */
    void    (*slice)(void);      /* return items from collection */
    void    (*delete)(void);     /* remove item from collection */
    void    (*find)(void);       /* find item in collection */
    void    (*iterate)(void);    /* iterate through items in collection */

};
        

enum {
    W_TYPE_VARIANT = 0,     /* NEVER SET A DATATYPE TO THIS! */
    W_TYPE_NOTHING,         /* undefined value */
    W_TYPE_INTEGER,         /* integer, used only in keys */
    W_TYPE_NUMBER,          /* float */
    W_TYPE_STRING,          /* char string */
    W_TYPE_OBJECT,          /* user defined object */
    W_TYPE_ARRAY,           /* static array */
    W_TYPE_TABLE,           /* dynamic array, keyed */
    W_TYPE_LIST,            /* dynamic array, ordered */
    W_TYPE_VARPTR,          /* pointer to a variant */
    W_TYPE_ROUTINE,         /* user defined routine */
    W_TYPE_DATETIME,        /* time */
    W_TYPE_LITERAL          /* value stored in literal table */
};

char *wDatatypeName[] = {
    "variant",
    "nothing",
    "integer",
    "number",
    "string",
    "object",
    "array",
    "table",
    "list",
    "varptr",
    "routine",
    "datetime"
};

wVariant *wVariantNew( void );
void wVariantRef( wVariant *src );
inline void wVariantDeref( wVariant *variant );
void wVariantCopy( wVariant *dst, wVariant *src );
void wVariantMove( wVariant *dst, wVariant *src );
void wVariantCoerce( wVariant *variant, int dataType );
int wVariantCompare( wVariant *v1, wVariant *v2 );
wNumber wVariantGetNumber( wVariant *variant );
char *wVariantGetStringChar( wVariant *variant );
void wVariantFilePrint( FILE *theFile, wVariant *v, int showQuotes );
void wVariantPrint( wVariant *v, int showQuotes );

#endif
#define WXBASIC_SHARED_DECLARES

