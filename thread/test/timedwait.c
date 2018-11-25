/*************************************************************************
    > File Name: timedwait.c
    > Author: DHD
    > Mail: 1423191087@qq.com
    > Created Time: 2018年11月25日 星期日 00时02分51秒
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <error.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
void *thread_fun1(void *);
void *thread_fun2(void *);

int main()
{
	pthread_t tid1, tid2;
	pthread_create(&tid1, NULL, thread_fun1, NULL);
	sleep(1);
	pthread_create(&tid2, NULL, thread_fun2, NULL);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	return 0;
}

void *thread_fun1(void * arg)
{
	pthread_mutex_lock(&mutex);
	struct timespec ts;
	clock_gettime(CLOCK_REALTIME, &ts);
	ts.tv_sec += 5;
	printf("this is pthread fun1\n");
	int rc = pthread_cond_timedwait(&cond, &mutex, &ts);
	//int rc = pthread_cond_wait(&cond, &mutex);
	
	if(rc == 0)
		printf("thread fun2 finish\n");
	else
		printf("thread fun2 finish. out of time\n");
	pthread_mutex_unlock(&mutex);
}

void *thread_fun2(void * arg)
{
	pthread_mutex_lock(&mutex);
	printf("this is pthread fun2\n");
//	pthread_cond_signal(&cond);


	pthread_mutex_unlock(&mutex);
}
