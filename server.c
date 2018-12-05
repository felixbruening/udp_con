/*
 * server.c
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
	int error;
	int sockfd;
	char buf[MAX_BUF];
	struct sockaddr_in sock;
	struct sockaddr_storage storage;
	socklen_t addr_size;

	printf("[----- Server starten -----]\n");

	memset(&sock, 0, sizeof(struct sockaddr_in));
	memset(&storage, 0, sizeof(struct sockaddr_in));

	if( (sockfd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0 )
	{
		printf("Error socket\n");
		return 0;
	}
	sock.sin_family = AF_INET;
	sock.sin_port = htons(PORT);
	//sock.sin_addr.s_addr = inet_addr("127.0.0.1");
	sock.sin_addr.s_addr = htonl(INADDR_ANY);
	if( bind(sockfd, (struct sockaddr*)&sock, sizeof(sock)) < 0 )
	{
		printf("Error while binding\n");
		return 0;
	}

	printf("[----- Server gestartet ---]\n");

	addr_size = sizeof(storage);
	printf("[Waiting for data...]\n");

	while(1)
	{
		recvfrom(sockfd, buf, MAX_BUF,0, (struct sockaddr*)&storage, &addr_size );

		printf("[Received: %s]\n", buf);
	}
	return 0;
}
