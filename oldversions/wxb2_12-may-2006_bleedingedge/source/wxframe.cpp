wSymbol *_wxSize;
wSymbol *_wxPoint;
wSymbol *_wxWindow;
wSymbol *_wxFrame;

// wxFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_FRAME_STYLE, const wxString& name = "frame")
void wrap_wxFrame_new()
{
    // pop the args
    wxString name = (wTheCall->parmCount > 6 ? wStackPopChar() : "frame");
    long style = (wTheCall->parmCount > 5 ? (long)wStackPopNumber() : wxDEFAULT_FRAME_STYLE);
    const wxSize *size = (wTheCall->parmCount > 4 ? (wxSize *)wStackPopObjectPtr( _wxSize) : &wxDefaultSize);
    const wxPoint *pos = (wTheCall->parmCount > 3 ? (wxPoint *)wStackPopObjectPtr( _wxPoint) : &wxDefaultPosition);
    wxString title = wStackPopChar();
    wxWindowID id = (wxWindowID)wStackPopNumber();
    wxWindow *parent = (wxWindow *)wStackPopObjectPtr( _wxWindow );

    // call new
    wxFrame *returns = new wxFrame(parent, id, title, *pos, *size, style, name);

    // deref args
    wWrapDerefArgs();

    // set result
    wWrapSetThis( _wxFrame, W_TRUE, (void *)returns );
}



void wrap_wxFrame_Show()
{
    bool returns;

    bool show = (bool)wStackPopNumber();
    returns = ((wxFrame *)(wTheCall->self->ptr))->Show();
    wWrapDerefArgs();
    wStackPushNumber( (wNumber)returns);
}

void wMakeWrappers() {
    _wxSize = wWrapClass( 0, NULL, "wxsize" );
    _wxPoint = wWrapClass( 0, NULL, "wxpoint" );
    _wxWindow = wWrapClass( 0, NULL, "wxwindow" );
    _wxFrame = wWrapClass( 0, NULL, "wxframe" );
    wWrapMethod( 0, _wxFrame, "new", wrap_wxFrame_new, 3, 0 );
    wWrapMethod( 0, _wxFrame, "show", wrap_wxFrame_Show, 1, 0 );
}




