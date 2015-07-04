/*
    Name:       data.h
    Purpose:    builtin types in wxBasic
    Author:     David Cuny
    Copyright:  (c) 2002 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*/

union wValue {
    wNumber  number;        /* number */
    char    *string;        /* pointer to string */
    wArray   *array;        /* address of array */
    wVariant *ref;          /* pointer to variant */
};

struct wVariant {
    int  datatype;          /* number, string or array */
    wValue value;           /* actual data value */
};

/* data types */
enum {
    W_DATA_UNDEFINED = 0, /* undefined, error */
    W_DATA_REF,           /* pointer to variant */
    W_DATA_NUMBER,        /* number */
    W_DATA_STRING,        /* pointer to string */
    W_DATA_ARRAY,         /* pointer to array */
    W_DATA_OBJECT         /* index to wrapped object */
};

char *wDatumName[] = {
    "Undefined",
    "Reference",
    "Number",
    "String",
    "Array",
    "Object"
};

/* the stack */
#define W_STACK_MAX (int) 4096      /* maximum stack size */
wVariant wData[W_STACK_MAX];        /* stack, also holds locals */
int     wTos = 0;                   /* top of stack */
int     wGlobals = 0;               /* count of global variables */
int     wLocalStart = 0;            /* position of first local in stack */
int     wStackMax = W_STACK_MAX-2;  /* maximum stack height */

void wFormatNumber( char *buffer, wNumber n );
int wAddGlobalToStack(void);
void wPushNumber( wNumber value );
wVariant *wGetStackPointer( int index );
void wDropTos(void);
wNumber wPopNumber(void);
void wPushStringCopy( char *string );
void wPushString( char *string );
char *wPopString(void);
void wCopyStackItem( int index );
int wGetStackType( int index );
void wPrintTos(void);
void wPrintStack(void);
