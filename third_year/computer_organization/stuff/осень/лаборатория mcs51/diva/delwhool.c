#include <reg51.h>
char Bb,i,j;
int S,Aa;
  
divf()
  {for( j=9 ; j>0; j-- )    
      S= (S <Aa) ? S<<1 : ((S-Aa)<<1) +1; 
	}
	 
main()
{
  S=P1<<8;
  Aa=P2<<8;
	P3=0; 
	   for(i=0;i<7;i++)
	      if(S>=Aa)
		        { Aa<<=1;PSW|=0x40; }
	       else divf(); 

  S=S>>i; P0=S;  
  while(1); 
}

