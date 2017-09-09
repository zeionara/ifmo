  #include <reg51.h>
 typedef unsigned int u16;
  typedef unsigned char u8;
  typedef unsigned long u32;
 
 u16 fd2( u16 x){

	return (((x&0xf0)>>4)*10 + (x&0xf));
	}
u8 f2d(u16 x){
	 return ((x/10)<<4) | (x%10)  ;
	 }
	
u32 trd2()
{    u16 N; 
	 //P3=f2d(fd2(P1));
	 N= fd2(P0)*100 + fd2(P1);
	 P2= f2d(N/100); 
	 P3=f2d((N%100));
     return N;
     }
