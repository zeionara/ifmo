#include <reg51.h>
typedef unsigned char uchar;
    uchar x,y,S,m;
  uchar Si(uchar ai)
  { return S=m-((y/ai*S)>>8) ;}
  main()
  { m=100;
  while(1)
   for(x=0;x<m;x++)
     { y=(x*x)>>8;S=m;
	    S=Si(42);
		 S=Si(20);
		 S=Si(6);
		 P2=(S*x)>>8;}}