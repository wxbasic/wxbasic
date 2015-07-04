/* standard libraries */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <float.h>
#include <time.h>
#include <errno.h>
#include <limits.h>
#include <signal.h>
#include <setjmp.h>


static void sigill( int s ) {
    printf("sigill caught\n");
}

static void sigsegv( int s ) {
    printf("sigsegv caught\n");
}

static void sigfpe( int s ) {
    printf("sigfpe caught\n");
}

int main(int argc, char **argv)
{
    int a,  b;
    char *buffer;

    /* set a signal */
    signal( SIGILL, sigill );
    signal( SIGFPE, sigfpe );
    signal( SIGSEGV, sigsegv );

    // generate an error
    printf("this should generate an error: %s \n", buffer[10000]);
    printf("this should generate another error: %s \n", buffer[10000]);

}
