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
#include <sys/msg.h>
#define BUFFER_SIZE 256

//union semun
union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
	struct seminfo *__buf;
};

//struct msgbuf
#define MSG_BUFFER_SIZE 2
struct msgbuf 
{
   	long mtype;
	char mtext[MSG_BUFFER_SIZE];
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

//IPC msg
int Msgget(key_t key, int msgflg);
int Msgctl(int msgid, int cmd, struct msqid_ds *buf);
int Msgsnd(int msgid, const void *msgp, size_t msgsz, int msgflg);
ssize_t Msgrcv(int msgid, void *msgp, size_t msgsz, long msgtyp, int msgflg);


//print
void err_quit(const char * str, ...);

//calloc
void *Calloc(size_t nmemb, size_t size);
#endif
