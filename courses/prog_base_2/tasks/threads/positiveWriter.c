#include <stdio.h>
#include <stdlib.h>
#include "positiveWriter.h"
#include "randomizer.h"
#include "mutex.h"
#include "thread.h"
#include <windows.h>
struct positiveWriter_s
{
    thread_t * thread;
};

void * checkNum(void * args)
{
    shared_t * pStruct = (shared_t *)args;
    while(1)
    {
         while(1)
         {
             mutex_lock(pStruct->mu);
             if(*pStruct->number > 0)
             {
                 printf("%i\n", *pStruct->number);
                 Sleep(100);
             }
              mutex_unlock(pStruct->mu);
         }
    }
    return NULL;
}
positiveWriter_t positiveWriter_new(shared_t * pStrc)
{
    positiveWriter_t pStruct = calloc(1, sizeof(positiveWriter_t));
    pStruct->thread = thread_create_args(checkNum, pStrc);
    return pStruct;
}

void positiveWriter_delete(positiveWriter_t pStruct)
{
    thread_free(pStruct->thread);
    free(pStruct);
}


void positiveWriter_join (positiveWriter_t pStruct)
{
    thread_join(pStruct->thread);
}
