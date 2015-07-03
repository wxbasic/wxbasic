///////////////////////////////////////////////////////////////////////////////
// prototypes of wxWindows classes for wxBasic
// (c) 2002 David Cuny
//
// To Do:
//        note that wxString is not returned as a pointer...
//
// The following errors occured when converting to 2.3.2. They
// are currently commented out, but need to be looked into and
// fixed:
//  Error E2034 wrap.cpp 5766: Cannot convert 'wxWindow *' to 'wxButton *' in function wxPanel_GetDefaultItem()
//  // wxButton* GetDefaultItem() const
//  void wxPanel_GetDefaultItem()
//  
//  Error E2285 wrap.cpp 7174: Could not find a match for 'wxStatusBar::wxStatusBar(wxWindow *,int,const wxPoint,const wxSize,long,wxString)' in function wxStatusBar_new()
//  // wxStatusBar(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = "statusBar")
//  void wxStatusBar_new()
//  
//  Error E2316 wrap.cpp 8191: 'Number' is not a member of 'wxChoice' in function wxChoice_Number()
//  // int Number() const
//  void wxChoice_Number()
//  
//  Error E2316 wrap.cpp 8490: 'Number' is not a member of 'wxComboBox' in function wxComboBox_Number()
//  // int Number() const
//  void wxComboBox_Number()
//  
//  Error E2316 wrap.cpp 9059: 'Number' is not a member of 'wxListBox' in function wxListBox_Number()
//  // int Number() const
//  void wxListBox_Number()
//  
//  Error E2227 wrap.cpp 11933: Extra parameter in call to wxWindowBase::GetLabel() const in function wxRadioBox_GetLabel()
//  // wxString GetLabel(int item) const;
//  void wxRadioBox_GetLabel()
//  
//  Error E2227 wrap.cpp 11946: Extra parameter in call to wxWindowBase::GetLabel() const in function wxRadioBox_GetItemLabel()
//  // %rename GetItemLabel wxString GetLabel(int n) const
//  void wxRadioBox_GetItemLabel()
//  
//  Error E2316 wrap.cpp 11979: 'Number' is not a member of 'wxRadioBox' in function wxRadioBox_Number()
//  // int Number() const
//  void wxRadioBox_Number()
//  
//  Error E2247 wrap.cpp 11993: 'wxString::wxString(int)' is not accessible in function wxRadioBox_SetItemLabel()
//  Error E2227 wrap.cpp 11993: Extra parameter in call to wxWindowBase::SetLabel(const wxString &) in function wxRadioBox_SetItemLabel()
//  // %rename SetItemLabel void SetLabel(int n, const wxString& label)
//  void wxRadioBox_SetItemLabel()
//  
//  Error E2352 wrap.cpp 15063: Cannot create instance of abstract class 'wxEvent' in function wxEvent_new()
//  Error E2353 wrap.cpp 15063: Class 'wxEvent' is abstract because of 'wxEvent::Clone() const = 0' in function wxEvent_new()
//  // wxEvent(int id = 0)
//  void wxEvent_new()
//  
//  

///////////////////////////////////////////////////////////////////////////////

%{
//'wx' prefix causes scanner to think it's a pointer
// typedef'ing it fixes that
typedef wxCoord coord;

// For cases where it's really a unsigned char*, so the scanner
// doesn't think it's a string
typedef unsigned char uchar;
%}

// enums, not classes
%enum wxDateTime::WeekDay
%enum wxEdge
%enum wxFontEncoding
%enum wxGrid::wxGridSelectionModes
%enum wxLayoutAlignment
%enum wxLayoutOrientation
%enum wxRelationship
%enum wxSashEdgePosition
%enum wxSocketNotify
%enum wxTreeItemIcon

// typedefs
%typedef wxNotebookPage wxWindow
%typedef wxCoord coord

// struct
%struct wxResourceTable

// defined so pointers can be flagged
%class wxAcceleratorTable
%class wxArrayInt
%class wxArrayTreeItemIds
%class wxCalendarDateAttr
    %include "wx/calctrl.h"
%class wxCaret
    %include "wx/caret.h"
%class wxClassInfo
%class wxDateTime
%class wxDropTarget
    %include "wx/dnd.h"
%class wxFontData
%class wxIcon
%class wxImageList
    %include "wx/imaglist.h"
%class wxListItem
%class wxLog
%class wxMDIClientWindow
    %include "wx/mdi.h"
%class wxMenuItemList
%class wxObjectRefData
// Fix: class probably can't be used...
// %class wxPlotCurve
%class wxPrintDialogData
%class wxRegion
%class wxRect
%class wxPageSetupDialogData
// %class wxSizer
%class wxSocketBase
    %include "wx/socket.h"
// Fix: Undefined symbol 'wxToolBarTool'
// %class wxToolBarTool
%class wxToolTip
    %include "wx/tooltip.h"
%class wxTreeItemData
%class wxTreeItemId
%class wxValidator
%class wxWindowList
%class wxList
%class wxPrintData
    %include "wx/cmndata.h"
win: %class wxMetafile
win:    %include "wx/metafile.h"
win: %class wxBitmapHandler
win: %class wxGDIImageHandler
%class wxMask
%class wxProcess
%class wxImageHandler
%class wxGridTableBase
    %include "wx/grid.h"

///////////////////////////////////////////////////////////////////////////////
// not really classes, but i'm sticking them here for convenience

%include "wx/tipdlg.h"
%include "wx/filedlg.h"
%include "wx/colordlg.h"
%include "wx/textdlg.h"
%include "wx/choicdlg.h"
%include "wx/msgdlg.h"
%include "wx/tipdlg.h"

// wxString wxFileSelector(const wxString& message, const wxString& default_path = "", const wxString& default_filename = "", const wxString& default_extension = "", const wxString& wildcard = "*.*", int flags = 0, wxWindow *parent = "", int x = -1, int y = -1)
// %alias wxGetColorFromUser wxColour wxGetColourFromUser(wxWindow *parent, const wxColour& colInit)
// long wxGetNumberFromUser( const wxString& message, const wxString& prompt, const wxString& caption, long value, long min = 0, long max = 100, wxWindow *parent = NULL, const wxPoint& pos = wxDefaultPosition)
// wxString wxGetPasswordFromUser(const wxString& message, const wxString& caption = "Input text", const wxString& default_value = "", wxWindow *parent = NULL)
// wxString wxGetTextFromUser(const wxString& message, const wxString& caption = "Input text", const wxString& default_value = "", wxWindow *parent = NULL, int x = -1, int y = -1, bool centre = TRUE)

// Fix: don't support multiple selections yet
// int wxGetMultipleChoice(const wxString& message, const wxString& caption, int n, const wxString& choices[], int nsel, int *selection, wxWindow *parent = NULL, int x = -1, int y = -1, bool centre = TRUE, int width=150, int height=200)
// wxString wxGetSingleChoice(const wxString& message, const wxString& caption, int n, const wxString& choices[], wxWindow *parent = NULL, int x = -1, int y = -1, bool centre = TRUE, int width=150, int height=200)
// int wxGetSingleChoiceIndex(const wxString& message, const wxString& caption, int n, const wxString& choices[], wxWindow *parent = NULL, int x = -1, int y = -1, bool centre = TRUE, int width=150, int height=200)

%builtin int wxMessageBox(const wxString& message, const wxString& caption = "Message", int style = wxOK | wxCENTRE, wxWindow *parent = NULL, int x = -1, int y = -1)

// bool wxShowTip(wxWindow *parent, wxTipProvider *tipProvider, bool showAtStartup = TRUE)

// Utility programs
%include "wx/utils.h"
// %include "wx/dde.h"
%include "wx/app.h"
%include "wx/window.h"

// Can't type correctly
// %builtin wxIconOrCursor wxDROP_ICON(const char *name)
%builtin long wxNewId()
%builtin void wxRegisterId(long id)
%builtin void wxBeginBusyCursor(wxCursor *cursor = wxHOURGLASS_CURSOR)
%builtin void wxBell()
%builtin wxObject * wxCreateDynamicObject(const wxString& className)
// Obsolete
// %builtin void wxDDECleanUp()
// %builtin void wxDDEInitialize()
// Can't handle ...
// %builtin void wxDebugMsg(const wxString& fmt, ...)
%builtin void wxDisplaySize(int *width, int *height)
%builtin void wxEnableTopLevelWindows(bool enable = TRUE)
// Don't use
// %builtin void wxEntry(HANDLE hInstance, HANDLE hPrevInstance, const wxString& commandLine, int cmdShow, bool enterLoop = TRUE)
%builtin void wxEndBusyCursor()
%builtin void wxError(const wxString& msg, const wxString& title = "wxWindows Internal Error")
// Fix: haven't wrapped wxProcess yet
%builtin long wxExecute(const wxString& command, bool sync = FALSE, wxProcess *callback = NULL)
%builtin void wxExit()
%builtin void wxFatalError(const wxString& msg, const wxString& title = "wxWindows Fatal Error")
%builtin int wxFindMenuItemId(wxFrame *frame, const wxString& menuString, const wxString& itemString)
%builtin wxWindow * wxFindWindowByLabel(const wxString& label, wxWindow *parent=NULL)
%builtin wxWindow * wxFindWindowByName(const wxString& name, wxWindow *parent=NULL)
%builtin wxWindow * wxFindWindowAtPoint(const wxPoint& pt)
%builtin wxWindow * wxFindWindowAtPointer(wxPoint& pt)
// Windows only
// wxWindow * wxGetActiveWindow()
// X only
// wxString wxGetDisplayName()
%builtin wxString wxGetHomeDir()
// not supported under Mac
// long wxGetFreeMemory()
%builtin wxPoint wxGetMousePosition()
%builtin wxString wxGetOsDescription()
%builtin int wxGetOsVersion(int *major = NULL, int *minor = NULL)
// FIX: Could not find a match for 'wxGetResource(wxString,wxString,wxString,wxString)' in function builtin_wxGetResource()
// %builtin bool wxGetResource(const wxString& section, const wxString& entry, const wxString& *value, const wxString& file = NULL)
// FIX: Can't find, for some reason
// %builtin bool wxGetUserId(const wxString& buf, int bufSize)
// %builtin const wxChar * wxGetUserHome(const wxString& user = "")
// %builtin bool wxGetUserName(const wxString& buf, int bufSize)
%builtin bool wxHandleFatalExceptions(bool doIt = TRUE)
// FIX: need to defined wxKillError class first...
// %builtin int wxKill(long pid, int sig = wxSIGTERM, wxKillError *rc = NULL)
// should probably do automatically...
// Fix: Call to undefined function 'wxInitAllImageHandlers' in function builtin_wxInitAllImageHandlers()
// %builtin void wxInitAllImageHandlers()
%builtin bool wxIsBusy()
// Windows only
// wxString wxLoadUserResource(const wxString& resourceName, const wxString& resourceType="TEXT")
%builtin wxString wxNow()
// Obsolete
// void wxPostDelete(wxObject *object)
%builtin void wxPostEvent(wxEvtHandler *dest, wxEvent& event)
%builtin bool wxSafeYield(wxWindow* win = NULL)
// X only
// void wxSetDisplayName(const wxString& displayName)
%builtin bool wxShell(const wxString& command = NULL)
%builtin void wxSleep(int secs)
// Macros, doesn't work...
// %builtin char wxToLower(char ch)
// %builtin char wxToUpper(char ch)
// Obsolete
// void wxTrace(const wxString& fmt, ...)
// void wxTraceLevel(int level, const wxString& fmt, ...)
%builtin void wxTrap()
%builtin void wxUsleep(unsigned long milliseconds)
// Fix: need to flag that it uses resources
// %builtin bool wxWriteResource(const wxString& section, const wxString& entry, const wxString& value, const wxString& file = NULL)
%builtin bool wxYield()
%builtin void wxWakeUpIdle()

///////////////////////////////////////////////////////////////////////////////
// Environment access functions
// from utils.h
%include <wx/utils.h>

// %builtin bool wxGetEnv(const wxString& var, wxString *value);
// returns value through arglist, so needs a wrapper
%{
    wxString builtin_getEnvValue( const wxString& var )
    {
        wxString value;
        wxGetEnv(var, &value);
        return value;
    }
%}
%builtin %alias wxGetEnvValue wxString builtin_getEnvValue( const wxString& var )

// Hack: changed wxChar to wxString
// %builtin bool wxSetEnv(const wxString& var, const wxChar *value);
%builtin bool wxSetEnv(const wxString& var, const wxString *value);
%builtin bool wxUnsetEnv(const wxString& var)

///////////////////////////////////////////////////////////////////////////////
// wxPoint

%class wxPoint
wxPoint(int x, int y)
~wxPoint()
int x
int y

///////////////////////////////////////////////////////////////////////////////
// wxSize

%class wxSize
wxSize(int width, int height)
~wxSize()
int GetWidth() const
int GetHeight() const
void Set(int width, int height)
void SetHeight(int height)
void SetWidth(int width)

///////////////////////////////////////////////////////////////////////////////
// wxObject

%class wxObject
wxObject()
~wxObject()
wxObjectRefData* m_refData
// Err: doesn't exist
//void Dump(ostream& stream)
wxClassInfo * GetClassInfo()
wxObjectRefData* GetRefData() const
bool IsKindOf(wxClassInfo *info)
void Ref(const wxObject& clone)
void SetRefData(wxObjectRefData* data)
void UnRef()
// debug only
// void * new(size_t size, const wxString& filename = NULL, int lineNum = 0)
// debug only
// void delete(void buf)


///////////////////////////////////////////////////////////////////////////////
// wxColourData

%class wxColourData, wxObject
%include "wx/cmndata.h"

%alias wxColorData wxColourData()
~wxColourData()
bool GetChooseFull() const
%alias GetColor wxColour& GetColour() const
%alias GetCustomColor wxColour& GetCustomColour(int i) const
void SetChooseFull(const bool flag)
%alias SetColor void SetColour(const wxColour& colour)
%alias SetCustomColor void SetCustomColour(int i, const wxColour& colour)


///////////////////////////////////////////////////////////////////////////////
// wxColour

%class %alias wxColor wxColour, wxObject
%include "wx/colour.h"

wxColour(const unsigned char red, const unsigned char green, const unsigned char blue)

// Error: typo in parm
// wxColour(const wxString& colourName)

// Not supported
// wxColour(const wxColour& colour)

unsigned char Blue() const
long GetPixel() const
unsigned char Green() const
bool Ok() const
unsigned char Red() const
void Set(const unsigned char red, const unsigned char green, const unsigned char blue)


///////////////////////////////////////////////////////////////////////////////
// Device Context


///////////////////////////////////////////////////////////////////////////////
// wxGDIObject

%class wxGDIObject, wxObject
wxGDIObject()


///////////////////////////////////////////////////////////////////////////////
// wxPen

%class wxPen, wxGDIObject
%include <wx/pen.h>

wxPen()
~wxPen()
int GetCap() const
wxColour& GetColour() const
// FIX!
// int GetDashes(wxDash** dashes) const
int GetJoin() const
win: wxBitmap* GetStipple() const
int GetStyle() const
int GetWidth() const
bool Ok() const
void SetCap(int capStyle)
%alias SetColor void SetColour(wxColour& colour)
%rename SetColourString %alias SetColorString void SetColour(const wxString& colourName)
%rename SetColourRGB %alias SetColorRGB void SetColour(int red, int green, int blue)
// FIX - need to add wxDash...
//void SetDashes(int nb_dashes, const wxDash *dash)
void SetJoin(int join_style)
// Fixed, missing const
// void SetStipple(const wxBitmap* stipple)
void SetStyle(int style)
void SetWidth(int width)



// alternate constructors
%ctor wxPenFromColour(const wxColour& colour, int width, int style)
%ctor wxPenFromColor(const wxColour& colour, int width, int style)
%ctor wxPenFromColourName(const wxString& colourName, int width, int style)
%ctor wxPenFromColorName(const wxString& colourName, int width, int style)
win: %ctor wxPenFromBitmap(const wxBitmap& stipple, int width)
%ctor wxPenCopy(const wxPen& pen)


///////////////////////////////////////////////////////////////////////////////
// wxPalette

%class wxPalette, wxGDIObject
%include "wx/palette.h"

// Fix: these look like strings
// wxPalette(int n, const unsigned char* red, const unsigned char* green, const unsigned char* blue)
wxPalette(int n, const uchar* red, const uchar* green, const uchar* blue)

~wxPalette()
// bool Create(int n, const unsigned char* red, const unsigned char* green, const unsigned char* blue)
bool Create(int n, const uchar* red, const uchar* green, const uchar* blue)
int GetPixel(const unsigned char red, const unsigned char green, const unsigned char blue) const

// bool GetRGB(int pixel, const unsigned char* red, const unsigned char* green, const unsigned char* blue) const
bool Ok() const


///////////////////////////////////////////////////////////////////////////////
// wxBrush

%class wxBrush, wxGDIObject
%include "wx/brush.h"

wxBrush(const wxColour& colour, int style)
%ctor wxBrushFromColourName(const wxString& colourName, int style)
%ctor wxBrushFromColorName(const wxString& colourName, int style)
%ctor wxBrushFromBitmap(const wxBitmap& stippleBitmap)
%ctor Copy(const wxBrush& brush)
// Fixed: removed void
~wxBrush()
%alias GetColor wxColour& GetColour() const
wxBitmap * GetStipple() const
int GetStyle() const
bool Ok() const
// alias...
%alias SetColor void SetColour(wxColour& colour)
%rename SetColourString %alias SetColorString void SetColour(const wxString& colourName)
%rename SetColourRGB %alias SetColorRGB void SetColour(const unsigned char red, const unsigned char green, const unsigned char blue)

void SetStipple(const wxBitmap& bitmap)
void SetStyle(int style)

// not supported
// wxBrush& operator =(const wxBrush& brush)
// bool operator ==(const wxBrush& brush)
// bool operator !=(const wxBrush& brush)

///////////////////////////////////////////////////////////////////////////////
// wxBrushList

%class wxBrushList, wxList 
%include "wx/gdicmn.h"

// Fixed: removed void
wxBrushList()
// used internally
// void AddBrush(wxBrush *brush)

// need alias...
wxBrush * FindOrCreateBrush(const wxColour& colour, int style)
// wxBrush * FindOrCreateBrush(const wxString& colourName, int style)

// used internally...
// void RemoveBrush(wxBrush *brush)


///////////////////////////////////////////////////////////////////////////////
// wxDC

%class wxDC, wxObject
%include "wx/dc.h"

// FIX: this is virtual in GTK, so can't be constructed
win: wxDC()
~wxDC()
void BeginDrawing()
bool Blit(wxCoord xdest, wxCoord ydest, wxCoord width, wxCoord height, wxDC* source, wxCoord xsrc, wxCoord ysrc, int logicalFunc = wxCOPY, bool useMask = FALSE)
void CalcBoundingBox(wxCoord x, wxCoord y)
void Clear()
void CrossHair(wxCoord x, wxCoord y)
void DestroyClippingRegion()
wxCoord DeviceToLogicalX(wxCoord x)
wxCoord DeviceToLogicalXRel(wxCoord x)
wxCoord DeviceToLogicalY(wxCoord y)
wxCoord DeviceToLogicalYRel(wxCoord y)
// Fixed: prototype for parms 5 and 6 were double
void DrawArc(wxCoord x1, wxCoord y1, wxCoord x2, wxCoord y2, wxCoord xc, wxCoord yc)
void DrawBitmap(const wxBitmap& bitmap, wxCoord x, wxCoord y, bool transparent)

// Alias
void DrawCheckMark(wxCoord x, wxCoord y, wxCoord width, wxCoord height)
%rename DrawCheckMarkRect void DrawCheckMark(const wxRect &rect)

void DrawEllipse(wxCoord x, wxCoord y, wxCoord width, wxCoord height)
void DrawEllipticArc(wxCoord x, wxCoord y, wxCoord width, wxCoord height, double start, double end)
void DrawIcon(const wxIcon& icon, wxCoord x, wxCoord y)
void DrawLine(wxCoord x1, wxCoord y1, wxCoord x2, wxCoord y2)

// Alias
void DrawLines(int n, wxPoint points[], wxCoord xoffset = 0, wxCoord yoffset = 0)
%rename DrawLinesList void DrawLines(wxList *points, wxCoord xoffset = 0, wxCoord yoffset = 0)

// Alias
void DrawPolygon(int n, wxPoint points[], wxCoord xoffset = 0, wxCoord yoffset = 0, int fill_style = wxODDEVEN_RULE)
%rename DrawPolygonList void DrawPolygon(wxList *points, wxCoord xoffset = 0, wxCoord yoffset = 0, int fill_style = wxODDEVEN_RULE)

void DrawPoint(wxCoord x, wxCoord y)
void DrawRectangle(wxCoord x, wxCoord y, wxCoord width, wxCoord height)
void DrawRotatedText(const wxString& text, wxCoord x, wxCoord y, double angle)
void DrawRoundedRectangle(wxCoord x, wxCoord y, wxCoord width, wxCoord height, double radius = 20)

// Fix!
// void DrawSpline(wxList *points)

void DrawText(const wxString& text, wxCoord x, wxCoord y)
void EndDoc()
void EndDrawing()
void EndPage()
void FloodFill(wxCoord x, wxCoord y, const wxColour& colour, int style=wxFLOOD_SURFACE)

// alias
wxBrush& GetBackground()
// const wxBrush& GetBackground() const

int GetBackgroundMode() const

// alias
wxBrush& GetBrush()
// const wxBrush& GetBrush() const

wxCoord GetCharHeight()
wxCoord GetCharWidth()
// void GetClippingBox(wxCoord *x, wxCoord *y, wxCoord *width, wxCoord *height)
%{
    void wxDC_GetClippingBoxX()
    {
        wxCoord x, y, width, height;
        ((wxDC *)wMe)->GetClippingBox(&x, &y, &width, &height);
        wPushNumber( (wNumber)x );
    }

    void wxDC_GetClippingBoxY()
    {
        wxCoord x, y, width, height;
        ((wxDC *)wMe)->GetClippingBox(&x, &y, &width, &height);
        wPushNumber( (wNumber)y );
    }

    void wxDC_GetClippingBoxWidth()
    {
        wxCoord x, y, width, height;
        ((wxDC *)wMe)->GetClippingBox(&x, &y, &width, &height);
        wPushNumber( (wNumber)width );
    }

    void wxDC_GetClippingBoxHeight()
    {
        wxCoord x, y, width, height;
        ((wxDC *)wMe)->GetClippingBox(&x, &y, &width, &height);
        wPushNumber( (wNumber)height );
    }

%}
%method GetPixelBoxX        wxDC_GetClippingBoxX()
%method GetPixelBoxY        wxDC_GetClippingBoxY()
%method GetPixelBoxWidth    wxDC_GetClippingBoxWidth()
%method GetPixelBoxHeight   wxDC_GetClippingBoxHeight()

wxFont& GetFont()
int GetLogicalFunction()
int GetMapMode()
bool GetOptimization()

// alias?
wxPen& GetPen()
// const wxPen& GetPen() const

bool GetPixel(wxCoord x, wxCoord y, wxColour *colour)
// void GetSize(wxCoord *width, wxCoord *height)

%{
    void wxDC_GetSizeX()
    {
        int x, y;
        // call GetSize
        ((wxDC *)wMe)->GetSize(&x, &y);
        wPushNumber( (wNumber)x );
    }

    void wxDC_GetSizeY()
    {
        int x, y;
        // call GetSize
        ((wxDC *)wMe)->GetSize(&x, &y);
        wPushNumber( (wNumber)y );
    }
%}
%method GetSizeX    wxDC_GetSizeX()
%method GetSizeY    wxDC_GetSizeY()

// alias?
// wxPython note: In place of a single overloaded method name, wxPython implements the following methods:
//        GetSize()  Returns a wxSize  
//        GetSizeTuple()  Returns a 2-tuple (width, height)  

const wxColour& GetTextBackground() const

// alias...
void GetTextExtent(const wxString& string, wxCoord *w, wxCoord *h, wxCoord *descent = NULL, wxCoord *externalLeading = NULL, wxFont *font = NULL)
// wxPython note: The following methods are implemented in wxPython:
//        GetTextExtent(string)  Returns a 2-tuple, (width, height)  
//        GetFullTextExtent(string, font=NULL)  Returns a 4-tuple, (width, height, descent, externalLeading)  

// alias...
wxColour& GetTextForeground()
// const wxColour& GetTextForeground() const

// void GetUserScale(double *x, double *y)
%{
    void wxDC_GetUserScaleX()
    {
        double x, y;
        ((wxDC *)wMe)->GetUserScale(&x, &y);
        wPushNumber( (wNumber)x );
    }

    void wxDC_GetUserScaleY()
    {
        double x, y;
        ((wxDC *)wMe)->GetUserScale(&x, &y);
        wPushNumber( (wNumber)y );
    }
%}
%method GetUserScaleX   wxDC_GetUserScaleX()
%method GetUserScaleY   wxDC_GetUserScaleY()


wxCoord LogicalToDeviceX(wxCoord x)
wxCoord LogicalToDeviceXRel(wxCoord x)
wxCoord LogicalToDeviceY(wxCoord y)
wxCoord LogicalToDeviceYRel(wxCoord y)
wxCoord MaxX()
wxCoord MaxY()
wxCoord MinX()
wxCoord MinY()
bool Ok()
void ResetBoundingBox()
void SetDeviceOrigin(wxCoord x, wxCoord y)
void SetBackground(const wxBrush& brush)
void SetBackgroundMode(int mode)

// alias...
%rename SetClippingRegionXY void SetClippingRegion(wxCoord x, wxCoord y, wxCoord width, wxCoord height)
void SetClippingRegion(const wxRegion& region)

void SetPalette(const wxPalette& palette)
void SetBrush(const wxBrush& brush)
void SetFont(const wxFont& font)
// Fixed: was int int
// void SetMapMode(int unit)
void SetOptimization(bool optimize)
void SetPen(const wxPen& pen)
void SetTextBackground(const wxColour& colour)
void SetTextForeground(const wxColour& colour)
void SetUserScale(double xScale, double yScale)
bool StartDoc(const wxString& message)
// Fixed: was bool, should have been void
void StartPage()


///////////////////////////////////////////////////////////////////////////////
// wxMemoryDC

%class wxMemoryDC, wxDC 
%include "wx/dcmemory.h"

wxMemoryDC()
// Error: missing void
void SelectObject(const wxBitmap& bitmap)


///////////////////////////////////////////////////////////////////////////////
// wxMetafileDC

// FIX: not in GTK
gtk: %skip

%class wxMetafileDC, wxDC 
%include "wx/metafile.h"

wxMetafileDC(const wxString& filename = "")
~wxMetafileDC()
win: wxMetafile * Close()


///////////////////////////////////////////////////////////////////////////////
// wxPostScriptDC

// FIX! not recognized? why?
%skip
%class wxPostScriptDC, wxDC 
%include "wx/dcps.h"

wxPostScriptDC(const wxPrintData& printData)
~wxPostScriptDC()
static void SetResolution(int ppi)
static int GetResolution()





///////////////////////////////////////////////////////////////////////////////
// wxPrinterDC

// FIX: not declared for GTK
gtk: %skip

%class wxPrinterDC, wxDC
%include "wx/dcprint.h"

wxPrinterDC(const wxPrintData& printData)



///////////////////////////////////////////////////////////////////////////////
// wxWindowDC

%class wxWindowDC, wxDC
%include "wx/dcclient.h"

wxWindowDC(wxWindow* window)


///////////////////////////////////////////////////////////////////////////////
// wxClientDC

%class wxClientDC, wxWindowDC
%include "wx/dcclient.h"

wxClientDC(wxWindow* window)



///////////////////////////////////////////////////////////////////////////////
// wxPaintDC

%class wxPaintDC, wxWindowDC
%include "wx/dcclient.h"

wxPaintDC(wxWindow* window)


///////////////////////////////////////////////////////////////////////////////
// wxScreenDC

%class wxScreenDC, wxDC
%include "wx/dcscreen.h"

wxScreenDC()

// need alias...
bool StartDrawingOnTop(wxWindow* window)
%rename StartDrawingOnTopRect bool StartDrawingOnTop(wxRect* rect = NULL)

bool EndDrawingOnTop()


///////////////////////////////////////////////////////////////////////////////
// wxBitmap


%class wxBitmap, wxGDIObject
%include "wx/bitmap.h"

// FIX: missing in GTK, different prototypes
win: wxBitmap(void* data, int type, int width, int height, int depth = -1)

%ctor wxBitmapCopy(const wxBitmap& bitmap)

// Not supported
// wxBitmap(const char bits[], int width, int height, int depth = 1)

// wxPython note: Constructors supported by wxPython are:
//        wxBitmap(name, flag)  Loads a bitmap from a file  
//        wxBitmapFromData(data, type, width, height, depth=1)  Creates a bitmap from the given data, which can be of arbitrary type.  
//        wxNoRefBitmap(name, flag)  This one won't own the reference, so Python won't call the destructor, this is good for toolbars and such where the parent will manage the bitmap.  
//        wxEmptyBitmap(width, height, depth = -1)  

%ctor wxEmptyBitmap( int width, int height, int depth = -1)
// FIX: this stopped working in 2.3.1
// %ctor wxBitmapFromFile( const wxString& name, long type)

~wxBitmap()
// FIX: Missing from GTK
win: static void AddHandler(wxBitmapHandler* handler)
win: static void CleanUpHandlers()
virtual bool Create(int width, int height, int depth = -1)

// fix, and alias...
// static wxBitmapHandler* FindHandler(const wxString& name)
// static wxBitmapHandler* FindHandler(const wxString& extension, long bitmapType)
// static wxBitmapHandler* FindHandler(long bitmapType)

int GetDepth() const
// FIX: Missing from GTK
win: static wxList& GetHandlers()
int GetHeight() const
wxPalette* GetPalette() const
wxMask* GetMask() const
int GetWidth() const
wxBitmap GetSubBitmap(const wxRect &rect) const
// FIX: missing in GTK
win: static void InitStandardHandlers()
win: static void InsertHandler(wxBitmapHandler* handler)
bool LoadFile(const wxString& name, long type)
bool Ok() const
// FIX: Missing in GTK
win: static bool RemoveHandler(const wxString& name)
bool SaveFile(const wxString& name, int type, wxPalette* palette = NULL)
void SetDepth(int depth)
void SetHeight(int height)
void SetMask(wxMask* mask)
// Fix: 'SetOk' is not a member of 'wxBitmap'
// void SetOk(int isOk)
// FIX: Missing in GTK
win: void SetPalette(const wxPalette& palette)
void SetWidth(int width)

// not supported
// wxBitmap& operator =(const wxBitmap& bitmap)
// bool operator ==(const wxBitmap& bitmap)
// bool operator !=(const wxBitmap& bitmap)



///////////////////////////////////////////////////////////////////////////////
// wxImage

%class wxImage, wxObject
%include "wx/image.h"

wxImage(const wxImage& image)
%ctor wxNullImage()
%ctor wxImageFromBitmap(const wxBitmap& bitmap)
%ctor wxEmptyImage(int width, int height)
%ctor wxImageFromData(int width, int height, uchar* data, bool static_data=FALSE)
%ctor wxImageFromFile(const wxString& name, long type = wxBITMAP_TYPE_ANY)
//%ctor wxImageFromStream wxImage(wxInputStream& stream, long type = wxBITMAP_TYPE_ANY)

~wxImage()
static void AddHandler(wxImageHandler* handler)
static void CleanUpHandlers()
wxBitmap ConvertToBitmap() const
wxImage Copy() const
// FIX: doesn't seem to be handling bool correctly
// bool Create(int width, int height)
// bool Destroy()
//static wxImageHandler* FindHandler(const wxString& name)
//static wxImageHandler* FindHandler(const wxString& extension, long imageType)
//static wxImageHandler* FindHandler(long imageType)
//static wxImageHandler* FindHandlerMime(const wxString& mimetype)
unsigned char GetBlue(int x, int y) const
uchar* GetData() const
unsigned char GetGreen(int x, int y) const
unsigned char GetRed(int x, int y) const
static wxList& GetHandlers()
int GetHeight() const
unsigned char GetMaskBlue() const
unsigned char GetMaskGreen() const
unsigned char GetMaskRed() const
const wxPalette& GetPalette() const
wxImage GetSubImage(const wxRect& rect) const
int GetWidth() const
bool HasMask() const
static void InitStandardHandlers()
static void InsertHandler(wxImageHandler* handler)
bool LoadFile(const wxString& name, long type = wxBITMAP_TYPE_ANY)
%rename LoadMimeFile bool LoadFile(const wxString& name, const wxString& mimetype)
bool Ok() const
static bool RemoveHandler(const wxString& name)
bool SaveFile(const wxString& name, int type)
%rename SaveMimeFile bool SaveFile(const wxString& name, const wxString& mimetype)
wxImage Mirror(bool horizontally = TRUE) const
void Replace(unsigned char r1, unsigned char g1, unsigned char b1, unsigned char r2, unsigned char g2, unsigned char b2)
// Fix: doesn't handle (yet)
// wxImage & Rescale(int width, int height)
wxImage Rotate(double angle, const wxPoint& rotationCentre, bool interpolating = TRUE, wxPoint* offsetAfterRotation = NULL)
wxImage Rotate90(bool clockwise = TRUE) const
wxImage Scale(int width, int height) const
void SetData(uchar* data)
void SetMask(bool hasMask = TRUE)
void SetMaskColour(unsigned char red, unsigned char blue, unsigned char green)
void SetPalette(const wxPalette& palette)
void SetRGB(int x, int y, unsigned char red, unsigned char green, unsigned char blue)




///////////////////////////////////////////////////////////////////////////////
// wxCursor

%class wxCursor, wxBitmap 
%include "wx/cursor.h"

// platform dependant, add later









///////////////////////////////////////////////////////////////////////////////
// wxEvtHandler
//
// event handling is *not* accessible like this through wxScript

%class wxEvtHandler, wxObject
wxEvtHandler()
~wxEvtHandler()
// virtual void AddPendingEvent(wxEvent& event)
// void Connect(int id, wxEventType eventType, wxObjectEventFunction function, wxObject* userData = NULL)
// bool Disconnect(int id, wxEventType eventType = wxEVT_NULL, wxObjectEventFunction function = NULL, wxObject* userData = NULL)
// void* GetClientData()
// bool GetEvtHandlerEnabled()
// wxEvtHandler* GetNextHandler()
// wxEvtHandler* GetPreviousHandler()
// virtual bool ProcessEvent(wxEvent& event)
// bool SearchEventTable(wxEventTable& table, wxEvent& event)
// void SetClientData(void* data)
// void SetEvtHandlerEnabled(bool enabled)
// void SetNextHandler(wxEvtHandler* handler)
// void SetPreviousHandler(wxEvtHandler* handler)

///////////////////////////////////////////////////////////////////////////////
// wxApp

%class wxApp, wxEvtHandler
int argc
char ** argv
virtual wxLog* CreateLogTarget()
void Dispatch()
wxString GetAppName() const
// FIX: Missing in GTK
win: bool GetAuto3D() const
wxString GetClassName() const
// Err: doesn't exist
// bool GetExitFrameOnDelete() const
wxWindow * GetTopWindow() const
bool GetUseBestVisual() const
wxString GetVendorName() const
void ExitMainLoop()
bool Initialized()
int MainLoop()
// void OnActivate(wxActivateEvent& event)
// int OnExit()
// void OnCharHook(wxKeyEvent& event)
// void OnFatalException()
// void OnIdle(wxIdleEvent& event)
// void OnEndSession(wxCloseEvent& event)
// bool OnInit()
// void OnQueryEndSession(wxCloseEvent& event)
// Err: can't convert tagMSG -> void**; Win32 only anyway
// bool ProcessMessage(MSG *msg)
bool Pending()
bool SendIdleEvents()
void SetAppName(const wxString& name)
// FIX: Missing in GTK
win: void SetAuto3D(const bool auto3D)
void SetClassName(const wxString& name)
void SetExitOnFrameDelete(bool flag)
void SetTopWindow(wxWindow* window)
void SetVendorName(const wxString& name)
virtual wxIcon GetStdIcon(int which) const
void SetUseBestVisual(bool flag)

///////////////////////////////////////////////////////////////////////////////
// wxWindow

%class wxWindow, wxEvtHandler

wxWindow(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = wxPanelNameStr)
~wxWindow()
virtual void AddChild(wxWindow* child)
virtual void CaptureMouse()
void Center(int direction = wxBOTH)
void CenterOnParent(int direction = wxBOTH)
void CenterOnScreen(int direction = wxBOTH)
void Centre(int direction = wxBOTH)
void CentreOnParent(int direction = wxBOTH)
void CentreOnScreen(int direction = wxBOTH)
void Clear()
virtual void ClientToScreen(int* x, int* y) const
virtual bool Close(bool force = FALSE)
%rename ConvertDialogPointToPixels wxPoint ConvertPixelsToDialog(const wxPoint& pt)
%rename ConvertDialogSizeToPixels wxSize ConvertPixelsToDialog(const wxSize& sz)
virtual bool Destroy()
virtual void DestroyChildren()
// FIX: Missing in GTK
win: virtual void DragAcceptFiles(bool accept)
virtual void Enable(bool enable)
static wxWindow* FindFocus()
wxWindow* FindWindow(long id)
virtual void Fit()
%alias GetBackgroundColor virtual wxColour GetBackgroundColour() const
virtual wxSize GetBestSize() const
wxCaret * GetCaret() const
virtual int GetCharHeight() const
virtual int GetCharWidth() const
// Error: had been wxList
wxWindowList& GetChildren()
// virtual void GetClientSize(int* width, int* height) const
%{
    void wxWindow_GetClientSizeWidth()
    {
        int width, height;
        ((wxWindow *)wMe)->GetClientSize(&width, &height);
        wPushNumber( (wNumber)width );
    }

    void wxWindow_GetClientSizeHeight()
    {
        int width, height;
        ((wxWindow *)wMe)->GetClientSize(&width, &height);
        wPushNumber( (wNumber)height );
    }


%}
%method GetClientSizeWidth      wxWindow_GetClientSizeWidth()
%method GetClientSizeHeight     wxWindow_GetClientSizeHeight()

virtual wxSize GetClientSize() const
wxLayoutConstraints* GetConstraints() const
wxDropTarget* GetDropTarget() const
wxEvtHandler* GetEventHandler() const
long GetExtraStyle() const
wxFont& GetFont() const
%alias GetForegroundColor virtual wxColour GetForegroundColour()
wxWindow* GetGrandParent() const
// platform dependant
// void* GetHandle() const
int GetId() const
virtual wxString GetLabel() const
virtual wxString GetName() const
virtual wxWindow* GetParent() const
// virtual void GetPosition(int* x, int* y) const
%{
    void wxWindow_GetPositionX()
    {
        int x, y;
        ((wxWindow *)wMe)->GetPosition(&x, &y);
        wPushNumber( (wNumber)x );
    }

    void wxWindow_GetPositionY()
    {
        int x, y;
        ((wxWindow *)wMe)->GetPosition(&x, &y);
        wPushNumber( (wNumber)y );
    }


%}
%method GetPositionX    wxWindow_GetPositionX()
%method GetPositionY    wxWindow_GetPositionY()

virtual wxRect GetRect() const
virtual int GetScrollThumb(int orientation)
virtual int GetScrollPos(int orientation)
virtual int GetScrollRange(int orientation)
// virtual void GetSize(int* width, int* height) const
%{
    void wxWindow_GetSizeWidth()
    {
        int width, height;
        ((wxWindow *)wMe)->GetSize(&width, &height);
        wPushNumber( (wNumber)width );
    }

    void wxWindow_GetSizeHeight()
    {
        int width, height;
        ((wxWindow *)wMe)->GetSize(&width, &height);
        wPushNumber( (wNumber)height );
    }


%}
%method GetSizeWidth    wxWindow_GetSizeWidth()
%method GetSizeHeight   wxWindow_GetSizeHeight()

// Error: last arg does not exist
// virtual void GetTextExtent(const wxString& string, int* x, int* y, int* descent = NULL, int* externalLeading = NULL, const wxFont* font = NULL, bool use16 = FALSE) const
// virtual void GetTextExtent(const wxString& string, int* x, int* y, int* descent = NULL, int* externalLeading = NULL, const wxFont* font = NULL ) const
%{
    void wxWindow_GetTextExtentX()
    {
        // arg
        wxString string = wPopString();

        int x, y, descent, externalLeading;
        ((wxWindow *)wMe)->GetTextExtent(string, &x, &y, &descent, &externalLeading);
        wPushNumber( (wNumber)x );
    }

    void wxWindow_GetTextExtentY()
    {
        // arg
        wxString string = wPopString();
        int x, y, descent, externalLeading;
        ((wxWindow *)wMe)->GetTextExtent(string, &x, &y, &descent, &externalLeading);
        wPushNumber( (wNumber)y );
    }


    void wxWindow_GetTextExtentDescent()
    {
        // arg
        wxString string = wPopString();
        int x, y, descent, externalLeading;
        ((wxWindow *)wMe)->GetTextExtent(string, &x, &y, &descent, &externalLeading);
        wPushNumber( (wNumber)descent );
    }

    void wxWindow_GetTextExtentExternalLeading()
    {
        // arg
        wxString string = wPopString();
        int x, y, descent, externalLeading;
        ((wxWindow *)wMe)->GetTextExtent(string, &x, &y, &descent, &externalLeading);
        wPushNumber( (wNumber)externalLeading );
    }


%}
%method GetTextExtentX                  wxWindow_GetTextExtentX( const wxString &string)
%method GetTextExtentY                  wxWindow_GetTextExtentY( const wxString &string)
%method GetTextExtentDescent            wxWindow_GetTextExtentX( const wxString &string)
%method GetTextExtentExternalLeading    wxWindow_GetTextExtentX( const wxString &string)

virtual wxString GetTitle()
virtual wxRegion GetUpdateRegion() const
wxValidator* GetValidator() const
long GetWindowStyleFlag() const
void InitDialog()
virtual bool IsEnabled() const
bool IsExposed(int x, int y) const
%rename IsExposedPoint bool IsExposed(wxPoint &pt) const
// bool IsExposed(int x, int y, int w, int h) const
%rename IsExposedRect bool IsExposed(wxRect &rect) const
virtual bool IsRetained() const
virtual bool IsShown() const
bool IsTopLevel() const
void Layout()
virtual bool LoadFromResource(wxWindow* parent, const wxString& resourceName, const wxResourceTable* resourceTable = NULL)
void Lower()
virtual void MakeModal(bool flag)
void Move(int x, int y)
%rename MoveXY void Move(const wxPoint& pt)
// void OnActivate(wxActivateEvent& event)
// void OnChar(wxKeyEvent& event)
// void OnCharHook(wxKeyEvent& event)
// virtual void OnCommand(wxEvtHandler& object, wxCommandEvent& event)
// virtual bool OnClose()
// void OnCloseWindow(wxCloseEvent& event)
// void OnDropFiles(wxDropFilesEvent& event)
// void OnEraseBackground(wxEraseEvent& event)
// void OnKeyDown(wxKeyEvent& event)
// void OnKeyUp(wxKeyEvent& event)
// void OnKillFocus(wxFocusEvent& event)
// void OnIdle(wxIdleEvent& event)
// void OnInitDialog(wxInitDialogEvent& event)
// void OnMenuCommand(wxCommandEvent& event)
// void OnMenuHighlight(wxMenuEvent& event)
// void OnMouseEvent(wxMouseEvent& event)
// void OnMove(wxMoveEvent& event)
// void OnPaint(wxPaintEvent& event)
// void OnScroll(wxScrollWinEvent& event)
// void OnSetFocus(wxFocusEvent& event)
// void OnSize(wxSizeEvent& event)
// %alias OnSysColorChanged void OnSysColourChanged(wxOnSysColourChangedEvent& event)
wxEvtHandler* PopEventHandler(bool deleteHandler = FALSE) const
bool PopupMenu(wxMenu* menu, const wxPoint& pos)
%rename PopupMenuXY bool PopupMenu(wxMenu* menu, int x, int y)
void PushEventHandler(wxEvtHandler* handler)
void Raise()
virtual void Refresh(bool eraseBackground = TRUE, const wxRect* rect = NULL)
virtual void ReleaseMouse()
virtual void RemoveChild(wxWindow* child)
virtual bool Reparent(wxWindow* newParent)
virtual wxPoint ScreenToClient(const wxPoint& pt) const
%rename ScreenToClientXY virtual void ScreenToClient(int* x, int* y) const
virtual void ScrollWindow(int dx, int dy, const wxRect* rect = NULL)
virtual void SetAcceleratorTable(const wxAcceleratorTable& accel)
void SetAutoLayout(bool autoLayout)
%alias SetBackgroundColor virtual void SetBackgroundColour(const wxColour& colour)
void SetCaret(wxCaret *caret) const
virtual void SetClientSize(const wxSize& size)
%rename SetClientSizeWH virtual void SetClientSize(int width, int height)
virtual void SetCursor(const wxCursor&cursor)
void SetConstraints(wxLayoutConstraints* constraints)
void SetDropTarget(wxDropTarget* target)
void SetEventHandler(wxEvtHandler* handler)
void SetExtraStyle(long exStyle)
virtual void SetFocus()
void SetFont(const wxFont& font)
%alias SetForegroundColor virtual void SetForegroundColour(const wxColour& colour)
void SetId(int id)
virtual void SetName(const wxString& name)
// obsolete.
// virtual void SetPalette(wxPalette* palette)
virtual void SetScrollbar(int orientation, int position, int thumbSize, int range, bool refresh = TRUE)
virtual void SetScrollPos(int orientation, int pos, bool refresh = TRUE)
%rename SetDimensions virtual void SetSize(int x, int y, int width, int height, int sizeFlags = wxSIZE_AUTO)
virtual void SetSize(int width, int height)
%rename SetPosition virtual void SetSize(const wxSize& size)
virtual void SetSizeHints(int minW=-1, int minH=-1, int maxW=-1, int maxH=-1, int incW=-1, int incH=-1)
void SetSizer(wxSizer* sizer)
virtual void SetTitle(const wxString& title)
virtual void SetValidator(const wxValidator& validator)
void SetToolTip(const wxString& tip)
wxToolTip* GetToolTip() const
void SetWindowStyle(long style)
virtual void SetWindowStyleFlag(long style)
virtual bool Show(bool show)
virtual bool TransferDataFromWindow()
virtual bool TransferDataToWindow()
virtual bool Validate()
void WarpPointer(int x, int y)



///////////////////////////////////////////////////////////////////////////////
// MANAGED WINDOWS
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// wxPanel

%class wxPanel, wxWindow

wxPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL, const wxString& name = "panel")
~wxPanel()
bool Create(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL, const wxString& name = "panel")
// FIXME: 2.3.2
// wxButton* GetDefaultItem() const
void InitDialog()
// %alias OnSysColorChanged void OnSysColourChanged(wxSysColourChangedEvent& event)
void SetDefaultItem(wxButton *btn)


///////////////////////////////////////////////////////////////////////////////
// wxDialog


%class wxDialog, wxPanel
wxDialog(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE, const wxString& name = "dialogBox")
~wxDialog()
void Centre(int direction = wxBOTH)
bool Create(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE, const wxString& name = "dialogBox")
void EndModal(int retCode)
int GetReturnCode()
wxString GetTitle() const
void Iconize(const bool iconize)
bool IsIconized() const
bool IsModal() const
// void OnCharHook(wxKeyEvent& event)
// void OnApply(wxCommandEvent& event)
// void OnCancel(wxCommandEvent& event)
// void OnOK(wxCommandEvent& event)
// %alias OnSysColorChanged void OnSysColourChanged(wxSysColourChangedEvent& event)
void SetModal(const bool flag)
void SetReturnCode(int retCode)
void SetTitle(const wxString& title)
bool Show(const bool show)
int ShowModal()

///////////////////////////////////////////////////////////////////////////////
// wxFrame
%class wxFrame, wxWindow

wxFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_FRAME_STYLE, const wxString& name = "frame")
~wxFrame()
void Centre(int direction = wxBOTH)
void Command(int id)
bool Create(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_FRAME_STYLE, const wxString& name = "frame")
virtual wxStatusBar* CreateStatusBar(int number = 1, long style = 0, wxWindowID id = -1, const wxString& name = "statusBar")
virtual wxToolBar* CreateToolBar(long style = wxNO_BORDER | wxTB_HORIZONTAL, wxWindowID id = -1, const wxString& name = "toolBar")
wxPoint GetClientAreaOrigin() const
wxMenuBar* GetMenuBar() const
wxStatusBar* GetStatusBar() const
wxString GetTitle() const
wxToolBar* GetToolBar() const
void Iconize(bool iconize)
bool IsIconized() const
bool IsMaximized() const
void Maximize(bool maximize)
// void OnActivate(wxActivateEvent& event)
// virtual wxStatusBar* OnCreateStatusBar(int number, long style, wxWindowID id, const wxString& name)
// virtual wxToolBar* OnCreateToolBar(long style, wxWindowID id, const wxString& name)
// void OnMenuCommand(wxCommandEvent& event)
// void OnMenuHighlight(wxMenuEvent& event)
// void OnSize(wxSizeEvent& event)
void SetIcon(const wxIcon& icon)
void SetMenuBar(wxMenuBar* menuBar)
void SetStatusBar(wxStatusBar* statusBar)
virtual void SetStatusText(const wxString& text, int number = 0)
virtual void SetStatusWidths(int n, int *widths)
// wxPython note: Only a single parameter is required, a Python list of integers.
void SetToolBar(wxToolBar* toolBar)
virtual void SetTitle(const wxString& title)
// FIX: Missing in GTK
win: bool ShowFullScreen(bool show, long style = wxFULLSCREEN_ALL)

    
///////////////////////////////////////////////////////////////////////////////
// wxMDIParentFrame

%class wxMDIParentFrame, wxFrame
wxMDIParentFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_FRAME_STYLE | wxVSCROLL | wxHSCROLL, const wxString& name = "frame")
~wxMDIParentFrame()
void ActivateNext()
void ActivatePrevious()
void ArrangeIcons()
void Cascade()
bool Create(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_FRAME_STYLE | wxVSCROLL | wxHSCROLL, const wxString& name = "frame")
// virtual void GetClientSize(int* width, int* height) const
%{
    void wxMDIParentFrame_GetClientSizeWidth()
    {
        int width, height;
        ((wxMDIParentFrame *)wMe)->GetClientSize(&width, &height);
        wPushNumber( (wNumber)width );
    }

    void wxMDIParentFrame_GetClientSizeHeight()
    {
        int width, height;
        ((wxMDIParentFrame *)wMe)->GetClientSize(&width, &height);
        wPushNumber( (wNumber)height );
    }

%}
%method GetClientSizeWidth  wxMDIParentFrame_GetClientSizeWidth()
%method GetClientSizeHeight wxMDIParentFrame_GetClientSizeHeight()

wxMDIChildFrame* GetActiveChild() const
wxMDIClientWindow* GetClientWindow() const
virtual wxWindow* GetToolBar() const
// FIX: Missing in GTK
win: wxMenu* GetWindowMenu() const
// virtual wxMDIClientWindow* OnCreateClient()
// Decl error
// virtual void SetToolBar(wxWindow* toolbar)
virtual void SetToolBar(wxToolBar* toolbar)
// FIX: Missing in GTK
win: void SetWindowMenu(wxMenu* menu)
void Tile()

///////////////////////////////////////////////////////////////////////////////
// wxMDIChildFrame

%class wxMDIChildFrame, wxFrame

wxMDIChildFrame(wxMDIParentFrame* parent, wxWindowID id, const wxString& title, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_FRAME_STYLE, const wxString& name = "frame")
~wxMDIChildFrame()
void Activate()
// Decl error
//bool Create(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_FRAME_STYLE, const wxString& name = "frame")
bool Create(wxMDIParentFrame* parent, wxWindowID id, const wxString& title, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_FRAME_STYLE, const wxString& name = "frame")
// FIX: Missing in GTK - Maximize(bool) exists
win: void Maximize()
void Restore()

///////////////////////////////////////////////////////////////////////////////
// wxMiniFrame

%class wxMiniFrame, wxFrame
%include "wx/minifram.h"
wxMiniFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_FRAME_STYLE, const wxString& name = "frame")
~wxMiniFrame()
bool Create(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_FRAME_STYLE, const wxString& name = "frame")

///////////////////////////////////////////////////////////////////////////////
// wxWizard

// Can't use until wxWizardPage is fixed
// %class wxWizard, wxDialog
// %include "wx/wizard.h"

// static wxWizard* Create(wxWindow* parent, int id = -1, const wxString& title = wxEmptyString, const wxBitmap& bitmap = wxNullBitmap, const wxPoint& pos = wxDefaultPosition)
// bool RunWizard(wxWizardPage* firstPage)
// wxWizardPage* GetCurrentPage() const
// wxSize GetPageSize() const
// void SetPageSize(const wxSize& sizePage)

///////////////////////////////////////////////////////////////////////////////
// wxTabbedDialog                deprecated; use wxNotebook instead
//

// %class wxTabbedDialog, wxDialog
// %include "wx/wxtab.h"
// 
// wxTabbedDialog(wxWindow *parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style=wxDEFAULT_DIALOG_STYLE, const wxString& name="dialogBox")
// ~wxTabbedDialog()
// void SetTabView(wxTabView *view)
// wxTabView * GetTabView()

///////////////////////////////////////////////////////////////////////////////
// MISCELLANEOUS WINDOWS
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// wxScrolledWindow

%class wxScrolledWindow, wxPanel
wxScrolledWindow(wxWindow* parent, wxWindowID id = -1, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxHSCROLL | wxVSCROLL, const wxString& name = "scrolledWindow")
~wxScrolledWindow()
// Error: missing comma
// void CalcScrolledPosition( int x, int y, int *xx int *yy) const
void CalcScrolledPosition( int x, int y, int *xx, int *yy) const
void CalcUnscrolledPosition( int x, int y, int *xx, int *yy) const
bool Create(wxWindow* parent, wxWindowID id = -1, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxHSCROLL | wxVSCROLL, const wxString& name = "scrolledWindow")
void EnableScrolling(const bool xScrolling, const bool yScrolling)
// void GetScrollPixelsPerUnit(int* xUnit, int* yUnit) const
%{
    void wxScrolledWindow_GetScrollPixelsPerUnitX()
    {
        int xUnit, yUnit;
        ((wxScrolledWindow *)wMe)->GetScrollPixelsPerUnit(&xUnit, &yUnit);
        wPushNumber( (wNumber)xUnit );
    }

    void wxScrolledWindow_GetScrollPixelsPerUnitY()
    {
        int xUnit, yUnit;
        ((wxScrolledWindow *)wMe)->GetScrollPixelsPerUnit(&xUnit, &yUnit);
        wPushNumber( (wNumber)yUnit );
    }
%}
%method GetScrollPixelsPerUnitX wxScrolledWindow_GetScrollPixelsPerUnitX()
%method GetScrollPixelsPerUnitY wxScrolledWindow_GetScrollPixelsPerUnitY()

// void GetVirtualSize(int* x, int* y) const
%{
    void wxScrolledWindow_GetVirtualSizeX()
    {
        int x, y;
        ((wxScrolledWindow *)wMe)->GetVirtualSize(&x, &y);
        wPushNumber( (wNumber)x );
    }

    void wxScrolledWindow_GetVirtualSizeY()
    {
        int x, y;
        ((wxScrolledWindow *)wMe)->GetVirtualSize(&x, &y);
        wPushNumber( (wNumber)y );
    }
%}
%method GetVirtualSizeX     wxScrolledWindow_GetVirtualSizeX()
%method GetVirtualSizeY     wxScrolledWindow_GetVirtualSizeY()

bool IsRetained() const
void PrepareDC(wxDC& dc)
// virtual void OnDraw(wxDC& dc)
void Scroll(int x, int y)
void SetScrollbars(int pixelsPerUnitX, int pixelsPerUnitY, int noUnitsX, int noUnitsY, int xPos = 0, int yPos = 0, bool noRefresh = FALSE)
void SetTargetWindow(wxWindow* window)
//void GetViewStart(int* x, int* y) const
%{
    void wxScrolledWindow_GetViewStartX()
    {
        int x, y;
        ((wxScrolledWindow *)wMe)->GetViewStart(&x, &y);
        wPushNumber( (wNumber)x );
    }

    void wxScrolledWindow_GetViewStartY()
    {
        int x, y;
        ((wxScrolledWindow *)wMe)->GetViewStart(&x, &y);
        wPushNumber( (wNumber)y );
    }
%}
%method GetViewStartX     wxScrolledWindow_GetViewStartX()
%method GetViewStartY     wxScrolledWindow_GetViewStartY()


///////////////////////////////////////////////////////////////////////////////
// wxGrid

%skip
%class wxGrid, wxPanel
%include "wx/grid.h"

wxGrid(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style=0, const wxString& name="grid")
void AdjustScrollbars()
bool AppendCols(int n=1, bool updateLabels=TRUE)
bool AppendRows(int n=1, bool updateLabels=TRUE)
void BeginBatch()
// bool CellHitTest(int x, int y, int *row, int *col)
%{
    void wxGrid_CellHitTest()
    {
        int row, col;
        bool result;
        int y = wPopNumber();
        int x = wPopNumber();
        result = ((wxGrid *)wMe)->CellHitTest(x, y, &row, &col)
        wPushNumber( (wNumber)result );
    }

    void wxGrid_CellHitTestRow()
    {
        int row, col;
        int y = wPopNumber();
        int x = wPopNumber();
        ((wxGrid *)wMe)->CellHitTest(x, y, &row, &col)
        wPushNumber( (wNumber)row );
    }

    void wxGrid_CellHitTestCol()
    {
        int row, col;
        int y = wPopNumber();
        int x = wPopNumber();
        ((wxGrid *)wMe)->CellHitTest(x, y, &row, &col)
        wPushNumber( (wNumber)col );
    }

%}
%method CellHitTestRow  wxGrid_CellHitTest( int x, int y )
%method CellHitTestRow  wxGrid_CellHitTestRow( int x, int y )
%method CellHitTestCol  wxGrid_CellHitTestCol( int x, int y )

bool CreateGrid(int rows, int cols, wxString **cellValues=NULL, short *widths=NULL, short defaultWidth=wxGRID_DEFAULT_CELL_WIDTH, short defaultHeight=wxGRID_DEFAULT_CELL_HEIGHT)
bool CurrentCellVisible()
bool DeleteCols(int pos=0, int n=1, bool updateLabels=TRUE)
bool DeleteRows(int pos=0, int n=1, bool updateLabels=TRUE)
void EndBatch()
int GetBatchCount() const
wxGridCell * GetCell(int row, int col) const
int GetCellAlignment(int row, int col) const
%rename GetDefCellAlignment int GetCellAlignment() const
%alias GetCellBackgroundColor wxColour& GetCellBackgroundColour(int row, int col) const
%rename GetDefCellBackgroundColour %alias GetDefCellBackgroundColor wxColour& GetCellBackgroundColour() const
// wxGridCell *** GetCells() const
%alias GetCellTextColor wxColour& GetCellTextColour(int row, int col) const
%alias GetDefCellTextColor %rename GetDefCellTextColour wxColour& GetCellTextColour() const
const wxFont& GetCellTextFont(int row, int col) const
%rename GetDefCellTextFont wxFont& GetCellTextFont() const
wxString& GetCellValue(int row, int col) const
int GetCols() const
int GetColumnWidth(int col) const
wxRectangle * GetCurrentRect() const
int GetCursorColumn() const
int GetCursorRow() const
bool GetEditable() const
bool GetEditInPlace() const
wxScrollBar * GetHorizScrollBar() const
int GetLabelAlignment(int orientation) const
%alias GetLabelBackgroundColor wxColour& GetLabelBackgroundColour() const
int GetLabelSize(int orientation) const
%alias GetLabelTextColor wxColour& GetLabelTextColour() const
wxFont& GetLabelTextFont() const
wxString& GetLabelValue(int orientation, int pos) const
int GetRowHeight(int row) const
int GetRows() 
int GetScrollPosX() const
int GetScrollPosY() const
wxTextCtrl * GetTextItem() const
wxScrollBar * GetVertScrollBar() const
bool InsertCols(int pos=0, int n=1, bool updateLabels=TRUE)
bool InsertRows(int pos=0, int n=1, bool updateLabels=TRUE)
// void OnActivate(bool active)
// void OnChangeLabels()
// void OnChangeSelectionLabel()
// wxGridCell * OnCreateCell()
// void OnLeftClick(int row, int col, int x, int y, bool control, bool shift)
// void OnRightClick(int row, int col, int x, int y, bool control, bool shift)
// void OnLeftClick(int row, int col, int x, int y, bool control, bool shift)
// void OnRightClick(int row, int col, int x, int y, bool control, bool shift)
// void OnSelectCell(int row, int col)
// void OnSelectCellImplementation(wxDC *dc, int row, int col)
void SetCellAlignment(int alignment, int row, int col)
%rename SetDefCellAlignment void SetCellAlignment(int alignment)
%alias SetCellBackgroundColor void SetCellBackgroundColour(const wxColour& colour, int row, int col)
%alias SetDefCellBackgroundColor %rename SetDefCellBackgroundColor void SetCellBackgroundColour(const wxColour& colour)
%alias SetCellTextColor void SetCellTextColour(const wxColour& colour, int row, int col)
%alias SetCellTextColor %rename SetDefCellTextColour void SetCellTextColour(const wxColour& colour)
void SetCellTextFont(const wxFont& font, int row, int col)
%rename SetDefCellTextFont void SetCellTextFont(const wxFont& font)
void SetCellValue(const wxString& val, int row, int col)
void SetColumnWidth(int col, int width)
void SetDividerPen(const wxPen& pen)
void SetEditable(bool editable)
void SetEditInPlace(bool edit = TRUE)
void SetGridCursor(int row, int col)
void SetLabelAlignment(int orientation, int alignment)
%alias SetLabelBackgroundColor void SetLabelBackgroundColour(const wxColour& value)
void SetLabelSize(int orientation, int size)
%alias SetLabelTextColor void SetLabelTextColour(const wxColour& value)
void SetLabelTextFont(const wxFont& font)
void SetLabelValue(int orientation, const wxString& value, int pos)
void SetRowHeight(int row, int height)
void UpdateDimensions()


///////////////////////////////////////////////////////////////////////////////
// wxSplitterWindow

%class wxSplitterWindow, wxWindow
%include "wx/splitter.h"

wxSplitterWindow(wxWindow* parent, wxWindowID id, const wxPoint& point = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style=wxSP_3D, const wxString& name = "splitterWindow")
~wxSplitterWindow()
// Error: int x, id = -1 missing
// bool Create(wxWindow* parent, wxWindowID id, int x, const wxPoint& point = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style=wxSP_3D, const wxString& name = "splitterWindow")
bool Create(wxWindow *parent, wxWindowID id = -1, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxSP_3D|wxCLIP_CHILDREN, const wxString& name = "splitter");
int GetMinimumPaneSize() const
int GetSashPosition()
int GetSplitMode() const
wxWindow* GetWindow1() const
wxWindow* GetWindow2() const
void Initialize(wxWindow* window)
bool IsSplit() const
// virtual void OnDoubleClickSash(int x, int y)
// virtual void OnUnsplit(wxWindow* removed)
// virtual bool OnSashPositionChange(int newSashPosition)
bool ReplaceWindow(wxWindow * winOld, wxWindow * winNew)
void SetSashPosition(int position, const bool redraw = TRUE)
void SetMinimumPaneSize(int paneSize)
void SetSplitMode(int mode)
bool SplitHorizontally(wxWindow* window1, wxWindow* window2, int sashPosition = 0)
bool SplitVertically(wxWindow* window1, wxWindow* window2, int sashPosition = 0)
bool Unsplit(wxWindow* toRemove = NULL)

///////////////////////////////////////////////////////////////////////////////
// wxStatusBar

%class wxStatusBar, wxWindow
// FIXME: 2.3.2
// wxStatusBar(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = "statusBar")
~wxStatusBar()
// Error: wrong set of args
// bool Create(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = "statusBar")
bool Create(wxWindow *parent, wxWindowID id, long style, const wxString& name = wxPanelNameStr)
virtual bool GetFieldRect(int i, wxRect& rect) const
int GetFieldsCount() const
virtual wxString GetStatusText(int ir = 0) const
// Error: not a member
// virtual void DrawField(wxDC& dc, int i)
// Error: not a member
// virtual void DrawFieldText(wxDC& dc, int i)
// Fix: 'InitColours' is not a member of 'wxStatusBar'
// %alias InitColors virtual void InitColours()
// %alias OnSysColorChanged void OnSysColourChanged(wxSysColourChangedEvent& event)
virtual void SetFieldsCount(int number = 1, int* widths = NULL)
// wxPython note: Only the first parameter is accepted. 
// Use SetStatusWidths to set the widths of the fields.
void SetMinHeight(int height)
virtual void SetStatusText(const wxString& text, int i = 0)
virtual void SetStatusWidths(int n, int *widths)
// wxPython note: Only a single parameter is required, a Python list of integers.

///////////////////////////////////////////////////////////////////////////////
// CONTROLS
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// wxControl

%class wxControl, wxWindow

void Command(wxCommandEvent& event)
wxString& GetLabel()
void SetLabel(const wxString& label)


///////////////////////////////////////////////////////////////////////////////
// wxButton


%class wxButton, wxControl    

// Error: pos missing optional value
// wxButton(wxWindow* parent, wxWindowID id, const wxString& label, const wxPoint& pos, const wxSize& size = wxDefaultSize, long style = 0, const wxValidator& validator, const wxString& name = "button")
wxButton(wxWindow *parent, wxWindowID id, const wxString& label, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxButtonNameStr)
~wxButton()
// Error: missing default validator
// bool Create(wxWindow* parent, wxWindowID id, const wxString& label, const wxPoint& pos, const wxSize& size = wxDefaultSize, long style = 0, const wxValidator& validator, const wxString& name = "button")
bool Create(wxWindow *parent, wxWindowID id, const wxString& label, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxButtonNameStr)
wxString GetLabel() const
wxSize GetDefaultSize()
void SetDefault()
void SetLabel(const wxString& label)


///////////////////////////////////////////////////////////////////////////////
// wxBitmapButton

%class wxBitmapButton, wxButton

wxBitmapButton( wxWindow* parent, wxWindowID id, const wxBitmap& bitmap, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxBU_AUTODRAW, const wxValidator& validator = wxDefaultValidator, const wxString& name = "button")
~wxBitmapButton()
// Error: missing default validator
bool Create(wxWindow* parent, wxWindowID id, const wxBitmap& bitmap, const wxPoint& pos, const wxSize& size = wxDefaultSize, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = "button")
wxBitmap& GetBitmapDisabled() const
wxBitmap& GetBitmapFocus() const
wxBitmap& GetBitmapLabel() const
wxBitmap& GetBitmapSelected() const
void SetBitmapDisabled(const wxBitmap& bitmap)
void SetBitmapFocus(const wxBitmap& bitmap)
void SetBitmapLabel(const wxBitmap& bitmap)
void SetBitmapSelected(const wxBitmap& bitmap)

///////////////////////////////////////////////////////////////////////////////
// wxCalendarCtrl

%class wxCalendarCtrl, wxControl
%include "wx/calctrl.h"

wxCalendarCtrl(wxWindow* parent, wxWindowID id, const wxDateTime& date = wxDefaultDateTime, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxCAL_SHOW_HOLIDAYS, const wxString& name = wxCalendarNameStr)
bool Create(wxWindow* parent, wxWindowID id, const wxDateTime& date = wxDefaultDateTime, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxCAL_SHOW_HOLIDAYS, const wxString& name = wxCalendarNameStr)
~wxCalendarCtrl()
void SetDate(const wxDateTime& date)
// Error: not being cast correctly
// const wxDateTime& GetDate() const
void EnableYearChange(bool enable = TRUE)
void EnableMonthChange(bool enable = TRUE)
void EnableHolidayDisplay(bool display = TRUE)
%alias SetHeaderColors void SetHeaderColours(const wxColour& colFg, const wxColour& colBg)
%alias GetHeaderColorFg const wxColour& GetHeaderColourFg() const
%alias GetHeaderColorBg const wxColour& GetHeaderColourBg() const
%alias SetHighlightColors void SetHighlightColours(const wxColour& colFg, const wxColour& colBg)
%alias GetHighlightColorFg const wxColour& GetHighlightColourFg() const
%alias GetHighlightColorBg const wxColour& GetHighlightColourBg() const
%alias SetHolidayColors void SetHolidayColours(const wxColour& colFg, const wxColour& colBg)
%alias GetHolidayColorFg const wxColour& GetHolidayColourFg() const
%alias GetHolidayColorBg const wxColour& GetHolidayColourBg() const
wxCalendarDateAttr * GetAttr(size_t day) const
void SetAttr(size_t day, wxCalendarDateAttr* attr)
void SetHoliday(size_t day)
void ResetAttr(size_t day)
// Error: ???
// wxCalendarHitTestResult HitTest(const wxPoint& pos, wxDateTime* date = NULL, wxDateTime::WeekDay* wd = NULL)

///////////////////////////////////////////////////////////////////////////////
// wxCheckBox

%class wxCheckBox, wxControl

// Error: missing default validator
wxCheckBox(wxWindow* parent, wxWindowID id, const wxString& label, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxValidator& val = wxDefaultValidator, const wxString& name = "checkBox")
~wxCheckBox()
// Error: missing default validator
bool Create(wxWindow* parent, wxWindowID id, const wxString& label, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxValidator& val = wxDefaultValidator, const wxString& name = "checkBox")
bool GetValue() const
void SetValue(const bool state)

///////////////////////////////////////////////////////////////////////////////
// wxChoice

%class wxChoice, wxControl

// Error: missing defaults
// wxChoice(wxWindow *parent, wxWindowID id, const wxPoint& pos, const wxSize& size, int n, const wxString choices[], long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = "choice")
wxChoice(wxWindow *parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, int n = 0, const wxString choices[] = NULL, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxChoiceNameStr)
// wxPython note: The wxChoice constructor in wxPython reduces the n and choices arguments
// are to a single argument, which is a list of strings.
~wxChoice()
void Append(const wxString& item)
void Clear()
// Error: missing validator
// bool Create(wxWindow *parent, wxWindowID id, const wxPoint& pos, const wxSize& size, int n, const wxString choices[], long style = 0, const wxString& name = "choice")
bool Create(wxWindow *parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, int n = 0, const wxString choices[] = NULL, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxChoiceNameStr)
int FindString(const wxString& string) const
int GetColumns() const
void* GetClientData(int n) const
int GetSelection() const
wxString GetString(int n) const
wxString GetStringSelection() const
// FIXME: 2.3.3
// int Number() const
void SetClientData(int n, void* data)
void SetColumns(int n = 1)
void SetSelection(int n)
void SetStringSelection(const wxString& string)

///////////////////////////////////////////////////////////////////////////////
// wxComboBox

%class wxComboBox, wxChoice

// Error: was int n, not int n = 0, and list was not NULL
wxComboBox(wxWindow* parent, wxWindowID id, const wxString& value = "", const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, int n = 0, const wxString choices[] = NULL, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = "comboBox")
// wxPython note: The wxComboBox constructor in wxPython reduces the n and 
// choices arguments are to a single argument, which is a list of strings.
~wxComboBox()
void Append(const wxString& item)
void Clear()
// Error: missing default value for n, choices[]
bool Create(wxWindow* parent, wxWindowID id, const wxString& value = "", const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, int n = 0, const wxString choices[] = NULL, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = "comboBox")
void Copy()
void Cut()
void Delete(int n)
int FindString(const wxString& string)
void* GetClientData(int n) const
long GetInsertionPoint() const
long GetLastPosition() const
int GetSelection() const
wxString GetString(int n) const
wxString GetStringSelection() const
wxString GetValue() const
// FIXME: 2.3.2
// int Number() const
void Paste()
void Replace(long from, long to, const wxString& text)
void Remove(long from, long to)
void SetClientData(int n, void* data)
void SetInsertionPoint(long pos)
void SetInsertionPointEnd()
void SetSelection(int n)
%rename SetMark void SetSelection(long from, long to)
void SetValue(const wxString& text)

///////////////////////////////////////////////////////////////////////////////
// wxGauge

%class wxGauge, wxControl

wxGauge(wxWindow* parent, wxWindowID id, int range, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxGA_HORIZONTAL, const wxValidator& validator = wxDefaultValidator, const wxString& name = "gauge")
~wxGauge()
bool Create(wxWindow* parent, wxWindowID id, int range, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxGA_HORIZONTAL, const wxValidator& validator = wxDefaultValidator, const wxString& name = "gauge")
int GetBezelFace() const
int GetRange() const
int GetShadowWidth() const
int GetValue() const
void SetBezelFace(int width)
void SetRange(int range)
void SetShadowWidth(int width)
void SetValue(int pos)


///////////////////////////////////////////////////////////////////////////////
// wxStaticBox

%class wxStaticBox, wxControl

wxStaticBox(wxWindow* parent, wxWindowID id, const wxString& label, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = "staticBox")
~wxStaticBox()
bool Create(wxWindow* parent, wxWindowID id, const wxString& label, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = "staticBox")


///////////////////////////////////////////////////////////////////////////////
// wxListBox

%class wxListBox, wxControl

// Error: was int n, not int n = 0
wxListBox(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, int n = 0, const wxString choices[] = NULL, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = "listBox")
// wxPython note: The wxListBox constructor in wxPython reduces the n and 
// choices arguments are to a single argument, which is a list of strings.
~wxListBox()
void Append(const wxString& item)
void Clear()
// Error: missing default value for n
bool Create(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, int n = 0, const wxString choices[] = NULL, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = "listBox")
void Delete(int n)
void Deselect(int n)
int FindString(const wxString& string)
void* GetClientData(int n) const
int GetSelection() const
int GetSelections(wxArrayInt& selections) const
// wxPython note: The wxPython version of this method takes no parameters and 
// returns a tuple of the selected items.
wxString GetString(int n) const
wxString GetStringSelection() const
// Fix: Ambiguity between 'wxString::wxString(int)' and 'wxString::wxString(unsigned int)' 
// void InsertItems(int nItems, const wxString items, int pos)
// wxPython note: The first two parameters are collapsed into a single parameter 
// for wxPython, which is a list of strings.
// FIXME: 2.3.2
// int Number() const
bool Selected(int n) const
// Skip: not implemented in GTK
// void Set(int n, const wxString* choices)
void SetClientData(int n, void* data)
void SetFirstItem(int n)
void SetSelection(int n, const bool select = TRUE)
void SetString(int n, const wxString& string)
void SetStringSelection(const wxString& string, const bool select = TRUE)

///////////////////////////////////////////////////////////////////////////////
// wxCheckListBox

%class wxCheckListBox, wxListBox
%include "wx/checklst.h"

// Error: was int n, not int n = 0
wxCheckListBox(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, int n = 0, const wxString choices[] = NULL, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = "listBox")
// wxPython note: The wxCheckListBox constructor in wxPython reduces the n and choices 
// arguments are to a single argument, which is a list of strings.
~wxCheckListBox()
void Check(int item, bool check = TRUE)
bool IsChecked(int item) const



///////////////////////////////////////////////////////////////////////////////
// wxListCtrl

%class wxListCtrl, wxControl
%include "wx/listctrl.h"

wxListCtrl(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxLC_ICON, const wxValidator& validator = wxDefaultValidator, const wxString& name = "listCtrl")
~wxListCtrl()
bool Arrange(int flag = wxLIST_ALIGN_DEFAULT)
bool Create(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxLC_ICON, const wxValidator& validator = wxDefaultValidator, const wxString& name = "listCtrl")
void ClearAll()
bool DeleteItem(long item)
bool DeleteAllItems()
bool DeleteColumn(int col)
void EditLabel(long item)
bool EnsureVisible(long item)
long FindItem(long start, const wxString& str, const bool partial = FALSE)
%rename FindItemData long FindItem(long start, long data)
%rename FindItemAtPos long FindItem(long start, const wxPoint& pt, int direction)
bool GetColumn(int col, wxListItem& item) const
int GetColumnWidth(int col) const
int GetCountPerPage() const
// Fix: Must take address of a memory location
// wxTextCtrl& GetEditControl() const
wxImageList* GetImageList(int which) const
bool GetItem(wxListItem& info) const
// The wxPython version of this method takes an integer parameter for the item ID, 
// an optional integer for the column number, and returns the wxListItem object. 
long GetItemData(long item) const
bool GetItemPosition(long item, wxPoint& pos) const
// The wxPython version of this method accepts only the item ID and returns the wxPoint.
bool GetItemRect(long item, wxRect& rect, int code = wxLIST_RECT_BOUNDS) const
// The wxPython version of this method accepts only the item ID and code and 
// returns the wxRect.
int GetItemState(long item, long stateMask) const
int GetItemCount() const
int GetItemSpacing(bool isSmall) const
wxString GetItemText(long item) const
long GetNextItem(long item, int geometry = wxLIST_NEXT_ALL, int state = wxLIST_STATE_DONTCARE) const
int GetSelectedItemCount() const
%alias GetTextColor wxColour GetTextColour() const
long GetTopItem() const
long HitTest(const wxPoint& point, int& flags)
// wxPython note: A tuple of values is returned in the wxPython version of this method. 
// The first value is the item id and the second is the flags value mentioned above.
long InsertColumn(long col, wxListItem& info)
%rename InsertColumnInfo long InsertColumn(long col, const wxString& heading, int format = wxLIST_FORMAT_LEFT, int width = -1)
long InsertItem(wxListItem& info)
%rename InsertStringItem long InsertItem(long index, const wxString& label)
%rename InsertImageItem long InsertItem(long index, int imageIndex)
%rename InsertImageStringItem long InsertItem(long index, const wxString& label, int imageIndex)
bool ScrollList(int dx, int dy)
%alias SetBackgroundColor void SetBackgroundColour(const wxColour& col)
bool SetColumn(int col, wxListItem& item)
bool SetColumnWidth(int col, int width)
void SetImageList(wxImageList* imageList, int which)
bool SetItem(wxListItem& info)
%rename SetStringItem long SetItem(long index, int col, const wxString& label, int imageId = -1)
bool SetItemData(long item, long data)
bool SetItemImage(long item, int image, int selImage)
bool SetItemPosition(long item, const wxPoint& pos)
bool SetItemState(long item, long state, long stateMask)
void SetItemText(long item, const wxString& text)
void SetSingleStyle(long style, const bool add = TRUE)
%alias SetTextColor void SetTextColour(const wxColour& col)
void SetWindowStyleFlag(long style)
// Fix: can't handle callbacks - Incompatible type conversion in function
// bool SortItems(wxListCtrlCompare fnSortCallBack, long data)
// wxPython uses the sortData parameter to pass the Python function to call, so it is not 
// available for programmer use. Call SortItems with a reference to a callable object that 
// expects two parameters.


///////////////////////////////////////////////////////////////////////////////
// wxTabCtrl

// FIX: Missing from GTK
// Is this class deprecated?

%skip

%class wxTabCtrl, wxControl
%include "wx/tabctrl.h"

// Error: missing default for size
wxTabCtrl(wxWindow *parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = "tabCtrl")

~wxTabCtrl()
// Error: missing default for size
bool Create(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = "tabCtrl")
bool DeleteAllItems()
bool DeleteItem(int item)
int GetCurFocus() const
wxImageList* GetImageList() const
int GetItemCount() const
// Error: Too few parameters in call
// void* GetItemData() const
void* GetItemData(int item) const
// Error: Too few parameters in call
// int GetItemImage() const
int GetItemImage(int item) const;
bool GetItemRect(int item, wxRect& rect) const
// Error: Too few parameters in call
// wxString GetItemText() const
wxString GetItemText(int item) const
int GetRowCount() const
int GetSelection() const
int HitTest(const wxPoint& pt, long& flags)
void InsertItem(int item, const wxString& text, int imageId = -1, void* clientData = NULL)
bool SetItemData(int item, void* data)
bool SetItemImage(int item, int image)
void SetImageList(wxImageList* imageList)
void SetItemSize(const wxSize& size)
bool SetItemText(int item, const wxString& text)
void SetPadding(const wxSize& padding)
int SetSelection(int item)


///////////////////////////////////////////////////////////////////////////////
// wxTextCtrl

    
// %class wxTextCtrl, streambuf
%class wxTextCtrl, wxControl

// Error: missing default validator
// wxTextCtrl(wxWindow* parent, wxWindowID id, const wxString& value = "", const wxPoint& pos, const wxSize& size = wxDefaultSize, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = "text")
wxTextCtrl(wxWindow *parent, wxWindowID id, const wxString& value = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxTextCtrlNameStr)

~wxTextCtrl()
void AppendText(const wxString& text)
virtual bool CanCopy()
virtual bool CanCut()
virtual bool CanPaste()
virtual bool CanRedo()
virtual bool CanUndo()
virtual void Clear()
virtual void Copy()
// Error: missing default validator, pos
bool Create(wxWindow* parent, wxWindowID id, const wxString& value = "", const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = "text")
virtual void Cut()
void DiscardEdits()
virtual long GetInsertionPoint() const
virtual long GetLastPosition() const
int GetLineLength(long lineNo) const
wxString GetLineText(long lineNo) const
int GetNumberOfLines() const
// virtual void GetSelection(long* from, long* to)
%{
    void wxTextCtrl_GetSelectionFrom()
    {
        long from, to;
        ((wxTextCtrl *)wMe)->GetSelection(&from, &to);
        wPushNumber( (wNumber)from );
    }

    void wxTextCtrl_GetSelectionTo()
    {
        long from, to;
        ((wxTextCtrl *)wMe)->GetSelection(&from, &to);
        wPushNumber( (wNumber)to );
    }

%}
%method GetSelectionFrom    wxTextCtrl_GetSelectionFrom()
%method GetSelectionTo      wxTextCtrl_GetSelectionTo()


wxString GetValue() const
bool IsModified() const
bool LoadFile(const wxString& filename)
// void OnChar(wxKeyEvent& event)
// void OnDropFiles(wxDropFilesEvent& event)
virtual void Paste()
bool PositionToXY(long pos, long *x, long *y) const
// In Python, PositionToXY() returns a tuple containing the x and y values, 
// so (x,y) = PositionToXY() is equivalent to the call described above.
virtual void Redo()
virtual void Remove(long from, long to)
virtual void Replace(long from, long to, const wxString& value)
bool SaveFile(const wxString& filename)
virtual void SetEditable(const bool editable)
virtual void SetInsertionPoint(long pos)
virtual void SetInsertionPointEnd()
virtual void SetSelection(long from, long to)
virtual void SetValue(const wxString& value)
void ShowPosition(long pos)
virtual void Undo()
void WriteText(const wxString& text)
long XYToPosition(long x, long y)
// wxTextCtrl& operator <<(const wxString& s)
// wxTextCtrl& operator <<(int i)
// wxTextCtrl& operator <<(long i)
// wxTextCtrl& operator <<(float f) 
// wxTextCtrl& operator <<(double d)
// wxTextCtrl& operator <<(char c)


///////////////////////////////////////////////////////////////////////////////
// wxTreeCtrl

%class wxTreeCtrl, wxControl
%include "wx/treectrl.h"

wxTreeCtrl(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTR_HAS_BUTTONS, const wxValidator& validator = wxDefaultValidator, const wxString& name = "listCtrl")
~wxTreeCtrl()
wxTreeItemId AddRoot(const wxString& text, int image = -1, int selImage = -1, wxTreeItemData* data = NULL)
wxTreeItemId AppendItem(const wxTreeItemId& parent, const wxString& text, int image = -1, int selImage = -1, wxTreeItemData* data = NULL)
void Collapse(const wxTreeItemId& item)
void CollapseAndReset(const wxTreeItemId& item)
// Error: should have been Create instead of wxTreeCtrl
// bool wxTreeCtrl(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTR_HAS_BUTTONS, const wxValidator& validator = wxDefaultValidator, const wxString& name = "listCtrl")
bool Create(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTR_HAS_BUTTONS, const wxValidator& validator = wxDefaultValidator, const wxString& name = "listCtrl")
void Delete(const wxTreeItemId& item)
void DeleteAllItems()
void EditLabel(const wxTreeItemId& item)
// FIX: Missing in GTK
win: void EndEditLabel(bool cancelEdit)
void EnsureVisible(const wxTreeItemId& item)
void Expand(const wxTreeItemId& item)
// FIX: Missing in GTK
win: bool GetBoundingRect(const wxTreeItemId& item, wxRect& rect, bool textOnly = FALSE) const
// The wxPython version of this method requires only the item and textOnly parameters. 
// The return value is either a wxRect object or None.
size_t GetChildrenCount(const wxTreeItemId& item, bool recursively = TRUE) const
int GetCount() const
// Fix: Must take address of a memory location
// wxTextCtrl& GetEditControl() const
wxTreeItemId GetFirstChild(const wxTreeItemId& item, long& cookie) const
// In wxPython the returned wxTreeItemId and the new cookie value are both returned as a 
// tuple containing the two values.
wxTreeItemId GetFirstVisibleItem() const
wxImageList* GetImageList() const
int GetIndent() const
wxTreeItemData* GetItemData(const wxTreeItemId& item) const
// wxPython provides the following shortcut method:
//        GetPyData(item)  Returns the Python Object associated with 
//                the wxTreeItemData for the given item Id.  
// Fix: (Warning) Initializing wxTreeItemIcon with double
int GetItemImage(const wxTreeItemId& item, wxTreeItemIcon which = wxTreeItemIcon_Normal) const
wxString GetItemText(const wxTreeItemId& item) const
wxTreeItemId GetLastChild(const wxTreeItemId& item) const
wxTreeItemId GetNextChild(const wxTreeItemId& item, long& cookie) const
// In wxPython the returned wxTreeItemId and the new cookie value are both returned as 
// a tuple containing the two values.
wxTreeItemId GetNextSibling(const wxTreeItemId& item) const
wxTreeItemId GetNextVisible(const wxTreeItemId& item) const
wxTreeItemId GetParent(const wxTreeItemId& item) const
wxTreeItemId GetPrevSibling(const wxTreeItemId& item) const
wxTreeItemId GetPrevVisible(const wxTreeItemId& item) const
wxTreeItemId GetRootItem() const
int GetItemSelectedImage(const wxTreeItemId& item) const
wxTreeItemId GetSelection() const
size_t GetSelections(wxArrayTreeItemIds& selection) const
// The wxPython version of this method accepts no parameters and returns a 
// Python list of wxTreeItemIds.
wxImageList* GetStateImageList() const
wxTreeItemId HitTest(const wxPoint& point, int& flags)
// in wxPython both the wxTreeItemId and the flags are returned as a tuple.
wxTreeItemId InsertItem(const wxTreeItemId& parent, const wxTreeItemId& previous, const wxString& text, int image = -1, int selImage = -1, wxTreeItemData* data = NULL)
%rename InsertItemBefore wxTreeItemId InsertItem(const wxTreeItemId& parent, size_t before, const wxString& text, int image = -1, int selImage = -1, wxTreeItemData* data = NULL)
bool IsBold(const wxTreeItemId& item) const
bool IsExpanded(const wxTreeItemId& item) const
bool IsSelected(const wxTreeItemId& item) const
bool IsVisible(const wxTreeItemId& item) const
bool ItemHasChildren(const wxTreeItemId& item) const
// int OnCompareItems(const wxTreeItemId& item1, const wxTreeItemId& item2)
wxTreeItemId PrependItem(const wxTreeItemId& parent, const wxString& text, int image = -1, int selImage = -1, wxTreeItemData* data = NULL)
void ScrollTo(const wxTreeItemId& item)
// Fix: Not an allowed type
// bool SelectItem(const wxTreeItemId& item)
void SetIndent(int indent)
void SetImageList(wxImageList* imageList)
%alias SetItemBackgroundColor void SetItemBackgroundColour(const wxTreeItemId& item, const wxColour& col)
void SetItemBold(const wxTreeItemId& item, bool bold = TRUE)
void SetItemData(const wxTreeItemId& item, wxTreeItemData* data)
// wxPython provides the following shortcut method:
//        SetPyData(item, obj)  Associate the given Python Object with the wxTreeItemData 
                for the given item Id.  
void SetItemFont(const wxTreeItemId& item, const wxFont& font)
void SetItemHasChildren(const wxTreeItemId& item, bool hasChildren = TRUE)
// Fix: (warning) Initializing wxTreeItemIcon with double
void SetItemImage(const wxTreeItemId& item, int image, wxTreeItemIcon which = wxTreeItemIcon_Normal)
void SetItemSelectedImage(const wxTreeItemId& item, int selImage)
void SetItemText(const wxTreeItemId& item, const wxString& text)
%alias SetItemTextColor void SetItemTextColour(const wxTreeItemId& item, const wxColour& col)
void SetStateImageList(wxImageList* imageList)
void SortChildren(const wxTreeItemId& item)
void Toggle(const wxTreeItemId& item)
void Unselect()
void UnselectAll()


///////////////////////////////////////////////////////////////////////////////
// wxScrollBar


%class wxScrollBar, wxControl

wxScrollBar(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxSB_HORIZONTAL, const wxValidator& validator = wxDefaultValidator, const wxString& name = "scrollBar")
~wxScrollBar()
bool Create(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxSB_HORIZONTAL, const wxValidator& validator = wxDefaultValidator, const wxString& name = "scrollBar")
int GetRange() const
int GetPageSize() const
int GetThumbPosition() const
// Error: 'GetThumbLength' is not a member of 'wxScrollBar'
// int GetThumbLength() const
void SetThumbPosition(int viewStart)
virtual void SetScrollbar(int position, int thumbSize, int range, int pageSize, const bool refresh = TRUE)


///////////////////////////////////////////////////////////////////////////////
// wxSpinButton

%class wxSpinButton, wxControl

// Error: Could not find a match for 'wxSpinButton::wxSpinButton(wxWindow *,double,wxPoint,wxSize,double,wxValidator,wxString)'
// wxSpinButton(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxSP_HORIZONTAL, const wxValidator& validator = wxDefaultValidator, const wxString& name = "spinButton")
wxSpinButton(wxWindow *parent, wxWindowID id = -1, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxSP_VERTICAL | wxSP_ARROW_KEYS, const wxString& name = "wxSpinButton")
~wxSpinButton()
// Error: Cannot initialize 'const wxString &' with 'wxValidator'
// bool Create(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxSP_HORIZONTAL, const wxValidator& validator = wxDefaultValidator, const wxString& name = "spinButton")
bool Create(wxWindow *parent, wxWindowID id = -1, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxSP_VERTICAL | wxSP_ARROW_KEYS, const wxString& name = "wxSpinButton")
int GetMax() const
int GetMin() const
int GetValue() const
void SetRange(int min, int max)
void SetValue(int value)


///////////////////////////////////////////////////////////////////////////////
// wxSpinCtrl

%class wxSpinCtrl, wxControl

// Fix: hacked out _T("wxSpinCtrl") in ctor and Create
wxSpinCtrl(wxWindow* parent, wxWindowID id = -1, const wxString& value = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxSP_ARROW_KEYS, int min = 0, int max = 100, int initial = 0, const wxString& name = "wxSpinCtrl")
bool Create(wxWindow* parent, wxWindowID id = -1, const wxString& value = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxSP_ARROW_KEYS, int min = 0, int max = 100, int initial = 0, const wxString& name = "wxSpinCtrl")
void SetValue(const wxString& text)
int GetValue() const
void SetRange(int minVal, int maxVal)
int GetMin() const
int GetMax() const


///////////////////////////////////////////////////////////////////////////////
// wxStaticText

%class wxStaticText, wxControl

wxStaticText(wxWindow* parent, wxWindowID id, const wxString& label, const wxPoint& pos, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = "staticText")
bool Create(wxWindow* parent, wxWindowID id, const wxString& label, const wxPoint& pos, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = "staticText")
wxString GetLabel() const
virtual void SetLabel(const wxString& label)


///////////////////////////////////////////////////////////////////////////////
// wxStaticBitmap

%class wxStaticBitmap, wxControl

// Error: (fix) arglist
// wxStaticBitmap(wxWindow* parent, wxWindowID id, const wxBitmap& label = "", const wxPoint& pos, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = "staticBitmap")
// Error: (fix) arglist
// bool Create(wxWindow* parent, wxWindowID id, const wxBitmap& label = "", const wxPoint& pos, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = "staticBitmap")
// Fix: Cannot convert 'const wxBitmap *' to 'wxBitmap *'
// wxBitmap& GetBitmap() const
virtual void SetBitmap(const wxBitmap& label)


///////////////////////////////////////////////////////////////////////////////
// wxRadioBox

%class wxRadioBox, wxControl

wxRadioBox(wxWindow* parent, wxWindowID id, const wxString& label, const wxPoint& point = wxDefaultPosition, const wxSize& size = wxDefaultSize, int n = 0, const wxString choices[] = NULL, int majorDimension = 0, long style = wxRA_SPECIFY_COLS, const wxValidator& validator = wxDefaultValidator, const wxString& name = "radioBox")
~wxRadioBox()
bool Create(wxWindow* parent, wxWindowID id, const wxString& label, const wxPoint& point = wxDefaultPosition, const wxSize& size = wxDefaultSize, int n = 0, const wxString choices[] = NULL, int majorDimension = 0, long style = wxRA_SPECIFY_COLS, const wxValidator& validator = wxDefaultValidator, const wxString& name = "radioBox")
void Enable(const bool enable)
%rename EnableItem void Enable(int n, const bool enable)
int FindString(const wxString& string) const
// Error: Too few parameters in call
// wxString GetLabel() const
// FIXME: 2.3.2
// wxString GetLabel(int item) const;

// FIXME: 2.3.2
// %rename GetItemLabel wxString GetLabel(int n) const
int GetSelection() const
wxString GetStringSelection() const
// FIXME: 2.3.2
// int Number() const
// Error: Could not find a match
// void SetLabel(const wxString& label)
// FIXME: 2.3.2
// %rename SetItemLabel void SetLabel(int n, const wxString& label)

void SetSelection(int n)
void SetStringSelection(const wxString& string)
void Show(const bool show)
%rename ShowItem void Show(int item, const bool show)
wxString GetString(int n) const


///////////////////////////////////////////////////////////////////////////////
// wxRadioButton

%class wxRadioButton, wxControl

wxRadioButton(wxWindow* parent, wxWindowID id, const wxString& label, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = "radioButton")
~wxRadioButton()
bool Create(wxWindow* parent, wxWindowID id, const wxString& label, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = "radioButton")
bool GetValue() const
void SetValue(const bool value)


///////////////////////////////////////////////////////////////////////////////
// wxSlider

%class wxSlider, wxControl

wxSlider(wxWindow* parent, wxWindowID id, int value , int minValue, int maxValue, const wxPoint& point = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxSL_HORIZONTAL, const wxValidator& validator = wxDefaultValidator, const wxString& name = "slider")
~wxSlider()
void ClearSel()
void ClearTicks()
bool Create(wxWindow* parent, wxWindowID id, int value , int minValue, int maxValue, const wxPoint& point = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxSL_HORIZONTAL, const wxValidator& validator = wxDefaultValidator, const wxString& name = "slider")
int GetLineSize() const
int GetMax() const
int GetMin() const
int GetPageSize() const
int GetSelEnd() const
int GetSelStart() const
int GetThumbLength() const
int GetTickFreq() const
int GetValue() const
void SetRange(int minValue, int maxValue)
void SetTickFreq(int n, int pos)
void SetLineSize(int lineSize)
void SetPageSize(int pageSize)
void SetSelection(int startPos, int endPos)
void SetThumbLength(int len)
void SetTick(int tickPos)
void SetValue(int value)

///////////////////////////////////////////////////////////////////////////////
// wxToolBar

%class wxToolBarBase, wxControl
%include "wx/tbarbase.h"


///////////////////////////////////////////////////////////////////////////////
// wxToolBar

%class wxToolBar, wxToolBarBase
%include "wx/toolbar.h"

wxToolBar(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTB_HORIZONTAL | wxNO_BORDER, const wxString& name = wxPanelNameStr)
~wxToolBar()
bool AddControl(wxControl* control)
void AddSeparator()
// Fix: Undefined symbol 'wxToolBarTool'
// wxToolBarTool* AddTool(int toolId, const wxBitmap& bitmap1, const wxString& shortHelpString = "", const wxString& longHelpString = "")
bool DeleteTool(int toolId)
bool DeleteToolByPos(size_t pos)
void EnableTool(int toolId, const bool enable)
// Fix: Undefined symbol 'wxToolBarTool'
// wxToolBarTool* FindToolForPosition(const float x, const float y) const
wxSize GetToolSize()
wxSize GetToolBitmapSize()
// Error: 'GetMargins' is not a member of 'wxToolBar'
// wxSize GetMargins() const
wxObject* GetToolClientData(int toolId) const
bool GetToolEnabled(int toolId) const
wxString GetToolLongHelp(int toolId) const
int GetToolPacking() const
int GetToolSeparation() const
wxString GetToolShortHelp(int toolId) const
bool GetToolState(int toolId) const
// Fix: Undefined symbol 'wxToolBarTool'
// wxToolBarTool * InsertControl(size_t pos, wxControl *control)
// Fix: Undefined symbol 'wxToolBarTool'
// wxToolBarTool * InsertSeparator(size_t pos)
// Fix: Undefined symbol 'wxToolBarTool'
// wxToolBarTool * InsertTool(size_t pos, int toolId, const wxBitmap& bitmap1, const wxBitmap& bitmap2 = wxNullBitmap, bool isToggle = FALSE, wxObject* clientData = NULL, const wxString& shortHelpString = "", const wxString& longHelpString = "")
// bool OnLeftClick(int toolId, bool toggleDown)
// void OnMouseEnter(int toolId)
// void OnRightClick(int toolId, float x, float y)
bool Realize()
// Fix: Undefined symbol 'wxToolBarTool'
// wxToolBarTool * RemoveTool(int id)
// FIX: Missing in GTK, perhaps SetMargins (int, int)
win: void SetMargins(const wxSize& size)
void SetToolBitmapSize(const wxSize& size)
// Error: (fix) was GetToolClientData, still broken
// void SetToolClientData(wxObject* clientData)
void SetToolLongHelp(int toolId, const wxString& helpString)
void SetToolPacking(int packing)
void SetToolShortHelp(int toolId, const wxString& helpString)
void SetToolSeparation(int separation)
void ToggleTool(int toolId, const bool toggle)


///////////////////////////////////////////////////////////////////////////////
// wxNotebook

    
%class wxNotebook, wxControl
%include "wx/notebook.h"

// Error: missing default size
wxNotebook(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = "notebook")
~wxNotebook()
bool AddPage(wxNotebookPage* page, const wxString& text, bool select = FALSE, int imageId = -1)
void AdvanceSelection(bool forward = TRUE)
// Error: missing default size
bool Create(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = "notebook")
bool DeleteAllPages()
bool DeletePage(int page)
wxImageList* GetImageList() const
wxNotebookPage* GetPage(int page)
int GetPageCount() const
int GetPageImage(int nPage) const
wxString GetPageText(int nPage) const
int GetRowCount() const
int GetSelection() const
bool InsertPage(int index, wxNotebookPage* page, const wxString& text, bool select = FALSE, int imageId = -1)
// void OnSelChange(wxNotebookEvent& event)
bool RemovePage(int page)
void SetImageList(wxImageList* imageList)
void SetPadding(const wxSize& padding)
void SetPageSize(const wxSize& size)
bool SetPageImage(int page, int image)
bool SetPageText(int page, const wxString& text)
int SetSelection(int page)

///////////////////////////////////////////////////////////////////////////////
// wxPlotWindow

// It doesn't look like this can be easily wrapped, since
// the class wxPlotCurve would have to be derived in order
// to make it work.

%skip
%class wxPlotWindow, wxScrolledWindow

wxPlotWindow(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, int flags = wxPLOT_DEFAULT)
~wxPlotWindow()
void Add(wxPlotCurve* curve)
size_t GetCount()
wxPlotCurve* GetAt(size_t n)
void SetCurrent(wxPlotCurve* current)
wxPlotCurve* GetCurrent()
void Delete(wxPlotCurve* curve)
void Move(wxPlotCurve* curve, int pixels_up)
void Enlarge(wxPlotCurve* curve, double factor)
void SetUnitsPerValue(double upv)
double GetUnitsPerValue()
void SetZoom(double zoom)
double GetZoom()
void RedrawEverything()
void RedrawXAxis()
void RedrawYAxis()
void SetScrollOnThumbRelease(bool onrelease = TRUE)
void SetEnlargeAroundWindowCentre(bool aroundwindow = TRUE)

///////////////////////////////////////////////////////////////////////////////
// wxSashWindow

%class wxSashWindow, wxWindow
%include "wx/sashwin.h"

// Error: wxSashWindow instead of wxWindow
// wxSashWindow(wxSashWindow* parent, wxSashWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxCLIP_CHILDREN | wxSW_3D, const wxString& name = "sashWindow")
wxSashWindow(wxWindow *parent, wxWindowID id = -1, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxSW_3D|wxCLIP_CHILDREN, const wxString& name = "sashWindow")
~wxSashWindow()
bool GetSashVisible(wxSashEdgePosition edge) const
int GetMaximumSizeX() const
int GetMaximumSizeY() const
int GetMinimumSizeX()
// Error: Extra parameter in call
// int GetMinimumSizeY(int min) const
int GetMinimumSizeY() const
bool HasBorder(wxSashEdgePosition edge) const
void SetMaximumSizeX(int min)
void SetMaximumSizeY(int min)
void SetMinimumSizeX(int min)
void SetMinimumSizeY(int min)
void SetSashVisible(wxSashEdgePosition edge, bool visible)
void SetSashBorder(wxSashEdgePosition edge, bool hasBorder)


///////////////////////////////////////////////////////////////////////////////
// wxSashLayoutWindow

    
%class wxSashLayoutWindow, wxSashWindow
%include "wx/laywin.h"

// Error: wxSashLayoutWindow instead of wxWindow
// wxSashLayoutWindow(wxSashLayoutWindow* parent, wxSashLayoutWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxCLIP_CHILDREN | wxSW_3D, const wxString& name = "layoutWindow")
wxSashLayoutWindow(wxWindow *parent, wxWindowID id = -1, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxSW_3D|wxCLIP_CHILDREN, const wxString& name = "layoutWindow")
~wxSashLayoutWindow()
wxLayoutAlignment GetAlignment() const
wxLayoutOrientation GetOrientation() const
// void OnCalculateLayout(wxCalculateLayoutEvent& event)
// void OnQueryLayoutInfo(wxQueryLayoutInfoEvent& event)
void SetAlignment(wxLayoutAlignment alignment)
void SetDefaultSize(const wxSize& size)
void SetOrientation(wxLayoutOrientation orientation)


///////////////////////////////////////////////////////////////////////////////
// wxWizardPage


// Fix: class must have virtual functions defined before using
// %class wxWizardPage, wxPanel

// wxWizardPage(wxWizard* parent, const wxBitmap& bitmap = wxNullBitmap)
// wxWizardPage* GetPrev() const
// wxWizardPage* GetNext() const
// wxBitmap GetBitmap() const


///////////////////////////////////////////////////////////////////////////////
// wxWizardPageSimple

// Can't use until wxWizardPage is fixed
// %class wxWizardPageSimple, wxWizardPage

// wxWizardPageSimple(wxWizard* parent = NULL, wxWizardPage* prev = NULL, wxWizardPage* next = NULL)
// void SetPrev(wxWizardPage* prev)
// void SetNext(wxWizardPage* next)
// static void Chain(wxWizardPageSimple* first, wxWizardPageSimple* second)


///////////////////////////////////////////////////////////////////////////////
// COMMON DIALOGS
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// wxColourDialog

%class %alias wxColorDialog wxColourDialog, wxDialog
%include "wx/colordlg.h"

wxColourDialog(wxWindow* parent, wxColourData* data = NULL)
~wxColourDialog()
bool Create(wxWindow* parent, wxColourData* data = NULL)
%alias GetColorData wxColourData& GetColourData()
int ShowModal()


///////////////////////////////////////////////////////////////////////////////
// wxFileDialog


%class wxFileDialog, wxDialog
%include "wx/filedlg.h"

wxFileDialog(wxWindow* parent, const wxString& message = "Choose a file", const wxString& defaultDir = "", const wxString& defaultFile = "", const wxString& wildcard = "*.*", long style = 0, const wxPoint& pos = wxDefaultPosition)
// constants for style:
// wxOPEN  This is an open dialog.  
// wxSAVE  This is a save dialog.  
// wxHIDE_READONLY  Hide read-only files.  
// wxOVERWRITE_PROMPT  Prompt for a conformation if a file will be overridden.  
// wxMULTIPLE  For open dialog only: allows selecting multiple files  

~wxFileDialog()
wxString GetDirectory() const
wxString GetFilename() const
// Uses arrays...
// void GetFilenames(wxArrayString& filenames) const
int GetFilterIndex() const
wxString GetMessage() const
wxString GetPath() const
// Uses arrays...
// void GetPaths(wxArrayString& paths) const
long GetStyle() const
wxString GetWildcard() const
void SetDirectory(const wxString& directory)
void SetFilename(const wxString& setfilename)
// Windows only
// void SetFilterIndex(int filterIndex)
void SetMessage(const wxString& message)
void SetPath(const wxString& path)
void SetStyle(long style)
void SetWildcard(const wxString& wildCard)
// Example: "BMP files (*.bmp)|*.bmp|GIF files (*.gif)|*.gif"
int ShowModal()
// returning wxID_OK if the user pressed OK, and wxID_CANCEL otherwise.


///////////////////////////////////////////////////////////////////////////////
// wxDirDialog

%class wxDirDialog, wxDialog

    
wxDirDialog(wxWindow* parent, const wxString& message = "Choose a directory", const wxString& defaultPath = "", long style = 0, const wxPoint& pos = wxDefaultPosition)
~wxDirDialog()
wxString GetPath() const
wxString GetMessage() const
long GetStyle() const
void SetMessage(const wxString& message)
void SetPath(const wxString& path)
void SetStyle(long style)
int ShowModal()


///////////////////////////////////////////////////////////////////////////////
// wxMultipleChoiceDialog
//
// NOTE: this class is not yet implemented.

// %class wxMultipleChoiceDialog, wxDialog


///////////////////////////////////////////////////////////////////////////////
// wxSingleChoiceDialog

%class wxSingleChoiceDialog, wxDialog

// Error: can't handle ** yet
// wxSingleChoiceDialog(wxWindow* parent, const wxString& message, const wxString& caption, int n, const wxString* choices, void** clientData = NULL, long style = wxOK | wxCANCEL | wxCENTRE, const wxPoint& pos = wxDefaultPosition)
// For Python the two parametes n and choices are collapsed into a single 
// parameter choices which is expected to be a Python list of strings.
~wxSingleChoiceDialog()
int GetSelection() const
char* GetSelectionClientData() const
wxString GetStringSelection() const
void SetSelection(int selection) const
int ShowModal()


///////////////////////////////////////////////////////////////////////////////
// wxTextEntryDialog

%class wxTextEntryDialog, wxDialog

wxTextEntryDialog(wxWindow* parent, const wxString& message, const wxString& caption = "Please enter text", const wxString& defaultValue = "", long style = wxOK | wxCANCEL | wxCENTRE, const wxPoint& pos = wxDefaultPosition)
~wxTextEntryDialog()
wxString GetValue() const
void SetValue(const wxString& value)
int ShowModal()


///////////////////////////////////////////////////////////////////////////////
// wxFontDialog

%class wxFontDialog, wxDialog
%include "wx/fontdlg.h"

wxFontDialog(wxWindow* parent, wxFontData* data = NULL)
~wxFontDialog()
wxFontData& GetFontData()
int ShowModal()


///////////////////////////////////////////////////////////////////////////////
// wxPageSetupDialog

%class wxPageSetupDialog, wxDialog
%include "wx/printdlg.h"

wxPageSetupDialog(wxWindow* parent, wxPageSetupDialogData* data = NULL)
~wxPageSetupDialog()
wxPageSetupDialogData& GetPageSetupData()
int ShowModal()


///////////////////////////////////////////////////////////////////////////////
// wxPrintDialog

%class wxPrintDialog, wxDialog

wxPrintDialog(wxWindow* parent, wxPrintDialogData* data = NULL)
~wxPrintDialog()
wxPrintDialogData& GetPrintDialogData()
wxDC* GetPrintDC()
int ShowModal()


///////////////////////////////////////////////////////////////////////////////
// wxMessageDialog

%class wxMessageDialog, wxDialog

wxMessageDialog(wxWindow* parent, const wxString& message, const wxString& caption = "Message box", long style = wxOK | wxCANCEL | wxCENTRE, const wxPoint& pos = wxDefaultPosition)
~wxMessageDialog()
int ShowModal()


///////////////////////////////////////////////////////////////////////////////
// MENUS
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// wxMenu

%class wxMenu, wxEvtHandler
%include "wx/menu.h"

wxMenu(const wxString& title = "", long style = 0)
~wxMenu()
void Append(int id, const wxString& item, const wxString& helpString = "", const bool checkable = FALSE)
%rename AppendMenu void Append(int id, const wxString& item, wxMenu *subMenu, const wxString& helpString = "")
%rename AppendItem void Append(wxMenuItem* menuItem)
void AppendSeparator()
void Break()
void Check(int id, const bool check)
void Delete(int id)
%rename DeleteItem void Delete(wxMenuItem *item)
void Destroy(int id)
%rename DestroyMenuItem void Destroy(wxMenuItem *item)
void Enable(int id, const bool enable)
int FindItem(const wxString& itemString) const
// Error: can't handle ** yet
// %rename FindItemById wxMenuItem * FindItem(int id, wxMenu **menu = NULL) const
wxString GetHelpString(int id) const
wxString GetLabel(int id) const
size_t GetMenuItemCount() const
wxMenuItemList& GetMenuItems() const
wxString GetTitle() const
bool Insert(size_t pos, wxMenuItem *item)
bool IsChecked(int id) const
bool IsEnabled(int id) const
%rename RemoveById wxMenuItem * Remove(int id)
wxMenuItem * Remove(wxMenuItem *item)
void SetHelpString(int id, const wxString& helpString)
void SetLabel(int id, const wxString& label)
void SetTitle(const wxString& title)
void UpdateUI(wxEvtHandler* source = NULL) const


///////////////////////////////////////////////////////////////////////////////
// wxMenuBar

%class wxMenuBar, wxEvtHandler

// Error: include void in declaration
wxMenuBar(long style = 0)
// void wxMenuBar(int n, wxMenu* menus[], const wxString titles[])
~wxMenuBar()
bool Append(wxMenu *menu, const wxString& title)
void Check(int id, const bool check)
void Enable(int id, const bool enable)
void EnableTop(int pos, const bool enable)
int FindMenu(const wxString& title) const
int FindMenuItem(const wxString& menuString, const wxString& itemString) const
// Error: can't handle ** yet
// wxMenuItem * FindItem(int id, wxMenu **menu = NULL) const
wxString GetHelpString(int id) const
wxString GetLabel(int id) const
wxString GetLabelTop(int pos) const
wxMenu* GetMenu(int menuIndex) const
int GetMenuCount() const
bool Insert(size_t pos, wxMenu *menu, const wxString& title)
bool IsChecked(int id) const
bool IsEnabled(int id) const
void Refresh()
wxMenu * Remove(size_t pos)
wxMenu * Replace(size_t pos, wxMenu *menu, const wxString& title)
void SetHelpString(int id, const wxString& helpString)
void SetLabel(int id, const wxString& label)
void SetLabelTop(int pos, const wxString& label)


///////////////////////////////////////////////////////////////////////////////
// wxMenuItem

%class wxMenuItem, wxObject
%include "wx/menuitem.h"

// Error: constant ID_SEPARATOR instead of wxID_SEPARATOR, wxEmptyString instead of ""
// wxMenuItem(wxMenu* parentMenu = NULL, int id = ID_SEPARATOR, const wxString& text = "", const wxString& helpString = "", bool checkable = FALSE, wxMenu* subMenu = NULL, )
wxMenuItem(wxMenu *parentMenu = NULL, int id = wxID_SEPARATOR, const wxString& text = wxEmptyString, const wxString& help = wxEmptyString, bool isCheckable = FALSE, wxMenu *subMenu = NULL)
~wxMenuItem()
void Check(bool check)
// Error: 'DeleteSubMenu' is not a member of 'wxMenuItem'
// void DeleteSubMenu()
void Enable(bool enable)
// FIX: Missing in GTK
win: %alias GetBackgroundColor wxColour& GetBackgroundColour() const
// Fix: Cannot convert 'const wxBitmap *' to 'wxBitmap *'
// wxBitmap& GetBitmap(bool checked = TRUE) const
// FIX: Missing in GTK
win: wxFont& GetFont() const
wxString GetHelp() const
int GetId() const
wxString GetLabel() const
static wxString GetLabelFromText(const wxString& text)
// FIX: Missing in GTK
win: int GetMarginWidth() const
// Fix: Member is ambiguous: 'wxMenuItemBase::GetName' and 'wxOwnerDrawn::GetName'
// wxString GetName() const
wxString GetText() const
wxMenu* GetSubMenu() const
// FIX: Missing in GTK
win: %alias GetTextColor wxColour& GetTextColour() const
bool IsCheckable() const
bool IsChecked() const
bool IsEnabled() const
bool IsSeparator() const
// FIX: Missing in GTK
win: %alias SetBackgroundColor void SetBackgroundColour(const wxColour& colour) const
win: void SetBitmaps(const wxBitmap& checked, const wxBitmap& unchecked = wxNullBitmap) const
win: void SetFont(const wxFont& font) const
void SetHelp(const wxString& helpString) const
win: void SetMarginWidth(int width) const
// Fix: Member is ambiguous: 'wxMenuItemBase::SetName' and 'wxOwnerDrawn::SetName'
// void SetName(const wxString& text) const
// FIX: Missing in GTK
win: %alias SetTextColor void SetTextColour(const wxColour& colour) const

///////////////////////////////////////////////////////////////////////////////
// EVENTS


///////////////////////////////////////////////////////////////////////////////
// wxEvent

%class wxEvent, wxObject
%include "wx/event.h"

// FIXME: 2.3.2
// wxEvent(int id = 0)
char* m_eventHandle
wxObject* m_eventObject
WXTYPE m_eventType
int m_id
bool m_skipped
long m_timeStamp
// Error: 'GetEventClass' is not a member of 'wxEvent'
// WXTYPE GetEventClass()
wxObject* GetEventObject()
WXTYPE GetEventType()
int GetId()
// Error: 'GetObjectType' is not a member of 'wxEvent'
// WXTYPE GetObjectType()
bool GetSkipped()
long GetTimestamp()
void SetEventObject(wxObject* object)
void SetEventType(WXTYPE typ)
void SetId(int id)
void SetTimestamp(long timeStamp)
void Skip(bool skip = TRUE)

///////////////////////////////////////////////////////////////////////////////
// wxTimerEvent

%class wxTimerEvent, wxObject
%include "wx/timer.h"

int GetInterval() const

///////////////////////////////////////////////////////////////////////////////
// wxCommandEvent

%class wxCommandEvent, wxEvent
%include "wx/event.h"

void* m_clientData
int m_commandInt
char* m_commandString
long m_extraLong
wxCommandEvent(WXTYPE commandEventType = 0, int id = 0)
// Error: 'Checked' is not a member of 'wxCommandEvent'
// bool Checked() const
void* GetClientData()
long GetExtraLong()
int GetInt()
int GetSelection()
// Error: Cannot convert 'wxString' to 'char *'
// char* GetString()
wxString GetString()
bool IsChecked() const
bool IsSelection()
void SetClientData(void* clientData)
void SetExtraLong(int extraLong)
void SetInt(int intCommand)
void SetString(char* string)

///////////////////////////////////////////////////////////////////////////////
// wxNotifyEvent

%class wxNotifyEvent, wxCommandEvent
%include "wx/event.h"

wxNotifyEvent(wxEventType eventType = wxEVT_NULL, int id = 0)
// Error: Extra parameter in call to wxNotifyEvent::Allow()
// void Allow(bool allow = TRUE)
bool IsAllowed() const
void Veto()


///////////////////////////////////////////////////////////////////////////////
// wxActivateEvent

%class wxActivateEvent, wxEvent
%include "wx/event.h"

wxActivateEvent(WXTYPE eventType = 0, bool active = TRUE, int id = 0)
bool m_active
bool GetActive() const


///////////////////////////////////////////////////////////////////////////////
// wxCalendarEvent

%class wxCalendarEvent, wxEvent
%include "wx/event.h"

wxCalendarEvent(wxCalendarCtrl *cal, wxEventType type)
const wxDateTime& GetDate() const
wxDateTime::WeekDay GetWeekDay() const

///////////////////////////////////////////////////////////////////////////////
// wxCalculateLayoutEvent

%class wxCalculateLayoutEvent, wxEvent
%include "wx/laywin.h"

wxCalculateLayoutEvent(wxWindowID id = 0)
int GetFlags() const
wxRect GetRect() const
void SetFlags(int flags)
void SetRect(const wxRect& rect)


///////////////////////////////////////////////////////////////////////////////
// wxCloseEvent

%class wxCloseEvent, wxEvent
%include "wx/event.h"

wxCloseEvent(WXTYPE commandEventType = 0, int id = 0)
bool CanVeto()
bool GetLoggingOff() const
// Error: 'GetSessionEnding' is not a member of 'wxCloseEvent'
// bool GetSessionEnding() const
// Error: 'GetForce' is not a member of 'wxCloseEvent'
// bool GetForce() const
void SetCanVeto(bool canVeto)
// Error: 'SetForce' is not a member of 'wxCloseEvent'
// void SetForce(bool force) const
void SetLoggingOff(bool loggingOff) const
void Veto(bool veto = TRUE)


///////////////////////////////////////////////////////////////////////////////
// wxDialUpEvent

%class wxDialUpEvent, wxCommandEvent
%include "wx/dialup.h"

wxDialUpEvent(bool isConnected, bool isOwnEvent)
bool IsConnectedEvent() const
bool IsOwnEvent() const


///////////////////////////////////////////////////////////////////////////////
// wxDropFilesEvent

%class wxDropFilesEvent, wxEvent
%include "wx/event.h"

// Error: no match to arglist
// wxDropFilesEvent(WXTYPE id = 0, int noFiles = 0, wxString* files = NULL)
// wxDropFilesEvent(wxEventType type = wxEVT_NULL, int noFiles = 0, wxString *files = (wxString *) NULL)
// wxDropFilesEvent(wxEventType type = wxEVT_NULL, int noFiles = 0, wxString *files = NULL)

wxString* m_files
int m_noFiles
wxPoint m_pos
wxString* GetFiles() const
int GetNumberOfFiles() const
wxPoint GetPosition() const


///////////////////////////////////////////////////////////////////////////////
// wxEraseEvent

%class wxEraseEvent, wxEvent
%include "wx/event.h"

wxEraseEvent(int id = 0, wxDC* dc = NULL)
wxDC* m_dc
wxDC* GetDC() const


///////////////////////////////////////////////////////////////////////////////
// wxFocusEvent

%class wxFocusEvent, wxEvent
%include "wx/event.h"

wxFocusEvent(WXTYPE eventType = 0, int id = 0)


///////////////////////////////////////////////////////////////////////////////
// wxKeyEvent

%class wxKeyEvent, wxEvent
%include "wx/event.h"

bool m_altDown
bool m_controlDown
long m_keyCode
bool m_metaDown
bool m_shiftDown
int m_x
int m_y
wxKeyEvent(WXTYPE keyEventType)
bool AltDown() const
bool ControlDown() const
int GetKeyCode() const
long GetX() 
long GetY() const
bool MetaDown() const

// need alias...
wxPoint GetPosition() const
// void GetPosition(long *x, long *y) 
%{
    void wxKeyEvent_GetPositionX()
    {
        long x, y;
        ((wxKeyEvent *)wMe)->GetPosition(&x, &y);
        wPushNumber( (wNumber)x );
    }

    void wxKeyEvent_GetPositionY()
    {
        long x, y;
        ((wxKeyEvent *)wMe)->GetPosition(&x, &y);
        wPushNumber( (wNumber)y );
    }
%}
%method GetPositionX    wxKeyEvent_GetPositionX()
%method GetPositionY    wxKeyEvent_GetPositionY()

bool HasModifiers() const
bool ShiftDown() const


///////////////////////////////////////////////////////////////////////////////
// wxIdleEvent

%class wxIdleEvent, wxEvent
%include "wx/event.h"

wxIdleEvent()
void RequestMore(bool needMore = TRUE)
bool MoreRequested() const


///////////////////////////////////////////////////////////////////////////////
// wxInitDialogEvent

%class wxInitDialogEvent, wxEvent
%include "wx/event.h"

wxInitDialogEvent(int id = 0)


///////////////////////////////////////////////////////////////////////////////
// wxJoystickEvent

%class wxJoystickEvent, wxEvent
%include "wx/event.h"

wxJoystickEvent(WXTYPE eventType = 0, int state = 0, int joystick = wxJOYSTICK1, int change = 0)
bool ButtonDown(int button = wxJOY_BUTTON_ANY) const
bool ButtonIsDown(int button = wxJOY_BUTTON_ANY) const
bool ButtonUp(int button = wxJOY_BUTTON_ANY) const
int GetButtonChange() const
int GetButtonState() const
int GetJoystick() const
wxPoint GetPosition() const
int GetZPosition() const
bool IsButton() const
bool IsMove() const
bool IsZMove() const


///////////////////////////////////////////////////////////////////////////////
// wxListEvent

%class wxListEvent, wxNotifyEvent
%include "wx/listctrl.h"

wxListEvent(WXTYPE commandType = 0, int id = 0)
int GetCode() const
long GetIndex() const
// FIXME: 2.3.2
// long GetOldIndex() const
int GetColumn() const
// FIXME: 2.3.2
// bool Cancelled() const
wxPoint GetPoint() const
const wxString& GetLabel() const
// Error? Appears twice
// const wxString& GetText() const
const wxString& GetText() const
int GetImage() const
long GetData() const
long GetMask() const
const wxListItem& GetItem() const


///////////////////////////////////////////////////////////////////////////////
// wxMenuEvent

%class wxMenuEvent, wxEvent
%include "wx/event.h"

// Error: wrong arglist
// wxMenuEvent(WXTYPE id = 0, int id = 0, wxDC* dc = NULL)
wxMenuEvent(wxEventType type = wxEVT_NULL, int id = 0)
int m_menuId
int GetMenuId() const


///////////////////////////////////////////////////////////////////////////////
// wxMouseEvent

%class wxMouseEvent, wxEvent
%include "wx/event.h"

bool m_altDown
bool m_controlDown
bool m_leftDown
bool m_middleDown
bool m_rightDown
bool m_leftDown
bool m_metaDown
bool m_shiftDown
long m_x
long m_y
bool AltDown()
bool Button(int button)
bool ButtonDClick(int but = -1)
bool ButtonDown(int but = -1)
bool ButtonUp(int but = -1)
bool ControlDown()
bool Dragging()
bool Entering()

// alias...
wxPoint GetPosition() const
// void GetPosition(wxCoord* x, wxCoord* y) const
// void GetPosition(long* x, long* y) const
%{
    void wxMouseEvent_GetPositionX()
    {
        long x, y;
        ((wxMouseEvent *)wMe)->GetPosition(&x, &y);
        wPushNumber( (wNumber)x );
    }

    void wxMouseEvent_GetPositionY()
    {
        long x, y;
        ((wxMouseEvent *)wMe)->GetPosition(&x, &y);
        wPushNumber( (wNumber)y );
    }


%}
%method GetPositionX    wxMouseEvent_GetPositionX()
%method GetPositionY    wxMouseEvent_GetPositionY()

wxPoint GetLogicalPosition(const wxDC& dc) const
long GetX() const
long GetY()
bool IsButton() const
bool Leaving() const
bool LeftDClick() const
bool LeftDown() const
bool LeftIsDown() const
bool LeftUp() const
bool MetaDown() const
bool MiddleDClick() const
bool MiddleDown() const
bool MiddleIsDown() const
bool MiddleUp() const
bool Moving() const
bool RightDClick() const
bool RightDown() const
bool RightIsDown() const
bool RightUp() const
bool ShiftDown() const


///////////////////////////////////////////////////////////////////////////////
// wxMoveEvent

%class wxMoveEvent, wxEvent
%include "wx/event.h"

wxMoveEvent(const wxPoint& pt, int id = 0)
wxPoint GetPosition() const


///////////////////////////////////////////////////////////////////////////////
// wxNotebookEvent

%class wxNotebookEvent, wxNotifyEvent
%include "wx/notebook.h"

wxNotebookEvent(wxEventType eventType = wxEVT_NULL, int id = 0, int sel = -1, int oldSel = -1)
int GetOldSelection() const
int GetSelection() const
void SetOldSelection(int page)
void SetSelection(int page)


///////////////////////////////////////////////////////////////////////////////
// wxPaintEvent

%class wxPaintEvent, wxEvent
%include "wx/event.h"

wxPaintEvent(int id = 0)


///////////////////////////////////////////////////////////////////////////////
// wxProcessEvent

%class wxProcessEvent, wxEvent
%include "wx/process.h"

wxProcessEvent(int id = 0, int pid = 0)
int m_pid
int GetPid() const
// Error: not a member
// void SetPid(int pid)


///////////////////////////////////////////////////////////////////////////////
// wxQueryLayoutInfoEvent

%class wxQueryLayoutInfoEvent, wxEvent
%include "wx/event.h"

wxQueryLayoutInfoEvent(wxWindowID id = 0)
int GetFlags() const
// Redundant?
// wxLayoutOrientation GetOrientation() const
int GetOrientation()
int GetRequestedLength() const
wxSize GetSize() const
void SetAlignment(wxLayoutAlignment alignment)
void SetFlags(int flags)
void SetOrientation(wxLayoutOrientation orientation)
void SetRequestedLength(int length)
void SetSize(const wxSize& size)


///////////////////////////////////////////////////////////////////////////////
// wxScrollEvent

%class wxScrollEvent, wxCommandEvent
%include "wx/event.h"

wxScrollEvent(WXTYPE commandType = 0, int id = 0, int pos = 0, int orientation = 0)
int GetOrientation() const
int GetPosition() const



///////////////////////////////////////////////////////////////////////////////
// wxScrollWinEvent

%class wxScrollWinEvent, wxEvent
%include "wx/event.h"

// Error: Could not find a match for 'wxScrollWinEvent::wxScrollWinEvent(short,int,int,int)'
// wxScrollWinEvent(WXTYPE commandType = 0, int id = 0, int pos = 0, int orientation = 0)
int GetOrientation() const
int GetPosition() const



///////////////////////////////////////////////////////////////////////////////
// wxSizeEvent

%class wxSizeEvent, wxEvent
%include "wx/event.h"

wxSizeEvent(const wxSize& sz, int id = 0)
wxSize GetSize() const


///////////////////////////////////////////////////////////////////////////////
// wxSocketEvent

%class wxSocketEvent, wxEvent
%include "wx/socket.h"

wxSocketEvent(int id = 0)
void * GetClientData()
wxSocketBase * GetSocket() const
wxSocketNotify GetSocketEvent() const


///////////////////////////////////////////////////////////////////////////////
// wxSpinEvent

%class wxSpinEvent, wxNotifyEvent
%include "wx/spinbutt.h"
%include "wx/spinctrl.h"

wxSpinEvent(wxEventType commandType = wxEVT_NULL, int id = 0)
int GetPosition() const
void SetPosition(int pos)



///////////////////////////////////////////////////////////////////////////////
// wxSysColourChangedEvent

%class wxSysColourChangedEvent, wxEvent
%include "wx/event.h"

// Error: Constructor doesn't match
//wxSysColourChanged()
wxSysColourChangedEvent()



///////////////////////////////////////////////////////////////////////////////
// wxTabEvent

// FIX: Missing in GTK (Obsolete)
gtk: %skip
%class wxTabEvent, wxCommandEvent
%include "wx/event.h"

wxTabEvent(WXTYPE commandType = 0, int id = 0)



///////////////////////////////////////////////////////////////////////////////
// wxTreeEvent

%class wxTreeEvent, wxNotifyEvent
%include "wx/treectrl.h"

wxTreeEvent(WXTYPE commandType = 0, int id = 0)
wxTreeItemId GetItem() const
wxTreeItemId GetOldItem() const
wxPoint GetPoint() const
int GetCode() const
const wxString& GetLabel() const



///////////////////////////////////////////////////////////////////////////////
// wxUpdateUIEvent

%class wxUpdateUIEvent, wxEvent
%include "wx/event.h"

wxUpdateUIEvent(wxWindowID commandId = 0)
bool m_checked
bool m_checked
bool m_setChecked
bool m_setEnabled
bool m_setText
wxString m_text
void Check(bool check)
void Enable(bool enable)
bool GetChecked() const
bool GetEnabled() const
bool GetSetChecked() const
bool GetSetEnabled() const
bool GetSetText() const
wxString GetText() const
void SetText(const wxString& text)



///////////////////////////////////////////////////////////////////////////////
// wxWizardEvent

%class wxWizardEvent, wxNotifyEvent
%include "wx/wizard.h"

wxWizardEvent(wxEventType type = wxEVT_NULL, int id = -1, bool direction = TRUE)
bool GetDirection() const





///////////////////////////////////////////////////////////////////////////////
// Window Layout


///////////////////////////////////////////////////////////////////////////////
// wxSizer

%class wxSizer, wxObject

// Abstract, so can't create directly
// wxSizer()
~wxSizer()
// use aliases here...
%rename AddWindow void Add(wxWindow* window, int option = 0,int flag = 0, int border = 0, wxObject* userData = NULL)
%rename AddSizer void Add(wxSizer* sizer, int option = 0, int flag = 0, int border = 0, wxObject* userData = NULL)
void Add(int width, int height, int option = 0, int flag = 0, int border = 0, wxObject* userData = NULL)

wxSize CalcMin()
void Fit(wxWindow* window)
wxSize GetSize()
wxPoint GetPosition()
wxSize GetMinSize()
void Layout()

// use aliases here...
%rename PrependWindow void Prepend(wxWindow* window, int option = 0, int flag = 0, int border = 0, wxObject* userData = NULL)
%rename PrependSizer void Prepend(wxSizer* sizer, int option = 0, int flag = 0, int border = 0, wxObject* userData = NULL)
void Prepend(int width, int height, int option = 0, int flag = 0, int border= 0, wxObject* userData = NULL)
void RecalcSizes()

// use aliases here...
%rename RemoveWindow bool Remove(wxWindow* window)
%rename RemoveSizer bool Remove(wxSizer* sizer)
bool Remove(int nth)

void SetDimension(int x, int y, int width, int height)
// alias...
void SetMinSize(int width, int height)
// Fix: size is not a pointer. hrm...
// %rename SetMinSizeSize void SetMinSize(wxSize size)

// alias
%rename SetWindowMinSize void SetItemMinSize(wxWindow* window, int width, int height)
%rename SetSizerMinSize void SetItemMinSize(wxSizer* sizer, int width, int height)
void SetItemMinSize(int pos, int width, int height)

void SetSizeHints(wxWindow* window)

///////////////////////////////////////////////////////////////////////////////
// wxGridSizer

%class wxGridSizer, wxSizer

// alias...
wxGridSizer(int cols, int rows, int vgap, int hgap)
// wxGridSizer(int cols, int vgap = 0, int hgap = 0)

///////////////////////////////////////////////////////////////////////////////
// wxFlexGridSizer

%class wxFlexGridSizer, wxGridSizer

// alias...
wxFlexGridSizer(int rows, int cols, int vgap, int hgap)
// wxFlexGridSizer(int cols, int vgap = 0, int hgap = 0)

///////////////////////////////////////////////////////////////////////////////
// wxBoxSizer

%class wxBoxSizer, wxSizer

wxBoxSizer(int orient)
void RecalcSizes()
wxSize CalcMin()
int GetOrientation()

///////////////////////////////////////////////////////////////////////////////
// wxStaticBoxSizer

%class wxStaticBoxSizer, wxBoxSizer

wxStaticBoxSizer(wxStaticBox* box, int orient)
wxStaticBox* GetStaticBox()

///////////////////////////////////////////////////////////////////////////////
// wxNotebookSizer

%class wxNotebookSizer, wxSizer

wxNotebookSizer(wxNotebook* notebook)
wxNotebook* GetNotebook()


///////////////////////////////////////////////////////////////////////////////
// wxIndividualLayoutConstraint

%class wxIndividualLayoutConstraint, wxObject

// Fixed: should not have had 'void'
wxIndividualLayoutConstraint()
void Above(wxWindow *otherWin, int margin = 0)
void Absolute(int value)
void AsIs()
void Below(wxWindow *otherWin, int margin = 0)
void Unconstrained()
void LeftOf(wxWindow *otherWin, int margin = 0)
void PercentOf(wxWindow *otherWin, wxEdge edge, int per)
void RightOf(wxWindow *otherWin, int margin = 0)
void SameAs(wxWindow *otherWin, wxEdge edge, int margin = 0)
void Set(wxRelationship rel, wxWindow *otherWin, wxEdge otherEdge, int value = 0, int margin = 0)


///////////////////////////////////////////////////////////////////////////////
// wxLayoutConstraints

%class wxLayoutConstraints, wxObject
%include "wx/layout.h"

wxLayoutConstraints()
wxIndividualLayoutConstraint bottom
wxIndividualLayoutConstraint centreX
wxIndividualLayoutConstraint centreY
wxIndividualLayoutConstraint height
wxIndividualLayoutConstraint left
wxIndividualLayoutConstraint right
wxIndividualLayoutConstraint top
wxIndividualLayoutConstraint width


///////////////////////////////////////////////////////////////////////////////
// wxFont

%class wxFont, wxGDIObject
%include "wx/font.h"

wxFont(int pointSize, int family, int style, int weight, const bool underline = FALSE, const wxString& faceName = "", wxFontEncoding encoding = wxFONTENCODING_DEFAULT)
~wxFont()
static wxFontEncoding GetDefaultEncoding()
wxString GetFaceName() const
int GetFamily() const
// Fix: not found under wxGTK 2.3.1
// int GetFontId() const
int GetPointSize() const
int GetStyle() const
bool GetUnderlined() const
int GetWeight() const
static void SetDefaultEncoding(wxFontEncoding encoding)
void SetFaceName(const wxString& faceName)
void SetFamily(int family)
void SetPointSize(int pointSize)
void SetStyle(int style)
void SetUnderlined(const bool underlined)
void SetWeight(int weight)


///////////////////////////////////////////////////////////////////////////////
// wxTimer

%class wxTimer, wxObject
%include "wx/timer.h"

wxTimer(wxEvtHandler *owner, int id = -1)
~wxTimer()
bool IsOneShot() const
bool IsRunning() const
void Notify()
void SetOwner(wxEvtHandler *owner, int id = -1)
bool Start(int milliseconds = -1, bool oneShot=FALSE)
void Stop()
