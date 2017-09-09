




      Aa equ A     ;делимое
      S equ R1     ;делитель 
	  B equ R2	   ;частное делимое
	  i equ R0

    cesg at 0
	start;
	  mov a,P0 ;делимое
	  mov B,P1 ;делитое.частное
	  mov a,S  ;делитель 
	  subb a,B	  ;	if(S>=Aa) {OV=1; goto out;}
	  jc m1
	  sbit OV
	  jmp out
	  mov i,#0
	  add a,B  	   ;восстановление делимого
	  clr c   ;
cikl: rlc a
      xch a,B	    ;S<<1
	  rlc a
	  xch a,B
	  subb a,B
      jnc m1
	   orl B,#01
	   setb C
	   inc i
	   cjne i,8,cikl
  m1:
  
  for (i=0 ; i<8; i++ )    
         S= (((S<<1)-Aa)>=0) ? (S<<1)-Aa +1 : S<<1 ;
out:
P3=S; //частное								
if (OV) Aa=0xff;  
}
  
