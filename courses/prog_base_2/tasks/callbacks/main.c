#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <conio.h>
typedef int (*LogCallback)();
typedef void (*LogCallback1)(int * sum, int elem);

void randomness(LogCallback equalsCB, LogCallback1 oppositeCB, int * sum)
{
    srand(time(NULL));
    int a;
    int b;
    while (!kbhit())
    {
        a = rand() % 10000 - 5000;
        b = rand() % 10000 - 5000;
    if ( a == b)
        equalsCB();
    if (a + b == 0)
        oppositeCB(sum, -abs(b));
    }
}

int equals_func1 ()
{
    printf("Equals\n");
    return 0;
}
int equals_func2 ()
{
     printf("The same numbers.\n");
     return 0;
}

void opposite_func1 (int * sum, int elem)
{
    printf("%i, %i\n", elem, -elem);
    *sum += elem;
}

void opposite_func2 (int * sum, int elem)
{
    printf("First: %i, second: %i\n", elem, -elem);
}

int main(void)
{
    LogCallback equals1 = equals_func1;
    LogCallback1 opposite1 = opposite_func1;
    //LogCallback equals1 = equals_func2;
    //LogCallback1 opposite1 = opposite_func2;
    int sum = 0;
    randomness(equals1, opposite1, &sum);
    printf("sum = %i", sum);
    getchar();
    return 0;
}
