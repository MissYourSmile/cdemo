/*************************************************************************
    > File Name: rm_sem.c
    > Author: DHD
    > Mail: 1423191087@qq.com
    > Created Time: 2018年11月13日 星期二 22时48分18秒
 ************************************************************************/

#include "../unpipc.h"

int main(int argc, char *argv[])
{
	if(argc < 2)
		err_quit("usage: %s <pathname>", argv[0]);
	int semid = Semget(Ftok(argv[1], 0xff), 0, 0);
	Semctl(semid, 0, IPC_RMID);
	return 0;
}
