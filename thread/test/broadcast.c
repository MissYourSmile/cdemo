/*************************************************************************
    > File Name: broadcast.c
    > Author: DHD
    > Mail: 1423191087@qq.com
    > Created Time: 2018年11月25日 星期日 19时05分07秒
 ************************************************************************/

#include<stdio.h>
#include<pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  cond  = PTHREAD_COND_INITIALIZER;

void *fun1(void* arg);
void *fun2(void* arg);
int main()
{
	pthread_t tid1;
	pthread_t tidArr[5];
	int i = 0;
	for( ; i < 5; ++i)
	{
		pthread_create(&tidArr[i], NULL, fun1, NULL);
	}
	sleep(3);
	pthread_create(&tid1, NULL, fun2, NULL);


	for( ; i < 5; ++i)
	{
		pthread_join(tidArr[i], NULL);
	}
	pthread_join(tid1, NULL);
	return 0;
}


void *fun1(void* arg)
{
	pthread_mutex_lock(&mutex);
	printf("this is fun1.\n");
	pthread_cond_wait(&cond, &mutex);
	printf("this is fun1 end .\n");
	pthread_mutex_unlock(&mutex);
}

void *fun2(void* arg)
{
	pthread_mutex_lock(&mutex);
	printf("this is fun2.\n");
	pthread_cond_broadcast(&cond);
	pthread_mutex_unlock(&mutex);
}
