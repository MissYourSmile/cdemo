/*************************************************************************
    > File Name: my_rwlock.h
    > Author: DHD
    > Mail: 1423191087@qq.com
    > Created Time: 2018年11月25日 星期日 21时16分33秒
 ************************************************************************/

#ifndef _PTHREAD_RWLOCK_H
#define _PTHREAD_RWLOCK_H
#include <pthread.h>
typedef struct my_rwlock_t
{
	pthread_mutex_t rw_mutex;
	pthread_cond_t rw_condreaders;
	pthread_cond_t rw_condwriters;
	int rw_magic;
	int rw_nwaitreaders;
	int rw_nwaitwriters;
	int rw_refcount;
}my_rwlock_t;

#define RW_MAGIC 0x19283746

#define MY_PTHREAD_RWLOCK_INITIALIZER {PTHREAD_MUTEX_INITIALIZER, \
			PTHREAD_COND_INITIALIZER, PTHREAD_COND_INITIALIZER, \
			RW_MAGIC, 0, 0, 0}

int my_rwlock_init(my_rwlock_t *);
int my_rwlock_destroy(my_rwlock_t *);
int my_rwlock_rdlock(my_rwlock_t *rw);
int my_rwlock_wrlock(my_rwlock_t *rw);
int my_rwlock_tryrdlock(my_rwlock_t *rw);
int my_rwlock_trywrlock(my_rwlock_t *rw);
int my_rwlock_unlock(my_rwlock_t *rw);
#endif
