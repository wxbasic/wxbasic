/*
    Name:       class.h
    Purpose:    wrappers to interface C++ classes to wxBasic
    Author:     David Cuny
    Copyright:  (c) 2002 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*/

typedef struct wWrappedMethod wWrappedMethod;
struct wWrappedMethod {
    char            *name;              /* name of method */
    int             hash;               /* hashed method name value */
    int             minArgs;            /* minimum number of args */
    int             maxArgs;            /* maximum number of args */
    void            (*routine)(void);   /* wrapped method */
    wWrappedMethod  *prior;             /* prior method in chain */
};

typedef struct wWrappedClass wWrappedClass;
struct wWrappedClass {
    char            *name;          /* class name */
    int             super;          /* superclass index */
    wWrappedMethod  *lastMethod;    /* pointer to last method */
};
                
typedef struct wWrappedObject wWrappedObject;
struct wWrappedObject {
    int         pointer;        /* pointer */
    int         classIndex;     /* index to wClassList */
    int         id;             /* wxWindows identifier */
};

#define         W_MAX_CLASSES 256
#define         W_MAX_OBJECTS 1024
#define         W_MAX_CREATE_STACK 256

wWrappedClass   *wClassList[W_MAX_CLASSES];       /* builtin classes */
wWrappedObject  *wObjectList[W_MAX_OBJECTS];      /* objects */
int             wCreateStack[W_MAX_CREATE_STACK]; /* objects created 'on stack' */

int             wNextClass = 1;          /* index of next class */
int             wNextObject = 1;         /* index of next object */
int             wCreateTos = 0;          /* top of createdStack */
int             wObjectIndex = 0;       /* value of _wxObject */

#define W_HASH_MULTIPLIER   31
#define W_HASH_MAX_HASH     1024


unsigned int wHashVal( char *str );
int wFindClass( char *name );
int wAddClass( int superIndex, char *name );
void wAddMethod( int classIndex, char *name, void (*routine)(void), int minArgs, int maxArgs );
wWrappedMethod *wFindClassMethod( int classIndex, char *name, int hash );
wWrappedMethod *wFindMethod( int classIndex, char *name );
int wGetObject( wNumber objectIndex );
int wPopPointer( int matchIndex );
void wResolveMethod( int objectIndex, char *name );
void wRunMethod( int classIndex, char *name );
wNumber wAddObject( int classIndex, int pointer );
void wRemoveObject( int objectIndex );
void wRunDestructor( int objectIndex, int typeOf );
int wClassSafeOnStack( int classIndex );
void wPushCreateStack( int i );
void wClearCreateStack();
