#ifndef POSITIVEWRITER_H
#define POSITIVEWRITER_H
#include "randomizer.h"

typedef struct positiveWriter_s * positiveWriter_t;

void * checkNum(void * args);
positiveWriter_t positiveWriter_new(shared_t * pStrc);
void positiveWriter_delete(positiveWriter_t pStruct);
void positiveWriter_join (positiveWriter_t pStruct);

#endif // POSITIVEWRITER_H
