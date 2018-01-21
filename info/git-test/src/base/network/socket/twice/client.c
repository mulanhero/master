/*
 * client.c
 *
 *  Created on: Dec 4, 2012
 *      Author: caoj7
 */


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define oops(msg) { perror(msg); exit(EXIT_FAILURE); }
#define SIZE 256

#define SERVER_IP "172.16.166.129"
#define PORT 8899

static int setup_socket()
{
	int socket_fd = socket(PF_INET, SOCK_STREAM, 0);
	if(socket_fd == -1) oops("ERROR: socket");


	struct sockaddr_in address;
	bzero(&address, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr(SERVER_IP);
	address.sin_port =  htons(PORT);

	int connect_result = connect(socket_fd, (struct sockaddr*)&address, sizeof(address));
	if(connect_result == -1) oops("connect error...");

	return socket_fd;
}

void operation(char *cmd_str)
{
	ssize_t count;
	char rt_str[SIZE];

	int socket_fd = setup_socket();

	size_t cmd_length = strlen(cmd_str) + 1; //including the ending '\0'
	uint32_t cmd_length_htonl = htonl(cmd_length);
	//1. send cmd's length+1
	count = send(socket_fd, (void*)&cmd_length_htonl, sizeof(uint32_t), 0);
	if(count == -1) oops("error: send ...");
	//2. send the cmd
	count = send(socket_fd, cmd_str, cmd_length, 0);
	if(count == -1) oops("error: send ...");
//	//3. recv
//	count = recv(socket_fd, rt_str, SIZE, 0);
//	if(count == -1) oops("error: recv ...");
//	puts(rt_str);
////	//4. if the above recv contains "pending", then recv again
//	if(strstr(rt_str, "pending")){
//		puts("haha");
//		count = recv(socket_fd, rt_str, SIZE, 0);
//		if(count == -1) oops("error: recv ...");
//		puts(rt_str);
//	}

	close(socket_fd);
}


int main(int argc, char **argv){
	char *str = "hello from client";
	operation(str);
	return 0;
}
