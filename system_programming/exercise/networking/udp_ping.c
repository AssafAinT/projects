#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "udp_ping_pong.h"

#define SERVERPORT "4950"    // the port users will be connecting to

int main(void)
{
    int sockfd; 
    int numbytes;
    int len;
    char buffer[MAXBUFLEN]; 
    char *Ping = "Ping"; 
    struct sockaddr_in servaddr; 
    size_t num_of_recives = 4;
    // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 )
    { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
    
    memset(&servaddr, 0, sizeof(servaddr)); 
        
    // Filling server information 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(4950); 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
    
    
    while(0 != num_of_recives)
    {

        sendto(sockfd, (const char *)Ping, strlen(Ping), 
            MSG_CONFIRM, (const struct sockaddr *) &servaddr,  
                sizeof(servaddr)); 
        printf("Ping Sent.\n"); 
                
        numbytes = recvfrom(sockfd, (char *)buffer, MAXBUFLEN,  
                    MSG_WAITALL, (struct sockaddr *) &servaddr, 
                    &len); 
        buffer[numbytes] = '\0'; 
        printf("Server : %s\n", buffer); 

        --num_of_recives;
    }
    
    close(sockfd); 
    return 0; 
}