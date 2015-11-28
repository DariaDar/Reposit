#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void fillRand2(int arr[], int size)
{
    int i;

    for (i = 0; i < size; i++)
    {
        arr[i] = rand ()%511-255;
    }

}

void printArr(int arr[], int size)
{
    int i;
    for(i = 0; i < size; i++)
    {
        printf("%i,\t", arr[i]);
    }
}

int checkRand2(int arr[], int size)
{
    int i;
    int result;

    for (i = 0; i < size; i++)
    {
        if ((arr[i] < -255) && (arr[i] > 255))
        {
            result = 0;
            break;
        }
        else
            {
                result = 0;
                break;
            }
    }

    return result;
}

float meanValue(int arr[], int size)
{
    int i;
    float sum = 0;
    float meanV;

    for (i = 0; i < size; i++)
    {
        sum = sum + arr[i];
    }
    meanV = sum/size;
    return meanV;
}


int minValue(int arr[], int size)
{
    int i;
    int Min;

    Min = arr[0];

    for(i = 0; i < size; i++)
    {
            if (arr[i] < Min)
            {
                Min = arr[i];
            }
    }
    return Min;
}

int meanIndex(int arr[], int size)
{
    float a = 0;
    float Min;
    int index = 0;
    float meanV;
    int i;


    meanV = meanValue(arr, size);

    Min = abs(arr[0] - meanV);
    for (i = 0; i < size; i++)
    {
        a = abs(arr[i] - meanV);

        if (a < Min)
        {
            index = i;
            Min = a;
        }
    }
    return index;
}

int minIndex(int arr[], int size)
{
    int i, min, index;
    min = arr[0];
    for (i = size - 1; i >= 0; i--)
    {
        if (min >= arr[i])
        {
            min = arr[i];
            index = i;
        }
    }
   return index;

}


int maxOccurance(int arr[], int size)
{
    int n = 1;
    int x = 0;
    int i;

    for(i = 1; i < size; i++)
    {
        if (arr[x] == arr[i])
        {
            n = n + 1;
        }
        else
        {
            n = n - 1;
        }
        if (n == 0)
        {
            x = i;
            n = 1;
        }
    }
    return arr[x];
}

void fillRan2(int arr1[], int arr2[], int size)
{
    int i, j;

    for(i = 0; i < size; i++)
    {
        arr1[i] = rand()%511 - 255;
        arr2[i] = rand()%511 - 255;
    }
}

int diff(int arr1[], int arr2[], int res[], int size)
{
    int i;
    int n = 0;
    int result;

    for(i = 0; i < size; i++)
    {
        res[i] = arr1[i] - arr2[i];
        if (res[i] == 0)
        {
            n = n + 1;
        }
    }

    if (n == size)
    {
        result = 1;
    }
    else
        result = 0;

    return result;
}

void rizn(int arr1[], int arr2[], int res[], int size)
{
    int i;

    for(i = 0; i < size; i++)
    {
        res[i] = arr1[i]/arr2[i];
        if(arr2[i] == 0)
        {
            res[i] = 0;
        }
    }
}

void printArrDiv(int res[], int size)
{
    int k;
    printf("res:\n");
    for(k = 0; k < size; k++)
    {
        printf("%i,\t", res[k]);
    }
    printf("\n\n");
}

int gt(int arr1[], int arr2[], int size)
{
    int i, num1, num2;
    int gt;
    for(i = 0; i < size; i++)
    {
        if (arr1[i] <= arr2[i])
        {
          return 0;
        }
    }
    return 1;

}

void land(int arr1[], int arr2[], int res[], int size)
{
    int i;
    for(i = 0; i < size; i++)
    {
        arr1[i] = rand()%2;
        arr2[i] = rand()%2;
    }

    for(i = 0; i < size; i++)
    {
        if(((arr1[i] == 0)||(arr1[i] == 1)) && ((arr2[i] == 0)))
        {
            res[i] = 0;
        }
        if ((arr1[i] == 1) && (arr2[i] == 1))
        {
            res[i] = 1;
        }
    }
}
