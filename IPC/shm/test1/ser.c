/*************************************************************************
    > File Name: ser.c
    > Author: DHD
    > Mail: 1423191087@qq.com
    > Created Time: 2018年11月18日 星期日 22时55分20秒
 ************************************************************************/

#include "../unpipc.h"

int main()
{
	int shmid = Shmget(Ftok("myshm", 0xff), 1024*1024, IPC_CREAT | 0755);
	int semid = Semget(Ftok("mysem", 0xff), 2, IPC_CREAT | 0755);
	char *buf = (char *)Shmat(shmid, NULL, 0);
	union semun arg;
	struct sembuf p = {0, -1, 0},
				  v = {1, 1, 0};
	arg.val = 0;
	Semctl(semid, 0, SETVAL, arg);
	Semctl(semid, 1, SETVAL, arg);
	
	while(1)
	{
		printf("Ser.>");
		scanf("%s", buf);
		Semop(semid, &v, 1);
		Semop(semid, &p, 1);
		printf("Cli.>%s\n", buf);
	}
	shmdt(buf);
	Shmctl(shmid, IPC_RMID, NULL);
	Semctl(semid, 0, IPC_RMID);
	return 0;
}
