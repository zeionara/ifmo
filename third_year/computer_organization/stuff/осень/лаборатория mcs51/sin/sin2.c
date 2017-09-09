#include <reg51.h>
typedef unsigned char uchar;
    uchar x,y,S,m;
  uchar Si(uchar ai)
  { return S=m-((((y*ai)>>8)*S)>>8) ;}
	//             m  m   
  main()
  { m=0xff;
  while(1)
   for(x=0;x<m;x++)
     { y=(x*x)>>8;S=m;
	    S=Si(6);
		 S=Si(13);
		 S=Si(40);
		 P2=(S*x)>>8;}}