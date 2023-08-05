/*
 * run: gcc stdout_0.c
 */

#include <stdio.h>


int main() {
    FILE *fp = stdout;
    int n;
    fprintf(fp, "%d ", 45);
    fflush(stdout);
    fprintf(stderr, "%d ", 65);

    printf( "hello " );
    fprintf( stderr, "HELP!" );
    printf( " world\n" );

    return 0;
}

/*
Output
45 65 HELP!hello  world

Bec stdout is buffered generally and stderr not
*/
