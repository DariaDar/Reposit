#ifndef LIST_H
#define LIST_H

typedef struct list_s list_t;

typedef struct event_s
{
    void * receiver;
    void * callback;
}event_t;

list_t * list_new();
void list_free(list_t * lt);
void list_push_back(list_t * lt, event_t * ptr);
event_t * list_pop_back(list_t * lt);
int list_getCount(list_t * lt);
event_t * list_getElem(list_t * lt, int index);

#endif // LIST_H
