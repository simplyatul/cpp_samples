#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define INFIFO  "/tmp/infifo"
#define OUTFIFO "/tmp/outfifo"
int main()
{
    /*Creates Fifo*/
    mkfifo(INFIFO, 0666);   
    mkfifo(OUTFIFO, 0666);   

    int infd, outfd;
    outfd = open (OUTFIFO, O_RDWR);
    char buff[100];
    //infd = open (INFIFO, O_RDONLY);
    infd = open (INFIFO, O_RDWR);
    while(1) {
        int sz = read (infd, buff, 100);

        if (sz > 0) {
            printf ("%s\n",buff);
            write(outfd, buff, sz);
        } else {
            printf("sz: %d\n", sz);
            //break;
        }
    }
    close(infd);
}

