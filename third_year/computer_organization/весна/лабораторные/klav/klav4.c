#include <reg51.h>
 char w,x,i,digit,mas[7],min;
 float numb,m;
char code scancode[]={ 0x7b,0xdd,0xde,0x7d,0xb7,0x7e,0xe7 };     //-1,234 esc
void Delay(int t)   
  { while(t--); }
char what(void); 
scan( ) interrupt  2
{   Delay(100);  
 w=scancode[i];                                                  	  
  what();        
      Delay(100); 
      }

main ()
{     x=0xFE;    
       numb=0;
       i=0;
      m=0; 
      IT1= EX1=EA=1;
      while (digit!='e')  Delay(100);
     while(1);
 }
char what(void) 
{   switch (w)       
                 {  case 0x77: digit='0'; break; 
                     case 0x7b: digit='1'; break;
                     case 0x7d: digit='2'; break;
                    case 0x7e: digit='3'; break;
                    case 0xb7: digit='4'; break;
                    case 0xbb: digit='5'; break;
                    case 0xbd: digit='6'; break;
                    case 0xbe: digit='7'; break;
                   case 0xd7: digit='8'; break;
                    case 0xdb: digit='9'; break;
                    case 0xdd: digit='-'; break;
                    case 0xde: digit=','; break;
                   case 0xe7: digit='e'; break;
                    default: digit=0xff;		
                 }

  if(digit==',')                    
          { m=1;mas[i++]=digit; goto exit;} 
 if(digit=='-') {min=1;mas[i++]=digit;goto exit;}

if(digit=='e') 
    	{ 
         if(m)  numb=numb/m;   i=0;m=0; 
                  if(min) numb=-numb;  goto exit;
                                        }				      
   else {mas[i++]=digit;
                   numb=numb*10 + (digit&0xf);
                    if(m) m*=10; }   
					  exit: return digit; } 
