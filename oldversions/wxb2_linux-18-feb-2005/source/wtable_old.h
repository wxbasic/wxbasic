/*************************************************************
    Name:       wtable.h
    Purpose:    W_TYPE_TABLE datatype: table datatype
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/

/* element in table */
struct wTableElement {
    wVariant key;       /* key, either wString or Integer */
    wVariant value;      /* data */
};

void wTableRegisterMethods( void );
void wTableRef( wVariant *src );
void wTableDeref( wVariant *vSrc );
void wTableCopy( wVariant *dst, wVariant *src );
void wTableClone( wVariant *dst, wVariant *src );
char *wTableToChar( wVariant *vSrc, int useQuotes );
int wTableFindIntKey( wGrow *table, int key );
int wTableFindStringKey( wGrow *table, wString *key );
int wTableLookup( wGrow *table, wVariant *key );
void wTableInsertElementAt( wGrow *table, wTableElement *element, int index );
wVariant *wTableIndex( wVariant *vSrc, int indexCount );
wVariant *wTableFind( wVariant *vSrc, wVariant *key );
void wTableInsert( wVariant *vSrc, wVariant *key, wVariant *value );
void wTableRemove( wVariant *vSrc, wVariant *key );
void wTableNew( wVariant *dest, int size );
int wTableIterate( wVariant *vTable, wVariant *vIndex, wVariant *vArg1, wVariant *vArg2  );
int wTableCount( wVariant *vSrc );
int wTableMethod( wVariant *vSrc, char *name, int argCount );
