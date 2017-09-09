
#include <reg51.h>

char d[5];   //массив битов-символов
 char count;
int period; 

intt0() interrupt 0    
{   TR0=0; TR1=0;  
 	   period= (TH1<<8)| TL1;
      if(TL0 <110)  //S0=3 ' D=300/3=100
		d[count] = '0';
	 else d[count] = '1';
			count++;
                  if (count==4)  count=0;  
       TL1=0; TH1=0; TL0=0; TH0=0;
	   TR0=1; TR1=1;
}

main(){ P3=0x3F;
        count = 0;
		TMOD = 0x019; //таймер 0 в режиме Gate
        IT0 = 1;
		EX0=1; 
	    EA = 1;
		TL1=0; TH1=0; TL0=0; TH0=0;
		//TR0 = 1;
		//TR1=1;			
		while(1);
		}
