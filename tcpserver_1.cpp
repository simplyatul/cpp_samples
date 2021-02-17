/* 
 * usage: tcpserver <port>
 * 
 * TCP Server take from #1 link
 * It then modified to demonstrate self-pipe trick
 * After a client ($ nc 127.0.0.1 <port>) is connected, it 
 * spawns a thread and write on pipe
 * epoll then reads from the pipe. you can decide then to 
 * come out from read loop and exit
 * 
 * Credits/Refs: 
 * 1. https://www.cs.cmu.edu/afs/cs/academic/class/15213-f99/www/class26/tcpserver.c
 * 2. https://programmer.ink/think/epoll-for-linux-programming.html
 * 2. https://suchprogramming.com/epoll-in-3-easy-steps/
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <pthread.h>
#define MAX_EVENTS 5
#define READ_SIZE 10
#include <sys/epoll.h> // for epoll_create1(), epoll_ctl(), struct epoll_event
#include <fcntl.h>
#include <errno.h>

#define BUFSIZE 1024

#if 0
/* 
 * Structs exported from in.h
 */

/* Internet address */
struct in_addr {
  unsigned int s_addr; 
};

/* Internet style socket address */
struct sockaddr_in  {
  unsigned short int sin_family; /* Address family */
  unsigned short int sin_port;   /* Port number */
  struct in_addr sin_addr;	 /* IP address */
  unsigned char sin_zero[...];   /* Pad to size of 'struct sockaddr' */
};

/*
 * Struct exported from netdb.h
 */

/* Domain name service (DNS) host entry */
struct hostent {
  char    *h_name;        /* official name of host */
  char    **h_aliases;    /* alias list */
  int     h_addrtype;     /* host address type */
  int     h_length;       /* length of address */
  char    **h_addr_list;  /* list of addresses */
}
#endif

/*
 * error - wrapper for perror
 */
void error(char *msg) {
  perror(msg);
  exit(1);
}

void * thread_1(void *fd) {
    int *pfd = (int *) fd;
    printf("pfd: %d\n", *pfd);
    sleep(5);
    printf("Writing to pipe...\n");
    write(*pfd, "STOP", 4);
    //close(*sfd);
}

void setnonblocking(int sock)
{
    int opts;
    opts=fcntl(sock,F_GETFL);
    if(opts<0)
    {
        perror("fcntl(sock,GETFL)");
        exit(1);
    }
    opts = opts|O_NONBLOCK;
    if(fcntl(sock,F_SETFL,opts)<0)
    {
        perror("fcntl(sock,SETFL,opts)");
        exit(1);
    }
}

int main(int argc, char **argv) {
  int parentfd; /* parent socket */
  int childfd; /* child socket */
  int portno; /* port to listen on */
  int clientlen; /* byte size of client's address */
  struct sockaddr_in serveraddr; /* server's addr */
  struct sockaddr_in clientaddr; /* client addr */
  struct hostent *hostp; /* client host info */
  char buf[BUFSIZE]; /* message buffer */
  char *hostaddrp; /* dotted decimal host addr string */
  int optval; /* flag value for setsockopt */
  int n; /* message byte size */

  /* 
   * check command line arguments 
   */
  if (argc != 2) {
    fprintf(stderr, "usage: %s <port>\n", argv[0]);
    exit(1);
  }
  portno = atoi(argv[1]);

  /* 
   * socket: create the parent socket 
   */
  parentfd = socket(AF_INET, SOCK_STREAM, 0);
  if (parentfd < 0) 
    error("ERROR opening socket");

  /* setsockopt: Handy debugging trick that lets 
   * us rerun the server immediately after we kill it; 
   * otherwise we have to wait about 20 secs. 
   * Eliminates "ERROR on binding: Address already in use" error. 
   */
  optval = 1;
  setsockopt(parentfd, SOL_SOCKET, SO_REUSEADDR, 
	     (const void *)&optval , sizeof(int));

  /*
   * build the server's Internet address
   */
  bzero((char *) &serveraddr, sizeof(serveraddr));

  /* this is an Internet address */
  serveraddr.sin_family = AF_INET;

  /* let the system figure out our IP address */
  serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

  /* this is the port we will listen on */
  serveraddr.sin_port = htons((unsigned short)portno);

  /* 
   * bind: associate the parent socket with a port 
   */
  if (bind(parentfd, (struct sockaddr *) &serveraddr, 
	   sizeof(serveraddr)) < 0) 
    error("ERROR on binding");

  /* 
   * listen: make this socket ready to accept connection requests 
   */
  if (listen(parentfd, 5) < 0) /* allow 5 requests to queue up */ 
    error("ERROR on listen");

  /* 
   * main loop: wait for a connection request, echo input line, 
   * then close connection.
   */
  clientlen = sizeof(clientaddr);
  bool once = true;
  while (once) {
    once = false;

    /* 
     * accept: wait for a connection request 
     */
    childfd = accept(parentfd, (struct sockaddr *) &clientaddr, (socklen_t*)&clientlen);
    if (childfd < 0) 
      error("ERROR on accept");
    
    /* 
     * gethostbyaddr: determine who sent the message 
     */
    hostp = gethostbyaddr((const char *)&clientaddr.sin_addr.s_addr, 
			  sizeof(clientaddr.sin_addr.s_addr), AF_INET);
    if (hostp == NULL)
      error("ERROR on gethostbyaddr");
    hostaddrp = inet_ntoa(clientaddr.sin_addr);
    if (hostaddrp == NULL)
      error("ERROR on inet_ntoa\n");
    printf("server established connection with %s (%s)\n", 
	   hostp->h_name, hostaddrp);
    
    printf("childfd: %d\n", childfd);
    setnonblocking(childfd);


    int running = 1, event_count, i;
    int bytes_read;
    char read_buffer[READ_SIZE + 1];
    struct epoll_event event, events[MAX_EVENTS];
    int epoll_fd = epoll_create1(0);

    if(epoll_fd == -1)
    {
        fprintf(stderr, "Failed to create epoll file descriptor\n");
        return 1;
    }

    event.events = EPOLLIN;
    event.data.fd = childfd;

    if(epoll_ctl(epoll_fd, EPOLL_CTL_ADD, event.data.fd, &event))
    {
        fprintf(stderr, "Failed to add file descriptor to epoll\n");
        close(epoll_fd);
        return 1;
    }

    /*
     * create pipe 
    */
    int pfd[2];
    //int ret_val = pipe(pfd);                 /* Create pipe */
    int ret_val = pipe2(pfd, O_NONBLOCK);                 /* Create pipe */
    if (ret_val != 0) {             /* Test for success */
        printf("Unable to create a pipe; errno=%d\n",errno);
        exit(1);                         /* Print error message and exit */
    }
    printf("pipe fds: %d, %d", pfd[0], pfd[1]);
    struct epoll_event pevent;
    pevent.events = EPOLLIN;
    pevent.data.fd = pfd[0]; // pass readfd

    if(epoll_ctl(epoll_fd, EPOLL_CTL_ADD, pevent.data.fd, &pevent))
    {
        fprintf(stderr, "Failed to add file descriptor to epoll\n");
        close(epoll_fd);
        return 1;
    }

    // create thread and pass write fd
    pthread_t tid;
    pthread_create(&tid, NULL, thread_1, (void*)(&pfd[1]));

    while(running)
    {
        printf("\nPolling for input...\n");
        event_count = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
        printf("%d ready events\n", event_count);
        for(i = 0; i < event_count; i++)
        {
            printf("Reading file descriptor '%d' -- ", events[i].data.fd);
            bytes_read = read(events[i].data.fd, read_buffer, READ_SIZE);
            printf("%d bytes read.\n", bytes_read);
            if(0 == bytes_read) {
                printf("Socket closed\n");
                running = 0;
            } else if(bytes_read < 0) {
                printf("Socket errno: %d\n", errno);
            } else {
                read_buffer[bytes_read] = '\0';
                printf("Read '%s'\n", read_buffer);
            }

            if(!strncmp(read_buffer, "stop\n", 5))
                running = 0;

        }
    }


#if 0

    /* 
     * read: read input string from the client
     */
    bzero(buf, BUFSIZE);
    n = read(childfd, buf, BUFSIZE);
    if (n < 0) 
        error("ERROR reading from socket errno: %d", errno);
    printf("server received %d bytes: %s", n, buf);


    /* 
     * write: echo the input string back to the client 
     */
    n = write(childfd, buf, strlen(buf));
    if (n < 0) 
        error("ERROR writing to socket");

    close(childfd);
#endif
  }
}

