// UseSinCosDLL.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <math.h>
#include <stdio.h>
#include <windows.h>
#define Sin 0
#define Cos 1

 typedef int (__cdecl *MyProc)(int Regime,double xn,double xk,double dx);

int _tmain(int argc, _TCHAR* argv[])
{
	double xn,xk,dx;
   	HINSTANCE hDLL;
	MyProc SinCos;

//	hDLL = LoadLibrary("SinCos.DLL");
		hDLL = LoadLibrary("ZagDll.DLL");

	if(!hDLL)
	{
		printf("\n Library not loaded\n");
		return 1;
	}
   //SinCos=(MyProc)GetProcAddress(hDLL,(LPSTR)1);
	SinCos=(MyProc)GetProcAddress(hDLL,"SinCos");


 while(1)
 {
   printf("\n Input xn,xk,dx\n");
   if(scanf("%lf%lf%lf",&xn,&xk,&dx) == -1) break;
   printf("\n Compute Sinus");

   if(SinCos(Sin,xn,xk,dx)) 
   {printf("\n Wrong calling\n");continue;}
   printf("\n Compute Cosinus");
   if(SinCos(Cos,xn,xk,dx)) {printf("\n Wrong calling\n");continue;}
   
 }


	return 0;
}

