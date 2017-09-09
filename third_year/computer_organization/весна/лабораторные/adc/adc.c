	#include <reg515.h>	

int mm;
unsigned int T;
unsigned char max,min,x;
float fmax;

unsigned char adc(void); //предопределение функции


	main()
	{  
	
             max=0; min=0x70; P3=0x7F;
	        while(INT0)    //ожидание INT0=P3.2pin==0
                  { adc();
				   if (P2>max) max=P2; 
	                if (P2<min) min=P2;
                   } 				   
                  mm=(max+min)/2; //среднее значение  	       
                  TMOD=1;
                  TH0=TL0=0;		
                  TR0=0;
                 while(adc()>=mm);	
                 while(adc()<=mm);	      //ожидание L/H  средней линии
		  TR0=1;
	          while(adc()>=mm);         //ожидание H/L  средней линии
                  TR0=0;
                  T=(TH0<<8)+TL0;
				  fmax= max*5.0/0x100;
		while(1);  //динамический останов
	}

unsigned char adc()
  { DAPR=0;       //запуск преобразования c опорным напряжением 5в
    while(BSY);  //задержка для завершения преобразования
	 P2=ADDAT;  //чтение результата и подтверждение его в P3 для Анализатора
	return P2;	}
 
