#include <stdlib.h>
#include <stdio.h>

#include "pensioner.h"

void print_pensioner(pensioner_t * ps)
{
	if(ps == NULL)
	{
		printf("Error. Pointer to  pensioner struct = NULL\n");
		return;
	}
	printf("Id: %d\nName: %s\nSurname: %s\nYear: %d\nExperience: %i\nPension: %.1f\nBirthday: %s\n\n",
        ps->id, ps->name, ps->surname, ps->year, ps->experience, ps->pension, ps->birthday);
}
void printList_pensioner(pensioner_t* arr, int len)
{
	for (int i = 0; i < len; i++)
	{
        print_pensioner(&arr[i]);
    }
}

char * pensioner_getName(pensioner_t * ps)
{
    return ps->name;
}
char *  pensioner_getSurname(pensioner_t * ps)
{
    return ps->surname;
}
int pensioner_getAge(pensioner_t * ps)
{
    return ps->year;
}
int pensioner_getExperience(pensioner_t * ps)
{
    return ps->experience;
}
char * pensioner_getYear(pensioner_t * ps)
{
    return ps->birthday;
}
double pensioner_getPension(pensioner_t * ps)
{
    return ps->pension;
}

