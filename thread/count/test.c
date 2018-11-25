/*************************************************************************
    > File Name: test.c
    > Author: DHD
    > Mail: 1423191087@qq.com
    > Created Time: 2018年11月23日 星期五 23时37分35秒
 ************************************************************************/

//A: 0 2 4 6 8 ...
//B: 1 3 5 7 9 ...

#include <stdio.h>
#include <pthread.h>

#define N 10

int count = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t isOpp = PTHREAD_COND_INITIALIZER;
pthread_cond_t isEven = PTHREAD_COND_INITIALIZER;


void *A(void * arg);
void *B(void * arg);

int main()
{
	pthread_t tid1, tid2;
	pthread_create(&tid1, NULL, A, NULL);
	pthread_create(&tid2, NULL, B, NULL);
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	return 0;
}

void *A(void * arg)
{
	pthread_mutex_lock(&mutex);
	while(count <= N)
	{
		if(count % 2 == 0)		
		{
			printf("A: %d\n", count);
			++count;
			pthread_cond_signal(&isEven);
		}
		else
		{
			pthread_cond_wait(&isOpp, &mutex);
		}
	}
	pthread_mutex_unlock(&mutex);
}

void *B(void * arg)
{
	pthread_mutex_lock(&mutex);
	while(count <= N)
	{
		if(count % 2 != 0)
		{
			printf("B: %d\n", count);
			++count;
			pthread_cond_signal(&isOpp);
		}
		else
		{
			pthread_cond_wait(&isEven, &mutex);
		}
	
	}
	pthread_mutex_unlock(&mutex);
}
