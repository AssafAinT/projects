/****************************************************
* TCP_UDP_SERVER                                    *
* Assaf Ainhoren                                    *
* date: 03.11.2022                                  *
****************************************************/
/********************************libraries includes****************************/
#ifndef __ILRD_RD127_128_TCP_UDP_SERVER_HPP
#define __ILRD_RD127_128_TCP_UDP_SERVER_HPP
#include <sys/select.h> //select
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#define PORT "7070"  // the port users will be connecting to

#define BACKLOG 10   // how many pending connections queue will hold

void sigchld_handler(int s);

void *get_in_addr(struct sockaddr *sa);

void CreateSocket(int *sockfd, int type_of_socket);

void SetUpServerSocket(struct addrinfo *hints, struct addrinfo **ai);

void SetUpClientSocket(struct sockaddr_in *sa);

void ArrangeSocketForListen(struct addrinfo **runner, struct addrinfo **ai,
                            int *listener_fd, int *opt);

void Send(int *listener_fd, int *current_fd, fd_set *master, int *fdmax, const char *string);

void Recv(int sockfd);

void InsertNewFdToSet(int *newfd, int *fd_max, fd_set *master, struct sockaddr_storage *remoteaddr, char *remoteIP);

int ReciveMessageFrom(int sockfd, char *buffer, size_t buf_len, 
                          struct sockaddr *sender);

int SendBackTo(int sockfd, const char *msg, size_t msg_len, 
                    struct sockaddr *sender);

void TcpManageMessage(fd_set *master, int sockfd);


int ControlFd(int i, fd_set *master, int *server_fd, int *maxfd);
#endif //__ILRD_RD127_128_TCP_UDP_SERVER_HPP