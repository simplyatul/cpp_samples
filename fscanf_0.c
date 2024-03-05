/*
 * MIT License
 * Copyright (c) 2024 Atul Thosar (atulthosar@gmail.com)
 */

#include <stdio.h>

/*
 * cat version.txt
 * VERSION=002.024.000
 *
 */

#define LEN 3
char vProfName[LEN] = {0};

int main() {

    FILE *fp = fopen("/tmp/" "version.txt", "r");
    if ( NULL == fp)
    {
        printf("Error: %s\n", "file not present\n");
        return -1;
    }

    char format[32]={0};
    snprintf(format, sizeof(format), "%%%ds", (int)(LEN-1));
    printf("format: %s\n", format);

    fscanf(fp, format, vProfName); // avoids buffer overflow
    printf("vProfName: %s\n", vProfName);
    fclose(fp);
}
