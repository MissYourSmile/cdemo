/*************************************************************************
    > File Name: sem_getval.c
    > Author: DHD
    > Mail: 1423191087@qq.com
    > Created Time: 2018年11月18日 星期日 15时12分51秒
 ************************************************************************/

#include "../unpipc.h"

int main(int argc, char *argv[])
{
	int semid, semnum;
	int val;
	if(argc != 3)
		err_quit("usage: %s <pathname> <semnum>", argv[0]);
	semid = Semget(Ftok(argv[1], 0xff), 0, 0);
	semnum = atoi(argv[2]);
	val = Semctl(semid, semnum, GETVAL);
	printf("semphore (%d) : %d\n", semnum, val);
	return 0;
}
