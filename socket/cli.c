/*************************************************************************
    > File Name: cil.c
    > Author: DHD
    > Mail: 1423191087@qq.com
    > Created Time: 2018年12月22日 星期六 00时25分48秒
 ************************************************************************/

#include "utili.h"

int main()
{
	int sockCli = socket(AF_INET, SOCK_STREAM, 0);
	if(sockCli == -1)
	{
		perror("socket.");
		exit(1);
	}
	
	struct sockaddr_in addrSer;
	addrSer.sin_family = AF_INET;
	addrSer.sin_port = htons(SERVER_PORT);
	addrSer.sin_addr.s_addr = inet_addr(SERVER_ADDR);

	socklen_t len = sizeof(struct sockaddr);
	int ret = connect(sockCli, (struct sockaddr*)&addrSer, len);

	if(ret == -1)
	{
		printf("Client connect server fail\n");
		exit(1);
	}
	else
	{
		printf("Client connect server success\n");
	}

	char sendbuf[BUFFER_SIZE] = "";
	char recvbuf[BUFFER_SIZE] = "";

	while(1)
	{
		printf("Cli.>");
		scanf("%s", sendbuf);
		send(sockCli, sendbuf, strlen(sendbuf)+1, 0);
		recv(sockCli, recvbuf, BUFFER_SIZE, 0);
		printf("Ser.>%s\n", recvbuf);
	}

	
	return 0;
}
