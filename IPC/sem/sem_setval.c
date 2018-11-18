/*************************************************************************
    > File Name: sem_setval.c
    > Author: DHD
    > Mail: 1423191087@qq.com
    > Created Time: 2018年11月18日 星期日 15时04分12秒
 ************************************************************************/

#include "../unpipc.h"

int main(int argc, char *argv[])
{
	int semid, semnum;
	int val;
	union semun arg;
	if(argc != 4)
		err_quit("usage: %s <pathname> <semnum> <value>", argv[0]);
	semid = Semget(Ftok(argv[1], 0xff), 0, 0);
	semnum = atoi(argv[2]);
	val = atoi(argv[3]);
	arg.val = val;
	Semctl(semid, semnum, SETVAL, arg);
	return 0;
}
