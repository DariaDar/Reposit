#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char * findWord(char * buf, int len, int lenWord);

void fprocess(const char * pread, const char * pwrite)
{
    int i = 0, len;
    char str[200];
    char * pWord;
    FILE * fp;
    fp = fopen(pread, "r");
    if(fp == NULL)
    {
        printf("File is not found");
        return;
    }

    while(i < 7)
    {
        fgets(str, 200, fp);
        i++;
    }
    fclose(fp);

    len = strlen(str);
    pWord = findWord(str, len, 5);
    if(pWord == NULL)
    {
        printf("Word is not found");
        return;
    }
    printf("Word is found: %s", pWord);

    fp = fopen(pwrite, "w");
    if(fp == NULL)
    {
        printf("Cannot open file");
        return;
    }
    fputs(pWord, fp);
    fclose(fp);
}

int findStart(char * buf, int len)
 {
	 int i;
	 for(i = 0; i < len; i++)
	 {
		 if(buf[i] != 0)
			 return i;
	 }
	 return (-1);
 }

 int findEnd(char * buf, int len)
 {
	 int i;
	 for(i = 0; i < len; i++)
	 {
		 if(buf[i] == 0)
			 return i;
	 }
	 return (-1);
 }


char * findWord(char * buf, int len, int lenWord)
{
	int i, index, posStart, posEnd;
	char * word;

	if(lenWord == 0)
        return NULL;

    for(i = 0; i < len; i++)
	{
		if((buf[i] == '\n') || (buf[i] == '\r') || (buf[i] == ' '))
			buf[i] = 0;
	}

	for(i = 0; i < len; i++)
    {
        posStart = i;
        index = findStart(&buf[i],len - i);

        if(index == -1)
            return NULL;

        posStart = posStart + index;

        posEnd = posStart;
        index = findEnd(&buf[posStart], len - posStart);

        if(index == -1)
            return NULL;

        posEnd = posEnd + index;

        if((posEnd - posStart) > lenWord)
        {
            word = &buf[posStart];
            return word;
        }
        i = posEnd;
    }
    return NULL;
}
