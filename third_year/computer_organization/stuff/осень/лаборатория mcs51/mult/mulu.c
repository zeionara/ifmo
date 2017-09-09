#include <reg51.h>
  int  S; //S-произведение,	 формула вероятности

main(){
  unsigned int S=0;
  char i,j;
  int xdata X[256];
 char a1,a0,b1,b0;
//ввод
  for(i=0;i<16;i++)
    for(j=0;j<16;j++)
       X[(i<<4)+j]=i*j;
      a1=P1>>4; a0=P1&0x0f; b1=P2>>4; b0=P2&0x0f;
         S=((a0*b0)+((a1*b0)<<4))<<4;
        S=((S+((a0*b1)<<4))>>4)+(a1*b1);
          P0=S; P3=S>>8;
            }
