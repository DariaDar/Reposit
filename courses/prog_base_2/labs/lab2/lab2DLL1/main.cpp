#include "main.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int check(stack_t * st, char * str)
{
    char buf[100];
    char word[50];
    sscanf(str, "%s", word);
    if(strstr(word, "pop") != NULL)
    {
        for(int i = 4; i < (int)strlen(word); i++)
        {
            if(isdigit(word[i]))
                sprintf(buf,"%i", word[i]);
        }
        return 1;
    }
    else
        return 0;
}

void reaction(stack_t * st, char * str)
{
    int num;
    sscanf(str, "pop %i", &num);
    if(num > stack_getCount(st))
    {
        printf("Number is bigger than count elements in stack.");
        return;
    }
    for(int i = 0; i < num - 1; i++)
        stack_pop(st);
}

extern "C" DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            // attach to process
            // return FALSE to fail DLL load
            break;

        case DLL_PROCESS_DETACH:
            // detach from process
            break;

        case DLL_THREAD_ATTACH:
            // attach to thread
            break;

        case DLL_THREAD_DETACH:
            // detach from thread
            break;
    }
    return TRUE; // succesful
}
