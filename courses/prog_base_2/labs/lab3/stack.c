#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "list.h"

#define STACK_MAX_SIZE 10

struct stack_s
{
    int num;
    int top;
    int arr[STACK_MAX_SIZE];
    list_t * dual;
    void * overflow_sub;
    cb_fn overflow_cb;
    void * empty_sub;
    cb_fn empty_cb;
};


stack_t * stack_new(int num)
{
    stack_t * st;
    st = calloc(1, sizeof(struct stack_s));
    st->num = num;
    st->top = -1;
    st->dual = list_new();
    st->overflow_sub = NULL;
    st->overflow_cb = NULL;
    st->empty_sub = NULL;
    st->empty_cb = NULL;
    return st;
}

void stack_delete(stack_t * st)
{
    list_free(st->dual);
    free(st);
}

void stack_push(stack_t * st, int val)
{
    if(st->top < STACK_MAX_SIZE - 1)
    {
        st->top++;
        st->arr[st->top] = val;
        printf("Value %i was PUSHED on stack %i\n", val, st->num);
        return;
    }
    else
    {
        if(st->overflow_cb != NULL)
        {
            st->overflow_cb(st->overflow_sub, st, OVER, val);
        }
    }
}

int stack_pop(stack_t * st)
{
    if(st->top >= 0)
    {
        int val = st->arr[st->top];
        st->arr[st->top] = 0;
        st->top--;
        printf("Value %i was POPPED from Stack %i\n", val, st->num);
        return val;
    }
    else
    {
        if(st->empty_cb != NULL)
        {
            st->empty_cb(st->empty_sub, st, EMPTY, 0);
        }
    }
    return 0;
}

void stack_insert(stack_t * st, int val)
{
    if(val >= 0)
        stack_push(st, val);
    else
        stack_pop(st);
}

void stack_subsOwerflow(stack_t * st, void * sub, cb_fn cb)
{
    st->overflow_sub = sub;
    st->overflow_cb = cb;
}

void stack_subsEmpty(stack_t * st, void * sub, cb_fn cb)
{
    st->empty_sub = sub;
    st->empty_cb = cb;
}

void stack_AddSubsDual(stack_t * st, void * sub, cb_fn cb)
{
    event_t * ev = (event_t*)calloc(1, sizeof(event_t));
    ev->receiver = sub;
    ev->callback = cb;
    list_push_back(st->dual, ev);
}

void stack_onEvent(void * sub, stack_t * sender, enum event_type type, int last_val)
{
    int count;
    char message[80];
    stack_t * stmp;

    stmp = (stack_t *)sub;
    if(type == OVER)
    {
        if(stmp->top < STACK_MAX_SIZE - 1)
        {
            sprintf(message, "Event OVER: Stack %i is FULL.\n", sender->num);
            printf(message);
            stack_push(stmp, last_val);
        }
        else
        {
            //Sub stack1
            count = list_getCount(stmp->dual);
            for(int i = 0; i < count; i++)
            {
                event_t * ev = list_getElem(stmp->dual, i);
                if(ev->callback != NULL)
                {
                    cb_fn fn = (cb_fn)ev->callback;

                    sprintf(message, "%s", (char *)ev->receiver);
					fn(ev->receiver, stmp, DUAL, 1);
                }
            }

            //Sub stack 2
            count = list_getCount(sender->dual);
            for(int i = 0; i < count; i++)
            {
                event_t * ev = list_getElem(sender->dual, i);
                if(ev->callback != NULL)
                {
                    cb_fn fn1 = (cb_fn)ev->callback;

                    sprintf(message, "%s", (char *)ev->receiver);
					fn1(ev->receiver, sender, DUAL, 1);
                }
            }
        }
    }

    if(type == EMPTY)
    {
        if(stmp->top >= STACK_MAX_SIZE)
        {
            sprintf(message, "Event EMPTY: Stack %i is EMPTY\n", sender->num);
            printf(message);
            stack_push(sender, stack_pop(stmp));
        }
        else
        {
            //Sub stack1
            count = list_getCount(stmp->dual);
            for(int i = 0; i < count; i++)
            {
                event_t * ev = list_getElem(stmp->dual, i);
                if(ev->callback != NULL)
                {
                    cb_fn fn = (cb_fn)ev->callback;

                    sprintf(message, "%s", (char *)ev->receiver);
					fn(ev->receiver, stmp, DUAL, 0);
                }
            }

            //Sub stack 2
            count = list_getCount(sender->dual);
            for(int i = 0; i < count; i++)
            {
                event_t * ev = list_getElem(sender->dual, i);
                if(ev->callback != NULL)
                {
                    cb_fn fn1 = (cb_fn)ev->callback;

                    sprintf(message, "%s", (char *)ev->receiver);
					fn1(ev->receiver, sender, DUAL, 0);
                }
            }
        }
    }
    if(type == DUAL)
    {
        user_t * user = (user_t *)sub;
        if(last_val)
            sprintf(message, "Event DUAL: User %s. Stack %i is FULL.\n", user->name, sender->num);
        else
            sprintf(message, "Event DUAL: User %s. Stack %i is EMPTY.\n", user->name, sender->num);
        printf(message);
    }

}
