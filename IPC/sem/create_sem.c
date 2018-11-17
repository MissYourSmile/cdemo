/*************************************************************************
    > File Name: create_sem.c
    > Author: DHD
    > Mail: 1423191087@qq.com
    > Created Time: 2018年11月13日 星期二 21时00分40秒
 ************************************************************************/

#include "../unpipc.h"

int main(int argc, char *argv[])
{
	if(argc < 3)
	{
		printf("usage: %s <pathname> <nsems>\n", argv[0]);
		return -1;
	}
	int c, oflag, semid, nsems;
	nsems = atoi(argv[2]);
	semid = Semget(Ftok(argv[1], 0xff), nsems, IPC_CREAT | IPC_EXCL | 0775);
	return 0;
}
