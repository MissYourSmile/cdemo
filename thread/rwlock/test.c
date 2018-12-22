/*************************************************************************
    > File Name: test.c
    > Author: DHD
    > Mail: 1423191087@qq.com
    > Created Time: 2018年11月25日 星期日 19时26分18秒
 ************************************************************************/

#include<stdio.h>
#include<pthread.h>
#include "test.h"

//read-write lock
//r-r not mutex
//r-w w-w mutex
//writer priority
#if 0
pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER; 

int main()
{
	pthread_t w_tid[3], r_tid[3];	
	int i = 0;
	//run two read thread
	for(i = 0; i < 2; ++i)
		pthread_create(&r_tid[i], NULL, thread_read, NULL);
	sleep(1);
	//run two write thread
	for(i = 0; i < 3; ++i)
		pthread_create(&w_tid[i], NULL, thread_write, NULL);
	//run one read thread
	pthread_create(&r_tid[2], NULL, thread_read, NULL);

	for(i = 0; i < 3; ++i)
	{
		pthread_join(r_tid[i], NULL);
		pthread_join(w_tid[i], NULL);
	}
	return 0;
}

void *thread_read(void *arg)
{
	pthread_rwlock_rdlock(&rwlock);
	printf("reading...\n");
	sleep(1);
	printf("reading finish.\n");
	pthread_rwlock_unlock(&rwlock);
}

void *thread_write(void *arg)
{
	pthread_rwlock_wrlock(&rwlock);
	printf("writing...\n");
	sleep(2);
	printf("writing finish.\n");
	pthread_rwlock_unlock(&rwlock);
}
#endif

#if 0
//read write privority test
#include "my_rwlock.h"
my_rwlock_t rwlock = MY_PTHREAD_RWLOCK_INITIALIZER; 

int main()
{
	pthread_t w_tid[3], r_tid[3];	
	int i = 0;
	//run two read thread
	for(i = 0; i < 2; ++i)
		pthread_create(&r_tid[i], NULL, thread_read, NULL);
	sleep(1);
	//run two write thread
	for(i = 0; i < 3; ++i)
		pthread_create(&w_tid[i], NULL, thread_write, NULL);
	sleep(1);
	//run one read thread
	pthread_create(&r_tid[2], NULL, thread_read, NULL);

	for(i = 0; i < 3; ++i)
	{
		pthread_join(r_tid[i], NULL);
		pthread_join(w_tid[i], NULL);
	}
	return 0;
}

void *thread_read(void *arg)
{
	my_rwlock_rdlock(&rwlock);
	printf("reading...\n");
	sleep(5);
	printf("reading finish.\n");
	my_rwlock_unlock(&rwlock);
}

void *thread_write(void *arg)
{
	my_rwlock_wrlock(&rwlock);
	printf("writing...\n");
	sleep(2);
	printf("writing finish.\n");
	my_rwlock_unlock(&rwlock);
}
#endif

#if 0
// pthread cancel test
#include "my_rwlock.h"
my_rwlock_t rwlock = MY_PTHREAD_RWLOCK_INITIALIZER; 
pthread_t w_tid, r_tid;	
int main()
{
	int i = 0;
	pthread_create(&r_tid, NULL, thread_read, NULL);
	sleep(1);
	pthread_create(&w_tid, NULL, thread_write, NULL);
	pthread_join(r_tid, NULL);
	pthread_join(w_tid, NULL);
	printf("rw_nwaitwriters = %d\n", rwlock.rw_nwaitwriters);
	return 0;
}

void *thread_read(void *arg)
{
	my_rwlock_rdlock(&rwlock);
	printf("reading...\n");
	sleep(3);
	pthread_cancel(w_tid);
	sleep(3);
	printf("reading finish.\n");
	my_rwlock_unlock(&rwlock);
	return NULL;
}

void *thread_write(void *arg)
{
	printf("per writing...\n");
	my_rwlock_wrlock(&rwlock);
	printf("writing...\n");
	my_rwlock_unlock(&rwlock);
	return NULL;
}
#endif

#if 1

//destroy error test
#include "my_rwlock.h"
my_rwlock_t rwlock;

int main()
{
	pthread_t tid1, tid2;
	my_rwlock_init(&rwlock);
	sleep(1);
	
	pthread_create(&tid1, NULL, thread_read, NULL);
	pthread_create(&tid2, NULL, thread_write, NULL);

	my_rwlock_destroy(&rwlock);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	return 0;
}
void *thread_read(void *arg)
{
	my_rwlock_rdlock(&rwlock);
	printf("reading...\n");
	my_rwlock_unlock(&rwlock);
}

void *thread_write(void *arg)
{
	my_rwlock_wrlock(&rwlock);
	printf("writing...\n");
	my_rwlock_unlock(&rwlock);
}
#endif
