/*************************************************************
    Name:       mem.c
    Purpose:    memory handling routines
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/

/* initialize memory tracking */
void wMemInit()
{
    /* currently, nothing to do */
}


/* find index of tracked memory in array */
wMemItem *wMemFind( void *ptr )
{
    wMemItem *link;

    /* null generates an error */
    if (ptr == NULL) {
        return NULL;
    }

    /* matches prior find? */
    if (wMemLastFind != NULL) {
        if (ptr <= wMemLastFind->memEnd && ptr >= wMemLastFind->memStart) {
            return wMemLastFind;
        }
    }

    /* walk through the linked list */
    link = wMemList;
    while (link != NULL) {
        if (ptr <= link->memEnd && ptr >= link->memStart) {
            break;
        }
        link = link->next;
    }
    wMemLastFind = link;
    return link;
}

/* ensure memory location was allocated */
void wMemIsGood( void *ptr, char *where )
{
    /* check it */
    if (wMemFind( ptr ) == NULL) {
        wErrorThrow( W_ERROR_INTERNAL, "Pointer %p not allocated in %s (wMemTest)", ptr, where );

    }
}

/* add tracked memory into array */
void wMemAdd( void *ptr, int size )
{
    wMemItem *link;

    /* is it already in memory? */
    link = wMemFind( ptr );
    if (link != NULL) {
        wErrorThrow( W_ERROR_INTERNAL, "Allocating the %p twice (wMemAdd)", ptr );
    }

    /* create a link and set up information */
    link = (wMemItem *)malloc( sizeof( wMemItem ) );
    link->memStart = ptr;

    /* yes, allocating 0 bytes does happen */
    if (size == 0) {
        link->memEnd = ptr;
    } else {
        link->memEnd = (void *)((int)ptr + size - 1);
    }

    /* link it to the start of the chain */
    link->next = wMemList;
    link->prior = NULL;
    
    if (wMemList != NULL) {
        wMemList->prior = link;
    }
    wMemList = link;
}

/* remove tracked memory link */
void wMemDelete( wMemItem *link )
{
    wMemItem *prior, *next;

    /* unlink next */
    next = link->next;
    if (next != NULL) {
        next->prior = link->prior;
    }

    /* unlink prior */
    prior = link->prior;
    if (prior != NULL) {
        prior->next = link->next;
    }

    /* clear last find? */
    if (wMemLastFind == link) {
        wMemLastFind = NULL;
    }

    /* memlist link? */
    if (link == wMemList) {
        wMemList = next;
    }

    /* free memory */
    free( (void *)link );
}


/* stop tracking memory */
void wMemRemove( void *ptr )
{
#ifdef __WDEBUG__
    wMemItem *link;
    
    if (ptr != NULL) {
        /* check memory list */
        link = wMemFind( ptr );
        if (link == NULL) {
            wErrorThrow( W_ERROR_INTERNAL, "Pointer %p not allocated (wFree)", ptr );
        } else {
            /* make sure it's the same address, not just in range */
            if (link->memStart != ptr) {
                wErrorThrow( W_ERROR_INTERNAL, "Pointer %p offset is wrong (wFree)", ptr );
            }
            wMemDelete( link );
        }
    }
#endif
}


/* safe version of malloc */
void *wMalloc( int size )
{
    void *data;

    /* size 0 is problematic */
    if (size == 0) {
        size = 32;
    }

    /* allocate the memory; use calloc to zero the data */
    data = calloc( 1, size );
    if (data == NULL) {
        wErrorThrow( W_ERROR_MEMORY, "Out of memory (wMalloc)" );
    }
    
#ifdef __WDEBUG__
    /* track the memory */
    wMemAdd( data, size );
#endif

    return data;
}

/* safe version of realloc */
void *wRealloc( void *ptr, int size )
{   
    void *data;
#ifdef __WDEBUG__
    wMemItem *link;

    /* see if it's in the list */
    link = wMemFind( ptr );    
    if (link == NULL) {
        wErrorThrow( W_ERROR_INTERNAL, "Pointer %p not allocated (wRealloc)", ptr );
    }
#endif

    /* check for reallocating zero bytes */
    if (size == 0) {
        /* do nothing */
        return ptr;
    }

    /* reallocate the memory? */
    data = realloc( ptr, size );
    if (data == NULL) {
        wErrorThrow( W_ERROR_MEMORY, "Out of memory (wRealloc)" );
    }

#ifdef __WDEBUG__
    /* update the link */
    link->memStart = (data);
    link->memEnd = (void *)((int)data + size - 1);
#endif

    return data;
}

/* safe version of free */
void wFree( void *ptr )
{
    if (ptr != NULL) {
#ifdef __WDEBUG__
        wMemRemove( ptr );
#endif
        /* free it */
        free( ptr );
    }
}


/* safe version of memmove */
void wMemMoveSafe( void *dst, void *src, int bytes, char *where )
{
#ifdef __WDEBUG__
    /* make sure the memory has been allocated */
    wMemItem *srcMem, *dstMem;

    /* search for pointers */
    srcMem = wMemFind( src );
    dstMem = wMemFind( dst );

    /* check range */
    if (srcMem == NULL) {
        wErrorThrow( W_ERROR_INTERNAL, "Source pointer %p not allocated (wMemMove:%s)", src, where );

    } else if (dstMem == NULL) {
        wErrorThrow( W_ERROR_INTERNAL, "Destination pointer %p not allocated (wMemMove:%s)", dst, where );

    } else if (bytes == 0) {
        /* don't need to test range */

    } else if (wMemFind( (void *)((int)src+(bytes-1)) ) != srcMem ) {
        wErrorThrow( W_ERROR_INTERNAL, "Source pointer %p outside range (wMemMove:%s)", src, where );

    } else if (wMemFind( (void *)((int)dst+(bytes-1)) ) != dstMem ) {
        wErrorThrow( W_ERROR_INTERNAL, "Destination pointer %p outside range (wMemMove:%s)", dst, where );
    }
#endif

    /* move the memory */
    memmove( dst, src, bytes );

}



