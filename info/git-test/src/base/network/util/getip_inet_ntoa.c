/*
 * getip_inet_ntoa.c
 *
 *  Created on: Dec 20, 2012
 *      Author: caoj7
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

//get IP address from  "struct sockaddr_in address"

#define IP "192.168.2.200"
#define PORT 5555

int main(){

        int socket_fd ;
        struct sockaddr_in address;

        if (socket_fd = socket(PF_INET, SOCK_STREAM, 0), socket_fd < 0){
                perror("socket");
                exit -1;
        }

        bzero((void *)&address, sizeof(address));
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = inet_addr(IP);
        address.sin_port =  htons(PORT);

        if(bind(socket_fd, (struct sockaddr *)&address, sizeof(address)) < 0){
                perror("bind");
                exit -1;
        }

        printf("%s\n", inet_ntoa(address.sin_addr));
        return 0;
}

