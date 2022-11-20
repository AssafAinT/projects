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

#define PORT "3490"  // the port users will be connecting to

#define BACKLOG 10   // how many pending connections queue will hold

void sigchld_handler(int s);

void *get_in_addr(struct sockaddr *sa);

void CreateSocket(int *sockfd);

void SetUpServerSocket(struct sockaddr_in *sa);

void SetUpClientSocket(struct sockaddr_in *sa);

void Send(int sockfd, const char *string);

void Recv(int sockfd);




