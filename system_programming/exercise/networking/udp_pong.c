#include <stdio.h>/*printf ,perror*/
#include <errno.h>
#include <string.h>


#include "udp_ping_pong.h"


int main(void)
{

    int sockfd = 0;
    struct addrinfo hints, *servinfo, *p;
    int rv = 0;
    int numbytes = 0;
    struct sockaddr_storage their_addr;
    char buf[MAXBUFLEN] = {'\0'};
    socklen_t addr_len;
    char s[INET6_ADDRSTRLEN]={'\0'};
    char *Pong = "Pong"; 
    size_t num_of_recives = 4;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET; // set to AF_INET to use IPv4
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE; // use my IP

    if ((rv = getaddrinfo(NULL, "7070", &hints, &servinfo)) != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return (1);
    }

    // loop through all the results and bind to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next)
    {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1)
            {
            perror("listener: socket");
            continue;
        }

        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1)
        {
            close(sockfd);
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

    freeaddrinfo(servinfo);

    printf("listener: waiting to recvfrom...\n");

    addr_len = sizeof(their_addr);
    while (num_of_recives != 0)
    {
        if ((numbytes = recvfrom(sockfd, buf, MAXBUFLEN-1 , 0,
            (struct sockaddr *)&their_addr, &addr_len)) == -1) 
        {
            perror("recvfrom");
            exit(1);
        }

        printf("listener: got packet from %s\n",
                inet_ntop(their_addr.ss_family,
                get_in_addr((struct sockaddr *)&their_addr),
                s, sizeof(s)));
        
        printf("listener: packet is %d bytes long\n", numbytes);
        buf[numbytes] = '\0';
        
        printf("listener: packet contains \"%s\"\n", buf);
        sleep(2);
        sendto(sockfd, (const char *)Pong, strlen(Pong),  
            MSG_CONFIRM, (const struct sockaddr *) &their_addr, 
                sizeof(their_addr)); 
        --num_of_recives;
    }

    close(sockfd);

    return 0;

}