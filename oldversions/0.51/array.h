/*
    Name:       array.h
    Purpose:    array structures for wxBasic
    Author:     David Cuny
    Copyright:  (c) 2002 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*/

struct wArrayCell {
    char    *key;               /* key */
    wVariant data;              /* data stored in cell */
};

struct wArray {
    int     indexes;                    /* count of indexes */
    int     elements;                   /* total number of elements */
    int     lower[W_MAX_INDEXES];       /* lower range of index */
    int     upper[W_MAX_INDEXES];       /* upper range of index */
    int     offset[W_MAX_INDEXES];      /* offset per index */
    int     isDynamic;                  /* dynamic array? */
    union {
        wVariant     *item;     /* variant static data array */
        wArrayCell   *cell;     /* dynamic data array */
    } data;
};


wArray *wCreateStaticArray( wSymbol *s );
wArray *wCreateDynamicArray( wSymbol *s );
wSymbol *wCreateArraySymbol( char *name, int args );
wArray *wGetArray( wSymbol *s );
int wGetStaticIndex( wArray *array, wSymbol *s );
char *wBuildKey( wArray *array, wSymbol *s );
int wFindKey( wArray *array, wSymbol *s, char *key );
void wGetDynamicValue( wArray *array, wSymbol *s );
int wGetDynamicKey( wArray *array, int index );
void wResizeDynamicArray( wArray *array );
void wInsertDynamicCell( wArray *array, int pos );
void wSetDynamicValue( wArray *array, wSymbol *s );
void wGetArrayElement( wSymbol *s );
void wSetArrayElement( wSymbol *s );
void wPushArray( wSymbol *s );
void wEraseArrayElement( wSymbol *s );
void wEraseArray( wSymbol *s );
void wFreeArray( wArray *array );
int wGetArrayIndexes( void );
int wGetArrayBound( int index, int upper );
