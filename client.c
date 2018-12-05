/*
 * client.c
 *
 *  Created on: 05.12.2018
 *      Author: Felix Bruening
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>


#define MAX_BUF 		20
#define PORT			8888

int main()
{
	int error, i;
	int sockfd;
	char buf[MAX_BUF];
	struct sockaddr_in sock;

	printf("[----- Client starten -----]\n");

	memset((char*)&sock, 0, sizeof(sock));
	sock.sin_family = AF_INET;
	sock.sin_port = htons(PORT);
	sock.sin_addr.s_addr = inet_addr("192.168.178.29");

	sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if( sockfd != -1 )
	{
		printf("[---- Client erfolgreich gestartet ----]\n");
	}

	for(;;)
	{
		printf("[---- Sende...]\n");
		sendto(sockfd, "Hallo Server!", strlen("Hallo Server!\n"), 0, &sock, sizeof(struct sockaddr_in));
		sleep(3);
	}

	close(sockfd);
	return 0;
}
