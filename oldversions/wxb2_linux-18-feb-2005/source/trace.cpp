/*
    Name:       trace.cpp
    Purpose:    Code trace and debug window for wxBasic
    Author:     David Cuny
    Copyright:  (c) 2005 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*/

int wTraceExists = 0;       // true if trace window exists

// Declarations
class wTraceWindowClass : public wxFrame
{
public:
    wTraceWindowClass();
    void OnCloseWindow(wxCommandEvent& event);

private:
    DECLARE_EVENT_TABLE()
};

// Event table
BEGIN_EVENT_TABLE(wTraceWindowClass, wxFrame)
    EVT_CLOSE(wTraceWindowClass::OnCloseWindow)
END_EVENT_TABLE()

wTraceWindowClass::wTraceWindowClass():
    wxFrame((wxFrame*)NULL,-1, "wxBasic Trace Window" )
{
    // flag that it exists
    wTraceExists = 1;

    // set to a rational size
    this->SetSize( 400, 400 );

    // show it
    this->Show(1);
}


void wTraceWindowClass::OnCloseWindow(wxCommandEvent& WXUNUSED(event))
{
    // clear flag
    wTraceExists = 0;

    // destroy the window
    this->Destroy();
}
