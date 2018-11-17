/*************************************************************************
    > File Name: unpipc.h
    > Author: DHD
    > Mail: 1423191087@qq.com
    > Created Time: 2018年11月13日 星期二 17时29分31秒
 ************************************************************************/

#ifndef _UNPIPC_H
#define _UNPIPC_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <sys/sem.h>
#define BUFFER_SIZE 256

int Mkfifo(const char* pathname);
int Pipe(int pipefd[2]);
int OpenW(const char* pathname);
int OpenR(const char* pathname);
key_t Ftok(const char *pathname, int proi_id);
int Semget(key_t key, int nsems, int semflg);
int Semctl(int semid, int semnum, int cmd);
int Semop(int semid, struct sembuf *sops, unsigned nsops);
#endif
