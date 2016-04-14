#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#include "user.h"
#include "queue.h"



enum KEYS
{
    USER1_LEFT = 0,
    USER1_UP,
    USER1_RIGHT,
    USER1_DOWN,
    USER1_FIRE,
    USER2_LEFT,
    USER2_UP,
    USER2_RIGHT,
    USER2_DOWN,
    USER2_FIRE
};


struct user_s
{
    int userCode;
}USER;

user_t user_new(int userCode)
{
    if(userCode < 0)
        return NULL;
    user_t pStruct;
    pStruct = calloc(1, sizeof(USER));
    pStruct->userCode = userCode;
    return pStruct;
}

void user_delete(user_t pStruct)
{
    free(pStruct);
}

int user_getUserCode(user_t pUser)
{
    return pUser->userCode;
}

void user_checkComm(user_t user1, user_t user2, queue_t pQueue)
{
    char num = getch();
    if(!kbhit())
    {
         switch (num)
        {
        case 'a':
            queue_enqueue(pQueue, user1->userCode, USER1_LEFT);
            break;
        case 'w':
            queue_enqueue(pQueue, user1->userCode, USER1_UP);
            break;
        case 'd':
            queue_enqueue(pQueue, user1->userCode, USER1_RIGHT);
            break;
        case 's':
            queue_enqueue(pQueue, user1->userCode, USER1_DOWN);
            break;
        case 'q':
            queue_enqueue(pQueue, user1->userCode, USER1_FIRE);
            break;
        case 'h':
            queue_enqueue(pQueue, user2->userCode, USER2_LEFT);
            break;
        case 'u':
            queue_enqueue(pQueue, user2->userCode, USER2_UP);
            break;
        case 'k':
            queue_enqueue(pQueue, user2->userCode, USER2_RIGHT);
            break;
        case 'j':
            queue_enqueue(pQueue, user2->userCode, USER2_DOWN);
            break;
        case 'i':
            queue_enqueue(pQueue, user2->userCode, USER2_FIRE);
            break;
        default: return;
        }
    return;
    }
}
