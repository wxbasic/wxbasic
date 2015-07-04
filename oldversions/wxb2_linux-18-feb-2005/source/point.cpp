#include <stdio.h>

// test class for wrappers
class Point {
    int x, y;

    public:

        Point( int a, int b ) {
            x = a;
            y = b;
        }

        int GetX() {
            return x;
        }

        int GetY() {
            return y;
        }
};
//    Point myPoint = Point( 10, 20 );
//    printf("x=%d, y=%d\n", myPoint.GetX(), myPoint.GetY() );
//    printf("x=%d, y=%d\n", (&myPoint)->GetX(), (&myPoint)->GetY() );
