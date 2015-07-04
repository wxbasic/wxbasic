/*************************************************************
    Name:       wrap.hpp
    Purpose:    Wrap wxWindows classes and methods for wxBasic
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/

#ifdef __BORLANDC__
    #pragma warn -8028
    #pragma warn -8006
#endif
#include "wx/calctrl.h"
#include "wx/caret.h"
#include "wx/dnd.h"
#include "wx/imaglist.h"
#include "wx/mdi.h"
#include "wx/socket.h"
#include "wx/tooltip.h"
#include "wx/grid.h"
#include "wx/config.h"
#include "wx/html/helpdata.h"
#include "wx/list.h"
#include "wx/tipdlg.h"
#include "wx/filedlg.h"
#include "wx/colordlg.h"
#include "wx/textdlg.h"
#include "wx/choicdlg.h"
#include "wx/msgdlg.h"
#include "wx/utils.h"
#include "wx/app.h"
#include "wx/window.h"
#include <wx/utils.h>
#include "wx/cmndata.h"
#include "wx/colour.h"
#include <wx/pen.h>
#include "wx/palette.h"
#include "wx/brush.h"
#include "wx/gdicmn.h"
#include "wx/dc.h"
#include "wx/dcmemory.h"
#include "wx/dcclient.h"
#include "wx/dcscreen.h"
#include "wx/bitmap.h"
#include "wx/image.h"
#include "wx/cursor.h"
#include "wx/fdrepdlg.h"
#include "wx/minifram.h"
#include "wx/splitter.h"
#include "wx/checklst.h"
#include "wx/listctrl.h"
#include "wx/treectrl.h"
#include "wx/tbarbase.h"
#include "wx/toolbar.h"
#include "wx/notebook.h"
#include "wx/sashwin.h"
#include "wx/laywin.h"
#include "wx/fontdlg.h"
#include "wx/printdlg.h"
#include "wx/menu.h"
#include "wx/menuitem.h"
#include "wx/event.h"
#include "wx/timer.h"
#include "wx/dialup.h"
#include "wx/process.h"
#include "wx/spinbutt.h"
#include "wx/spinctrl.h"
#include "wx/wizard.h"
#include "wx/layout.h"
#include "wx/font.h"
#include "wx/wxhtml.h"
#include "wx/fs_zip.h"
