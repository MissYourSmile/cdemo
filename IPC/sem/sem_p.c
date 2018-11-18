/*************************************************************************
    > File Name: sem_p.c
    > Author: DHD
    > Mail: 1423191087@qq.com
    > Created Time: 2018年11月18日 星期日 19时23分13秒
 ************************************************************************/

#include "../unpipc.h"

int main(int argc, char *argv[])
{
	int semid;
	struct sembuf op;
	if(argc != 3)
		err_quit("usage: %s <pathnema> <semnum>", argv[0]);
	semid = Semget(Ftok(argv[1], 0xff), 0, 0);
	op.sem_num = atoi(argv[2]);
	op.sem_op = -1;
	op.sem_flg = 0;
	Semop(semid, &op, 1);
	return 0;
}
