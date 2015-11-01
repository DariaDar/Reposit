#include <string.h>
#include <stdio.h>

char * process(char * resultStr, const char * textLines[], int linesNum, const char * extraStr)
{

    int i, v;
    int j;
    int k;
    int s;
    int l = 0;
    int q = 0;
    char str[100];
    str[0] = 0;


    for(i = 0; i < linesNum; i++)
    {
        s = 0;
        for(j = 0; j < strlen(extraStr); j++)
        {
            for(k = 0; k < strlen(textLines[i]); k++)
            {
                if(*(textLines[i] + k) == extraStr[j])
                {
                    s++;
                    l = i;

                }
            }
        }

        if(s > 0)
        {
            q = q +1;
            strcat(str, textLines[l]);
            strcat(str, ", ");

        }
    }
    str[strlen(str) - 2] = 0;
    sprintf(resultStr, "%i", q);
    strcat(resultStr, " ");
    strcat(resultStr, str);





    return resultStr;
}
