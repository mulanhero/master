/*
 * ipconfig.c
 *
 *  Created on: Dec 6, 2012
 *      Author: caoj7
 */

#include <string.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <stdio.h>
#include <netinet/in.h>

int get_gw_ip(char *eth, char *ipaddr)
{
	int sock_fd;
	struct  sockaddr_in my_addr;
	struct ifreq ifr;

	if ((sock_fd = socket(PF_INET, SOCK_DGRAM, 0)) == -1){
		perror("socket");
		return -1;
	 }

	/**//* Get IP Address */
	strncpy(ifr.ifr_name, eth, IF_NAMESIZE);
	ifr.ifr_name[IFNAMSIZ-1]='\0';

	if (ioctl(sock_fd, SIOCGIFADDR, &ifr) < 0){
		fprintf(stderr, "No such device %s\n", eth);
		return -1;
	}


	memcpy(&my_addr, &ifr.ifr_addr, sizeof(my_addr));
	asprintf(&ipaddr, "%s", inet_ntoa(my_addr.sin_addr));
//	strcpy(ipaddr, );
	close(sock_fd);

	return 0;
}


int main(){
	char *ipaddr;
	get_gw_ip("eth0", ipaddr);

	puts(ipaddr);
	return 0;
}
