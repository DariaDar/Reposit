#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

int main()
{
    int size, i, j, cnt = 0;
    char * str = calloc(200, sizeof(char));
    const char * exstraStr = "aeoiuyAEOIUY";
    printf("Enter your string: ");
    scanf("%s", str);
    size = strlen(str)/sizeof(str[0]);

    for(i = 0; i < size; i++)
    {
        for(j = 0; j < 12; j++)
        {
            if(str[i] == exstraStr[j])
            {
                cnt = cnt + 1;
            }
        }
    }

    printf("Count of vowels: %i", cnt);
    free(str);
    return 0;
}
