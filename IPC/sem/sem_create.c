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
		err_quit("usage: %s <pathname> <nsems>", argv[0]);
	int nsems;
	nsems = atoi(argv[2]);
	Semget(Ftok(argv[1], 0xff), nsems, IPC_CREAT | IPC_EXCL | 0775);
	return 0;
}
