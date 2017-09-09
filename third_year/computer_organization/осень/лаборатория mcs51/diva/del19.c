
#include <reg51.h>
#include <intrins.h>
char Aa, wrk,B,i; 
main()
{ 
  Aa=P0; //делимое
  B= P1;       //делитель 
  C=0;  
if (Aa>=wrk){OV=1; goto out;} //контроль переполнения и завершение.
  for (i=0 ; i<8; i++ ) 
    { _crol_(Aa,1);
      if(Aa>=wrk) {  C=1;_crol_(B,1);
               Aa=(Aa -wrk) : }
     }                          
out:
P3=B; //частное
if (OV) P3=0xff;  
}
