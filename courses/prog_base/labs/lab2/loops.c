#include <stdio.h>
#include <math.h>

double calc(int n, int m)
{
    int i, j;
    double sum1 = 0, sum2 = 0;
    double x = 0, y = 0;

    for(i = 1; i <= n; i++)
    {
        sum1 = 0;
        for(j = 1; j <= m; j++)
        {
            y = pow(j, i);
            sum1 = sum1 + y;
        }
        x = sin((2*M_PI)/i)*pow(sum1, 1/2);
        sum2 = sum2 + x;
    }
    return sum2;

}

