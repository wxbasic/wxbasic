/*
    Name:       connect.cpp
    Purpose:    Callbacks for events in wxBasic
    Author:     David Cuny
    Copyright:  (c) 2002 David Cuny <dcuny@lanset.com>
    Licence:    LGPL

    Additions:  Mattia Barbon suggested using wxObject to hold the
                callback handle, and supplied the code.
*/



class wCallback: public wxObject {
public:
    wCallback( wSymbol *theRoutine ) { routine = theRoutine; }
    wSymbol  *routine;
};

// connect an object and event to a callback
void wConnect( int id, int useId, int handle, int theEvent, wSymbol *routine )
{
    // get the object
    if (handle == 0) {
        wFatal( W_RUNTIME, "wConnect: object handle is null" );
    }

    // get the handler
    wxEvtHandler *handler = (wxEvtHandler *)wGetObject( handle );

    // don't use id?
    if (!useId) {
        // use default id
        id = ((wxWindow *)handler)->GetId();
    }

    // check args
    if (routine->args != 1) {
        wFatal( W_RUNTIME, "The callback routine %s must take 1 arg, not %d",
                    routine->name, routine->args );
    }

    // attach handler
    handler->Connect( id, 
        (wxEventType) theEvent,
        (wxObjectEventFunction) (wxEventFunction) &wxBasic::HandleEvent,
        new wCallback( routine ) );

}


// call a user defined function
void wRunCallback(wxEvent *event)
{
    // this is a modification of runFunction

    int     priorLocalStart, priorTos, numArgs, localCount, i, classIndex;
    int     id, eventObject, e;
    WXTYPE  eventType;
    id = ((wxEvent *)event)->GetId();
    eventObject = (int)((wxEvent *)event)->GetEventObject();
    eventType = ((wxEvent *)event)->GetEventType();

    // wrap the event
    classIndex = wClassifyEvent( eventType );
    if (classIndex == -1) {
        classIndex = _wxEvent;
    }

    e = (int)wAddObject( classIndex, (int)(wxEvent *)event );

    // get the callback
    wCallback *theCallback = (wCallback *)event->m_callbackUserData;
    wSymbol *routine = theCallback->routine;
    if (routine->forward) {
        wFatal( W_RUNTIME, "Callback routine %s has not been defined yet", routine->name );
    }

    // redundant test
    if (routine->args != 1) {
        wFatal( W_RUNTIME, "The callback routine %s must take 1 arg, not %d",
            routine->name, routine->args );
    }

    /* return value */
    wPushNumber( 0 );

    /* argc */
    wPushNumber( 1 );

    /* start of local variables */
    priorLocalStart = wLocalStart;
    priorTos = wTos;

    /* mark start of created objects */
    wPushCreateStack( 0 );

    /* evaluate parameters */
    wPushNumber( (wNumber)e );

    /* number of args */
    numArgs = (wTos-priorTos);
    wData[priorTos].value.number = (wNumber)numArgs;

    /* allocate locals */
    localCount = routine->optArgs + routine->locals;
    for ( i = 0; i < (localCount - numArgs); i++ ) {
        wPushNumber( 0 );
    }

    /* set start of locals */
    wLocalStart = priorTos;

    /* run code */
    wEval( routine->code );

    /* exit routine flag set? */
    if (wExitRoutineFlag != 0) {
        wExitRoutineFlag = 0;
    }

    /* destroy created objects */
    wClearCreateStack();

    /* clear locals off stack */
    for ( i = localCount; i > 0; i-- ) {
        /* need to free record? */
        if ( i > numArgs && wData[wTos].datatype == W_DATA_ARRAY) {
            wFreeArray( wData[wTos].value.array );
        }
        wPopNumber();
    }

    /* drop argc */
    wDropTos();

    /* drop result */
    wDropTos();

    /* restore marker */
    wLocalStart = priorLocalStart;

    /* destroy, but don't run destructor */
    wRemoveObject( e );

}
