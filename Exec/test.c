#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	printf("main rum\n");
	pid_t pid = fork();
	if(-1 == pid)
	{
		perror("fork.");
		exit(1);
	}
	else if(0 == pid)
	{
		printf("This is child , pid = %d\n", getpid());
		char *arr[] = {"child", "Hello", NULL};
		execv("child", arr);	
	}
	else
	{
		waitpid(pid);
		printf("This is parent , pid = %d\n", getpid());
	}
	return 0;
}
