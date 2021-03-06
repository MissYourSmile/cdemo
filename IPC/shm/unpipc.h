/*************************************************************************
    > File Name: unpipc.h
    > Author: DHD
    > Mail: 1423191087@qq.com
    > Created Time: 2018年11月13日 星期二 17时29分31秒
 ************************************************************************/

#ifndef _UNPIPC_H
#define _UNPIPC_H

#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <sys/sem.h>
#include <sys/shm.h>
#define BUFFER_SIZE 256

//union semun
union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
	struct seminfo *__buf;
};

//Pipe
int Mkfifo(const char* pathname);
int Pipe(int pipefd[2]);
int OpenW(const char* pathname);
int OpenR(const char* pathname);

//IPC sem
key_t Ftok(const char *pathname, int proi_id);
int Semget(key_t key, int nsems, int semflg);
int Semctl(int semid, int semnum, int cmd, ...);
int Semop(int semid, struct sembuf *sops, unsigned nsops);

//IPC shm
int Shmget(key_t key, size_t size, int shmflg);
int Shmctl(int shmid, int cmd, struct shmid_ds *buf);
void *Shmat(int shmid, const void *shmaddr, int shmflg);


//print
void err_quit(const char * str, ...);

//calloc
void *Calloc(size_t nmemb, size_t size);
#endif
