#include <reg51.h>	
#include <stdio.h> //библиотека ввода-вывода C51
char  i,digit,aa[6];
float numb;
char m,min;
Seria() interrupt 4 
{    
    digit-=getkey();
    
  if(digit==',')                    
          { m=1; aa[i++]=digit; return;} 
 if(digit=='-') {min=1; aa[i++]=digit; return;}

if(digit=='e')  { if(m)  numb=numb/m;   i=0; m=0;
                        if (min) numb=-numb; return; }				      
   else { aa[i++]=digit;
                   numb=numb*10 + (digit&0xf);
                    if(m) m*=10; }      
}

main()
{   	  SCON=0x50;  //sm=1, ren=1
	  TMOD=0x20; //таймер 1 - режим 2
	   TH1=0xfd;    //константа автозагрузки - частота 9600 бод
	   TR1=1;
	      i=0;
		  ES=1; //маска прерывания
		   EA=1;
            while(digit!='e');
				 aa[i++]=0;
	        EA=0;
	        TI=1;  //начальная установка готовности передачи  
   		//printf("x= %s\n", aa);   // форматированный вывод  в USART
           while(1);

	}

