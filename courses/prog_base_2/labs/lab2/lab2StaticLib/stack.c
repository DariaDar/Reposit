#define DATA_MAX 50
#define LINE_MAX 50
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct stack_s
{
    char arr[DATA_MAX][LINE_MAX];
    int top;
};


stack_t * stack_new()
{
    stack_t * self = malloc(sizeof(struct stack_s));
    self->top = 0;
    for(int i = 0; i < DATA_MAX; i++)
    {
        self->arr[i][0] = '\0';
    }
    return self;
}

void stack_delete(stack_t * self)
{
    free(self->arr);
    free(self);
}

void stack_push(stack_t * self, char * str)
{
    if(stack_getCount(self) >= DATA_MAX)
    {
        printf("Stack overflow.");
        return;
    }
    strcpy(self->arr[self->top], str);
    self->top += 1;
}

char * stack_pop(stack_t * self)
{
    if(self->top > 0)
    {
        char * val = stack_peek(self);
        self->top -= 1;
        return val;
    }
    else
    {
        printf("Stack is empty.");
        return NULL;
    }
}

char * stack_peek(stack_t * self)
{
    if(stack_getCount(self) == 0)
    {
        printf("Empty stack");
        return NULL;
    }
    return self->arr[self->top];
}

int stack_getCount(stack_t * self)
{
    return self->top;
}

void stack_print(stack_t * self)
{
    fflush(stdin);
    printf("---------\n");
    if(self->top == 0)
    {
        printf("Empty stack.\n");
        return;
    }
    for(int i = 0; i < self->top; i++)
    {
        printf("%i: %s\n", i + 1, self->arr[i]);
    }
    printf("\n---------\n\n");
}
