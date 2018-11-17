/*************************************************************************
    > File Name: unpipc.c
    > Author: DHD
    > Mail: 1423191087@qq.com
    > Created Time: 2018年11月13日 星期二 17时46分10秒
 ************************************************************************/
#include "unpipc.h"
int Mkfifo(const char* pathname)
{
	int ret = mkfifo(pathname, 0755);
	if(-1 == ret && errno != EEXIST)
	{
		perror("mkfifo.");
		exit(1);
	}
	return ret;
}

int OpenW(const char* pathname)
{
	int ret = open(pathname, O_WRONLY);
	if(-1 == ret)
	{
		perror("open write file.");
		exit(1);
	}
	return ret;
}


int OpenR(const char* pathname)
{
	int ret = open(pathname, O_RDONLY);
	if(-1 == ret)
	{
		perror("open read file.");
		exit(1);
	}
	return ret;
}

int Pipe(int pipefd[2])
{
	int ret = pipe(pipefd);
	if(-1 == ret)
	{
		perror("pipe.");
		exit(1);
	}
	return ret;
}

key_t Ftok(const char *pathname, int proi_id)
{
	key_t key = ftok(pathname, proi_id);
	if(key == -1)
	{
		perror("ftok3.");
		exit(1);
	}
	return key;
}


int Semget(key_t key, int nsems, int semflg)
{
	int sem_id = semget(key, nsems, semflg);
	if(-1 == sem_id)
	{
		perror("semget.");
		exit(1);
	}
	return sem_id;
}

int Semctl(int semid, int semnum, int cmd)
{
	int ret = semctl(semid, semnum, cmd);
	if(-1 == ret)
	{
		perror("semctl.");
		exit(1);
	}
	return ret;
}

int Semop(int semid, struct sembuf *sops, unsigned nsops)
{
	int ret = semop(semid, sops, nsops);
	if(-1 == ret)
	{
		perror("semop.");
		exit(1);
	}
	return ret;
}
