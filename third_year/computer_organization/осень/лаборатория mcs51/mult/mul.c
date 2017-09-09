  //Si+1=2-1(Si+Abn-i) 
#include <reg51.h>

main()
{
  long S;
  unsigned int A;
  char i;
   S=P0;
   A=P1<<8;
  for(i=0;i<8;i++)
     S= (S&1)? (S+A)>>1 : S>>1;
   P2=S>>8;
   P3=S;
}