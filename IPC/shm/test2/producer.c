/*************************************************************************
    > File Name: producer.c
    > Author: DHD
    > Mail: 1423191087@qq.com
    > Created Time: 2018年11月18日 星期日 22时55分20秒
 ************************************************************************/

#include "../unpipc.h"

int main()
{
	int shmid = Shmget(Ftok("myshm", 0xff), sizeof(int), IPC_CREAT | IPC_EXCL | 0755);
	int semid = Semget(Ftok("mysem", 0xff), 2, IPC_CREAT | IPC_EXCL | 0755);
	int *buf = (int *)Shmat(shmid, NULL, 0);
	union semun arg;
	struct sembuf op[2];
	int i;
	arg.val = 1;
	op[0].sem_num = 0;
	op[0].sem_op = -1;
	op[0].sem_flg = 0;
	op[1].sem_num = 1;
	op[1].sem_op = 1;
	op[1].sem_flg = 0;

	Semctl(semid, 0, SETVAL, arg);
	arg.val = 0;
	Semctl(semid, 1, SETVAL, arg);
	for(i = 0; i < 10; i++)
	{
		Semop(semid, &op[0], 1);
		*buf = i;
		printf("%d\t", *buf);
		Semop(semid, &op[1], 1);
	}
	Shmctl(shmid, IPC_RMID, NULL);
	Semctl(semid, 0, IPC_RMID);
	return 0;
}
