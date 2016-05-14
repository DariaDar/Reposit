#ifndef STACK_H
#define STACK_H

typedef struct stack_s stack_t;
stack_t * stack_new();
void stack_delete(stack_t * self);
void stack_push(stack_t * self, char * str);
char * stack_pop(stack_t * self);
char * stack_peek(stack_t * self);
int stack_getCount(stack_t * self);
void stack_print(stack_t * self);

#endif // STACK_H
