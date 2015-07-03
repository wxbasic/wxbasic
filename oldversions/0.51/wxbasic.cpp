/*
    Name:       wxbasic.cpp
    Purpose:    wxWindows class to interface to wxBasic
    Author:     David Cuny
    Copyright:  (c) 2002 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*/

#ifdef __GNUG__
    #pragma implementation "wxbasic.cpp"
    #pragma interface "wxbasic.cpp"
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWindows headers)
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

// resources
#if defined(__WXGTK__) || defined(__WXMOTIF__)
    #include "mondrian.xpm"
#endif

// the console
#include "console.cpp"

// Each program should derive a class from wxApp
class wxBasic : public wxApp
{
public:
    // implement base class virtuals
    virtual bool OnInit();
    virtual int OnExit();

    // event handlers (these functions should _not_ be virtual)
    void HandleEvent(wxEvent& event);
};

IMPLEMENT_APP(wxBasic)

// load wxBasic core
#define __WXWIN__
#include "core.c"

bool wxBasic::OnInit(void)
{
    // set handle for wxApp() function
    wAppIndex = (int)wAddObject( _wxApp, (int)&wxGetApp() );

    // in case MainLoop() is called from wxBasic
    SetExitOnFrameDelete( TRUE );

    // mark bottom of create stack
    wPushCreateStack(0);

    // execute the program
    wInterpret( argc, argv );

    // in case MainLoop() wasn't called from wxBasic
    return (GetTopWindow() != NULL);
}

// event handler
void wxBasic::HandleEvent(wxEvent& event)
{
    wRunCallback( &event );
}


// cleanup
int wxBasic::OnExit()
{
    // delete any objects on the stack
    wClearCreateStack();

    // close files, generate warnings
    wShutdown(0);

    // doesn't actually return from wShutdown...
    return 0;
}
