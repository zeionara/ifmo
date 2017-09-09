	   #include <reg515.h>	

int mm;
unsigned int T;
unsigned char max,min;

unsigned char adc(void); //ожидание завершения переобразования
	main()
	{  
             max=0; min=0x70;
			      while(INT0)	   //ожидание INT0=0
                  { if (adc()>max) max=P2; 
	                if (adc()<min) min=P2;
                   } 				   
                  mm=(max+min)/2; //среднее   	       
                  TMOD=1;
                  TH0=TL0=0;		
                  TR0=0;
                 while(adc()>=mm);	//ожидание H/L  средней линии
		TR0=1;
	    while(adc()<=mm);         //ожидание L/H  средней линии
                  TR0=0;
                  T=(TH0<<8)+TL0;
				  while(1);  //динамический останов

	}
 unsigned char adc(void)
  {  unsigned char x;
    DAPR=0;  
     while(BSY);  	//ожидание завершения преобразования
    return P2=x=ADDAT; 
		}
