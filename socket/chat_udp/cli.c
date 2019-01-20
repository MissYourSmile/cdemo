/*************************************************************************
    > File Name: cli.c
    > Author: DHD
    > Mail: 1423191087@qq.com
    > Created Time: 2019年01月20日 星期日 09时24分05秒
 ************************************************************************/

#include "../utili.h"
#define BUFFER_SIZE 256

int main()
{
	int sockCli = start_up("192.168.56.101", 8080, UDP, CLIENT);
	char sendbuf[BUFFER_SIZE] = "";
	char recvbuf[BUFFER_SIZE] = "";
	struct sockaddr_in addrSer;
	addrSer.sin_family = AF_INET;
	addrSer.sin_port = htons(8080);
	addrSer.sin_addr.s_addr = inet_addr("192.168.56.101");
	socklen_t len = sizeof(struct sockaddr);
	while(1)
	{
		printf("CLi:>");
		scanf("%s", sendbuf);
		sendto(sockCli, sendbuf, strlen(sendbuf)+1, 0, (struct sockaddr*)&addrSer, len);
		recvfrom(sockCli, recvbuf, BUFFER_SIZE, 0, (struct sockaddr*)&addrSer, &len);
		printf("%s\n", recvbuf);
	}
	return 0;
}
