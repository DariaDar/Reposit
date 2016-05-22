#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nlp.h"
#include "list.h"

struct stopWords_s
{
    char word[20];
    int cnt;
};

struct word_s
{
    char * word;
};

struct sentence_s
{
    char * str;
    list_t * words;
};

struct text_s
{
    list_t * sentences;
    char * textBuf;
    stopWords_t * stopWords;
    int cntStopWords;
};

///>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<///

word_t * word_new(char * word)
{
    word_t * w = calloc(1, sizeof(struct word_s));
    w->word = malloc((strlen(word) + 1) * sizeof(char));
    strcpy(w->word, word);
    return w;
}

void word_delete(word_t * w)
{
    free(w->word);
    free(w);
}


///>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<///
sentence_t * sentence_new(char * str)
{
    sentence_t * s = calloc(1, sizeof(struct sentence_s));
    s->str = malloc((strlen(str) + 1) * sizeof(char));
    strcpy(s->str, str);
    s->words = list_new();
    return s;
}

void sentence_delete(sentence_t * s)
{
    for(int i = 0; i < list_getSize(s->words); i++)
    {
        word_delete(list_get(s->words, i));
    }
    list_free(s->words);
    free(s->str);
    free(s);
}

///>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<///

text_t * text_new()
{
    text_t * t = calloc(1, sizeof(struct text_s));
    t->sentences = list_new();
    return t;
}

void text_delete(text_t * t)
{
    for(int i = 0; i < list_getSize(t->sentences); i++)
    {
        sentence_delete(list_get(t->sentences, i));
    }
    list_free(t->sentences);
    free(t->stopWords);
    free(t->textBuf);
    free(t);
}


void text_readFile(text_t * t, char * fileName)
{
    FILE * fp = fopen(fileName, "rb");
    if(fp == NULL)
    {
        printf("Error!");
        return;
    }
    fseek(fp,0,SEEK_END);
    long length = ftell(fp);
    fseek(fp,0,SEEK_SET);
    t->textBuf = calloc(length, sizeof(char));
    fread(t->textBuf, length, sizeof(char), fp);
    fclose(fp);
}

void text_readStopWords(text_t * t, char * filename)
{
    FILE * fp = fopen(filename, "r");
    char str[20];
    int cnt = 0;
    while(!feof(fp))
    {
        fgets(str, 20, fp);
        cnt++;
    }
    t->cntStopWords = cnt;
    t->stopWords = calloc(cnt, sizeof(struct stopWords_s));
    fseek(fp, 0, SEEK_SET);
    for(int i = 0; i < cnt; i++)
    {
        fgets(t->stopWords[i].word, 20, fp);
        int length = strlen(t->stopWords[i].word);
        t->stopWords[i].word[length - 1] = 0;
        t->stopWords[i].cnt = 0;
    }
    fclose(fp);
}

void text_onSentences(text_t * t)
{
    char * str;

    str = strtok(t->textBuf, ".?!");
    while (str != NULL)
    {
        sentence_t * sent = sentence_new(str);
        list_push_back(t->sentences, sent);
        str = strtok(NULL, ".?!");
    }
    for(int i = 0; i < list_getSize(t->sentences); i++)
    {
        sentence_onWords(list_get(t->sentences, i));
    }
}

void sentence_onWords(sentence_t * s)
{
    char * str;
    str = strtok(s->str, " ,:();");

        while (str != NULL)
        {
            word_t * wor = word_new(str);
            list_push_back(s->words, wor);
            str = strtok(NULL, " ,:();");
        }
}

void text_counting(text_t * t)
{
    int cntW = 0;
    for(int i = 0; i < t->cntStopWords; i++)
    {
        for(int j = 0; j < list_getSize(t->sentences); j++)
        {
            sentence_t * sent = list_get(t->sentences, j);
            for(int k = 0; k < list_getSize(sent->words); k++)
            {
                sentence_t * sent2 = list_get(t->sentences, j);
                word_t * wComp = list_get(sent2->words, k);
                if(strcmp(t->stopWords[i].word, wComp->word) == 0)
                    cntW++;
            }
        }
        t->stopWords[i].cnt = cntW;
        cntW = 0;
    }
}

void text_writeFile(text_t * t, char * fileName)
{
    FILE * fp = fopen(fileName, "w");
    if(fp == NULL)
        return;
    char str[50];

    for(int i = 0; i < t->cntStopWords; i++)
    {
        sprintf(str, "%s: %i\n", t->stopWords[i].word, t->stopWords[i].cnt);
        fwrite(str, strlen(str), sizeof(char) , fp);
    }

    fclose(fp);
}
