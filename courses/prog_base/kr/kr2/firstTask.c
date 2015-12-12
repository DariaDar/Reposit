#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <strings.h>
#include <ctype.h>

//VAR N8
void file(const char * pread, const char * pwrite);


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

int findWords(char * buf , int len, int min, int Max)
{
    int i, index, posStart, posEnd, a,b, res;

    for(i = 0; i < len; i++)
	{
		a = buf[i];
		b = isalpha(a);
		if(b == 0)
        {
            buf[i] = 0;
        }
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

        //word = &buf[posStart];

        if((posEnd - posStart) <= min)
        {
            min = posEnd - posStart;
        }
        if((posEnd - posStart >= Max))
        {
            Max = posEnd - posStart;
        }
        i = posEnd;
    }
    res = Max - min;
    return res;
}

void file(const char * pread, const char * pwrite)
{
    char str[200];
    int len;
    int resWord;
    int min = 100;
    int Max = 1;
    FILE * fp;

    fp = fopen(pread,"r");
    if(fp == NULL)
    {
        printf("File is not found!");
        return;
    }

    fgets(str,200,fp);
    fclose(fp);

    len = strlen(str);
    resWord = findWords(str,len, min, Max);

    printf("Res: %i", resWord);

    fp = fopen(pwrite, "w");
    if(fp == NULL)
    {
        printf("Error! Can't open file.");
        return;
    }

    char str11[100];
    sprintf(str11, "%i", resWord);
    fputs(str11, fp);
    fclose(fp);
}

int main(int argc, char * argv[])
{
    file(argv[1],argv[2]);
    return 0;
}
