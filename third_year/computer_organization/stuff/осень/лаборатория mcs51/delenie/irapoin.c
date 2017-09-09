  
  
   #include  <reg51.h>
unsigned char x,i; //переменная в Data
char code * y="125";  //указатель на текстовую константу, имя переменной 
char xdata  * yy;       //указатель текстовой  переменной
main()
	{   for (i=0; i<3; i++) 
	        x=x*10+(*y++&0x0f);                          
                for (i=7;i>=0; i--)
                     {  *yy++= (x&0x01) ? '1' : '0';
                                x=x>>1;
		             }
  		   }
