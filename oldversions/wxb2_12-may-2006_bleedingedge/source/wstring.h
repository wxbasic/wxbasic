/*************************************************************
    Name:       wstring.h
    Purpose:    strings for wxBasic
    Author:     David Cuny
    Copyright:  (c); 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/


#ifndef WXBASIC_WSTRING_DECLARES
#define WXBASIC_WSTRING_DECLARES


/* copy on write string */
struct wString {
    int refCount;       /* number of people looking at string */
    int length;         /* length of the string, not including terminator */
    char text;          /* the string (more will be allocated); */
};


void wStringRegisterMethods( void );
void wStringRef( wVariant *src );
void wStringDeref( wVariant *src );
void wStringCopy(wVariant *dst, wVariant *src);
void wStringClone( wVariant *dst, wVariant *src );
int wStringFromChar( wVariant *dst, char *buffer );
char *wStringChar(wVariant *src);
char *wStringToChar(wVariant *src, int useQuotes, int limit);
wNumber wStringToNumber(wVariant *src);
int wStringCompare( wVariant *v1, wVariant *v2 );
int wStringCompareString( wString *s1, wString *s2 );
int wStringEqual( wVariant *s1, wVariant *s2 );
int wStringIsTrue( wVariant *s1 );
void wStringNew( wVariant *variant, char *text, int length );
void wStringCopySubstr( wString *dst, int dstStart, wString *src, int srcStart, int count );
void wStringGetIndex( wVariant *dst, wVariant *src, int index );
void wStringUnique( wVariant *variant );
void wStringChopn( wVariant *variant, int n );
void wStringConcat( wVariant *dst, wVariant *src );
void wStringSubstr( wVariant *dst, wVariant *src, int start, int end );
wVariant *wStringFindIndex( wVariant *vSrc, int indexCount );
void wStringRepeat( wVariant *result, wVariant *source, int reps );
int wStringIndex( wVariant *lookIn, wVariant *lookFor, int start );
int wStringRIndex( wVariant *lookIn, wVariant *lookFor, int start );
void wStringToLower( wVariant *src );
void wStringToUpper( wVariant *src );
void wStringLTrim( wVariant *src );
void wStringRTrim( wVariant *src );
void wStringReplace( wVariant *vDst, wVariant *vSrc, wVariant *vReplace, wVariant *vReplacement, int start );
void wStringReverse( wVariant *vDst, wVariant *vSrc );
int wStringTally( wVariant *vSrc, wVariant *vSubString, int start );
int wStringCount( wVariant *vSrc );
int wStringMethod( wVariant *vSrc, char *name, int argCount );
int wStringIterate( wVariant *vString, wVariant *vIndex, wVariant *vArg1, wVariant *vArg2 );


#endif
