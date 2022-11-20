#include <errno.h>
#include <stdlib.h>
#include "tcp_ping_pong.h"

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

void SetUpServerSocket(struct sockaddr_in *sa)
{
        
    // Filling server information 
    sa->sin_family = AF_INET; 
    sa->sin_addr.s_addr = inet_addr("127.0.0.1");
    sa->sin_port = htons(7070); 
}

void SetUpClientSocket(struct sockaddr_in *sa)
{
        
    // Filling server information 
    sa->sin_family = AF_INET; 
    sa->sin_addr.s_addr = htonl(INADDR_ANY);
    sa->sin_port = htons(3490); 
}


void Send(int sockfd, const char *string)
{
    int numbytes = strlen(string);
    if (numbytes != send(sockfd, string, numbytes, 0))
    {
        perror("send");
        exit(2);
    }
    printf("%s Sent.\n", string); 

}

void Recv(int sockfd)
{
    char buffer[1024] = {'\0'};
    int numbytes = 0;
    if ((numbytes = recv(sockfd, (char *)buffer, 1023 , 0)) == -1) 
    {
        perror("recv");
        exit(-1);
    }
    buffer[numbytes] = '\0'; 
    printf("%s recived\n", buffer);

}

void CreateSocket(int *sockfd)
{
    *sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (*sockfd  == -1)
    {
        perror("socket");
    }
    else
    {
        printf("Socket successfully created..\n");
    }
}