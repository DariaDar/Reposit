#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//VAR 23

/*char toBinary(int size, char * numb)
{
    char bNum[100];
    int i, x, a;
    for(i = 0; i < size; i++)
    {
        x = numb[i];
    }


    return bNum;
}*/

double toNormal(int size, char * numb)
{
    int sum = 0;
    int x, a, i;
    for(i = 0; i < size; i++)
    {
        x = numb[i];
        a = x^(size-i);
        sum = sum + a;
    }
    return sum;
}
int main()
{
    char numb[100];
    int size;
    double a = 0;
    printf("Enter your number: ");
    scanf("%s", numb);

    size = strlen(numb)/sizeof(numb[0]);

    a = atof(numb);
    if(a == 0)
    {
        printf("Error!");
        return 0;
    }
    //toBinary(size,numb);
    printf("Normal: %f", toNormal(size,numb));
    return 0;
}
