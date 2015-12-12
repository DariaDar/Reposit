#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct MOVIE
{
    char nameMov[200];
    char character[200];
};

struct MOVIE movie[] = {{"LOST", "Kate"}, {"Inseption", "Leo"}};

struct WOMEN
{
    char name[50];
    int age;
    char movie[50];
}WOMEN;

/*void str(struct * pWom, FILE * fp)
{
    fp = fopen("struct.txt", "r");
    fp(fclose);
}*/

int main()
{
    time_t t;
    t = time(NULL);
    struct WOMEN * pWoman;
    int cnt = 3;
    int i;
    FILE * fp;
    //Заполняем (выделяем память на 3 структуры)
    pWoman = calloc(cnt, sizeof(WOMEN));

    //str(pWoman, fp);

    for(int i = 0; i < cnt; i++)
    {
        printf("\nEnter actress name: ");
        scanf("%s", pWoman[i].name);
        printf("\n\nEnter actress age: ");
        scanf("%i", pWoman[i].age);
        printf("\n\nEnter actress best role: ");
        scanf("%s", pWoman[i].movie);
    }

    for(i = 0; i < cnt; i++)
    {
        printf("Name: %s\n\n", pWoman[i].name);
        printf("Age: %i", pWoman[i].age);
        printf("Role: %s", pWoman[i].movie);
    }

    free(pWoman);

    return 0;
}
