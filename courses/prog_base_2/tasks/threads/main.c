#include <stdio.h>
#include <stdlib.h>
#include "randomizer.h"
#include "positiveWriter.h"
#include "mutex.h"
#include "thread.h"
#include <windows.h>

int main()
{
    shared_t sharedData;
    int value = 0;
    sharedData.number = &value;
    sharedData.mu = mutex_new();

    random_t rand1 = random_new(&sharedData);
    random_t rand2 = random_new(&sharedData);
    random_t rand3 = random_new(&sharedData);
    positiveWriter_t posNum = positiveWriter_new(&sharedData);

    positiveWriter_join (posNum);

    random_delete(rand1);
    random_delete(rand2);
    random_delete(rand3);

    positiveWriter_delete(posNum);
    mutex_free(sharedData.mu);
    return 0;
}
