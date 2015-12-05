#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//VAR 23

int main()
{
    time_t t;
    srand(time(&t));

    int n, i, min;
    int dis = 0;
    printf("Enter size of arrays:");
    scanf("%i", &n);

    int arr1[n];
    int arr2[n];
    int resArr[n];
    //Заполняем рандомом
    for(i = 0; i < n; i++)
    {
        arr1[i] = rand()%100;
        arr2[i] = rand()%100;
    }
    //Печатаем массивы
    printf("Arr1: ");
    for(i = 0; i < n; i++)
    {
        printf("%i, ", arr1[i]);
    }
    printf("\n\nArr2: ");
    for(i = 0; i < n; i++)
    {
        printf("%i, ", arr2[i]);
    }
    printf("\n");

    //Минимальный элемент
    min = abs(arr1[0] - arr2[0]);
    //Записываем разницы в массив, находим минимальную
    for(i = 0; i < n; i++)
    {
        resArr[i] = abs(arr1[i] - arr2[i]);
        dis = abs(arr1[i] - arr2[i]);
        if(dis <= min)
        {
            min = dis;
        }
    }

    printf("\nResArr: ");
    for(i = 0; i < n; i++)
    {
       printf("%i, ", resArr[i]);
    }
    printf("\n\nMin = %i", min);

    return 0;
}
