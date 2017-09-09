#include <reg51.h>
#include <intrins.h>

sbit Bi=B^0;
char i;
char Aa;

main(){
char wrk=P0;
 B=P1;
for(i=8;i>0;i--)
 {if(Bi) Aa=Aa+wrk;
 Aa=_cror_(Aa,1); B=_cror_(B,1);}
 P2=Aa; P3=B;
 }