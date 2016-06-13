#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void test();

int getNumber(char * str)
{
    if(str == NULL)
        return -5;

    char * hStr;
    int cnt = 0;
    hStr = strtok(str, "0123456789");
    while(hStr != NULL)
    {
        hStr = strtok(NULL, ".");
        cnt++;
    }
    return cnt - 1;
}


int main()
{
    test();
    char str[] = "main2.0cat3.7Roll72.5";

    int cnt = getNumber(str);
    if(cnt == -5)
    {
        printf("Empty string.");
        return 0;
    }

    printf("Number count: %i", cnt);
    return 0;
}
