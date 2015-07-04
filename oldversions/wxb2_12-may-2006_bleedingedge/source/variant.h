/************************************************************
    Name:       variant.h
    Purpose:    implementation of datatypes for wxBasic
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/

#ifndef WXBASIC_VARIANT_DECLARES
#define WXBASIC_VARIANT_DECLARES


/* variant data element */
struct wVariant {
    int dataType;           /* type of data */
    int typeCast;			/* expected datatype */	
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
    } value ;
};


struct wVariantHandler {
    wSymbol     *klass;
    int          isNumeric;
    void         (*ref)(wVariant *dst);
    void         (*deref)(wVariant *dst);
    void         (*copy)(wVariant *dst, wVariant *src);
    void         (*clone)(wVariant *dst, wVariant *src);
    void         (*fromNumber)(wVariant *dst, wNumber n );
    wNumber      (*toNumber)(wVariant *src);
    int          (*fromChar)(wVariant *dst, char *buffer);
    char*        (*toChar)(wVariant *dst, int useQuotes, int depthLimit );
    int          (*compare)(wVariant *v1, wVariant *v2 );
    int          (*equal)(wVariant *v1, wVariant *v2 );
    int          (*isTrue)(wVariant *v1);
    int          (*count)( wVariant *src );
    wVariant*    (*index)( wVariant *src, int indexCount );
    void         (*insert)( wVariant *dst, wVariant *value, wVariant *key );
    wVariant*    (*find)( wVariant *src, wVariant *key );
    void         (*remove)( wVariant *src, wVariant *key );
    void         (*append)( wVariant *src, wVariant *value );
    void         (*prepend)( wVariant *src,wVariant *value );
    void         (*slice)( wVariant *vDst, wVariant *vSrc, int startOf, int endOf );
    int          (*iterate)( wVariant *vSrc, wVariant *vIndex, wVariant *vArg1, wVariant *vArg2 );
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
    W_TYPE_DATETIME         /* time */
};

char *wDataTypeName[] = {
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

void wVariantInit(void);
void wVariantAddMethod( int dataType, char *method, void (*routine)(void), int reqCount, int optCount );
wVariant *wVariantNew( void );
void wVariantRef( wVariant *src );
void wVariantDeref( wVariant *src );
void wVariantCopy( wVariant *dst, wVariant *src );
void wVariantClone( wVariant *dst, wVariant *src );
void wVariantMove( wVariant *dst, wVariant *src );
void wVariantClone( wVariant *dst, wVariant *src );
void wVariantCoerce( wVariant *variant, int dataType );
int wVariantCompare( wVariant *v1, wVariant *v2 );
int wVariantEqual( wVariant *v1, wVariant *v2 );
int wVariantIsTrue( wVariant *v1 );
wNumber wVariantGetNumber( wVariant *variant );
char *wVariantToChar( wVariant *src, int useQuotes, int limit );
void wVariantFromChar( wVariant *dst, char *buffer, int coerceFrom, int coerceTo );
void wVariantFilePrint( FILE *theFile, wVariant *src, int showQuotes );
void wVariantPrint( wVariant *v, int showQuotes );
void wVariantMethodCheckArgs( char *name, int expect, int actual );
wVariant *wVariantIndex( wVariant *vSrc, int indexCount );
void wVariantAdd( wVariant *vSrc, wVariant *value, wVariant *key );
int wVariantIterate( wVariant *vSrc, wVariant *vIndex, wVariant *vArg1, wVariant *vArg2 );
void wVariantSlice( wVariant *vDst, wVariant *vSrc, int startOf, int endOf );
void wVariantAppend( wVariant *vDst, wVariant *value );
void wVariantPrepend( wVariant *vDst, wVariant *value );
int wVariantCount( wVariant *vSrc );
void wVariantMethodGetType( void );
void wVariantMethodToString( void );
void wVariantMethodEqual( void );
void wVariantMethodCompare( void );
void wVariantMethodIsTrue( void );
void wVariantMethodAppend( void );
void wVariantMethodPrepend( void );
void wVariantMethodClone( void );
void wVariantMethodCount( void );
void wVariantMethodIsNumeric( void );

#endif
