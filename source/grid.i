

wxGrid, wxScrolledWindow
<wx/grid.h>

wxGrid(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxWANTS_CHARS, const wxString& name = wxPanelNameStr)
~wxGrid()
bool AppendCols(int numCols = 1, bool updateLabels = true)
bool AppendRows(int numRows = 1, bool updateLabels = true)
void AutoSize()
void AutoSizeColOrRow(int n, bool setAsMin, bool column)
void AutoSizeColumn(int col, bool setAsMin = true)
void AutoSizeColumns(bool setAsMin = true)
void AutoSizeRow(int row, bool setAsMin = true)
void AutoSizeRows(bool setAsMin = true)
void BeginBatch()
wxRect BlockToDeviceRect(const wxGridCellCoords & topLeft, const wxGridCellCoords & bottomRight)
bool CanDragColSize()
bool CanDragRowSize()
bool CanDragGridSize()
bool CanEnableCellControl() const
bool CanHaveAttributes()
wxRect CellToRect(int row, int col)
// FIXME! Need alias
//wxRect CellToRect(const wxGridCellCoords& coords)
void ClearGrid()
void ClearSelection()
bool CreateGrid(int numRows, int numCols, wxGrid::wxGridSelectionModes selmode = wxGrid::wxGridSelectCells)
bool DeleteCols(int pos = 0, int numCols = 1, bool updateLabels = true)
bool DeleteRows(int pos = 0, int numRows = 1, bool updateLabels = true)
void DisableCellEditControl()
void DisableDragColSize()
void DisableDragGridSize()
void DisableDragRowSize()
void EnableCellEditControl(bool enable = true)
// issues one of these two:
//wxEVT_GRID_EDITOR_SHOWN
//wxEVT_GRID_EDITOR_HIDDEN
void EnableDragColSize(bool enable = true)
void EnableDragGridSize(bool enable = true)
void EnableDragRowSize(bool enable = true)
void EnableEditing(bool edit)
void EnableGridLines(bool enable = true)
void EndBatch()
void Fit()
void ForceRefresh()
int GetBatchCount()
// FIXME: needs wrapper
void GetCellAlignment(int row, int col, int* horiz, int* vert)
wxColour GetCellBackgroundColour(int row, int col)
wxGridCellEditor* GetCellEditor(int row, int col)
wxFont GetCellFont(int row, int col)
wxGridCellRenderer* GetCellRenderer(int row, int col)
wxColour GetCellTextColour(int row, int col)
wxString GetCellValue(int row, int col)
// FIXME: alias
//wxString GetCellValue(const wxGridCellCoords&coords)
int GetColLeft(int col) const
void GetColLabelAlignment(int* horiz, int* vert)
int GetColLabelSize()
wxString GetColLabelValue(int col)
int GetColMinimalAcceptableWidth()
int GetColMinimalWidth(int col) const
int GetColRight(int col) const
int GetColSize(int col)
void GetDefaultCellAlignment(int* horiz, int* vert)
wxColour GetDefaultCellBackgroundColour()
wxFont GetDefaultCellFont()
wxColour GetDefaultCellTextColour()
int GetDefaultColLabelSize()
int GetDefaultColSize()
wxGridCellEditor* GetDefaultEditor() const
wxGridCellEditor* GetDefaultEditorForCell(int row, int col) const
// FIXME: need alias
//wxGridCellEditor* GetDefaultEditorForCell(const wxGridCellCoords& c) const
wxGridCellEditor* GetDefaultEditorForType(const wxString& typeName) const
wxGridCellRenderer* GetDefaultRenderer() const
wxGridCellRenderer* GetDefaultRendererForCell(int row, int col) const
wxGridCellRenderer* GetDefaultRendererForType(const wxString& typeName) const
int GetDefaultRowLabelSize()
int GetDefaultRowSize()
int GetGridCursorCol()
int GetGridCursorRow()
wxColour GetGridLineColour()
bool GridLinesEnabled()
wxColour GetLabelBackgroundColour()
wxFont GetLabelFont()
wxColour GetLabelTextColour()
int GetNumberCols()
int GetNumberRows()
wxGridCellAttr* GetOrCreateCellAttr(int row, int col) const
int GetRowMinimalAcceptableHeight()
int GetRowMinimalHeight(int col) const
// FIXME: needs wrapper
//void GetRowLabelAlignment(int* horiz, int* vert)
int GetRowLabelSize()
wxString GetRowLabelValue(int row)
int GetRowSize(int row)
int GetScrollLinesX() const
int GetScrollLinesY() const
wxGrid::wxGridSelectionModes GetSelectionMode() const
wxGridCellCoordsArray GetSelectedCells() const
wxArrayInt GetSelectedCols() const
wxArrayInt GetSelectedRows() const
wxColour GetSelectionBackground() const
wxGridCellCoordsArray GetSelectionBlockTopLeft() const
wxGridCellCoordsArray GetSelectionBlockBottomRight() const
wxColour GetSelectionForeground() const
wxGridTableBase * GetTable() const
int GetViewWidth()
void HideCellEditControl()
void InitColWidths()
void InitRowHeights()
bool InsertCols(int pos = 0, int numCols = 1, bool updateLabels = true)
bool InsertRows(int pos = 0, int numRows = 1, bool updateLabels = true)
bool IsCellEditControlEnabled() const
bool IsCurrentCellReadOnly() const
bool IsEditable()
bool IsInSelection(int row, int col) const
// FIXME: needs wrapper
//bool IsInSelection(const wxGridCellCoords& coords) const
bool IsReadOnly(int row, int col) const
bool IsSelection()
bool IsVisible(int row, int col, bool wholeCellVisible = true)
// FIXME: needs wrapper
//bool IsVisible(const wxGridCellCoords& coords, bool wholeCellVisible = true)
void MakeCellVisible(int row, int col)
// FIXME: needs wrapper
//void MakeCellVisible(const wxGridCellCoords& coords)
bool MoveCursorDown(bool expandSelection)
bool MoveCursorLeft(bool expandSelection)
bool MoveCursorRight(bool expandSelection)
bool MoveCursorUp(bool expandSelection)
bool MoveCursorDownBlock(bool expandSelection)
bool MoveCursorLeftBlock(bool expandSelection)
bool MoveCursorRightBlock(bool expandSelection)
bool MoveCursorUpBlock(bool expandSelection)
bool MovePageDown()
bool MovePageUp()
void RegisterDataType(const wxString& typeName, wxGridCellRenderer* renderer, wxGridCellEditor* editor)
void SaveEditControlValue()
void SelectAll()
void SelectBlock(int topRow, int leftCol, int bottomRow, int rightCol, bool addToSelected = false)
// FIXME: needs wrapper
//void SelectBlock(const wxGridCellCoords& topLeft, const wxGridCellCoords& bottomRight, bool addToSelected = false)
void SelectCol(int col, bool addToSelected = false)
wxRect SelectionToDeviceRect()
void SelectRow(int row, bool addToSelected = false)
void SetCellAlignment(int row, int col, int horiz, int vert)
// FIXME: needs alias (or wrapper)
// void SetCellAlignment(int align, int row, int col)
void SetCellBackgroundColour(int row, int col, const wxColour& colour)
void SetCellEditor(int row, int col, wxGridCellEditor* editor)
void SetCellFont(int row, int col, const wxFont& font)
void SetCellRenderer(int row, int col, wxGridCellRenderer* renderer)
void SetCellTextColour(int row, int col, const wxColour& colour)
// FIXME: needs alias
//void SetCellTextColour(const wxColour& val, int row, int col)
//void SetCellTextColour(const wxColour& colour)
void SetCellValue(int row, int col, const wxString& s)
// FIXME: needs alias
//void SetCellValue(const wxGridCellCoords& coords, const wxString& s)
//void SetCellValue(const wxString& val, int row, int col)
void SetColAttr(int col, wxGridCellAttr* attr)
void SetColFormatBool(int col)
void SetColFormatNumber(int col)
void SetColFormatFloat(int col, int width = -1, int precision = -1)
void SetColFormatCustom(int col, const wxString& typeName)
void SetColLabelAlignment(int horiz, int vert)
void SetColLabelSize(int height)
void SetColLabelValue(int col, const wxString& value)
void SetColMinimalWidth(int col, int width
void SetColMinimalAcceptableWidth(int width)
void SetColSize(int col, int width)
void SetDefaultCellAlignment(int horiz, int vert)
void SetDefaultCellBackgroundColour(const wxColour& colour)
void SetDefaultCellFont(const wxFont& font)
void SetDefaultCellTextColour(const wxColour& colour)
void SetDefaultEditor(wxGridCellEditor* editor)
void SetDefaultRenderer(wxGridCellRenderer* renderer)
void SetDefaultColSize(int width, bool resizeExistingCols = false)
void SetDefaultRowSize(int height, bool resizeExistingRows = false)
void SetGridCursor(int row, int col)
void SetGridLineColour(const wxColour&colour)
void SetLabelBackgroundColour(const wxColour& colour)
void SetLabelFont(const wxFont& font)
void SetLabelTextColour(const wxColour& colour)
void SetMargins(int extraWidth, int extraHeight)
int SetOrCalcColumnSizes(bool calcOnly, bool setAsMin = true)
int SetOrCalcRowSizes(bool calcOnly, bool setAsMin = true)
void SetReadOnly(int row, int col, bool isReadOnly = true)
void SetRowAttr(int row, wxGridCellAttr* attr)
void SetRowLabelAlignment(int horiz, int vert)
void SetRowLabelSize(int width)
void SetRowLabelValue(int row, const wxString& value)
void SetRowMinimalHeight(int row, int height)
void SetRowMinimalAcceptableHeight(int height)
void SetRowSize(int row, int height)
void SetScrollLinesX(int x)
void SetScrollLinesY(int y)
void SetSelectionBackground(const wxColour& c)
void SetSelectionForeground(const wxColour& c)
void SetSelectionMode(wxGrid::wxGridSelectionModes selmode)
// FIXME: enums?
//wxGrid::wxGridSelectCells
//wxGrid::wxGridSelectRows
//wxGrid::wxGridSelectColumns
bool SetTable(wxGridTableBase* table, bool takeOwnership = false, wxGrid::wxGridSelectionModes selmode = wxGrid::wxGridSelectCells)
void ShowCellEditControl()
int XToCol(int x)
int XToEdgeOfCol(int x)
// fixme: need this constant?
// wxNOT_FOUND
int YToEdgeOfRow(int y)
int YToRow(int y)









--

// wxGridEvent
wxGridEvent, wxNotifyEvent
<wx/grid.h>

wxGridEvent(int id, wxEventType type, wxObject* obj, int row = -1, int col = -1, int x = -1, int y = -1, bool sel = true, bool control = false, bool shift = false, bool alt = false, bool meta = false)
bool AltDown()
bool ControlDown()
int GetCol()
wxPoint GetPosition()
int GetRow()
bool MetaDown()
bool Selecting()
bool ShiftDown()

wxEVT_GRID_CELL_LEFT_CLICK
wxEVT_GRID_CELL_RIGHT_CLICK
wxEVT_GRID_CELL_LEFT_DCLICK
wxEVT_GRID_CELL_RIGHT_DCLICK
wxEVT_GRID_LABEL_LEFT_CLICK
wxEVT_GRID_LABEL_RIGHT_CLICK
wxEVT_GRID_LABEL_LEFT_DCLICK
wxEVT_GRID_LABEL_RIGHT_DCLICK
wxEVT_GRID_CELL_CHANGE
wxEVT_GRID_SELECT_CELL
wxEVT_GRID_EDITOR_HIDDEN
wxEVT_GRID_EDITOR_SHOWN
wxEVT_GRID_CELL_LEFT_CLICK
wxEVT_GRID_CELL_RIGHT_CLICK
wxEVT_GRID_CELL_LEFT_DCLICK
wxEVT_GRID_CELL_RIGHT_DCLICK
wxEVT_GRID_LABEL_LEFT_CLICK
wxEVT_GRID_LABEL_RIGHT_CLICK
wxEVT_GRID_LABEL_LEFT_DCLICK
wxEVT_GRID_LABEL_RIGHT_DCLICK
wxEVT_GRID_CELL_CHANGE
wxEVT_GRID_SELECT_CELL
wxEVT_GRID_EDITOR_HIDDEN
wxEVT_GRID_EDITOR_SHOWN

// wxGridSizeEvent
wxGridSizeEvent, wxNotifyEvent
<wx/grid.h>

wxGridSizeEvent(int id, wxEventType type, wxObject* obj, int rowOrCol = -1, int x = -1, int y = -1, bool control = false, bool shift = false, bool alt = false, bool meta = false)
bool AltDown()
bool ControlDown()
wxPoint GetPosition()
int GetRowOrCol()
bool MetaDown()
bool ShiftDown()

wxEVT_GRID_COL_SIZE
wxEVT_GRID_ROW_SIZE

// wxGridRangeSelectEvent
wxGridRangeSelectEvent, wxNotifyEvent
<wx/grid.h>

wxEVT_GRID_RANGE_SELECT

wxGridRangeSelectEvent(int id, wxEventType type, wxObject* obj, const wxGridCellCoords& topLeft, const wxGridCellCoords& bottomRight, bool sel = true, bool control = false, bool shift = false, bool alt = false, bool meta = false)
bool AltDown()
bool ControlDown()
wxGridCellCoords GetBottomRightCoords()
int GetBottomRow()
int GetLeftCol()
int GetRightCol()
wxGridCellCoords GetTopLeftCoords()
int GetTopRow()
bool MetaDown()
bool Selecting()
bool ShiftDown()
