/*************************************************************************
    > File Name: sem_ops.c
    > Author: DHD
    > Mail: 1423191087@qq.com
    > Created Time: 2018年11月18日 星期日 18时36分46秒
 ************************************************************************/

#include "../unpipc.h"

int main(int argc, char *argv[])
{
	int semid, i;
	unsigned nops;
	struct sembuf *sops;
	if(argc < 2)	
		err_quit("usage: %s <pathname> [ semops ... ]", argv[0]);
	
	semid = Semget(Ftok(argv[1], 0xff), 0, 0);
	nops = argc - 2;
	sops = (struct sembuf*)Calloc(nops, sizeof(struct sembuf));
	for(i = 0; i < nops; i++)
	{
		sops[i].sem_num = i;
		sops[i].sem_op = atoi(argv[i+2]);
		sops[i].sem_flg = 0;
	}
	Semop(semid, sops, nops);	
	return 0;
}
