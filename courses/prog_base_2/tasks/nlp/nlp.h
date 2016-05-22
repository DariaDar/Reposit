#ifndef NLP_H
#define NLP_H

#define MAX_CNT_W 50
#define MAX_CNT_S 3000

typedef struct stopWords_s stopWords_t;
typedef struct word_s word_t;
typedef struct sentence_s sentence_t;
typedef struct text_s text_t;


word_t * word_new(char * word);
void word_delete(word_t * w);

sentence_t * sentence_new();
void sentence_delete(sentence_t * s);

text_t * text_new();
void text_delete(text_t * t);
void text_readFile(text_t * t, char * fileName);
void text_readStopWords(text_t * t, char * filename);
void text_onSentences(text_t * t);
void sentence_onWords(sentence_t * s);
void text_counting(text_t * t);

void text_writeFile(text_t * t, char * fileName);



#endif // NLP
