#include <reg51.h>

main()
{ int S=P1<<8 ;
   int A=P2<<8 ;
   char i;
while(1)
  for (i=0 ; i<8; i++ )    
         P3=S= (((S<<1)-A)>=0) ? (S<<1)-A +1 : S<<1 ;
}
