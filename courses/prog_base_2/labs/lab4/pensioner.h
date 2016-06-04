#ifndef _PENSIONER
#define _PENSIONER
#include "cJSON.h"

typedef struct pensioner_s
{
    int id;
    char	name[256];
    char	surname[256];
	int		experience;
	double	pension;
	char	birthday[20];
} pensioner_t;

pensioner_t * pensioner_new();
void pensioner_delete(pensioner_t * pens);

pensioner_t * pensioner_set(pensioner_t * pens, int id, char * birthday, char * name,
                            char * lastname, double pension, int experience);
int pensioner_getID(pensioner_t * ps);
char * pensioner_getName(pensioner_t * ps);
char *  pensioner_getSurname(pensioner_t * ps);
int pensioner_getExperience(pensioner_t * ps);
char * pensioner_getYear(pensioner_t * ps);
double pensioner_getPension(pensioner_t * ps);
char * pensioner_toJSON(pensioner_t * pens);
char * pensioner_toHTML(pensioner_t * pens, int id);

#endif
