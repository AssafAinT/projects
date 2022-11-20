#include "udp_broadcast.h"

void CreateSocket(int *sockfd)
{
    *sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (*sockfd  == -1)
    {
        perror("socket");
    }
    else
    {
        printf("Socket successfully created..\n");
    }
}