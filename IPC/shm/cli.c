/*************************************************************************
    > File Name: cli.c
    > Author: DHD
    > Mail: 1423191087@qq.com
    > Created Time: 2018年11月19日 星期一 00时15分34秒
 ************************************************************************/

#include "../unpipc.h"

int main()
{
	int shmid = Shmget(Ftok("myshm", 0xff), sizeof(int), 0);
	int semid = Semget(Ftok("mysem", 0xff), 0, 0); 
	int *buf =(int *) Shmat(shmid, NULL, SHM_RDONLY); 
	struct sembuf op[2];
	op[0].sem_num = 1;
	op[0].sem_op = -1;
	op[0].sem_flg = 0;
	op[1].sem_num = 0;
	op[1].sem_op = 1;
	op[1].sem_flg = 0;
		Semop(semid, &op[0], 1);
		printf("num is %d\n", *buf);
		Semop(semid, &op[1], 1);
	return 0;
}
