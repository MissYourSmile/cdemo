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

int Semctl(int semid, int semnum, int cmd, ...)
{
	va_list ap;
	va_start(ap, cmd);
	int ret;
	switch(cmd)
	{
		case SETALL:
		case GETALL:
		case SETVAL:
		case IPC_STAT:
			ret = semctl(semid, semnum, cmd, va_arg(ap, union semun));
			break;
		default:
			ret = semctl(semid, semnum, cmd);
	}
	va_end(ap);
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

void err_quit(const char * str, ...)
{
	va_list ap;
	va_start(ap, str);
	printf(str, va_arg(ap, char *));
	printf("\n");
	va_end(ap);
	exit(1);
}

void *Calloc(size_t nmemb, size_t size)
{
	void *ptr = calloc(nmemb, size);
	if(NULL == ptr)
	{
		perror("calloc");
		exit(1);
	}
	return ptr;
}

int Shmget(key_t key, size_t size, int shmflg)
{
	int ret = shmget(key, size, shmflg);
	if(-1 == ret)
	{
		perror("shmget.");
		exit(1);
	}
	return ret;
}
int Shmctl(int shmid, int cmd, struct shmid_ds *buf)
{
	int ret = shmctl(shmid, cmd, buf);
	if(-1 == ret)
	{
		perror("shmctl.");
		exit(1);
	}
	return ret;
}

void *Shmat(int shmid, const void *shmaddr, int shmflg)
{
	void *ptr = shmat(shmid, shmaddr, shmflg);
	if((void*)-1 == ptr)
	{
		perror("shmat.");
		exit(1);
	}
	return ptr;
}
