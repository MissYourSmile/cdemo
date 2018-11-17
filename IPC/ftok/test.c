/*************************************************************************
    > File Name: test.c
    > Author: DHD
    > Mail: 1423191087@qq.com
    > Created Time: 2018年11月10日 星期六 12时27分03秒
 ************************************************************************/

#include "../unpipc.h"

int main()
{
	key_t key = Ftok("mytest", 0xff);
	printf("key = %x\n", key);

	key = Ftok("youtest", 0xff);
	printf("key = %x\n", key);

	key = Ftok("mytest", 0xfe);
	printf("key = %x\n", key);

	return 0;
}
