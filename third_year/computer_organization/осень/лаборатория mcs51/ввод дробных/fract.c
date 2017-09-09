#include <reg51.h>
// #include "inter.c"
 
 typedef unsigned int u16;
  typedef unsigned char u8;
  typedef unsigned long u32;
 
 u8 fd2( u8 x){	//перевод char-целого 10.2 

	return (((x&0xf0)>>4)*10 + (x&0xf));
	}
u8 f2d(u8 x){  //перевод char-целого 2.10
	 return ((x/10)<<4) | (x%10)  ;
	 }
	
u32 trd2()	  //перевод int-целого 10/2 -> 2/10
{    u16 N; 
	 N= fd2(P0)*100 + fd2(P1);
	 P2= f2d(N/100); 
	 P3=f2d((N%100));
     return (u32)N;
     }
 u32 M;
 u32 Z;

 u8 tr2d(u16 x){   //перевод char-дробного 2/10 в формате int 
     u16 y=x*10;
    return ((y&0xf00)>>4) |((((y&0xff)*10)&0xf00)>>8); 
   }

u8 i,k;

 main(){   
	//M=(trd2()<<16)/10000;  // перевод int-дробного 10/2 в формате long m=2^16
	 Z=trd2(); M=(((((Z/100)<<8)+ (((Z%100))<<8)/100))<<8)/100;      
	 /*
	P2=f2d((M*100)>>16);  //перевод int-дробного 2/10 в формате long
	Z=(M&0xffff)*100;
	P3=f2d(Z>>16);
	 */
	 i=((M>>8)*100)>>8;
	 k=((((M>>8)*100)+(M&0xff))*100)>>8;
	 P2=f2d(i);
	 P3=f2d(k);

	}
