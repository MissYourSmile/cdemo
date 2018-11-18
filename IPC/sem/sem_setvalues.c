/*************************************************************************
    > File Name: sem_setvalues.c
    > Author: DHD
    > Mail: 1423191087@qq.com
    > Created Time: 2018年11月18日 星期日 10时34分21秒
 ************************************************************************/

#include "../unpipc.h"

int main(int argc, char *argv[])
{
	int semid, nsems, i;
	unsigned short *ptr;
	struct semid_ds seminfo;
	union semun arg;
	if(argc < 2)
		err_quit("usage: %s <pathname> [ values ... ]", argv[0]);
	//get the number of semphores in the set
	semid = Semget(Ftok(argv[1], 0xff), 0, 0);
	arg.buf = &seminfo;
	Semctl(semid, 0, IPC_STAT, arg);
	nsems = arg.buf->sem_nsems;
	//get values from Cmd
	if(argc != nsems + 2)
		err_quit("missing parameter, %d semphores in the set", nsems);
	ptr = (unsigned short *)Calloc(nsems, sizeof(unsigned short));
	arg.array = ptr;
	for(i = 0; i < nsems; i++)
		ptr[i] = atoi(argv[i+2]);
	//set values
	Semctl(semid, 0, SETALL, arg);
	
	return 0;
}
