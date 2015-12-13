#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

int sum(const char * str, int len, int cnt);

int main()
{
    char str[100];
    int len, res = 0, cnt = 0;
    printf("Enter your sting: ");
    gets(str);
    len = strlen(str);
    res = sum(str, len, cnt);
    printf("cnt = %i", res);

    return 0;
}

int sum(const char * str, int len, int cnt)
{
    if(len == 0)
            return cnt;
    if(str[0] != ' ')
        sum(str + 1,len - 1, cnt);
    else
        sum(str + 1,len - 1, cnt + 1);
}
