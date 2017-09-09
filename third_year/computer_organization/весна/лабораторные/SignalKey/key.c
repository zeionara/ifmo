#include <reg51.h>
#include <stdio.h>
char x,y,i;
char aa[5];
float z=12.5;
main()
{
   for (i=0;i<5;i++)
	   aa[i]=getkey();
	   printf("aa[]= %s\n",aa);
//	   printf("z= %f\n",z);
   while(1);
}
