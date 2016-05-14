#include <stdio.h>
#include <string.h>
#include "main.h"

int check(stack_t * st, char * str)
{
    if((int)stack_getCount(st) > 10)
        return 1;
    return 0;
}

void reaction(stack_t * st, char * str)
{
    int l = strlen(str);
    for(int i = 0; i < strlen(str); i++)
    {
        stack_pop(st);
    }
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
