/*************************************************************
    Name:       connect.cpp
    Purpose:    implement callbacks for events
    Author:     David Cuny
    Copyright:  (c) 2003 David Cuny <dcuny@lanset.com>
    Licence:    LGPL

    Additions:  Mattia Barbon suggested using wxObject to
                hold the callback handle, and supplied the code.

*************************************************************/

class wCallback: public wxObject {
public:
    wCallback( wSymbol *theRoutine ) { routine = theRoutine; }
    wSymbol  *routine;
};

// connect an object and event to a callback
void wConnect( int id, int useId, void *handle, int theEvent, wSymbol *routine )
{
    // get the object
    if (handle == NULL) {
        wErrorThrow( W_ERROR_CONVERT, "wConnect: object handle is null" );
    }

    // get the handler
    wxEvtHandler *handler = (wxEvtHandler *)handle;

    // don't use id?
    if (!useId) {
        // use default id
        id = ((wxWindow *)handler)->GetId();
    }

    // check args
    if (routine->args != 1) {
        wErrorThrow( W_ERROR_ARGS, "The callback routine %s must take 1 arg, not %d",
                    routine->name, routine->args );
    }

    // attach handler
    handler->Connect( id, 
        (wxEventType) theEvent,
        (wxObjectEventFunction) (wxEventFunction) &wxBasic::HandleEvent,
        new wCallback( routine ) );

}


// disconnect an object and event to a callback
void wDisconnect( int id, int useId, void *handle, int theEvent )
{
    // get the object
    if (handle == NULL) {
        wErrorThrow( W_ERROR_CONVERT, "wDisconnect: object handle is null" );
    }

    // get the handler
    wxEvtHandler *handler = (wxEvtHandler *)handle;

    // don't use id?
    if (!useId) {
        // use default id
        id = ((wxWindow *)handler)->GetId();
    }

    // attach handler
    handler->Disconnect( id, 
        (wxEventType) theEvent,
        (wxObjectEventFunction) (wxEventFunction) &wxBasic::HandleEvent );

}


// call a user defined function
void wRunCallback(wxEvent *event)
{
    // this is a modification of runFunction

    int     priorLocalStart, priorTos, numArgs, localCount, i;
    int     id, e;
    WXTYPE  eventType;
    id = ((wxEvent *)event)->GetId();
    eventType = ((wxEvent *)event)->GetEventType();
    wSymbol *klass;

    // skip if program is halted
    if (wTheHaltFlag || wTheTraceWaitFlag) {
        return;
    }

    // get the callback
    wCallback *theCallback = (wCallback *)event->m_callbackUserData;
    wSymbol *routine = theCallback->routine;

    // redundant test
    if (routine->args != 1) {
        wErrorThrow( W_ERROR_ARGS, "The callback routine %s must take 1 arg, not %d",
            routine->name, routine->args );
	}

	// determine the type of event
	klass = wClassifyEvent( eventType );

	// push the event as a non-temporary object
	wWrapPushObject( klass, W_FALSE, (void *)event );

	// get the pointer to the wrapped event, so it can be destroyed later
	wVariant *theEvent = wStackPeek( 0 );
    wObject *theObject = theEvent->value.object;
   
	/* call the routine: 1 arg in, nothing returned */
	wCallRoutine( routine, 1, 0, NULL, NULL );
   
	// destroy the wrapper holding the event, but don't call the finalize routine
	wFree( theObject );
}

