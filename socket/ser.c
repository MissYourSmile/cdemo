/*************************************************************************
    > File Name: ser.c
    > Author: DHD
    > Mail: 1423191087@qq.com
    > Created Time: 2018年12月21日 星期五 22时44分55秒
 ************************************************************************/

#include "utili.h"

int main()
{
	int sockSer = socket(AF_INET, SOCK_STREAM, 0);
	if(sockSer == -1)
	{
		perror("socket.");
		exit(1);
	}

	struct sockaddr_in addrSer, addrCli;	
	addrSer.sin_family = AF_INET;
	addrSer.sin_port = htons(SERVER_PORT);
	addrSer.sin_addr.s_addr = inet_addr(SERVER_ADDR);
	socklen_t len = sizeof(struct sockaddr);
	int ret = bind(sockSer, (struct sockaddr*)&addrSer, len);
	if(ret == -1)
	{
		perror("bind.");
		exit(1);
	}

	ret = listen(sockSer, SOCKET_QUEUE_SIZE);
	if(ret == -1)
	{
		perror("listen.");
		exit(1);
	}

	int sockConn = accept(sockSer, (struct sockaddr*)&addrCli, &len);
	if(sockConn == -1)
	{
		printf("Server accept client connect fail\n");
		exit(1);
	}
	else
	{
		printf("Server accept client connect success\n");
	}

	char recvbuf[BUFFER_SIZE] = "";
	char sendbuf[BUFFER_SIZE] = "";
	while(1)
	{
		recv(sockConn, recvbuf, BUFFER_SIZE, 0);	
		//for(i = 0; i < strlen(recvbuf); i++)	
		//	sendbuf[i] = toupper(recvbuf[i]);
		//sendbuf[i] = '\0';
		printf("Cli.>%s\n", recvbuf);
		printf("Ser.>");
		scanf("%s", sendbuf);
		send(sockConn, sendbuf, strlen(sendbuf)+1, 0);
	}
	
	return 0;
}
