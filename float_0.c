/*
 * run: gcc float_0.c
 */

#include <stdio.h>


int main() {
    float y = 4.7;
    if(y == 4.7) // 4.7 is trated as double and hence it prints B
        printf("A\n");
    else
        printf("B\n");

    y = 0.9;
    if(y == 0.9f)
        printf("A\n");
    else
        printf("B\n");

// Ref: https://stackoverflow.com/questions/9850663/comparing-same-float-values-in-c
    float f = 0.7;    // double converted to float
    double d1 = 0.7;  // double kept as double
    double d2 = f;    // float converted back to double

    printf ("double:            %.30f\n", d1);
    printf ("double from float: %.30f\n", d2);

    return 0;

}

