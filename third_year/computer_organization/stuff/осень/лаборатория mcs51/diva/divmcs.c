   #include <reg51.h>
#include <intrins.h> //библиотека макросов
sbit Bi=B^0;        //бит регистра B

char  i;
char Aa;              //аккумулятор

main(){
char  wrk=P0;  //wr множимое
Aa=0;         //reset
 B=P1;              //wr множитель
for(i=-8;i!=0;i++)    //wr i,  i+1
 {if(Bi) Aa=Aa+wrk;
 Aa=_cror_(Aa,1); B=cror_(B,1);}
 P2=Aa; P3=B;
 }
