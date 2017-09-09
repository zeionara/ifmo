	  #include <reg51.h>
	  unsigned int x,y,z;
	 main(){  
	 //while(1)
	 //for (x=0;x<0x0FF;x++){ 
	   x=0xfa;
	   y= x>>2;
	   y=(x*(0x041 -y))>>8;
	   y= (0x080 -y );
	   z= (x*x)>>8;
	   	y= (z*y)>>8;
	  P2= x-y; 
	  }
	  
	   Отладка фнкции log(1+x)~ x- x2/2+x3/3-x4/4  = x- x2(1/2 - x(1/3 - x/4))
                                  С масштабом  255-256    
                                                    = x- (((x*x)>>8)*(0x80 - (x*(0x41 - (x>>2))>>8))>>8)
Unsigned int x,y,z; - все разности  положительные

#include <reg51.h>
	  unsigned int x,y,z;
	 main(){  
	 //while(1)
	 //for (x=0;x<0x0FF;x++){ 
	   x=0xff;
	   y= x>>2;
	   y=(x*(0x041 -y))>>8; //здесь должно быть максимально точное округление 256/4
	   y= (0x080 -y );
	   z= (x*x)>>8;     //ошибочный знаковый сдвиг при int
	   	y= (z*y)>>8; 
	  P2= x-y;   //P2=0x84
	  }
