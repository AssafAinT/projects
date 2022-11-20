#include "tcp_ping_pong.h"
int main(void)
{
    int sockfd = 0;
    int connect_fd = 0;
    size_t num_of_send = 4;
    struct sockaddr_in servaddr;
    struct sockaddr_in client;

    CreateSocket(&sockfd);
    if (sockfd  == -1)
    {
        return -1;
    }

    memset(&servaddr, 0, sizeof(struct sockaddr_in)); 
    SetUpServerSocket(&servaddr);

    if (0 != connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)))
    {
        perror("connect");
        return -1;
    }
    
    for (size_t i = 0; i < num_of_send ; ++i)
    {
        Send(sockfd, "ping");
        Recv(sockfd);
    }
    

    close(sockfd);
    return 0;


}