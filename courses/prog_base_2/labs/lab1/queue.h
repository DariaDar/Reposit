#ifndef QUEUE_H
#define QUEUE_H
#include "user.h"


typedef struct queue_s * queue_t;

queue_t queue_new();
void queue_delete(queue_t pQueue);

void queue_enqueue(queue_t pQueue, int uNumb, int code);
struct command queue_dequeue(queue_t pQueue);
int queue_getLastUser(queue_t pQueue);
int queue_getLastCommand(queue_t pQueue);
int queue_getQEnd(queue_t pQueue);
void queue_print(queue_t pQueue);
void queue_countNull(queue_t pQueue);
int queue_getCntElem(queue_t pQueue);


#endif // QUEUE_H
