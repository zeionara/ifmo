
#include <reg51.h>
  typedef   unsigned char uchar;   
   uchar   i,x,y, S,m,R,n;
uchar Si()
      {   return R=((R*y)>>8)/(i<<1)/((i<<1)+1) ;}
        main()
{   m=0xff;    
 while(1)
  for(x=0; x<m; x++)
      {y=(x*x)>>8; S=m; n=4; R=x; 
        for(i=1;i<n;i++)
         S= (i%2)?  S-Si() : S+Si() ;
       P2=S;
        }
}
