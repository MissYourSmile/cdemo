/*************************************************************************
    > File Name: ser.c
    > Author: DHD
    > Mail: 1423191087@qq.com
    > Created Time: 2018年11月07日 星期三 23时46分09秒
 ************************************************************************/

#include "../unpipc.h"

int main()
{
	//读和写是针对 server 而言的
	const char* write_fifo= "write_fifo"; 
	const char* read_fifo = "read_fifo";
	int read_fd = OpenR(write_fifo);
	Mkfifo(read_fifo);
	int write_fd= OpenW(read_fifo);

	char sendbuf[BUFFER_SIZE];
	char recvbuf[BUFFER_SIZE];
	while(1)
	{
		read(read_fd, recvbuf, BUFFER_SIZE);
		printf("Ser:>%s\n", recvbuf);
		printf("Cli:>");
		scanf("%s", sendbuf);
		write(write_fd, sendbuf, strlen(sendbuf)+1);
	}
	close(write_fd);
	close(read_fd);
	return 0;
}
