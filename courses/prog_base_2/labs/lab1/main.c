#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include "user.h"
#include "queue.h"
#include "user_tests.h"
#include "queue_tests.h"
void user_checkComm(user_t user1, user_t user2, queue_t pQueue);

int main(void)
{
    user_tests();
    queue_tests();
    user_t user1 = user_new(1);
    user_t user2 = user_new(2);
    queue_t pQueue = queue_new();

    clock_t start;
    fflush(stdout);
    char c = 'f';
    while(c != '-')
    {
        start = clock();
        while(clock() - start < CLOCKS_PER_SEC/30)
        {
            user_checkComm(user1, user2, pQueue);
        }
            queue_print(pQueue);
            printf("\n");
            queue_countNull(pQueue);
            c = getch();
    }

    user_delete(user1);
    user_delete(user2);
    queue_delete(pQueue);

    return 0;
}
