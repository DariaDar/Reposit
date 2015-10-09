#include <math.h>

int exec(int op, int a, int b) 
{
	int result, res;
	int c;

	if (op < 0)
	{
		op = -op;
		c = a;	
		a = b;
		b = c;
	}

	scanf_s( "%i %i %i", &op, &a, &b);
	switch (op)
	{
	case 0:
		result = -a;
		break;

	case 1:
		result = a+b;
		break;

	case 2:
		result = a-b;
		break;

	case 3:
		result = a*b;
		break;

	case 4:
		result = a/b;
		break;

	case 5:
		result = abs(a);
		break;

	case 6:
		result = (int)pow((double)a,b);
		break;

	case 7:
	case 13:
	case 77:
		result = a%b;
		break;

	case 8:
		//max
		if (a>=b)
		{
			result = a;
		}
		else
		{
			result = b;
		}
		break;

	case 9:
		//min
		if (a <= b)
		{
			result = a;
		}
		else
			result = b;
		break;	

	case 10: 
		res = (abs(b) % 8);
		switch(res)
		{
		case 0:
			result = abs(a) * sizeof(char);
			break;

		case 1:
			result = abs(a) * sizeof(signed char);
			break;

		case 2:
			result = abs(a) * sizeof(short);
			break;

		case 3:
			result = abs(a) * sizeof(unsigned int);
			break;

		case 4:
			result = abs(a) * sizeof(long);
			break;

		case 5:
			result = abs(a) * sizeof(unsigned long long);
			break;

		case 6:
			result = abs(a) * sizeof(float);
			break;

		default:
			result = abs(a) * sizeof(double);
			break;
		}
		break;

	case 11:
		if (b=7)
		{
			result = 0;
		}
		else
		result = (int)(tan(a*M_PI) / (7 - b));
		break;

	default:
		if (op >= 100)
		{
			result = -1;
		}
		
		else
			{
				if ((a==-1) || (b==-1) || ((a==-1) && (b==-1)))
			 {
				result = 0;
			 }
			   else
			        result = (op % abs(a + 1)) + (op % abs(b + 1));
				break;
			}
	}
   
	return result;
}