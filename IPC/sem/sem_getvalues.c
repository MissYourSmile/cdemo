/*************************************************************************
    > File Name: sem_getvalues.c
    > Author: DHD
    > Mail: 1423191087@qq.com
    > Created Time: 2018年11月18日 星期日 14时35分32秒
 ************************************************************************/

#include "../unpipc.h"

int main(int argc, char *args[])
{
	int semid, nsems, i;
	unsigned short *ptr;
	struct semid_ds seminfo;
	union semun arg;
	if(argc != 2)
		err_quit("usage: %s <pathname>", args[0]);
	//get the number of semphore set
	semid = Semget(Ftok(args[1], 0xff), 0, 0);	
	arg.buf = &seminfo;
	Semctl(semid, 0, IPC_STAT, arg);
	nsems = arg.buf->sem_nsems;
	//get the value of every semphore in set
	ptr = (unsigned short *)Calloc(nsems, sizeof(unsigned short));
	arg.array = ptr;
	Semctl(semid, 0, GETALL, arg);
	for(i = 0; i < nsems; i++)
		printf("sem_value (%d) : %d\n", i, ptr[i]);
	return 0;
}
