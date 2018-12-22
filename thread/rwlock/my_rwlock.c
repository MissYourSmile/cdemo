/*************************************************************************
    > File Name: my_rwlock.c
    > Author: DHD
    > Mail: 1423191087@qq.com
    > Created Time: 2018年11月25日 星期日 22时24分36秒
 ************************************************************************/

#include "my_rwlock.h"
#include <errno.h>
#include <stdio.h>
//#define READERS_PRIORITY

int my_rwlock_init(my_rwlock_t *rw)
{
	int result;
	if(0 != (result = pthread_mutex_init(&rw->rw_mutex, NULL)))
		goto err1;
	if(0 != (result = pthread_cond_init(&rw->rw_condreaders, NULL)))
		goto err2;
	if(0 != (result = pthread_cond_init(&rw->rw_condwriters, NULL)))
		goto err3;
	rw->rw_nwaitreaders = 0;
	rw->rw_nwaitwriters = 0;
	rw->rw_refcount = 0;
	rw->rw_magic = RW_MAGIC;
	return 0;

err3:
	pthread_cond_destroy(&rw->rw_condreaders);
err2:
	pthread_mutex_destroy(&rw->rw_mutex);
err1:
	return result;
}

int my_rwlock_destroy(my_rwlock_t *rw)
{
	if(rw->rw_magic != RW_MAGIC)
		return EINVAL;
	if(rw->rw_nwaitreaders != 0 || rw->rw_nwaitwriters != 0
			|| rw->rw_refcount != 0)
		return EBUSY;
	pthread_mutex_destroy(&rw->rw_mutex);
	pthread_cond_destroy(&rw->rw_condreaders);
	pthread_cond_destroy(&rw->rw_condwriters);
	rw->rw_magic = 0;
	return 0;	
}

int my_rwlock_rdlock(my_rwlock_t *rw)
{
	int result = 0;

	if(rw->rw_magic != RW_MAGIC)
		return EINVAL;
	if(0 != (result = pthread_mutex_lock(&rw->rw_mutex)))
		return result; 
#ifdef READERS_PRIORITY
	while(rw->rw_refcount < 0)
#else
	while(rw->rw_refcount < 0 || rw->rw_nwaitwriters > 0)
#endif
	{
		rw->rw_nwaitreaders++;
		pthread_cleanup_push(&rwlock_cancelrdwait, (void*)rw);
		result = pthread_cond_wait(&rw->rw_condreaders, &rw->rw_mutex);
		pthread_cleanup_pop(0);
		rw->rw_nwaitreaders--;
		if(result != 0)	
			break;
	}
	if(result == 0)
		rw->rw_refcount++;
	pthread_mutex_unlock(&rw->rw_mutex);
	return result;
}

int my_rwlock_wrlock(my_rwlock_t *rw)
{
	int result = 0;

	if(rw->rw_magic != RW_MAGIC)
		return EINVAL;
	if(0 != (result = pthread_mutex_lock(&rw->rw_mutex)))
		return result; 
#ifdef READERS_PRIORITY
	while(rw->rw_refcount != 0 || rw->rw_nwaitreaders > 0)
#else
	while(rw->rw_refcount != 0)
#endif
	{
		rw->rw_nwaitwriters++;
		pthread_cleanup_push(&rwlock_cancelwrwait, (void*)rw);
		result = pthread_cond_wait(&rw->rw_condwriters, &rw->rw_mutex);
		pthread_cleanup_pop(0);
		rw->rw_nwaitwriters--;
		if(result != 0)	
			break;
	}
	if(result == 0)
		rw->rw_refcount = -1;
	pthread_mutex_unlock(&rw->rw_mutex);
	return result;
}
int my_rwlock_tryrdlock(my_rwlock_t *rw)
{
	int result = 0;

	if(rw->rw_magic != RW_MAGIC)
		return EINVAL;
	if(0 != (result = pthread_mutex_lock(&rw->rw_mutex)))
		return result; 
#ifdef READERS_PRIORITY
	if(rw->rw_refcount < 0)
#else
	if(rw->rw_refcount < 0 || rw->rw_nwaitwriters > 0)
#endif
		return EBUSY;
	else
		rw->rw_refcount++;
	pthread_mutex_unlock(&rw->rw_mutex);
	return result;
	
}
int my_rwlock_trywrlock(my_rwlock_t *rw)
{
	int result = 0;

	if(rw->rw_magic != RW_MAGIC)
		return EINVAL;
	if(0 != (result = pthread_mutex_lock(&rw->rw_mutex)))
		return result; 
#ifdef READERS_PRIORITY
	if(rw->rw_refcount != 0 || rw->rw_nwaitreaders > 0)
#else
	if(rw->rw_refcount != 0)
#endif
		return EBUSY;
	else
		rw->rw_refcount++;
	pthread_mutex_unlock(&rw->rw_mutex);
	return result;

}

int my_rwlock_unlock(my_rwlock_t *rw)
{
	int result;
	if(rw->rw_magic != RW_MAGIC)
		return EINVAL;
	if(0 != (result = pthread_mutex_lock(&rw->rw_mutex)))
		return result;

	if(rw->rw_refcount > 0)
		rw->rw_refcount--;
	else if(rw->rw_refcount == -1)
		rw->rw_refcount = 0;		
	else
		printf("unlock error refcount : %d\n", rw->rw_refcount);

#ifdef READERS_PRIORITY
	if(rw->rw_nwaitreaders > 0)
		result = pthread_cond_broadcast(&rw->rw_condreaders);
	else if(rw->rw_nwaitwriters > 0)
	{
		if(rw->rw_refcount == 0)
			result = pthread_cond_signal(&rw->rw_condwriters);
	}
#else
	if(rw->rw_nwaitwriters > 0)
	{
		if(rw->rw_refcount == 0)
			result = pthread_cond_signal(&rw->rw_condwriters);
	}
	else if(rw->rw_nwaitreaders > 0)
		result = pthread_cond_broadcast(&rw->rw_condreaders);
#endif

	pthread_mutex_unlock(&rw->rw_mutex);
	return result;
}


void rwlock_cancelrdwait(void * arg)
{
	my_rwlock_t *rw = (my_rwlock_t*)arg;
	rw->rw_nwaitreaders--;
	pthread_mutex_unlock(&rw->rw_mutex);
}
void rwlock_cancelwrwait(void * arg)
{
	my_rwlock_t *rw = (my_rwlock_t*)arg;
	rw->rw_nwaitwriters--;
	pthread_mutex_unlock(&rw->rw_mutex);
}
