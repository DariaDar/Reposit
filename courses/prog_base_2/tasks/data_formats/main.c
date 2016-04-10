#include <stdio.h>
#include <stdlib.h>
#include "pensioner.h"
#include "parse.h"
#define CNT 3


int main()
{
    pensioner_t pens[CNT];

    for(int i = 0; i < CNT; i++)
        pens[i] = pensioner_new();

    for(int i = 0; i < CNT; i++)
    {
        parse(pens, "pensioners.xml");
    }
    for(int i = 0; i < CNT; i++)
    {
        pensioner_print(pens[i], i);
    }
    for(int i = 0; i < CNT; i++)
        pensioner_delete(pens[i]);

    return 0;
}

