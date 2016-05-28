#ifndef _PENSIONER
#define _PENSIONER

typedef struct pensioner_s
{
	int		id;
    char	name[256];
    char	surname[256];
	int		year;
	int		experience;
	float	pension;
	char	birthday[20];

} pensioner_t;

void print_pensioner(pensioner_t * ps);
void printList_pensioner(pensioner_t* arr, int len);
char * pensioner_getName(pensioner_t * ps);
char *  pensioner_getSurname(pensioner_t * ps);
int pensioner_getAge(pensioner_t * ps);
int pensioner_getExperience(pensioner_t * ps);
char * pensioner_getYear(pensioner_t * ps);
double pensioner_getPension(pensioner_t * ps);

#endif
