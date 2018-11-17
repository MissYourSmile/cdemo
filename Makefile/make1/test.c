/*************************************************************************
    > File Name: test.c
    > Author: DHD
    > Mail: 1423191087@qq.com
    > Created Time: 2018年11月17日 星期六 16时53分31秒
 ************************************************************************/

#include<stdio.h>
#include "max.h"
#include "min.h"

int main(int argc, char *argv[])
{
	if(argc < 3)
	{
		printf("usage: %s <number1> <number2>\n");
		return -1;
	}
	int a = atoi(argv[1]);
	int b = atoi(argv[2]);
	printf("max = %d\n", max(a, b));
	printf("min = %d\n", min(a, b));
	return 0;
}
