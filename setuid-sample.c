/*
 * This program is taken from the Book
 * The Design of the Unix Operating System 
 * By Maurice Bach
 */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>


int main() {
    int uid, euid, fdmjb, fdmaury;

    uid = getuid();  /* get real UID */
    euid = geteuid(); /* get effective UID */

    printf("uid %d euid %d\n", uid, euid);

    fdmjb = open("mjb", O_RDONLY);
    fdmaury = open("maury", O_RDONLY);
    printf("fdmjb %d fdmaury %d\n", fdmjb, fdmaury);

    setuid(uid);

    printf("after setuid (%d): uid %d euid %d\n", uid, getuid(), geteuid());

    fdmjb = open("mjb", O_RDONLY);
    fdmaury = open("maury", O_RDONLY);
    printf("fdmjb %d fdmaury %d\n", fdmjb, fdmaury);

    setuid(euid);
    printf("after setuid (%d): uid %d euid %d\n", euid, getuid(), geteuid());
}
