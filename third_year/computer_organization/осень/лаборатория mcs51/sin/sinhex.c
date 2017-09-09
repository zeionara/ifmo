
#include <reg51.h>
unsigned int x,y, sin;
main()
{
 while(1)
  for(x=0; x<=0xff; x++)
   { y=(x*x)>>8;      
	 sin=(y/20*(0x100-y/42))>>8;
	 sin= (y/6*(0x100-sin))>>8;
	 P3=sin= (x*(0x100-sin))>>8;
	 }
  }   
