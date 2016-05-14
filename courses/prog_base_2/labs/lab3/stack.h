#ifndef STACK_H
#define STACK_H

#define MAX_STACK_SIZE 10
#include "webpage.h"
typedef struct stack_s stack_t;

typedef int (*cb_push_val)(stack_t * st, int ival);
typedef int (*cb_pop_val)(stack_t * st, int *ival);

stack_t * stack_new();
void stack_delete(stack_t * st);

void stack_push(stack_t * st, int value);
int stack_pop(stack_t * st);
int stack_peek(stack_t * st);
int stack_getCount(stack_t * st);
void stack_setWebpage(stack_t * st, webpage_t * wp);
void stack_setSt(stack_t * self, stack_t * st1);
int stack_getStackNum(stack_t * st);

#endif // STACK_H
