#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int i = 0;
	printf("child pid = %d\n", getpid());
	for(i = 0; i < argc; i++)
	{
		puts(argv[i]);
		sleep(1);
	}
	return 0;
}
