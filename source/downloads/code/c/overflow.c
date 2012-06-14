#include	<stdlib.h>
#include	<stdio.h>
int main ( int argc, char *argv[] )
{
    float a, c;
    int b;
    b = 200 * 300 * 400 * 500;
    a = (3.14 + 1e20) - 1e20;
    printf ( "the b is %d\n", b );
    printf ( "the a is %f\n", a );
    c = 3.14 + (1e20 - 1e20);
    printf ( "the c is %f\n", c );
    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
