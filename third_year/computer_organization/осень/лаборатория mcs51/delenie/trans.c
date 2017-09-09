
      #include <reg51.h>
	  char i,x;    //двоичные числа  в памяти Data, 
      char  code y[ ]= "123"; //символьная строка в  памяти Code
      char  xdata yy[8]; 
	  main(){
		{     x=0; 
    for (i=0; i<3; i++)     
            x=x*10+(y[i]&0x0f);	                   
     for(i=7;i>=0; i--)   //преобразование  двоичного числа char x  в ASCII
       {  yy[i]= (x&0x01) ?   '1' :  '0' ; x=x>>1;} }
			 }
