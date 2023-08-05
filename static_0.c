/*
 * run: gcc static_0.c
 */

#include <stdio.h>

static int sVar1; // def initialized to zero
static int sVar2 = 10;

int main() {
    printf("%d\n", sVar1);
    static int sVar2 = 20;
    printf("%d\n", sVar2);
    {
        static int sVar2 = 30;
        printf("%d\n", sVar2);
    }
    return 0;
}

/*
Output
0
20
30

*/
