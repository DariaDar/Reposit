#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

struct CITIES
{
    char name[100];
    int cntPeople;
    char country[100];
}CITIES;


int count(int size, struct CITIES arr[size])
{
    int i, cntCity = 0;
    for(i = 0; i < size; i++)
    {
       if(arr[i].cntPeople > 1000000)
       {
           cntCity = cntCity + 1;
       }
    }
    return cntCity;
}

void change(struct CITIES * p, const char * newName)
{
  strcpy(p->name,newName);
}

void print(struct CITIES * p)
{
   printf("\n\nYour changes: %s, %i, %s\n\n", p->name, p->cntPeople, p->country);
}


int main()
{
    int size, i, n;
    const char newName[100];

    struct CITIES city[] = {
                            {"Copenhagen",562379,"Denmark"},
                            {"Vienna",1741000,"Austria"},
                            {"Hamburg",1734000,"Germany"},
                            {"Stockholm",789024,"Sweden"},
                            {"Kyiv",2804000,"Ukraine"},
                            {"Brussels",177307,"Belgium"}
                    };

    size = sizeof(city)/sizeof(CITIES);

     for(i = 0; i < size; i++)
    {
        printf("%i. %s, %i, %s\n\n", i, city[i].name, city[i].cntPeople, city[i].country);
    }

    printf("Cities, where more 1 000 000 people: %i\n\n", count(size,city));

    printf("Enter index of the city that you want to rename: ");
    scanf("%i", &n);
    printf("Enter new name of the city: ");
    scanf("%s", newName);

    change(&city[n],newName);
    print(&city[n]);


    return 0;
}
