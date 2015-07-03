/*
    Name:       keyword.h
    Purpose:    keywords for wxBasic
    Author:     David Cuny
    Copyright:  (c) 2002 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*/

typedef struct wKeyword wKeyword;

struct wKeyword {
    char    *name;
    int     value;
};

void wInitKeywords(void);
