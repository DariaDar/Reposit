#include <stdio.h>
#include <stdlib.h>

char * checkStr(char * str, int linesNum, struct Keys *pKeys)
{
    int i;
    char * strRes[100];
    for(i = 0; i < linesNum; i++)
    {
        if(str[i] == (*pKeys).hello)
            strRes[i] =(*pKeys).hello;
        else if (str[i] == (*pKeys).cat)
            strRes[i] =(*pKeys).cat;
        else if (str[i] == (*pKeys).file)
            strRes[i] =(*pKeys).file;
    }
    return strRes;
}

int main()
{
    struct Keys
    {
        char *hello[10] = "hello";
        char *cat[10] = "cat";
        char *file[10] = "file"
    };

    struct Keys arr[] = {1, 2 , 3};;

    struct Keys * pKeys;

    char * string[100];
    printf("Enter string:");
    scanf("%s", str);

    int linesNum = strlen(string) / sizeof(str[0]);

    printf("%s", checkStr(str, linesNum, pKeys));


    return 0;
}
