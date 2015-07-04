/*************************************************************
    Name:       wvarptr.c
    Purpose:    W_TYPE_VARPTR datatype
	Author:     David Cuny
	Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
	Licence:    LGPL
*************************************************************/

void wVarPtrRegisterMethods()
{
    /* register the routines */
    wTheHandler[W_TYPE_VARPTR]->isNumeric       = W_FALSE;
    wTheHandler[W_TYPE_VARPTR]->ref             = wVarPtrRef;
    wTheHandler[W_TYPE_VARPTR]->deref           = wVarPtrDeref;
// FIXME: is this supposed to copy data or error out?
//    wTheHandler[W_TYPE_VARPTR]->copy            = wVarPtrCopyData;
    wTheHandler[W_TYPE_VARPTR]->copy            = NULL;
    wTheHandler[W_TYPE_VARPTR]->clone           = NULL;
    wTheHandler[W_TYPE_VARPTR]->fromNumber      = NULL;
    wTheHandler[W_TYPE_VARPTR]->toNumber        = NULL;
    wTheHandler[W_TYPE_VARPTR]->fromChar        = NULL;
    wTheHandler[W_TYPE_VARPTR]->toChar          = wVarPtrToChar;
    wTheHandler[W_TYPE_VARPTR]->compare         = NULL;
    wTheHandler[W_TYPE_VARPTR]->equal           = NULL;
    wTheHandler[W_TYPE_VARPTR]->isTrue          = NULL;
    wTheHandler[W_TYPE_VARPTR]->count           = NULL;
    wTheHandler[W_TYPE_VARPTR]->index           = NULL;
    wTheHandler[W_TYPE_VARPTR]->find            = NULL;
    wTheHandler[W_TYPE_VARPTR]->remove          = NULL;
    wTheHandler[W_TYPE_VARPTR]->append          = NULL;
    wTheHandler[W_TYPE_VARPTR]->prepend         = NULL;
    wTheHandler[W_TYPE_VARPTR]->slice           = NULL;
    wTheHandler[W_TYPE_VARPTR]->iterate         = NULL;
}

/* refcount the item the VARPTR points to */
void wVarPtrRef( wVariant *src )
{
	/* refcount the referenced value */
	wVariantRef( src->value.varptr );
}

void wVarPtrDeref( wVariant *src )
{
	/* deref the object being pointed to */
	wVariantDeref( src->value.varptr );
}

/* copy the value of the VARPTR from src to dst */
void wVarPtrCopyData( wVariant *dst, wVariant *src )
{	
	dst->value.varptr = src->value.varptr;
}


char *wVarPtrToChar( wVariant *src, int useQuotes, int limit )
{
	char *buffer, *tmpBuffer;

	/* get the value pointed to */
    tmpBuffer = wVariantToChar( src->value.varptr, W_TRUE, limit );

	/* build a buffer to hold it plus quotes */
	buffer = (char *)wMalloc( strlen( tmpBuffer ) + 32 );

	/* build the quoted version */
	sprintf( buffer, "varptr@%p:%s", src->value.varptr, tmpBuffer );

	/* free the temp buffer */
	wFree( tmpBuffer );

	return buffer;
}
