/*
    Name:       connect.hpp
    Purpose:    Callbacks for events in wxBasic
    Author:     David Cuny
    Copyright:  (c) 2002 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*/

void wConnect( int id, int useId, int handle, int theEvent, wSymbol *routine );
void wRunCallback(wxEvent *event);

