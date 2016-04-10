#ifndef PENSIONER_H
#define PENSIONER_H

typedef struct pensioner_s * pensioner_t;

pensioner_t pensioner_new();
void pensioner_delete(pensioner_t pPens);
void pensioner_set(pensioner_t pPens, char * n, char * s, char * d, char * p, char * g, char * pr, char * e);
void pensioner_print(pensioner_t pPens, int i);

#endif // PENSIONER_H

