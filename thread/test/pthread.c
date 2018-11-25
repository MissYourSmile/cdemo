/*************************************************************************
    > File Name: test.c
    > Author: DHD
    > Mail: 1423191087@qq.com
    > Created Time: 2018年11月23日 星期五 19时39分03秒
 ************************************************************************/

#include<stdio.h>
#include<pthread.h>

void *thread_fun(void *arg)
{
	int i = *(int *)arg;
	printf("this is child thread %d %x\n", i, pthread_self());
	char talk[256] = "";
	sprintf(talk, "thread %x finish", pthread_self());
	pthread_exit(talk);
}

int main()
{
	pthread_t tidArr[10];
	int i;
	char *buf;
	for(i = 0; i < 10; i++)
	{
		pthread_create(&tidArr[i], NULL, thread_fun, &i);
	}
	for(i = 0; i < 10; i++)
	{
		pthread_join(tidArr[i], (void**)&buf);
		printf("%s\n", buf);
	}
	return 0;
}
