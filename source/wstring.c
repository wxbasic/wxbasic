/*************************************************************
    Name:       wstring.c
    Purpose:    builtin string datatype
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/

void wStringRegisterMethods()
{
    /* register the routines */
    wTheHandler[W_TYPE_STRING]->isNumeric       = W_FALSE;
    wTheHandler[W_TYPE_STRING]->ref             = wStringRef;
    wTheHandler[W_TYPE_STRING]->deref           = wStringDeref;
    wTheHandler[W_TYPE_STRING]->copy            = wStringCopy;
    wTheHandler[W_TYPE_STRING]->clone           = wStringClone;
    wTheHandler[W_TYPE_STRING]->fromNumber      = NULL;
    wTheHandler[W_TYPE_STRING]->toNumber        = wStringToNumber;
    wTheHandler[W_TYPE_STRING]->fromChar        = wStringFromChar;
    wTheHandler[W_TYPE_STRING]->toChar          = wStringToChar;
    wTheHandler[W_TYPE_STRING]->compare         = wStringCompare;
    wTheHandler[W_TYPE_STRING]->equal           = wStringEqual;
    wTheHandler[W_TYPE_STRING]->isTrue          = wStringIsTrue;
    wTheHandler[W_TYPE_STRING]->count           = wStringCount;
    wTheHandler[W_TYPE_STRING]->index           = wStringFindIndex;
    wTheHandler[W_TYPE_STRING]->find            = NULL;
    wTheHandler[W_TYPE_STRING]->remove          = NULL;
    wTheHandler[W_TYPE_STRING]->append          = wStringConcat;
    wTheHandler[W_TYPE_STRING]->prepend         = NULL;
    wTheHandler[W_TYPE_STRING]->slice           = wStringSubstr;
    wTheHandler[W_TYPE_STRING]->iterate         = wStringIterate;


    wTheHandler[W_TYPE_LIST]->insert        = wListInsert;

    /* create a string to hold indexed strings */
    wTheIndexedString = wVariantNew();
}

/* refcount a string */
void wStringRef( wVariant *src )
{
    wMemTest( src, "wStringRef:src->value.src" );
    wMemTest( &(src->value.string), "wStringRef:src->value.string" );
    src->value.string->refCount++;
}

/* dereference a string */
void wStringDeref( wVariant *src )
{
    wString *s;
    
    /* get the string */
    s = src->value.string;
    wMemTest( src->value.string, "wStringDeref:value.string" );

    /* decrement reference count */
    s->refCount--;

    /* if no more references, destroy string */
    if (s->refCount < 1) {
        wFree( s );
    }
}


/* copy variant data */
void wStringCopy(wVariant *dst, wVariant *src)
{
    wMemTest( src->value.string, "wStringCopyVariantData:src->value.string" );
    dst->value.string = src->value.string;    
}

/* dst gets a unique copy of src */
void wStringClone( wVariant *dst, wVariant *src )
{
    /* this probably isn't really needed, since wStringCopy will create a   */
    /* refcounted string. But it'll be more efficient if clone() is used.   */

    wString *oldString;

    /* get the string */
    oldString = src->value.string;
    wMemTest( oldString, "wStringClone:oldString" );

    /* create a new wString */
    wStringNew( dst, &(oldString->text), oldString->length );

}



/* create from char */
int wStringFromChar( wVariant *dst, char *buffer )
{
	int length;
	wString *newString;

	/* get the length of the string */
	length = strlen( buffer );

    /* create a string */
    newString = (wString *)wMalloc( sizeof( wString ) + (length+1) );
    newString->refCount = 1;
    newString->length = length;
    wMemMove( (void *)&(newString->text), (void *)buffer, length+1, "wStringFromChar" );

    /* place into the variant */
    dst->value.string = newString;
    return W_TRUE;
}


/* return pointer to char buffer */
char *wStringChar(wVariant *src)
{	
	/* get the buffer */
	return &(src->value.string->text);
}


/* convert to char */
char *wStringToChar(wVariant *src, int useQuotes, int limit )
{	
    int stringSize, bufferSize;
    char *buffer;

    /* get the size of the string */
    stringSize = src->value.string->length;

    /* allocate space for terminator, and possibly quotes */
    bufferSize = stringSize + 1;
    if (useQuotes) {
        bufferSize += 2;
    }

    /* allocate a buffer */
    buffer = (char *)wMalloc( bufferSize );
    
    /* move string to the buffer */
    if (useQuotes) {
        /* move string */
        wMemMove( (void *)(buffer+1), (void *)wStringChar(src), stringSize, "wStringToChar" );
        /* add quotes */
        buffer[0] = '\"';
        buffer[stringSize+1] = '\"';
        buffer[stringSize+2] = '\0';
    } else {
        /* move the string, including the terminator */
        wMemMove( (void *)buffer, (void *)wStringChar(src), stringSize+1, "wStringToChar" );
    }        

	return buffer;
}


/* convert to a number */
wNumber wStringToNumber(wVariant *src)
{
    wNumber n;

    wMemTest( src, "wStringToNumber:variant" );

    /* convert to a number */
    if (sscanf( wStringChar(src), "%f", &n ) != 1) {
        wErrorThrow( W_ERROR_CONVERT, "Unable to convert String \"%s\" to Number",
            wStringChar(src) );
		n = (wNumber)0;
    }
    return n;
}


/* compare one string to another */
int wStringCompare( wVariant *v1, wVariant *v2 )
{
    // FIXME! This should be a macro, or inline, or something...
    return wStringCompareString( v1->value.string, v2->value.string );
}

/* compare one string to another */
int wStringCompareString( wString *s1, wString *s2 )
{
    int i, length1, length2, length, diff;
    char *text1, *text2;

    wMemTest( s1, "wStringCompare:s1" );
    wMemTest( s2, "wStringCompare:s2" );

    /* the lengths */
    length1 = s1->length;
    length2 = s2->length;

    /* the value */
   	text1 = &(s1->text);
    text2 = &(s2->text);

    /* handle simple cases */
    if (text1 == text2)  {
            return 0;
            
    } else if (length1 == 0 && length2 == 0) {
            return 0;
            
    } else if (length1 == 0) {
            return 1;
            
    } else if (length2 == 0) {
            return -1;
            
    } else {
        /* walk shortest distance */
        if (length1 < length2) {
            length = length1;
        } else {
            length = length2;
        }

        /* character by character comparison. */
        for ( i = 0; i < length; i++ ) {
            /* compare the characters */
            diff = text1[i] - text2[i];
            if (diff !=0) {
                if (diff > 0) {
                    return 1;
                } else {
                    return -1;
                }
            }
        }
    }

    /* compare which is longest */
    if (length1 == length2) {
        return 0;
    } else if (length1 > length2) {
        return 1;
    } else {
        return -1;
    }
}


/* check strings for exact equality */
int wStringEqual( wVariant *s1, wVariant *s2 )
{
    wMemTest( s1, "wStringEqual:s1" );
    wMemTest( s2, "wStringEqual:s2" );

	/* check if it's the same string */
	if (s1->value.string == s2->value.string) {
		return W_TRUE;
	} else {
		/* use compare */
		return (wStringCompare( s1, s2 ) == 0);
	}
}


/* check strings for exact equality */
int wStringIsTrue( wVariant *s1 )
{
    wMemTest( s1, "wStringIsTrue:s1" );

    /* true if it has a length */
    return (s1->value.string->length != 0);
}


/* create a wString, and copy the value if not NULL */
void wStringNew( wVariant *variant, char *text, int length )
{    
    wString *newString;

    wMemTest( variant, "wStringNew:variant" );

    /* make sure it's empty */
    wVariantDeref( variant );

    /* calculate the length of the string? Only do this with a C string! */
    if (length == -1) {
        if (text == NULL) {
            length = 0;
        } else {
            length = strlen( text );
        }
    }
        
    /* create the string */
    newString = (wString *)wMalloc( sizeof( wString ) + (length+1) );
    newString->refCount = 1;
    newString->length = length;

    /* set the variant */
    variant->dataType = W_TYPE_STRING;
    variant->value.string = newString;
        
    /* copy value? */
    if (text == NULL) {
        /* set terminator */
        newString->text = '\0';
        
    } else {
        /* copy the string */                
        wMemMove( (void *)&(newString->text), 
            (void *)text, length+1, "wStringNew" );

    }
}    


/* move value from one string area to another. No safety checks! */
void wStringCopySubstr( wString *dst, int dstStart, wString *src, int srcStart, int count )
{

	/* FIXME! There is a name conflict here */
	void *src1, *dst1;

    wMemTest( dst, "wStringCopySubstr:dst" );
    wMemTest( src, "wStringCopySubstr:src" );

    /* offsets */
    src1 = (void *)((&(src->text))+srcStart);
    dst1 = (void *)((&(dst->text))+dstStart);

    wMemTest( dst1, "wStringCopySubstr:dst1" );
    wMemTest( src1, "wStringCopySubstr:src1" );

    /* move value */
    wMemMove( dst1, src1, count, "wStringCopySubstr" );
}


/* ensure that a string is unique */
void wStringUnique( wVariant *variant )
{
    wString *oldString;

    wMemTest( variant, "wStringUnique:variant" );

    /* sanity check */
    if (variant->dataType != W_TYPE_STRING) {
        wErrorThrow( W_ERROR_CONVERT, "Value is %s, not a string (wStringUnique)",
            wDataTypeName[variant->dataType] );
    }

    /* get the string */
    oldString = variant->value.string;
    wMemTest( oldString, "wStringCopySubstr:oldString" );

    /* check reference count */
    if (oldString->refCount > 1) {
        /* create a new wString */
        wStringNew( variant, 
            &(oldString->text), 
            oldString->length );
    }

}


/* remove n characters from the end of the string */
void wStringChopn( wVariant *variant, int n )
{
    int newLength;
    wString *s;

    wMemTest( variant, "wStringChopN:variant" );

    /* ensure this is not a shared string */
    wStringUnique( variant );

    s = variant->value.string;
    newLength = s->length - n;

    /* range check */
    if (n <= 0) {
        newLength = 0;
    }

    /* adjust length */
    s->length = newLength;
    (&s->text)[newLength] = '\0';
}


/* glue two strings together */
void wStringConcat( wVariant *dst, wVariant *src )
{
    int newLength;    
    wString *dstString, *srcString, *newString;

    wMemTest( src, "wStringConcat:src" );
    wMemTest( dst, "wStringConcat:dst" );

    /* FIXME: automatic conversion? */
        
    /* get the strings */
    dstString = dst->value.string;
    srcString = src->value.string;

    wMemTest( srcString, "wStringConcat:srcString" );
    wMemTest( dstString, "wStringConcat:dstString" );

    /* early out? */
    if (srcString->length == 0) {
        /* nothing to do */
        return;
    }

    /* length zero? */
    if (dstString->length ==  0) {
        /* copy */
        wVariantCopy( dst, src );
        return;
    }
    
    /* calculate the new length of the string */
    newLength = dstString->length + srcString->length;

    /* can modify directly? */
    if (dstString->refCount < 2) {
        /* reallocate space */
        dstString = (wString *)wRealloc( (void *)dstString, sizeof( wString ) + (newLength+1) );
        dst->value.string = dstString;

        /* concat the value from the second string */
        wStringCopySubstr( dstString, dstString->length, srcString, 0, srcString->length+1 );

        /* adjust the length */
        dstString->length = newLength;

    } else {
        /* create a new string large enough to hold the value */
        newString = (wString *)wMalloc( sizeof( wString ) + (newLength+1) );
        newString->refCount = 1;
        newString->length = newLength;

        /* copy destination string */
        wStringCopySubstr( newString, 0, dstString, 0, (dstString->length)+1 );

        /* concat the value from the source string */
        wStringCopySubstr( newString, dstString->length, srcString, 0, srcString->length+1 );
        newString->length = newLength;

        /* decrement old string refcount */
        dstString->refCount--;

        /* point to new string */
        dst->value.string = newString;
    }

}


/* get a substring from a string */
void wStringSubstr( wVariant *dst, wVariant *src, int start, int end )
{
    int bytes;    
    wString *s;

    wMemTest( src, "wStringSubstr:src" );
    wMemTest( dst, "wStringSubstr:dst" );

    /* get the string */
    s = src->value.string;
    wMemTest( s, "wStringSubstr:s" );

    /* bounds check */
    if (start < 1) {
        start = 1;
    }

    if (end > s->length) {
        end = s->length;
    }
    
    /* number of bytes to move (not including terminator) */
    bytes = (end - start) + 1;

    /* not a unique string? */
    if (start == 1 && end == s->length) {
        /* return the same string */
        wVariantCopy( dst, src );
        return;
    }
        /* empty string? */
        if (bytes < 1) {
            /* create an empty string */
            wStringNew( dst, NULL, -1 );
        } else {
            /* create a new, empty string with enough space for the string */                
            wStringNew( dst, NULL, bytes );
        
            /* copy the substring */        
            wStringCopySubstr( dst->value.string, 0, s, start-1, bytes );

            /* set terminator */
            (&dst->value.string->text)[bytes] = '\0';
        }
}

/* return pointer to element in a string, NULL if not found */
wVariant *wStringFindIndex( wVariant *vSrc, int indexCount )
{
    int index;
    char letters[1], *theText;
    wString *srcString, *dstString;

    /* the values of the indexes are on the stack */

    /* check count */
    if (indexCount != 1) {
        wErrorThrow( W_ERROR_INDEX, "String expects 1 index, not %d", indexCount );
        return NULL;
    }

    /* get the index */
    index = (int)wStackPopNumber();

    /* get the source string */
    srcString = vSrc->value.string;

    /* ensure the variable is free */
    wVariantDeref( wTheIndexedString );
        
    /* check the length against the index */
    if (index < 1 || index > srcString->length) {
        /* outside range */
        wStringNew( wTheIndexedString, "", -1 );

    } else {
        /* set destination string */
        theText = &(srcString->text);
        letters[0] = theText[index-1];
        letters[1] = '\0';
        wStringNew( wTheIndexedString, letters, 1 );
    }

    /* return pointer to element */
    return wTheIndexedString;
}


/* repeat a string */
void wStringRepeat( wVariant *result, wVariant *source, int reps )
{
    int oldLength, newLength, i;    
    wString *s, *newString;

    wMemTest( source, "wStringRepeat:source" );
    wMemTest( result, "wStringRepeat:result" );

    /* get the string */
    s = source->value.string;

    wMemTest( s, "wStringRepeat:s" );

        /* get size of the string */
    oldLength = s->length;
    newLength = oldLength * reps;
        
    /* create a new, empty string */
    wStringNew( result, NULL,  newLength );
        newString = result->value.string;
    
    /* skip if it's an empty string */
    if (newLength > 0) {   
        /* copy the string reps times */
        for( i = 0; i < reps; i++ ) {
                /* copy string value */
                wStringCopySubstr( newString, i*oldLength, s, 0, oldLength );
        }
        
        /* terminate */
        (&newString->text)[newLength] = '\0';
    }
    
    /* set the variant */
    wVariantDeref( result );
    result->dataType = W_TYPE_STRING;
    result->value.string = newString;

}



/* return position of substring in string */
int wStringIndex( wVariant *lookIn, wVariant *lookFor, int start )
{
    int i, lookInLength, lookForLength, position;
    char *lookInText, *lookForText;
    wString *lookInString, *lookForString;

    wMemTest( lookIn, "wStringIndex:lookIn" );
    wMemTest( lookFor, "wStringIndex:lookFor" );

        /* FIXME: should this fix the datatypes? */

    /* get the strings */
    lookInString = lookIn->value.string;
    lookForString = lookFor->value.string;

    wMemTest( lookInString, "wStringIndex:lookInString" );
    wMemTest( lookForString, "wStringIndex:lookForString" );

    /* length of search string */
    lookInLength = lookInString->length;
    lookForLength = lookForString->length;

    /* range check */
    if (start < 1) {
        start = 1;
    }
    
    /* early outs */
    if (lookForLength > lookInLength 
        || lookInLength == 0 
        || lookForLength == 0 
        || start > lookInLength ) {
        position = 0;

    } else {

        /* get the char value */
        lookInText = wStringChar(lookIn);
        lookForText = wStringChar(lookFor);

        wMemTest( lookInText, "wStringIndex:lookInText" );
        wMemTest( lookForText, "wStringIndex:lookForText" );

        /* loop through string */
        position = 0;
        for ( i = start-1; i < lookInLength-lookForLength+1; i++ ) {
            /* compare */
            if (memcmp( (void *)(lookInText+i), (void *)lookForText, lookForLength ) == 0) {
                position = i+1;
                break;
            }
        }
    }
    return position;
}



/* reverse Instr function, search from end to start */
int wStringRIndex( wVariant *lookIn, wVariant *lookFor, int start )
{
    int     searchLen, findLen, i;
    char   *find, *search;

    wMemTest( lookIn, "wStringRIndex:lookIn" );
    wMemTest( lookFor, "wStringRIndex:lookFor" );

    search = wStringChar(lookIn);
    find = wStringChar(lookFor);

    wMemTest( search, "wStringRIndex:search" );
    wMemTest( find, "wStringRIndex:find" );

    findLen = lookFor->value.string->length;
    searchLen = lookIn->value.string->length;

    /* searching for empty string? */
    if (searchLen == 0 || findLen == 0) {
        return 0;
    }
    /* search */
    for ( i = start-1; i >= 0; i-- ) {
        if (strncmp( search+i, find, findLen ) == 0) {
            return i+1;
        }
    }

    /* not found */
    return 0;
}

/* convert string data to lower case */
void wStringToLower( wVariant *src )
{
    int         len, i;
    char        *text;

    wMemTest( src, "wStringToLower:src" );

    /* ensure that it is unique */
    wStringUnique( src );

    /* get the string value */
    text = wStringChar(src);
    wMemTest( text, "wStringToLower:text" );

    /* string length */
    len = src->value.string->length;

    /* convert */
    for ( i = 0; i<len; i++){
        text[i] = (char)tolower( (int)text[i] );
    }
}

/* convert string to upper case */
void wStringToUpper( wVariant *src )
{
    int         len, i;
    char        *text;

    wMemTest( src, "wStringToUpper:src" );

    /* ensure that it is unique */
    wStringUnique( src );

    /* get the string value */
    text = wStringChar(src);
    wMemTest( text, "wStringToUpper:string" );

    /* get length */
    len = src->value.string->length;

    /* convert */
    for ( i = 0; i<len; i++){
        text[i] = (char)toupper( (int)text[i] );
    }
}

void wStringLTrim( wVariant *src )
{
    int         len, i;
    char        *text;

    wMemTest( src->value.string, "wStringLTrim:string" );

    /* get the string value */
    text = wStringChar(src);

    /* get length */
    len = src->value.string->length;

    /* find start of non-whitespace */
    for ( i = 0; i < len; i++){
        if (!isspace(text[i])) {
            break;
        }
    }

    /* different? */
    if (i) {
        /* ensure the string is unique */
        wStringUnique( src );

        /* get the string (it might have moved) */
        text = wStringChar(src);

        /* get trimmed length */
        len = src->value.string->length - i;

        /* move value over, including string terminator */
        wMemMove( text, &(text[i]), len+1, "wStringLTrim" );

        /* set the new length */
        src->value.string->length = len;
    }
}


void wStringRTrim( wVariant *src )
{

    int         len, i;
    char        *text;


    /* convert it to a string */
    wVariantCoerce( src, W_TYPE_STRING );

    /* get the string value */
    text = wStringChar(src);
    wMemTest( text, "wStringRTrim:text" );

    /* length */
    len = src->value.string->length;

    /* scan string looking for whitespace character */
    for ( i = len; i > 0; i-- ) {
        if (!isspace(text[i-1])) {
            break;
        }
    }

    /* change? */
    if (i != len) {
        /* make sure it's unique */
        wStringUnique( src );
            
        /* change the length */
        (wStringChar(src))[i] = '\0';
        src->value.string->length = i;
    }
        
}

/* replace string from source with replace starting at index */
void wStringReplace( wVariant *vDst, wVariant *vSrc, wVariant *vReplace, wVariant *vReplacement, int start )
{
    int         i, at, tally;
    int         sourceLen, replaceLen, replacementLen, newLen;
    char        *src, *replace, *replacement, *dst;

    wMemTest( vDst, "wStringReplace:vDst" );
    wMemTest( vSrc, "wStringReplace:vSrc" );
    wMemTest( vReplace, "wStringReplace:vReplace" );

    /* convert everything to a string */
    /* FIXME: look at in context to make sure coersion is correct... */
    wVariantCoerce( vSrc, W_TYPE_STRING );
    wVariantCoerce( vReplace, W_TYPE_STRING );
    wVariantCoerce( vReplacement, W_TYPE_STRING );

    /* get the string data */
    src = wStringChar(vSrc);
    replace = wStringChar(vReplace);
    replacement = wStringChar(vReplacement);

    /* get the lengths */    
    sourceLen = vSrc->value.string->length;
    replaceLen = vReplace->value.string->length;
    replacementLen = vReplacement->value.string->length;

    /* count the number of replacements */
    tally = 0;
    if ((sourceLen >= replaceLen) && (replaceLen != 0)) {
        for ( i = 0; i < sourceLen - replaceLen + 1; i++ ) {
            if (strncmp( src+i, replace, replaceLen ) == 0 ) {
                /* increment */
                tally++;
                /* skip remainder of match */
                i += replaceLen-1;
            }
        }
    }

    /* nothing to replace, use source string */
    if (tally == 0) {
        vSrc->value.string->refCount++;
        vDst->dataType = W_TYPE_STRING;
        vDst->value.string = vSrc->value.string;
        return;
    }

    /* allocate space to build a new string */
    newLen = sourceLen + ((replacementLen-replaceLen)*tally);
    wStringNew( vDst, NULL, newLen );
    dst = wStringChar(vDst);

    at = 0;

    /* walk through the source string */
    for ( i = 0; i < sourceLen; i++ ) {
        /* not past start? */
        if ( i < start-1 ) {
            /* insert the character */
            dst[at] = src[i];
            at += 1;

        /* is this a match? */
        } else if (strncmp( src+i, replace, replaceLen ) == 0 ) {
            /* insert replacement string */
            strncpy( &(dst[at]), replacement, replacementLen );
            at += replacementLen;
            i += replaceLen-1;

        } else {
            /* insert the character */
            dst[at] = src[i];
            at += 1;
        }
    }

    /* end the new string */
    dst[at] = '\0';
    
}

/* reverse a string */
void wStringReverse( wVariant *vDst, wVariant *vSrc )
{
    int         len, i, j;
    char        *srcBuffer, *dstBuffer;

    wMemTest( vDst, "wStringReverse:vDst" );
    wMemTest( vSrc, "wStringReverse:vSrc" );

    /* coerce into a string */
    wVariantCoerce( vSrc, W_TYPE_STRING );
    srcBuffer = wStringChar(vSrc);
    
    /* source length */
    len = vSrc->value.string->length;

    /* create a new string */
    wStringNew( vDst, NULL, len );
    dstBuffer = wStringChar(vDst);

    j = len-1;
    for( i = 0; i < len; i++ ) {
        dstBuffer[j--] = srcBuffer[i];
    }
    dstBuffer[len] = '\0';
}

/* count number of occurances of substring */
int wStringTally( wVariant *vSrc, wVariant *vSubString, int start )
{
    int         i, tally;
    int         srcLen, subLen;
    char        *srcBuffer, *subBuffer;

    /* coerce the values to strings */
    wVariantCoerce( vSrc, W_TYPE_STRING );
    wVariantCoerce( vSubString, W_TYPE_STRING );

    /* get buffers */
    srcBuffer = wStringChar(vSrc);
    subBuffer = wStringChar(vSubString);

    /* get the lengths */
    srcLen = vSrc->value.string->length;
    subLen = vSubString->value.string->length;

    /* count the number of substrings */
    tally = 0;
    if ((srcLen >= subLen) && (subLen != 0)) {
        for ( i = start-1; i < srcLen - subLen + 1; i++ ) {
            if (strncmp( srcBuffer+i, subBuffer, subLen ) == 0 ) {
                /* increment */
                tally++;
                /* skip remainder of match */
                i += subLen-1;
            }
        }
    }

    return tally;
}

/* count string length */
int wStringCount( wVariant *vSrc )
{
    /* get the count */
    return vSrc->value.string->length;
}



/* string methods */
int wStringMethod( wVariant *vSrc, char *name, int argCount )
{
    int index;
    wVariant *item;

    /* FIXME : should add an INSERT at some point */
    if (strcmp( name, "prepend" ) == 0 ) {
        /* check arg count */
        wVariantMethodCheckArgs( "String:prepend", 1, argCount );

        /* get the item to append */
        item = wStackPeek(0);

        /* item onto vSrc */
        wStringConcat( vSrc, item );

        /* replace item with vSrc, leaving it on the stack */
        wVariantCopy( item, vSrc );

        /* number of values returned */
        return 1;

    } else {
        wErrorThrow( W_ERROR_NOSUCH, "Method String:%s not found", name );
        return 0;
    }
}

/* return next char in string */
int wStringIterate( wVariant *vString, wVariant *vIndex, wVariant *vArg1, wVariant *vArg2 )
{
    int i;
    wString *theString;

    /* increment index */
    i = ++vIndex->value.integer;

    /* get list */
    theString = vString->value.string;

    /* outside of range? */
    if (i > theString->length ) {
        /* return false to mark end of string */
        return W_FALSE;
    }

    /* copy index */
    wVariantCopy( vArg1, vIndex );


    /* get char from string? */
    if (vArg2) {
        wStringSubstr( vArg2, vString, i, i);
    }

    /* return true to mark got an element */
    return W_TRUE;

}

