/*************************************************************
    Name:       wtable.h
    Purpose:    W_TYPE_TABLE datatype: table datatype
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/

#ifndef WXBASIC_WTABLE_DECLARES
#define WXBASIC_WTABLE_DECLARES


/* element in hashtable */
struct wTableElement {
    wVariant key;       /* key, either wString or Integer */
    wVariant value;     /* data */
    void *prior;        /* prior element in chain */
    void *next;         /* next element in chain */
};

void wTableRegisterMethods( void );
void wTableRef( wVariant *src );
void wTableDeref( wVariant *vSrc );
wTableElement *wTableElementCreate( wGrow *table, wTableElement *prior, wVariant *key, wVariant *value );
void wTableCopy( wVariant *dst, wVariant *src );
void wTableClone( wVariant *dst, wVariant *src );
char *wTableToChar( wVariant *vSrc, int useQuotes, int limit );
int wTableGetIntHashValue( int i );
int wTableGetCharHashValue( char *letters );
int wTableGetHashValue( wVariant *key );
wTableElement *wTableFindIntKey( wGrow *table, int key, int *flag );
wTableElement *wTableFindStringKey( wGrow *table, wVariant *key, int *flag );
wTableElement *wTableLookup( wGrow *table, wVariant *key, int *flag );
wVariant *wTableIndex( wVariant *vSrc, int indexCount );
wVariant *wTableFind( wVariant *vSrc, wVariant *key );
void wTableInsert( wVariant *vSrc, wVariant *key, wVariant *value );
void wTableRemove( wVariant *vSrc, wVariant *vKey );
void wTableNew( wVariant *dest );
int wTableIterate( wVariant *vTable, wVariant *vIndex, wVariant *vArg1, wVariant *vArg2  );
int wTableCount( wVariant *vSrc );
int wTableMethod( wVariant *vSrc, char *name, int argCount );
void wTableMethodInsert( void );
void wTableMethodRemove( void );
int wTableHasKey( wVariant *source, wVariant *key );
void wTableMethodHasKey( void );

#endif
