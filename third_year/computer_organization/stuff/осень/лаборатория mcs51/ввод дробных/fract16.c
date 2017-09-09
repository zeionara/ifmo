#include <reg51.h>
typedef unsigned int u16; 
typedef unsigned char u8;
typedef unsigned long u32;
u32 N;

u16 fd2(u8 x){    ;перевод 10/2 двух цифр в целый m=100
   return (((x&0xf0)>>4)*10 + (x&0x0f)); }
    
u8 f2d(u32 y){    ;перевод из int 2/10  двух старших цифр m=2^8 
     u16 yy;
	 yy= ((y*100)&0xff0000)>>16;
	 return  ((yy/10)<<4)| (yy%10);
    }

u8 f2dm(u32 y){   ;перевод из int 2/10  двух младших цифр m=2^8 
     u16 yy;
	 yy= (((y*100)&0xffff)*100)>>16;
	 return  ((yy/10)<<4)| (yy%10);
    }

main()
{   while(1)
    {
	N=fd2(P0)*100 + fd2(P1);
	N=(N<<16);
	N/=10000;
	P2=f2d(N);
	P3=f2dm(N);
     }    
}
