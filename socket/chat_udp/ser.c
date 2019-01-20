/*************************************************************************
    > File Name: ser.c
    > Author: DHD
    > Mail: 1423191087@qq.com
    > Created Time: 2019年01月20日 星期日 09时41分45秒
 ************************************************************************/

#include "../utili.h"
#define BUFFER_SIZE 256

int main()
{
	int sockSer = start_up("192.168.56.101", 8080, UDP, SERVER);

	char sendbuf[BUFFER_SIZE] = "";
	char recvbuf[BUFFER_SIZE] = "";
	struct sockaddr_in addrCli;
	addrCli.sin_family = AF_INET;
	addrCli.sin_port = htons(8080);
	addrCli.sin_addr.s_addr = inet_addr("192.168.56.101");
	socklen_t len = sizeof(struct sockaddr);
	while(1)
	{
		recvfrom(sockSer, recvbuf, BUFFER_SIZE, 0, (struct sockaddr*)&addrCli, &len);
		printf("CLi:>%s\n", recvbuf);
		printf("Ser:>");
		scanf("%s", sendbuf);
		sendto(sockSer, sendbuf, strlen(sendbuf)+1, 0, (struct sockaddr*)&addrCli, len);
	}

	
	return 0;
}
