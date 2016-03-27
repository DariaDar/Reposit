#include "randomizer.h"
#include <stdio.h>
#include <stdlib.h>
#include "mutex.h"
#include "thread.h"
#include <time.h>

struct random_s
{
    thread_t * thread;
};

void * setNumb(void * args)
{
    srand(time(NULL));
    shared_t * pRandom = (shared_t *)args;
    while(1)
    {
        mutex_lock(pRandom->mu);
        *pRandom->number = rand()%200-100;
        mutex_unlock(pRandom->mu);
    }
    return NULL;
}


random_t random_new(shared_t * pStrc)
{
    random_t pRandom = calloc(1, sizeof(random_t));;
    pRandom->thread = thread_create_args(setNumb, pStrc);
    return pRandom;
}

void random_delete(random_t pRandom)
{
    thread_free(pRandom->thread);
    free(pRandom);
}
