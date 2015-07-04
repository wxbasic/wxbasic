/*************************************************************
    Name:       connect.hpp
    Purpose:    implement callbacks for events
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/

void wConnect( int id, int useId, void *handle, int theEvent, wSymbol *routine );
void wDisconnect( int id, int useId, void *handle, int theEvent );
void wDisconnectAll( int id, int useId );
void wRunCallback(wxEvent *event);
