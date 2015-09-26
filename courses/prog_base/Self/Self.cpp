// Self.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"


int _main()
{
	int h,m,code;
float price;
scanf ("%i %i %i", &code, &h, &m);
switch (code){
case 44: price=0.44*(h*60+m);
	break;
case 66: price=1.05*(h*60+m);
	break;

	case 111:price=0;
		break;
	case 1:price=30*(h*60+m);
		printf("price %f", price);
	   break;
}
	return 0;
}

