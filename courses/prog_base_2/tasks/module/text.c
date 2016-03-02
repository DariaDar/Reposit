#include "text.h"
#include <stdio.h>
#include <string.h>



text_t text_new( int cntMax, char * str)
{
    text_t pStruct;

    pStruct = calloc(1, sizeof(struct text_s));
    pStruct->cntMax = cntMax;

    pStruct->StrIn = calloc(cntMax,sizeof(STRIN));
    if(str != NULL)
    {
        pStruct->StrIn[0].pStr = calloc(strlen(str) + 1,sizeof(char));
        memcpy(pStruct->StrIn[0].pStr, str, strlen(str));
        pStruct->StrIn[0].formatting = 0;
        pStruct->cntReal = 1;
    }
    //printf("%s\n", pStruct->StrIn[0].pStr);

    return pStruct;
}

void text_delete(text_t textStruct)
{
    int i;
    for(i = 0; i < textStruct->cntMax; i++)
    {
        if(textStruct->StrIn[i].pStr != NULL)
        {
            free(textStruct->StrIn[i].pStr);
            textStruct->StrIn[i].pStr = NULL;
        }
    }
    free(textStruct->StrIn);
    free(textStruct);
}

int text_getRealCntStr(text_t pStruct)
{
    int i;
    pStruct->cntReal = 0;
    for(i = 0; i < pStruct->cntMax; i++)
    {
        if(pStruct->StrIn[i].pStr != NULL)
        {
            pStruct->cntReal++;
        }
    }
    return pStruct->cntReal;
}


void text_setFormat(int index, int formatNumber, text_t pStruct)
{
    if(index > pStruct->cntReal || index < 0)
        return;
    if(formatNumber >= 0 && formatNumber <=3)
    {
        pStruct->StrIn[index].formatting = formatNumber;
    }
    else
        printf("Wrong number");

}

void text_getListForm(text_t pStruct, int format)
{
    int i;
    for(i = 0; i < pStruct->cntReal; i++)
    {
        if(pStruct->StrIn[i].formatting == format)
        {
            printf("%i. %s\n", i,pStruct->StrIn[i].pStr);
        }
    }
}

void text_deleteStr(text_t pStruct, int index)
{
    int i;
    STRIN tmp;
    if(pStruct->cntReal == 0)
    {
        return;
    }
    if(index >= pStruct->cntReal)
        return;
    if(pStruct->StrIn[index].pStr != NULL)
    {
        free(pStruct->StrIn[index].pStr);
        pStruct->StrIn[index].pStr = NULL;
    }


    for(i = index; i < pStruct->cntReal - 1; i++)
    {
        memcpy(&tmp, &pStruct->StrIn[i], sizeof(STRIN));
        memcpy(&pStruct->StrIn[i], &pStruct->StrIn[i + 1], sizeof(STRIN));
        memcpy(&pStruct->StrIn[i + 1], &tmp, sizeof(STRIN));
    }
    pStruct->cntReal--;
}

void text_Insert(text_t pStruct, int index, char * _pStr)
{
    int i;

    if(pStruct->cntReal >= pStruct->cntMax)
        return;
    if(index < 0 || index > pStruct->cntReal)
        return;
    for(i = pStruct->cntReal - 1; i >= index; i--)
    {
        memcpy(&pStruct->StrIn[i+1], &pStruct->StrIn[i], sizeof(STRIN));
    }
    pStruct->StrIn[index].pStr = NULL;
    pStruct->StrIn[index].formatting = 0;

    pStruct->StrIn[index].pStr = calloc(strlen(_pStr) + 1,sizeof(char));
    memcpy(pStruct->StrIn[index].pStr, _pStr, strlen(_pStr));
    pStruct->StrIn[index].formatting = 0;
    pStruct->cntReal++;
}
void text_getList(text_t pStruct)
{
    int i;
    for(i = 0; i < pStruct->cntReal; i++)
    {
        printf("%i. %s (%i)\n", i, pStruct->StrIn[i].pStr, pStruct->StrIn[i].formatting);
    }
}
