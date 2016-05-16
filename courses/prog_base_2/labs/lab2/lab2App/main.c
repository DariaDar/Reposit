#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <string.h>

#include <stack.h>

typedef int (*check_f)(stack_t * st, char * str);
typedef void (*reaction_f)(stack_t * st, char * str);

typedef struct dynamic_s
{
    HANDLE hLib;
    check_f check;
    reaction_f reaction;
}dynamic_t;

//dynamic_t * dynamic_init(const char * dllName);


const char * userChoise()
{
    int n;
    fflush(stdin);
    printf("Choose DLL:\n1. lab2DLL1\n2. lab2DLL2\n>>");
    scanf("%i", &n);
    if(n == 1)
        return "lab2DLL1.dll";
    else if(n == 2)
        return "lab2DLL2.dll";
    return NULL;
}

dynamic_t * dynamic_init(const char * dllName)
{
    dynamic_t * dyn = malloc(sizeof(struct dynamic_s));
    dyn->hLib = LoadLibrary(dllName);
    dyn->check = NULL;
    dyn->reaction = NULL;
    if(NULL != dyn->hLib)
    {
        dyn->check = (check_f)GetProcAddress(dyn->hLib, "check");
        dyn->reaction = (reaction_f)GetProcAddress(dyn->hLib, "reaction");
        return dyn;
    }
    else
        return NULL;
}

void dynamic_clean(dynamic_t * dyn)
{
    FreeLibrary(dyn->hLib);
    free(dyn);
}

int main()
{
    stack_t * st = stack_new();
    const char * dllName = userChoise();
    dynamic_t * dll = dynamic_init(dllName);
    if(dll == NULL)
    {
        printf("Can't get compare function!\n");
        return 1;
    }
    if(dll->reaction == NULL)
    {
        printf("Can't get reaction function!\n");
        return 1;
    }
    if(dll->check == NULL)
    {
        printf("Can't get check function!\n");
        return 1;
    }
    printf("Dynamic loaded!\n");
    srand(time(NULL));

    while(1)
    {
        printf("Enter the command: ");
        char command[50];
        fflush(stdin);
        gets(command);
        if(dll->check(st, command))
        {
            dll->reaction(st, command);
        }
        char word[50];
        char numb[50];
        sscanf(command, "%s", word);
        if(strcmp(word, "push") == 0)
        {
            sscanf(command, "%s %s", word, numb);
            stack_push(st, numb);
            stack_print(st);
        }
        else if(strcmp(word, (char *)"pop") == 0)
        {
            stack_pop(st);
            stack_print(st);
        }
        else if(strcmp(word, "peek") == 0)
        {
            printf("Peek: %s\n", stack_peek(st));
        }
        else if(strcmp(word, "count") == 0)
        {
            printf("Count: %i\n", stack_getCount(st));
        }
        else if(strcmp(word, "exit") == 0)
        {
            return 0;
        }
        else if(strlen(command) > 0)
        {
            printf("Unknown command.\n");
        }
    }
}
