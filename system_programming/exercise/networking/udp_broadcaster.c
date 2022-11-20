#include "udp_broadcast.h"

int main(int argc, char **argv)
{

    int sockfd;
    struct sockaddr_in their_addr; // connector's address information
    struct hostent *he;
    int numbytes;
    int broadcast = 1;
    //char broadcast = '1'; // if that doesn't work, try this

    if (argc != 3)
    {
        fprintf(stderr,"usage: broadcaster hostname message\n");
        exit(1);
    }

    if ((he=gethostbyname(argv[1])) == NULL) 
    {  // get the host info
        perror("gethostbyname");
        exit(1);
    }
    
    if (he)
    {
        puts(he->h_name);
    }

    CreateSocket(&sockfd);
    if (sockfd  == -1)
    {
        return sockfd;
    }

    // this call is what allows broadcast packets to be sent:
    if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, (char *)&broadcast,sizeof(broadcast)) == -1)
    {
        perror("setsockopt (SO_BROADCAST)");
        return (-1);
    }
    
    int addr_len = sizeof(struct sockaddr_in);

    memset((void*)&their_addr, 0, addr_len);

    their_addr.sin_family = AF_INET;     // host byte order
    their_addr.sin_port = htons(SERVERPORT); // short, network byte order
    their_addr.sin_addr.s_addr = inet_addr(argv[1]);
    

    if (-1 == (numbytes=sendto(sockfd, argv[2], strlen(argv[2]), 0, (struct sockaddr *)&their_addr,
        addr_len)))
    {
        perror("sendto");
        exit(1);
    }

    printf("sent %d bytes to %s\n", numbytes,
        inet_ntoa(their_addr.sin_addr));

    close(sockfd);
}