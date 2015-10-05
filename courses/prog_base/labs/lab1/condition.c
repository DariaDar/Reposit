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
   int pos = 0; //ƒодатн≥ значенн€
   int neg = 0; //¬≥д*Їмн≥ значенн€
   int sumPos = 0; //—ума додатн≥х значень
   int sumNeg = 0; // —ума в≥д*Їмних значень

   

   // якщо вс≥ числа в≥д*Їмн≥

   if ((a < 0) && (b < 0) && (c < 0))
   { 
	   //знаходимо суму вс≥х трьох чисел
		 Sum = a + b + c;

	   // знаходимо м≥н≥мальне число
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

	   //модуль м≥н числа
	   modmin = abs(min);

	   //сума двох ≥нших
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
   
  
   //якщо не вс≥ числа додатн≥
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

	// якщо 1 число в≥д*Їмне
	if (neg == 1)
	{
	   if (sumNeg > -256)
	   {
		   result = 1;
	   }
	   else 
		   result = 0;
	}
   
	//якщо 2 числа в≥д*Їмн≥
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


   //якщо вс≥ числа додатн≥
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