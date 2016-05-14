#include <stdlib.h>
#include "list.h"

struct list_s
{
    event_t ** arr;
    int count;
};

list_t * list_new()
{
    list_t * lt;
    lt = malloc(sizeof(struct list_s));
    lt->count = 0;
    lt->arr = malloc(0);
    return lt;
}

void list_free(list_t * lt)
{
    free(lt->arr);
    free(lt);
}

void list_push_back(list_t * lt, event_t * ptr)
{
    lt->count++;
    lt->arr = realloc(lt->arr, sizeof(void *) * lt->count);
    lt->arr[lt->count - 1] = ptr;
}


event_t * list_pop_back(list_t * lt)
{
    lt->count--;
    event_t * ret = lt->arr[lt->count];
    lt->arr = realloc(lt->arr, sizeof(void *) * lt->count);
    return ret;
}

int list_getCount(list_t * lt)
{
    return lt->count;
}

event_t * event_getElem(list_t * lt, int index)
{
    return lt->arr[index];
}


