#include <math.h>

int satisfies(int a, int b, int c) 
{
   int result;
   int modmin;
   int sum2;
   int Sum;
   int x;
   int min;
   int max;
   int pos = 0; //������ ��������
   int neg = 0; //³�*��� ��������
   int sumPos = 0; //���� ������� �������
   int sumNeg = 0; // ���� ��*����� �������

   

   // ���� �� ����� ��*���

   if ((a < 0) && (b < 0) && (c < 0))
   { 
	   //��������� ���� ��� ����� �����
		 Sum = a + b + c;

	   // ��������� �������� �����
	   if (a <= b)
	   {
		   x = a;
	   }
	   else 
		   x= b;
	  
	   if (x <= c)
	   {
		   min = x;
	   }
	   else
		   min = c;

	   //������ �� �����
	   modmin = abs(min);

	   //���� ���� �����
	   sum2 = Sum - min;

	  
		if ((sum2 < -256) && (modmin < 256) && ((modmin == 2) || (modmin == 4) || (modmin == 8) || (modmin == 16) || (modmin == 32) || (modmin == 64) || (modmin == 128)))
			{
				result = 1;
			}
		else
		{
			if ((sum2 > modmin) && (sum2 > -256));
			{
				result = 1;
			}
				result = 0;
		}
		
	
			
   }
   
  
   //���� �� �� ����� ������
   if (((a*b) <0) || ((a*c)<0) || ((b*c) < 0))
   {
	if (a >= 0)
	{
	   pos = pos + 1;
	   sumPos = sumPos + a;
	}
	else
	{
	   neg = neg + 1;
	   sumNeg = sumNeg + a;
	}

	if ( b >= 0)
	{
	   pos = pos + 1;
	   sumPos = sumPos + b;
	}
	else
	{
	   neg = neg + 1;
	   sumNeg = sumNeg + b;
	}
   
	if (c >= 0)
	{
	   pos = pos + 1;
	   sumPos = sumPos + c;
	}
	else
	{
	   neg = neg + 1;
	   sumNeg = sumNeg + c;
	}

	// ���� 1 ����� ��*����
	if (neg == 1)
	{
	   if (sumNeg > -256)
	   {
		   result = 1;
	   }
	   else 
		   result = 0;
	}
   
	//���� 2 ����� ��*���
	if (neg == 2)
	{
	   if ((sumNeg*7) > -256)
	   {
		   result = 1;
	   }
	   else 
		   result = 0;
	}
   } 


   //���� �� ����� ������
   if ((a >= 0) && (b >= 0) && (c >= 0))
   {
	   //MAX
	   if (a >= b)
	   {
		   x = a;
	   }
	   else
		   x = b;
	   
	   if (x >= c)
	   {
		   max = x;
	   }
	   else
		   max = c;

	   //MIN
	   if (a <= b)
	   {
		   x = a;
	   }
	   else
		   x = b;

	   if (x <= c)
	   {
		   min = x;
	   }
	   else
		   min = c;

	   if (max*min < 256)
	   {
		   result = 1;
	   }
	   else 
		   result = 0;
   }

   
   return result;
}