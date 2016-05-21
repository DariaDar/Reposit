#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "stack.h"
#include "list.h"
void user_tests();

int randR(int minV, int maxV)
{
    int val;
    val = (int)((double)rand() / (RAND_MAX + 1) * (maxV - minV) + minV);
    return val;
}


int main()
{
    user_tests();

    stack_t * st1 = stack_new(1);
    stack_t * st2 = stack_new(2);

    stack_subsOwerflow(st1, st2, stack_onEvent);
    stack_subsEmpty(st1, st2, stack_onEvent);

    stack_subsOwerflow(st2, st1, stack_onEvent);
    stack_subsEmpty(st2, st1, stack_onEvent);

    user_t users1[4] = {{"Taras"}, {"Olya"}, {"Ira"}, {"Andriy"}};
    user_t users2[3] = {{"Jess"}, {"John"}, {"Rob"}};
    for(int i = 0; i < 4; i++)
    {
        stack_AddSubsDual(st1, &users1[i], stack_onEvent);
    }
    for(int i = 0; i < 3; i++)
    {
        stack_AddSubsDual(st2, &users2[i], stack_onEvent);
    }

    for(int i = 0; i < 5; i++)
    {
        stack_push(st1, i);
        stack_push(st2, i + 1);
    }

    while(1)
    {
        int stNum = randR(1, 3);
        int val = randR(-100, 100);
        switch(stNum)
        {
        case 1:
            stack_insert(st1, val);
            break;
        case 2:
            stack_insert(st2, val);
            break;
        }
        sleep(1);
    }

    stack_delete(st1);
    stack_delete(st2);
    return 0;
}
