#include "tcp_ping_pong.h"

int main(void)
{
    int sockfd = 0;
    int connfd = 0;
    socklen_t len = 0;
    struct sockaddr_in servaddr;
    struct sockaddr_storage cli;
    size_t num_of_recives = 4;
    char buff[1024] = {'\0'};
    char s[INET6_ADDRSTRLEN] = {'\0'};

    // socket create and verification
    CreateSocket(&sockfd);
    if (sockfd == -1) 
    {
        return sockfd;
    }
        

    memset(&servaddr, 0, sizeof(servaddr));
    // assign IP, PORT
    SetUpClientSocket(&servaddr);
   
    // Binding newly created socket to given IP and verification
    if ((bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) == -1)
    {
        printf("socket bind failed...\n");
        return -1;
    }
    else
    {
        printf("Socket successfully binded..\n");
    }
   
    // Now server is ready to listen and verification
    if ((listen(sockfd, 1)) == -1) 
    {
        printf("Listen failed...\n");
        return -1;
    }
    else
    {
        printf("Server listening..\n");
    }

    len = (socklen_t)sizeof(cli);
   
    // Accept the data packet from client and verification
    connfd = accept(sockfd, (struct sockaddr *)&cli, &len);
    if (connfd == -1)
    {
        printf("server accept failed...\n");
        return -1;
    }
    else
    {
        printf("server accept the client...\n");
    }
   
    // Function for chatting between client and server
    
    int numbytes = 0;
    while (0 != num_of_recives)
    {
        Recv(connfd);

        printf("listener: got packet from %s\n",
                inet_ntop(cli.ss_family,
                get_in_addr((struct sockaddr *)&cli),
                s, sizeof(s)));
        
        sleep(2);
        Send(connfd, "pong");
        --num_of_recives;
    }
   
    // After chatting close the socket
    close(sockfd);
    close(connfd);  

    return 0; 
}