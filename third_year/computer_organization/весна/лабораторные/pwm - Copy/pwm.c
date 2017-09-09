
#include <reg51.h>

char d[8];   //массив битов-символов
 char count,i,sta;
unsigned int period,Pi0=0,Pi1; 

intt0() interrupt 0    
{       TR1=0;
      if((TL1==0)&&(sta==0))goto fin;   
 	   Pi1= (TH1<<8)| TL1;
	   TR1=1;
	   period=Pi1-Pi0;
	   Pi0=Pi1;
	   
      if(TL0 <110)  //S0=3 ' D=300/3=100
		d[count] = '0';
	 else d[count] = '1';
			count++;
                  if (count==9)  count=0;  
fin:       TL0=0; TH0=0;sta=0;
	   TR0=1; 

}

main(){ 
        count = 0;
		TMOD = 0x019; //таймер в режиме Gate
        IT0 = 1;
		EX0=1; 
	    EA = 1;
		P3=0;
		TL1=0; TH1=0; TL0=0; TH0=0;
		TR0=TR1=1; 			
		while(1);
		}
