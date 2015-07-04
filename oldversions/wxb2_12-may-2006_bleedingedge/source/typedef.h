/*************************************************************
    Name:       typedef.h
    Purpose:    forward references to structs
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/

#ifndef WXBASIC_TYPEDEF_DECLARES
#define WXBASIC_TYPEDEF_DECLARES


/* macro for struct declarations */
#define W_STRUCT(a) typedef struct a a

/* the structs */
W_STRUCT(wMemItem);
W_STRUCT(wMemConcatBuffer);
W_STRUCT(wGrow);
W_STRUCT(wVariant);
W_STRUCT(wDataStack);
W_STRUCT(wString);
W_STRUCT(wSymbol);
W_STRUCT(wSource);
W_STRUCT(wToken);
W_STRUCT(wCode);
W_STRUCT(wCall);
W_STRUCT(wObject);
W_STRUCT(wArray);
W_STRUCT(wTableElement);
W_STRUCT(wVariantHandler);
W_STRUCT(wCatch);

#endif
