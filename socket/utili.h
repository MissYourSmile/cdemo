/*************************************************************************
    > File Name: utili.h
    > Author: DHD
    > Mail: 1423191087@qq.com
    > Created Time: 2018年12月21日 星期五 22时42分26秒
 ************************************************************************/

#ifndef _UTILI_H
#define _UTILI_H
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SOCKET_QUEUE_SIZE 5
#define TCP 0x00
#define UDP 0x01
#define SERVER 0x02
#define CLIENT 0x03
int start_up(const char *ip, const short port, int mode = TCP, int funct = SERVER)
{
	int sockfd;
	if(mode == TCP)
	{
		sockfd = socket(AF_INET, SOCK_STREAM, 0);
	}	
	else if(mode == UDP)
	{
		sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	}
	else
	{
		printf("mode error\n");
		exit(1);
	}
	if(-1 == sockfd)
	{
		perror("socket.");
		exit(1);
	}
	
	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	address.sin_addr.s_addr = inet_addr(ip);
	
	int yes;
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

	socklen_t len = sizeof(struct sockaddr);

	if(funct == SERVER)
	{
		int ret = bind(sockfd, (struct sockaddr*)&address, len);
		if(ret == -1)
		{
			perror("bind.");
			exit(1);
		}
		if(mode == TCP)
		{
			ret = listen(sockfd, SOCKET_QUEUE_SIZE);
			if(ret == -1)
			{
				perror("listen.");
				exit(1);
			}
		}
	}
	else if(funct == CLIENT)
	{
		if(mode == TCP)
		{
			int ret = connect(sockfd, (struct sockaddr*)&address, len);
			if(ret == -1)
			{
				perror("connect");
				exit(1);
			}
		}
	}
	else
	{
		printf("funct error\n");
	}
	return sockfd;
}
#endif
