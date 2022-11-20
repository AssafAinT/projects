#include <errno.h>
#include <stdlib.h>
#include "tcp_udp_server.hpp"
#define buff_size 1024
void Send(int *listener_fd, int *current_fd,
          fd_set *master, int *fdmax, const char *string)
{
    int j = 0;
    for( ; j <= *fdmax; ++j) 
    {
        // send to everyone!
        if (FD_ISSET(j, master)) 
        {
            // except the listener and ourselves
            if (j != *listener_fd && j != *current_fd)
            {
                if (send(j, string, strlen(string), 0) == -1) 
                {
                    perror("send");
                }
            }
        }
    }
}
void TcpManageMessage(fd_set *master, int sockfd)
{
    char buffer[buff_size] = "";
    int numbytes = 0;
    if (0 == (numbytes = read(sockfd, buffer, buff_size)))
    {
        FD_CLR(sockfd, master);
    }
    else
    {
        buffer[numbytes] = '\0';
        printf("%s\n", buffer);
        write(sockfd, "Pong\n", 6);
    }
}

int ControlFd(int i, fd_set *master, int *server_fd, int *maxfd)
{
    struct sockaddr sock;
    int newfd = 0;
    if (STDIN_FILENO == i)
    {
        char buffer[buff_size] = "";
        int numbytes = 0;
        numbytes = read(0, buffer, buff_size);
        buffer[numbytes] = '\0';
        if (0 == strncmp("quit", buffer, 4))
        {
            exit(1);   
        }
        printf("Pong\n");
    }
    else if (i == server_fd[1]) /* UDP */
    {
        char buffer[buff_size] = "";
        int numbytes = 0;
        if (-1 ==  ReciveMessageFrom(server_fd[0], buffer, buff_size, &sock)) 
        {
            perror("recvfrom");
            exit(1);
        }
        buffer[numbytes] = '\0';
        printf("%s\n", buffer);
        if (-1 ==  SendBackTo(server_fd[1], "Pong\n",6, &sock))
        {
            perror("Could not send message back");
            exit(1);
        }
    }
    else if (i == server_fd[0]) /* TCP */
    {
        socklen_t len = 0;
        if (-1 == (newfd = accept(server_fd[0], &sock, &len)))
        {
            perror(" Fail To Accept A Tcp");
            exit(1);
        }
        FD_SET(newfd, master);
        if (newfd > *maxfd)
        {
            *maxfd = newfd;
        }
        
    }
    else
    {
        TcpManageMessage(master, i);
    }

    return (0);
}
int ReciveMessageFrom(int sockfd, char *buffer, size_t buf_len, 
                          struct sockaddr *sender)
{
    int numbytes = 0;
    socklen_t len = sizeof(struct sockaddr);
    if (-1 == (numbytes = recvfrom(sockfd, buffer , buf_len , 0, 
            sender, &len)))
    {
        perror("Failed to recive");
        exit(-1);    
    }

    return (numbytes);
}

int SendBackTo(int sockfd, const char *msg, size_t msg_len, 
                    struct sockaddr *sender)
{
    if (-1 == sendto(sockfd, msg, msg_len, MSG_CONFIRM, sender, sizeof(struct sockaddr)))
    {
        perror("Failed to Send");
        exit(1);
    }
 
    return (0); 
}

void ArrangeSocketForListen(struct addrinfo **runner, struct addrinfo **ai,
                            int *listener_fd, int *opt)
{
    for(*runner = *ai; *runner != NULL; *runner =(* runner)->ai_next) 
    {
        *listener_fd = socket((* runner)->ai_family, (* runner)->ai_socktype,
                             (* runner)->ai_protocol);
        if (*listener_fd == -1)
        { 
            continue;
        }
        
        // lose the pesky "address already in use" error message
        setsockopt(*listener_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int));

        if (bind(*listener_fd, (* runner)->ai_addr, (* runner)->ai_addrlen) == -1) 
        {
            close(*listener_fd);
            continue;
        }

        break;
    }
}
