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
	Mkfifo(write_fifo);
	int write_fd= OpenW(write_fifo);
	int read_fd;
	while(-1 == (read_fd = OpenR(read_fifo)))
		sleep(1);

	char sendbuf[BUFFER_SIZE];
	char recvbuf[BUFFER_SIZE];
	while(1)
	{
		printf("Ser:>");
		scanf("%s", sendbuf);
		write(write_fd, sendbuf, strlen(sendbuf)+1);
		read(read_fd, recvbuf, BUFFER_SIZE);
		printf("Cli:>%s\n", recvbuf);
	}
	close(write_fd);
	close(read_fd);
	return 0;
}
