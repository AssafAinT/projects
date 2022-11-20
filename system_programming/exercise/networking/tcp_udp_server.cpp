#include <errno.h>
#include <stdlib.h>
#include "tcp_udp_server.hpp"

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define INTERVAL 2
#define MICRO_INTER 5000

int main(void)
{
    fd_set master;    // master file descriptor list
    fd_set read_fds;  // temp file descriptor list for select()
    int fdmax;        // maximum file descriptor number
    int listener[2];     // listening socket descriptor
    int newfd;        // newly accept()ed socket descriptor
    struct sockaddr_storage remoteaddr; // client address
    socklen_t addrlen;

    char buf[256];    // buffer for client data
    int nbytes;

    char remoteIP[INET6_ADDRSTRLEN];

    int yes=1;        // for setsockopt() SO_REUSEADDR, below
    int i = 0;

    struct addrinfo hints;
    struct addrinfo *ai;
    struct addrinfo *ai2;
    struct addrinfo *p;

    FD_ZERO(&master);    // clear the master and temp sets
    FD_ZERO(&read_fds);

    // get us a socket and bind it
    SetUpServerSocket(&hints, &ai);
    
    ArrangeSocketForListen(&p, &ai, &listener[0], &yes);
    // error check for bind
    if (p == NULL) 
    {
        fprintf(stderr, "selectserver: failed to bind\n");
        return -1;
    }
    
    int rv = 0;  
    memset(&hints, 0, sizeof(addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE;

        if ((rv = getaddrinfo(NULL, "4950", &hints, &ai2)) != 0) 
    {
        fprintf(stderr, "selectserver: %s\n", gai_strerror(rv));
        exit(1);
    }

    for(p = ai2; p != NULL; p = p->ai_next)
    {
        if ((listener[1] = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1)
            {
            perror("listener: socket");
            continue;
        }

        if (bind(listener[1], p->ai_addr, p->ai_addrlen) == -1)
        {
            close(listener[1]);
            perror("listener: bind");
            continue;
        }
        break;
    }

    if (p == NULL)
    {
        fprintf(stderr, "listener: failed to bind socket\n");
        return 2;
    }



    freeaddrinfo(ai2); // all done with this
    freeaddrinfo(ai); // all done with this

    // listen
    if (listen(listener[0], 10) == -1) 
    {
        perror("listen");
        return -1;
    }

    // add the listener to the master set
    FD_SET(STDIN_FILENO, &master);
    FD_SET(listener[0], &master);
    FD_SET(listener[1], &master);

    // keep track of the biggest file descriptor
    fdmax = MAX(listener[0], listener[1]);
    // main loop
    for(;;) 
    {
        struct timeval time = {7, 0};
        read_fds = master; // copy it
        int status = 0;
        if (-1 == (status = select(fdmax+1, &read_fds, NULL, NULL, &time)))
        {
            perror("select");
            return -1;
        }
        else if (status == 0)
        {
            printf("timeout\n");
        }
        
        else
        {
            // run through the existing connections looking for data to read
            for(i = 0; i <= fdmax; ++i) 
            {
                if (FD_ISSET(i, &read_fds)) 
                { // we got one!!
                    if (-1 == ControlFd(i, &master, listener,&fdmax))
                    {
                        return (-1);
                    }

                }
            }
        }
    }
    return 0;
}

void sigchld_handler(int s)
{
    /* waitpid() might overwrite errno, so we save and restore it:*/
    int saved_errno = errno;

    while(waitpid(-1, NULL, WNOHANG) > 0);

    errno = saved_errno;
}

void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }
}


void CreateSocket(int *sockfd, int type_of_socket)
{
    *sockfd = socket(AF_INET, type_of_socket, 0);
    if (*sockfd  == -1)
    {
        perror("socket");
    }
    else
    {
        printf("Socket successfully created..\n");
    }

}

void SetUpServerSocket(struct addrinfo *hints, struct addrinfo **ai)
{  
    int rv = 0;  
    memset(hints, 0, sizeof(addrinfo));
    hints->ai_family = AF_UNSPEC;
    hints->ai_socktype = SOCK_STREAM;
    hints->ai_flags = AI_PASSIVE;

    if ((rv = getaddrinfo(NULL, PORT, hints, ai)) != 0) 
    {
        fprintf(stderr, "selectserver: %s\n", gai_strerror(rv));
        exit(1);
    }
}

void SetUpClientSocket(struct sockaddr_in *sa)
{  
    // Filling server information 
    sa->sin_family = AF_INET; 
    sa->sin_addr.s_addr = htonl(INADDR_ANY);
    sa->sin_port = htons(3490); 
}


