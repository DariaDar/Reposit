#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include "user.h"

const char * descCom[] = {"Left","Up","Right","Down","Attacked","Left","Up","Right","Down","Attacked"};

typedef struct command
{
    int userNumb;
    int cmd;
    char * description;

} COMMAND;

struct queue_s
{
    int Qend;
    int Qhead;
    COMMAND pCommand[200];
}QUEUE;

queue_t queue_new()
{
    queue_t pQueue;
    pQueue = calloc(1, sizeof(QUEUE));
    pQueue->Qend = 0;
    pQueue->Qhead = 0;
    return pQueue;
}

void queue_delete(queue_t pQueue)
{
    free(pQueue);
}

void queue_enqueue(queue_t pQueue, int uNumb, int code)
{
    pQueue->pCommand[pQueue->Qend].cmd = code;
    pQueue->pCommand[pQueue->Qend].userNumb = uNumb;
    pQueue->pCommand[pQueue->Qend].description = descCom[code];
    pQueue->Qend++;
}

struct command queue_dequeue(queue_t pQueue)
{
    COMMAND temp = pQueue->pCommand[pQueue->Qhead];
    pQueue->Qhead++;
    return temp;
}


int queue_getLastUser(queue_t pQueue)
{
    return pQueue->pCommand[pQueue->Qend - 1].userNumb;
}

int queue_getLastCommand(queue_t pQueue)
{
    return pQueue->pCommand[pQueue->Qend - 1].cmd;
}

int queue_getQEnd(queue_t pQueue)
{
    return pQueue->Qend;
}

void queue_print(queue_t pQueue)
{
    for(int i = 0; i < pQueue->Qend; i++)
    {
        printf("Player %i: %s\n", pQueue->pCommand[i].userNumb, pQueue->pCommand[i].description);
    }
}

void queue_countNull(queue_t pQueue)
{
    pQueue->Qend = 0;
    pQueue->Qhead = 0;
}

int queue_getCntElem(queue_t pQueue)
{
    int cnt = 0;
    for(int i = 0; i < pQueue->Qend; i++)
    {
        if(pQueue->pCommand[i].userNumb == 1 || pQueue->pCommand[i].userNumb == 2)
            cnt++;
    }
    return cnt;
}
