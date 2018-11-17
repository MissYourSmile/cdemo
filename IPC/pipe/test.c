/*************************************************************************
    > File Name: test.c
    > Author: DHD
    > Mail: 1423191087@qq.com
    > Created Time: 2018年11月05日 星期一 20时02分50秒
 ************************************************************************/

#include"../unpipc.h"
#include <time.h>

void Child(int pipe_read[2], int pipe_write[2]);
void Parent(int pipe_read[2], int pipe_write[2]);

int main()
{
	int pipefd1[2];
	int pipefd2[2];
	Pipe(pipefd1);
	Pipe(pipefd2);
	pid_t pid = fork();
	
	if(pid == 0)
		Child(pipefd1, pipefd2);
	else if(pid > 0)
		Parent(pipefd2, pipefd1);
	else
		perror("fork");	
	return 0;
}

void Child(int pipe_read[2], int pipe_write[2])
{
	char *child_talk[] = {"Hi", "I,m fine, thanks.", "It is", NULL};
	close(pipe_read[1]);
	close(pipe_write[0]);

	int i = 0;
	char *talk = child_talk[i];
	char talk_buf[256];
	char buffer[256];
	while(talk != NULL)
	{
		read(pipe_read[0], buffer, 256);
		printf("Parent.> %s\n", buffer);
		write(pipe_write[1], talk, strlen(talk)+1);
		talk = child_talk[++i];
	}
	
	close(pipe_read[0]);
	close(pipe_write[1]);
}

void Parent(int pipe_read[2], int pipe_write[2])
{
	char *parent_talk[] = {"Hello", "How are you", "What's time.", NULL};
	close(pipe_read[1]);
	close(pipe_write[0]);

	int i = 0;
	char *talk = parent_talk[i];
	char buffer[256];
	while(talk != NULL)
	{
		write(pipe_write[1], talk, strlen(talk)+1);
		read(pipe_read[0], buffer, 256);
		printf("Child.> %s ", buffer);
		if(2 == i)
		{
			time_t result = time(NULL);
			printf(asctime(localtime(&result)));
		}
		printf("\n");
		talk = parent_talk[++i];
	}

	close(pipe_read[0]);
	close(pipe_write[1]);

	int status;
	wait(&status);
}
