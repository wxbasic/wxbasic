/*
    Name:       wxbasic.cpp
    Purpose:    wxWindows class to interface to wxBasic
    Author:     David Cuny
    Copyright:  (c) 2002 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*/

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

// ----------------------------------------------------------------------------
// resources
// ----------------------------------------------------------------------------

// the application icon (under Windows and OS/2 it is in resources)
#if defined(__WXGTK__) || defined(__WXMOTIF__) || defined(__WXMAC__) || defined(__WXMGL__) || defined(__WXX11__)
    #include "mondrian.xpm"
#endif

// the console and trace windows
#include "console.cpp"
#include "trace.cpp"

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
#include "main.c"

bool wxBasic::OnInit(void)
{
    int result;

    // initialize all image handlers
    wxInitAllImageHandlers();

    // initialize the ZIP file system for wxHtmlHelpController
    // wxFileSystem::AddHandler(new wxZipFSHandler);

    // cause the application to close if the main window is closed
    SetExitOnFrameDelete( TRUE );

    // execute the program
    result = wMainInterpret( argc, argv );

    // shut down
    return W_FALSE;
}

// event handler
void wxBasic::HandleEvent(wxEvent& event)
{
    wRunCallback( &event );
}


// cleanup
int wxBasic::OnExit()
{
    // doesn't actually return from wShutdown...
    return 0;
}
