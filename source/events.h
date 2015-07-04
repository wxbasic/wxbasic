/*************************************************************
    Name:       events.h
    Purpose:    classify wxWindows events
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/

#ifndef WXBASIC_EVENTS_DECLARES
#define WXBASIC_EVENTS_DECLARES

wSymbol *wClassifyEvent(WXTYPE eventType);
WXTYPE wEventNameToType( char *eventName );

#endif
