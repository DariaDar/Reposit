#include <stdlib.h>
#include "resource.h"
#include <string.h>
#include "pensioner.h"
#define MAX_SIZE 300

struct resource_s
{
	pensioner_t * arr[MAX_SIZE];
	int size;
};

resource_t * resource_new()
{
	resource_t * res = calloc(1, sizeof(struct resource_s));
	res->size = 0;
	return res;
}

void resource_free(resource_t * res)
{
	for(int i = 0; i < res->size; i++)
    {
        pensioner_delete(res->arr[i]);
    }
	free(res);
}

void * resource_add(resource_t * res, pensioner_t * pens)
{
    res->arr[res->size] = pens;
    res->size++;
}

pensioner_t * resource_getbyId(resource_t * res, int id)
{
    for(int i = 0; i < res->size; i++)
	{
		if(res->arr[i]->id == id)
		{
			return(res->arr[i]);
		}
	}
	return NULL;
}

pensioner_t * resource_getPens(resource_t * res, int index)
{
    return res->arr[index];
}

int resource_getID(resource_t * res, int index)
{
    return res->arr[index]->id;
}

pensioner_t * resource_deletePens(resource_t * res, int id)
{
    pensioner_t * toDel;
    for(int i = 0; i < res->size; i++)
    {
        if(res->arr[i]->id == id)
        {
            toDel = res->arr[i];
            for (int j = i; j < res->size - 1; j++)
            {
                res->arr[j] = res->arr[j+1];
            }
            res->size--;
        }
    }
    return toDel;
}

int resource_getCnt(resource_t * res)
{
	return res->size;
}


