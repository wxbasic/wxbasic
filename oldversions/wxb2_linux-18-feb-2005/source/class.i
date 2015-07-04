///////////////////////////////////////////////////////////////////////////////
// prototypes of wxWindows classes for wxBasic
// (c) 2004 David Cuny
//
// To Do:
//        note that wxString is not returned as a pointer...
//
// More fixes: these failed in wxGTK-2.3.2 when I added OpenGL support, oddly enough:
// wxIndividualLayoutConstraint::Above
// wxIndividualLayoutConstraint::Below
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

// String constants
%str wxALL_FILES_PATTERN
%str wxALL_FILES

// Put this stuff in order...
%num wxBIG_ENDIAN 
%num wxLITTLE_ENDIAN 
%num wxPDP_ENDIAN 
%num wxBYTE_ORDER 

%num wxED_CLIENT_MARGIN 
%num wxED_BUTTONS_BOTTOM 
%num wxED_BUTTONS_RIGHT 
%num wxED_STATIC_LINE 
%num wxEXT_DIALOG_STYLE 
%num wxTB_HORIZONTAL 
%num wxTB_VERTICAL 
%num wxTB_3DBUTTONS 
%num wxTB_FLAT 
%num wxTB_DOCKABLE 
%num wxMB_DOCKABLE 
%num wxMENU_TEAROFF 
%num wxCOLOURED 
%num wxFIXED_LENGTH 
%num wxLB_SORT 
%num wxLB_SINGLE 
%num wxLB_MULTIPLE 
%num wxLB_EXTENDED 
%num wxLB_OWNERDRAW 
%num wxLB_NEEDED_SB 
%num wxLB_ALWAYS_SB 
%num wxLB_HSCROLL 
%num wxPROCESS_ENTER 
%num wxPASSWORD 
%num wxCB_SIMPLE 
%num wxCB_SORT 
%num wxCB_READONLY 
%num wxCB_DROPDOWN 
%num wxRA_SPECIFY_COLS 
%num wxRA_SPECIFY_ROWS 
%num wxRA_HORIZONTAL 
%num wxRA_VERTICAL 
%num wxRB_GROUP 
%num wxGA_HORIZONTAL 
%num wxGA_VERTICAL 
%num wxGA_PROGRESSBAR 
%num wxGA_SMOOTH 
%num wxSL_HORIZONTAL 
%num wxSL_VERTICAL 
%num wxSL_NOTIFY_DRAG 
%num wxSL_AUTOTICKS 
%num wxSL_LABELS 
%num wxSL_LEFT 
%num wxSL_TOP 
%num wxSL_RIGHT 
%num wxSL_BOTTOM 
%num wxSL_BOTH 
%num wxSL_SELRANGE 
%num wxSB_HORIZONTAL 
%num wxSB_VERTICAL 
%num wxBU_AUTODRAW 
%num wxBU_NOAUTODRAW 
%num wxBU_LEFT 
%num wxBU_TOP 
%num wxBU_RIGHT 
%num wxBU_BOTTOM 
%num wxTR_HAS_BUTTONS 
%num wxTR_EDIT_LABELS 
%num wxTR_LINES_AT_ROOT 
%num wxTR_SINGLE 
%num wxTR_MULTIPLE 
%num wxTR_EXTENDED 
%num wxTR_HAS_VARIABLE_ROW_HEIGHT 
%num wxTR_NO_LINES 
%num wxTR_MAC_BUTTONS 
%num wxTR_ROW_LINES 
%num wxLC_VRULES 
%num wxLC_HRULES 
%num wxLC_ICON 
%num wxLC_SMALL_ICON 
%num wxLC_LIST 
%num wxLC_REPORT 
%num wxLC_ALIGN_TOP 
%num wxLC_ALIGN_LEFT 
%num wxLC_AUTOARRANGE 
%num wxLC_USER_TEXT 
%num wxLC_EDIT_LABELS 
%num wxLC_NO_HEADER 
%num wxLC_NO_SORT_HEADER 
%num wxLC_SINGLE_SEL 
%num wxLC_SORT_ASCENDING 
%num wxLC_SORT_DESCENDING 
%num wxLC_MASK_TYPE 
%num wxLC_MASK_ALIGN 
%num wxLC_MASK_SORT 
%num wxSP_HORIZONTAL 
%num wxSP_VERTICAL 
%num wxSP_ARROW_KEYS 
%num wxSP_WRAP 
%num wxSP_NOBORDER 
%num wxSP_NOSASH 
%num wxSP_BORDER 
%num wxSP_PERMIT_UNSPLIT 
%num wxSP_LIVE_UPDATE 
%num wxSP_3DSASH 
%num wxSP_3DBORDER 
%num wxSP_FULLSASH 
%num wxSP_3D 
%num wxTC_MULTILINE 
%num wxTC_RIGHTJUSTIFY 
%num wxTC_FIXEDWIDTH 
%num wxTC_OWNERDRAW 
%num wxNB_FIXEDWIDTH 
%num wxNB_LEFT 
%num wxNB_RIGHT 
%num wxNB_BOTTOM 
%num wxST_SIZEGRIP 
%num wxST_NO_AUTORESIZE 
%num wxLI_HORIZONTAL 
%num wxLI_VERTICAL 
%num wxPD_CAN_ABORT 
%num wxPD_APP_MODAL 
%num wxPD_AUTO_HIDE 
%num wxPD_ELAPSED_TIME 
%num wxPD_ESTIMATED_TIME 
%num wxPD_REMAINING_TIME 
%num wxHW_SCROLLBAR_NEVER 
%num wxHW_SCROLLBAR_AUTO 
%num wxCAL_SUNDAY_FIRST 
%num wxCAL_MONDAY_FIRST 
%num wxCAL_SHOW_HOLIDAYS 
%num wxCAL_NO_YEAR_CHANGE 
%num wxCAL_NO_MONTH_CHANGE 
%num wxFORWARD 
%num wxBACKWARD 
%num wxRESET 
%num wxHELP 
%num wxMORE 
%num wxSETUP 

// Standard menu events
%num wxID_SEPARATOR
%num wxID_LOWEST 
%num wxID_OPEN 
%num wxID_CLOSE 
%num wxID_NEW 
%num wxID_SAVE 
%num wxID_SAVEAS 
%num wxID_REVERT 
%num wxID_EXIT 
%num wxID_UNDO 
%num wxID_REDO 
%num wxID_HELP 
%num wxID_PRINT 
%num wxID_PRINT_SETUP 
%num wxID_PREVIEW 
%num wxID_ABOUT 
%num wxID_HELP_CONTENTS 
%num wxID_HELP_COMMANDS 
%num wxID_HELP_PROCEDURES 
%num wxID_HELP_CONTEXT 
%num wxID_CUT 
%num wxID_COPY 
%num wxID_PASTE 
%num wxID_CLEAR 
%num wxID_FIND 
%num wxID_DUPLICATE 
%num wxID_SELECTALL 
%num wxID_FILE1 
%num wxID_FILE2 
%num wxID_FILE3 
%num wxID_FILE4 
%num wxID_FILE5 
%num wxID_FILE6 
%num wxID_FILE7 
%num wxID_FILE8 
%num wxID_FILE9

// Standard responses
%num wxID_OK 
%num wxID_CANCEL 
%num wxID_APPLY 
%num wxID_YES 
%num wxID_NO 
%num wxID_STATIC 
%num wxID_FORWARD 
%num wxID_BACKWARD 
%num wxID_DEFAULT 
%num wxID_MORE 
%num wxID_SETUP 
%num wxID_RESET 
%num wxID_CONTEXT_HELP 
%num wxID_YESTOALL 
%num wxID_NOTOALL 
%num wxID_ABORT 
%num wxID_RETRY 
%num wxID_IGNORE 
%num wxID_FILEDLGG 
%num wxID_HIGHEST

%num wxSIZE_AUTO_WIDTH 
%num wxSIZE_AUTO_HEIGHT 
%num wxSIZE_AUTO 
%num wxSIZE_USE_EXISTING 
%num wxSIZE_ALLOW_MINUS_ONE 
%num wxSIZE_NO_ADJUSTMENTS 
%num wxFLOOD_SURFACE 
%num wxFLOOD_BORDER 
%num wxODDEVEN_RULE 
%num wxWINDING_RULE 
%num wxTOOL_TOP 
%num wxTOOL_BOTTOM 
%num wxTOOL_LEFT 
%num wxTOOL_RIGHT 
%num wxMM_TEXT 
%num wxMM_LOMETRIC 
%num wxMM_HIMETRIC 
%num wxMM_LOENGLISH 
%num wxMM_HIENGLISH 
%num wxMM_TWIPS 
%num wxMM_ISOTROPIC 
%num wxMM_ANISOTROPIC 
%num wxMM_POINTS 
%num wxMM_METRIC 
%num wxPORTRAIT 
%num wxLANDSCAPE 
%num wxPRINT_QUALITY_HIGH 
%num wxPRINT_QUALITY_MEDIUM 
%num wxPRINT_QUALITY_LOW 
%num wxPRINT_QUALITY_DRAFT 

// Command events
%num wxEVT_COMMAND_BUTTON_CLICKED
%num wxEVT_COMMAND_CHECKBOX_CLICKED 
%num wxEVT_COMMAND_CHOICE_SELECTED 
%num wxEVT_COMMAND_LISTBOX_SELECTED 
%num wxEVT_COMMAND_LISTBOX_DOUBLECLICKED 
%num wxEVT_COMMAND_CHECKLISTBOX_TOGGLED 
%num wxEVT_COMMAND_TEXT_UPDATED 
%num wxEVT_COMMAND_TEXT_ENTER 
%num wxEVT_COMMAND_MENU_SELECTED 
%num wxEVT_COMMAND_SLIDER_UPDATED 
%num wxEVT_COMMAND_RADIOBOX_SELECTED 
%num wxEVT_COMMAND_RADIOBUTTON_SELECTED 
%num wxEVT_COMMAND_SCROLLBAR_UPDATED 
%num wxEVT_COMMAND_VLBOX_SELECTED 
%num wxEVT_COMMAND_COMBOBOX_SELECTED 
%num wxEVT_COMMAND_TOOL_RCLICKED 
%num wxEVT_COMMAND_TOOL_ENTER 
%num wxEVT_COMMAND_SPINCTRL_UPDATED

// More events
%num wxEVT_SOCKET 
%num wxEVT_TIMER  
%num wxEVT_LEFT_DOWN 
%num wxEVT_LEFT_UP 
%num wxEVT_MIDDLE_DOWN 
%num wxEVT_MIDDLE_UP 
%num wxEVT_RIGHT_DOWN 
%num wxEVT_RIGHT_UP 
%num wxEVT_MOTION 
%num wxEVT_ENTER_WINDOW 
%num wxEVT_LEAVE_WINDOW 
%num wxEVT_LEFT_DCLICK 
%num wxEVT_MIDDLE_DCLICK 
%num wxEVT_RIGHT_DCLICK 
%num wxEVT_SET_FOCUS 
%num wxEVT_KILL_FOCUS 
%num wxEVT_MOUSEWHEEL 
%num wxEVT_NC_LEFT_DOWN 
%num wxEVT_NC_LEFT_UP 
%num wxEVT_NC_MIDDLE_DOWN 
%num wxEVT_NC_MIDDLE_UP 
%num wxEVT_NC_RIGHT_DOWN 
%num wxEVT_NC_RIGHT_UP 
%num wxEVT_NC_MOTION 
%num wxEVT_NC_ENTER_WINDOW 
%num wxEVT_NC_LEAVE_WINDOW 
%num wxEVT_NC_LEFT_DCLICK 
%num wxEVT_NC_MIDDLE_DCLICK 
%num wxEVT_NC_RIGHT_DCLICK 
%num wxEVT_CHAR 
%num wxEVT_CHAR_HOOK 
%num wxEVT_NAVIGATION_KEY 
%num wxEVT_KEY_DOWN 
%num wxEVT_KEY_UP 
%num wxEVT_SET_CURSOR 
%num wxEVT_SCROLL_TOP 
%num wxEVT_SCROLL_BOTTOM 
%num wxEVT_SCROLL_LINEUP 
%num wxEVT_SCROLL_LINEDOWN 
%num wxEVT_SCROLL_PAGEUP 
%num wxEVT_SCROLL_PAGEDOWN 
%num wxEVT_SCROLL_THUMBTRACK 
%num wxEVT_SCROLL_THUMBRELEASE 
%num wxEVT_SCROLLWIN_TOP 
%num wxEVT_SCROLLWIN_BOTTOM 
%num wxEVT_SCROLLWIN_LINEUP 
%num wxEVT_SCROLLWIN_LINEDOWN 
%num wxEVT_SCROLLWIN_PAGEUP 
%num wxEVT_SCROLLWIN_PAGEDOWN 
%num wxEVT_SCROLLWIN_THUMBTRACK 
%num wxEVT_SCROLLWIN_THUMBRELEASE 
%num wxEVT_SIZE 
%num wxEVT_MOVE 
%num wxEVT_CLOSE_WINDOW 
%num wxEVT_END_SESSION 
%num wxEVT_QUERY_END_SESSION 
%num wxEVT_ACTIVATE_APP 
%num wxEVT_POWER 
%num wxEVT_ACTIVATE 
%num wxEVT_CREATE 
%num wxEVT_DESTROY 
%num wxEVT_SHOW 
%num wxEVT_ICONIZE 
%num wxEVT_MAXIMIZE 
%num wxEVT_MOUSE_CAPTURE_CHANGED 
%num wxEVT_PAINT 
%num wxEVT_ERASE_BACKGROUND 
%num wxEVT_NC_PAINT 
%num wxEVT_PAINT_ICON 
%num wxEVT_MENU_HIGHLIGHT 
%num wxEVT_CONTEXT_MENU 
%num wxEVT_SYS_COLOUR_CHANGED 
%num wxEVT_SETTING_CHANGED 
%num wxEVT_QUERY_NEW_PALETTE 
%num wxEVT_PALETTE_CHANGED 
%num wxEVT_JOY_BUTTON_DOWN 
%num wxEVT_JOY_BUTTON_UP 
%num wxEVT_JOY_MOVE 
%num wxEVT_JOY_ZMOVE 
%num wxEVT_DROP_FILES 
%num wxEVT_DRAW_ITEM 
%num wxEVT_MEASURE_ITEM 
%num wxEVT_COMPARE_ITEM 
%num wxEVT_INIT_DIALOG 
%num wxEVT_IDLE 
%num wxEVT_UPDATE_UI 
%num wxEVT_COMMAND_LEFT_CLICK 
%num wxEVT_COMMAND_LEFT_DCLICK 
%num wxEVT_COMMAND_RIGHT_CLICK 
%num wxEVT_COMMAND_RIGHT_DCLICK 
%num wxEVT_COMMAND_SET_FOCUS 
%num wxEVT_COMMAND_KILL_FOCUS 
%num wxEVT_COMMAND_ENTER 
%num wxEVT_HELP 
%num wxEVT_DETAILED_HELP 
%num wxEVT_COMMAND_TOOL_CLICKED 
%num wxHF_TOOLBAR 
%num wxHF_FLAT_TOOLBAR 
%num wxHF_CONTENTS 
%num wxHF_INDEX 
%num wxHF_SEARCH 
%num wxHF_BOOKMARKS 
%num wxHF_OPEN_FILES 
%num wxHF_PRINT 
%num wxHF_MERGE_BOOKS 
%num wxHF_ICONS_BOOK 
%num wxHF_ICONS_FOLDER 
%num wxHF_ICONS_BOOK_CHAPTER
%num wxHF_DEFAULT_STYLE 

// keycodes
%num WXK_BACK
%num WXK_TAB
%num WXK_RETURN
%num WXK_ESCAPE
%num WXK_SPACE
%num WXK_DELETE
%num WXK_START
%num WXK_LBUTTON
%num WXK_RBUTTON
%num WXK_CANCEL
%num WXK_MBUTTON
%num WXK_CLEAR
%num WXK_SHIFT
%num WXK_ALT
%num WXK_CONTROL
%num WXK_MENU
%num WXK_PAUSE
%num WXK_CAPITAL
%num WXK_PRIOR
%num WXK_NEXT
%num WXK_END
%num WXK_HOME
%num WXK_LEFT
%num WXK_UP
%num WXK_RIGHT 
%num WXK_DOWN 
%num WXK_SELECT 
%num WXK_PRINT 
%num WXK_EXECUTE 
%num WXK_SNAPSHOT 
%num WXK_INSERT 
%num WXK_HELP 
%num WXK_NUMPAD0 
%num WXK_NUMPAD1 
%num WXK_NUMPAD2 
%num WXK_NUMPAD3 
%num WXK_NUMPAD4 
%num WXK_NUMPAD5 
%num WXK_NUMPAD6 
%num WXK_NUMPAD7 
%num WXK_NUMPAD8 
%num WXK_NUMPAD9 
%num WXK_MULTIPLY 
%num WXK_ADD 
%num WXK_SEPARATOR 
%num WXK_SUBTRACT 
%num WXK_DECIMAL 
%num WXK_DIVIDE 
%num WXK_F1 
%num WXK_F2 
%num WXK_F3 
%num WXK_F4 
%num WXK_F5 
%num WXK_F6 
%num WXK_F7 
%num WXK_F8 
%num WXK_F9 
%num WXK_F10 
%num WXK_F11 
%num WXK_F12 
%num WXK_F13 
%num WXK_F14 
%num WXK_F15 
%num WXK_F16 
%num WXK_F17 
%num WXK_F18 
%num WXK_F19 
%num WXK_F20 
%num WXK_F21 
%num WXK_F22 
%num WXK_F23 
%num WXK_F24 
%num WXK_NUMLOCK 
%num WXK_SCROLL 
%num WXK_PAGEUP 
%num WXK_PAGEDOWN 
%num WXK_NUMPAD_SPACE 
%num WXK_NUMPAD_TAB 
%num WXK_NUMPAD_ENTER 
%num WXK_NUMPAD_F1 
%num WXK_NUMPAD_F2 
%num WXK_NUMPAD_F3 
%num WXK_NUMPAD_F4 
%num WXK_NUMPAD_HOME 
%num WXK_NUMPAD_LEFT 
%num WXK_NUMPAD_UP 
%num WXK_NUMPAD_RIGHT 
%num WXK_NUMPAD_DOWN 
%num WXK_NUMPAD_PRIOR 
%num WXK_NUMPAD_PAGEUP 
%num WXK_NUMPAD_NEXT 
%num WXK_NUMPAD_PAGEDOWN 
%num WXK_NUMPAD_END 
%num WXK_NUMPAD_BEGIN 
%num WXK_NUMPAD_INSERT 
%num WXK_NUMPAD_DELETE 
%num WXK_NUMPAD_EQUAL 
%num WXK_NUMPAD_MULTIPLY 
%num WXK_NUMPAD_ADD 
%num WXK_NUMPAD_SEPARATOR 
%num WXK_NUMPAD_SUBTRACT 
%num WXK_NUMPAD_DECIMAL 
%num WXK_NUMPAD_DIVIDE 

// enums, not classes
%enum wxDateTime::WeekDay
%enum wxDateTime::Country
%enum wxDateTime::Month
wxDateTime::Calendar
%enum wxEdge
%enum wxFontEncoding
%enum wxGrid::wxGridSelectionModes
%enum wxLayoutAlignment
%enum wxLayoutOrientation
%enum wxRelationship
%enum wxSashEdgePosition
%enum wxSocketNotify
%enum wxTreeItemIcon
%enum wxPaperSize
%enum wxPrintQuality
%enum wxDuplexMode
%enum wxListColumnFormat

// typedefs
%typedef wxNotebookPage wxWindow
%typedef wxCoord coord
%typedef wxDateTime_t time_t
%typedef TimeZone double

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
%class wxDateSpan
%class wxDropTarget
    %include "wx/dnd.h"
%class wxIcon
%ptr wxNullIcon
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
// %class wxSizer
// Fix: Undefined symbol 'wxToolBarTool'
// %class wxToolBarTool
%class wxToolTip
    %include "wx/tooltip.h"
%class wxTreeItemData
%class wxTreeItemId
%class wxValidator
%class wxWindowList
win: %class wxMetafile
win:    %include "wx/metafile.h"
win: %class wxBitmapHandler
win: %class wxGDIImageHandler
%class wxMask
%class wxProcess
%class wxImageHandler
%class wxGridTableBase
    %include "wx/grid.h"
%class wxConfigBase
    %include "wx/config.h"
%class wxHtmlHelpData
    %include "wx/html/helpdata.h"
%class wxMemoryBuffer
%class wxNodeBase
    %include "wx/list.h"
%class wxSockAddress
    %include "wx/socket.h"
%class wxTimeSpan

///////////////////////////////////////////////////////////////////////////////
// not really classes, but i'm sticking them here for convenience

%include "wx/tipdlg.h"
%include "wx/filedlg.h"
%include "wx/colordlg.h"
%include "wx/textdlg.h"
%include "wx/choicdlg.h"
%include "wx/msgdlg.h"
%include "wx/tipdlg.h"

// Fixed: Changed wxChar to wxString
// Fixed: wxWindow default had been "", changed to NULL
%builtin wxString wxFileSelector(const wxString& message, const wxString& default_path = "", const wxString& default_filename = "", const wxString& default_extension = "", const wxString& wildcard = "*.*", int flags = 0, wxWindow *parent = NULL, int x = -1, int y = -1)
%builtin %alias wxGetColorFromUser wxColour wxGetColourFromUser(wxWindow *parent, const wxColour& colInit)
%builtin long wxGetNumberFromUser( const wxString& message, const wxString& prompt, const wxString& caption, long value, long min = 0, long max = 100, wxWindow *parent = NULL, const wxPoint& pos = wxDefaultPosition)
%builtin wxString wxGetPasswordFromUser(const wxString& message, const wxString& caption = "Input text", const wxString& default_value = "", wxWindow *parent = NULL)
%builtin wxString wxGetTextFromUser(const wxString& message, const wxString& caption = "Input text", const wxString& default_value = "", wxWindow *parent = NULL, int x = -1, int y = -1, bool centre = TRUE)

// Fix: don't support multiple selections yet
// int wxGetMultipleChoice(const wxString& message, const wxString& caption, int n, const wxString& choices[], int nsel, int *selection, wxWindow *parent = NULL, int x = -1, int y = -1, bool centre = TRUE, int width=150, int height=200)
// wxString wxGetSingleChoice(const wxString& message, const wxString& caption, int n, const wxString& choices[], wxWindow *parent = NULL, int x = -1, int y = -1, bool centre = TRUE, int width=150, int height=200)
// int wxGetSingleChoiceIndex(const wxString& message, const wxString& caption, int n, const wxString& choices[], wxWindow *parent = NULL, int x = -1, int y = -1, bool centre = TRUE, int width=150, int height=200)

%builtin int wxMessageBox(const wxString& message, const wxString& caption = "Message", int style = wxOK | wxCENTRE, wxWindow *parent = NULL, int x = -1, int y = -1)
%num wxOK 
%num wxYES_NO 
%num wxCANCEL 
%num wxYES 
%num wxNO 
%num wxNO_DEFAULT 
%num wxYES_DEFAULT 
%num wxICON_EXCLAMATION 
%num wxICON_HAND 
%num wxICON_WARNING 
%num wxICON_ERROR 
%num wxICON_QUESTION 
%num wxICON_INFORMATION 
%num wxICON_STOP 
%num wxICON_ASTERISK 
%num wxICON_MASK 


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
// %builtin int wxGetOsVersion(int *major = NULL, int *minor = NULL)
%{
    void GetOsVersion()
    {
        int major, minor;
        wxGetOsVersion( &major, &minor );
        wStackPushNumber( (wNumber)major );
        wStackPushNumber( (wNumber)minor );
    }
%}
%builtin %rename wxGetOsVersion void GetOsVersion()


%num wxUNKNOWN_PLATFORM
%num wxCURSES
%num wxXVIEW_X
%num wxMOTIF_X
%num wxCOSE_X
%num wxNEXTSTEP
%num wxBEOS
%num wxGTK
%num wxGTK_WIN32
%num wxGTK_OS2
%num wxGTK_BEOS
%num wxGEOS
%num wxOS2_PM
%num wxWINDOWS
%num wxPENWINDOWS
%num wxWINDOWS_NT
%num wxWIN32S
%num wxWIN95
%num wxWIN386
%num wxMGL_UNIX
%num wxMGL_X
%num wxMGL_WIN32
%num wxMGL_OS2
%num wxWINDOWS_OS2
%num wxUNIX


%builtin const wxString wxGetTranslation(const wxString str)
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
// File utility functions

// file functions

%include <wx/utils.h>
%include <wx/docview.h>

%builtin bool wxDirExists(const wxString& dirname)
// %builtin void wxDos2UnixFilename(wxChar *s)
%builtin void wxDos2UnixFilename(char *s)
%builtin bool wxFileExists(const wxString& filename)
%builtin time_t wxFileModificationTime(const wxString& filename)

// these two are obsolete. use wxFileName::SplitPath instead
%builtin wxString wxFileNameFromPath(const wxString& path)
// char * wxFileNameFromPath(char *path)
%builtin wxString wxFindFirstFile(const char *spec, int flags = 0)
%builtin wxString wxFindNextFile()
// FIXME: needs wrapper to pass values back
// %builtin bool wxGetDiskSpace(const wxString& path, wxLongLong *total = NULL, wxLongLong *free = NULL)
%builtin wxString wxGetOSDirectory()
%builtin bool wxIsAbsolutePath(const wxString& filename)
%builtin wxString wxPathOnly(const wxString& path)
// %builtin void wxUnix2DosFilename(const wxString& s)
%builtin void wxUnix2DosFilename(const char *s)
%builtin bool wxConcatFiles(const wxString& file1, const wxString& file2, const wxString& file3)
%builtin bool wxCopyFile(const wxString& file1, const wxString& file2, bool overwrite = TRUE)
%builtin wxString wxGetCwd()
%builtin wxString wxGetWorkingDirectory(char *buf=NULL, int sz=1000)
// These two are obsolete, use wxFileName::CreateTempFileName instead
// char * wxGetTempFileName(const wxString& prefix, char *buf=NULL)
%builtin bool wxGetTempFileName(const wxString& prefix, wxString& buf)
%builtin bool wxIsWild(const wxString& pattern)
%builtin bool wxMatchWild(const wxString& pattern, const wxString& text, bool dot_special)
%builtin bool wxMkdir(const wxString& dir, int perm = 0777)
%builtin bool wxRemoveFile(const wxString& file)
%builtin bool wxRenameFile(const wxString& file1, const wxString& file2)
%builtin bool wxRmdir(const wxString& dir, int flags=0)
%builtin bool wxSetWorkingDirectory(const wxString& dir)
// NB: This function is obsolete, please use wxFileName::SplitPath instead.
// %builtin void wxSplitPath(const char * fullname, wxString * path, wxString * name, wxString * ext)
// FIXME: can't handle ostream or istream datatypes
// %builtin bool wxTransferFileToStream(const wxString& filename, ostream& stream)
// %builtin bool wxTransferStreamToFile(istream& stream const wxString& filename)




///////////////////////////////////////////////////////////////////////////////
// NON-GUI CLASSES

///////////////////////////////////////////////////////////////////////////////
// wxLocale

%class wxLocale
%include "wx/intl.h"

wxLocale()
~wxLocale()
bool AddCatalog(const char *szDomain)
void AddCatalogLookupPathPrefix(const wxString& prefix)
// FIXME: needs custom wrapper for wxLanguageInfo structure
// static void AddLanguage(const wxLanguageInfo& info)
wxString GetCanonicalName() const
int GetLanguage() const
// FIXME: needs custom wrapper for wxLanguageInfo structure
// static wxLanguageInfo * GetLanguageInfo(int lang) const
const char* GetLocale() const
const wxString& GetName() const
const char* GetString(const char *szOrigString, const char *szDomain = NULL) const
wxString GetSysName() const
static wxFontEncoding GetSystemEncoding() const
static wxString GetSystemEncodingName() const
static int GetSystemLanguage() const
bool Init(int language = wxLANGUAGE_DEFAULT, int flags = wxLOCALE_LOAD_DEFAULT | wxLOCALE_CONV_ENCODING)
// deprecated
// bool Init(const char *szName, const char *szShort = NULL, const char *szLocale = NULL, bool bLoadDefault = TRUE, bool bConvertEncoding = FALSE)
bool IsLoaded(const char* domain) const
bool IsOk() const


%num wxLOCALE_LOAD_DEFAULT
%num wxLOCALE_CONV_ENCODING 	


%num  wxLANGUAGE_DEFAULT
%num wxLANGUAGE_UNKNOWN
%num wxLANGUAGE_USER_DEFINED
%num wxLANGUAGE_ABKHAZIAN
%num wxLANGUAGE_AFAR
%num wxLANGUAGE_AFRIKAANS
%num wxLANGUAGE_ALBANIAN
%num wxLANGUAGE_AMHARIC
%num wxLANGUAGE_ARABIC
%num wxLANGUAGE_ARABIC_ALGERIA
%num wxLANGUAGE_ARABIC_BAHRAIN
%num wxLANGUAGE_ARABIC_EGYPT
%num wxLANGUAGE_ARABIC_IRAQ
%num wxLANGUAGE_ARABIC_JORDAN
%num wxLANGUAGE_ARABIC_KUWAIT
%num wxLANGUAGE_ARABIC_LEBANON
%num wxLANGUAGE_ARABIC_LIBYA
%num wxLANGUAGE_ARABIC_MOROCCO
%num wxLANGUAGE_ARABIC_OMAN
%num wxLANGUAGE_ARABIC_QATAR
%num wxLANGUAGE_ARABIC_SAUDI_ARABIA
%num wxLANGUAGE_ARABIC_SUDAN
%num wxLANGUAGE_ARABIC_SYRIA
%num wxLANGUAGE_ARABIC_TUNISIA
%num wxLANGUAGE_ARABIC_UAE
%num wxLANGUAGE_ARABIC_YEMEN
%num wxLANGUAGE_ARMENIAN
%num wxLANGUAGE_ASSAMESE
%num wxLANGUAGE_AYMARA
%num wxLANGUAGE_AZERI
%num wxLANGUAGE_AZERI_CYRILLIC
%num wxLANGUAGE_AZERI_LATIN
%num wxLANGUAGE_BASHKIR
%num wxLANGUAGE_BASQUE
%num wxLANGUAGE_BELARUSIAN
%num wxLANGUAGE_BENGALI
%num wxLANGUAGE_BHUTANI
%num wxLANGUAGE_BIHARI
%num wxLANGUAGE_BISLAMA
%num wxLANGUAGE_BRETON
%num wxLANGUAGE_BULGARIAN
%num wxLANGUAGE_BURMESE
%num wxLANGUAGE_CAMBODIAN
%num wxLANGUAGE_CATALAN
%num wxLANGUAGE_CHINESE
%num wxLANGUAGE_CHINESE_SIMPLIFIED
%num wxLANGUAGE_CHINESE_TRADITIONAL
%num wxLANGUAGE_CHINESE_HONGKONG
%num wxLANGUAGE_CHINESE_MACAU
%num wxLANGUAGE_CHINESE_SINGAPORE
%num wxLANGUAGE_CHINESE_TAIWAN
%num wxLANGUAGE_CORSICAN
%num wxLANGUAGE_CROATIAN
%num wxLANGUAGE_CZECH
%num wxLANGUAGE_DANISH
%num wxLANGUAGE_DUTCH
%num wxLANGUAGE_DUTCH_BELGIAN
%num wxLANGUAGE_ENGLISH
%num wxLANGUAGE_ENGLISH_UK
%num wxLANGUAGE_ENGLISH_US
%num wxLANGUAGE_ENGLISH_AUSTRALIA
%num wxLANGUAGE_ENGLISH_BELIZE
%num wxLANGUAGE_ENGLISH_BOTSWANA
%num wxLANGUAGE_ENGLISH_CANADA
%num wxLANGUAGE_ENGLISH_CARIBBEAN
%num wxLANGUAGE_ENGLISH_DENMARK
%num wxLANGUAGE_ENGLISH_EIRE
%num wxLANGUAGE_ENGLISH_JAMAICA
%num wxLANGUAGE_ENGLISH_NEW_ZEALAND
%num wxLANGUAGE_ENGLISH_PHILIPPINES
%num wxLANGUAGE_ENGLISH_SOUTH_AFRICA
%num wxLANGUAGE_ENGLISH_TRINIDAD
%num wxLANGUAGE_ENGLISH_ZIMBABWE
%num wxLANGUAGE_ESPERANTO
%num wxLANGUAGE_ESTONIAN
%num wxLANGUAGE_FAEROESE
%num wxLANGUAGE_FARSI
%num wxLANGUAGE_FIJI
%num wxLANGUAGE_FINNISH
%num wxLANGUAGE_FRENCH
%num wxLANGUAGE_FRENCH_BELGIAN
%num wxLANGUAGE_FRENCH_CANADIAN
%num wxLANGUAGE_FRENCH_LUXEMBOURG
%num wxLANGUAGE_FRENCH_MONACO
%num wxLANGUAGE_FRENCH_SWISS
%num wxLANGUAGE_FRISIAN
%num wxLANGUAGE_GALICIAN
%num wxLANGUAGE_GEORGIAN
%num wxLANGUAGE_GERMAN
%num wxLANGUAGE_GERMAN_AUSTRIAN
%num wxLANGUAGE_GERMAN_BELGIUM
%num wxLANGUAGE_GERMAN_LIECHTENSTEIN
%num wxLANGUAGE_GERMAN_LUXEMBOURG
%num wxLANGUAGE_GERMAN_SWISS
%num wxLANGUAGE_GREEK
%num wxLANGUAGE_GREENLANDIC
%num wxLANGUAGE_GUARANI
%num wxLANGUAGE_GUJARATI
%num wxLANGUAGE_HAUSA
%num wxLANGUAGE_HEBREW
%num wxLANGUAGE_HINDI
%num wxLANGUAGE_HUNGARIAN
%num wxLANGUAGE_ICELANDIC
%num wxLANGUAGE_INDONESIAN
%num wxLANGUAGE_INTERLINGUA
%num wxLANGUAGE_INTERLINGUE
%num wxLANGUAGE_INUKTITUT
%num wxLANGUAGE_INUPIAK
%num wxLANGUAGE_IRISH
%num wxLANGUAGE_ITALIAN
%num wxLANGUAGE_ITALIAN_SWISS
%num wxLANGUAGE_JAPANESE
%num wxLANGUAGE_JAVANESE
%num wxLANGUAGE_KANNADA
%num wxLANGUAGE_KASHMIRI
%num wxLANGUAGE_KASHMIRI_INDIA
%num wxLANGUAGE_KAZAKH
%num wxLANGUAGE_KERNEWEK
%num wxLANGUAGE_KINYARWANDA
%num wxLANGUAGE_KIRGHIZ
%num wxLANGUAGE_KIRUNDI
%num wxLANGUAGE_KONKANI
%num wxLANGUAGE_KOREAN
%num wxLANGUAGE_KURDISH
%num wxLANGUAGE_LAOTHIAN
%num wxLANGUAGE_LATIN
%num wxLANGUAGE_LATVIAN
%num wxLANGUAGE_LINGALA
%num wxLANGUAGE_LITHUANIAN
%num wxLANGUAGE_MACEDONIAN
%num wxLANGUAGE_MALAGASY
%num wxLANGUAGE_MALAY
%num wxLANGUAGE_MALAYALAM
%num wxLANGUAGE_MALAY_BRUNEI_DARUSSALAM
%num wxLANGUAGE_MALAY_MALAYSIA
%num wxLANGUAGE_MALTESE
%num wxLANGUAGE_MANIPURI
%num wxLANGUAGE_MAORI
%num wxLANGUAGE_MARATHI
%num wxLANGUAGE_MOLDAVIAN
%num wxLANGUAGE_MONGOLIAN
%num wxLANGUAGE_NAURU
%num wxLANGUAGE_NEPALI
%num wxLANGUAGE_NEPALI_INDIA
%num wxLANGUAGE_NORWEGIAN_BOKMAL
%num wxLANGUAGE_NORWEGIAN_NYNORSK
%num wxLANGUAGE_OCCITAN
%num wxLANGUAGE_ORIYA
%num wxLANGUAGE_OROMO
%num wxLANGUAGE_PASHTO
%num wxLANGUAGE_POLISH
%num wxLANGUAGE_PORTUGUESE
%num wxLANGUAGE_PORTUGUESE_BRAZILIAN
%num wxLANGUAGE_PUNJABI
%num wxLANGUAGE_QUECHUA
%num wxLANGUAGE_RHAETO_ROMANCE
%num wxLANGUAGE_ROMANIAN
%num wxLANGUAGE_RUSSIAN
%num wxLANGUAGE_RUSSIAN_UKRAINE
%num wxLANGUAGE_SAMOAN
%num wxLANGUAGE_SANGHO
%num wxLANGUAGE_SANSKRIT
%num wxLANGUAGE_SCOTS_GAELIC
%num wxLANGUAGE_SERBIAN
%num wxLANGUAGE_SERBIAN_CYRILLIC
%num wxLANGUAGE_SERBIAN_LATIN
%num wxLANGUAGE_SERBO_CROATIAN
%num wxLANGUAGE_SESOTHO
%num wxLANGUAGE_SETSWANA
%num wxLANGUAGE_SHONA
%num wxLANGUAGE_SINDHI
%num wxLANGUAGE_SINHALESE
%num wxLANGUAGE_SISWATI
%num wxLANGUAGE_SLOVAK
%num wxLANGUAGE_SLOVENIAN
%num wxLANGUAGE_SOMALI
%num wxLANGUAGE_SPANISH
%num wxLANGUAGE_SPANISH_ARGENTINA
%num wxLANGUAGE_SPANISH_BOLIVIA
%num wxLANGUAGE_SPANISH_CHILE
%num wxLANGUAGE_SPANISH_COLOMBIA
%num wxLANGUAGE_SPANISH_COSTA_RICA
%num wxLANGUAGE_SPANISH_DOMINICAN_REPUBLIC
%num wxLANGUAGE_SPANISH_ECUADOR
%num wxLANGUAGE_SPANISH_EL_SALVADOR
%num wxLANGUAGE_SPANISH_GUATEMALA
%num wxLANGUAGE_SPANISH_HONDURAS
%num wxLANGUAGE_SPANISH_MEXICAN
%num wxLANGUAGE_SPANISH_MODERN
%num wxLANGUAGE_SPANISH_NICARAGUA
%num wxLANGUAGE_SPANISH_PANAMA
%num wxLANGUAGE_SPANISH_PARAGUAY
%num wxLANGUAGE_SPANISH_PERU
%num wxLANGUAGE_SPANISH_PUERTO_RICO
%num wxLANGUAGE_SPANISH_URUGUAY
%num wxLANGUAGE_SPANISH_US
%num wxLANGUAGE_SPANISH_VENEZUELA
%num wxLANGUAGE_SUNDANESE
%num wxLANGUAGE_SWAHILI
%num wxLANGUAGE_SWEDISH
%num wxLANGUAGE_SWEDISH_FINLAND
%num wxLANGUAGE_TAGALOG
%num wxLANGUAGE_TAJIK
%num wxLANGUAGE_TAMIL
%num wxLANGUAGE_TATAR
%num wxLANGUAGE_TELUGU
%num wxLANGUAGE_THAI
%num wxLANGUAGE_TIBETAN
%num wxLANGUAGE_TIGRINYA
%num wxLANGUAGE_TONGA
%num wxLANGUAGE_TSONGA
%num wxLANGUAGE_TURKISH
%num wxLANGUAGE_TURKMEN
%num wxLANGUAGE_TWI
%num wxLANGUAGE_UIGHUR
%num wxLANGUAGE_UKRAINIAN
%num wxLANGUAGE_URDU
%num wxLANGUAGE_URDU_INDIA
%num wxLANGUAGE_URDU_PAKISTAN
%num wxLANGUAGE_UZBEK
%num wxLANGUAGE_UZBEK_CYRILLIC
%num wxLANGUAGE_UZBEK_LATIN
%num wxLANGUAGE_VIETNAMESE
%num wxLANGUAGE_VOLAPUK
%num wxLANGUAGE_WELSH
%num wxLANGUAGE_WOLOF
%num wxLANGUAGE_XHOSA
%num wxLANGUAGE_YIDDISH
%num wxLANGUAGE_YORUBA
%num wxLANGUAGE_ZHUANG
%num wxLANGUAGE_ZULU



///////////////////////////////////////////////////////////////////////////////
// wxObject

%class wxObject
wxObject()
~wxObject()
* m_refData
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
// wxNode

%class wxNode
%include "wx/list.h"

void * Data()
wxNodeBase * Next()
wxNodeBase * GetPrevious()
// Fixed: changed void* to wxObject*
// void SetData(void *data)
void SetData( wxObject *data )
// FIX! 'int wxNodeBase::IndexOf() const' is protected
// int IndexOf()


///////////////////////////////////////////////////////////////////////////////
// wxList

%class wxList, wxObject
%include "wx/list.h"

wxList()
%ctor wxListKey(unsigned int key_type)
// wxList(int n, wxObject *objects[])
// wxList(wxObject *object, ...)
~wxList()
wxNode * Append(wxObject *object)
%rename AppendNumericKey wxNode * Append(long key, wxObject *object)
%rename AppendStringKey wxNode * Append(const wxString& key, wxObject *object)
void Clear()
void DeleteContents(bool destroy)
bool DeleteNode(wxNode *node)
bool DeleteObject(wxObject *object)
%rename FindNumericKey wxNode * Find(long key)
%rename FindStringKey wxNode * Find(const wxString& key)
size_t GetCount() const
wxNode * GetFirst()
wxNode * GetLast()
int IndexOf(wxObject* obj )
wxNode * Insert(wxObject *object)
%rename InsertAt wxNode * Insert(size_t position, wxObject *object)
%rename InsertBefore wxNode * Insert(wxNode *node, wxObject *object)
bool IsEmpty() const
wxNode * Item(size_t index) const
// Deprecated, use Find
// wxNode * Member(wxObject *object)
// Deprecated, use GetCount
// wxNode * Nth(int n)
// Fix: Can't implement
// void Sort(wxSortCompareFunction compfunc)

///////////////////////////////////////////////////////////////////////////////
// wxDataFormat
//

%class wxDataFormat
wxDataFormat(const wxString *format)

%num wxDF_INVALID
%num wxDF_TEXT
%num wxDF_BITMAP
%num wxDF_METAFILE
%num wxDF_SYLK
%num wxDF_DIF
%num wxDF_TIFF
%num wxDF_OEMTEXT
%num wxDF_DIB
%num wxDF_PALETTE
%num wxDF_PENDATA
%num wxDF_RIFF
%num wxDF_WAVE
%num wxDF_UNICODETEXT
%num wxDF_ENHMETAFILE
%num wxDF_FILENAME
%num wxDF_LOCALE
%num wxDF_PRIVATE
%num wxDF_MAX



///////////////////////////////////////////////////////////////////////////////
// wxTipProvider
//

%class wxTipProvider
%include "wx/tipdlg.h"
// Can't create: abstract class
// wxTipProvider(size_t currentTip)
wxString GetTip()
size_t GetCurrentTip() const

// Not class methods, but related
%builtin bool wxShowTip(wxWindow *parent, wxTipProvider *tipProvider, bool showAtStartup = TRUE)
%builtin wxTipProvider * wxCreateFileTipProvider(const wxString& filename, size_t currentTip)


///////////////////////////////////////////////////////////////////////////////
// wxPoint

%class wxPoint
wxPoint(int x, int y)
~wxPoint()
int x
int y
%{
    void wxPoint_Get()
    {
        int x, y;
        x = ((wxPoint *)wTheCall->self->ptr)->x;
        y = ((wxPoint *)wTheCall->self->ptr)->y;
        wWrapDerefArgs();
        wStackPushNumber( (wNumber)x );
        wStackPushNumber( (wNumber)y );
    }

    void wxPoint_GetX()
    {
        int x;
        x = ((wxPoint *)wTheCall->self->ptr)->x;
        wWrapDerefArgs();
        wStackPushNumber( (wNumber)x );
    }
    void wxPoint_GetY()
    {
        int y;
        y = ((wxPoint *)wTheCall->self->ptr)->y;
        wWrapDerefArgs();
        wStackPushNumber( (wNumber)y );
    }
%}
%method Get wxPoint_Get()
%method GetX wxPoint_GetX()
%method GetY wxPoint_GetY()

// alias wxDefaultPosition
%{
    #define __wxDefaultPosition &wxDefaultPosition
%}
%ptr %alias wxDefaultPosition __wxDefaultPosition

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

// alias __wxDefaultSize
%{
    #define __wxDefaultSize &wxDefaultSize
%}
%ptr %alias wxDefaultSize __wxDefaultSize


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

%class wxColour, wxObject
%include "wx/colour.h"

wxColour(const unsigned char red, const unsigned char green, const unsigned char blue)
%ctor wxColor(const unsigned char red, const unsigned char green, const unsigned char blue)

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
     
%ptr wxBLACK
%ptr wxWHITE
%ptr wxRED
%ptr wxBLUE
%ptr wxGREEN
%ptr wxCYAN
%ptr wxLIGHT_GREY
%ptr wxNullColour

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

%ptr wxRED_PEN
%ptr wxCYAN_PEN
%ptr wxGREEN_PEN
%ptr wxBLACK_PEN
%ptr wxWHITE_PEN
%ptr wxTRANSPARENT_PEN
%ptr wxBLACK_DASHED_PEN
%ptr wxGREY_PEN
%ptr wxMEDIUM_GREY_PEN
%ptr wxLIGHT_GREY_PEN

%ptr wxNullPen


%num wxSOLID
%num wxDOT
%num wxLONG_DASH
%num wxSHORT_DASH
%num wxDOT_DASH
%num wxUSER_DASH
%num wxTRANSPARENT
%num wxSTIPPLE
%num wxBDIAGONAL_HATCH
%num wxCROSSDIAG_HATCH
%num wxFDIAGONAL_HATCH
%num wxCROSS_HATCH
%num wxHORIZONTAL_HATCH
%num wxVERTICAL_HATCH
%num wxJOIN_BEVEL
%num wxJOIN_MITER
%num wxJOIN_ROUND
%num wxCAP_ROUND
%num wxCAP_PROJECTING
%num wxCAP_BUTT


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
%ctor wxBrushCopy(const wxBrush& brush)
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


%ptr wxBLUE_BRUSH
%ptr wxGREEN_BRUSH
%ptr wxWHITE_BRUSH
%ptr wxBLACK_BRUSH
%ptr wxTRANSPARENT_BRUSH
%ptr wxCYAN_BRUSH
%ptr wxRED_BRUSH
%ptr wxGREY_BRUSH
%ptr wxMEDIUM_GREY_BRUSH
%ptr wxLIGHT_GREY_BRUSH

%ptr wxNullBrush

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
%rename DrawLinesFromList void DrawLines(wxList *points, wxCoord xoffset = 0, wxCoord yoffset = 0)

// Alias
void DrawPolygon(int n, wxPoint points[], wxCoord xoffset = 0, wxCoord yoffset = 0, int fill_style = wxODDEVEN_RULE)
%rename DrawPolygonFromList void DrawPolygon(wxList *points, wxCoord xoffset = 0, wxCoord yoffset = 0, int fill_style = wxODDEVEN_RULE)

void DrawPoint(wxCoord x, wxCoord y)
void DrawRectangle(wxCoord x, wxCoord y, wxCoord width, wxCoord height)
void DrawRotatedText(const wxString& text, wxCoord x, wxCoord y, double angle)
void DrawRoundedRectangle(wxCoord x, wxCoord y, wxCoord width, wxCoord height, double radius = 20)

// Fix!
%rename DrawSplineFromList void DrawSpline(wxList *points)

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
    void wxDC_GetClippingBox()
    {
        wxCoord x, y, width, height;
        ((wxDC *)wTheCall->self->ptr)->GetClippingBox(&x, &y, &width, &height);
        wWrapDerefArgs();
        wStackPushNumber( (wNumber)x );
        wStackPushNumber( (wNumber)y );
        wStackPushNumber( (wNumber)width );
        wStackPushNumber( (wNumber)height );
    }

    void wxDC_GetClippingBoxX()
    {
        wxCoord x, y, width, height;
        ((wxDC *)wTheCall->self->ptr)->GetClippingBox(&x, &y, &width, &height);
        wWrapDerefArgs();
        wStackPushNumber( (wNumber)x );
    }

    void wxDC_GetClippingBoxY()
    {
        wxCoord x, y, width, height;
        ((wxDC *)wTheCall->self->ptr)->GetClippingBox(&x, &y, &width, &height);
        wWrapDerefArgs();
        wStackPushNumber( (wNumber)y );
    }

    void wxDC_GetClippingBoxWidth()
    {
        wxCoord x, y, width, height;
        ((wxDC *)wTheCall->self->ptr)->GetClippingBox(&x, &y, &width, &height);
        wWrapDerefArgs();
        wStackPushNumber( (wNumber)width );
    }

    void wxDC_GetClippingBoxHeight()
    {
        wxCoord x, y, width, height;
        ((wxDC *)wTheCall->self->ptr)->GetClippingBox(&x, &y, &width, &height);
        wWrapDerefArgs();
        wStackPushNumber( (wNumber)height );
    }

%}
%method GetPixelBox         wxDC_GetClippingBox()
%method GetPixelBoxX        wxDC_GetClippingBoxX()
%method GetPixelBoxY        wxDC_GetClippingBoxY()
%method GetPixelBoxWidth    wxDC_GetClippingBoxWidth()
%method GetPixelBoxHeight   wxDC_GetClippingBoxHeight()

wxFont& GetFont()
int GetLogicalFunction()
int GetMapMode()
bool GetOptimization()

wxPen& GetPen()
// const wxPen& GetPen() const
// bool GetPixel(wxCoord x, wxCoord y, wxColour *colour)
%{
    void wxDC_GetPixel()
    {
		wxCoord y = wStackPopNumber();		
        wxCoord x = wStackPopNumber();
        wxColour *returns;
        ((wxDC *)wTheCall->self->ptr)->GetPixel(x, y, returns);
        wWrapDerefArgs();
		wWrapSetThis( _wxColour, (void *)returns );        
    }
%}
%method GetPixel wxDC_GetPixel(wxCoord x, wxCoord y)


// void GetSize(wxCoord *width, wxCoord *height)
// wxPython note: In place of a single overloaded method name, wxPython implements the following methods:
//        GetSize()  Returns a wxSize  
//        GetSizeTuple()  Returns a 2-tuple (width, height)  

%{
    void wxDC_GetSize()
    {
        int x, y;
        // call GetSize
        ((wxDC *)wTheCall->self->ptr)->GetSize(&x, &y);
        wWrapDerefArgs();
        wStackPushNumber( (wNumber)x );
        wStackPushNumber( (wNumber)y );
    }
    void wxDC_GetSizeX()
    {
        int x, y;
        // call GetSize
        ((wxDC *)wTheCall->self->ptr)->GetSize(&x, &y);
        wWrapDerefArgs();
        wStackPushNumber( (wNumber)x );
    }

    void wxDC_GetSizeY()
    {
        int x, y;
        // call GetSize
        ((wxDC *)wTheCall->self->ptr)->GetSize(&x, &y);
        wWrapDerefArgs();
        wStackPushNumber( (wNumber)y );
    }
%}
%method GetSize     wxDC_GetSize()
%method GetSizeX    wxDC_GetSizeX()
%method GetSizeY    wxDC_GetSizeY()

const wxColour& GetTextBackground() const

// void GetTextExtent(const wxString& string, wxCoord *w, wxCoord *h, wxCoord *descent = NULL, wxCoord *externalLeading = NULL, wxFont *font = NULL)
// wxPython note: The following methods are implemented in wxPython:
//        GetTextExtent(string)  Returns a 2-tuple, (width, height)  
//        GetFullTextExtent(string, font=NULL)  Returns a 4-tuple, (width, height, descent, externalLeading)  

%{
    void wxDC_GetTextExtentWidth()
    {
        // returned parameters
        wxCoord w, h, descent, externalLeading;

        // wxFont *font = NULL
        wxFont *font = (wTheCall->parmCount > 1 ? (wxFont *)wStackPopObjectPtr( _wxFont) : NULL);

        // const wxString& string
        wxString string = wStackPopChar();

        // call GetTextExtent
        ((wxDC *)wTheCall->self->ptr)->GetTextExtent(string, &w, &h, &descent, &externalLeading, font);
        wWrapDerefArgs();

        // return the width
        wStackPushNumber( (wNumber)w );
    }

    void wxDC_GetTextExtentHeight()
    {
        // returned parameters
        wxCoord w, h, descent, externalLeading;

        // wxFont *font = NULL
        wxFont *font = (wTheCall->parmCount > 1 ? (wxFont *)wStackPopObjectPtr( _wxFont) : NULL);

        // const wxString& string
        wxString string = wStackPopChar();

        // call GetTextExtent
        ((wxDC *)wTheCall->self->ptr)->GetTextExtent(string, &w, &h, &descent, &externalLeading, font);
        wWrapDerefArgs();

        // return the height
        wStackPushNumber( (wNumber)h );
    }

    void wxDC_GetTextExtentDescent()
    {
        // returned parameters
        wxCoord w, h, descent, externalLeading;

        // wxFont *font = NULL
        wxFont *font = (wTheCall->parmCount > 1 ? (wxFont *)wStackPopObjectPtr( _wxFont) : NULL);

        // const wxString& string
        wxString string = wStackPopChar();

        // call GetTextExtent
        ((wxDC *)wTheCall->self->ptr)->GetTextExtent(string, &w, &h, &descent, &externalLeading, font);
        wWrapDerefArgs();

        // return the descent
        wStackPushNumber( (wNumber)descent );
    }

    void wxDC_GetTextExtentExternalLeading()
    {
        // returned parameters
        wxCoord w, h, descent, externalLeading;

        // wxFont *font = NULL
        wxFont *font = (wTheCall->parmCount > 1 ? (wxFont *)wStackPopObjectPtr( _wxFont) : NULL);

        // const wxString& string
        wxString string = wStackPopChar();

        // call GetTextExtent
        ((wxDC *)wTheCall->self->ptr)->GetTextExtent(string, &w, &h, &descent, &externalLeading, font);
        wWrapDerefArgs();

        // return the external leading
        wStackPushNumber( (wNumber)externalLeading );
    }

%}
%method GetTextExtentWidth              wxDC_GetTextExtentWidth( const wxString& string, wxFont *font = NULL )
%method GetTextExtentHeight             wxDC_GetTextExtentHeight( const wxString& string, wxFont *font = NULL )
%method GetTextExtentDescent            wxDC_GetTextExtentDescent( const wxString& string, wxFont *font = NULL )
%method GetTextExtentExternalLeading    wxDC_GetTextExtentExternalLeading( const wxString& string, wxFont *font = NULL )

// alias...
wxColour& GetTextForeground()
// const wxColour& GetTextForeground() const

// void GetUserScale(double *x, double *y)
%{
    void wxDC_GetUserScale()
    {
        double x, y;
        ((wxDC *)wTheCall->self->ptr)->GetUserScale(&x, &y);
        wWrapDerefArgs();
        wStackPushNumber( (wNumber)x );
        wStackPushNumber( (wNumber)y );
    }

    void wxDC_GetUserScaleX()
    {
        double x, y;
        ((wxDC *)wTheCall->self->ptr)->GetUserScale(&x, &y);
        wWrapDerefArgs();
        wStackPushNumber( (wNumber)x );
    }

    void wxDC_GetUserScaleY()
    {
        double x, y;
        ((wxDC *)wTheCall->self->ptr)->GetUserScale(&x, &y);
        wWrapDerefArgs();
        wStackPushNumber( (wNumber)y );
    }
%}
%method GetUserScale    wxDC_GetUserScale()
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

%num wxCLEAR
%num wxXOR
%num wxINVERT
%num wxOR_REVERSE
%num wxAND_REVERSE
%num wxCOPY
%num wxAND
%num wxAND_INVERT
%num wxNO_OP
%num wxNOR
%num wxEQUIV
%num wxSRC_INVERT
%num wxOR_INVERT
%num wxNAND
%num wxOR
%num wxSET


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
// wxPrintData

%class wxPrintData, wxObject
% include "wx/cmndata.h"

wxPrintData()
// FIX! Alternate constructor
// wxPrintData(const wxPrintData& data)
~wxPrintData()
bool GetCollate() const
bool GetColour() const
wxDuplexMode GetDuplex() const
int GetNoCopies() const
int GetOrientation() const
wxPaperSize GetPaperId() const
const wxString& GetPrinterName() const
wxPrintQuality GetQuality() const
bool Ok() const
void SetCollate(bool flag)
%alias SetColor void SetColour(bool flag)
void SetDuplex(wxDuplexMode mode)
void SetNoCopies(int n)
void SetOrientation(int orientation)
void SetPaperId(wxPaperSize paperId)
void SetPrinterName(const wxString& printerName)
void SetQuality(wxPrintQuality quality)

%num wxPAPER_NONE 
%num wxPAPER_LETTER 
%num wxPAPER_LEGAL 
%num wxPAPER_A4 
%num wxPAPER_CSHEET 
%num wxPAPER_DSHEET 
%num wxPAPER_ESHEET 
%num wxPAPER_LETTERSMALL 
%num wxPAPER_TABLOID 
%num wxPAPER_LEDGER 
%num wxPAPER_STATEMENT 
%num wxPAPER_EXECUTIVE 
%num wxPAPER_A3 
%num wxPAPER_A4SMALL 
%num wxPAPER_A5 
%num wxPAPER_B4 
%num wxPAPER_B5 
%num wxPAPER_FOLIO 
%num wxPAPER_QUARTO 
%num wxPAPER_10X14 
%num wxPAPER_11X17 
%num wxPAPER_NOTE 
%num wxPAPER_ENV_9 
%num wxPAPER_ENV_10 
%num wxPAPER_ENV_11 
%num wxPAPER_ENV_12 
%num wxPAPER_ENV_14 
%num wxPAPER_ENV_DL 
%num wxPAPER_ENV_C5 
%num wxPAPER_ENV_C3 
%num wxPAPER_ENV_C4 
%num wxPAPER_ENV_C6 
%num wxPAPER_ENV_C65 
%num wxPAPER_ENV_B4 
%num wxPAPER_ENV_B5 
%num wxPAPER_ENV_B6 
%num wxPAPER_ENV_ITALY 
%num wxPAPER_ENV_MONARCH 
%num wxPAPER_ENV_PERSONAL 
%num wxPAPER_FANFOLD_US 
%num wxPAPER_FANFOLD_STD_GERMAN 
%num wxPAPER_FANFOLD_LGL_GERMAN 
%num wxPAPER_ISO_B4 
%num wxPAPER_JAPANESE_POSTCARD 
%num wxPAPER_9X11 
%num wxPAPER_10X11 
%num wxPAPER_15X11 
%num wxPAPER_ENV_INVITE 
%num wxPAPER_LETTER_EXTRA 
%num wxPAPER_LEGAL_EXTRA 
%num wxPAPER_TABLOID_EXTRA 
%num wxPAPER_A4_EXTRA 
%num wxPAPER_LETTER_TRANSVERSE 
%num wxPAPER_A4_TRANSVERSE 
%num wxPAPER_LETTER_EXTRA_TRANSVERSE 
%num wxPAPER_A_PLUS 
%num wxPAPER_B_PLUS 
%num wxPAPER_LETTER_PLUS 
%num wxPAPER_A4_PLUS 
%num wxPAPER_A5_TRANSVERSE 
%num wxPAPER_B5_TRANSVERSE 
%num wxPAPER_A3_EXTRA 
%num wxPAPER_A5_EXTRA 
%num wxPAPER_B5_EXTRA 
%num wxPAPER_A2 
%num wxPAPER_A3_TRANSVERSE 
%num wxPAPER_A3_EXTRA_TRANSVERSE 
%num wxDUPLEX_SIMPLEX 
%num wxDUPLEX_HORIZONTAL 
%num wxDUPLEX_VERTICAL 
%num wxPRINT_MODE_NONE 
%num wxPRINT_MODE_PREVIEW 
%num wxPRINT_MODE_FILE 
%num wxPRINT_MODE_PRINTER 


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

%ptr wxNullBitmap

%num wxBITMAP_TYPE_INVALID
%num wxBITMAP_TYPE_BMP
%num wxBITMAP_TYPE_BMP_RESOURCE
%num wxBITMAP_TYPE_RESOURCE
%num wxBITMAP_TYPE_ICO
%num wxBITMAP_TYPE_ICO_RESOURCE
%num wxBITMAP_TYPE_CUR
%num wxBITMAP_TYPE_CUR_RESOURCE
%num wxBITMAP_TYPE_XBM
%num wxBITMAP_TYPE_XBM_DATA
%num wxBITMAP_TYPE_XPM
%num wxBITMAP_TYPE_XPM_DATA
%num wxBITMAP_TYPE_TIF
%num wxBITMAP_TYPE_TIF_RESOURCE
%num wxBITMAP_TYPE_GIF
%num wxBITMAP_TYPE_GIF_RESOURCE
%num wxBITMAP_TYPE_PNG
%num wxBITMAP_TYPE_PNG_RESOURCE
%num wxBITMAP_TYPE_JPEG
%num wxBITMAP_TYPE_JPEG_RESOURCE
%num wxBITMAP_TYPE_PNM
%num wxBITMAP_TYPE_PNM_RESOURCE
%num wxBITMAP_TYPE_PCX
%num wxBITMAP_TYPE_PCX_RESOURCE
%num wxBITMAP_TYPE_PICT
%num wxBITMAP_TYPE_PICT_RESOURCE
%num wxBITMAP_TYPE_ICON
%num wxBITMAP_TYPE_ICON_RESOURCE
%num wxBITMAP_TYPE_MACCURSOR
%num wxBITMAP_TYPE_MACCURSOR_RESOURCE
%num wxBITMAP_TYPE_ANY


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
%alias SetMaskColor void SetMaskColour(unsigned char red, unsigned char blue, unsigned char green)
void SetPalette(const wxPalette& palette)
void SetRGB(int x, int y, unsigned char red, unsigned char green, unsigned char blue)


///////////////////////////////////////////////////////////////////////////////
// wxImageList


%class wxImageList, wxObject
%include "wx/imaglist.h"

wxImageList()
int Add(const wxBitmap& bitmap, const wxBitmap& mask = wxNullBitmap)
%rename AddWithColourMask int Add(const wxBitmap& bitmap, const wxColour& maskColour)
%rename AddIcon int Add(const wxIcon& icon)
bool Create(int width, int height, const bool mask = TRUE, int initialCount = 1)
bool Draw(int index, wxDC& dc, int x, int y, int flags = wxIMAGELIST_DRAW_NORMAL, const bool solidBackground = FALSE)

%num wxIMAGELIST_DRAW_NORMAL
%num wxIMAGELIST_DRAW_TRANSPARENT
%num wxIMAGELIST_DRAW_SELECTED
%num wxIMAGELIST_DRAW_FOCUSED

int GetImageCount() const
// bool GetSize(int index, int& width, int& height) const
%{
    void wxImageList_GetSize()
    {
        int index = wStackPopNumber();   
        int width, height;
        ((wxImageList *)wTheCall->self->ptr)->GetSize(index, width, height);
        wWrapDerefArgs();        
        wStackPushNumber( (wNumber)width );
        wStackPushNumber( (wNumber)height );
    }
    void wxImageList_GetSizeWidth()
    {
        int index = wStackPopNumber();   
        int width, height;
        ((wxImageList *)wTheCall->self->ptr)->GetSize(index, width, height);
        wWrapDerefArgs();        
        wStackPushNumber( (wNumber)width );
    }
    void wxImageList_GetSizeHeight()
    {
        int index = wStackPopNumber();   
        int width, height;
        ((wxImageList *)wTheCall->self->ptr)->GetSize(index, width, height);
        wWrapDerefArgs();        
        wStackPushNumber( (wNumber)height );
    }
%}
%method GetSize wxImageList_GetSize(int index)
%method GetSizeWidth wxImageList_GetSizeWidth(int index)
%method GetSizeHeight wxImageList_GetSizeHeight(int index)

bool Remove(int index)
bool RemoveAll()
bool Replace(int index, const wxBitmap& bitmap, const wxBitmap& mask = wxNullBitmap)
%rename ReplaceIcon bool Replace(int index, const wxIcon& icon)


///////////////////////////////////////////////////////////////////////////////
// wxCursor

%class wxCursor, wxBitmap 
%include "wx/cursor.h"

// platform dependant, add later


%ptr wxSTANDARD_CURSOR
%ptr wxHOURGLASS_CURSOR
%ptr wxCROSS_CURSOR
%ptr wxNullCursor

%num wxCURSOR_NONE
%num wxCURSOR_ARROW
%num wxCURSOR_BULLSEYE
%num wxCURSOR_CHAR
%num wxCURSOR_CROSS
%num wxCURSOR_HAND
%num wxCURSOR_IBEAM
%num wxCURSOR_LEFT_BUTTON
%num wxCURSOR_MAGNIFIER
%num wxCURSOR_MIDDLE_BUTTON
%num wxCURSOR_NO_ENTRY
%num wxCURSOR_PAINT_BRUSH
%num wxCURSOR_PENCIL
%num wxCURSOR_POINT_LEFT
%num wxCURSOR_POINT_RIGHT
%num wxCURSOR_QUESTION_ARROW
%num wxCURSOR_RIGHT_BUTTON
%num wxCURSOR_SIZENESW
%num wxCURSOR_SIZENS
%num wxCURSOR_SIZENWSE
%num wxCURSOR_SIZEWE
%num wxCURSOR_SIZING
%num wxCURSOR_SPRAYCAN
%num wxCURSOR_WAIT
%num wxCURSOR_WATCH
%num wxCURSOR_BLANK
%num wxCURSOR_ARROWWAIT
%num wxCURSOR_MAX




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
// don't create alias for these; they already exist above
void Centre(int direction = wxBOTH)
void CentreOnParent(int direction = wxBOTH)
void CentreOnScreen(int direction = wxBOTH)
void Clear()
// virtual void ClientToScreen(int* x, int* y) const
%{
    void wxWindow_ClientToScreen()
    {
        int x = wStackPopNumber();
        int y = wStackPopNumber();
        ((wxWindow *)wTheCall->self->ptr)->ClientToScreen(&x, &y);
        wWrapDerefArgs();
        wStackPushNumber( (wNumber)x );
        wStackPushNumber( (wNumber)y );
    }
    void wxWindow_ClientToScreenX()
    {
        int x = wStackPopNumber();
        int y = 0;
        ((wxWindow *)wTheCall->self->ptr)->ClientToScreen(&x, &y);
        wWrapDerefArgs();
        wStackPushNumber( (wNumber)x );
    }
    void wxWindow_ClientToScreenY()
    {
        int x = 0;
        int y = wStackPopNumber();
        ((wxWindow *)wTheCall->self->ptr)->ClientToScreen(&x, &y);
        wWrapDerefArgs();
        wStackPushNumber( (wNumber)y );
    }
%}
%method ClientToScreen wxWindow_ClientToScreen( int x, int y )
%method ClientToScreenX wxWindow_ClientToScreenX( int x )
%method ClientToScreenY wxWindow_ClientToScreenY( int y )

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
virtual void FitInside()
virtual void Freeze()
wxSize GetAdjustedBestSize() const
%alias GetBackgroundColor virtual wxColour GetBackgroundColour() const
virtual wxSize GetBestSize() const
wxCaret * GetCaret() const
static wxWindow * GetCapture()
virtual int GetCharHeight() const
virtual int GetCharWidth() const
// Error: had been wxList
wxWindowList& GetChildren()
// virtual void GetClientSize(int* width, int* height) const
%{
    void wxWindow_GetClientSizeWidth()
    {
        int width, height;
        ((wxWindow *)wTheCall->self->ptr)->GetClientSize(&width, &height);
        wWrapDerefArgs();
        wStackPushNumber( (wNumber)width );
    }

    void wxWindow_GetClientSizeHeight()
    {
        int width, height;
        ((wxWindow *)wTheCall->self->ptr)->GetClientSize(&width, &height);
        wWrapDerefArgs();
        wStackPushNumber( (wNumber)height );
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
virtual wxString GetHelpText() const
int GetId() const
virtual wxString GetLabel() const
virtual wxString GetName() const
virtual wxWindow* GetParent() const
// virtual void GetPosition(int* x, int* y) const
%{
    void wxWindow_GetPosition()
    {
        int x, y;
        ((wxWindow *)wTheCall->self->ptr)->GetPosition(&x, &y);
        wWrapDerefArgs();
        wStackPushNumber( (wNumber)x );
        wStackPushNumber( (wNumber)y );
    }
    void wxWindow_GetPositionX()
    {
        int x, y;
        ((wxWindow *)wTheCall->self->ptr)->GetPosition(&x, &y);
        wWrapDerefArgs();
        wStackPushNumber( (wNumber)x );
    }

    void wxWindow_GetPositionY()
    {
        int x, y;
        ((wxWindow *)wTheCall->self->ptr)->GetPosition(&x, &y);
        wWrapDerefArgs();
        wStackPushNumber( (wNumber)y );
    }


%}
%method GetPosition     wxWindow_GetPosition()
%method GetPositionX    wxWindow_GetPositionX()
%method GetPositionY    wxWindow_GetPositionY()

virtual wxRect GetRect() const
virtual int GetScrollThumb(int orientation)
virtual int GetScrollPos(int orientation)
virtual int GetScrollRange(int orientation)
// virtual void GetSize(int* width, int* height) const
%{
    void wxWindow_GetSize()
    {
        int width, height;
        ((wxWindow *)wTheCall->self->ptr)->GetSize(&width, &height);
        wWrapDerefArgs();
        wStackPushNumber( (wNumber)width );
        wStackPushNumber( (wNumber)height );
    }

    void wxWindow_GetSizeWidth()
    {
        int width, height;
        ((wxWindow *)wTheCall->self->ptr)->GetSize(&width, &height);
        wWrapDerefArgs();
        wStackPushNumber( (wNumber)width );
    }

    void wxWindow_GetSizeHeight()
    {
        int width, height;
        ((wxWindow *)wTheCall->self->ptr)->GetSize(&width, &height);
        wWrapDerefArgs();
        wStackPushNumber( (wNumber)height );
    }


%}
%method GetSize         wxWindow_GetSize()
%method GetSizeWidth    wxWindow_GetSizeWidth()
%method GetSizeHeight   wxWindow_GetSizeHeight()

wxSizer * GetSizer() const
// Error: last arg does not exist
// virtual void GetTextExtent(const wxString& string, int* x, int* y, int* descent = NULL, int* externalLeading = NULL, const wxFont* font = NULL, bool use16 = FALSE) const
// virtual void GetTextExtent(const wxString& string, int* x, int* y, int* descent = NULL, int* externalLeading = NULL, const wxFont* font = NULL ) const
%{
    void wxWindow_GetTextExtent()
    {
        // arg
        wxString string = wStackPopChar();

        int x, y, descent, externalLeading;
        ((wxWindow *)wTheCall->self->ptr)->GetTextExtent(string, &x, &y, &descent, &externalLeading);
        wWrapDerefArgs();
        wStackPushNumber( (wNumber)x );
        wStackPushNumber( (wNumber)y );
        wStackPushNumber( (wNumber)descent );
        wStackPushNumber( (wNumber)externalLeading );
    }

    void wxWindow_GetTextExtentX()
    {
        // arg
        wxString string = wStackPopChar();

        int x, y, descent, externalLeading;
        ((wxWindow *)wTheCall->self->ptr)->GetTextExtent(string, &x, &y, &descent, &externalLeading);
        wWrapDerefArgs();
        wStackPushNumber( (wNumber)x );
    }

    void wxWindow_GetTextExtentY()
    {
        // arg
        wxString string = wStackPopChar();
        int x, y, descent, externalLeading;
        ((wxWindow *)wTheCall->self->ptr)->GetTextExtent(string, &x, &y, &descent, &externalLeading);
        wWrapDerefArgs();
        wStackPushNumber( (wNumber)y );
    }


    void wxWindow_GetTextExtentDescent()
    {
        // arg
        wxString string = wStackPopChar();
        int x, y, descent, externalLeading;
        ((wxWindow *)wTheCall->self->ptr)->GetTextExtent(string, &x, &y, &descent, &externalLeading);
        wWrapDerefArgs();
        wStackPushNumber( (wNumber)descent );
    }

    void wxWindow_GetTextExtentExternalLeading()
    {
        // arg
        wxString string = wStackPopChar();
        int x, y, descent, externalLeading;
        ((wxWindow *)wTheCall->self->ptr)->GetTextExtent(string, &x, &y, &descent, &externalLeading);
        wWrapDerefArgs();
        wStackPushNumber( (wNumber)externalLeading );
    }


%}
%method GetTextExtent                   wxWindow_GetTextExtent( const wxString &string)
%method GetTextExtentX                  wxWindow_GetTextExtentX( const wxString &string)
%method GetTextExtentY                  wxWindow_GetTextExtentY( const wxString &string)
%method GetTextExtentDescent            wxWindow_GetTextExtentX( const wxString &string)
%method GetTextExtentExternalLeading    wxWindow_GetTextExtentX( const wxString &string)

virtual wxString GetTitle()
virtual wxRegion GetUpdateRegion() const
wxToolTip* GetToolTip() const
wxValidator* GetValidator() const
wxSize GetVirtualSize() const
long GetWindowStyleFlag() const
virtual bool HasCapture() const
bool Hide()
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
// FIXME
// virtual bool LoadFromResource(wxWindow* parent, const wxString& resourceName, const wxResourceTable* resourceTable = NULL)
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
// virtual void Refresh(const wxRect& rect)
virtual void ReleaseMouse()
virtual void RemoveChild(wxWindow* child)
bool RemoveEventHandler(wxEvtHandler *handler)
virtual bool Reparent(wxWindow* newParent)
virtual wxPoint ScreenToClient(const wxPoint& pt) const
%rename ScreenToClientXY virtual void ScreenToClient(int* x, int* y) const
virtual bool ScrollLines(int lines)
virtual bool ScrollPages(int pages)
virtual void ScrollWindow(int dx, int dy, const wxRect* rect = NULL)
virtual void SetAcceleratorTable(const wxAcceleratorTable& accel)
void SetAutoLayout(bool autoLayout)
%alias SetBackgroundColor virtual void SetBackgroundColour(const wxColour& colour)
void SetCaret(wxCaret *caret) const
virtual void SetClientSize(const wxSize& size)
%rename SetClientSizeWH virtual void SetClientSize(int width, int height)
void SetContainingSizer(wxSizer* sizer)
virtual void SetCursor(const wxCursor&cursor)
void SetConstraints(wxLayoutConstraints* constraints)
void SetDropTarget(wxDropTarget* target)
void SetEventHandler(wxEvtHandler* handler)
void SetExtraStyle(long exStyle)
virtual void SetFocus()
virtual void SetFocusFromKbd()
void SetFont(const wxFont& font)
%alias SetForegroundColor virtual void SetForegroundColour(const wxColour& colour)
virtual void SetHelpText(const wxString& helpText)
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
void SetSizerAndFit(wxSizer* sizer, bool deleteOld=TRUE)
virtual void SetTitle(const wxString& title)
virtual void SetThemeEnabled(bool enable)
virtual void SetValidator(const wxValidator& validator)
void SetToolTip(const wxString& tip)
void SetWindowStyle(long style)
virtual void SetWindowStyleFlag(long style)
virtual bool Show(bool show)
virtual void Thaw()
virtual bool TransferDataFromWindow()
virtual bool TransferDataToWindow()
virtual void Update()
virtual bool Validate()
void WarpPointer(int x, int y)

// %num wxCENTER_FRAME
%num %alias wxCENTER_ON_SCREEN wxCENTRE_ON_SCREEN
%num wxVSCROLL 
%num wxHSCROLL 
%num wxCAPTION 
%num wxDOUBLE_BORDER 
%num wxSUNKEN_BORDER 
%num wxRAISED_BORDER 
%num wxBORDER 
%num wxSIMPLE_BORDER 
%num wxSTATIC_BORDER 
%num wxTRANSPARENT_WINDOW 
%num wxNO_BORDER 
%num %alias wxUSER_COLORS wxUSER_COLOURS 
%num wxNO_3D 
%num wxCLIP_CHILDREN 
%num wxCLIP_SIBLINGS 
%num wxTAB_TRAVERSAL 
%num wxWANTS_CHARS 
%num wxRETAINED 
%num wxBACKINGSTORE 
%num wxNO_FULL_REPAINT_ON_RESIZE 
%num wxWS_EX_VALIDATE_RECURSIVELY 
%num wxSTAY_ON_TOP 
%num wxICONIZE 
%num wxMINIMIZE 
%num wxMAXIMIZE 
%num wxSYSTEM_MENU 
%num wxMINIMIZE_BOX 
%num wxMAXIMIZE_BOX 
%num wxTINY_CAPTION_HORIZ 
%num wxTINY_CAPTION_VERT 
%num wxRESIZE_BORDER 
%num wxDIALOG_NO_PARENT 
%num wxFRAME_NO_TASKBAR 
%num wxFRAME_TOOL_WINDOW 
%num wxRESIZE_BOX 
%num wxTHICK_FRAME 
%num wxDIALOG_MODAL 
%num wxDIALOG_MODELESS 
%num wxFRAME_FLOAT_ON_PARENT 
%num wxFRAME_EX_CONTEXTHELP 
%num wxDIALOG_EX_CONTEXTHELP 
%num wxFRAME_NO_WINDOW_MENU 
%num wxDEFAULT_FRAME_STYLE 
%num wxDEFAULT_DIALOG_STYLE


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


%class wxDialog, wxWindow
wxDialog(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE, const wxString& name = "dialogBox")
~wxDialog()
%alias Center void Centre(int direction = wxBOTH)
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
// wxFindReplaceData

%class wxFindReplaceData, wxObject
%include "wx/fdrepdlg.h"

wxFindReplaceData(wxUint32 flags = 0)
const wxString& GetFindString()
const wxString& GetReplaceString()
int GetFlags() const
void SetFlags(wxUint32 flags)
void SetFindString(const wxString& str)
void SetReplaceString(const wxString& str)


///////////////////////////////////////////////////////////////////////////////
// wxFindReplaceDialog

%class wxFindReplaceDialog, wxDialog
%include "wx/fdrepdlg.h"

wxFindReplaceDialog(wxWindow * parent, wxFindReplaceData* data, const wxString& title, int style = 0)
~wxFindReplaceDialog()
bool Create(wxWindow * parent, wxFindReplaceData* data, const wxString& title, int style = 0)
const wxFindReplaceData* GetData() const

%num wxFR_DOWN
%num wxFR_WHOLEWORD
%num wxFR_MATCHCASE
%num wxFR_REPLACEDIALOG
%num wxFR_NOUPDOWN
%num wxFR_NOMATCHCASE
%num wxFR_NOWHOLEWORD

%num wxEVT_COMMAND_FIND
%num wxEVT_COMMAND_FIND_NEXT
%num wxEVT_COMMAND_FIND_REPLACE
%num wxEVT_COMMAND_FIND_REPLACE_ALL
%num wxEVT_COMMAND_FIND_CLOSE

///////////////////////////////////////////////////////////////////////////////
// wxFrame
%class wxFrame, wxWindow

wxFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_FRAME_STYLE, const wxString& name = "frame")
~wxFrame()
%alias Center void Centre(int direction = wxBOTH)
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
    void wxMDIParentFrame_GetClientSize()
    {
        int width, height;
        ((wxMDIParentFrame *)wTheCall->self->ptr)->GetClientSize(&width, &height);
        wWrapDerefArgs();
        wStackPushNumber( (wNumber)width );
        wStackPushNumber( (wNumber)height );
    }

    void wxMDIParentFrame_GetClientSizeWidth()
    {
        int width, height;
        ((wxMDIParentFrame *)wTheCall->self->ptr)->GetClientSize(&width, &height);
        wWrapDerefArgs();
        wStackPushNumber( (wNumber)width );
    }

    void wxMDIParentFrame_GetClientSizeHeight()
    {
        int width, height;
        ((wxMDIParentFrame *)wTheCall->self->ptr)->GetClientSize(&width, &height);
        wWrapDerefArgs();
        wStackPushNumber( (wNumber)height );
    }

%}
%method GetClientSize       wxMDIParentFrame_GetClientSize()
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
    void wxScrolledWindow_GetScrollPixelsPerUnit()
    {
        int xUnit, yUnit;
        ((wxScrolledWindow *)wTheCall->self->ptr)->GetScrollPixelsPerUnit(&xUnit, &yUnit);
        wWrapDerefArgs();
        wStackPushNumber( (wNumber)xUnit );
        wStackPushNumber( (wNumber)yUnit );
    }

    void wxScrolledWindow_GetScrollPixelsPerUnitX()
    {
        int xUnit, yUnit;
        ((wxScrolledWindow *)wTheCall->self->ptr)->GetScrollPixelsPerUnit(&xUnit, &yUnit);
        wWrapDerefArgs();
        wStackPushNumber( (wNumber)xUnit );
    }

    void wxScrolledWindow_GetScrollPixelsPerUnitY()
    {
        int xUnit, yUnit;
        ((wxScrolledWindow *)wTheCall->self->ptr)->GetScrollPixelsPerUnit(&xUnit, &yUnit);
        wWrapDerefArgs();
        wStackPushNumber( (wNumber)yUnit );
    }
%}
%method GetScrollPixelsPerUnit  wxScrolledWindow_GetScrollPixelsPerUnit()
%method GetScrollPixelsPerUnitX wxScrolledWindow_GetScrollPixelsPerUnitX()
%method GetScrollPixelsPerUnitY wxScrolledWindow_GetScrollPixelsPerUnitY()

// void GetVirtualSize(int* x, int* y) const
%{
    void wxScrolledWindow_GetVirtualSize()
    {
        int x, y;
        ((wxScrolledWindow *)wTheCall->self->ptr)->GetVirtualSize(&x, &y);
        wWrapDerefArgs();
        wStackPushNumber( (wNumber)x );
        wStackPushNumber( (wNumber)y );
    }

    void wxScrolledWindow_GetVirtualSizeX()
    {
        int x, y;
        ((wxScrolledWindow *)wTheCall->self->ptr)->GetVirtualSize(&x, &y);
        wWrapDerefArgs();
        wStackPushNumber( (wNumber)x );
    }

    void wxScrolledWindow_GetVirtualSizeY()
    {
        int x, y;
        ((wxScrolledWindow *)wTheCall->self->ptr)->GetVirtualSize(&x, &y);
        wWrapDerefArgs();
        wStackPushNumber( (wNumber)y );
    }
%}
%method GetVirtualSize      wxScrolledWindow_GetVirtualSize()
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
    void wxScrolledWindow_GetViewStart()
    {
        int x, y;
        ((wxScrolledWindow *)wTheCall->self->ptr)->GetViewStart(&x, &y);
        wWrapDerefArgs();
        wStackPushNumber( (wNumber)x );
        wStackPushNumber( (wNumber)y );
    }

    void wxScrolledWindow_GetViewStartX()
    {
        int x, y;
        ((wxScrolledWindow *)wTheCall->self->ptr)->GetViewStart(&x, &y);
        wWrapDerefArgs();
        wStackPushNumber( (wNumber)x );
    }

    void wxScrolledWindow_GetViewStartY()
    {
        int x, y;
        ((wxScrolledWindow *)wTheCall->self->ptr)->GetViewStart(&x, &y);
        wWrapDerefArgs();
        wStackPushNumber( (wNumber)y );
    }
%}
%method GetViewStart      wxScrolledWindow_GetViewStart()
%method GetViewStartX     wxScrolledWindow_GetViewStartX()
%method GetViewStartY     wxScrolledWindow_GetViewStartY()

///////////////////////////////////////////////////////////////////////////////
// wxHtmlFilter

%class wxHtmlFilter, wxObject
%include "wx/html/htmlfilt.h"

// wxFSFile not wrapped yet
//bool CanRead(const wxFSFile& file)
//wxString ReadFile(const wxFSFile& file)


///////////////////////////////////////////////////////////////////////////////
// wxHtmlWindow

%class wxHtmlWindow, wxScrolledWindow
%include "wx/html/htmlwin.h"

wxHtmlWindow(wxWindow *parent, wxWindowID id = -1, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxHW_SCROLLBAR_AUTO, const wxString& name = "htmlWindow")
static void AddFilter(wxHtmlFilter *filter)
bool AppendToPage(const wxString& source)
//wxHtmlContainerCell* GetInternalRepresentation() const
wxString GetOpenedAnchor()
wxString GetOpenedPage()
wxString GetOpenedPageTitle()
wxFrame* GetRelatedFrame() const
bool HistoryBack()
bool HistoryCanBack()
bool HistoryCanForward()
void HistoryClear()
bool HistoryForward()
// FIXME: wxFileName not implemented yet
// virtual bool LoadFile(const wxFileName& filename)
virtual bool LoadPage(const wxString& location)
// virtual void OnCellClicked(wxHtmlCell *cell, wxCoord x, wxCoord y, const wxMouseEvent& event)
// virtual void OnCellMouseHover(wxHtmlCell *cell, wxCoord x, wxCoord y)
// virtual void OnLinkClicked(const wxHtmlLinkInfo& link)
// virtual wxHtmlOpeningStatus OnOpeningURL(wxHtmlURLType type,const wxString& url, wxString *redirect)
// virtual void OnSetTitle(const wxString& title)
virtual void ReadCustomization(wxConfigBase *cfg, wxString path = wxEmptyString)
void SetBorders(int b)
void SetFonts(wxString normal_face, wxString fixed_face, const int *sizes = NULL)
bool SetPage(const wxString& source)
void SetRelatedFrame(wxFrame* frame, const wxString& format)
void SetRelatedStatusBar(int bar)
virtual void WriteCustomization(wxConfigBase *cfg, wxString path = wxEmptyString)

// wxHtmlURL types
%num wxHTML_URL_PAGE
%num wxHTML_URL_IMAGE
%num wxHTML_URL_OTHER

// wxHTML_REDIRECT
%num wxHTML_OPEN
%num wxHTML_BLOCK
%num wxHTML_REDIRECT



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
        int y = wStackPopNumber();
        int x = wStackPopNumber();
        result = ((wxGrid *)wTheCall->self->ptr)->CellHitTest(x, y, &row, &col)
        wWrapDerefArgs();
        wStackPushNumber( (wNumber)result );
        wStackPushNumber( (wNumber)row );
        wStackPushNumber( (wNumber)col );
    }

    void wxGrid_CellHitTestRow()
    {
        int row, col;
        int y = wStackPopNumber();
        int x = wStackPopNumber();
        ((wxGrid *)wTheCall->self->ptr)->CellHitTest(x, y, &row, &col)
        wWrapDerefArgs();
        wStackPushNumber( (wNumber)row );
    }

    void wxGrid_CellHitTestCol()
    {
        int row, col;
        int y = wStackPopNumber();
        int x = wStackPopNumber();
        ((wxGrid *)wTheCall->self->ptr)->CellHitTest(x, y, &row, &col)
        wWrapDerefArgs();
        wStackPushNumber( (wNumber)col );
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
// wxDateTime

%class wxDateTime
%include "wx/datetime.h"

wxDateTime()
// FIXME: these ctor declarations are wrong
// %ctor wxDateTimeFromTimeT wxDateTime(time_t timet)
// %ctor wxDateTimeFromJDN wxDateTime(double jdn)
// %ctor wxDateTimeFromHMS wxDateTime(wxDateTime_t hour, wxDateTime_t minute = 0, wxDateTime_t second = 0, wxDateTime_t millisec = 0)
// FIXME: "month should be optional"  Hrm?
// %ctor wxDateTimeFromDMYwxDateTime& wxDateTime(wxDateTime_t day, wxDateTime::Month month = wxDateTime::Inv_Month, int wxDateTime::Inv_Year, wxDateTime_t hour = 0, wxDateTime_t minute = 0, wxDateTime_t second = 0, wxDateTime_t millisec = 0)
wxDateTime& SetToCurrent()
%rename SetTimeT wxDateTime& Set(time_t timet)
%rename SetJDN wxDateTime& Set(double jdn)
%rename SetHMS wxDateTime& Set(wxDateTime_t hour, wxDateTime_t minute = 0, wxDateTime_t second = 0, wxDateTime_t millisec = 0)
wxDateTime& Set(wxDateTime_t day, wxDateTime::Month month = wxDateTime::Inv_Month, int year = wxDateTime::Inv_Year, wxDateTime_t hour = 0, wxDateTime_t minute = 0, wxDateTime_t second = 0, wxDateTime_t millisec = 0)
wxDateTime& ResetTime()
wxDateTime& SetYear(int year)
wxDateTime& SetMonth(wxDateTime::Month month)
wxDateTime& SetDay(wxDateTime_t day)
wxDateTime& SetHour(wxDateTime_t hour)
wxDateTime& SetMinute(wxDateTime_t minute)
wxDateTime& SetSecond(wxDateTime_t second)
wxDateTime& SetMillisecond(wxDateTime_t millisecond)
bool IsValid() const
// FIXME: what's the problem here?
// Tm GetTm(const TimeZone tz = wxDateTime::Local) const
time_t GetTicks() const
int GetYear(const TimeZone tz = wxDateTime::Local) const
int GetMonth(const TimeZone tz = wxDateTime::Local) const
wxDateTime_t GetDay(const TimeZone tz = wxDateTime::Local) const
// FIXME: doc don't show wxPython name
%rename GetWeekDayTZ wxDateTime::WeekDay GetWeekDay(const TimeZone tz = wxDateTime::Local) const
wxDateTime_t GetHour(const TimeZone tz = wxDateTime::Local) const
wxDateTime_t GetMinute(const TimeZone tz = wxDateTime::Local) const
wxDateTime_t GetSecond(const TimeZone tz = wxDateTime::Local) const
wxDateTime_t GetMillisecond(const TimeZone tz = wxDateTime::Local) const
wxDateTime_t GetDayOfYear(const TimeZone tz = wxDateTime::Local) const
wxDateTime_t GetWeekOfYear(wxDateTime::WeekFlags flags = wxDateTime::Monday_First, const TimeZone tz = wxDateTime::Local) const
wxDateTime_t GetWeekOfMonth(wxDateTime::WeekFlags flags = wxDateTime::Monday_First, const TimeZone tz = wxDateTime::Local) const
bool IsWorkDay(wxDateTime::Country country = wxDateTime::Country_Default) const
// FIXME: appears to be missing under MSW 2.4.2
// bool IsGregorianDate(wxDateTime::GregorianAdoption country = wxDateTime::Gr_Standard) const
wxDateTime& SetFromDOS(unsigned long ddt)
unsigned long GetAsDOS() const
bool IsEqualTo(const wxDateTime& datetime) const
bool IsEarlierThan(const wxDateTime& datetime) const
bool IsLaterThan(const wxDateTime& datetime) const
bool IsStrictlyBetween(const wxDateTime& t1, const wxDateTime& t2) const
bool IsBetween(const wxDateTime& t1, const wxDateTime& t2) const
bool IsSameDate(const wxDateTime& dt) const
bool IsSameTime(const wxDateTime& dt) const
bool IsEqualUpTo(const wxDateTime& dt, const wxTimeSpan& ts) const
%rename AddTS wxDateTime Add(const wxTimeSpan& diff) const
%rename SubtractTS wxDateTime Subtract(const wxTimeSpan& diff) const
%rename AddDS wxDateTime Add(const wxDateSpan& diff) const
%rename SubtractDS wxDateTime Subtract(const wxDateSpan& diff) const
wxTimeSpan Subtract(const wxDateTime& dt) const
//const wxChar * ParseRfc822Date(const wxChar* date)
//const wxChar * ParseFormat(const wxChar *date, const wxChar *format = "%c", const wxDateTime& dateDef = wxDefaultDateTime)
//const wxChar * ParseDateTime(const wxChar *datetime)
//const wxChar * ParseDate(const wxChar *date)
//const wxChar * ParseTime(const wxChar *time)
wxString ParseRfc822Date(const char* date)
wxString ParseFormat(const char *date, const char *format = "%c", const wxDateTime& dateDef = wxDefaultDateTime)
wxString ParseDateTime(const char *datetime)
wxString ParseDate(const char *date)
wxString ParseTime(const char *time)
// FIXME: changed wxChar to char
wxString Format(const char *format = "%c", const TimeZone tz = wxDateTime::Local) const
wxString FormatDate() const
wxString FormatTime() const
wxString FormatISODate() const
wxString FormatISOTime() const
wxDateTime& SetToWeekDayInSameWeek(wxDateTime::WeekDay weekday, wxDateTime::WeekFlags flags = wxDateTime::Monday_First)
wxDateTime GetWeekDayInSameWeek(wxDateTime::WeekDay weekday, wxDateTime::WeekFlags flags = wxDateTime::Monday_First) const
wxDateTime& SetToNextWeekDay(wxDateTime::WeekDay weekday)
wxDateTime GetNextWeekDay(wxDateTime::WeekDay weekday) const
wxDateTime& SetToPrevWeekDay(wxDateTime::WeekDay weekday)
wxDateTime GetPrevWeekDay(wxDateTime::WeekDay weekday) const
bool SetToWeekDay(wxDateTime::WeekDay weekday, int n = 1, wxDateTime::Month month = wxDateTime::Inv_Month, int year = wxDateTime::Inv_Year)

wxDateTime GetWeekDay(wxDateTime::WeekDay weekday, int n = 1, wxDateTime::Month month = wxDateTime::Inv_Month, int year = wxDateTime::Inv_Year) const
bool SetToLastWeekDay(wxDateTime::WeekDay weekday, wxDateTime::Month month = wxDateTime::Inv_Month, int year = wxDateTime::Inv_Year)
wxDateTime GetLastWeekDay(wxDateTime::WeekDay weekday, wxDateTime::Month month = wxDateTime::Inv_Month, int year = wxDateTime::Inv_Year)
bool SetToTheWeek(wxDateTime_t numWeek, wxDateTime::WeekDay weekday = wxDateTime::Mon, wxDateTime::WeekFlags flags = wxDateTime::Monday_First)
wxDateTime GetWeek(wxDateTime_t numWeek, wxDateTime::WeekDay weekday = wxDateTime::Mon, wxDateTime::WeekFlags flags = wxDateTime::Monday_First) const
wxDateTime& SetToLastMonthDay(wxDateTime::Month month = wxDateTime::Inv_Month, int year = wxDateTime::Inv_Year)
wxDateTime GetLastMonthDay(wxDateTime::Month month = wxDateTime::Inv_Month, int year = wxDateTime::Inv_Year) const
wxDateTime& SetToYearDay(wxDateTime_t yday)
wxDateTime GetYearDay(wxDateTime_t yday) const
double GetJulianDayNumber() const
double GetJDN() const
double GetModifiedJulianDayNumber() const
double GetMJD() const
double GetRataDie() const
wxDateTime ToTimezone(const TimeZone tz, bool noDST = FALSE) const
wxDateTime& MakeTimezone(const TimeZone tz, bool noDST = FALSE)
wxDateTime ToGMT(bool noDST = FALSE) const
wxDateTime& MakeGMT(bool noDST = FALSE)
int IsDST(wxDateTime::Country country = wxDateTime::Country_Default) const

// these are static, and not really class members
%builtin %rename wxDateTime_ConvertYearToBC static int wxDateTime::ConvertYearToBC(int year)
// FIXME: need to create wrappers for GetAmPmStrings
// %builtin %rename wxDateTime_GetAmPmStrings static void wxDateTime::GetAmPmStrings(wxString *am, wxString *pm)
%builtin %rename wxDateTime_GetBeginDST static wxDateTime wxDateTime::GetBeginDST(int year = wxDateTime::Inv_Year, wxDateTime::Country country = wxDateTime::Country_Default)
%builtin %rename wxDateTime_GetCountry static wxDateTime::Country wxDateTime::GetCountry()
%builtin %rename wxDateTime_GetCurrentYear static int wxDateTime::GetCurrentYear(wxDateTime::Calendar cal = wxDateTime::Gregorian)
%builtin %rename wxDateTime_GetCurrentMonth static int wxDateTime::GetCurrentMonth(wxDateTime::Calendar cal = wxDateTime::Gregorian)
%builtin %rename wxDateTime_GetCentury static int wxDateTime::GetCentury(int year = wxDateTime::Inv_Year)
%builtin %rename wxDateTime_GetEndDST static wxDateTime wxDateTime::GetEndDST(int year = wxDateTime::Inv_Year, wxDateTime::Country country = wxDateTime::Country_Default)
%builtin %rename wxDateTime_GetMonthName static wxString wxDateTime::GetMonthName(int month, wxDateTime::NameFlags flags = wxDateTime::Name_Full)
%builtin %rename wxDateTime_GetNumberOfDaysInYear static wxDateTime_t wxDateTime::GetNumberOfDays(int year, wxDateTime::Calendar cal = wxDateTime::Gregorian)
%builtin %rename wxDateTime_GetNumberOfDaysInMonth static wxDateTime_t wxDateTime::GetNumberOfDays(wxDateTime::Month month, int year = wxDateTime::Inv_Year, wxDateTime::Calendar cal = wxDateTime::Gregorian)
%builtin %rename wxDateTime_GetWeekDayName static wxString wxDateTime::GetWeekDayName(wxDateTime::WeekDay weekday, wxDateTime::NameFlags flags = wxDateTime::Name_Full)
%builtin %rename wxDateTime_IsLeapYear static bool wxDateTime::IsLeapYear(int year = wxDateTime::Inv_Year, wxDateTime::Calendar cal = wxDateTime::Gregorian)
%builtin %rename wxDateTime_IsWestEuropeanCountry static bool wxDateTime::IsWestEuropeanCountry(wxDateTime::Country country = wxDateTime::Country_Default)
%builtin %rename wxDateTime_IsDSTApplicable static bool wxDateTime::IsDSTApplicable(int year = wxDateTime::Inv_Year, wxDateTime::Country country = wxDateTime::Country_Default)
%builtin %rename wxDateTime_wxDateTime static wxDateTime wxDateTime::Now()
%builtin %rename wxDateTime_SetCountry void wxDateTime::SetCountry(wxDateTime::Country country)
%builtin %rename wxDateTime_Today static wxDateTime wxDateTime::Today()
%builtin %rename wxDateTime_UNow static wxDateTime wxDateTime::UNow()


%num %rename wxTZ_Local wxDateTime::Local
%num %rename wxTZ_GTM_1 wxDateTime::GMT_1
%num %rename wxTZ_GTM_2 wxDateTime::GMT_2
%num %rename wxTZ_GTM_3 wxDateTime::GMT_3
%num %rename wxTZ_GTM_4 wxDateTime::GMT_4
%num %rename wxTZ_GTM_5 wxDateTime::GMT_5
%num %rename wxTZ_GTM_6 wxDateTime::GMT_6
%num %rename wxTZ_GTM_7 wxDateTime::GMT_7
%num %rename wxTZ_GTM_8 wxDateTime::GMT_8
%num %rename wxTZ_GTM_9 wxDateTime::GMT_9
%num %rename wxTZ_GTM_10 wxDateTime::GMT_10
%num %rename wxTZ_GTM_11 wxDateTime::GMT_11
%num %rename wxTZ_GTM_12 wxDateTime::GMT_12
%num %rename wxTZ_GTM0 wxDateTime::GMT0
%num %rename wxTZ_GTM1 wxDateTime::GMT1
%num %rename wxTZ_GTM2 wxDateTime::GMT2
%num %rename wxTZ_GTM3 wxDateTime::GMT3
%num %rename wxTZ_GTM4 wxDateTime::GMT4
%num %rename wxTZ_GTM5 wxDateTime::GMT5
%num %rename wxTZ_GTM6 wxDateTime::GMT6
%num %rename wxTZ_GTM7 wxDateTime::GMT7
%num %rename wxTZ_GTM8 wxDateTime::GMT8
%num %rename wxTZ_GTM9 wxDateTime::GMT9
%num %rename wxTZ_GTM10 wxDateTime::GMT10
%num %rename wxTZ_GTM11 wxDateTime::GMT11
%num %rename wxTZ_GTM12 wxDateTime::GMT12

%num %rename wxTZ_WET wxDateTime::WET
%num %rename wxTZ_WESTT wxDateTime::WEST
%num %rename wxTZ_CET wxDateTime::CET
%num %rename wxTZ_CEST wxDateTime::CEST
%num %rename wxTZ_EET wxDateTime::EET
%num %rename wxTZ_EEST wxDateTime::EEST
%num %rename wxTZ_MSK wxDateTime::MSK
%num %rename wxTZ_MSD wxDateTime::MSD

%num %rename wxTZ_AST wxDateTime::AST
%num %rename wxTZ_ADT wxDateTime::ADT
%num %rename wxTZ_EST wxDateTime::EST
%num %rename wxTZ_EDT wxDateTime::EDT
%num %rename wxTZ_CST wxDateTime::CST
%num %rename wxTZ_CDT wxDateTime::CDT
%num %rename wxTZ_MST wxDateTime::MST
%num %rename wxTZ_MDTT wxDateTime::MDT
%num %rename wxTZ_PST wxDateTime::PST
%num %rename wxTZ_PDT wxDateTime::PDT
%num %rename wxTZ_HST wxDateTime::HST
%num %rename wxTZ_SKST wxDateTime::AKST
%num %rename wxTZ_AKDT wxDateTime::AKST
%num %rename wxTZ_A_WST wxDateTime::A_WST
%num %rename wxTZ_A_CST wxDateTime::A_CST
%num %rename wxTZ_A_EST wxDateTime::A_EST
%num %rename wxTZ_A_ESST wxDateTime::A_ESST

%num %rename wxDateTime_Jan wxDateTime::Jan
%num %rename wxDateTime_Feb wxDateTime::Feb
%num %rename wxDateTime_Mar wxDateTime::Mar
%num %rename wxDateTime_Apr wxDateTime::Apr
%num %rename wxDateTime_May wxDateTime::May
%num %rename wxDateTime_Jun wxDateTime::Jun
%num %rename wxDateTime_Jul wxDateTime::Jul
%num %rename wxDateTime_Aug wxDateTime::Aug
%num %rename wxDateTime_Sep wxDateTime::Sep
%num %rename wxDateTime_Oct wxDateTime::Oct
%num %rename wxDateTime_Nov wxDateTime::Nov
%num %rename wxDateTime_Dec wxDateTime::Dec
%num %rename wxDateTime_Inv_Month wxDateTime::Inv_Month

%num %rename wxDateTime_Sun wxDateTime::Sun
%num %rename wxDateTime_Mon wxDateTime::Mon
%num %rename wxDateTime_Tue wxDateTime::Tue
%num %rename wxDateTime_Wed wxDateTime::Wed
%num %rename wxDateTime_Thu wxDateTime::Thu
%num %rename wxDateTime_Fri wxDateTime::Fri
%num %rename wxDateTime_Sat wxDateTime::Sat
%num %rename wxDateTime_Inv_WeekDay wxDateTime::Inv_WeekDay

%num %rename wxDateTime_Inv_Year wxDateTime::Inv_Year

%num %rename wxDateTime_Name_Full wxDateTime::Name_Full
%num %rename wxDateTime_Name_Abbr wxDateTime::Name_Abbr
	
%num %rename wxDateTime_Gregorian wxDateTime::Gregorian
%num %rename wxDateTime_Julian wxDateTime::Julian

%num %rename wxDateTime_Unknown wxDateTime::Country_Unknown
%num %rename wxDateTime_Default wxDateTime::Country_Default
%num %rename wxDateTime_WesternEurope_Start wxDateTime::Country_WesternEurope_Start
%num %rename wxDateTime_EEC wxDateTime::Country_EEC
%num %rename wxDateTime_France wxDateTime::France
%num %rename wxDateTime_Germany wxDateTime::Germany
%num %rename wxDateTime_UK wxDateTime::UK
%num %rename wxDateTime_Russia wxDateTime::Russia
%num %rename wxDateTime_USA wxDateTime::USA
	
%num %rename wxDateTime_Default_First wxDateTime::Default_First
%num %rename wxDateTime_Monday_First wxDateTime::Monday_First
%num %rename wxDateTime_Sunday_First wxDateTime::Monday_First



///////////////////////////////////////////////////////////////////////////////
// wxCalendarCtrl

%class wxCalendarCtrl, wxControl
%include "wx/calctrl.h"

wxCalendarCtrl(wxWindow* parent, wxWindowID id, const wxDateTime& date = wxDefaultDateTime, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxCAL_SHOW_HOLIDAYS, const wxString& name = wxCalendarNameStr)
bool Create(wxWindow* parent, wxWindowID id, const wxDateTime& date = wxDefaultDateTime, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxCAL_SHOW_HOLIDAYS, const wxString& name = wxCalendarNameStr)
~wxCalendarCtrl()
void SetDate(const wxDateTime& date)
const wxDateTime& GetDate() const
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
int GetCount() const
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
// Deprecated, use GetCount instead
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
// wxListItem

%class wxListItem, wxObject
%include "wx/listctrl.h"

wxListItem()
void Clear()
wxListColumnFormat GetAlign() const
wxColour GetBackgroundColour() const
int GetColumn() const
long GetData() const
wxFont GetFont() const
long GetId() const
int GetImage() const
long GetMask() const
long GetState() const
const wxString& GetText() const
wxColour GetTextColour() const
int GetWidth() const
void SetAlign(wxListColumnFormat align)
%alias SetBackgroundColor void SetBackgroundColour(const wxColour& colBack)
void SetColumn(int col)
void SetData(long data)
// void SetData(void* data)
void SetFont(const wxFont& font)
void SetId(long id)
void SetImage(int image)
void SetMask(long mask)
void SetState(long state)
void SetStateMask(long stateMask)
void SetText(const wxString& text)
%alias SetTextColor void SetTextColour(const wxColour& colText)
void SetWidth(int width)

%num wxLIST_MASK_STATE
%num wxLIST_MASK_TEXT
%num wxLIST_MASK_IMAGE
%num wxLIST_MASK_DATA
%num wxLIST_MASK_WIDTH
%num wxLIST_MASK_FORMAT

%num wxLIST_FORMAT_LEFT
%num wxLIST_FORMAT_RIGHT
%num wxLIST_FORMAT_CENTRE
%num %alias wxLIST_FORMAT_CENTER

// commented items are win32 only
// %num wxLIST_STATE_DONTCARE
// %num wxLIST_STATE_DROPHILITED
%num wxLIST_STATE_FOCUSED
%num wxLIST_STATE_SELECTED
// %num wxLIST_STATE_CUT


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
// bool GetItemRect(long item, wxRect& rect, int code = wxLIST_RECT_BOUNDS) const
%{
    void wxListCtrl_GetItemRect()
    {
        int code = wStackPopNumber();
        long item = wStackPopNumber();

        wxRect *returns;
        ((wxListCtrl *)wTheCall->self->ptr)->GetItemRect(item,*returns,code);
        wWrapDerefArgs();
        wWrapSetThis( _wxRect, (void *)returns );        
    }
%}
%method GetItemRect wxListCtrl_GetItemRect(long item, int code)

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
%{
    void wxTabCtrl_GetItemRect()
    {
        long item = wStackPopNumber();

        wxRect *returns;
        ((wxListCtrl *)wTheCall->self->ptr)->GetItemRect(item,*returns);
        wWrapDerefArgs();
        wWrapSetThis( _wxRect, (void *)returns );        
    }
%}
%method GetItemRect wxTabCtrl_GetItemRect(long item, int code)


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
    void wxTextCtrl_GetSelection()
    {
        long from, to;
        ((wxTextCtrl *)wTheCall->self->ptr)->GetSelection(&from, &to);
        wWrapDerefArgs();
        wStackPushNumber( (wNumber)from );
        wStackPushNumber( (wNumber)to );
    }

    void wxTextCtrl_GetSelectionFrom()
    {
        long from, to;
        ((wxTextCtrl *)wTheCall->self->ptr)->GetSelection(&from, &to);
        wWrapDerefArgs();
        wStackPushNumber( (wNumber)from );
    }

    void wxTextCtrl_GetSelectionTo()
    {
        long from, to;
        ((wxTextCtrl *)wTheCall->self->ptr)->GetSelection(&from, &to);
        wWrapDerefArgs();
        wStackPushNumber( (wNumber)to );
    }

%}
%method GetSelection        wxTextCtrl_GetSelection()
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

%num wxTE_PROCESS_ENTER 
%num wxTE_PROCESS_TAB 
%num wxTE_MULTILINE 
%num wxTE_PASSWORD 
%num wxTE_READONLY 
%num wxTE_RICH 
%num wxTE_RICH2 
%num wxTE_AUTO_URL 
%num wxTE_NOHIDESEL 
%num wxTE_LEFT 
%num %alias wxTE_CENTER wxTE_CENTRE
%num wxTE_RIGHT 
%num wxTE_DONTWRAP 
%num wxTE_LINEWRAP 
%num wxTE_WORDWRAP 


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
// wxTreeItemId GetFirstChild(const wxTreeItemId& item, long& cookie) const
// In wxPython the returned wxTreeItemId and the new cookie value are both returned as a 
// tuple containing the two values.
%{
    void wxTreeCtrl_GetFirstChild()
    {
    // long cookie
    long cookie = (long)wStackPopNumber();
    // const wxTreeItemId& item
    wxTreeItemId *item = (wxTreeItemId *)wStackPopObjectPtr( _wxTreeItemId);
    wxTreeItemId *returns = new wxTreeItemId(((wxTreeCtrl *)(wTheCall->self->ptr))->GetFirstChild(*item, cookie));
    wWrapDerefArgs();
    wWrapPushObject( _wxTreeItemId, W_TRUE, (void *)returns );    
    wStackPushNumber( (wNumber)cookie );
    }
%}
%method GetFirstChild wxTreeCtrl_GetFirstChild(const wxTreeItemId& item, long cookie) const

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

// In wxPython the returned wxTreeItemId and the new cookie value are both returned as
// a tuple containing the two values.
// wxTreeItemId GetNextChild(const wxTreeItemId& item, long& cookie) const
%{
    void wxTreeCtrl_GetNextChild()
    {
    // long cookie
    long cookie = (long)wStackPopNumber();
    // const wxTreeItemId& item
    wxTreeItemId *item = (wxTreeItemId *)wStackPopObjectPtr( _wxTreeItemId);
    // call GetNextChild
    // make a pointer via copy constructor
    wxTreeItemId *returns = new wxTreeItemId(((wxTreeCtrl *)(wTheCall->self->ptr))->GetNextChild(*item, cookie));
    wWrapDerefArgs();
    wWrapPushObject( _wxTreeItemId, W_TRUE, (void *)returns );    
    wStackPushNumber( (wNumber)cookie );
    }
%}
%method GetNextChild wxTreeCtrl_GetNextChild(const wxTreeItemId& item, long cookie) const

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
void SelectItem(const wxTreeItemId& item)
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

%num wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED
%num wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGING


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
%alias SetEnlargeAroundWindowCenter void SetEnlargeAroundWindowCentre(bool aroundwindow = TRUE)

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

%num  wxSASH_DRAG_NONE
%num  wxSASH_DRAG_DRAGGING
%num  wxSASH_DRAG_LEFT_DOWN
%num  wxSASH_TOP
%num  wxSASH_RIGHT
%num  wxSASH_BOTTOM
%num  wxSASH_LEFT
%num  wxSASH_NONE


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

%class wxColourDialog, wxDialog
%include "wx/colordlg.h"

wxColourDialog(wxWindow* parent, wxColourData* data = NULL)
%ctor wxColorDialog(wxWindow* parent, wxColourData* data = NULL)
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

%num wxOPEN
%num wxSAVE
%num wxOVERWRITE_PROMPT
%num wxHIDE_READONLY
%num wxFILE_MUST_EXIST
%num wxMULTIPLE
%num wxCHANGE_DIR


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

////////////////////////////////////////////////////////////
// wxFontData

%class wxFontData, wxObject
%include "wx/cmndata.h"

wxFontData()
~wxFontData()
void EnableEffects(bool enable)
bool GetAllowSymbols()
%alias GetColor wxColour& GetColour()
wxFont GetChosenFont()
bool GetEnableEffects()
wxFont GetInitialFont()
bool GetShowHelp()
void SetAllowSymbols(bool allowSymbols)
void SetChosenFont(const wxFont& font)
void SetColour(const wxColour& colour)
void SetInitialFont(const wxFont&font)
void SetRange(int min, int max)
void SetShowHelp(bool showHelp)

///////////////////////////////////////////////////////////////////////////////
// wxFontDialog

%class wxFontDialog, wxDialog
%include "wx/fontdlg.h"

wxFontDialog(wxWindow* parent, wxFontData* data = NULL)
~wxFontDialog()
wxFontData& GetFontData()
int ShowModal()

///////////////////////////////////////////////////////////////////////////////
// wxPageSetupDialogData

%class wxPageSetupDialogData, wxObject
%include "wx/cmndata.h"

wxPageSetupDialogData()
// FIX! Add alternate constructors
// wxPageSetupDialogData(wxPageSetupDialogData& data)
// wxPrintDialogData(wxPrintData& printData)
~wxPageSetupDialogData()
void EnableHelp(bool flag)
void EnableMargins(bool flag)
void EnableOrientation(bool flag)
void EnablePaper(bool flag)
void EnablePrinter(bool flag)
bool GetDefaultMinMargins() const
bool GetEnableMargins() const
bool GetEnableOrientation() const
bool GetEnablePaper() const
bool GetEnablePrinter() const
bool GetEnableHelp() const
bool GetDefaultInfo() const
wxPoint GetMarginTopLeft() const
wxPoint GetMarginBottomRight() const
wxPoint GetMinMarginTopLeft() const
wxPoint GetMinMarginBottomRight() const
wxPaperSize GetPaperId() const
wxSize GetPaperSize() const
wxPrintData& GetPrintData()
bool Ok() const
void SetDefaultInfo(bool flag)
void SetDefaultMinMargins(bool flag)
void SetMarginTopLeft(const wxPoint& pt)
void SetMarginBottomRight(const wxPoint& pt)
void SetMinMarginTopLeft(const wxPoint& pt)
void SetMinMarginBottomRight(const wxPoint& pt)
void SetPaperId(wxPaperSize& id)
void SetPaperSize(const wxSize& size)
void SetPrintData(const wxPrintData& printData)



///////////////////////////////////////////////////////////////////////////////
// wxPageSetupDialog

%class wxPageSetupDialog, wxDialog
%include "wx/printdlg.h"

wxPageSetupDialog(wxWindow* parent, wxPageSetupDialogData* data = NULL)
~wxPageSetupDialog()
wxPageSetupDialogData& GetPageSetupData()
// FIX! Appears to be missing from wxGTK
// bool Ok() const
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
void AppendCheckItem(int id, const wxString&  item, const wxString& helpString = "")
void AppendRadioItem(int id, const wxString&  item, const wxString& helpString = "")
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
void InsertCheckItem(size_t pos, int id, const wxString&  item, const wxString& helpString = "")
void InsertRadioItem(size_t pos, int id, const wxString&  item, const wxString& helpString = "")
void InsertSeparator(size_t pos)
bool IsChecked(int id) const
bool IsEnabled(int id) const
%rename PrependItem void Prepend( wxMenuItem *item)
void Prepend(int id, const wxString& item, const wxString& helpString = "", wxItemKind kind = wxITEM_NORMAL)
void PrependCheckItem(int id, const wxString&  item, const wxString& helpString = "")
void PrependRadioItem(int id, const wxString&  item, const wxString& helpString = "")
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
    void wxKeyEvent_GetPositionXY()
    {
        long x, y;
        ((wxKeyEvent *)wTheCall->self->ptr)->GetPosition(&x, &y);
        wWrapDerefArgs();
        wStackPushNumber( (wNumber)x );
        wStackPushNumber( (wNumber)y );
    }

    void wxKeyEvent_GetPositionX()
    {
        long x, y;
        ((wxKeyEvent *)wTheCall->self->ptr)->GetPosition(&x, &y);
        wWrapDerefArgs();
        wStackPushNumber( (wNumber)x );
    }

    void wxKeyEvent_GetPositionY()
    {
        long x, y;
        ((wxKeyEvent *)wTheCall->self->ptr)->GetPosition(&x, &y);
        wWrapDerefArgs();
        wStackPushNumber( (wNumber)y );
    }
%}
%method GetPositionXY   wxKeyEvent_GetPositionXY()
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
// wxJoystick

%class wxJoystick, wxObject
%include "wx/joystick.h"

%num wxJOYSTICK1
%num wxJOYSTICK2
// %num wxJOYSTICK3
// %num wxJOYSTICK4

wxJoystick(int joystick = wxJOYSTICK1)
~wxJoystick()
int GetButtonState() const
int GetManufacturerId() const
int GetMovementThreshold() const
int GetNumberAxes() const
int GetNumberButtons() const
int GetNumberJoysticks() const
int GetPollingMax() const
int GetPollingMin() const
int GetProductId() const
wxString GetProductName() const
wxPoint GetPosition() const
int GetPOVPosition() const
int GetPOVCTSPosition() const
int GetRudderMax() const
int GetRudderMin() const
int GetRudderPosition() const
int GetUMax() const
int GetUMin() const
int GetUPosition() const
int GetVMax() const
int GetVMin() const
int GetVPosition() const
int GetXMax() const
int GetXMin() const
int GetYMax() const
int GetYMin() const
int GetZMax() const
int GetZMin() const
int GetZPosition() const
bool HasPOV() const
bool HasPOV4Dir() const
bool HasPOVCTS() const
bool HasRudder() const
bool HasU() const
bool HasV() const
bool HasZ() const
bool IsOk() const
bool ReleaseCapture()
bool SetCapture(wxWindow* win, int pollingFreq = 0)
void SetMovementThreshold(int threshold)

///////////////////////////////////////////////////////////////////////////////
// %wxJoystickEvent

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

%num wxJOY_BUTTON_ANY

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
    void wxMouseEvent_GetPositionXY()
    {
        long x, y;
        ((wxMouseEvent *)wTheCall->self->ptr)->GetPosition(&x, &y);
        wWrapDerefArgs();
        wStackPushNumber( (wNumber)x );
        wStackPushNumber( (wNumber)y );
    }

    void wxMouseEvent_GetPositionX()
    {
        long x, y;
        ((wxMouseEvent *)wTheCall->self->ptr)->GetPosition(&x, &y);
        wWrapDerefArgs();
        wStackPushNumber( (wNumber)x );
    }

    void wxMouseEvent_GetPositionY()
    {
        long x, y;
        ((wxMouseEvent *)wTheCall->self->ptr)->GetPosition(&x, &y);
        wWrapDerefArgs();
        wStackPushNumber( (wNumber)y );
    }



%}
%method GetPositionXY   wxMouseEvent_GetPositionXY()
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
jbool m_checked
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
// wxSplitterEvent

%class wxSplitterEvent, wxNotifyEvent
%include "wx/splitter.h"

wxSplitterEvent(wxEventType eventType = wxEVT_NULL, wxSplitterWindow * splitter = NULL)
int GetSashPosition() const
int GetX() const
int GetY() const
wxWindow* GetWindowBeingRemoved() const
void SetSashPosition(int pos)




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

%num %alias wxCENTER wxCENTRE
%num wxHORIZONTAL
%num wxVERTICAL
%num wxBOTH
%num wxLEFT
%num wxRIGHT
%num wxUP
%num wxDOWN
%num wxTOP
%num wxBOTTOM
%num wxNORTH
%num wxSOUTH
%num wxWEST
%num wxEAST
%num wxALL
%num wxALIGN_NOT
%num %alias wxALIGN_CENTER_HORIZONTAL wxALIGN_CENTRE_HORIZONTAL
%num wxALIGN_LEFT
%num wxALIGN_TOP
%num wxALIGN_RIGHT
%num wxALIGN_BOTTOM
%num %alias wxALIGN_CENTER_VERTICAL wxALIGN_CENTRE_VERTICAL
%num %alias wxALIGN_CENTER wxALIGN_CENTRE
%num wxSTRETCH_NOT
%num wxSHRINK
%num wxGROW
%num wxEXPAND
%num wxSHAPED
%num wxADJUST_MINSIZE
%num wxDEFAULT



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
// void Above(wxWindow *otherWin, int margin = 0)
void Absolute(int value)
void AsIs()
// void Below(wxWindow *otherWin, int margin = 0)
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

%ptr wxNORMAL_FONT
%ptr wxSMALL_FONT
%ptr wxITALIC_FONT
%ptr wxSWISS_FONT
%ptr wxNullFont

%num wxDECORATIVE
%num wxROMAN
%num wxSCRIPT
%num wxSWISS
%num wxMODERN
%num wxTELETYPE
%num wxVARIABLE
%num wxFIXED
%num wxNORMAL
%num wxLIGHT
%num wxBOLD
%num wxITALIC
%num wxSLANT


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


///////////////////////////////////////////////////////////////////////////////
// wxHtmlHelpController
//
// This actually derives from wxHelpController, but since it
// basically reimplements everything, and it's the only help
// controller supported, we lie and say it's derived from wxObject
//
// The zip filesystem is needed to read the zipped help file.

%class wxHtmlHelpController, wxObject
%include "wx/wxhtml.h"
%include "wx/fs_zip.h"

wxHtmlHelpController(int style = wxHF_DEFAULT_STYLE)
bool AddBook(const wxString& book, bool show_wait_msg)
// Fix: 'wxHtmlHelpController::CreateHelpFrame(wxHtmlHelpData *)' is not accessible in function wxHtmlHelpController_CreateHelpFrame()
// virtual wxHtmlHelpFrame* CreateHelpFrame(wxHtmlHelpData * data)
void Display(const wxString& x)
%rename DisplayId void Display(const int id)
void DisplayContents()
void DisplayIndex()
bool KeywordSearch(const wxString& keyword)
void ReadCustomization(wxConfigBase* cfg, wxString path = wxEmptyString)
void SetTempDir(const wxString& path)
void SetTitleFormat(const wxString& format)
void UseConfig(wxConfigBase* config, const wxString& rootpath = wxEmptyString)
void WriteCustomization(wxConfigBase* cfg, wxString path = wxEmptyString)


///////////////////////////////////////////////////////////////////////////////
// wxStyledTextCtrl

%class wxStyledTextCtrl, wxControl
%include "wx/stc/stc.h"

// from stc.cpp

wxStyledTextCtrl(wxWindow *parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = wxSTCNameStr)
~wxStyledTextCtrl()
long SendMsg(int msg, long wp, long lp)
void AddText(const wxString& text) 
void AddStyledText(const wxMemoryBuffer& data)
void InsertText(int pos, const wxString& text)
void ClearAll()
void ClearDocumentStyle()
int GetLength()
int GetCharAt(int pos)
int GetCurrentPos()
int GetAnchor()
int GetStyleAt(int pos)
void Redo()
void SetUndoCollection(bool collectUndo)
void SelectAll()
void SetSavePoint()
wxMemoryBuffer GetStyledText(int startPos, int endPos)
bool CanRedo()
int MarkerLineFromHandle(int handle)
void MarkerDeleteHandle(int handle)
bool GetUndoCollection()
int GetViewWhiteSpace()
void SetViewWhiteSpace(int viewWS)
// int PositionFromPoint(wxPoint pt)
int PositionFromPointClose(int x, int y)
void GotoLine(int line)
void GotoPos(int pos)
void SetAnchor(int posAnchor)
wxString GetCurLine(int* linePos)
int GetEndStyled()
void ConvertEOLs(int eolMode)
int GetEOLMode()
void SetEOLMode(int eolMode)
void StartStyling(int pos, int mask)
void SetStyling(int length, int style)
bool GetBufferedDraw()
void SetBufferedDraw(bool buffered)
void SetTabWidth(int tabWidth)
int GetTabWidth()
void SetCodePage(int codePage)
void MarkerDefine(int markerNumber, int markerSymbol, const wxColour& foreground, const wxColour& background)
void MarkerSetForeground(int markerNumber, const wxColour& fore)
void MarkerSetBackground(int markerNumber, const wxColour& back)
int MarkerAdd(int line, int markerNumber)
void MarkerDelete(int line, int markerNumber)
void MarkerDeleteAll(int markerNumber)
int MarkerGet(int line)
int MarkerNext(int lineStart, int markerMask)
int MarkerPrevious(int lineStart, int markerMask)
void MarkerDefineBitmap(int markerNumber, const wxBitmap& bmp)
void SetMarginType(int margin, int marginType)
int GetMarginType(int margin)
void SetMarginWidth(int margin, int pixelWidth)
int GetMarginWidth(int margin)
void SetMarginMask(int margin, int mask)
int GetMarginMask(int margin)
void SetMarginSensitive(int margin, bool sensitive)
bool GetMarginSensitive(int margin)
void StyleClearAll()
void StyleSetForeground(int style, const wxColour& fore)
void StyleSetBackground(int style, const wxColour& back)
void StyleSetBold(int style, bool bold)
void StyleSetItalic(int style, bool italic)
void StyleSetSize(int style, int sizePoints)
void StyleSetFaceName(int style, const wxString& fontName)
void StyleSetEOLFilled(int style, bool filled)
void StyleResetDefault()
void StyleSetUnderline(int style, bool underline)
void StyleSetCase(int style, int caseForce)
void StyleSetCharacterSet(int style, int characterSet)
void StyleSetHotSpot(int style, bool hotspot)
void SetSelForeground(bool useSetting, const wxColour& fore)
void SetSelBackground(bool useSetting, const wxColour& back)
void SetCaretForeground(const wxColour& fore)
void CmdKeyAssign(int key, int modifiers, int cmd)
void CmdKeyClear(int key, int modifiers)
void CmdKeyClearAll()
void SetStyleBytes(int length, char* styleBytes)
void StyleSetVisible(int style, bool visible)
int GetCaretPeriod()
void SetCaretPeriod(int periodMilliseconds)
void SetWordChars(const wxString& characters)
void BeginUndoAction()
void EndUndoAction()
void IndicatorSetStyle(int indic, int style)
int IndicatorGetStyle(int indic)
void IndicatorSetForeground(int indic, const wxColour& fore)
wxColour IndicatorGetForeground(int indic)
void SetWhitespaceForeground(bool useSetting, const wxColour& fore)
void SetWhitespaceBackground(bool useSetting, const wxColour& back)
void SetStyleBits(int bits)
int GetStyleBits()
void SetLineState(int line, int state)
int GetLineState(int line)
int GetMaxLineState()
bool GetCaretLineVisible()
void SetCaretLineVisible(bool show)
wxColour GetCaretLineBack()
void SetCaretLineBack(const wxColour& back)
void StyleSetChangeable(int style, bool changeable)
void AutoCompShow(int lenEntered, const wxString& itemList)
void AutoCompCancel()
bool AutoCompActive()
int AutoCompPosStart()
void AutoCompComplete()
void AutoCompStops(const wxString& characterSet)
void AutoCompSetSeparator(int separatorCharacter)
int AutoCompGetSeparator()
void AutoCompSelect(const wxString& text)
void AutoCompSetCancelAtStart(bool cancel)
bool AutoCompGetCancelAtStart()
void AutoCompSetFillUps(const wxString& characterSet)
void AutoCompSetChooseSingle(bool chooseSingle)
bool AutoCompGetChooseSingle()
void AutoCompSetIgnoreCase(bool ignoreCase)
bool AutoCompGetIgnoreCase()
void UserListShow(int listType, const wxString& itemList)
void AutoCompSetAutoHide(bool autoHide)
bool AutoCompGetAutoHide()
void AutoCompSetDropRestOfWord(bool dropRestOfWord)
bool AutoCompGetDropRestOfWord()
void RegisterImage(int type, const wxBitmap& bmp)
void ClearRegisteredImages()
int AutoCompGetTypeSeparator()
void AutoCompSetTypeSeparator(int separatorCharacter)
void SetIndent(int indentSize)
int GetIndent()
void SetUseTabs(bool useTabs)
bool GetUseTabs()
void SetLineIndentation(int line, int indentSize)
int GetLineIndentation(int line)
int GetLineIndentPosition(int line)
int GetColumn(int pos)
void SetUseHorizontalScrollBar(bool show)
bool GetUseHorizontalScrollBar()
void SetIndentationGuides(bool show)
bool GetIndentationGuides()
void SetHighlightGuide(int column)
int GetHighlightGuide()
int GetLineEndPosition(int line)
int GetCodePage()
wxColour GetCaretForeground()
bool GetReadOnly()
void SetCurrentPos(int pos)
void SetSelectionStart(int pos)
int GetSelectionStart()
void SetSelectionEnd(int pos)
int GetSelectionEnd()
void SetPrintMagnification(int magnification)
int GetPrintMagnification()
void SetPrintColourMode(int mode)
int GetPrintColourMode()
int FindText(int minPos, int maxPos, const wxString& text, int flags)
// int FormatRange(bool doDraw, int startPos, int endPos, wxDC* draw, wxDC* target, wxRect renderRect, wxRect pageRect)
int GetFirstVisibleLine()
wxString GetLine(int line)
int GetLineCount()
void SetMarginLeft(int pixelWidth)
int GetMarginLeft()
void SetMarginRight(int pixelWidth)
int GetMarginRight()
bool GetModify()
void SetSelection(int start, int end)
wxString GetSelectedText()
wxString GetTextRange(int startPos, int endPos)
void HideSelection(bool normal)
int LineFromPosition(int pos)
int PositionFromLine(int line)
void LineScroll(int columns, int lines)
void EnsureCaretVisible()
void ReplaceSelection(const wxString& text)
void SetReadOnly(bool readOnly)
bool CanPaste()
bool CanUndo()
void EmptyUndoBuffer()
void Undo()
void Cut()
void Copy()
void Paste()
void Clear()
void SetText(const wxString& text)
wxString GetText()
int GetTextLength()
void SetOvertype(bool overtype)
bool GetOvertype()
void SetCaretWidth(int pixelWidth)
int GetCaretWidth()
void SetTargetStart(int pos)
int GetTargetStart()
void SetTargetEnd(int pos)
int GetTargetEnd()
int ReplaceTarget(const wxString& text)
int ReplaceTargetRE(const wxString& text)
int SearchInTarget(const wxString& text)
void SetSearchFlags(int flags)
int GetSearchFlags()
void CallTipShow(int pos, const wxString& definition)
void CallTipCancel()
bool CallTipActive()
int CallTipPosAtStart()
void CallTipSetHighlight(int start, int end)
void CallTipSetBackground(const wxColour& back)
void CallTipSetForeground(const wxColour& fore)
void CallTipSetForegroundHighlight(const wxColour& fore)
int VisibleFromDocLine(int line)
int DocLineFromVisible(int lineDisplay)
void SetFoldLevel(int line, int level)
int GetFoldLevel(int line)
int GetLastChild(int line, int level)
int GetFoldParent(int line)
void ShowLines(int lineStart, int lineEnd)
void HideLines(int lineStart, int lineEnd)
bool GetLineVisible(int line)
void SetFoldExpanded(int line, bool expanded)
bool GetFoldExpanded(int line)
void ToggleFold(int line)
void EnsureVisible(int line)
void SetFoldFlags(int flags)
void EnsureVisibleEnforcePolicy(int line)
void SetTabIndents(bool tabIndents)
bool GetTabIndents()
void SetBackSpaceUnIndents(bool bsUnIndents)
bool GetBackSpaceUnIndents()
void SetMouseDwellTime(int periodMilliseconds)
int GetMouseDwellTime()
int WordStartPosition(int pos, bool onlyWordCharacters)
int WordEndPosition(int pos, bool onlyWordCharacters)
void SetWrapMode(int mode)
int GetWrapMode()
void SetLayoutCache(int mode)
int GetLayoutCache()
void SetScrollWidth(int pixelWidth)
int GetScrollWidth()
int TextWidth(int style, const wxString& text)
void SetEndAtLastLine(bool endAtLastLine)
int GetEndAtLastLine()
int TextHeight(int line)
void SetUseVerticalScrollBar(bool show)
bool GetUseVerticalScrollBar()
void AppendText(int length, const wxString& text)
bool GetTwoPhaseDraw()
void SetTwoPhaseDraw(bool twoPhase)
void TargetFromSelection()
void LinesJoin()
void LinesSplit(int pixelWidth)
void SetFoldMarginColour(bool useSetting, const wxColour& back)
void SetFoldMarginHiColour(bool useSetting, const wxColour& fore)
void LineDuplicate()
void HomeDisplay()
void HomeDisplayExtend()
void LineEndDisplay()
void LineEndDisplayExtend()
void LineCopy()
void MoveCaretInsideView()
int LineLength(int line)
void BraceHighlight(int pos1, int pos2)
void BraceBadLight(int pos)
int BraceMatch(int pos)
bool GetViewEOL()
void SetViewEOL(bool visible)
void* GetDocPointer()
void SetDocPointer(void* docPointer)
void SetModEventMask(int mask)
int GetEdgeColumn()
void SetEdgeColumn(int column)
int GetEdgeMode()
void SetEdgeMode(int mode)
wxColour GetEdgeColour()
void SetEdgeColour(const wxColour& edgeColour)
void SearchAnchor()
int SearchNext(int flags, const wxString& text)
int SearchPrev(int flags, const wxString& text)
int LinesOnScreen()
void UsePopUp(bool allowPopUp)
bool SelectionIsRectangle()
void SetZoom(int zoom)
int GetZoom()
void* CreateDocument()
void AddRefDocument(void* docPointer)
void ReleaseDocument(void* docPointer)
int GetModEventMask()
void SetSTCFocus(bool focus)
bool GetSTCFocus()
void SetStatus(int statusCode)
int GetStatus()
void SetMouseDownCaptures(bool captures)
bool GetMouseDownCaptures()
void SetSTCCursor(int cursorType)
int GetSTCCursor()
void SetControlCharSymbol(int symbol)
int GetControlCharSymbol()
void WordPartLeft()
void WordPartLeftExtend()
void WordPartRight()
void WordPartRightExtend()
void SetVisiblePolicy(int visiblePolicy, int visibleSlop)
void DelLineLeft()
void DelLineRight()
void SetXOffset(int newOffset)
int GetXOffset()
void ChooseCaretX()
void SetXCaretPolicy(int caretPolicy, int caretSlop)
void SetYCaretPolicy(int caretPolicy, int caretSlop)
void SetPrintWrapMode(int mode)
int GetPrintWrapMode()
void SetHotspotActiveForeground(bool useSetting, const wxColour& fore)
void SetHotspotActiveBackground(bool useSetting, const wxColour& back)
void SetHotspotActiveUnderline(bool underline)
int PositionBefore(int pos)
int PositionAfter(int pos)
void CopyRange(int start, int end)
void CopyText(int length, const wxString& text)
void StartRecord()
void StopRecord()
void SetLexer(int lexer)
int GetLexer()
void Colourise(int start, int end)
void SetProperty(const wxString& key, const wxString& value)
void SetKeyWords(int keywordSet, const wxString& keyWords)
void SetLexerLanguage(const wxString& language)
int GetCurrentLine()
void StyleSetSpec(int styleNum, const wxString& spec)
void StyleSetFont(int styleNum, wxFont& font)
void StyleSetFontAttr(int styleNum, int size, const wxString& faceName, bool bold, bool italic, bool underline)
void CmdKeyExecute(int cmd)
void SetMargins(int left, int right)
void GetSelection(int* startPos, int* endPos)
wxPoint PointFromPosition(int pos)
void ScrollToLine(int line)
void ScrollToColumn(int column)
bool SaveFile(const wxString& filename)
bool LoadFile(const wxString& filename)
// wxDragResult DoDragOver(wxCoord x, wxCoord y, wxDragResult def) 
bool DoDropText(long x, long y, const wxString& data) 

// from contrib/include/wx/stc/stc.h
%num wxSTC_INVALID_POSITION 
%num wxSTC_START 
%num wxSTC_OPTIONAL_START 
%num wxSTC_LEXER_START 
%num wxSTC_CMD_REDO 
%num wxSTC_CMD_SELECTALL 
%num wxSTC_WS_INVISIBLE 
%num wxSTC_WS_VISIBLEALWAYS 
%num wxSTC_WS_VISIBLEAFTERINDENT 
%num wxSTC_EOL_CRLF 
%num wxSTC_EOL_CR 
%num wxSTC_EOL_LF 
%num wxSTC_CP_UTF8 
%num wxSTC_MARKER_MAX 
%num wxSTC_MARK_CIRCLE 
%num wxSTC_MARK_ROUNDRECT 
%num wxSTC_MARK_ARROW 
%num wxSTC_MARK_SMALLRECT 
%num wxSTC_MARK_SHORTARROW 
%num wxSTC_MARK_EMPTY 
%num wxSTC_MARK_ARROWDOWN 
%num wxSTC_MARK_MINUS 
%num wxSTC_MARK_PLUS 
%num wxSTC_MARK_VLINE 
%num wxSTC_MARK_LCORNER 
%num wxSTC_MARK_TCORNER 
%num wxSTC_MARK_BOXPLUS 
%num wxSTC_MARK_BOXPLUSCONNECTED 
%num wxSTC_MARK_BOXMINUS 
%num wxSTC_MARK_BOXMINUSCONNECTED 
%num wxSTC_MARK_LCORNERCURVE 
%num wxSTC_MARK_TCORNERCURVE 
%num wxSTC_MARK_CIRCLEPLUS 
%num wxSTC_MARK_CIRCLEPLUSCONNECTED 
%num wxSTC_MARK_CIRCLEMINUS 
%num wxSTC_MARK_CIRCLEMINUSCONNECTED 
%num wxSTC_MARK_CHARACTER 
%num wxSTC_MARKNUM_FOLDEREND 
%num wxSTC_MARKNUM_FOLDEROPENMID 
%num wxSTC_MARKNUM_FOLDERMIDTAIL 
%num wxSTC_MARKNUM_FOLDERTAIL 
%num wxSTC_MARKNUM_FOLDERSUB 
%num wxSTC_MARKNUM_FOLDER 
%num wxSTC_MARKNUM_FOLDEROPEN 
%num wxSTC_MARGIN_SYMBOL 
%num wxSTC_MARGIN_NUMBER 
%num wxSTC_STYLE_DEFAULT 
%num wxSTC_STYLE_LINENUMBER 
%num wxSTC_STYLE_BRACELIGHT 
%num wxSTC_STYLE_BRACEBAD 
%num wxSTC_STYLE_CONTROLCHAR 
%num wxSTC_STYLE_INDENTGUIDE 
%num wxSTC_STYLE_LASTPREDEFINED 
%num wxSTC_STYLE_MAX 
%num wxSTC_CHARSET_ANSI 
%num wxSTC_CHARSET_DEFAULT 
%num wxSTC_CHARSET_BALTIC 
%num wxSTC_CHARSET_CHINESEBIG5 
%num wxSTC_CHARSET_EASTEUROPE 
%num wxSTC_CHARSET_GB2312 
%num wxSTC_CHARSET_GREEK 
%num wxSTC_CHARSET_HANGUL 
%num wxSTC_CHARSET_MAC 
%num wxSTC_CHARSET_OEM 
%num wxSTC_CHARSET_RUSSIAN 
%num wxSTC_CHARSET_SHIFTJIS 
%num wxSTC_CHARSET_SYMBOL 
%num wxSTC_CHARSET_TURKISH 
%num wxSTC_CHARSET_JOHAB 
%num wxSTC_CHARSET_HEBREW 
%num wxSTC_CHARSET_ARABIC 
%num wxSTC_CHARSET_VIETNAMESE 
%num wxSTC_CHARSET_THAI 
%num wxSTC_CASE_MIXED 
%num wxSTC_CASE_UPPER 
%num wxSTC_CASE_LOWER 
%num wxSTC_INDIC_MAX 
%num wxSTC_INDIC_PLAIN 
%num wxSTC_INDIC_SQUIGGLE 
%num wxSTC_INDIC_TT 
%num wxSTC_INDIC_DIAGONAL 
%num wxSTC_INDIC_STRIKE 
%num wxSTC_INDIC0_MASK 
%num wxSTC_INDIC1_MASK 
%num wxSTC_INDIC2_MASK 
%num wxSTC_INDICS_MASK 
%num wxSTC_PRINT_NORMAL 
%num wxSTC_PRINT_INVERTLIGHT 
%num wxSTC_PRINT_BLACKONWHITE 
%num %alias wxSTC_PRINT_COLORONWHITE wxSTC_PRINT_COLOURONWHITE 
%num %alias wxSTC_PRINT_COLORONWHITEDEFAULTBG wxSTC_PRINT_COLOURONWHITEDEFAULTBG 
%num wxSTC_FIND_WHOLEWORD 
%num wxSTC_FIND_MATCHCASE 
%num wxSTC_FIND_WORDSTART 
%num wxSTC_FIND_REGEXP 
%num wxSTC_CMD_UNDO 
%num wxSTC_CMD_CUT 
%num wxSTC_CMD_COPY 
%num wxSTC_CMD_PASTE 
%num wxSTC_FOLDLEVELBASE 
%num wxSTC_FOLDLEVELWHITEFLAG 
%num wxSTC_FOLDLEVELHEADERFLAG 
%num wxSTC_FOLDLEVELNUMBERMASK 
%num wxSTC_TIME_FOREVER 
%num wxSTC_CMD_LINEDOWN 
%num wxSTC_CMD_LINEDOWNEXTEND 
%num wxSTC_CMD_LINEUP 
%num wxSTC_CMD_LINEUPEXTEND 
%num wxSTC_CMD_CHARLEFT 
%num wxSTC_CMD_CHARLEFTEXTEND 
%num wxSTC_CMD_CHARRIGHT 
%num wxSTC_CMD_CHARRIGHTEXTEND 
%num wxSTC_CMD_WORDLEFT 
%num wxSTC_CMD_WORDLEFTEXTEND 
%num wxSTC_CMD_WORDRIGHT 
%num wxSTC_CMD_WORDRIGHTEXTEND 
%num wxSTC_CMD_HOME 
%num wxSTC_CMD_HOMEEXTEND 
%num wxSTC_CMD_LINEEND 
%num wxSTC_CMD_LINEENDEXTEND 
%num wxSTC_CMD_DOCUMENTSTART 
%num wxSTC_CMD_DOCUMENTSTARTEXTEND 
%num wxSTC_CMD_DOCUMENTEND 
%num wxSTC_CMD_DOCUMENTENDEXTEND 
%num wxSTC_CMD_PAGEUP 
%num wxSTC_CMD_PAGEUPEXTEND 
%num wxSTC_CMD_PAGEDOWN 
%num wxSTC_CMD_PAGEDOWNEXTEND 
%num wxSTC_CMD_EDITTOGGLEOVERTYPE 
%num wxSTC_CMD_CANCEL 
%num wxSTC_CMD_DELETEBACK 
%num wxSTC_CMD_TAB 
%num wxSTC_CMD_BACKTAB 
%num wxSTC_CMD_NEWLINE 
%num wxSTC_CMD_FORMFEED 
%num wxSTC_CMD_VCHOME 
%num wxSTC_CMD_VCHOMEEXTEND 
%num wxSTC_CMD_ZOOMIN 
%num wxSTC_CMD_ZOOMOUT 
%num wxSTC_CMD_DELWORDLEFT 
%num wxSTC_CMD_DELWORDRIGHT 
%num wxSTC_CMD_LINECUT 
%num wxSTC_CMD_LINEDELETE 
%num wxSTC_CMD_LINETRANSPOSE 
%num wxSTC_CMD_LOWERCASE 
%num wxSTC_CMD_UPPERCASE 
%num wxSTC_CMD_LINESCROLLDOWN 
%num wxSTC_CMD_LINESCROLLUP 
%num wxSTC_EDGE_NONE 
%num wxSTC_EDGE_LINE 
%num wxSTC_EDGE_BACKGROUND 
%num wxSTC_CARET_SLOP 
%num wxSTC_CARET_STRICT 
%num wxSTC_CURSORNORMAL 
%num wxSTC_CURSORWAIT 
%num wxSTC_VISIBLE_SLOP 
%num wxSTC_VISIBLE_STRICT 
%num wxSTC_MOD_INSERTTEXT 
%num wxSTC_MOD_DELETETEXT 
%num wxSTC_MOD_CHANGESTYLE 
%num wxSTC_MOD_CHANGEFOLD 
%num wxSTC_PERFORMED_USER 
%num wxSTC_PERFORMED_UNDO 
%num wxSTC_PERFORMED_REDO 
%num wxSTC_LASTSTEPINUNDOREDO 
%num wxSTC_MOD_CHANGEMARKER 
%num wxSTC_MOD_BEFOREINSERT 
%num wxSTC_MOD_BEFOREDELETE 
%num wxSTC_MODEVENTMASKALL 
%num wxSTC_KEY_DOWN 
%num wxSTC_KEY_UP 
%num wxSTC_KEY_LEFT 
%num wxSTC_KEY_RIGHT 
%num wxSTC_KEY_HOME 
%num wxSTC_KEY_END 
%num wxSTC_KEY_PRIOR 
%num wxSTC_KEY_NEXT 
%num wxSTC_KEY_DELETE 
%num wxSTC_KEY_INSERT 
%num wxSTC_KEY_ESCAPE 
%num wxSTC_KEY_BACK 
%num wxSTC_KEY_TAB 
%num wxSTC_KEY_RETURN 
%num wxSTC_KEY_ADD 
%num wxSTC_KEY_SUBTRACT 
%num wxSTC_KEY_DIVIDE 
%num wxSTC_SCMOD_SHIFT 
%num wxSTC_SCMOD_CTRL 
%num wxSTC_SCMOD_ALT 
%num wxSTC_LEX_CONTAINER 
%num wxSTC_LEX_NULL 
%num wxSTC_LEX_PYTHON 
%num wxSTC_LEX_CPP 
%num wxSTC_LEX_HTML 
%num wxSTC_LEX_XML 
%num wxSTC_LEX_PERL 
%num wxSTC_LEX_SQL 
%num wxSTC_LEX_VB 
%num wxSTC_LEX_PROPERTIES 
%num wxSTC_LEX_ERRORLIST 
%num wxSTC_LEX_MAKEFILE 
%num wxSTC_LEX_BATCH 
%num wxSTC_LEX_XCODE 
%num wxSTC_LEX_LATEX 
%num wxSTC_LEX_LUA 
%num wxSTC_LEX_DIFF 
%num wxSTC_LEX_CONF 
%num wxSTC_LEX_PASCAL 
%num wxSTC_LEX_AVE 
%num wxSTC_LEX_ADA 
%num wxSTC_LEX_LISP 
%num wxSTC_LEX_RUBY 
%num wxSTC_LEX_EIFFEL 
%num wxSTC_LEX_EIFFELKW 
%num wxSTC_LEX_TCL 
%num wxSTC_LEX_NNCRONTAB 
%num wxSTC_LEX_AUTOMATIC 
%num wxSTC_P_DEFAULT 
%num wxSTC_P_COMMENTLINE 
%num wxSTC_P_NUMBER 
%num wxSTC_P_STRING 
%num wxSTC_P_CHARACTER 
%num wxSTC_P_WORD 
%num wxSTC_P_TRIPLE 
%num wxSTC_P_TRIPLEDOUBLE 
%num wxSTC_P_CLASSNAME 
%num wxSTC_P_DEFNAME 
%num wxSTC_P_OPERATOR 
%num wxSTC_P_IDENTIFIER 
%num wxSTC_P_COMMENTBLOCK 
%num wxSTC_P_STRINGEOL 
%num wxSTC_C_DEFAULT 
%num wxSTC_C_COMMENT 
%num wxSTC_C_COMMENTLINE 
%num wxSTC_C_COMMENTDOC 
%num wxSTC_C_NUMBER 
%num wxSTC_C_WORD 
%num wxSTC_C_STRING 
%num wxSTC_C_CHARACTER 
%num wxSTC_C_UUID 
%num wxSTC_C_PREPROCESSOR 
%num wxSTC_C_OPERATOR 
%num wxSTC_C_IDENTIFIER 
%num wxSTC_C_STRINGEOL 
%num wxSTC_C_VERBATIM 
%num wxSTC_C_REGEX 
%num wxSTC_C_COMMENTLINEDOC 
%num wxSTC_C_WORD2 
%num wxSTC_C_COMMENTDOCKEYWORD 
%num wxSTC_C_COMMENTDOCKEYWORDERROR 
%num wxSTC_H_DEFAULT 
%num wxSTC_H_TAG 
%num wxSTC_H_TAGUNKNOWN 
%num wxSTC_H_ATTRIBUTE 
%num wxSTC_H_ATTRIBUTEUNKNOWN 
%num wxSTC_H_NUMBER 
%num wxSTC_H_DOUBLESTRING 
%num wxSTC_H_SINGLESTRING 
%num wxSTC_H_OTHER 
%num wxSTC_H_COMMENT 
%num wxSTC_H_ENTITY 
%num wxSTC_H_TAGEND 
%num wxSTC_H_XMLSTART 
%num wxSTC_H_XMLEND 
%num wxSTC_H_SCRIPT 
%num wxSTC_H_ASP 
%num wxSTC_H_ASPAT 
%num wxSTC_H_CDATA 
%num wxSTC_H_QUESTION 
%num wxSTC_H_VALUE 
%num wxSTC_H_XCCOMMENT 
%num wxSTC_H_SGML_DEFAULT 
%num wxSTC_H_SGML_COMMAND 
%num wxSTC_H_SGML_1ST_PARAM 
%num wxSTC_H_SGML_DOUBLESTRING 
%num wxSTC_H_SGML_SIMPLESTRING 
%num wxSTC_H_SGML_ERROR 
%num wxSTC_H_SGML_SPECIAL 
%num wxSTC_H_SGML_ENTITY 
%num wxSTC_H_SGML_COMMENT 
%num wxSTC_H_SGML_1ST_PARAM_COMMENT 
%num wxSTC_H_SGML_BLOCK_DEFAULT 
%num wxSTC_HJ_START 
%num wxSTC_HJ_DEFAULT 
%num wxSTC_HJ_COMMENT 
%num wxSTC_HJ_COMMENTLINE 
%num wxSTC_HJ_COMMENTDOC 
%num wxSTC_HJ_NUMBER 
%num wxSTC_HJ_WORD 
%num wxSTC_HJ_KEYWORD 
%num wxSTC_HJ_DOUBLESTRING 
%num wxSTC_HJ_SINGLESTRING 
%num wxSTC_HJ_SYMBOLS 
%num wxSTC_HJ_STRINGEOL 
%num wxSTC_HJ_REGEX 
%num wxSTC_HJA_START 
%num wxSTC_HJA_DEFAULT 
%num wxSTC_HJA_COMMENT 
%num wxSTC_HJA_COMMENTLINE 
%num wxSTC_HJA_COMMENTDOC 
%num wxSTC_HJA_NUMBER 
%num wxSTC_HJA_WORD 
%num wxSTC_HJA_KEYWORD 
%num wxSTC_HJA_DOUBLESTRING 
%num wxSTC_HJA_SINGLESTRING 
%num wxSTC_HJA_SYMBOLS 
%num wxSTC_HJA_STRINGEOL 
%num wxSTC_HJA_REGEX 
%num wxSTC_HB_START 
%num wxSTC_HB_DEFAULT 
%num wxSTC_HB_COMMENTLINE 
%num wxSTC_HB_NUMBER 
%num wxSTC_HB_WORD 
%num wxSTC_HB_STRING 
%num wxSTC_HB_IDENTIFIER 
%num wxSTC_HB_STRINGEOL 
%num wxSTC_HBA_START 
%num wxSTC_HBA_DEFAULT 
%num wxSTC_HBA_COMMENTLINE 
%num wxSTC_HBA_NUMBER 
%num wxSTC_HBA_WORD 
%num wxSTC_HBA_STRING 
%num wxSTC_HBA_IDENTIFIER 
%num wxSTC_HBA_STRINGEOL 
%num wxSTC_HP_START 
%num wxSTC_HP_DEFAULT 
%num wxSTC_HP_COMMENTLINE 
%num wxSTC_HP_NUMBER 
%num wxSTC_HP_STRING 
%num wxSTC_HP_CHARACTER 
%num wxSTC_HP_WORD 
%num wxSTC_HP_TRIPLE 
%num wxSTC_HP_TRIPLEDOUBLE 
%num wxSTC_HP_CLASSNAME 
%num wxSTC_HP_DEFNAME 
%num wxSTC_HP_OPERATOR 
%num wxSTC_HP_IDENTIFIER 
%num wxSTC_HPA_START 
%num wxSTC_HPA_DEFAULT 
%num wxSTC_HPA_COMMENTLINE 
%num wxSTC_HPA_NUMBER 
%num wxSTC_HPA_STRING 
%num wxSTC_HPA_CHARACTER 
%num wxSTC_HPA_WORD 
%num wxSTC_HPA_TRIPLE 
%num wxSTC_HPA_TRIPLEDOUBLE 
%num wxSTC_HPA_CLASSNAME 
%num wxSTC_HPA_DEFNAME 
%num wxSTC_HPA_OPERATOR 
%num wxSTC_HPA_IDENTIFIER 
%num wxSTC_HPHP_DEFAULT 
%num wxSTC_HPHP_HSTRING 
%num wxSTC_HPHP_SIMPLESTRING 
%num wxSTC_HPHP_WORD 
%num wxSTC_HPHP_NUMBER 
%num wxSTC_HPHP_VARIABLE 
%num wxSTC_HPHP_COMMENT 
%num wxSTC_HPHP_COMMENTLINE 
%num wxSTC_HPHP_HSTRING_VARIABLE 
%num wxSTC_HPHP_OPERATOR 
%num wxSTC_PL_DEFAULT 
%num wxSTC_PL_ERROR 
%num wxSTC_PL_COMMENTLINE 
%num wxSTC_PL_POD 
%num wxSTC_PL_NUMBER 
%num wxSTC_PL_WORD 
%num wxSTC_PL_STRING 
%num wxSTC_PL_CHARACTER 
%num wxSTC_PL_PUNCTUATION 
%num wxSTC_PL_PREPROCESSOR 
%num wxSTC_PL_OPERATOR 
%num wxSTC_PL_IDENTIFIER 
%num wxSTC_PL_SCALAR 
%num wxSTC_PL_ARRAY 
%num wxSTC_PL_HASH 
%num wxSTC_PL_SYMBOLTABLE 
%num wxSTC_PL_REGEX 
%num wxSTC_PL_REGSUBST 
%num wxSTC_PL_LONGQUOTE 
%num wxSTC_PL_BACKTICKS 
%num wxSTC_PL_DATASECTION 
%num wxSTC_PL_HERE_DELIM 
%num wxSTC_PL_HERE_Q 
%num wxSTC_PL_HERE_QQ 
%num wxSTC_PL_HERE_QX 
%num wxSTC_PL_STRING_Q 
%num wxSTC_PL_STRING_QQ 
%num wxSTC_PL_STRING_QX 
%num wxSTC_PL_STRING_QR 
%num wxSTC_PL_STRING_QW 
%num wxSTC_L_DEFAULT 
%num wxSTC_L_COMMAND 
%num wxSTC_L_TAG 
%num wxSTC_L_MATH 
%num wxSTC_L_COMMENT 
%num wxSTC_LUA_DEFAULT 
%num wxSTC_LUA_COMMENT 
%num wxSTC_LUA_COMMENTLINE 
%num wxSTC_LUA_COMMENTDOC 
%num wxSTC_LUA_NUMBER 
%num wxSTC_LUA_WORD 
%num wxSTC_LUA_STRING 
%num wxSTC_LUA_CHARACTER 
%num wxSTC_LUA_LITERALSTRING 
%num wxSTC_LUA_PREPROCESSOR 
%num wxSTC_LUA_OPERATOR 
%num wxSTC_LUA_IDENTIFIER 
%num wxSTC_LUA_STRINGEOL 
%num wxSTC_ERR_DEFAULT 
%num wxSTC_ERR_PYTHON 
%num wxSTC_ERR_GCC 
%num wxSTC_ERR_MS 
%num wxSTC_ERR_CMD 
%num wxSTC_ERR_BORLAND 
%num wxSTC_ERR_PERL 
%num wxSTC_ERR_NET 
%num wxSTC_ERR_LUA 
%num wxSTC_ERR_DIFF_CHANGED 
%num wxSTC_ERR_DIFF_ADDITION 
%num wxSTC_ERR_DIFF_DELETION 
%num wxSTC_ERR_DIFF_MESSAGE 
%num wxSTC_BAT_DEFAULT 
%num wxSTC_BAT_COMMENT 
%num wxSTC_BAT_WORD 
%num wxSTC_BAT_LABEL 
%num wxSTC_BAT_HIDE 
%num wxSTC_BAT_COMMAND 
%num wxSTC_BAT_IDENTIFIER 
%num wxSTC_BAT_OPERATOR 
%num wxSTC_MAKE_DEFAULT 
%num wxSTC_MAKE_COMMENT 
%num wxSTC_MAKE_PREPROCESSOR 
%num wxSTC_MAKE_IDENTIFIER 
%num wxSTC_MAKE_OPERATOR 
%num wxSTC_MAKE_TARGET 
%num wxSTC_MAKE_IDEOL 
%num wxSTC_CONF_DEFAULT 
%num wxSTC_CONF_COMMENT 
%num wxSTC_CONF_NUMBER 
%num wxSTC_CONF_IDENTIFIER 
%num wxSTC_CONF_EXTENSION 
%num wxSTC_CONF_PARAMETER 
%num wxSTC_CONF_STRING 
%num wxSTC_CONF_OPERATOR 
%num wxSTC_CONF_IP 
%num wxSTC_CONF_DIRECTIVE 
%num wxSTC_AVE_DEFAULT 
%num wxSTC_AVE_COMMENT 
%num wxSTC_AVE_NUMBER 
%num wxSTC_AVE_WORD 
//%num wxSTC_AVE_KEYWORD 
//%num wxSTC_AVE_STATEMENT 
%num wxSTC_AVE_STRING 
%num wxSTC_AVE_ENUM 
%num wxSTC_AVE_STRINGEOL 
%num wxSTC_AVE_IDENTIFIER 
%num wxSTC_AVE_OPERATOR 
%num wxSTC_ADA_DEFAULT 
//%num wxSTC_ADA_COMMENT 
%num wxSTC_ADA_NUMBER 
%num wxSTC_ADA_WORD 
%num wxSTC_ADA_STRING 
%num wxSTC_ADA_CHARACTER 
//%num wxSTC_ADA_OPERATOR 
%num wxSTC_ADA_IDENTIFIER 
%num wxSTC_ADA_STRINGEOL 
%num wxSTC_LISP_DEFAULT 
%num wxSTC_LISP_COMMENT 
%num wxSTC_LISP_NUMBER 
%num wxSTC_LISP_KEYWORD 
%num wxSTC_LISP_STRING 
%num wxSTC_LISP_STRINGEOL 
%num wxSTC_LISP_IDENTIFIER 
%num wxSTC_LISP_OPERATOR 
%num wxSTC_EIFFEL_DEFAULT 
%num wxSTC_EIFFEL_COMMENTLINE 
%num wxSTC_EIFFEL_NUMBER 
%num wxSTC_EIFFEL_WORD 
%num wxSTC_EIFFEL_STRING 
%num wxSTC_EIFFEL_CHARACTER 
%num wxSTC_EIFFEL_OPERATOR 
%num wxSTC_EIFFEL_IDENTIFIER 
%num wxSTC_EIFFEL_STRINGEOL 
%num wxSTC_NNCRONTAB_DEFAULT 
%num wxSTC_NNCRONTAB_COMMENT 
%num wxSTC_NNCRONTAB_TASK 
%num wxSTC_NNCRONTAB_SECTION 
%num wxSTC_NNCRONTAB_KEYWORD 
%num wxSTC_NNCRONTAB_MODIFIER 
%num wxSTC_NNCRONTAB_ASTERISK 
%num wxSTC_NNCRONTAB_NUMBER 
%num wxSTC_NNCRONTAB_STRING 
%num wxSTC_NNCRONTAB_ENVIRONMENT 
%num wxSTC_NNCRONTAB_IDENTIFIER 
%num wxSTC_MASK_FOLDERS 

// the event codes
%num wxEVT_STC_CHANGE
%num wxEVT_STC_STYLENEEDED
%num wxEVT_STC_CHARADDED
%num wxEVT_STC_SAVEPOINTREACHED
%num wxEVT_STC_SAVEPOINTLEFT
%num wxEVT_STC_ROMODIFYATTEMPT
%num wxEVT_STC_KEY
%num wxEVT_STC_DOUBLECLICK
%num wxEVT_STC_UPDATEUI
%num wxEVT_STC_MODIFIED
%num wxEVT_STC_MACRORECORD
%num wxEVT_STC_MARGINCLICK
%num wxEVT_STC_NEEDSHOWN
%num wxEVT_STC_POSCHANGED
%num wxEVT_STC_PAINTED
%num wxEVT_STC_USERLISTSELECTION
%num wxEVT_STC_URIDROPPED
%num wxEVT_STC_DWELLSTART
%num wxEVT_STC_DWELLEND
%num wxEVT_STC_START_DRAG
%num wxEVT_STC_DRAG_OVER
%num wxEVT_STC_DO_DROP
%num wxEVT_STC_ZOOM
%num wxEVT_STC_HOTSPOT_CLICK
%num wxEVT_STC_HOTSPOT_DCLICK
%num wxEVT_STC_CALLTIP_CLICK


///////////////////////////////////////////////////////////////////////////////
// wxStyledTextEvent

%class wxStyledTextEvent, wxCommandEvent
%include "wx/stc/stc.h"

wxStyledTextEvent(wxEventType commandType=0, int id=0);
// FIX! Should this be a Clone cto or something?
// wxStyledTextEvent(const wxStyledTextEvent& event);
~wxStyledTextEvent()
void SetPosition(int pos)
void SetKey(int k)
void SetModifiers(int m)
void SetModificationType(int t)
void SetText(const wxString& t)
void SetLength(int len)
void SetLinesAdded(int num)
void SetLine(int val)
void SetFoldLevelNow(int val)
void SetFoldLevelPrev(int val)
void SetMargin(int val)
void SetMessage(int val)
void SetWParam(int val)
void SetLParam(int val)
void SetListType(int val)
void SetX(int val)
void SetY(int val)
void SetDragText(const wxString& val)
void SetDragAllowMove(bool val)
int  GetPosition()
int  GetKey()
int  GetModifiers()
int  GetModificationType()
wxString GetText() const
int  GetLength() const
int  GetLinesAdded() const
int  GetLine() const
int  GetFoldLevelNow() const
int  GetFoldLevelPrev() const
int  GetMargin() const
int  GetMessage() const
int  GetWParam() const
int  GetLParam() const
int  GetListType() const
int  GetX() const
int  GetY() const
wxString GetDragText()
bool GetDragAllowMove()
// Mac doesn't support
//    wxDragResult GetDragResult()     { return m_dragResult; }
bool GetShift()
bool GetControl()
bool GetAlt()
virtual wxEvent* Clone()

///////////////////////////////////////////////////////////////////////////////
// wxWave

// This is having trouble finding the class

%skip
%class wxWave, wxObject
%include "wx/wave.h"

wxWave()
ctor %wxWaveFromFile(const wxString& fileName, bool isResource = FALSE)
~wxWave()
bool Create(const wxString& fileName, bool isResource = FALSE)
bool IsOk() const
bool Play(bool async = TRUE, bool looped = FALSE) const


///////////////////////////////////////////////////////////////////////////////
// wxDir

%class wxDir
%include "wx/dir.h"


wxDir()
~wxDir()
static bool Exists(const wxString& dir)
bool Open(const wxString& dir)
bool IsOpened() const
// bool GetFirst(wxString* filename, const wxString& filespec = wxEmptyString, int flags = wxDIR_DEFAULT) const
%{
	// char *GetFirst(const wxString& filespec = wxEmptyString, int flags = wxDIR_DEFAULT) const
    void wxDir_GetFirst()
	{
		// int flags		
		int flags = (wTheCall->parmCount > 1 ? (int)wStackPopNumber() : wxDIR_DEFAULT );
	
		// const wxString& value = wxEmptyString
        wxString filespec = (wTheCall->parmCount > 0 ? wStackPopChar() : wxEmptyString);
		
        // allocate string to hold the result
        wxString filename = wxString();
		
		// call wxDir::GetFirst
        ((wxDir *)wTheCall->self->ptr)->GetFirst(&filename, filespec, flags);
		
		wWrapDerefArgs();
        wStackPushChar( (char *)(filename.c_str()), W_TRUE );    
	}
%}
%method GetFirst wxDir_GetFirst(const wxString& filespec = wxEmptyString, int flags = wxDIR_DEFAULT)

// bool GetNext(wxString* filename) const
%{
    // char *GetNext()
    void wxDir_GetNext()
	{
        // allocate string to hold the result
        wxString filename = wxString();
		
        // call wxDir::GetNext
        ((wxDir *)wTheCall->self->ptr)->GetNext(&filename);
		
		wWrapDerefArgs();
        wStackPushChar( (char *)(filename.c_str()), W_TRUE );    
	}
%}
%method GetNext wxDir_GetNext()

bool HasFiles(const wxString& filespec = wxEmptyString)
bool HasSubDirs(const wxString& dirspec = wxEmptyString)
// FIXME: wxDirTraverser not defined yet
// size_t Traverse(wxDirTraverser& sink, const wxString& filespec = wxEmptyString, int flags = wxDIR_DEFAULT)
// FIXME: returning arrays is not currently supported
// static size_t GetAllFiles(const wxString& dirname, wxArrayString *files, const wxString& filespec = wxEmptyString, int flags = wxDIR_DEFAULT)

// enums
%num wxDIR_FILES
%num wxDIR_DIRS
%num wxDIR_HIDDEN
%num wxDIR_DOTDOT
%num wxDIR_DEFAULT


///////////////////////////////////////////////////////////////////////////////
// wxStreamBase

%class wxStreamBase
%include "wx/stream.h"

wxStreamBase()
~wxStreamBase()
int IsOk() const
int LastError() const
	%num wxSTREAM_NO_ERROR
	%num wxSTREAM_EOF
	%num wxSTREAM_WRITE_ERROR
	%num wxSTREAM_READ_ERROR
// FIXME: these are documented, but don't seem to exist
// size_t OnSysRead(void* buffer, size_t bufsize)
// off_t OnSysSeek(off_t pos, wxSeekMode mode)
// off_t OnSysTell() const
// size_t OnSysWrite(void *buffer, size_t bufsize)
size_t GetSize() const



///////////////////////////////////////////////////////////////////////////////
// wxInputStream

%class wxInputStream, wxStreamBase
%include "wx/stream.h"

// wxInputStream()
// ~wxInputStream()
char GetC()
boolean Eof() const
size_t LastRead() const
char Peek()
// void Read(void *buffer, size_t size)
%{
    // void Read(void * buffer, size_t size)
    void wxInputStream_Read()
    {
        // the number of bytes
        int size = (int)wStackPopNumber();
    
        // allocate a buffer of the requested size
        void *buffer = wMalloc( size );
    
        // call Read
        ((wxInputStream*)(wTheCall->self->ptr))->Read(buffer, size);
    
        // clear the args
        wWrapDerefArgs();
    
        // wrap the buffer into a string
        wStackPushChar( (char *)(buffer), W_TRUE );
    
        // free the buffer
        wFree( buffer );
    }

%}
%method Read      wxInputStream_Read( int nbytes )


off_t SeekI(off_t pos, wxSeekMode mode = wxFromStart)
off_t TellI() const
// FIXME: not implemented
// size_t Ungetch(const char* buffer, size_t size)
// FIXME: rename this, only ungets a single char
// bool Ungetch(char c)


///////////////////////////////////////////////////////////////////////////////
// wxOutputStream

%class wxOutputStream, wxStreamBase
%include "wx/stream.h"

wxOutputStream()
~wxOutputStream()
size_t LastWrite() const
void PutC(char c)
off_t SeekO(off_t pos, wxSeekMode mode)
off_t TellO() const
// wxOutputStream& Write(const void *buffer, size_t size)
// wxOutputStream& Write(wxInputStream& stream_in)
%{
    // wxOutputStream& Write(const void *buffer, size_t size)
    void wxOutputStream_Write()
    {
        // get pointer to the string
        wVariant *theString = wStackPopString();
        int nbytes = wStringCount( theString );
        void *buffer = (void *)wStringChar( theString );

        // call Write
        ((wxOutputStream *)(wTheCall->self->ptr))->Write(buffer, nbytes);
    
        // clear the args
        wWrapDerefArgs();
    }

    // void WriteFromStream(wxInputStream& stream_in)
    void wxOutputStream_WriteFromStream()
    {
        // get the input stream
        wxInputStream *stream_in = (wxInputStream *)wStackPopObjectPtr( _wxInputStream );

        // call Write
        ((wxOutputStream *)(wTheCall->self->ptr))->Write(*stream_in);
    
        // clear the args
        wWrapDerefArgs();
    }
%}
%method Write           wxOutputStream_Write( wxString *buffer )
%method WriteFromStream wxOutputStream_WriteFromStream( wxInputStream& stream_in )




///////////////////////////////////////////////////////////////////////////////
// wxSocketBase

%class wxSocketBase, wxObject
%include "wx/socket.h"


wxSocketBase()
~wxSocketBase()
// FIXME: i don't think wxBasic can do this
// wxSocketBase::wxSockCbk Callback(wxSocketBase::wxSockCbk callback)
// char * CallbackData(char *cdata)
void Close()
bool Destroy()
// wxSocketBase& Discard()
bool Error() const
void * GetClientData() const
// bool GetLocal(wxSockAddress& addr) const
%{
    void wxSocketBase_GetLocal()
    {
        wxSockAddress *returns;
        ((wxSocketBase *)wTheCall->self->ptr)->GetLocal(*returns);
        wWrapDerefArgs();
        wWrapSetThis( _wxSocketBase, (void *)returns );        
    }
%}
%method GetLocal wxSocketBase_GetLocal()

int GetFlags() const
// bool GetPeer(wxSockAddress& addr) const
%{
    void wxSocketBase_GetPeer()
    {
        wxSockAddress *returns;
        ((wxSocketBase *)wTheCall->self->ptr)->GetPeer(*returns);
        wWrapDerefArgs();
        wWrapSetThis( _wxSocketBase, (void *)returns );        
    }
%}
%method GetPeer wxSocketBase_GetPeer()

void InterruptWait()
bool IsConnected() const
bool IsData() const
bool IsDisconnected() const
unsigned int LastCount() const
int LastError() const
	%num wxSOCKET_NOERROR
	%num wxSOCKET_INVOP
	%num wxSOCKET_IOERR
	%num wxSOCKET_INVADDR
	%num wxSOCKET_INVSOCK
	%num wxSOCKET_NOHOST
	%num wxSOCKET_INVPORT
	%num wxSOCKET_WOULDBLOCK
	%num wxSOCKET_TIMEDOUT
	%num wxSOCKET_MEMERR
void Notify(bool notify)
bool Ok() const
void RestoreState()
void SaveState()
void SetClientData(void *data)
void SetEventHandler(wxEvtHandler& handler, int id = -1)
void SetFlags(int flags)
	%num wxSOCKET_NONE
	%num wxSOCKET_NOWAIT
	%num wxSOCKET_WAITALL
	wxSOCKET_BLOCK
void SetNotify(int flags)
	%num wxSOCKET_INPUT
	%num wxSOCKET_OUTPUT
	%num wxSOCKET_CONNECTION
	%num wxSOCKET_LOST
void SetTimeout(int seconds)

// FIXME: All these are wrapped to return strings
// void Peek(void * buffer, wxUint32 nbytes)
// void Read(void * buffer, wxUint32 nbytes)
// void ReadMsg(void * buffer, wxUint32 nbytes)


%{
    // wxSocketBase Peek(void * buffer, wxUint32 nbytes)
    void wxSocketBase_Peek()
    {
        // get the number of bytes
        int nbytes = (int)wStackPopNumber();
    
        // allocate a buffer of the requested size
        void *buffer = wMalloc( nbytes );
    
        // call Peek    
        ((wxSocketBase *)(wTheCall->self->ptr))->Peek(buffer, nbytes);
    
        // clear the args
        wWrapDerefArgs();
    
        // wrap the buffer into a string
        wStackPushChar( (char *)(buffer), W_TRUE );
    
        // free the buffer
        wFree( buffer );
    }

    // wxSocketBase Read(void * buffer, wxUint32 nbytes)
    void wxSocketBase_Read()
    {
        // get the number of bytes
        int nbytes = (int)wStackPopNumber();
    
        // allocate a buffer of the requested size
        void *buffer = wMalloc( nbytes );
    
        // call Read
        ((wxSocketBase *)(wTheCall->self->ptr))->Read(buffer, nbytes);
    
        // clear the args
        wWrapDerefArgs();
    
        // wrap the buffer into a string
        wStackPushChar( (char *)(buffer), W_TRUE );
    
        // free the buffer
        wFree( buffer );
    }


    // wxSocketBase ReadMsg(void * buffer, wxUint32 nbytes)
    void wxSocketBase_ReadMsg()
    {
        // get the number of bytes
        int nbytes = (int)wStackPopNumber();
    
        // allocate a buffer of the requested size
        void *buffer = wMalloc( nbytes );
    
        // call ReadMsg
        ((wxSocketBase *)(wTheCall->self->ptr))->ReadMsg(buffer, nbytes);
    
        // clear the args
        wWrapDerefArgs();
    
        // wrap the buffer into a string
        wStackPushChar( (char *)(buffer), W_TRUE );
    
        // free the buffer
        wFree( buffer );
    }

%}
%method Peek      wxSocketBase_Peek( int nbytes )
%method Read      wxSocketBase_Read( int nbytes )
%method ReadMsg   wxSocketBase_ReadMsg( int nbytes )

// FIXME: not implemented
// wxSocketBase Unread(const void * buffer, wxUint32 nbytes)
bool Wait(long seconds = -1, long millisecond = 0)
bool WaitForLost(long seconds = -1, long millisecond = 0)
bool WaitForRead(long seconds = -1, long millisecond = 0)
bool WaitForWrite(long seconds = -1, long millisecond = 0)

// FIXME: wrapped
//void Write(const void * buffer, wxUint32 nbytes)
//void WriteMsg(const void * buffer, wxUint32 nbytes)
%{
    // void Write(void * buffer, wxUint32 nbytes)
    void wxSocketBase_Write()
    {
        // get the string
        wVariant *theString = wStackPopString();
        int nbytes = wStringCount( theString );
        void *buffer = (void *)wStringChar( theString );

        // call Write
        ((wxSocketBase *)(wTheCall->self->ptr))->Write(buffer, nbytes);
    
        // clear the args
        wWrapDerefArgs();
    }

    // void WriteMsg(void * buffer, wxUint32 nbytes)
    void wxSocketBase_WriteMsg()
    {
        // get the string
        wVariant *theString = wStackPopString();
        int nbytes = wStringCount( theString );
        void *buffer = (void *)wStringChar( theString );

        // call Write
        ((wxSocketBase *)(wTheCall->self->ptr))->WriteMsg(buffer, nbytes);
    
        // clear the args
        wWrapDerefArgs();
    }
%}
%method Write       wxSocketBase_Write( wxString *buffer )
%method WriteMsg    wxSocketBase_WriteMsg( wxString *buffer )

///////////////////////////////////////////////////////////////////////////////
// wxSocketClient

%class wxSocketClient, wxSocketBase
%include "wx/socket.h"

wxSocketClient(wxSocketFlags flags = wxSOCKET_NONE)
~wxSocketClient()
bool Connect(wxSockAddress& address, bool wait = TRUE)
bool WaitOnConnect(long seconds = -1, long milliseconds = 0)


///////////////////////////////////////////////////////////////////////////////
// wxProtocol

%class wxProtocol, wxSocketClient
%include "wx/protocol/protocol.h"

bool Reconnect()
wxInputStream *GetInputStream(const wxString& path)
bool Abort()
wxString GetContentType()
void  SetUser(const wxString& user)
void SetPassword(const wxString& user)


// error codes
%num wxPROTO_NOERR
%num wxPROTO_NETERR
%num wxPROTO_PROTERR
%num wxPROTO_CONNERR
%num wxPROTO_INVVAL
%num wxPROTO_NOHNDLR
%num wxPROTO_NOFILE
%num wxPROTO_ABRT
%num wxPROTO_RCNCT
// %num wxPROTO_STREAM

///////////////////////////////////////////////////////////////////////////////
// wxFTP

%class wxFTP, wxProtocol
%include "wx/protocol/ftp.h"

wxFTP()
~wxFTP()
bool Abort()
bool CheckCommand(const wxString& command, char ret)
bool Connect(const wxString& host)
char SendCommand(const wxString& command)
const wxString& GetLastResult()
bool ChDir(const wxString& dir)
bool MkDir(const wxString& dir)
bool RmDir(const wxString& dir)
wxString Pwd()
bool Rename(const wxString& src, const wxString& dst)
bool RmFile(const wxString& path)
bool SetAscii()
bool SetBinary()
// FIXME: use a win: and gtk: tag to make this work...
bool SetTransferMode(int mode)
void SetUser(const wxString& user)
void SetPassword(const wxString& passwd)
bool FileExists(const wxString& filename)
int GetFileSize(const wxString& filename)
// bool GetDirList(wxArrayString& files, const wxString& wildcard = "")
// bool GetFilesList(wxArrayString& files, const wxString& wildcard = "")
wxOutputStream * GetOutputStream(const wxString& file)
wxInputStream * GetInputStream(const wxString& path)

// transfer modes
// %num wxFTP_ASCII wxFTP:ASCII
// %num wxFTP_BINARY wxFTP:BINARY


///////////////////////////////////////////////////////////////////////////////
// wxHTTP

%class wxHTTP, wxProtocol
%include "wx/protocol/protocol.h"

wxInputStream * GetInputStream(const wxString& path)
void SetHeader(const wxString& header, const wxString& h_data)
wxString GetHeader(const wxString& header)


///////////////////////////////////////////////////////////////////////////////
// wxUrl

%class wxURL, wxObject
%include "wx/url.h"

wxURL(const wxString& url)
~wxURL()
wxString GetProtocolName() const
wxProtocol& GetProtocol()
wxString GetPath()
int GetError() const
wxInputStream * GetInputStream()
static void SetDefaultProxy(const wxString& url_proxy)
void SetProxy(const wxString& url_proxy)
static wxString ConvertToValidURI(const wxString& uri)


// error codes
%num wxURL_NOERR
%num wxURL_SNTXERR
%num wxURL_NOPROTO
%num wxURL_NOHOST
%num wxURL_NOPATH
%num wxURL_CONNERR
%num wxURL_PROTOERR
