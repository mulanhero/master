/*
 * server.c
 *
 *  Created on: Dec 4, 2012
 *      Author: caoj7
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<unistd.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdint.h>

#define oops(msg) { perror(msg); exit(EXIT_FAILURE); }
#define SIZE 256

#define SERVER_IP "172.16.166.129"
#define PORT 8899

static int setup_socket()
{
	int socket_fd = socket(PF_INET, SOCK_STREAM, 0);
	if(socket_fd == -1) oops("socket initiating error...");

	struct sockaddr_in address;
	bzero((void *)&address, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr(SERVER_IP);
	address.sin_port =  htons(PORT);

	int bind_return =  bind(socket_fd, (struct sockaddr *)&address, sizeof(address));
	if(bind_return == -1) oops("bind error...");

	int listen_return = listen(socket_fd, 1);
	if(listen_return == -1) oops("listen error...");

	return socket_fd;
}


void running()
{
	char rcv_str[SIZE];
	ssize_t length, cmd_length;
	size_t cmd_length_ntohl;
	char *send_str1 = "sorry, pending, please wait.";
	char *send_str2 = "hello, world! from server";

	int socket_fd = setup_socket();

	while(1){
		int fd = accept(socket_fd, NULL, NULL);
		if(fd == -1) oops("accept error...");


		length = read(fd, (void*)&cmd_length, sizeof(uint32_t));
		if(length == -1) oops("read error...");

		cmd_length_ntohl = ntohl(cmd_length);
		printf("length = %d\n", cmd_length_ntohl);

		//read the cmd, its length is cmd_length_ntohl, including '\0'
		length = read(fd, (void*)rcv_str, cmd_length_ntohl);
		if(length == -1) oops("read error...");
		printf("rcv_str = %s\n", rcv_str);

		printf("ok1");
//		length = write(fd, send_str1, strlen(send_str1)+1);
//		printf("ok2");
//		if(length == -1) oops("write error...");
//
//		printf("ok3");
//		length = write(fd, send_str2, strlen(send_str2)+1);
//		if(length == -1) oops("write error...");

//		fclose(fp);
	}
}

int main(int argc, char *argv[]){
	running();
	return 0;
}


