/*************************************************************
    Name:       events.c
    Purpose:    classify wxWindows events
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL
*************************************************************/


/* classifyEvent: return pointer to event class, or NULL if not found */
wSymbol *wClassifyEvent(WXTYPE eventType)
{
    /* wxWizardEvent */
//$    if (eventType == wxEVT_WIZARD_PAGE_CHANGED               ) return _wxWizardEvent;
//$    if (eventType == wxEVT_WIZARD_PAGE_CHANGING              ) return _wxWizardEvent;
//$    if (eventType == wxEVT_WIZARD_CANCEL                     ) return _wxWizardEvent;

    /* wxMenuEvent */
    if (eventType == wxEVT_MENU_HIGHLIGHT                    ) return _wxMenuEvent;

    /* wxSizeEvent */
    if (eventType == wxEVT_SIZE                              ) return _wxSizeEvent;

    /* wxKeyEvent */
    if (eventType == wxEVT_KEY_UP                            ) return _wxKeyEvent;
    if (eventType == wxEVT_KEY_DOWN                          ) return _wxKeyEvent;
    if (eventType == wxEVT_CHAR_HOOK                         ) return _wxKeyEvent;

    /* generic */
    if (eventType == wxEVT_NC_PAINT                          ) return _wxEvent;
    if (eventType == wxEVT_PALETTE_CHANGED                   ) return _wxEvent;
    if (eventType == wxEVT_CLOSE_WINDOW                      ) return _wxEvent;
    if (eventType == wxEVT_CHAR                              ) return _wxEvent;
    if (eventType == wxEVT_MEASURE_ITEM                      ) return _wxEvent;
    if (eventType == wxEVT_POWER                             ) return _wxEvent;
    if (eventType == wxEVT_COMPARE_ITEM                      ) return _wxEvent;
    if (eventType == wxEVT_QUERY_END_SESSION                 ) return _wxEvent;
    if (eventType == wxEVT_NAVIGATION_KEY                    ) return _wxEvent;
    if (eventType == wxEVT_PAINT_ICON                        ) return _wxEvent;
    if (eventType == wxEVT_SETTING_CHANGED                   ) return _wxEvent;
    if (eventType == wxEVT_MAXIMIZE                          ) return _wxEvent;
    if (eventType == wxEVT_DRAW_ITEM                         ) return _wxEvent;
    if (eventType == wxEVT_ICONIZE                           ) return _wxEvent;
    if (eventType == wxEVT_CREATE                            ) return _wxEvent;
    if (eventType == wxEVT_SHOW                              ) return _wxEvent;
    if (eventType == wxEVT_MOUSE_CAPTURE_CHANGED             ) return _wxEvent;
    if (eventType == wxEVT_END_SESSION                       ) return _wxEvent;
    if (eventType == wxEVT_QUERY_NEW_PALETTE                 ) return _wxEvent;
    if (eventType == wxEVT_CONTEXT_MENU                      ) return _wxEvent;
    if (eventType == wxEVT_DESTROY                           ) return _wxEvent;
    if (eventType == wxEVT_SET_CURSOR                        ) return _wxEvent;

    /* wxDropFilesEvent */
    if (eventType == wxEVT_DROP_FILES                        ) return _wxDropFilesEvent;

    /* wxScrollEvent */
    if (eventType == wxEVT_SCROLL_TOP                        ) return _wxScrollEvent;
    if (eventType == wxEVT_SCROLL_THUMBTRACK                 ) return _wxScrollEvent;
    if (eventType == wxEVT_SCROLL_THUMBRELEASE               ) return _wxScrollEvent;
    if (eventType == wxEVT_SCROLL_LINEUP                     ) return _wxScrollEvent;
    if (eventType == wxEVT_SCROLL_PAGEUP                     ) return _wxScrollEvent;
    if (eventType == wxEVT_SCROLL_PAGEDOWN                   ) return _wxScrollEvent;
    if (eventType == wxEVT_SCROLL_LINEDOWN                   ) return _wxScrollEvent;
    if (eventType == wxEVT_SCROLL_BOTTOM                     ) return _wxScrollEvent;

    /* wxCalendarEvent */
    if (eventType == wxEVT_CALENDAR_MONTH_CHANGED            ) return _wxCalendarEvent;
    if (eventType == wxEVT_CALENDAR_DAY_CHANGED              ) return _wxCalendarEvent;
    if (eventType == wxEVT_CALENDAR_YEAR_CHANGED             ) return _wxCalendarEvent;
    if (eventType == wxEVT_CALENDAR_WEEKDAY_CLICKED          ) return _wxCalendarEvent;
    if (eventType == wxEVT_CALENDAR_DOUBLECLICKED            ) return _wxCalendarEvent;
    if (eventType == wxEVT_CALENDAR_SEL_CHANGED              ) return _wxCalendarEvent;

    /* wxDialupEvent */
    if (eventType == wxEVT_DIALUP_DISCONNECTED               ) return _wxDialUpEvent;
    if (eventType == wxEVT_DIALUP_CONNECTED                  ) return _wxDialUpEvent;

    /* wxScrollWinEvent */
    if (eventType == wxEVT_SCROLLWIN_TOP                     ) return _wxScrollWinEvent;
    if (eventType == wxEVT_SCROLLWIN_LINEUP                  ) return _wxScrollWinEvent;
    if (eventType == wxEVT_SCROLLWIN_PAGEUP                  ) return _wxScrollWinEvent;
    if (eventType == wxEVT_SCROLLWIN_THUMBRELEASE            ) return _wxScrollWinEvent;
    if (eventType == wxEVT_SCROLLWIN_BOTTOM                  ) return _wxScrollWinEvent;
    if (eventType == wxEVT_SCROLLWIN_PAGEDOWN                ) return _wxScrollWinEvent;
    if (eventType == wxEVT_SCROLLWIN_THUMBTRACK              ) return _wxScrollWinEvent;
    if (eventType == wxEVT_SCROLLWIN_LINEDOWN                ) return _wxScrollWinEvent;

    /* wxListEvent */
    if (eventType == wxEVT_COMMAND_LIST_BEGIN_RDRAG          ) return _wxListEvent;
    if (eventType == wxEVT_COMMAND_LIST_ITEM_MIDDLE_CLICK    ) return _wxListEvent;
    if (eventType == wxEVT_COMMAND_LIST_INSERT_ITEM          ) return _wxListEvent;
    if (eventType == wxEVT_COMMAND_LIST_ITEM_DESELECTED      ) return _wxListEvent;
    if (eventType == wxEVT_COMMAND_LIST_KEY_DOWN             ) return _wxListEvent;
    if (eventType == wxEVT_COMMAND_LIST_DELETE_ALL_ITEMS     ) return _wxListEvent;
    if (eventType == wxEVT_COMMAND_LIST_BEGIN_LABEL_EDIT     ) return _wxListEvent;
    if (eventType == wxEVT_COMMAND_LIST_END_LABEL_EDIT       ) return _wxListEvent;
    if (eventType == wxEVT_COMMAND_LIST_ITEM_SELECTED        ) return _wxListEvent;
    if (eventType == wxEVT_COMMAND_LIST_GET_INFO             ) return _wxListEvent;
    if (eventType == wxEVT_COMMAND_LIST_DELETE_ITEM          ) return _wxListEvent;
    if (eventType == wxEVT_COMMAND_LIST_SET_INFO             ) return _wxListEvent;
    if (eventType == wxEVT_COMMAND_LIST_BEGIN_DRAG           ) return _wxListEvent;
    if (eventType == wxEVT_COMMAND_LIST_ITEM_ACTIVATED       ) return _wxListEvent;
    if (eventType == wxEVT_COMMAND_LIST_COL_CLICK            ) return _wxListEvent;
    if (eventType == wxEVT_COMMAND_LIST_ITEM_RIGHT_CLICK     ) return _wxListEvent;

    /* wxIdleEvent */
    if (eventType == wxEVT_IDLE                              ) return _wxIdleEvent;

    /* wxNotebookEvent */
    if (eventType == wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED     ) return _wxNotebookEvent;
    if (eventType == wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGING    ) return _wxNotebookEvent;

    /* wxProcessEvent */
    if (eventType == wxEVT_END_PROCESS                       ) return _wxProcessEvent;

    /* wxMouseEvent */
    if (eventType == wxEVT_RIGHT_DCLICK                      ) return _wxMouseEvent;
    if (eventType == wxEVT_LEFT_DOWN                         ) return _wxMouseEvent;
    if (eventType == wxEVT_RIGHT_UP                          ) return _wxMouseEvent;
    if (eventType == wxEVT_NC_MIDDLE_UP                      ) return _wxMouseEvent;
    if (eventType == wxEVT_RIGHT_DOWN                        ) return _wxMouseEvent;
    if (eventType == wxEVT_NC_RIGHT_DOWN                     ) return _wxMouseEvent;
    if (eventType == wxEVT_NC_RIGHT_UP                       ) return _wxMouseEvent;
    if (eventType == wxEVT_KILL_FOCUS                        ) return _wxMouseEvent;
    if (eventType == wxEVT_MOTION                            ) return _wxMouseEvent;
    if (eventType == wxEVT_NC_LEFT_DOWN                      ) return _wxMouseEvent;
    if (eventType == wxEVT_NC_MOTION                         ) return _wxMouseEvent;
    if (eventType == wxEVT_NC_LEAVE_WINDOW                   ) return _wxMouseEvent;
    if (eventType == wxEVT_MIDDLE_DOWN                       ) return _wxMouseEvent;
    if (eventType == wxEVT_LEFT_DCLICK                       ) return _wxMouseEvent;
    if (eventType == wxEVT_NC_ENTER_WINDOW                   ) return _wxMouseEvent;
    if (eventType == wxEVT_MIDDLE_UP                         ) return _wxMouseEvent;
    if (eventType == wxEVT_NC_MIDDLE_DOWN                    ) return _wxMouseEvent;
    if (eventType == wxEVT_MIDDLE_DCLICK                     ) return _wxMouseEvent;
    if (eventType == wxEVT_NC_RIGHT_DCLICK                   ) return _wxMouseEvent;
    if (eventType == wxEVT_NC_LEFT_DCLICK                    ) return _wxMouseEvent;
    if (eventType == wxEVT_SET_FOCUS                         ) return _wxMouseEvent;
    if (eventType == wxEVT_LEAVE_WINDOW                      ) return _wxMouseEvent;
    if (eventType == wxEVT_NC_LEFT_UP                        ) return _wxMouseEvent;
    if (eventType == wxEVT_ENTER_WINDOW                      ) return _wxMouseEvent;
    if (eventType == wxEVT_LEFT_UP                           ) return _wxMouseEvent;
    if (eventType == wxEVT_NC_MIDDLE_DCLICK                  ) return _wxMouseEvent;

    /* wxCommandEvent */
    if (eventType == wxEVT_COMMAND_RIGHT_DCLICK              ) return _wxCommandEvent;
    if (eventType == wxEVT_COMMAND_LISTBOX_DOUBLECLICKED     ) return _wxCommandEvent;
    if (eventType == wxEVT_COMMAND_LEFT_CLICK                ) return _wxCommandEvent;
    if (eventType == wxEVT_COMMAND_SPINCTRL_UPDATED          ) return _wxCommandEvent;
    if (eventType == wxEVT_COMMAND_VLBOX_SELECTED            ) return _wxCommandEvent;
    if (eventType == wxEVT_COMMAND_TEXT_UPDATED              ) return _wxCommandEvent;
    if (eventType == wxEVT_COMMAND_BUTTON_CLICKED            ) return _wxCommandEvent;
    if (eventType == wxEVT_COMMAND_CHECKLISTBOX_TOGGLED      ) return _wxCommandEvent;
    if (eventType == wxEVT_COMMAND_RADIOBUTTON_SELECTED      ) return _wxCommandEvent;
    if (eventType == wxEVT_COMMAND_RIGHT_CLICK               ) return _wxCommandEvent;
    if (eventType == wxEVT_COMMAND_LISTBOX_SELECTED          ) return _wxCommandEvent;
    if (eventType == wxEVT_COMMAND_KILL_FOCUS                ) return _wxCommandEvent;
    if (eventType == wxEVT_COMMAND_CHECKBOX_CLICKED          ) return _wxCommandEvent;
    if (eventType == wxEVT_COMMAND_SET_FOCUS                 ) return _wxCommandEvent;
    if (eventType == wxEVT_COMMAND_RADIOBOX_SELECTED         ) return _wxCommandEvent;
    if (eventType == wxEVT_COMMAND_TOOL_ENTER                ) return _wxCommandEvent;
    if (eventType == wxEVT_COMMAND_SCROLLBAR_UPDATED         ) return _wxCommandEvent;
    if (eventType == wxEVT_COMMAND_SLIDER_UPDATED            ) return _wxCommandEvent;
    if (eventType == wxEVT_COMMAND_TEXT_ENTER                ) return _wxCommandEvent;
    if (eventType == wxEVT_COMMAND_COMBOBOX_SELECTED         ) return _wxCommandEvent;
    if (eventType == wxEVT_COMMAND_CHOICE_SELECTED           ) return _wxCommandEvent;
    if (eventType == wxEVT_COMMAND_MENU_SELECTED             ) return _wxCommandEvent;
    if (eventType == wxEVT_COMMAND_TOOL_CLICKED              ) return _wxCommandEvent;
    if (eventType == wxEVT_COMMAND_ENTER                     ) return _wxCommandEvent;
    if (eventType == wxEVT_COMMAND_LEFT_DCLICK               ) return _wxCommandEvent;
    if (eventType == wxEVT_COMMAND_TOOL_RCLICKED             ) return _wxCommandEvent;

    /* wxUpdateUIEvent */
    if (eventType == wxEVT_UPDATE_UI                         ) return _wxUpdateUIEvent;

    /* wxTreeEvent */
    if (eventType == wxEVT_COMMAND_TREE_BEGIN_RDRAG          ) return _wxTreeEvent;
    if (eventType == wxEVT_COMMAND_TREE_KEY_DOWN             ) return _wxTreeEvent;
    if (eventType == wxEVT_COMMAND_TREE_ITEM_ACTIVATED       ) return _wxTreeEvent;
    if (eventType == wxEVT_COMMAND_TREE_GET_INFO             ) return _wxTreeEvent;
    if (eventType == wxEVT_COMMAND_TREE_ITEM_EXPANDING       ) return _wxTreeEvent;
    if (eventType == wxEVT_COMMAND_TREE_SEL_CHANGED          ) return _wxTreeEvent;
    if (eventType == wxEVT_COMMAND_TREE_ITEM_COLLAPSED       ) return _wxTreeEvent;
    if (eventType == wxEVT_COMMAND_TREE_SET_INFO             ) return _wxTreeEvent;
    if (eventType == wxEVT_COMMAND_TREE_BEGIN_LABEL_EDIT     ) return _wxTreeEvent;
    if (eventType == wxEVT_COMMAND_TREE_ITEM_EXPANDED        ) return _wxTreeEvent;
    if (eventType == wxEVT_COMMAND_TREE_SEL_CHANGING         ) return _wxTreeEvent;
    if (eventType == wxEVT_COMMAND_TREE_ITEM_COLLAPSING      ) return _wxTreeEvent;
    if (eventType == wxEVT_COMMAND_TREE_BEGIN_DRAG           ) return _wxTreeEvent;
    if (eventType == wxEVT_COMMAND_TREE_END_DRAG             ) return _wxTreeEvent;
    if (eventType == wxEVT_COMMAND_TREE_DELETE_ITEM          ) return _wxTreeEvent;
    if (eventType == wxEVT_COMMAND_TREE_ITEM_MIDDLE_CLICK    ) return _wxTreeEvent;
    if (eventType == wxEVT_COMMAND_TREE_ITEM_RIGHT_CLICK     ) return _wxTreeEvent;
    if (eventType == wxEVT_COMMAND_TREE_END_LABEL_EDIT       ) return _wxTreeEvent;

    /* wxInitDialogEvent */
    if (eventType == wxEVT_INIT_DIALOG                       ) return _wxInitDialogEvent;

    /* wxEraseEvent */
    if (eventType == wxEVT_ERASE_BACKGROUND                  ) return _wxEraseEvent;

    /* wxActivateEvent */
    if (eventType == wxEVT_ACTIVATE_APP                      ) return _wxActivateEvent;
    if (eventType == wxEVT_ACTIVATE                          ) return _wxActivateEvent;

    /* wxSocketEvent */
    if (eventType == wxEVT_SOCKET                            ) return _wxSocketEvent;

    /* wxSysColourChangedEvent */
    if (eventType == wxEVT_SYS_COLOUR_CHANGED                ) return _wxSysColourChangedEvent;

    /* wxPaintEvent */
    if (eventType == wxEVT_PAINT                             ) return _wxPaintEvent;

    /* wxJoystickEvent; */
    if (eventType == wxEVT_JOY_ZMOVE                         ) return _wxJoystickEvent;;
    if (eventType == wxEVT_JOY_BUTTON_DOWN                   ) return _wxJoystickEvent;;
    if (eventType == wxEVT_JOY_MOVE                          ) return _wxJoystickEvent;;
    if (eventType == wxEVT_JOY_BUTTON_UP                     ) return _wxJoystickEvent;;

    /* wxMoveEvent */
    if (eventType == wxEVT_MOVE                              ) return _wxMoveEvent;

    /* wxTimerEvent */
    if (eventType == wxEVT_TIMER                             ) return _wxTimerEvent;

    /* splitter */
    if (eventType == wxEVT_COMMAND_SPLITTER_SASH_POS_CHANGING) return _wxSplitterEvent;
    if (eventType == wxEVT_COMMAND_SPLITTER_SASH_POS_CHANGED ) return _wxSplitterEvent;
    if (eventType == wxEVT_COMMAND_SPLITTER_DOUBLECLICKED    ) return _wxSplitterEvent;
    if (eventType == wxEVT_COMMAND_SPLITTER_UNSPLIT          ) return _wxSplitterEvent;

    /* wxStyledTextEvent */
    if (eventType == wxEVT_STC_CHANGE                       ) return _wxStyledTextEvent;
    if (eventType == wxEVT_STC_STYLENEEDED                  ) return _wxStyledTextEvent;
    if (eventType == wxEVT_STC_CHARADDED                    ) return _wxStyledTextEvent;
    if (eventType == wxEVT_STC_SAVEPOINTREACHED             ) return _wxStyledTextEvent;
    if (eventType == wxEVT_STC_SAVEPOINTLEFT                ) return _wxStyledTextEvent;
    if (eventType == wxEVT_STC_ROMODIFYATTEMPT              ) return _wxStyledTextEvent;
    if (eventType == wxEVT_STC_KEY                          ) return _wxStyledTextEvent;
    if (eventType == wxEVT_STC_DOUBLECLICK                  ) return _wxStyledTextEvent;
    if (eventType == wxEVT_STC_UPDATEUI                     ) return _wxStyledTextEvent;
    if (eventType == wxEVT_STC_MODIFIED                     ) return _wxStyledTextEvent;
    if (eventType == wxEVT_STC_MACRORECORD                  ) return _wxStyledTextEvent;
    if (eventType == wxEVT_STC_MARGINCLICK                  ) return _wxStyledTextEvent;
    if (eventType == wxEVT_STC_NEEDSHOWN                    ) return _wxStyledTextEvent;
    if (eventType == wxEVT_STC_POSCHANGED                   ) return _wxStyledTextEvent;
    if (eventType == wxEVT_STC_PAINTED                      ) return _wxStyledTextEvent;
    if (eventType == wxEVT_STC_USERLISTSELECTION            ) return _wxStyledTextEvent;
    if (eventType == wxEVT_STC_URIDROPPED                   ) return _wxStyledTextEvent;
    if (eventType == wxEVT_STC_DWELLSTART                   ) return _wxStyledTextEvent;
    if (eventType == wxEVT_STC_DWELLEND                     ) return _wxStyledTextEvent;
    if (eventType == wxEVT_STC_START_DRAG                   ) return _wxStyledTextEvent;
    if (eventType == wxEVT_STC_DRAG_OVER                    ) return _wxStyledTextEvent;
    if (eventType == wxEVT_STC_DO_DROP                      ) return _wxStyledTextEvent;
    if (eventType == wxEVT_STC_ZOOM                         ) return _wxStyledTextEvent;
    if (eventType == wxEVT_STC_HOTSPOT_CLICK                ) return _wxStyledTextEvent;
    if (eventType == wxEVT_STC_HOTSPOT_DCLICK               ) return _wxStyledTextEvent;
    if (eventType == wxEVT_STC_CALLTIP_CLICK                ) return _wxStyledTextEvent;

    /* probably user defined */
    return _wxEvent;
}
