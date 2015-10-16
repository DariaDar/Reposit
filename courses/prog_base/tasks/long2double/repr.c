#include "stdafx.h"
#include <string.h>
#include <math.h>
#include <Manipulations.h>

double long2double(long long);

int main()
{
	long long number = 0;
	double result;

	scanf_s("%lld", &number);

	result = long2double(number);
	printf("%.325llf", result);

	return 0;
}

double long2double(long long number)
{
	double mantissa = 0; // Мантисса,
	double mantissaNorm = 0;
	long long E = 0;  //Порядок (экспонента)
	int znak; // знак
	int i; // счетчик

	double value = 0; // кінцевий результат
	long long t = number;
	
	double M0 = 0; // Мантисса
	int n = -52; // Степень
	int bitM = 0; //bit мантиссы
	
	// Выделяем мантиссу
	for (i = 0; i <=51; i++)
	{
		bitM = (t >> i) & 1;
		M0 = bitM * pow ((double) 2, n);
		mantissa = mantissa + M0;
		n = n + 1;
	}

	mantissaNorm = mantissa + 1.0;

	// Находим экспоненту
		
	    E = t >> 52;
		E = 0x00000000000007FF & E; 

		//E = E - 1023; Нормализованная
		
	//Знак
		if (((t >> 63) & 1) == 0)
		{
			znak = 0;
		}
		else
		{
			znak = 1;
		}

		// Условия:
		//+-INF
		if ((E == 2047) && (mantissa == 0))
		{
			if (znak == 0)
			{
				value = POSITIVE_INFINITY;
			}
			else 
			{
				value = NEGATIVE_INFINITY;
			}
		}
		//NAN
		if ((E == 2047) && (mantissa != 0))
		{
			value = NaN;
		}
		// +-0
		if ((E == 0) && (mantissa == 0))
		{
			if (znak == 0)
			{
				value = 0;
			}
			else
			{
				value = -0;
			}
		}

		// Нормализированное
		if ((E > 0) && (E <2047))
		{
			value = pow((double)-1, znak) * pow ((double) 2, (double)(E - 1023)) * mantissaNorm;
		}

		//Денормализированное
		if ((E == 0) && (mantissa != 0))
		{
			value = pow((double) (-1), znak) * pow ((double) 2, (-1022)) * mantissa;
		}

	return (double) value;
}