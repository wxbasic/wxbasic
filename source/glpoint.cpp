#include <stdio.h>

/*************************************************************
    Name:       glpoint.cpp
    Purpose:    3D point class of OpenGL support
    Author:     David Cuny
    Copyright:  (c) 2005 David Cuny <dcuny@lanset.com>
    Licence:    LGPL

    Additions:  Mattia Barbon suggested using wxObject to
                hold the callback handle, and supplied the code.

*************************************************************/


// FIXME: needs a destructor
// FIXME: should handle arrays



class GlPoint3D {
        GLfloat* point = (GLfloat *)wMalloc( sizeof( GLfloat ) * 3 );


    public:

        Point( GLfloat x, GLfloat y, GLfloat z ) {
            point[0] = x;
            point[1] = y;
            point[2] = z;
        }

        GLfloat GetX() {
            return point[0];
        }

        GLfloat GetY() {
            return point[1];
        }

        GLfloat GetZ() {
            return point[2];
        }

        GLfloat SetX( GLfloat x ) {
            point[0] = x;
        }

        GLfloat SetY( GLfloat y ) {
            point[1] = y;
        }

        GLfloat SetZ( GLfloat z ) {
            point[2] = z;
        }

};
