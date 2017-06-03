#include "stdafx.h"
#include <math.h>
#include <stdio.h>
#define Sin 0
#define Cos 1

int SinCos(int Regime,double xn,double xk,double dx)
{
	char function[2][20]={" Sin(x)  "," Cos(x)  "};
	double x;

	if(Regime != Cos && Regime != Sin) return 1;
	if(xn >xk) return 2;
	printf("\n------------------");
	printf("\n|   x    |%s|",function[Regime]);
	printf("\n--------------------");
	for(x=xn; x <=xk+0.001; x+=dx)
	{
     if(Regime == Sin)
	 printf("\n|%7.2lf |%7.3lf  |",x,sin(x));
	 else
		 printf("\n|%7.2lf |%7.3lf  |",x,cos(x));
	}
	printf("\n--------------------");
	return 0;

}