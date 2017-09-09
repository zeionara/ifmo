
#include <reg51.h>
unsigned char x,y, sin;
main()
{
 while(1)
  for(x=0; x<=0xff; x++)
   { y=(x*x)>>8;      
	 sin=(y/20*(0-y/42))>>8;
	 sin= (y/6*(0-sin))>>8;
	 P3=sin= (x*(0-sin))>>8;
	 }
  }   
