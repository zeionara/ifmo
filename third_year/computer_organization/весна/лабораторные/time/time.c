#include <reg51.h>

unsigned    char sec,min;   
unsigned   int count=0, time;
intt0() interrupt 1  //счетчик	
{ P2=0; 
  TH0=  (-5000)>>8;
  TL0=  (-5000);
  count++;  //счетчик переполнений
	time+=10;
  if(count==200 ) {sec++;count=0;} 
  if(sec== 60 ){min++; sec=0;}
  P2=0x7f; 
   }
main()
{ 
  TMOD=1;  //16- бит таймер Tm0     
  ET0=1;       //маска TF0
  TR0=1;      //разрешение счета Tm0
  EA=1;       //разрешение прерываний
  while(1)    
    { P1=sec;
	    //P2=min;
		 }
}
