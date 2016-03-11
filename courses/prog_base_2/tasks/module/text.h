#ifndef TEXT_H
#define TEXT_H
#include <stdlib.h>

typedef struct text_s * text_t;

//constructor
text_t text_new(int cntMax, char * str);

//destructor
void text_delete(text_t p);

int text_getRealCntStr(text_t p);

void text_getList(text_t pStruct);

void text_setFormat(int index,int formatNumber, text_t pStruct);

void text_getListForm(text_t pStruct, int formatting);

void text_deleteStr(text_t pStruct, int index);

void text_Insert(text_t pStruct, int index, char * _pStr);

#endif // TEXT_H
