/*************************************************************************
    > File Name: cil.c
    > Author: DHD
    > Mail: 1423191087@qq.com
    > Created Time: 2018年12月22日 星期六 00时25分48秒
 ************************************************************************/

#include "../utili.h"

#define BUFFER_SIZE 256
int main()
{
	int sockCli = start_up("192.168.56.101", 8080, TCP, CLIENT);
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
