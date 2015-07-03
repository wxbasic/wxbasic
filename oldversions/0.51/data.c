/*
    Name:       data.c
    Purpose:    builtin types in wxBasic
    Author:     David Cuny
    Copyright:  (c) 2002 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*/

/* format number in buffer, remove trailing zeros */
void wFormatNumber( char *buffer, wNumber n )
{
    int     i;

    /* no floating point? */
    if (floor(n) == n) {
        sprintf( buffer, W_NUMBER_INT_FORMAT, n );

    } else {
        /* format with floating point */
        sprintf( buffer, W_NUMBER_FLOAT_FORMAT, n );
    
        /* search for non-zero */
        for( i = strlen(buffer)-1; i > 0; i-- ) {
            if (buffer[i] != '0') {
                break;
            } else if (buffer[i-1] != '.') {
                buffer[i] = '\0';
            }
        }
    }
}



/* return index for global on stack */
int wAddGlobalToStack()
{
    wGlobals++;
    wStackMax--;
    if (wTos == wStackMax) {
        wFatal( W_RUNTIME, "addGlobalToStack: out of stack space");
    }
    return wStackMax+1;
}

/* push a number onto the stack */
void wPushNumber( wNumber value )
{
    if (wTos == wStackMax) {
        wFatal( W_RUNTIME, "pushNumber: stack overflow" );
    }

    wTos++;
    wData[wTos].datatype = W_DATA_NUMBER;
    wData[wTos].value.number = value;
}

/* return pointer from stack */
wVariant *wGetStackPointer( int index )
{
    /* indirected? */
    if (wData[index].datatype == W_DATA_REF) {
        return wData[index].value.ref;
    } else {
        return &wData[index];
    }
}


/* remove top of stack and discard */
void wDropTos()
{
    /* need to free? */
    if (wData[wTos].datatype == W_DATA_STRING) {
        wFree( wData[wTos].value.string );
    }
    wData[wTos--].datatype = W_DATA_UNDEFINED;
}

/* pop a number off the stack */
wNumber wPopNumber()
{
    wNumber  result;
    wVariant *v;

    if (wTos==0) {
        wFatal( W_RUNTIME, "popNumber: stack underflow" );
    }

    v = wGetStackPointer( wTos );
    switch (v->datatype) {
    case W_DATA_NUMBER:
    case W_DATA_OBJECT:
        wTos--;
        return v->value.number;

    case W_DATA_STRING:
        result = (wNumber)atof(v->value.string);

        /* need to free? */
        if (wData[wTos].datatype == W_DATA_STRING) {
            wFree( wData[wTos].value.string );
            wData[wTos].datatype = W_DATA_UNDEFINED;
        }
        wTos--;
        return result;

    default:
        /* silently fail... */
        wTos--;
        return 0;
    }
}


/* push a copy of a string onto the stack */
void wPushStringCopy( char *string )
{
    if (wTos == wStackMax) {
        wFatal( W_RUNTIME, "pushStringCopy: stack overflow" );
    }

    wTos++;
    wData[wTos].datatype = W_DATA_STRING;
    if (string==NULL) {
        wData[wTos].value.string = wCopyString("");
    } else {
        wData[wTos].value.string = wCopyString( string );
    }
}

/* push a String onto the stack, no copy */
void wPushString( char *string )
{

    if (wTos==wStackMax) {
        wFatal( W_RUNTIME, "PushString: stack overflow" );
    }

    wTos++;
    wData[wTos].datatype = W_DATA_STRING;
    if (string==NULL) {
        wData[wTos].value.string = wCopyString("");
    } else {
        wData[wTos].value.string = string;
    }
}


/* pop a string off the stack */
char *wPopString()
{
    char    *string;    
    wVariant *v;
    char    buffer[32];

    if (wTos==0) {
        wFatal( W_RUNTIME, "PopString: stack underflow" );
    }

    v = wGetStackPointer( wTos );
    if (wData[wTos].datatype == W_DATA_STRING) {
        /* string on stack */
        string = v->value.string;
        v->datatype = W_DATA_UNDEFINED;

    } else if (v->datatype == W_DATA_STRING) {
        /* copy from ref */
        string = wCopyString( v->value.string );

    } else if (v->datatype == W_DATA_NUMBER) {
        wFormatNumber( buffer, v->value.number );
        string = wCopyString( buffer );

    } else {
        /* create an empty string */
        string = wCopyString("");        
    }
    wTos--;
    return string;
}

/* copy stack item to top of stack */
void wCopyStackItem( int index )
{

    if (wTos == wStackMax) {
        wFatal( W_RUNTIME, "copyStackItem: stack overflow" );
    }
    wTos++;

    switch (wData[index].datatype) {
    case W_DATA_UNDEFINED:
        wData[wTos].datatype = W_DATA_UNDEFINED;
        break;

    case W_DATA_REF:
        wData[wTos].datatype = W_DATA_REF;
        wData[wTos].value.ref = wData[index].value.ref;
        break;

    case W_DATA_NUMBER:
    case W_DATA_STRING:
    case W_DATA_OBJECT:
        wData[wTos].datatype = W_DATA_REF;
        wData[wTos].value.ref = wGetStackPointer( index );
        break;
        
    case W_DATA_ARRAY:
        wData[wTos].datatype = wData[index].datatype;
        wData[wTos].value.array = wData[index].value.array;
        break;

    default:
        wFatal( W_RUNTIME, "copyStackItem: unknown data type: %s",
            wDatumName[ wData[index].datatype ] );
    }
}


/* return datatype of item on stack */
int wGetStackType( int index )
{
    wVariant *v;
    v = wGetStackPointer( index );
    return v->datatype;
}


/* print top of stack item, core of print routine */
void wPrintTos()
{
    char    *string;
    char    buffer[32];
    int     typeOf;

    typeOf = wGetStackType( wTos );
    switch (typeOf) {
    case W_DATA_NUMBER:
        wFormatNumber( buffer, wPopNumber() );
        wConsole( "%s", buffer );
        break;

    case W_DATA_STRING:
        string = wPopString();
        wConsole( "%s", string );
        wFree( string );
        break;

    case W_DATA_OBJECT:
        wConsole( "%d", (int)wPopNumber() );

    default:
        wFatal( W_RUNTIME, "printTos: can't print %s", wDatumName[typeOf] );
    }
}

/* display stack for debugging */
void wPrintStack()
{
    int     i;
    char    flag;
    wVariant *v;

    for ( i = 0; i <= wTos; i++ ) {

        v = wGetStackPointer( i );
        if (wData[i].datatype == W_DATA_REF) {
            flag = '*';
        } else {
            flag = ' ';
        }

        switch (v->datatype) {
        case W_DATA_UNDEFINED:
            wConsole( "(%d)->undefined ", i );
            break;
        case W_DATA_NUMBER:
            wConsole( "(%d)->%c%Lf ", i, flag, v->value.number );
            break;
        case W_DATA_STRING:
            wConsole( "(%d)->%c%s ", i, flag, v->value.string );
            break;
        case W_DATA_ARRAY:
            wConsole( "(%d)->array ", i );
            break;
        case W_DATA_REF:
            wConsole( "(%d)->REF ", i );
        case W_DATA_OBJECT:
            wConsole( "(%d)->OBJ:%Lf ", i, v->value.number );
            break;
        default:
            wConsole( "(%d)->%s ", i, wDatumName[wData[i].datatype] );
            break;
        }
        if (i==wLocalStart){
            wConsole("[LOCALS]");
        }
    }
    wConsole( "[TOS]\n" );
}
