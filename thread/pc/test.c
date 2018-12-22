#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>

#define OVER -1
#define COUNT 20
#define BUFFER_SIZE 8

typedef struct 
{
    int buffer[BUFFER_SIZE];
    pthread_mutex_t mutex;
    pthread_cond_t  notfull;
    pthread_cond_t  notempty;
    int writepos;
    int readpos;
}pc_st;

static pc_st pct;

void init_pc(pc_st *pc)
{
    memset(pc->buffer, 0, sizeof(pc->buffer));
    //pc->mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_init(&pc->mutex, NULL);
    pthread_cond_init(&pc->notfull, NULL);
    pthread_cond_init(&pc->notempty,NULL);
    pc->writepos = 0;
    pc->readpos = 0;
}
void destroy_pc(pc_st *pc)
{
    memset(pc->buffer, 0, sizeof(pc->buffer));
    pthread_mutex_destroy(&pc->mutex);
    pthread_cond_destroy(&pc->notfull);
    pthread_cond_destroy(&pc->notempty);
    pc->writepos = 0;
    pc->readpos = 0;
}

////////////////////////////////////////////////////////
void put_value(pc_st *pc, int val)
{
	pthread_mutex_lock(&pc->mutex);
	if((pc->writepos + 1) % BUFFER_SIZE == pc->readpos)
		pthread_cond_wait(&pc->notfull, &pc->mutex);
    pc->buffer[pc->writepos] = val;
    pc->writepos = (pc->writepos + 1) % BUFFER_SIZE;
	pthread_cond_signal(&pc->notempty);
	pthread_mutex_unlock(&pc->mutex);
}
int get_value(pc_st *pc)
{
	pthread_mutex_lock(&pc->mutex);
	if(pc->writepos == pc->readpos)
		pthread_cond_wait(&pc->notempty, &pc->mutex);
    int value = pc->buffer[pc->readpos];
    pc->readpos = (pc->readpos + 1) % BUFFER_SIZE;
	pthread_cond_signal(&pc->notfull);
	pthread_mutex_unlock(&pc->mutex);
    return value;
}
////////////////////////////////////////////////////////

void* producer(void *arg)
{
    int i = 1;
    for(; i<=COUNT; ++i)
    {
        put_value(&pct, i);
    }
    put_value(&pct, OVER);
}
void* consumer(void *arg)
{
    int value;
    while(1)
    {
        value = get_value(&pct);
        if(value == OVER)
            break;
        printf("value = %d\n",value);
        sleep(1);
    }
}

int main()
{
    init_pc(&pct);
    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, producer, NULL);
    pthread_create(&tid2, NULL, consumer, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    destroy_pc(&pct);
    return 0;
}
