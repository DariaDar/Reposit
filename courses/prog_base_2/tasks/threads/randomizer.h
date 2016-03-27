#ifndef RANDOMIZER_H
#define RANDOMIZER_H
#include "mutex.h"
#include "thread.h"

typedef struct shared_s
{
    int * number;
    mutex_t * mu;
}shared_t;

typedef struct random_s * random_t;

void * setNumb(void * args);
random_t random_new(shared_t * pStrc);
void random_delete(random_t pRandom);
#endif //RANDOMIZER_H
