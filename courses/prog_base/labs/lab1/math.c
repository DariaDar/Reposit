#include <math.h>

double calc(double x, double y, double z) 
{
	double a;

	if ((x == -y) || (x==y) || (z == 0) || (sin(y) == 0) )
	{
		return NaN;
	}
	else
	{
		a = pow(x, y+1)/pow(x-y, 1/z) + y/(8*fabs(x+y)) + pow(x, 1/fabs(sin(y)));
	
	}
	return a;
}