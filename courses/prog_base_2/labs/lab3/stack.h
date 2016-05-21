#ifndef STACK_H
#define STACK_H

#include "list.h"

enum event_type
{
    OVER,
    EMPTY,
    DUAL
};

typedef struct user_s
{
    char name[100];
};

typedef struct stack_s stack_t;
typedef struct user_s user_t;

typedef void (*cb_fn)(void * sub, stack_t * st, enum event_type type, int last_val);

stack_t * stack_new(int num);
void stack_delete(stack_t * st);
void stack_push(stack_t * st, int val);
int stack_pop(stack_t * st);
void stack_insert(stack_t * st, int val);


void stack_subsOwerflow(stack_t * st, void * sub, cb_fn cb);
void stack_subsEmpty(stack_t * st, void * sub, cb_fn cb);
void stack_AddSubsDual(stack_t * st, void * sub, cb_fn cb);
void stack_onEvent(void * sub, stack_t * sender, enum event_type type, int last_val);

#endif // STACK_H
