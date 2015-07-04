/*
    Name:       console.cpp
    Purpose:    Emulated console for wxWrappers
    Author:     David Cuny
    Copyright:  (c) 2002 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*/

/*
    This emulates a console, so the print statement has something
    that can be printed to. The print routine is implemented in
    wConsole(...).

    The console is simply a wxFrame with a wxTextCtrl in it. The
    only reason for defining a class was to set up the callback
    to clear consoleExists when the window is closed.

    The following global variables are used:

        wConsoleExists      If non-zero, the console was created.
        wConsoleText        Pointer wxTextCtrl that holds text

    When the console window is closed, it is destroyed. This
    allows wxBasic to fall out of the main loop when the main
    window is closed. Otherwise, it hangs around as an invisible
    task in the background.
*/


int wConsoleExists = 0;              // true if console exists
int wConsoleLineCount = 0;           // approx. count of lines on console
wxTextCtrl *wConsoleText = NULL;  // write on this


// Declarations
class wConsoleClass : public wxFrame
{
public:
    wConsoleClass();
    void OnCloseWindow(wxCommandEvent& event);

private:
    DECLARE_EVENT_TABLE()
};

// Event table
BEGIN_EVENT_TABLE(wConsoleClass, wxFrame)
    EVT_CLOSE(wConsoleClass::OnCloseWindow)
END_EVENT_TABLE()

wConsoleClass::wConsoleClass():
    wxFrame((wxFrame*)NULL,-1, "Console" )
{
    // flag that it exists
    wConsoleExists = 1;

    // set to a rational size
    this->SetSize( 400, 400 );

    // control for writing text to
    wConsoleText = new wxTextCtrl( this, -1, "", wxPoint( 0, 0 ),
        wxSize( 400, 400 ), wxTE_MULTILINE | wxTE_READONLY );

    // show it
    this->Show(1);
}


void wConsoleClass::OnCloseWindow(wxCommandEvent& WXUNUSED(event))
{
    // clear flag
    wConsoleExists = 0;

    // destroy the window
    this->Destroy();
}
