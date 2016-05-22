#include <stdio.h>
#include <stdlib.h>
#include "nlp.h"

int main()
{
    char dali[10] = "dali.txt";
    char stop[15] = "stopWords.txt";
    text_t * text = text_new();
    text_readFile(text, dali);
    text_readStopWords(text, stop);
    text_onSentences(text);
    text_counting(text);
    text_writeFile(text, "output.txt");

    text_delete(text);
    return 0;
}
