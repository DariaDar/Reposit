#ifndef RESOURCE_H
#define RESOURCE_H
#include "pensioner.h"

typedef struct resource_s resource_t;

resource_t * resource_new();
void resource_free(resource_t * r);
void * resource_add(resource_t * res, pensioner_t * pens);
pensioner_t * resource_getPens(resource_t * res, int index);
pensioner_t * resource_getbyId(resource_t * res, int id);
pensioner_t * resource_deletePens(resource_t * res, int id);
int resource_getCnt(resource_t * res);
int resource_getID(resource_t * res, int index);

#endif // RESOURCE_H
