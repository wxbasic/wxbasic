/*
    Name:       trace.cpp
    Purpose:    Code trace and debug window for wxBasic
    Author:     David Cuny
    Copyright:  (c) 2005 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*/

#include "wx/stc/stc.h"
#include "wx/splitter.h"
#include "wx/listctrl.h"
#include "wx/notebook.h"
#include "grow.h"
#include "source.h"
#include "trace.h"

// icons
#include "icons/run_xpm.xpm"
#include "icons/stop_xpm.xpm"
#include "icons/step_into_xpm.xpm"
#include "icons/step_over_xpm.xpm"
#include "icons/step_out_xpm.xpm"

// Declarations
class wTraceWindowClass : public wxFrame
{
    public:
        wxToolBar           *toolBar;
        wxStyledTextCtrl    *textCtrl;
        wxListView          *variableList;
        wxListView          *stackList;
        wxNotebook          *notebook;

        wTraceWindowClass();
        void OnRun(wxCommandEvent& event);
        void OnStop(wxCommandEvent& event);
        void OnStepInto(wxCommandEvent& event);
        void OnStepOver(wxCommandEvent& event);
        void OnStepOut(wxCommandEvent& event);
        void GotoLine(int lineNumber);
        void AddVariable( char *name, char *value );
        void AddStack( char *name, char *value );
        void OnCloseWindow(wxCommandEvent& event);        
    
    private:
        DECLARE_EVENT_TABLE()
};


// holds the trace window (if any exists)
wTraceWindowClass *wTraceWindow = NULL;


// Constants
enum
{
    wxID_RUN = wxID_HIGHEST,
    wxID_STOP,
    wxID_STEP_INTO,
    wxID_STEP_OVER,
    wxID_STEP_OUT
};


// Event table
BEGIN_EVENT_TABLE(wTraceWindowClass, wxFrame)
    EVT_CLOSE(wTraceWindowClass::OnCloseWindow)
    EVT_MENU(wxID_RUN, wTraceWindowClass::OnRun)
    EVT_MENU(wxID_STOP, wTraceWindowClass::OnStop)
    EVT_MENU(wxID_STEP_INTO, wTraceWindowClass::OnStepInto)
    EVT_MENU(wxID_STEP_OVER, wTraceWindowClass::OnStepOver)
    EVT_MENU(wxID_STEP_OUT, wTraceWindowClass::OnStepOut)
END_EVENT_TABLE()

wTraceWindowClass::wTraceWindowClass():
    wxFrame((wxFrame*)NULL,-1, "wxBasic Trace Window" )
{
    int i, lineCount;

    // set to a rational size
    this->SetSize( 600, 500 );

    // create a status bar
    this->CreateStatusBar(1);
    this->SetStatusText("wxBasic Debugger");


    // create a toolbar
    this->toolBar = CreateToolBar();
    this->toolBar->SetMargins(4, 4);

    this->toolBar->AddTool(wxID_RUN, "Run", wxBitmap(run_xpm), "Run without debugging");
    this->toolBar->AddSeparator();
    this->toolBar->AddTool(wxID_STEP_INTO, "Step Into", wxBitmap(step_into_xpm), "Step into call");
    this->toolBar->AddTool(wxID_STEP_OVER, "Step Over", wxBitmap(step_over_xpm), "Step to next instruction on this level");
    this->toolBar->AddTool(wxID_STEP_OUT, "Step Out", wxBitmap(step_out_xpm), "Step up one level level");
    this->toolBar->AddSeparator();
    this->toolBar->AddTool(wxID_STOP, "Stop", wxBitmap(stop_xpm), "Halt the application");

    // update the toolbar
    this->toolBar->Realize();

    // create a splitter window
    wxSplitterWindow *splitWindow = new wxSplitterWindow( this, -1);

    // create a top panel with a sizer
    wxPanel *topPanel = new wxPanel(splitWindow, -1);
    wxBoxSizer *topSizer = new wxBoxSizer( wxHORIZONTAL );
    topPanel->SetSizer( topSizer );

    // create a notebook in the top panel
    this->notebook = new wxNotebook(topPanel, -1);
    topSizer->Add( this->notebook, 1, wxEXPAND);


    // create a listView for holding variables
    this->variableList = new wxListView(this->notebook, -1,
        wxDefaultPosition, wxDefaultSize,
        wxLC_REPORT | wxLC_SINGLE_SEL | wxSUNKEN_BORDER | wxLC_EDIT_LABELS);

    // variable name column
    this->variableList->InsertColumn(0, "Name");
    this->variableList->SetColumnWidth( 0, 80 );

    // variable value column
    this->variableList->InsertColumn(1, "Value");
    this->variableList->SetColumnWidth( 1, 600 );

    // place the listview in a notebook page
    this->notebook->AddPage( this->variableList, "Variables" );

    // create a listView for holding stack values
    this->stackList = new wxListView(this->notebook, -1,
        wxDefaultPosition, wxDefaultSize,
        wxLC_REPORT | wxLC_SINGLE_SEL | wxSUNKEN_BORDER | wxLC_EDIT_LABELS);

    // variable name column
    this->stackList->InsertColumn(0, "Name");
    this->variableList->SetColumnWidth( 0, 80 );

    // variable value column
    this->stackList->InsertColumn(1, "Value");
    this->stackList->SetColumnWidth( 1, 600 );

    // place the listview in a notebook page
    this->notebook->AddPage( this->stackList, "Stack" );


    // create a bottom panel
    wxPanel *bottomPanel = new wxPanel(splitWindow, -1);
    wxBoxSizer *bottomSizer = new wxBoxSizer( wxHORIZONTAL );
    bottomPanel->SetSizer( bottomSizer );

    // place the panels in the splitter window
    splitWindow->SplitHorizontally(topPanel, bottomPanel, 200);

    // create a styled text control in the bottom panel
    this->textCtrl = new wxStyledTextCtrl(bottomPanel, -1);
    bottomSizer->Add( this->textCtrl, 1, wxEXPAND);

    // get the count of source code lines
    lineCount = wSourceCount();

    // fill the text control with source code
    for (i = 1; i <= lineCount; i++ ) {
        // get the text
        char *text = wSourceGet( i )->text;
        // add the line of text
        this->textCtrl->AddText( text );
    }

    // set to read-only
    this->textCtrl->SetReadOnly(TRUE);


    // create numbered margins
    this->textCtrl->SetMarginWidth( 0, 36 );
    this->textCtrl->SetMarginType( 0, wxSTC_STYLE_LINENUMBER );

    // create marker zero
    this->textCtrl->MarkerDefine(0, wxSTC_MARK_SHORTARROW, wxColor( 0x00, 0x00, 0x00 ), wxColor( 0x80, 0x00, 0x00 ) );
    this->textCtrl->MarkerSetForeground( 0, wxColor( 0x00, 0x00, 0x00 ) );
    this->textCtrl->MarkerSetBackground( 0, wxColor( 0x80, 0x00, 0x00 ) );

    // show it
    this->Show(1);
}

void wTraceWindowClass::GotoLine(int lineNumber)
{

    // FIXME: add range check

    /* go to the requested line */
    this->textCtrl->GotoLine( lineNumber-1 );

    // clear any prior markers
    this->textCtrl->MarkerDeleteAll( 0 );

    /* make sure the line is visible */
    this->textCtrl->EnsureVisible( lineNumber-1 );

    /* mark the line */
    this->textCtrl->MarkerAdd( lineNumber-1, 0 );

}

void wTraceWindowClass::AddVariable( char *name, char *value ) {

    // get count of items
    int i = this->variableList->GetItemCount();   

    // insert the name and value
    long tmp = variableList->InsertItem(i, name, 0);
    this->variableList->SetItemData(tmp, i);   
    this->variableList->SetItem(i, 1, value);
}


void wTraceWindowClass::AddStack( char *name, char *value ) {

    // get count of items
    int i = this->stackList->GetItemCount();   

    // insert the name and value
    long tmp = stackList->InsertItem(i, name, 0);
    this->stackList->SetItemData(tmp, i);   
    this->stackList->SetItem(i, 1, value);
}


void wTraceWindowClass::OnRun(wxCommandEvent& event)
{
    wTraceRun();
}

void wTraceWindowClass::OnStop(wxCommandEvent& event)
{
    wTraceStop();
}


void wTraceWindowClass::OnStepInto(wxCommandEvent& event)
{
    wTraceStepInto();
}

void wTraceWindowClass::OnStepOver(wxCommandEvent& event)
{
    wTraceStepOver();
}

void wTraceWindowClass::OnStepOut(wxCommandEvent& event)
{
    wTraceStepOut();
}


void wTraceWindowClass::OnCloseWindow(wxCommandEvent& WXUNUSED(event))
{
    // destroy the window
    this->Destroy();

    // clear control
    wTraceWindow = NULL;

}
