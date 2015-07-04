wSymbol *_Point;

void wrap_Point_new() {
    // get the results from the stack
    int b = (int)wStackPopNumber();
    int a = (int)wStackPopNumber();

    // create the object
    Point *result = new Point( a, b );

    // push the object onto the stack
    wWrapAndPushObject( _Point, 1, (void *)result );
}


void wrap_Point_getx() {
    int result;
    result = ((Point *)(wTheCall->self->ptr))->GetX();
    wStackPushNumber( (wNumber)result );
}

void wrap_Point_gety() {
    int result;
    result = ((Point *)(wTheCall->self->ptr))->GetY();
    wStackPushNumber( (wNumber)result );
}


void wMakeWrappers() {
    _Point = wWrapClass( "Point", NULL );
    wWrapMethod( _Point, "new", wrap_Point_new, 2, 0 );
    wWrapMethod( _Point, "getx", wrap_Point_getx, 0, 0 );
    wWrapMethod( _Point, "gety", wrap_Point_gety, 0, 0 );
}
