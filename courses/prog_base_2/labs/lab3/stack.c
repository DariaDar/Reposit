#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

struct stack_s
{
    int num;
    int * arr;
    int top;
    cb_push_val pushToObj;
    cb_pop_val popFromObj;
    stack_t * obj;
    webpage_t * wb;
};

//Push in another stack
int push_val(stack_t * st, int val)
{
    if(st->top < MAX_STACK_SIZE)
    {
        stack_push(st, val);
        printf("-----Push  %d to stack number %d------\n", val, st->num);
        return 1;
    }
    return 0;
}

//Pop from another stack
int pop_val(stack_t * st, int *val)
{
    if(stack_peek(st) >= 0)
    {
        *val = stack_pop(st);
        printf("-----Pop  %d from stack number %d------\n", *val, st->num);
        return 1;
    }
    return 0;
}

//Pointer to the second object
void stack_setSt(stack_t * self, stack_t * st)
{
    self->obj = st;
}

stack_t * stack_new(int number)
{
    stack_t * st;
    st = calloc(1, sizeof(struct stack_s));
    st->num = number;
    st->arr = malloc(MAX_STACK_SIZE * sizeof(int));
    st->top = -1;
    st->pushToObj = push_val;
    st->popFromObj = pop_val;
    return st;
}

void stack_delete(stack_t * st)
{
    free(st->arr);
    free(st);
}

void stack_push(stack_t * st, int value)
{
    char message[80];
    if(st->top < MAX_STACK_SIZE)
    {
        st->top += 1;
        st->arr[st->top] = value;
        printf("Pushed value on Stack %i\n", st->num);
    }
    else
        {
            int tran = st->pushToObj(st->obj, value);
            if(tran == 0)
            {
               sprintf(message, "Stack %i is full!\n", st->num);
               webpage_sendMessage(st->wb, message);
            }
        }
}

int stack_pop(stack_t * st)
{
    char message[80];
    int val = 0;
    if(st->top >= 0)
    {
        val = stack_peek(st);
        st->top--;
        printf("Popped value from Stack %i.\n", st->num);
        return val;
    }
    else
    {
        val = 0;
        int tran = st->popFromObj(st->obj, &val);
        if(tran == 0)
        {
            sprintf(message, "Stack %i is empty!", st->num);
            webpage_sendMessage(st->wb, message);
        }
        else
        {
            stack_push(st, val);
        }
    }
    return val;
}

int stack_peek(stack_t * st)
{
    if(st->top == -1)
        return -1;
    return st->arr[st->top];
}

void stack_setWebpage(stack_t * st, webpage_t * wp)
{
    st->wb = wp;
}

int stack_getCount(stack_t * st)
{
    return st->top;
}

int stack_getStackNum(stack_t * st)
{
    return st->num;
}
