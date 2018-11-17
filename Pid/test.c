/*************************************************************************
    > File Name: test.c
    > Author: DHD
    > Mail: 1423191087@qq.com
    > Created Time: 2018年11月05日 星期一 18时36分07秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>

int main()
{
	pid_t pid;
	pid = fork();
	if(0 == pid)
	{
		printf("This is a child process pid = %d, ppid = %d\n", getpid(), getppid());
	}
	else if(0 < pid)
	{
		printf("This is a parent process pid = %d\n", getpid());
		int status;
		wait(&status);
	}
	else
	{
		printf("error\n");
	}
	return 0;
}
