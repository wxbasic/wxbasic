/*************************************************************
    Name:       zstring.c
    Purpose:    builtin string datatype
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/


/* refcount a string */
wStringRef( wVariant *src )
{
    wMemTest( src->value.string, "wStringRef:src->value.string" );
    src->value.string->refCount++;
}

/* dereference a string */
wStringDeref( wVariant *src )
{
    wMemTest( s, "wStringDeref:s" );

    /* decrement reference count */
    s->refCount--;

    /* if no more references, destroy string */
    if (s->refCount < 1) {            
        wFree( s );
    }
}


/* copy variant data */
void wStringCopyData(wVariant *dst, wVariant *src);
    wMemTest( src->value.string, "wStringCopyVariantData:src->value.string" );
    dst->value.string = src->value.string;    
}


/* create from char */
void wStringFromChar( variant *dst, char *buffer )
{
	int length;
	wString *newString;

	/* get the length of the string */
	length = strlen( buffer );

    /* create a string */
    newString = (wString *)wMalloc( sizeof( wString ) + (length+1) );
    newString->refCount = 1;
    newString->length = length;
    wMemMove( (void *)wStringData(newString), (void *)text, length+1, "wStringFromChar" );

    /* place into the variant */
    variant->value.string = newString;
}


/* convert to char */
char *wStringToChar(wVariant *src, int useQuotes)
{	
	/* FIXME: this doesn't quote the string yet */
	/* the *proper* thing to do is to get the length and do a memmove */

	/* copy string to buffer */
	return wStringData( char *wCopyChar( src->value.string ) );
}


/* convert to a number */
wNumber wStringToNumber(wVariant *src);
    wNumber n;

    wMemTest( variant, "wStringToNumber:variant" );

    /* convert to a number */
    if (sscanf( wStringData(variant->value.string), "%f", &n ) != 1) {
        wErrorFatal( "Unable to convert String \"%s\" to Number",
            wStringData(variant->value.string) );
        wErrorSet( W_ERROR_CONVERT );
		n = (wNumber)0;
    }
    return n;
}


/* compare one string to another */
int wStringCompare( wString *s1, wString *s2 )
{
    int i, length1, length2, length, diff;
    char *text1, *text2;

    wMemTest( s1, "wStringCompare:s1" );
    wMemTest( s2, "wStringCompare:s2" );

    /* the lengths */
    length1 = s1->length;
    length2 = s2->length;

    /* the value */
    text1 = wStringData( s1 );
    text2 = wStringData( s2 );

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
            /* compare the numbers */
            diff = text2[i] - text1[i];
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



wNumberRegisterType()
{
    /* register the routines */
    wDataHandler[W_TYPE_STRING].ref = wStringRef;
    wDataHandler[W_TYPE_STRING].deref = wStringDeref;
    wDataHandler[W_TYPE_STRING].copyData = wStringCopyData;    
    wDataHandler[W_TYPE_STRING].fromChar = wStringFromChar;
    wDataHandler[W_TYPE_STRING].toChar = wStringToChar;
    wDataHandler[W_TYPE_STRING].toNumber = wStringToNumber;
	wDataHandler[W_TYPE_STRING].compare = wStringToNumber;
    wDataHandler[W_TYPE_STRING].index = NULL;
	wDataHandler[W_TYPE_STRING].append = NULL;
	wDataHandler[W_TYPE_STRING].prepend = NULL;
	wDataHandler[W_TYPE_STRING].insertAt = NULL;
	wDataHandler[W_TYPE_STRING].slice = NULL;
	wDataHandler[W_TYPE_STRING].remove = NULL;
	wDataHandler[W_TYPE_STRING].find = NULL;
	wDataHandler[W_TYPE_STRING].iterate = NULL;
}



/* return pointer to string value area */
char *wStringData( wString *s )
{
    wMemTest( s, "wStringData:s" );

    /* get the string */
    return &(s->text);
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
        wMemMove( (void *)wStringData(newString), (void *)text, length+1, "wStringNew" );

    }
}    


/* move value from one string area to another. No safety checks! */
void wStringClone( wString *dst, int dstStart, wString *src, int srcStart, int count )
{

	/* FIXME! There is a name conflict here */
	void *src1, *dst1;

    wMemTest( dst, "wStringClone:dst" );
    wMemTest( src, "wStringClone:src" );

    /* offsets */
    src1 = (void *)((&(src->text))+srcStart);
    dst1 = (void *)((&(dst->text))+dstStart);

    wMemTest( dst1, "wStringClone:dst1" );
    wMemTest( src1, "wStringClone:src1" );

    /* move value */
    wMemMove( dst1, src1, count, "wStringClone" );
}


/* ensure that a string is unique */
void wStringUnique( wVariant *variant )
{
    wString *oldString;

    wMemTest( variant, "wStringUnique:variant" );

    /* sanity check */
    if (variant->dataType != W_TYPE_STRING) {
        wErrorFatal("Value is %s, not a string (wStringUnique)",
            wDatatypeName[variant->dataType] );
        wErrorSet( W_ERROR_CONVERT );
    }

    /* get the string */
    oldString = variant->value.string;
    wMemTest( oldString, "wStringClone:oldString" );

    /* check reference count */
    if (oldString->refCount > 1) {
        /* create a new wString */
        wStringNew( variant, wStringData(oldString), oldString->length );
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
        wStringClone( dstString, dstString->length, srcString, 0, srcString->length+1 );

        /* adjust the length */
        dstString->length = newLength;

    } else {
        /* create a new string large enough to hold the value */
        newString = (wString *)wMalloc( sizeof( wString ) + (newLength+1) );
        newString->refCount = 1;
        newString->length = newLength;

        /* copy destination string */
        wStringClone( newString, 0, dstString, 0, (dstString->length)+1 );

        /* concat the value from the source string */
        wStringClone( newString, dstString->length, srcString, 0, srcString->length+1 );
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
            wStringClone( dst->value.string, 0, s, start-1, bytes );

            /* set terminator */
            (&dst->value.string->text)[bytes] = '\0';
        }
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
                wStringClone( newString, i*oldLength, s, 0, oldLength );
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
        lookInText = wStringData( lookInString );
        lookForText = wStringData( lookForString );

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

    search = wStringData( lookIn->value.string );
    find = wStringData( lookFor->value.string );

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

/* convert string to lower case */
void wStringToLower( wVariant *variant )
{
    int         len, i;
    char        *text;

    wMemTest( variant, "wStringToLower:variant" );

    /* ensure that it is unique */
    wStringUnique( variant );

    /* get the string value */
    text = wVariantGetStringChar( variant );
    wMemTest( text, "wStringToLower:text" );

    /* string length */
    len = variant->value.string->length;

    /* convert */
    for ( i = 0; i<len; i++){
        text[i] = (char)tolower( (int)text[i] );
    }
}

/* convert string to upper case */
void wStringToUpper( wVariant *variant )
{
    int         len, i;
    char        *text;

    wMemTest( variant, "wStringToUpper:variant" );

    /* ensure that it is unique */
    wStringUnique( variant );

    /* get the string value */
    text = wVariantGetStringChar( variant );
    wMemTest( text, "wStringToUpper:text" );

    /* get length */
    len = variant->value.string->length;

    /* convert */
    for ( i = 0; i<len; i++){
        text[i] = (char)toupper( (int)text[i] );
    }
}

void wStringLTrim( wVariant *variant )
{
    int         len, i;
    char        *text;

    wMemTest( variant, "wStringLTrim:variant" );

    /* get the string value */
    text = wVariantGetStringChar( variant );
    wMemTest( text, "wStringLTrim:text" );

    /* get length */
    len = variant->value.string->length;

    /* find start of non-whitespace */
    for ( i = 0; i < len; i++){
        if (!isspace(text[i])) {
            break;
        }
    }

    /* different? */
    if (i) {
        /* ensure the string is unique */
        wStringUnique( variant );

        /* get the string value */
        text = wVariantGetStringChar( variant );
        wMemTest( text, "wStringLTrim:text (in loop)" );

        /* get length */
        len = variant->value.string->length - i;
        variant->value.string->length = len;

        /* move value over */
        wMemMove( text, &(text[i]), len, "wStringLTrim" );

        /* set terminator */
        text[len] = '\0';
    }
}


void wStringRTrim( wVariant *variant )
{

    int         len, i;
    char        *text;

    wMemTest( variant, "wStringRTrim:variant" );

    /* ensure it's a string */
    wVariantCoerce( variant, W_TYPE_STRING );

    /* get the string value */
    text = wVariantGetStringChar( variant );
    wMemTest( text, "wStringRTrim:text" );

    /* length */
    len = variant->value.string->length;

    /* scan string looking for whitespace character */
    for ( i = len; i > 0; i-- ) {
        if (!isspace(text[i-1])) {
            break;
        }
    }

    /* change? */
    if (i != len) {
        /* make sure it's unique */
        wStringUnique( variant );
            
        /* change the length */
        (&variant->value.string->text)[i] = '\0';
        variant->value.string->length = i;
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

    src = wVariantGetStringChar( vSrc );
    replace = wVariantGetStringChar( vReplace );
    replacement = wVariantGetStringChar( vReplacement );

    wMemTest( src, "wStringReplace:src" );
    wMemTest( replace, "wStringReplace:replace" );
    wMemTest( replacement, "wStringReplace:replacement" );

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
    dst = wVariantGetStringChar( vDst );

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
            strncpy( dst, replacement, replacementLen );
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

    /* source value */
    srcBuffer = wVariantGetStringChar( vSrc );
    wMemTest( srcBuffer, "wStringReverse:srcBuffer" );

    /* source length */
    len = vSrc->value.string->length;

    /* create a new string */
    wStringNew( vDst, NULL, len );
    dstBuffer = wVariantGetStringChar( vDst );

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

    wMemTest( vSrc, "wStringTally:vSrc" );
    wMemTest( vSubString, "wStringTally:vSubString" );

    srcBuffer = wVariantGetStringChar( vSrc );
    subBuffer = wVariantGetStringChar( vSubString );

    wMemTest( srcBuffer, "wStringTally:srcBuffer" );
    wMemTest( subBuffer, "wStringTally:subBuffer" );

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
