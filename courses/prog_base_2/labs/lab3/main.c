#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "list.h"
#include <time.h>
#include "webpage.h"


void user_tests();

typedef struct client_s
{
    char name[100];
}client_t;

void clientInfo(void * receiver, char * message)
{
    client_t * client = (client_t *)receiver;
    printf("Client %s, message: %s\n", client->name, message);
}

int rangedRand(int minVal, int maxVal)
{
    int val = rand()%(maxVal - 1) + minVal;
    return val;
}

void chooseAction(stack_t * st, int val)
{
    if(val >= 0)
        stack_push(st, val);
    else
        stack_pop(st);
}

int main()
{
    user_tests();
    time_t t;
    srand(time(&t));

    webpage_t * wp1 = webpage_new();
    webpage_t * wp2 = webpage_new();

    stack_t * st1 = stack_new(1);
    stack_t * st2 = stack_new(2);

    stack_setSt(st1, st2);
    stack_setSt(st2, st1);

    stack_setWebpage(st1, wp1);
    stack_setWebpage(st2, wp2);

    client_t clients[4] = {{"Taras"}, {"Olya"}, {"Ira"}, {"Andriy"}};
    for(int i = 0; i < 4; i++)
    {
        webpage_subscribeNotification(wp1, &clients[i], clientInfo);
        webpage_subscribeNotification(wp2, &clients[i], clientInfo);
    }

    for(int i = 0; i < 5; i++)
	{
		stack_push(st1, i+1);
		stack_push(st2, 0 - (i+1));
	}

    while(1)
    {
        int randSt = rangedRand(1, 3);
        int randNum = rangedRand(-100, 100);
        switch(randSt)
        {
        case 1:
            chooseAction(st1, randNum);
            break;
        case 2:
            chooseAction(st2, randNum);
            break;
        default:
            break;
        }
        sleep(1);
    }
    stack_delete(st1);
    stack_delete(st2);
    webpage_free(wp1);
    webpage_free(wp2);
    return 0;
}
