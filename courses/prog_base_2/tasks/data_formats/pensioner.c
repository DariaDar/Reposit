#include "pensioner.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct work
{
    char * profession;
    int experience;
}WORK;


typedef struct pensioner_s
{
    char * name;
    char * surname;
    char * birthdate;
    int grumpiness;
    double pension;
    WORK group;
}PENSIONER;

pensioner_t pensioner_new()
{
    pensioner_t pPens = malloc(sizeof(PENSIONER));
    return pPens;
}

void pensioner_delete(pensioner_t pPens)
{
    free(pPens);
}

void pensioner_set(pensioner_t pPens, char * n, char * s, char * d, char * p, char * g, char * pr, char * e)
{
    pPens->name = n;
    pPens->surname = s;
    pPens->birthdate = d;
    pPens->pension = atof(p);
    pPens->grumpiness = atoi(g);
    pPens->group.profession = pr;
    pPens->group.experience = atoi(e);
}

void pensioner_print(pensioner_t pPens, int i)
{
    printf(">>>>Pensioner %i<<<<<\n\n", i+1);
    printf("Name: %s\nSurname: %s\nBirthdate: %s\nPension: %f\nGrumpiness (1-10): %i\n", pPens->name, pPens->surname, pPens->birthdate, pPens->pension, pPens->grumpiness);
    puts("----Work----");
    printf("Profession: %s\nExperience (years): %i\n", pPens->group.profession, pPens->group.experience);
    puts("------------\n\n");

}
